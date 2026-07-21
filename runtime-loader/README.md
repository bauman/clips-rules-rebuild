# runtime-loader

Load native shared-library plugins into a running CLIPS environment, from CLIPS
rules, without rebuilding CLIPS.

A plugin is an ordinary shared library exporting one or more functions with the
CLIPS UDF signature. Asserting a fact makes one available as a normal CLIPS
function:

```clips
(assert (functions (library "./libcube.so") (function "Cube")))
(run)
(Cube 3)          ; => 27, dispatched into the plugin
```

The point is not convenience — it is that a long-running rules engine can pick up
native code it was never linked against, and can **swap that code out and back in
without touching a single rule**.

---

## Contents

- [How it works](#how-it-works)
- [The fact protocol](#the-fact-protocol)
- [`loaded` result codes](#loaded-result-codes)
- [Lifecycle: load, bounce, cleanup](#lifecycle-load-bounce-cleanup)
- [Hot-updating a plugin](#hot-updating-a-plugin)
- [Writing a plugin](#writing-a-plugin)
- [Declared shape (the `arity` slot)](#declared-shape-the-arity-slot)
- [Who is responsible for what](#who-is-responsible-for-what)
- [Constraints and gotchas](#constraints-and-gotchas)
- [Embedding it in your own program](#embedding-it-in-your-own-program)
- [Building](#building)

---

## How it works

`setup_dispatcher(env)` installs into a CLIPS environment:

- five UDFs — `LoadDispatch`, `UnLoadDispatch`, `CleanupDispatch`,
  `DispatchLibraryOf`, and `Dispatch`
- a `functions` deftemplate and the load / unload / cleanup / error rules

When a load fact fires, the loader `dlopen`s (or `LoadLibrary`s) the library,
resolves the symbol, and generates a small CLIPS **wrapper deffunction**:

```clips
(deffunction Cube ($?args) (Dispatch Cube (expand$ ?args)))
```

That wrapper is the whole trick. It holds **no reference to the library** — only
the permanent `Dispatch` UDF and the function's name. `Dispatch` looks the name up
in a process-global table at call time. Everything else in the design follows from
that indirection: rules bind to the wrapper, the wrapper resolves late, and the
library underneath can therefore come and go.

---

## The fact protocol

Everything is driven by `functions` facts. You never call the UDFs directly.

```clips
(deftemplate functions
   (slot library  (type STRING))                    ; path to the shared library
   (slot function (type STRING))                    ; exported symbol name
   (slot action   (type STRING)  (default "load"))  ; load | unload | cleanup
   (slot loaded   (type INTEGER) (default 0))       ; result — see below
   (slot error    (type STRING))                    ; explanation on failure
   (slot arity    (type INTEGER) (default -1)))     ; optional declared shape
```

The rules match on `action` + `loaded` and write the outcome back into `loaded`,
filling `error` when something goes wrong. So a failed load is not an exception —
it is a fact you can write rules against:

```clips
(defrule complain-about-failed-plugins
   (functions (function ?f) (loaded ?c&:(< ?c 0)) (error ?why))
   =>
   (printout t "plugin " ?f " failed (" ?c "): " ?why crlf))
```

---

## `loaded` result codes

| code | meaning |
|-----:|---------|
| `2` | cleaned up — the wrapper was removed, the name no longer exists |
| `1` | loaded and callable |
| `0` | not loaded (fresh fact, or successfully unloaded — wrapper still present) |
| `-1` | the wrapper deffunction could not be built (non-ASCII function name?) |
| `-2` | function name too long for the generated wrapper |
| `-3` | the **library** failed to load — wrong path, or a dependency did not resolve |
| `-4` | name collision — that function name is already loaded from a different library path |
| `-6` | the library loaded but the **symbol** was not found — wrong/misspelled name, or not exported |
| `-7` | declared `arity` out of range (use `-1`, or `0..64`) |
| `-30` | cleanup: the wrapper was deletable but removing it failed |
| `-31` | cleanup: refused — the wrapper is still referenced by other constructs |
| `-32` | unload: that function is not loaded |
| `-200` | invalid arguments (library/function were not both strings) |

`-3` and `-6` are deliberately distinct: *"I couldn't open the file"* and *"I opened
it but your function isn't in there"* are the two mistakes plugin authors actually
make, and they need different fixes.

---

## Lifecycle: load, bounce, cleanup

Three actions, and the distinction between the last two matters.

### `load`

```clips
(assert (functions (library "./libcube.so") (function "Cube")))
```

Opens the library, resolves the symbol, generates the wrapper. `loaded` → `1`.

### `unload` — the bounce

```clips
(modify ?f (action "unload"))
```

Releases the **library** (removes the global entry; closes the library once no
function still references it). `loaded` → `0`.

It deliberately **keeps the wrapper**. Consequences:

- unload **always succeeds** — rules that call the function do not block it, and
  are left completely untouched
- while unloaded the wrapper is inert: calling it returns `FALSE` (fail-safe, never
  a dangling call into unmapped code)
- re-asserting `(action "load") (loaded 0)` repopulates the table and the **same
  wrapper works again**

That is what makes a hot update possible.

### `cleanup` — retire the name

```clips
(modify ?f (action "cleanup"))
```

Removes the wrapper, so the name stops existing in this environment — a later call
is an unknown-function error rather than `FALSE`. `loaded` → `2`.

Reach for it when a plugin's legitimate results *include* `FALSE` (a predicate
returning `TRUE`/`FALSE`/`FAIL` — an unloaded `FALSE` is indistinguishable from a
real answer), or when retiring a feature outright.

Cleanup is **refused (`-31`) while any construct references the wrapper**. CLIPS
counts a deffunction as busy for every rule or deffunction whose body calls it, so
you must tear those down first — that is the caller's job:

```clips
(undefrule uses-cube)          ; every rule that calls it
(modify ?f (action "cleanup"))
```

Facts are irrelevant; only *constructs* hold a reference.

### Order does not matter

`unload` and `cleanup` are orthogonal — cleanup never touches the library, unload
never touches the wrapper. All of these are valid:

| sequence | effect |
|---|---|
| `unload` → `cleanup` | release the library, then retire the name |
| `cleanup` → `unload` | retire the name, then release the library |
| `cleanup` alone | retire the name here, **leave the library loaded** for other environments |
| `cleanup` → `load` | retire the old wrapper, then build a fresh one |

The last two matter because **unload is process-global** while **cleanup is
environment-local**: an environment must be able to retire its own wrapper without
pulling a shared library out from under other environments.

---

## Hot-updating a plugin

The payoff. Replace a plugin's code under a live rule base:

```clips
(modify ?f (action "unload"))                 ; 1. release the library
(run)
;    2. replace the file on disk  (see the warning below)
(modify ?f (action "load") (loaded 0))        ; 3. load the new build
(run)
;    4. the same, never-rebuilt rules now run the new code
```

No rule is touched at any point.

> **Replace the file atomically.** Write the new build to a temporary name and
> `rename()` it over the target. Do **not** truncate-and-rewrite the library in
> place: on macOS the kernel will `SIGKILL` your process when it later maps the
> modified file, because the code signature no longer matches the cached pages.
> `rename()` swaps in a fresh inode and avoids this — and it is the correct
> atomic-deploy pattern anyway.

On Windows there is a useful side effect: a DLL that was not genuinely released
cannot be replaced (sharing violation), so a successful deploy is itself evidence
the unload worked.

---

## Writing a plugin

A plugin function is an ordinary exported C function with the CLIPS UDF signature:

```c
#include "clips.h"

void Cube(Environment *env, UDFContext *udfc, UDFValue *out)
{
    UDFValue arg;
    /* argument 1 is the dispatch NAME; argument 2 onward are the real arguments */
    if (!UDFNthArgument(udfc, 2, NUMBER_BITS, &arg)) { return; }
    long long v = arg.integerValue->contents;
    out->integerValue = CreateInteger(env, v * v * v);
}
```

Two things to know:

**Argument 1 is the function name.** `Dispatch` receives the name first, so your
arguments start at index 2.

**Validate permissively.** `UDFNthArgument` with a restrictive mask (e.g.
`INTEGER_BIT`) raises a hard `[ARGACCES2]` error and *halts the deffunction* on a
type mismatch — the caller sees an evaluation error, not your return value. To
report a refusal yourself, retrieve with `ANY_TYPE_BITS` and check the type:

```c
if (!UDFNthArgument(udfc, 2, ANY_TYPE_BITS, &arg) || arg.header->type != INTEGER_TYPE) {
    out->lexemeValue = CreateSymbol(env, "FAIL");
    return;
}
```

### The `TRUE` / `FALSE` / `FAIL` convention

Return a **symbol**, not a boolean, whenever your result set already includes
`FALSE`. Folding "bad input" or "I can't run here" into `FALSE` makes a failure
indistinguishable from a legitimate negative answer — an `IsOdd` that returns
`FALSE` on an unsupported host is claiming the number is even.

### Worked examples

| directory | what it demonstrates |
|---|---|
| `plugins/Cube` | plain C; also builds `cube2`, a byte-identical second library used by the name-collision tests |
| `plugins/IsOdd` | assembly at its most minimal — a single masking instruction, in four per-toolchain files |
| `plugins/IsPrime` | a real assembly routine: branches, a loop, multiply, integer division |
| `plugins/MatrixMultiplyAMX` | undocumented hardware — Apple's AMX coprocessor via inline asm, with a runtime capability probe |
| `plugins/CubeForTesting` | **test fixture, deliberately wrong.** Not an example to copy |

Each plugin directory is self-contained (sources + `CMakeLists.txt`) so it can be
copied as a starting point. The parent `CMakeLists.txt` only decides *which*
plugins are built.

### Architecture-specific plugins

`IsOdd` and `IsPrime` ship the same routine once per *(architecture, toolchain)*
pair, because the assembler dialects differ — and on x86-64 so does the ABI:

|  | POSIX (GAS, `.S`) | Windows (MSVC, `.asm`) |
|---|---|---|
| **aarch64** | `is_prime_aarch64.S` | `is_prime_arm64_msvc.asm` (armasm64) |
| **x86-64** | `is_prime_x86_64.S` | `is_prime_x64_msvc.asm` (MASM/ml64) |

On aarch64 both ABIs pass argument 1 in `x0`, so those two files differ only in
syntax. On x86-64 System V uses `RDI` while Microsoft x64 uses `RCX`, so those two
differ in **register allocation** — porting assembly between ABIs is not a
search-and-replace.

**To add an architecture:** drop in one assembly file implementing the core and add
one branch to that plugin's `CMakeLists.txt`. Nothing else changes — not the C
adapter, not the test, not any rule.

---

## Declared shape (the `arity` slot)

The `arity` slot selects which wrapper is generated, and with it *who validates
the call*.

### Default (`arity -1`, omitted) — signature-agnostic

```clips
(deffunction NAME ($?args) (Dispatch NAME (expand$ ?args)))
```

Any exported symbol can be wrapped without declaring anything. CLIPS accepts any
call, so **all** validation lands in the plugin, which reports refusal as `FAIL`.

> **`$?args` flattens multifields.** Calling
> `(F (create$ 1 2 3) (create$ 4 5))` binds `?args` to **one 5-element**
> multifield, and `expand$` passes 5 loose scalars. A plugin under this wrapper
> **never receives a multifield argument** — only scalars. (Returning one is fine
> either way.)

### Declared (`arity N`, 0–64) — fixed parameters

```clips
(assert (functions (library "...") (function "MatrixMultiply") (arity 2)))
```

```clips
(deffunction MatrixMultiply (?a1 ?a2) (Dispatch MatrixMultiply ?a1 ?a2))
```

Fixed parameters **preserve multifields**, which is the only way to pass more than
one: CLIPS multifields cannot nest, so nothing can be encoded inside a single one.

The trade, and why it is per-plugin: declaring a shape moves **signature** errors
to CLIPS, which rejects a wrong-sized call itself before your code runs. It does
not silence you — argument **content** and **environment** refusals are still
yours to report:

```clips
(MatrixMultiply (create$ 1 2 3 4 5 6 7 8) (create$ 9 10 11 12 13 14 15 16))
; => (130.0 140.0 322.0 348.0)

(MatrixMultiply (create$ 1 2) (create$ 3 4) (create$ 5 6))
; => [ARGACCES1] Function 'MatrixMultiply' expected exactly 2 arguments   <- CLIPS

(MatrixMultiply (create$ 1 2 3) (create$ 4 5 6))
; => FAIL                                                                <- the plugin
```

Two distinguishable diagnostics for two genuinely different mistakes.

---

## Who is responsible for what

Three layers, deliberately separated:

**The loader knows nothing about your plugin.** It resolves a symbol and calls it.
It takes only cheap, robust steps to check things, and documents what it does not
cover rather than pretending to enforce it.

**The plugin author must not wreck the process.** The loader cannot know that your
plugin needs particular silicon, a device, or a driver — so *you* must check before
doing anything unsafe. `plugins/MatrixMultiplyAMX` is the worked example: running
AMX instructions on hardware without them is a `SIGILL` that kills the entire CLIPS
process, so the plugin probes for the capability first and returns `FAIL` if it is
absent.

> **Probe, don't infer.** That plugin originally allowlisted CPU brand strings. It
> worked on real hardware and **crashed in CI**, because virtualised macOS runners
> report an Apple Silicon brand string but do not expose the coprocessor. The CPU
> model does not determine whether an instruction will execute. Attempt the
> operation under a `SIGILL` handler and cache the result — that is correct
> regardless of *why* the feature is missing.

**The rule author sees CLIPS values.** Every refusal arrives as a fact slot or a
returned symbol that rules can react to — never a crash.

---

## Constraints and gotchas

**Function names must be unique across all libraries.** The function table is keyed
by name process-wide. The first library to register a name owns it until fully
unloaded; the same name from another library is refused with `-4`. You control the
exported symbol name, so give wrappers distinct names (`lib1_Cube`, `lib2_Cube`).

**A library is identified by the literal path string.** No canonicalisation is
performed, so `"./libcube.so"` and `"/opt/x/libcube.so"` are two libraries even
when they are the same file — the second is refused with `-4`. Use one consistent
spelling throughout your rule base.

This is deliberate. `realpath()` would collapse that case *and* resolve symlinks,
but hard links, bind mounts and separate copies still produce distinct paths for
identical content; keying on device+inode would catch hard links but still miss
copies. More fundamentally, path identity is not library identity in a system that
supports hot updates — replacing the file at a fixed path is a *feature* here. There
is no stable answer, so the loader does not pretend to compute one. The `-4`
message names the conflicting path so a mismatch is obvious.

**Unload is process-global.** A loaded function has one global table entry shared by
every environment (load-once / dedup), so unloading removes it for *all*
environments. Others keep their wrappers and get `FALSE` from a dispatch. Cleanup,
by contrast, is environment-local.

**A failed symbol lookup (`-6`) leaves the library loaded.** The library opened
successfully; only the symbol was missing. It stays in the table until
`teardown_dispatcher()`, so repeatedly retrying wrong function names against the
same library accumulates loaded-but-unused libraries.

**Windows paths are interpreted in the ANSI code page.** The loader uses
`LoadLibraryA`, so non-ASCII plugin paths will not round-trip on Windows.

**Concurrency.** Concurrent *loads* are safe (a load only adds entries, and the same
library loads exactly once). Concurrent *dispatch* is safe (lookups are locked and a
miss fails safe to `FALSE`). **Unload and teardown require quiescence** — they free
entries, so unloading while another thread is dispatching the same function is
undefined.

---

## Embedding it in your own program

```c
#include "clips.h"
#include "dispatcher.h"

Environment *env = CreateEnvironment();
if (setup_dispatcher(env) != BE_NO_ERROR) { /* the loader is unusable — bail out */ }

/* ... assert functions facts, Run(env, ...), use the plugins ... */

DestroyEnvironment(env);      /* for EVERY environment that was set up */
teardown_dispatcher();        /* optional; only after the last one is gone */
```

The public C API is small:

| function | purpose |
|---|---|
| `BuildError setup_dispatcher(Environment *)` | install the loader into an environment (idempotent per environment) |
| `bool teardown_dispatcher(void)` | **expert.** Release all process-global state; returns `false` if any environment is still alive |
| `long loader_library_count(void)` | introspection: libraries currently loaded |
| `long loader_function_count(void)` | introspection: functions currently loaded |

**Always check `setup_dispatcher`'s result** — a non-zero return means the
environment is not usable as a loader.

**You usually do not need `teardown_dispatcher()`.** Process exit reclaims
everything; it exists to reset the loader *within* a long-running process. It must
be called only after every environment that was set up has been destroyed (it
refuses otherwise), and it requires quiescence. See `include/dispatcher.h` for the
full contract.

`runtime-clips` is a ready-made CLI with the loader pre-registered — useful for
trying a plugin without writing a host program:

```console
$ runtime-clips
CLIPS> (assert (functions (library "./libcube.so") (function "Cube")))
CLIPS> (run)
CLIPS> (Cube 3)
27
```

---

## Building

Built as part of the top-level project with `-Dbuild-642=ON`:

```sh
mkdir build && cd build
cmake -Dbuild-642=ON -Dbuild-641-6=OFF ..
cmake --build .
ctest
```

Produces `libdispatcher` (shared + static), the example plugins, the
`runtime-clips` CLI, and the test suite.

Installed artifacts carry a loader-relative rpath (`@loader_path/../lib` /
`$ORIGIN/../lib`), so an installed `runtime-clips` finds its libraries without
`DYLD_LIBRARY_PATH` or `LD_LIBRARY_PATH`. The shared library is versioned
(`SOVERSION`), so consumers link against a stable soname.

Plugins that have no implementation for the host architecture simply are not built,
and their tests are skipped — `MatrixMultiplyAMX` is Apple-Silicon-only, and the
assembly plugins build only where they have a core for the target.
