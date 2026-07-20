#ifndef RUNTIME_LOADER_PLUGIN_NAMES_H
#define RUNTIME_LOADER_PLUGIN_NAMES_H

/* Platform-specific filenames for the plugins, as the tests load them at runtime
   (dlopen/LoadLibrary) from the build directory:

     CUBE_LIB              the real example plugin (plugins/Cube), exports Cube+Square
     CUBE2_LIB             a byte-identical SECOND library built from the same source,
                           so two distinct files export the same names -- what the
                           cross-library name-collision constraint (F4) needs
     CUBE_FOR_TESTING_LIB  a deliberately WRONG build of Cube (n^3 + 1000), a test
                           fixture only (plugins/CubeForTesting) -- it makes a hot
                           update observable, and must never be used as an example
     HOTSWAP_LIB           a scratch path the hot-update test deploys onto, first
                           with the real plugin and then with the wrong one, so the
                           effect of a genuine reload is visible in the result */
#ifdef WIN32
#  define CUBE_LIB    "cube.dll"
#  define CUBE2_LIB   "cube2.dll"
#  define CUBE_FOR_TESTING_LIB  "cubefortesting.dll"
#  define HOTSWAP_LIB "hotswap.dll"
#elif defined(__APPLE__)
#  define CUBE_LIB    "./libcube.dylib"
#  define CUBE2_LIB   "./libcube2.dylib"
#  define CUBE_FOR_TESTING_LIB  "./libcubefortesting.dylib"
#  define HOTSWAP_LIB "./libhotswap.dylib"
#else
#  define CUBE_LIB    "./libcube.so"
#  define CUBE2_LIB   "./libcube2.so"
#  define CUBE_FOR_TESTING_LIB  "./libcubefortesting.so"
#  define HOTSWAP_LIB "./libhotswap.so"
#endif

/* The assembly-backed IsOdd plugin is aarch64/arm64-only, but that includes
   Windows/ARM64 (armasm64 core), so it needs a name on every platform. */
#ifdef WIN32
#  define ISODD_LIB "isodd.dll"
#elif defined(__APPLE__)
#  define ISODD_LIB "./libisodd.dylib"
#else
#  define ISODD_LIB "./libisodd.so"
#endif

#endif
