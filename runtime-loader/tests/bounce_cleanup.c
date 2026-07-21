#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"
#include "run_bounded.h"

/*
 * The two-tier lifecycle: BOUNCE vs CLEANUP.
 *
 * BOUNCE (unload -> replace the file -> load) is the reason unload exists: a
 * long-running process swaps a plugin without tearing down its rule base. So
 * unload must succeed even while defrules reference the function. It releases the
 * library but KEEPS this environment's deffunction wrapper, which holds no
 * reference to the library (its body is just `(Dispatch <name> ...)`). While
 * unloaded the wrapper is inert and fails safe to FALSE; reloading re-populates
 * the global table and the SAME wrapper starts working again.
 *
 * CLEANUP retires the name itself by removing the wrapper. It is deliberately a
 * separate step because it is the destructive one: it can only succeed once no
 * construct references the function, so the caller tears down their rules first.
 * It matters because a surviving wrapper answers FALSE, which for a plugin whose
 * real result set includes FALSE (IsOdd: TRUE/FALSE/FAIL) is indistinguishable
 * from a legitimate answer. After cleanup the name is genuinely gone, so a call
 * is an unknown-function error instead.
 *
 * This test walks the whole cycle with a defrule referencing the function the
 * entire time -- the exact situation that used to make unload fail.
 */

static void fail(int* failures, const char* msg)
{
   fprintf(stderr, "FAIL: %s\n", msg);
   (*failures)++;
}

/* `loaded` slot of the Cube fact */
static long long loaded_slot(Environment* env)
{
   CLIPSValue rv;
   if (Eval(env, "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\") ?f:loaded)", &rv) != EE_NO_ERROR) { return -999; }
   if (rv.header->type != INTEGER_TYPE) { return -999; }
   return rv.integerValue->contents;
}

static void set_action(Environment* env, const char* action, int loaded)
{
   char b[256];
   snprintf(b, sizeof(b),
            "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\")"
            " (modify ?f (action \"%s\") (loaded %d)))", action, loaded);
   Eval(env, b, NULL);
}

