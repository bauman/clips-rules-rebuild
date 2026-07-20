#ifndef LOADER_H
#define LOADER_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/* A plugin entry point has the CLIPS UDF signature: it returns void and takes
   (Environment*, UDFContext*, UDFValue*). The pointer type must match that exactly
   -- calling through a pointer whose return type disagrees with the function's is
   undefined behavior. (The POSIX variant previously declared a void* return, not
   void, which is why this is stated explicitly.) */
#ifdef WIN32
typedef void(__cdecl* CALLABLE)(void* env, void* udfc, void* out);
#else
typedef void (*CALLABLE)(void* env, void* udfc, void* out);
#endif

EXTERNC void* load_lib(const char* dll_name);

EXTERNC void* free_lib(void* v_hinstLib);

EXTERNC CALLABLE load_fn(void* v_hinstLib, const char* func_name);

#endif