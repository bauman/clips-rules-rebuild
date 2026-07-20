#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"

/*
 * F7 regression: unloading a function from an environment that never loaded it.
 *
 * Env A loads Cube (creating the process-global table entry AND A's deffunction).
 * Env B is set up but never loads Cube, so B has NO deffunction for it -- yet the
 * fact interface is public, so B can assert an unload fact with (loaded 1) by
 * hand. UnLoader then finds the global entry and calls UnDefineFuncIfRequired,
 * where FindDeffunction returns NULL; before the F7 fix that NULL went straight
 * into DeffunctionIsDeletable (which dereferences it) -- segfault.
 *
 * After the fix: no crash, B's fact gets (loaded 0) (vacuous local success), the
 * global entry is removed (unload is process-global, F2), and A's subsequent
 * Dispatch fails safe to FALSE.
 */

static void fail(int* failures, const char* msg)
{
   fprintf(stderr, "FAIL: %s\n", msg);
   (*failures)++;
}

int main(void)
{
   int failures = 0;
   CLIPSValue rv;
   Environment* a = CreateEnvironment();
   Environment* b = CreateEnvironment();
   if ((a == NULL) || (b == NULL)) { fprintf(stderr, "could not create environments\n"); return 1; }
   if ((setup_dispatcher(a) != BE_NO_ERROR) || (setup_dispatcher(b) != BE_NO_ERROR))
     { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }

   /* only A loads Cube */
   AssertString(a, "(functions (library \"" CUBE_LIB "\") (function \"Cube\"))");
   Run(a, -1);
   if (Eval(a, "(Cube 3)", &rv) != EE_NO_ERROR || rv.header->type != INTEGER_TYPE
       || rv.integerValue->contents != 27)
     { fail(&failures, "env A Cube(3) != 27 after load"); }
   if (loader_function_count() != 1)
     { fail(&failures, "expected exactly 1 global function entry after A's load"); }

   /* B -- which has no Cube deffunction -- hand-asserts an unload fact. Before
      the F7 fix this Run segfaulted. */
   AssertString(b, "(functions (library \"" CUBE_LIB "\") (function \"Cube\")"
                   " (action \"unload\") (loaded 1))");
   Run(b, -1);

   /* B's fact must carry the defined vacuous-success result, not garbage */
   if (Eval(b, "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\") ?f:loaded)", &rv) != EE_NO_ERROR
       || rv.header->type != INTEGER_TYPE || rv.integerValue->contents != 0)
     { fail(&failures, "env B unload fact did not end with (loaded 0)"); }

   /* the unload was process-global: the entry is gone... */
   if (loader_function_count() != 0)
     { fail(&failures, "global function entry not removed by B's unload"); }

   /* ...and A's still-bound deffunction fails safe to FALSE (F2 contract) */
   if (Eval(a, "(Cube 3)", &rv) != EE_NO_ERROR)
     { fail(&failures, "env A Cube(3) eval error after B's unload"); }
   else if ((rv.header->type != SYMBOL_TYPE) || (strcmp(rv.lexemeValue->contents, "FALSE") != 0))
     { fail(&failures, "env A Cube(3) did not fail safe to FALSE after B's unload"); }

   DestroyEnvironment(a);
   DestroyEnvironment(b);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("F7 unload-without-deffunction: OK\n");
   return 0;
}