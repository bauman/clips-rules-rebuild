#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"
#include "run_bounded.h"

/*
 * HOT UPDATE: ship a bug fix by replacing a plugin's shared library underneath a
 * running rule base, without touching a single rule.
 *
 * This is the scenario the whole bounce design exists for, staged the way it
 * actually happens in production: the deployed plugin is BUGGY (it returns
 * n^3 + 1000), the rule base is already built on top of it, and a corrected build
 * is rolled out in place. The answer observed through the UNCHANGED rule goes from
 * wrong (1027) to right (27) -- which could not happen if the buggy library had
 * merely stayed mapped, or if the "reload" had been a no-op.
 *
 * It is also the one test that proves the reload is REAL, precisely because the
 * two builds differ in behaviour; see plugins/CubeForTesting.
 *
 * Sequence:
 *   1. deploy the BUGGY build, load it, build a defrule that calls the function
 *   2. run: the rule produces the buggy answer (1027)
 *   3. unload -- must succeed even though the rule references the function
 *   4. verify the rule, the deffunction wrapper, and the fact base are all intact
 *   5. deploy the FIXED build over the same library path
 *   6. load again
 *   7. run: the SAME, never-rebuilt rule now produces the correct answer (27)
 *
 * Step 5 also matters on Windows: a DLL that was not genuinely released cannot be
 * replaced (sharing violation), so a successful deploy there is independent
 * evidence that FreeLibrary actually took effect.
 */

static void fail(int* failures, const char* msg)
{
   fprintf(stderr, "FAIL: %s\n", msg);
   (*failures)++;
}

static int copy_bytes(const char* src, const char* dst)
{
   char buf[8192];
   size_t n;
   int ok = 1;
   FILE* in = fopen(src, "rb");
   FILE* out;
   if (in == NULL) { return 0; }
   out = fopen(dst, "wb");
   if (out == NULL) { fclose(in); return 0; }
   while ((n = fread(buf, 1, sizeof buf, in)) > 0)
     { if (fwrite(buf, 1, n, out) != n) { ok = 0; break; } }
   if (fclose(out) != 0) { ok = 0; }
   fclose(in);
   return ok;
}

/*
 * The "deploy" step: put `src` at path `dst`, replacing whatever is there.
 *
 * Deliberately writes a temp file and rename()s it into place rather than
 * truncating `dst` and rewriting it. Overwriting a shared library IN PLACE after
 * it has been mapped is genuinely unsafe: on macOS the kernel SIGKILLs the
 * process when it later maps the modified file, because the code signature no
 * longer matches what was cached (observed while writing this test -- the
 * in-place version died with signal 9 on the second load). rename() swaps in a fresh
 * inode instead, which is also the atomic-replace pattern a real deployment
 * should use.
 */
static int deploy_file(const char* src, const char* dst)
{
   char tmp[512];
   snprintf(tmp, sizeof tmp, "%s.new", dst);
   if (!copy_bytes(src, tmp)) { return 0; }
   remove(dst);                                   /* Windows: rename fails if dst exists */
   if (rename(tmp, dst) != 0) { remove(tmp); return 0; }
   return 1;
}

static long long loaded_slot(Environment* env)
{
   CLIPSValue rv;
   if (Eval(env, "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\") ?f:loaded)", &rv) != EE_NO_ERROR) { return -999; }
   if (rv.header->type != INTEGER_TYPE) { return -999; }
   return rv.integerValue->contents;
}

/* Assert an `m` fact with value 3, let the rule fire, and report what it computed. */
static long long rule_result(Environment* env, int* failures, const char* phase)
{
   CLIPSValue rv;
   char msg[160];
   AssertString(env, "(m (v 3))");
   if (run_bounded(env, 10, 6, phase) < 0) { return -999; }
   if (Eval(env, "(do-for-fact ((?f m)) (eq ?f:done TRUE) ?f:v)", &rv) != EE_NO_ERROR
       || rv.header->type != INTEGER_TYPE)
     {
      snprintf(msg, sizeof msg, "%s: could not read the rule's result", phase);
      fail(failures, msg);
      return -999;
     }
   /* retract so the next phase starts clean */
   Eval(env, "(do-for-fact ((?f m)) TRUE (retract ?f))", NULL);
   return rv.integerValue->contents;
}

