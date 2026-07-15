#include <stdbool.h>
#include <windows.h> 

typedef void (__cdecl* MYPROC)(void* env, void* udfc, void* out);

int main() {
    HINSTANCE hinstLib = LoadLibrary(TEXT("cube.dll"));
    if (hinstLib == NULL) {
        return 1;  // cube.dll failed to load
    }
    MYPROC ProcAdd = (MYPROC)GetProcAddress(hinstLib, TEXT("Cube"));
    if (ProcAdd == NULL) {
        FreeLibrary(hinstLib);
        return 2;  // Cube not exported by cube.dll
    }
    if (!FreeLibrary(hinstLib)) {
        return 3;  // failed to free the library
    }
    return 0;
}

