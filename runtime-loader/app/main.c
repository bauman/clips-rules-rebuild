#include <stdio.h>

#include "clips.h"
#include "dispatcher.h"

/*
 * runtime-clips — a standalone CLIPS runtime with the runtime-loader plugin
 * system pre-registered.
 *
 * On startup it creates a CLIPS environment and calls setup_dispatcher(), which
 * registers the LoadDispatch / UnLoadDispatch / Dispatch UDFs, the `functions`
 * deftemplate, and the load/unload/error rules. Any .clp files named on the
 * command line are then loaded, the environment is reset and run, and finally an
 * interactive CLIPS REPL is entered.
 *
 * Within CLIPS you can load a shared-library plugin and expose its UDF at
 * runtime by asserting a `functions` fact, e.g.:
 *
 *     (assert (functions (library "./libcube.so") (function "Cube")))
 *     (run)
 *     (Cube 3)        ; -> 27, dispatched into the plugin
 */
int main(int argc, char **argv)
{
   Environment *env;
   int i;

   env = CreateEnvironment();
   if (env == NULL)
     {
      fprintf(stderr, "runtime-clips: could not create CLIPS environment\n");
      return 1;
     }

   if (setup_dispatcher(env) != BE_NO_ERROR)
     {
      fprintf(stderr, "runtime-clips: could not initialize the runtime loader\n");
      DestroyEnvironment(env);
      return 1;
     }

   for (i = 1; i < argc; i++)
     {
      if (Load(env, argv[i]) != LE_NO_ERROR)
        { fprintf(stderr, "runtime-clips: failed to load '%s'\n", argv[i]); }
     }

   Reset(env);
   Run(env, -1);

   CommandLoop(env);

   DestroyEnvironment(env);
   return 0;
}
