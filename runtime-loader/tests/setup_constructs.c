#include <stdio.h>

#include "clips.h"
#include "dispatcher.h"

/*
 * setup_dispatcher must build ALL of its hardcoded constructs successfully.
 *
 * This is the regression guard for the error-propagation fix (BuildError is an
 * enum, not a count -- see build_step in dispatcher.c): if someone later edits a
 * hardcoded deftemplate/defrule string into something malformed, setup_dispatcher
 * must now surface it as a non-BE_NO_ERROR return, and this test fails.
 *
 * It also checks each construct exists BY NAME, which is strictly stronger than a
 * BE_NO_ERROR check: it catches SILENT REPLACEMENT (two constructs accidentally
 * sharing a name -- Build returns success but one clobbers the other). That was a
 * real bug once (F4: two rules both named loader-invalid-loader-type), and a
 * return-code check alone would not have caught it.
 */

static const char* expected_rules[] = {
   "loadlib",
   "unloadlib",
   "loader-invalid-args",
   "loader-invalid-function-name",
   "loader-invalid-function-length",
   "loader-load-failed",
   "loader-symbol-not-found",
   "loader-invalid-arity",
   "loader-name-collision",
   "cleanuplib",
   "cleanup-delete-failed",
   "cleanup-still-referenced",
   "unloader-not-loaded",
};

/* Assert every expected construct is present in env. Returns the failure count. */
static int check_constructs(Environment* env, const char* phase)
{
   int failures = 0;
   size_t i;
   if (FindDeftemplate(env, "functions") == NULL)
     { fprintf(stderr, "FAIL (%s): deftemplate `functions` missing\n", phase); failures++; }
   for (i = 0; i < sizeof(expected_rules) / sizeof(expected_rules[0]); i++)
     {
      if (FindDefrule(env, expected_rules[i]) == NULL)
        { fprintf(stderr, "FAIL (%s): defrule `%s` missing\n", phase, expected_rules[i]); failures++; }
     }
   return failures;
}

int main(void)
{
   int failures = 0;
   Environment* env = CreateEnvironment();
   if (env == NULL) { fprintf(stderr, "could not create environment\n"); return 1; }

   /* first call does the real build: must succeed and install every construct */
   if (setup_dispatcher(env) != BE_NO_ERROR)
     { fprintf(stderr, "FAIL: setup_dispatcher did not return BE_NO_ERROR\n"); failures++; }
   failures += check_constructs(env, "after setup");

   /* second call is the idempotent no-op path: still success, constructs intact
      (not rebuilt, duplicated, or dropped) */
   if (setup_dispatcher(env) != BE_NO_ERROR)
     { fprintf(stderr, "FAIL: idempotent setup_dispatcher did not return BE_NO_ERROR\n"); failures++; }
   failures += check_constructs(env, "after idempotent re-setup");

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("setup_dispatcher builds all constructs: OK\n");
   return 0;
}
