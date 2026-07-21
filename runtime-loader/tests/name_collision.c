#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clips.h"
#include "dispatcher.h"
#include "plugin_names.h"
#include "run_bounded.h"

/*
 * Absolute spelling of a path, portably.
 *
 * realpath() is POSIX-only -- MSVC has no such symbol, and using it here failed to
 * LINK on every Windows leg. _fullpath() is the CRT equivalent and has the same
 * shape (fills the buffer, returns it or NULL).
 *
 * The difference between them does not matter for this test: _fullpath only makes
 * a path absolute and does not resolve symlinks, but all we need is a DIFFERENT
 * SPELLING of the same file, which is exactly what it produces.
 */
#ifdef WIN32
#  define ABSPATH(dst, src) _fullpath((dst), (src), sizeof(dst))
#else
#  define ABSPATH(dst, src) realpath((src), (dst))
#endif

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
   if (run_bounded(env, 10, 6, "load Cube from cube") < 0) { return 1; }
   if (eval_int(env, "(Cube 3)") != 27) { fprintf(stderr, "FAIL: Cube(3) != 27\n"); failures++; }

   /* same name from a DIFFERENT library -> must be refused */
   AssertString(env, "(functions (library \"" CUBE2_LIB "\") (function \"Cube\"))");
   /* refused: loadlib fires, then the -4 name-collision error rule */
   if (run_bounded(env, 10, 6, "load Cube from cube2 (collision)") < 0) { return 1; }

   collision_loaded = loaded_for_library(env, CUBE2_LIB, &found);
   if (!found)                     { fprintf(stderr, "FAIL: collision fact not found\n"); failures++; }
   else if (collision_loaded != -4){ fprintf(stderr, "FAIL: collision loaded=%lld, expected -4\n", collision_loaded); failures++; }

   /* original must still dispatch into the first library */
   if (eval_int(env, "(Cube 3)") != 27) { fprintf(stderr, "FAIL: original Cube broke after collision\n"); failures++; }

   /* PATH IDENTITY: a library is keyed by the literal path string, so the SAME
      file under a second spelling is treated as a different library and refused.
      This is documented behaviour (dispatcher.h), not a bug -- canonicalisation
      cannot be made correct, so the loader does not attempt it. Asserted here so
      the documented rule stays true. */
   {
      char abs[1200];
      char fact[1400];
      CLIPSValue rv;
      if (ABSPATH(abs, CUBE_LIB) == NULL)
        {
         /* Never silently skip: ctest runs us from the directory holding the
            plugin, so this resolving is part of the contract being tested. */
         fprintf(stderr, "FAIL: could not resolve an absolute path for %s (wrong working directory?)\n", CUBE_LIB);
         failures++;
        }
      else
        {
         char* p;
         /* Windows returns backslash paths, and CLIPS treats backslash as an
            ESCAPE inside a string literal -- embedding "D:\\a\\b\\cube.dll" in a
            fact silently yields "D:abcube.dll", so the load would fail as a bad
            path (-3) instead of the collision (-4) we are testing. Normalise to
            forward slashes, which Windows accepts in LoadLibrary and which need no
            escaping. A no-op on POSIX. */
         for (p = abs; *p != '\0'; p++) { if (*p == '\\') { *p = '/'; } }

         snprintf(fact, sizeof fact,
                  "(functions (library \"%s\") (function \"Cube\"))", abs);
         AssertString(env, fact);
         if (run_bounded(env, 10, 6, "same file, absolute spelling") < 0) { return 1; }

         if (Eval(env, "(do-for-fact ((?f functions)) (eq ?f:library \"" CUBE_LIB "\") ?f:loaded)", &rv) != EE_NO_ERROR
             || rv.header->type != INTEGER_TYPE || rv.integerValue->contents != 1)
           { fprintf(stderr, "FAIL: the original relative-path load should still be loaded\n"); failures++; }

         snprintf(fact, sizeof fact,
                  "(do-for-fact ((?f functions)) (eq ?f:library \"%s\") ?f:loaded)", abs);
         if (Eval(env, fact, &rv) != EE_NO_ERROR
             || rv.header->type != INTEGER_TYPE || rv.integerValue->contents != -4)
           { fprintf(stderr, "FAIL: same file under an absolute spelling should be refused with -4\n"); failures++; }

         /* and the diagnostic must NAME the conflicting path, so the user can see
            it is the same file rather than guessing */
         snprintf(fact, sizeof fact,
                  "(do-for-fact ((?f functions)) (eq ?f:library \"%s\") ?f:error)", abs);
         if (Eval(env, fact, &rv) != EE_NO_ERROR || rv.header->type != STRING_TYPE
             || strstr(rv.lexemeValue->contents, CUBE_LIB) == NULL)
           { fprintf(stderr, "FAIL: the -4 error should name the owning library path\n"); failures++; }
        }
   }

   DestroyEnvironment(env);

   if (failures) { fprintf(stderr, "%d failure(s)\n", failures); return 1; }
   printf("F4 name-collision: OK\n");
   return 0;
}
