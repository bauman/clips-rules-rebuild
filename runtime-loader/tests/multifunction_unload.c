#include <stdio.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"

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
   Run(env, -1);

   if (eval_int(env, "(Cube 3)") != 27)   { fprintf(stderr, "FAIL: Cube(3) != 27 before unload\n"); failures++; }
   if (eval_int(env, "(Square 3)") != 9)  { fprintf(stderr, "FAIL: Square(3) != 9 before unload\n"); failures++; }

   /* unload only Cube; Square (same library) must keep working */
   Eval(env, "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\") (modify ?f (action \"unload\")))", NULL);
   Run(env, -1);

   if (eval_int(env, "(Square 3)") != 9)
     { fprintf(stderr, "FAIL: Square(3) != 9 after unloading its sibling Cube (F1 regression)\n"); failures++; }

   if (FindDeffunction(env, "Cube") != NULL)
     { fprintf(stderr, "FAIL: Cube deffunction still defined after unload\n"); failures++; }

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("F1 multifunction-unload: OK\n");
   return 0;
}