int main(void)
{
   int failures = 0;
   CLIPSValue rv;
   Environment* env;

   /* ---- 1. deploy the BUGGY build -- this is what is already in production ---- */
   if (!deploy_file(CUBE_FOR_TESTING_LIB, HOTSWAP_LIB))
     { fprintf(stderr, "could not deploy the buggy build (%s -> %s)\n", CUBE_FOR_TESTING_LIB, HOTSWAP_LIB); return 1; }

   env = CreateEnvironment();
   if (env == NULL) { fprintf(stderr, "could not create environment\n"); return 1; }
   if (setup_dispatcher(env) != BE_NO_ERROR) { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }

   AssertString(env, "(functions (library \"" HOTSWAP_LIB "\") (function \"Cube\"))");
   if (run_bounded(env, 10, 6, "load the buggy build") < 0) { return 1; }
   if (loaded_slot(env) != 1) { fail(&failures, "the buggy build did not load"); }

   /* the rule base -- built ONCE here and never touched again */
   Build(env, "(deftemplate m (slot v (type INTEGER)) (slot done (type SYMBOL) (default FALSE)))");
   Build(env, "(defrule uses-cube ?d <- (m (v ?v) (done FALSE)) => (modify ?d (v (Cube ?v)) (done TRUE)))");
   if (FindDefrule(env, "uses-cube") == NULL) { fail(&failures, "could not build the rule"); return 1; }

   /* ---- 2. the bug is observable through the rule ---- */
   if (rule_result(env, &failures, "rule with the buggy build") != 1027)
     { fail(&failures, "rule did not produce the buggy answer (1027)"); }

   /* ---- 3. unload, with the rule still referencing the function ---- */
   Eval(env, "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\") (modify ?f (action \"unload\")))", NULL);
   if (run_bounded(env, 10, 6, "unload") < 0) { return 1; }
   if (loaded_slot(env) != 0)
     { fail(&failures, "unload did not succeed while a rule referenced the function"); }

   /* ---- 4. everything CLIPS-side survived the unload ---- */
   if (FindDefrule(env, "uses-cube") == NULL)   { fail(&failures, "the rule was destroyed by the unload"); }
   if (FindDeffunction(env, "Cube") == NULL)    { fail(&failures, "the wrapper was destroyed by the unload"); }
   if (FindDeftemplate(env, "m") == NULL)       { fail(&failures, "the template was destroyed by the unload"); }
   /* and while unloaded the wrapper is inert rather than dangling */
   if (Eval(env, "(Cube 3)", &rv) != EE_NO_ERROR)
     { fail(&failures, "calling Cube while unloaded errored instead of failing safe"); }
   else if (rv.header->type != SYMBOL_TYPE || strcmp(rv.lexemeValue->contents, "FALSE") != 0)
     { fail(&failures, "unloaded Cube did not fail safe to FALSE"); }

   /* ---- 5. THE DEPLOY: roll out the FIXED build over the same path ----
      On Windows this only succeeds if the DLL was genuinely released. */
   if (!deploy_file(CUBE_LIB, HOTSWAP_LIB))
     { fail(&failures, "could not deploy the fixed build (still held open?)"); return 1; }

   /* ---- 6. load again from the SAME path ---- */
   Eval(env, "(do-for-fact ((?f functions)) (eq ?f:function \"Cube\") (modify ?f (action \"load\") (loaded 0)))", NULL);
   if (run_bounded(env, 10, 6, "load the fixed build") < 0) { return 1; }
   if (loaded_slot(env) != 1) { fail(&failures, "the fixed build did not load"); }

   /* ---- 7. the untouched rule now yields the CORRECT answer ---- */
   if (FindDefrule(env, "uses-cube") == NULL)
     { fail(&failures, "the rule vanished across the hot update"); }
   {
      long long r = rule_result(env, &failures, "rule with the fixed build");
      if (r == 1027)
        { fail(&failures, "still the buggy answer -- the old library was never released, the fix did not take"); }
      else if (r != 27)
        { fprintf(stderr, "FAIL: rule produced %lld, expected the fixed answer 27\n", r); failures++; }
   }

   DestroyEnvironment(env);
   remove(HOTSWAP_LIB);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("hot update: bug fix deployed under a live, never-modified rule base: OK\n");
   return 0;
}
