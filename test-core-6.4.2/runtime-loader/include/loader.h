#ifndef LOADER_H
#define LOADER_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#ifdef WIN32
typedef void(__cdecl* CALLABLE)(void* env, void* udfc, void* out);
#else
typedef void * (*CALLABLE)(void* env, void* udfc, void* out);
#endif

EXTERNC void* load_lib(const char* dll_name);

EXTERNC void* free_lib(void* v_hinstLib);

EXTERNC CALLABLE load_fn(void* v_hinstLib, const char* func_name);

#endif