#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"

/*
 * End-to-end test of the assembly-backed IsOdd plugin. It exercises the whole
 * point of the runtime loader: a CLIPS rule/expression calls IsOdd, the dispatcher
 * routes into the runtime-loaded plugin, the C wrapper hands off to the AArch64
 * assembly core, and a CLIPS boolean comes back. Only built/run on aarch64/arm64
 * (gated by RUNTIME_LOADER_HAVE_ISODD in CMake).
 */

/* Evaluate a CLIPS expression and assert it returns the expected symbol. */
static void check(Environment* env, const char* expr, const char* expect, int* failures)
{
   CLIPSValue rv;
   if (Eval(env, expr, &rv) != EE_NO_ERROR)
     { fprintf(stderr, "FAIL: eval error for %s\n", expr); (*failures)++; return; }
   if (rv.header->type != SYMBOL_TYPE || strcmp(rv.lexemeValue->contents, expect) != 0)
     {
      fprintf(stderr, "FAIL: %s = %s, expected %s\n", expr,
              (rv.header->type == SYMBOL_TYPE ? rv.lexemeValue->contents : "<non-symbol>"), expect);
      (*failures)++;
     }
}

int main(void)
{
   int failures = 0;
   Environment* env = CreateEnvironment();
   if (env == NULL) { fprintf(stderr, "could not create environment\n"); return 1; }
   if (setup_dispatcher(env) != BE_NO_ERROR) { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }

   AssertString(env, "(functions (library \"" ISODD_LIB "\") (function \"IsOdd\"))");
   Run(env, -1);

   /* parity across positives, zero, and negatives (two's-complement low bit) */
   check(env, "(IsOdd 3)", "TRUE", &failures);
   check(env, "(IsOdd 4)", "FALSE", &failures);
   check(env, "(IsOdd 0)", "FALSE", &failures);
   check(env, "(IsOdd 1)", "TRUE", &failures);
   check(env, "(IsOdd -1)", "TRUE", &failures);           /* 0xFFFF...FF & 1 == 1 */
   check(env, "(IsOdd -2)", "FALSE", &failures);          /* 0xFFFF...FE & 1 == 0 */
   check(env, "(IsOdd 1000000001)", "TRUE", &failures);
   check(env, "(IsOdd 1000000000)", "FALSE", &failures);

   /* non-integer arguments -> FAIL (distinct from FALSE/even), not a crash */
   check(env, "(IsOdd \"not-a-number\")", "FAIL", &failures);
   check(env, "(IsOdd 2.5)", "FAIL", &failures);          /* float, not an integer */
   check(env, "(IsOdd oddball)", "FAIL", &failures);      /* a symbol */

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("IsOdd (asm core) TRUE/FALSE/FAIL: OK\n");
   return 0;
}
