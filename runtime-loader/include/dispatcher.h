/*
 * runtime-loader dispatcher -- public interface.
 *
 * The dispatcher lets CLIPS rules load shared-library plugins at runtime and
 * call functions they export. setup_dispatcher() installs, into a CLIPS
 * environment, the machinery that makes this work:
 *
 *   - four UDFs: LoadDispatch / UnLoadDispatch / CleanupDispatch / Dispatch
 *   - a `functions` deftemplate plus the load / unload / error rules
 *
 * Asserting a `(functions (library "...") (function "..."))` fact and running
 * the environment then dlopen/LoadLibrary's the plugin and defines a CLIPS
 * deffunction that routes calls through Dispatch into the plugin.
 *
 * CONSTRAINT -- function names must be unique across ALL libraries. The function
 * table is keyed by name process-wide, so the first library to register a given
 * name owns it until fully unloaded; requesting that name from a different
 * library is refused (the load fact's `loaded` slot is set to -4 and its `error`
 * slot explains). If you wrap two libraries that both export e.g. `Cube`, give
 * the wrappers distinct names (`lib1_Cube`, `lib2_Cube`) -- the exported symbol
 * must have the CLIPS UDF signature `void name(Environment*, UDFContext*,
 * UDFValue*)`, so the wrapper author already controls the name.
 *
 * TWO LIFETIMES -- understand these before calling teardown_dispatcher():
 *
 *   PER-ENVIRONMENT state -- the `functions` template, the rules, the UDFs, and
 *     the generated deffunctions. Created by setup_dispatcher(env); destroyed
 *     automatically by DestroyEnvironment(env).
 *
 *   PROCESS-GLOBAL state -- the table of loaded libraries, the table of resolved
 *     function pointers, and the lock guarding them. Shared by EVERY environment
 *     that calls setup_dispatcher(); persists until teardown_dispatcher() frees
 *     it.
 *
 * TWO-TIER LIFECYCLE -- `unload` and `cleanup` do different jobs:
 *
 *   UNLOAD (the "bounce") -- `(functions ... (action "unload"))` with `loaded 1`.
 *     Releases the LIBRARY (removes the global function entry; dlclose/FreeLibrary
 *     once no entry still references that library) and leaves `loaded 0`. It
 *     deliberately KEEPS this environment's generated deffunction wrapper, whose
 *     body is just `(Dispatch <name> (expand$ ?args))` -- it references the
 *     permanent Dispatch UDF and a name string, never the library. Consequences:
 *       * unload ALWAYS succeeds; defrules that call the function do not block it,
 *         and are left untouched;
 *       * while unloaded the wrapper is inert -- a call fails safe to FALSE;
 *       * re-asserting `(action "load") (loaded 0)` repopulates the table and the
 *         SAME wrapper works again.
 *     That is the point: a running process can unload a plugin, replace the file
 *     on disk, and reload it without tearing down or rebuilding any rules.
 *
 *   CLEANUP (retire the name) -- `(functions ... (action "cleanup"))`. Removes the
 *     wrapper, so the name stops existing in this environment: a subsequent call
 *     is an unknown-function error rather than FALSE. Reach for it when a plugin's
 *     legitimate results include FALSE -- e.g. a predicate returning
 *     TRUE/FALSE/FAIL, where an unloaded FALSE is indistinguishable from a real
 *     answer -- or when you are retiring the feature outright. Success leaves
 *     `loaded 2` (terminal).
 *
 *     ORDER DOES NOT MATTER. Cleanup and unload are orthogonal: cleanup never
 *     touches the library or the global table, and unload never touches the
 *     wrapper. Cleanup is accepted whether the function is currently loaded or
 *     not, so all of these are valid:
 *         unload then cleanup      -- release the library, then retire the name
 *         cleanup then unload      -- retire the name, then release the library
 *         cleanup alone            -- retire the name here, LEAVE the library
 *                                     loaded for other environments
 *         cleanup then load        -- retire the old wrapper, then load again to
 *                                     build a fresh one (and new rules around it)
 *     The last two matter because unload is process-GLOBAL while cleanup is
 *     environment-LOCAL: an environment must be able to retire its own wrapper
 *     without pulling the library out from under other environments.
 *     Cleanup is REFUSED (-31) while any construct references the wrapper: CLIPS
 *     counts a deffunction as busy for every construct whose body installs a call
 *     to it. Removing those constructs first is the CALLER's job:
 *         (undefrule uses-cube)      ; every rule/deffunction that calls it
 *         ... assert (action "cleanup") (loaded 0), run ...
 *     Facts are irrelevant -- only constructs hold the reference.
 *
 * BOTH ARE PROCESS-GLOBAL FOR THE LIBRARY (expert) -- a loaded function has ONE
 * global table entry shared by every environment (load-once / dedup), so an
 * unload removes it for ALL environments, not just the one that ran it. Other
 * environments keep their wrappers and get FALSE from a Dispatch (fail-safe --
 * never a dangling call). Cleanup, by contrast, only removes the wrapper in the
 * environment that runs it. In a multi-environment process the recommended path
 * is still to load and not unload; let process exit reclaim everything (cf.
 * teardown_dispatcher). If you must bounce in-process, do it when no other
 * environment is mid-call on that function.
 *
 * DECLARED SHAPE (the optional `arity` slot) -- controls the wrapper that gets
 * generated for the function, and with it who validates the call:
 *
 *   arity -1 (the DEFAULT, "unspecified"):
 *       (deffunction NAME ($?args) (Dispatch NAME (expand$ ?args)))
 *     The loader stays entirely signature-agnostic -- any exported symbol can be
 *     wrapped without declaring anything, which is right for ordinary scalar
 *     functions (see the Cube / IsOdd / IsPrime examples). CLIPS accepts any call,
 *     so ALL validation lands in the plugin, which reports refusal as FAIL.
 *     CAVEAT: a $?args parameter FLATTENS multifields. Calling
 *         (F (create$ 1 2 3) (create$ 4 5))
 *     binds ?args to ONE 5-element multifield, and expand$ passes 5 loose scalars.
 *     A plugin under this wrapper therefore NEVER receives a multifield argument
 *     -- only scalars. (Returning a multifield works fine either way.)
 *
 *   arity N (0 .. 64):
 *       (deffunction NAME (?a1 ... ?aN) (Dispatch NAME ?a1 ... ?aN))
 *     Fixed parameters, so each one PRESERVES a multifield. This is the only way
 *     to pass more than one multifield: CLIPS multifields cannot nest, so nothing
 *     can be encoded inside a single one. Declaring a shape is what lets a plugin
 *     take structured arguments -- e.g. MatrixMultiply taking two 8-element
 *     matrices. An out-of-range value is refused with -7.
 *
 *   THE TRADE, and why it is per-plugin: declaring a shape moves SIGNATURE errors
 *   to CLIPS, which rejects a wrong-sized call itself ([ARGACCES1]) before the
 *   plugin runs. It does NOT take away the plugin's voice -- argument CONTENT and
 *   environment refusals (e.g. "this host has no such coprocessor") are still the
 *   plugin's to report, and still come back as FAIL. Splitting them is usually an
 *   improvement: "you called this wrong" and "I cannot run here" become two
 *   distinguishable diagnostics instead of one ambiguous FAIL.
 *
 * `loaded` SLOT VALUES -- the fact protocol reports every outcome here, and each
 * failure also fills the `error` slot with an explanatory message:
 *
 *      2  cleaned up: the wrapper was removed, the name no longer exists
 *      1  loaded and callable
 *      0  not loaded (fresh fact, or successfully unloaded -- wrapper still there)
 *     -1  the generated deffunction could not be built (non-ASCII function name?)
 *     -2  function name too long for the generated deffunction
 *     -3  the LIBRARY failed to load -- wrong path, or a dependency did not resolve
 *     -4  name collision: that function name is already loaded from a DIFFERENT
 *         library (see CONSTRAINT above)
 *     -6  the library loaded but the SYMBOL was not found in it -- wrong or
 *         misspelled function name, or it is not exported
 *     -7  the declared `arity` is out of range (use -1, or 0..64)
 *    -30  cleanup: the wrapper was deletable but removing it failed
 *    -31  cleanup: refused, the wrapper is still referenced by other constructs
 *         (or is currently executing) -- remove them and retry
 *    -32  unload: that function is not loaded (never was, or another environment
 *         already unloaded it process-globally)
 *   -200  invalid arguments (library/function were not both strings)
 *
 * CONCURRENCY -- the tables are guarded by one process-wide read/write lock:
 *   - Concurrent LOADS are safe: a load only ADDS table entries (it never frees
 *     or mutates an existing one), and the same library/function loads exactly
 *     once -- a race loser discards its handle (see F3 in CLAUDE.md).
 *   - Concurrent DISPATCH is safe: lookups are locked and a miss fails safe to
 *     FALSE.
 *   - UNLOAD and teardown_dispatcher are the exception -- they FREE entries, so
 *     they require quiescence. Unloading (or tearing down) while another thread
 *     is dispatching or loading the SAME library is undefined (a freed entry
 *     could be used). This is the "unload is expert" contract above.
 *   - The unique-name constraint holds under concurrency: if two threads load the
 *     same name from different libraries at once, exactly one wins and the other
 *     is refused (-4) -- the load never silently misroutes into the wrong library
 *     (the success path re-checks the owning library, not just the name). The one
 *     residual, best-effort part is cleanup, not correctness: the refused loser may
 *     leave its own library dlopen'd-but-unreferenced until teardown_dispatcher()
 *     reclaims it. A caller that respects the constraint never hits any of this.
 */

