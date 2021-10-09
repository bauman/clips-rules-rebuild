#ifndef LOADER_H
#define LOADER_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif


typedef void(__cdecl* CALLABLE)(void* env, void* udfc, void* out);

EXTERNC void* load_lib(const char* dll_name);

EXTERNC void* free_lib(void* v_hinstLib);

EXTERNC CALLABLE load_fn(void* v_hinstLib, const char* func_name);

#endif