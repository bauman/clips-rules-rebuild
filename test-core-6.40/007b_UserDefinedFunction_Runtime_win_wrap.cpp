#include <stdbool.h>
#include <windows.h> 

typedef void (__cdecl* MYPROC)(void* env, void* udfc, void* out);

void main() {
    HINSTANCE hinstLib;
    MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;
    hinstLib = LoadLibrary(TEXT("udfrt007.dll"));
    ProcAdd = (MYPROC)GetProcAddress(hinstLib,TEXT("Cube"));
    
    fFreeResult = FreeLibrary(hinstLib);
}