#include "clips.h"


/*
 * Install the runtime loader into `env`. Idempotent per environment: adds the
 * LoadDispatch/UnLoadDispatch/Dispatch UDFs, the `functions` deftemplate, and
 * the load/unload/error rules, and ensures the process-global lock exists. A
 * repeat call on the same environment is a harmless no-op (detected via the
 * `functions` template), so it is safe to call from library code that cannot
 * know whether the environment was already set up.
 *
 * Returns BE_NO_ERROR on success (or if already set up). On failure returns a
 * non-zero BuildError: BE_COULD_NOT_BUILD_ERROR if any of the loader UDFs
 * (LoadDispatch/UnLoadDispatch/Dispatch) could not be registered -- in which
 * case the dispatch mechanism is non-functional and nothing further is built --
 * otherwise the accumulated BuildError from constructing the template and rules.
 * Always check the result; a non-zero return means the environment is NOT usable
 * as a runtime loader.
 */
BuildError setup_dispatcher(Environment* env);


/*
 * EXPERT MODE -- most callers should never call this. The loader's
 * process-global state (plugin handles, tables, lock) is reclaimed by the OS at
 * process exit, so the normal, RECOMMENDED path is to simply never tear down:
 * set up environments, use them, let the process end. Reach for
 * teardown_dispatcher() ONLY to reset the loader *within* a long-running process
 * without restarting it -- an uncommon need that comes with the real trip
 * hazards spelled out below. The live-environment guard is minimum due
 * diligence, not a safety net; correct use is ultimately the caller's.
 *
 * Tear down the PROCESS-GLOBAL loader state so the next setup_dispatcher() /
 * plugin load starts from a clean slate: unloads every plugin (dlclose /
 * FreeLibrary), frees and empties the library/function tables, and destroys the
 * shared lock. This is the explicit "destructor" for the loader, provided so a
 * consumer can force a reinitialize; it is deliberately NOT wired to atexit().
 * Calling it with nothing loaded is safe (idempotent).
 *
 * Returns true if teardown happened. Returns false -- doing nothing -- if any
 * environment that setup_dispatcher() installed into is still alive (tracked via
 * a per-environment cleanup callback CLIPS runs at DestroyEnvironment). This is
 * a guard against the common ordering mistake below, NOT a concurrency guarantee
 * (see THREADING): a caller that ignores the contract can still race a new
 * setup_dispatcher() against this check.
 *
 * ===================== CALL ORDERING (REQUIRED) =====================
 * teardown_dispatcher() MUST be called only AFTER every CLIPS environment that
 * called setup_dispatcher() has been freed with DestroyEnvironment().
 *
 * A still-live environment holds the `functions` template, the loader UDFs, and
 * plugin-backed deffunctions whose bodies dispatch through these global tables.
 * Once teardown has emptied the tables and unloaded the plugins, any such
 * environment resolves a dispatch into nothing -- into code that has been
 * unloaded -- yielding undefined / garbage results. Freeing the environments
 * first removes every reference into this shared state before it is released.
 *
 * The safe lifecycle is therefore strictly:
 *
 *     env = CreateEnvironment();
 *     setup_dispatcher(env);
 *     ... use ...
 *     DestroyEnvironment(env);     // for EVERY environment that was set up
 *     teardown_dispatcher();       // only after the last one is gone
 *
 * SCALE / NO REGISTRY: "every environment" is meant literally and without bound.
 * The expected usage is an application that creates environments dynamically and
 * possibly by the thousands (e.g. one per request or per worker), all sharing
 * this one process-global loader state. The loader deliberately keeps NO list of
 * the environments that were set up -- such a registry would not scale and would
 * introduce its own lifetime-tracking problems -- so nothing can enforce or log
 * this ordering on your behalf. Treat teardown_dispatcher() as a process-global
 * reinitialize to run only at a globally quiescent point (application shutdown,
 * or a deliberate full reset once no loader-using environment remains). Correct
 * ordering is the application's lifecycle responsibility; the caller must be
 * well-behaved.
 *
 * THREADING: the loader must additionally be quiescent -- no other thread may be
 * inside a Dispatch/LoadDispatch/UnLoadDispatch call (or a plugin-backed
 * deffunction) while teardown runs. Destroying a lock or a plugin that is still
 * in use is undefined behavior. This function neither can nor does enforce these
 * preconditions; they are the caller's contract.
 * ====================================================================
 */
bool teardown_dispatcher(void);


/* Introspection into the process-global loader tables: the number of libraries /
 * functions currently loaded. Thread-safe (read under the table lock). Primarily
 * for tests and diagnostics -- e.g. asserting the concurrent load path keeps
 * exactly one entry per library (load-once). */
long loader_library_count(void);
long loader_function_count(void);

