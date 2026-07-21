#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"
#include "run_bounded.h"

/*
 * F2 regression: unloading is process-global. Two environments share the one
 * global entry for a loaded function (load-once / dedup). When environment A
 * unloads it, environment B still has a deffunction bound to that name -- a
 * Dispatch of it must FAIL SAFE (return FALSE), never a dangling call into the
 * removed entry / unmapped library and never an unset (garbage) result.
 */

static long long eval_int(Environment* env, const char* expr, int* ok)
{
   CLIPSValue rv;
   *ok = 0;
   if (Eval(env, expr, &rv) != EE_NO_ERROR) { return 0; }
   if (rv.header->type != INTEGER_TYPE) { return 0; }
   *ok = 1;
   return rv.integerValue->contents;
}

/* Returns 0 on success, non-zero if the load rule loop ran away. */
static int load_cube(Environment* env)
{
   AssertString(env, "(functions (library \"" CUBE_LIB "\") (function \"Cube\"))");
   return (run_bounded(env, 10, 6, "load Cube") < 0) ? 1 : 0;
}

int main(void)
{
   int failures = 0;
   int ok = 0;
   CLIPSValue rv;
   Environment* a = CreateEnvironment();
   Environment* b = CreateEnvironment();
   if ((a == NULL) || (b == NULL)) { fprintf(stderr, "could not create environments\n"); return 1; }
   if ((setup_dispatcher(a) != BE_NO_ERROR) || (setup_dispatcher(b) != BE_NO_ERROR))
     { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }

   if (load_cube(a) || load_cube(b)) { return 1; }

   /* both environments dispatch correctly to start */
   if (eval_int(a, "(Cube 3)", &ok) != 27 || !ok) { fprintf(stderr, "FAIL: env A Cube(3) != 27\n"); failures++; }
   if (eval_int(b, "(Cube 3)", &ok) != 27 || !ok) { fprintf(stderr, "FAIL: env B Cube(3) != 27\n"); failures++; }

   /* env A unloads Cube -- process-global, so it disappears for env B too */
   Eval(a, "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\") (modify ?f (action \"unload\")))", NULL);
   if (run_bounded(a, 10, 6, "env A unload Cube") < 0) { return 1; }

   /* env B still has its deffunction; the Dispatch must fail safe to FALSE */
   if (Eval(b, "(Cube 3)", &rv) != EE_NO_ERROR)
     { fprintf(stderr, "FAIL: env B Cube(3) eval error after cross-env unload\n"); failures++; }
   else if ((rv.header->type != SYMBOL_TYPE) || (strcmp(rv.lexemeValue->contents, "FALSE") != 0))
     { fprintf(stderr, "FAIL: env B Cube(3) did not fail safe to FALSE after unload\n"); failures++; }

   DestroyEnvironment(a);
   DestroyEnvironment(b);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("F2 cross-env-unload fail-safe: OK\n");
   return 0;
}
