#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"
#include "run_bounded.h"

/*
 * F8 regression: unloading a function that is not in the global table must yield
 * a DEFINED result (-32) in the fact's `loaded` slot, never an unset UDFValue.
 *
 * The unloadlib rule fires on any (action "unload") (loaded 1) fact -- and
 * (loaded 1) can simply be hand-asserted -- then writes UnLoadDispatch's out
 * value into the `loaded` slot. Before the fix, a global-table miss returned
 * with `out` untouched, so the slot got garbage. Two reachable cases:
 *
 *   1. the function was never loaded at all;
 *   2. it was loaded, then already unloaded (unload is process-global, F2 --
 *      e.g. by another environment), and is unloaded again.
 */

static void fail(int* failures, const char* msg)
{
   fprintf(stderr, "FAIL: %s\n", msg);
   (*failures)++;
}

/* loaded slot of the functions fact whose function slot == fname */
static long long fact_loaded(Environment* env, const char* fname, int* ok)
{
   CLIPSValue rv;
   char expr[256];
   *ok = 0;
   snprintf(expr, sizeof(expr),
            "(do-for-fact ((?f functions)) (eq ?f:function \"%s\") ?f:loaded)", fname);
   if (Eval(env, expr, &rv) != EE_NO_ERROR) { return 0; }
   if (rv.header->type != INTEGER_TYPE) { return 0; }
   *ok = 1;
   return rv.integerValue->contents;
}

int main(void)
{
   int failures = 0;
   int ok = 0;
   CLIPSValue rv;
   Environment* env = CreateEnvironment();
   if (env == NULL) { fprintf(stderr, "could not create environment\n"); return 1; }
   if (setup_dispatcher(env) != BE_NO_ERROR)
     { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }

   /* case 1: never loaded -- hand-asserted unload fact */
   AssertString(env, "(functions (library \"no-such-lib\") (function \"Nope\")"
                     " (action \"unload\") (loaded 1))");
   /* the F8 runaway lived here: unbounded, garbage `loaded` span forever */
   if (run_bounded(env, 10, 6, "unload never-loaded fn") < 0) { return 1; }
   if (fact_loaded(env, "Nope", &ok) != -32 || !ok)
     { fail(&failures, "never-loaded unload did not end with (loaded -32)"); }
   if (Eval(env, "(do-for-fact ((?f functions)) (eq ?f:function \"Nope\") ?f:error)", &rv) != EE_NO_ERROR
       || rv.header->type != STRING_TYPE
       || strstr(rv.lexemeValue->contents, "not loaded") == NULL)
     { fail(&failures, "never-loaded unload did not get the unloader-not-loaded error slot"); }

   /* case 2: load, unload (removes the global entry), then unload AGAIN */
   AssertString(env, "(functions (library \"" CUBE_LIB "\") (function \"Cube\"))");
   if (run_bounded(env, 10, 6, "load Cube") < 0) { return 1; }
   if (fact_loaded(env, "Cube", &ok) != 1 || !ok)
     { fail(&failures, "Cube did not load (loaded != 1)"); }

   Eval(env, "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\")"
             " (modify ?f (action \"unload\")))", NULL);
   if (run_bounded(env, 10, 6, "first unload Cube") < 0) { return 1; }
   if (fact_loaded(env, "Cube", &ok) != 0 || !ok)
     { fail(&failures, "first Cube unload did not succeed (loaded != 0)"); }
   if (loader_function_count() != 0)
     { fail(&failures, "global function entry not removed by first unload"); }

   Eval(env, "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\")"
             " (modify ?f (action \"unload\") (loaded 1)))", NULL);
   if (run_bounded(env, 10, 6, "second unload Cube (already gone)") < 0) { return 1; }
   if (fact_loaded(env, "Cube", &ok) != -32 || !ok)
     { fail(&failures, "second Cube unload did not end with (loaded -32)"); }

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("F8 unload-not-loaded defined result: OK\n");
   return 0;
}
