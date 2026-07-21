#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"
#include "run_bounded.h"

/*
 * F1 regression: unloading one function of a multi-function library must NOT
 * unload the library out from under its sibling functions. Before the fix,
 * UnLoader dlclose'd the library on the first function's unload, leaving the
 * sibling's ->ref dangling into unmapped code -> segfault on its next Dispatch.
 *
 * Loads Cube and Square (both from the one cube library), unloads Cube, then
 * calls Square: it must still return 9 and the process must not crash.
 */

static long long eval_int(Environment* env, const char* expr)
{
   CLIPSValue rv;
   if (Eval(env, expr, &rv) != EE_NO_ERROR) { return -99999; }
   return rv.integerValue->contents;
}

int main(void)
{
   int failures = 0;
   Environment* env = CreateEnvironment();
   if (env == NULL) { fprintf(stderr, "could not create environment\n"); return 1; }
   if (setup_dispatcher(env) != BE_NO_ERROR) { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }

   AssertString(env, "(functions (library \"" CUBE_LIB "\") (function \"Cube\"))");
   AssertString(env, "(functions (library \"" CUBE_LIB "\") (function \"Square\"))");
   /* two load facts asserted here, so two loadlib firings are expected */
   if (run_bounded(env, 10, 6, "load Cube + Square") < 0) { return 1; }

   if (eval_int(env, "(Cube 3)") != 27)   { fprintf(stderr, "FAIL: Cube(3) != 27 before unload\n"); failures++; }
   if (eval_int(env, "(Square 3)") != 9)  { fprintf(stderr, "FAIL: Square(3) != 9 before unload\n"); failures++; }

   /* unload only Cube; Square (same library) must keep working */
   Eval(env, "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\") (modify ?f (action \"unload\")))", NULL);
   if (run_bounded(env, 10, 6, "unload Cube only") < 0) { return 1; }

   if (eval_int(env, "(Square 3)") != 9)
     { fprintf(stderr, "FAIL: Square(3) != 9 after unloading its sibling Cube (F1 regression)\n"); failures++; }

   /* Unload is a BOUNCE: it releases the library but deliberately KEEPS this
      environment's wrapper, so rules referencing the function stay valid and the
      library can be replaced and reloaded. The wrapper is inert while unloaded --
      Dispatch misses the global table and fails safe to FALSE. Retiring the name
      itself is the separate `cleanup` action. */
   if (FindDeffunction(env, "Cube") == NULL)
     { fprintf(stderr, "FAIL: Cube wrapper was removed by unload (should survive for the bounce)\n"); failures++; }

   {
      CLIPSValue rv;
      if (Eval(env, "(Cube 3)", &rv) != EE_NO_ERROR)
        { fprintf(stderr, "FAIL: calling unloaded Cube errored instead of failing safe\n"); failures++; }
      else if (rv.header->type != SYMBOL_TYPE || strcmp(rv.lexemeValue->contents, "FALSE") != 0)
        { fprintf(stderr, "FAIL: unloaded Cube did not fail safe to FALSE\n"); failures++; }
   }

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("F1 multifunction-unload: OK\n");
   return 0;
}
