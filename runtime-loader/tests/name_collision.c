#include <stdio.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"

/*
 * F4 regression: function names must be unique across ALL libraries. A name
 * already loaded from one library must be refused (loaded == -4) when requested
 * from a DIFFERENT library, and the original must keep working.
 *
 * cube and cube2 are two distinct shared libraries that both export "Cube"
 * (built from the same source). We load Cube from cube, then try to load Cube
 * from cube2 and assert the second load is refused.
 */

static long long eval_int(Environment* env, const char* expr)
{
   CLIPSValue rv;
   if (Eval(env, expr, &rv) != EE_NO_ERROR) { return -99999; }
   return rv.integerValue->contents;
}

/* Find the `functions` fact for a given library and return its `loaded` slot.
   Sets *found to whether such a fact exists. */
static long long loaded_for_library(Environment* env, const char* library, int* found)
{
   Fact* f = GetNextFact(env, NULL);
   *found = 0;
   while (f != NULL)
     {
      CLIPSValue lib;
      if ((GetFactSlot(f, "library", &lib) == GSE_NO_ERROR) &&
          (lib.lexemeValue != NULL) &&
          (strcmp(lib.lexemeValue->contents, library) == 0))
        {
         CLIPSValue loaded;
         GetFactSlot(f, "loaded", &loaded);
         *found = 1;
         return loaded.integerValue->contents;
        }
      f = GetNextFact(env, f);
     }
   return 0;
}

int main(void)
{
   int failures = 0;
   int found = 0;
   long long collision_loaded;
   Environment* env = CreateEnvironment();
   if (env == NULL) { fprintf(stderr, "could not create environment\n"); return 1; }
   if (setup_dispatcher(env) != BE_NO_ERROR) { fprintf(stderr, "setup_dispatcher failed\n"); return 1; }

   AssertString(env, "(functions (library \"" CUBE_LIB "\") (function \"Cube\"))");
   Run(env, -1);
   if (eval_int(env, "(Cube 3)") != 27) { fprintf(stderr, "FAIL: Cube(3) != 27\n"); failures++; }

   /* same name from a DIFFERENT library -> must be refused */
   AssertString(env, "(functions (library \"" CUBE2_LIB "\") (function \"Cube\"))");
   Run(env, -1);

   collision_loaded = loaded_for_library(env, CUBE2_LIB, &found);
   if (!found)                     { fprintf(stderr, "FAIL: collision fact not found\n"); failures++; }
   else if (collision_loaded != -4){ fprintf(stderr, "FAIL: collision loaded=%lld, expected -4\n", collision_loaded); failures++; }

   /* original must still dispatch into the first library */
   if (eval_int(env, "(Cube 3)") != 27) { fprintf(stderr, "FAIL: original Cube broke after collision\n"); failures++; }

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("F4 name-collision: OK\n");
   return 0;
}
