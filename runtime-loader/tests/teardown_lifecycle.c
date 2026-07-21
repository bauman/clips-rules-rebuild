#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"
#include "run_bounded.h"
#include "locker.h"   /* ensure_lock: teardown destroys the shared lock; verify it comes back */

/*
 * teardown_dispatcher() lifecycle.
 *
 * This is the loader's explicit "destructor" for its PROCESS-GLOBAL state, and it
 * is the one first-class API that had no coverage. It carries a real guard --
 * refusing while any environment set up by setup_dispatcher() is still alive --
 * and that guard is the sort of thing that quietly rots: it depends on a CLIPS
 * environment-cleanup callback firing at DestroyEnvironment to decrement a
 * counter, which nothing else in the suite exercises.
 *
 * The phases below walk the documented contract end to end:
 *
 *   1. teardown on a clean slate succeeds (idempotent, nothing loaded, and the
 *      shared lock may never have been created)
 *   2. REFUSED while an environment is alive -- and "refused" must mean it did
 *      nothing at all, not that it half-tore-down
 *   3. still refused when only SOME environments are gone (it is a count, not a
 *      flag)
 *   4. succeeds once the last environment is destroyed, and empties both tables
 *   5. the loader is REUSABLE afterwards -- a fresh setup_dispatcher + load works.
 *      This is the phase that matters most: teardown destroys the process-wide
 *      lock, so if ensure_lock() failed to rebuild it, everything after would
 *      deadlock or crash rather than fail visibly.
 *   6. a second teardown is safe
 */

static void fail(int* failures, const char* msg)
{
   fprintf(stderr, "FAIL: %s\n", msg);
   (*failures)++;
}

/* Load the cube plugin into env and confirm it dispatches. Returns 0 on success. */
static int load_and_check(Environment* env, int* failures, const char* phase)
{
   CLIPSValue rv;
   char msg[160];
   AssertString(env, "(functions (library \"" CUBE_LIB "\") (function \"Cube\"))");
   if (run_bounded(env, 10, 6, phase) < 0) { return 1; }
   if (Eval(env, "(Cube 3)", &rv) != EE_NO_ERROR
       || rv.header->type != INTEGER_TYPE
       || rv.integerValue->contents != 27)
     {
      snprintf(msg, sizeof msg, "%s: Cube(3) did not return 27", phase);
      fail(failures, msg);
      return 1;
     }
   return 0;
}

int main(void)
{
   int failures = 0;
   CLIPSValue rv;
   Environment *a, *b, *c;

   /* ---- 1. clean slate: nothing set up, nothing loaded, no lock yet ---- */
   if (!teardown_dispatcher())
     { fail(&failures, "teardown on a clean slate should succeed"); }

   /* ---- 2. refused while an environment is alive ---- */
   a = CreateEnvironment();
   if (a == NULL) { fprintf(stderr, "could not create environment\n"); return 1; }
   if (setup_dispatcher(a) != BE_NO_ERROR) { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }
   if (load_and_check(a, &failures, "load into env a")) { return 1; }
   if (loader_function_count() != 1 || loader_library_count() != 1)
     { fail(&failures, "expected exactly one loaded library and function"); }

   if (teardown_dispatcher())
     { fail(&failures, "teardown should be REFUSED while an environment is alive"); }

   /* "refused" must mean it did nothing -- the tables and the plugin are intact */
   if (loader_function_count() != 1 || loader_library_count() != 1)
     { fail(&failures, "a refused teardown must not touch the tables"); }
   if (Eval(a, "(Cube 3)", &rv) != EE_NO_ERROR
       || rv.header->type != INTEGER_TYPE || rv.integerValue->contents != 27)
     { fail(&failures, "a refused teardown must leave the plugin working"); }

   /* ---- 3. a second environment: still refused after only one is destroyed ---- */
   b = CreateEnvironment();
   if (b == NULL) { fprintf(stderr, "could not create second environment\n"); return 1; }
   if (setup_dispatcher(b) != BE_NO_ERROR) { fprintf(stderr, "setup_dispatcher(b) failed\n"); return 1; }

   DestroyEnvironment(a);
   if (teardown_dispatcher())
     { fail(&failures, "teardown should still be refused while a second environment lives"); }
   if (loader_function_count() != 1)
     { fail(&failures, "tables must survive while any environment is alive"); }

   /* ---- 4. the last environment goes: teardown succeeds and empties everything ---- */
   DestroyEnvironment(b);
   if (!teardown_dispatcher())
     { fail(&failures, "teardown should succeed once every environment is destroyed"); }
   if (loader_function_count() != 0)
     { fail(&failures, "teardown did not clear the function table"); }
   if (loader_library_count() != 0)
     { fail(&failures, "teardown did not clear the library table"); }

   /* ---- 5. REUSABLE: the loader must work again from a clean slate ----
      teardown destroyed the process-wide lock; ensure_lock() has to rebuild it,
      and the plugin has to load again from scratch. */
   /* Assert the lock itself was rebuilt. This needs checking DIRECTLY: every
      lock and unlock helper is a no-op when handed a NULL lock, so a loader whose
      lock was destroyed and never recreated still behaves perfectly
      single-threaded -- it just runs with the process-global tables completely
      unprotected. The functional reuse below therefore does NOT prove the
      rebuild; only this assertion does. (Verified: with the rebuild disabled, the
      rest of this test still passed.) */
   if (ensure_lock() == NULL)
     { fail(&failures, "teardown destroyed the shared lock and ensure_lock() did not rebuild it"); }

   c = CreateEnvironment();
   if (c == NULL) { fprintf(stderr, "could not create environment after teardown\n"); return 1; }
   if (setup_dispatcher(c) != BE_NO_ERROR)
     { fail(&failures, "setup_dispatcher failed after a teardown"); }
   else if (load_and_check(c, &failures, "reload after teardown") == 0)
     {
      if (loader_function_count() != 1 || loader_library_count() != 1)
        { fail(&failures, "reload after teardown did not repopulate the tables"); }
     }

   DestroyEnvironment(c);

   /* ---- 6. teardown again, then once more: both must be safe ---- */
   if (!teardown_dispatcher())
     { fail(&failures, "teardown after the reuse cycle should succeed"); }
   if (!teardown_dispatcher())
     { fail(&failures, "a repeated teardown should be safe (idempotent)"); }
   if (loader_function_count() != 0 || loader_library_count() != 0)
     { fail(&failures, "tables should be empty after the final teardown"); }

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("teardown lifecycle (guard, reuse, idempotence): OK\n");
   return 0;
}
