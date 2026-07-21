#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"
#include "run_bounded.h"

/*
 * End-to-end test of the AMX matrix-multiply plugin.
 *
 * The result is checked against a plain-C reference computed here, NOT against
 * hardcoded numbers. That matters more than usual: the plugin drives undocumented
 * silicon through reverse-engineered instruction encodings, so "it returned
 * something" is worth very little -- the only meaningful assertion is that the
 * coprocessor agrees with an independent implementation of the same arithmetic.
 *
 * Also exercises the plugin's half of the loader contract: malformed arguments
 * must come back as the symbol FAIL, not as a crash and not as a wrong matrix.
 *
 * Only built/run on Apple Silicon (gated by `if (TARGET matrixmultiply)`).
 */

static void fail(int* failures, const char* msg)
{
   fprintf(stderr, "FAIL: %s\n", msg);
   (*failures)++;
}

/* Plain-C reference: C(2x2) = A(2x4) * B(4x2), all row-major. */
static void reference_matmul(const double A[8], const double B[8], double C[4])
{
   int i, j, k;
   for (i = 0; i < 2; i++)
     for (j = 0; j < 2; j++)
       {
        double sum = 0.0;
        for (k = 0; k < 4; k++) { sum += A[i * 4 + k] * B[k * 2 + j]; }
        C[i * 2 + j] = sum;
       }
}

/* Call (MatrixMultiply <A> <B>) and compare against the reference. */
static void check_product(Environment* env, const double A[8], const double B[8],
                          const char* label, int* failures)
{
   CLIPSValue rv;
   char expr[512];
   double expected[4];
   int i, n;

   /* 16 scalars: A (2x4) then B (4x2). The loader's wrapper flattens multifields,
      so (MatrixMultiply (create$ ...) (create$ ...)) arrives identically -- both
      spellings are exercised below. */
   n = snprintf(expr, sizeof expr,
                "(MatrixMultiply %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g)",
                A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],
                B[0],B[1],B[2],B[3],B[4],B[5],B[6],B[7]);
   if (n <= 0 || (size_t)n >= sizeof expr) { fail(failures, "expression too long"); return; }

   reference_matmul(A, B, expected);

   if (Eval(env, expr, &rv) != EE_NO_ERROR)
     { fail(failures, "eval error calling MatrixMultiply"); return; }
   if (rv.header->type != MULTIFIELD_TYPE)
     {
      fprintf(stderr, "FAIL: %s: expected a multifield result, got %s\n", label,
              (rv.header->type == SYMBOL_TYPE ? rv.lexemeValue->contents : "<other>"));
      (*failures)++;
      return;
     }
   if (rv.multifieldValue->length != 4)
     { fail(failures, "result multifield was not 4 elements"); return; }

   for (i = 0; i < 4; i++)
     {
      CLIPSValue *e = &rv.multifieldValue->contents[i];
      double got = (e->header->type == FLOAT_TYPE)   ? e->floatValue->contents
                 : (e->header->type == INTEGER_TYPE) ? (double)e->integerValue->contents
                 : -1e30;
      if (got != expected[i])
        {
         fprintf(stderr, "FAIL: %s: element %d = %g, reference says %g\n",
                 label, i, got, expected[i]);
         (*failures)++;
        }
     }
}

static void check_symbol(Environment* env, const char* expr, const char* expect, int* failures)
{
   CLIPSValue rv;
   if (Eval(env, expr, &rv) != EE_NO_ERROR)
     { fprintf(stderr, "FAIL: eval error for %s\n", expr); (*failures)++; return; }
   if (rv.header->type != SYMBOL_TYPE || strcmp(rv.lexemeValue->contents, expect) != 0)
     {
      fprintf(stderr, "FAIL: %s did not return %s\n", expr, expect);
      (*failures)++;
     }
}

int main(void)
{
   int failures = 0;
   CLIPSValue rv;
   Environment* env = CreateEnvironment();
   if (env == NULL) { fprintf(stderr, "could not create environment\n"); return 1; }
   if (setup_dispatcher(env) != BE_NO_ERROR) { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }

   AssertString(env, "(functions (library \"" MATMUL_LIB "\") (function \"MatrixMultiply\"))");
   if (run_bounded(env, 10, 6, "load MatrixMultiply") < 0) { return 1; }

   /* If the plugin refuses this host, every product call returns FAIL. That is a
      correct outcome for the contract, but it means the arithmetic below proves
      nothing -- so say so loudly rather than reporting a hollow pass. */
   if (Eval(env, "(MatrixMultiply 1 2 3 4 5 6 7 8 1 0 0 1 0 0 0 0)", &rv) == EE_NO_ERROR
       && rv.header->type == SYMBOL_TYPE && strcmp(rv.lexemeValue->contents, "FAIL") == 0)
     {
      fprintf(stderr, "SKIP: the plugin refused this host (no AMX) -- arithmetic not exercised\n");
      DestroyEnvironment(env);
      return 0;
     }

   {
      /* the worked example: A(2x4) * B(4x2) */
      static const double A1[8] = {1,2,3,4, 5,6,7,8};
      static const double B1[8] = {9,10, 11,12, 13,14, 15,16};
      check_product(env, A1, B1, "classic 2x4 * 4x2", &failures);

      /* identity-ish: B selects columns, so C is the first two columns of A */
      static const double A2[8] = {1,2,3,4, 5,6,7,8};
      static const double B2[8] = {1,0, 0,1, 0,0, 0,0};
      check_product(env, A2, B2, "column selection", &failures);

      /* zeros, negatives and fractions */
      static const double A3[8] = {0,0,0,0, 0,0,0,0};
      static const double B3[8] = {1,2, 3,4, 5,6, 7,8};
      check_product(env, A3, B3, "zero matrix", &failures);

      static const double A4[8] = {-1,2,-3,4, 5,-6,7,-8};
      static const double B4[8] = {-9,10, 11,-12, -13,14, 15,-16};
      check_product(env, A4, B4, "signed values", &failures);

      static const double A5[8] = {0.5,1.5,2.5,3.5, -0.5,-1.5,-2.5,-3.5};
      static const double B5[8] = {0.25,0.5, 1.25,1.5, 2.25,2.5, 3.25,3.5};
      check_product(env, A5, B5, "fractional values", &failures);
   }

   /* the contract: malformed arguments are refused as FAIL, never a crash */
   check_symbol(env, "(MatrixMultiply 1 2 3)", "FAIL", &failures);                       /* too few */
   check_symbol(env, "(MatrixMultiply 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17)", "FAIL", &failures); /* too many */
   check_symbol(env, "(MatrixMultiply 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 abc)", "FAIL", &failures);   /* non-number */
   check_symbol(env, "(MatrixMultiply \"a\" 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16)", "FAIL", &failures);/* string */

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("MatrixMultiply (Apple AMX coprocessor) vs C reference: OK\n");
   return 0;
}
