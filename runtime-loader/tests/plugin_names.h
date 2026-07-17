#ifndef RUNTIME_LOADER_PLUGIN_NAMES_H
#define RUNTIME_LOADER_PLUGIN_NAMES_H

/* Platform-specific filenames for the example plugins, as the tests load them at
   runtime (dlopen/LoadLibrary) from the build directory. `cube` and `cube2` are
   two distinct shared libraries built from the same plugins/Cube.c, so they
   export the SAME symbols (Cube, Square) from different files -- exactly what the
   cross-library name-collision test (F4) needs. */
#ifdef WIN32
#  define CUBE_LIB  "cube.dll"
#  define CUBE2_LIB "cube2.dll"
#elif defined(__APPLE__)
#  define CUBE_LIB  "./libcube.dylib"
#  define CUBE2_LIB "./libcube2.dylib"
#else
#  define CUBE_LIB  "./libcube.so"
#  define CUBE2_LIB "./libcube2.so"
#endif

#endif
