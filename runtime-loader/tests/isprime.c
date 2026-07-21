#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"
#include "run_bounded.h"

/*
 * End-to-end test of the assembly-backed IsPrime plugin: a CLIPS expression calls
 * IsPrime, the dispatcher routes into the runtime-loaded plugin, the C wrapper
 * hands off to the hand-written assembly core (trial division), and a CLIPS
 * symbol comes back.
 *
 * Unlike IsOdd, whose core is one masking instruction, this core has branches, a
 * loop, a multiply and a division -- so the cases below deliberately exercise the
 * loop rather than just the entry conditions: composites whose smallest factor is
 * found on the first, a middle, and the last iteration, plus perfect squares
 * (where d*d == n is the boundary of the stop condition).
 *
 * Only built/run where the plugin has an assembly core for this architecture
 * (gated by `if (TARGET isprime)` in CMake).
 */

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

   AssertString(env, "(functions (library \"" ISPRIME_LIB "\") (function \"IsPrime\"))");
   if (run_bounded(env, 10, 6, "load IsPrime") < 0) { return 1; }

   /* entry conditions: below 2, the even prime, and evens */
   check(env, "(IsPrime -7)", "FALSE", &failures);
   check(env, "(IsPrime 0)",  "FALSE", &failures);
   check(env, "(IsPrime 1)",  "FALSE", &failures);
   check(env, "(IsPrime 2)",  "TRUE",  &failures);   /* the only even prime */
   check(env, "(IsPrime 4)",  "FALSE", &failures);
   check(env, "(IsPrime 100)","FALSE", &failures);

   /* small odd primes -- 3 exits before the loop body can divide */
   check(env, "(IsPrime 3)",  "TRUE",  &failures);
   check(env, "(IsPrime 5)",  "TRUE",  &failures);
   check(env, "(IsPrime 7)",  "TRUE",  &failures);
   check(env, "(IsPrime 11)", "TRUE",  &failures);
   check(env, "(IsPrime 13)", "TRUE",  &failures);

   /* perfect squares of primes: d*d == n exactly, the stop-condition boundary */
   check(env, "(IsPrime 9)",  "FALSE", &failures);   /* 3*3 */
   check(env, "(IsPrime 25)", "FALSE", &failures);   /* 5*5 */
   check(env, "(IsPrime 49)", "FALSE", &failures);   /* 7*7 */

   /* composites found later in the loop */
   check(env, "(IsPrime 21)", "FALSE", &failures);   /* 3 * 7  */
   check(env, "(IsPrime 91)", "FALSE", &failures);   /* 7 * 13 */
   check(env, "(IsPrime 7917)", "FALSE", &failures); /* 3 * 2639 */

   /* larger primes -- these run the loop to completion */
   check(env, "(IsPrime 97)",   "TRUE", &failures);
   check(env, "(IsPrime 7919)", "TRUE", &failures);  /* the 1000th prime */
   check(env, "(IsPrime 104729)", "TRUE", &failures);/* the 10000th prime */

   /* non-integer arguments -> FAIL (distinct from FALSE), not a crash */
   check(env, "(IsPrime \"seven\")", "FAIL", &failures);
   check(env, "(IsPrime 7.5)", "FAIL", &failures);
   check(env, "(IsPrime someSymbol)", "FAIL", &failures);

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("IsPrime (asm core: branches, loop, mul, div) TRUE/FALSE/FAIL: OK\n");
   return 0;
}
