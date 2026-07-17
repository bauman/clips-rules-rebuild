#include <stdio.h>

#include "clips.h"
#include "dispatcher.h"

static void Dummy(Environment* env, UDFContext* udfc, UDFValue* out)
{ (void)env; (void)udfc; (void)out; }

/*
 * setup_dispatcher must NOT mask a UDF-registration failure. The three loader
 * UDFs (LoadDispatch/UnLoadDispatch/Dispatch) ARE the module; if one can't be
 * registered the dispatcher is non-functional, so setup_dispatcher must return a
 * non-zero BuildError instead of building rules that reference missing functions
 * and reporting success.
 */
int main(void)
{
   int failures = 0;

   /* positive control: a clean environment sets up successfully */
   Environment* ok = CreateEnvironment();
   if (setup_dispatcher(ok) != BE_NO_ERROR)
     { fprintf(stderr, "FAIL: setup_dispatcher failed on a clean environment\n"); failures++; }
   DestroyEnvironment(ok);

   /* negative: pre-register a conflicting "LoadDispatch" so the loader's AddUDF
      for that name fails; setup_dispatcher must report the failure */
   Environment* bad = CreateEnvironment();
   AddUDF(bad, "LoadDispatch", "l", 0, 0, "", Dummy, "Dummy", NULL);
   if (setup_dispatcher(bad) == BE_NO_ERROR)
     { fprintf(stderr, "FAIL: setup_dispatcher masked a UDF-registration failure\n"); failures++; }
   DestroyEnvironment(bad);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("UDF registration failure propagation: OK\n");
   return 0;
}
