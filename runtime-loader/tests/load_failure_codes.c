#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"

/*
 * The two load-failure modes must be distinguishable in the `loaded` slot:
 *
 *   -3  the library itself failed to load (bad path / missing dependency)
 *   -6  the library loaded, but the requested function/symbol was not found in it
 *
 * These were previously a single -3 ("unable to load library OR function"), which
 * sent a plugin author debugging the wrong thing. Both paths are reachable through
 * the public fact interface, so this is a real end-to-end test (bad path -> -3,
 * real library + bogus function -> -6), with a positive control (Cube -> 1).
 */

static void fail(int* failures, const char* msg)
{
   fprintf(stderr, "FAIL: %s\n", msg);
   (*failures)++;
}

/* Assert a load fact, run, and return the resulting `loaded` slot for that fact
   (matched by its function name). Sets *ok=0 if the fact/slot can't be read. */
static long long load_and_get_code(Environment* env, const char* lib, const char* fn, int* ok)
{
   CLIPSValue rv;
   char buf[512];
   *ok = 0;
   snprintf(buf, sizeof(buf), "(functions (library \"%s\") (function \"%s\"))", lib, fn);
   AssertString(env, buf);
   Run(env, -1);
   snprintf(buf, sizeof(buf),
            "(do-for-fact ((?f functions)) (eq ?f:function \"%s\") ?f:loaded)", fn);
   if (Eval(env, buf, &rv) != EE_NO_ERROR) { return 0; }
   if (rv.header->type != INTEGER_TYPE) { return 0; }
   *ok = 1;
   return rv.integerValue->contents;
}

int main(void)
{
   int failures = 0;
   int ok = 0;
   Environment* env = CreateEnvironment();
   if (env == NULL) { fprintf(stderr, "could not create environment\n"); return 1; }
   if (setup_dispatcher(env) != BE_NO_ERROR)
     { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }

   /* -3: library path that does not resolve. (Distinct function names per case so
      the do-for-fact lookup below matches exactly one `functions` fact.) */
   if (load_and_get_code(env, "./no-such-library.so", "MissingLibFn", &ok) != -3 || !ok)
     { fail(&failures, "bad library path did not yield loaded == -3"); }

   /* -6: real library, function/symbol that is not exported by it */
   if (load_and_get_code(env, CUBE_LIB, "NotAnExport", &ok) != -6 || !ok)
     { fail(&failures, "missing symbol in a loaded library did not yield loaded == -6"); }

   /* positive control: real library + real function loads (loaded == 1) */
   if (load_and_get_code(env, CUBE_LIB, "Cube", &ok) != 1 || !ok)
     { fail(&failures, "valid library+function did not yield loaded == 1"); }

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("load-failure codes (-3 lib / -6 symbol / 1 ok): OK\n");
   return 0;
}