int main(void)
{
   int failures = 0;
   CLIPSValue rv;
   Environment* env = CreateEnvironment();
   if (env == NULL) { fprintf(stderr, "could not create environment\n"); return 1; }
   if (setup_dispatcher(env) != BE_NO_ERROR) { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }

   /* load, then build a defrule that REFERENCES the function (this is what holds a
      busy count on the wrapper and used to block unload entirely) */
   AssertString(env, "(functions (library \"" CUBE_LIB "\") (function \"Cube\"))");
   if (run_bounded(env, 10, 6, "initial load") < 0) { return 1; }
   if (loaded_slot(env) != 1) { fail(&failures, "initial load did not reach loaded 1"); }

   Build(env, "(deftemplate m (slot v (type INTEGER)) (slot done (type SYMBOL) (default FALSE)))");
   Build(env, "(defrule uses-cube ?d <- (m (v ?v) (done FALSE)) => (modify ?d (v (Cube ?v)) (done TRUE)))");
   if (FindDefrule(env, "uses-cube") == NULL) { fail(&failures, "could not build the referencing rule"); }

   if (Eval(env, "(Cube 3)", &rv) != EE_NO_ERROR || rv.integerValue->contents != 27)
     { fail(&failures, "Cube(3) != 27 while loaded"); }

   /* ---- BOUNCE step 1: unload must SUCCEED despite the referencing rule ---- */
   set_action(env, "unload", 1);
   if (run_bounded(env, 10, 6, "unload while a rule references it") < 0) { return 1; }
   if (loaded_slot(env) != 0)
     { fail(&failures, "unload did not reach loaded 0 (bounce blocked by the referencing rule?)"); }

   /* the wrapper survives, and is inert: fails safe to FALSE rather than erroring */
   if (FindDeffunction(env, "Cube") == NULL)
     { fail(&failures, "unload removed the wrapper (should survive for the bounce)"); }
   if (Eval(env, "(Cube 3)", &rv) != EE_NO_ERROR)
     { fail(&failures, "calling unloaded Cube errored instead of failing safe"); }
   else if (rv.header->type != SYMBOL_TYPE || strcmp(rv.lexemeValue->contents, "FALSE") != 0)
     { fail(&failures, "unloaded Cube did not fail safe to FALSE"); }

   /* the referencing rule is still intact -- nothing was torn down */
   if (FindDefrule(env, "uses-cube") == NULL)
     { fail(&failures, "unload destroyed the referencing rule"); }

   /* ---- BOUNCE step 2: reload, and the SAME wrapper works again ---- */
   set_action(env, "load", 0);
   if (run_bounded(env, 10, 6, "reload") < 0) { return 1; }
   if (loaded_slot(env) != 1) { fail(&failures, "reload did not reach loaded 1"); }
   if (Eval(env, "(Cube 3)", &rv) != EE_NO_ERROR || rv.header->type != INTEGER_TYPE
       || rv.integerValue->contents != 27)
     { fail(&failures, "Cube(3) != 27 after reload"); }

   /* and the pre-existing rule still dispatches correctly through the revived
      wrapper: asserting an `m` fact makes uses-cube fire and cube its value */
   AssertString(env, "(m (v 3))");
   if (run_bounded(env, 10, 6, "referencing rule after reload") < 0) { return 1; }
   if (Eval(env, "(do-for-fact ((?f m)) (eq ?f:done TRUE) ?f:v)", &rv) != EE_NO_ERROR
       || rv.header->type != INTEGER_TYPE || rv.integerValue->contents != 27)
     { fail(&failures, "the pre-existing rule did not cube its fact through the reloaded wrapper"); }

   /* ---- CLEANUP: refused while the rule still references the function ---- */
   set_action(env, "unload", 1);
   if (run_bounded(env, 10, 6, "unload before cleanup") < 0) { return 1; }
   set_action(env, "cleanup", 0);
   if (run_bounded(env, 10, 6, "cleanup while still referenced") < 0) { return 1; }
   if (loaded_slot(env) != -31)
     { fail(&failures, "cleanup was not refused (-31) while a rule still references the function"); }
   if (FindDeffunction(env, "Cube") == NULL)
     { fail(&failures, "refused cleanup removed the wrapper anyway"); }

   /* ---- CLEANUP: succeeds once the caller tears their rule down ---- */
   Eval(env, "(undefrule uses-cube)", NULL);
   set_action(env, "cleanup", 0);
   if (run_bounded(env, 10, 6, "cleanup after rule teardown") < 0) { return 1; }
   if (loaded_slot(env) != 2)
     { fail(&failures, "cleanup did not reach the terminal loaded 2"); }
   if (FindDeffunction(env, "Cube") != NULL)
     { fail(&failures, "cleanup did not remove the wrapper"); }

   /* the name is genuinely gone now: a call is an ERROR, not a silent FALSE --
      which is the whole point for plugins whose real results include FALSE */
   if (Eval(env, "(Cube 3)", &rv) == EE_NO_ERROR)
     { fail(&failures, "Cube still callable after cleanup (should be unknown function)"); }

   /* ---- cleanup then REBUILD: loading again creates a fresh wrapper ---- */
   set_action(env, "load", 0);
   if (run_bounded(env, 10, 6, "load again after cleanup") < 0) { return 1; }
   if (loaded_slot(env) != 1) { fail(&failures, "could not load again after cleanup"); }
   if (FindDeffunction(env, "Cube") == NULL)
     { fail(&failures, "loading after cleanup did not rebuild the wrapper"); }
   if (Eval(env, "(Cube 3)", &rv) != EE_NO_ERROR || rv.header->type != INTEGER_TYPE
       || rv.integerValue->contents != 27)
     { fail(&failures, "Cube(3) != 27 after cleanup-then-reload"); }

   /* ---- cleanup BEFORE unload: the reverse order must work too ----
      cleanup is environment-local and never touches the library, so it is legal
      while the function is still loaded (loaded 1). */
   set_action(env, "cleanup", 1);
   if (run_bounded(env, 10, 6, "cleanup while still loaded") < 0) { return 1; }
   if (loaded_slot(env) != 2)
     { fail(&failures, "cleanup while loaded was not accepted (ordering constraint?)"); }
   if (FindDeffunction(env, "Cube") != NULL)
     { fail(&failures, "cleanup while loaded did not remove the wrapper"); }

   /* the library is still loaded process-globally -- cleanup did not release it,
      which is what lets other environments keep using it */
   if (loader_function_count() != 1)
     { fail(&failures, "cleanup released the global entry (should be unload's job only)"); }

   /* ...and unload still works afterwards, releasing the library */
   set_action(env, "unload", 1);
   if (run_bounded(env, 10, 6, "unload after cleanup") < 0) { return 1; }
   if (loader_function_count() != 0)
     { fail(&failures, "unload after cleanup did not release the global entry"); }

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("bounce (unload/reload with a live rule) + cleanup (retire the name): OK\n");
   return 0;
}
