
#include <stdbool.h>
#include "loader.h"

#ifdef WIN32
#include <Windows.h>
#else
#include <stddef.h>
#include <dlfcn.h>
#endif



void* free_lib(void* v_hinstLib) {
    void* result = v_hinstLib;
    if (v_hinstLib) {
#ifdef WIN32
        HINSTANCE* hinstLib_p = (HINSTANCE*)v_hinstLib;
        HINSTANCE hinstLib = *hinstLib_p;
        BOOL freed = FreeLibrary(hinstLib);
#else
        bool freed = dlclose(v_hinstLib);
#endif
        if (freed) {
            result = NULL;
        }
    }
    return result;
}


void* load_lib(const char* dll_name)
{
#ifdef WIN32
    void* v_hinstLib = calloc(1, sizeof(HINSTANCE));
    if (v_hinstLib) {
        HINSTANCE hinstLib = LoadLibrary(TEXT(dll_name));
        memcpy_s(v_hinstLib, sizeof(HINSTANCE), &hinstLib, sizeof(HINSTANCE));
        if (!hinstLib) {
            free(v_hinstLib);
            v_hinstLib = NULL;
        }
    }
#else
    void* v_hinstLib = dlopen(dll_name, RTLD_NOW);
#endif
    return v_hinstLib;
}



CALLABLE load_fn(void* v_hinstLib, const char * func_name)
{
    CALLABLE ProcAdd = NULL;
    if (v_hinstLib) {
#ifdef WIN32
        HINSTANCE* hinstLib_p = (HINSTANCE*)v_hinstLib;
        HINSTANCE hinstLib = *hinstLib_p;
        ProcAdd = (CALLABLE)GetProcAddress(hinstLib, TEXT(func_name));
#else
        ProcAdd = (CALLABLE) dlsym(v_hinstLib, func_name);
#endif
    }
    return ProcAdd; // ProcAdd;
}

