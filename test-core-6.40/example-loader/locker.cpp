#ifdef WIN32
#include <Windows.h>
#else

#endif

#include "locker.h"


void* create_lock() {
    SRWLOCK * srwLock = (SRWLOCK *)calloc(1, sizeof(SRWLOCK));
    if (srwLock) {
        InitializeSRWLock(srwLock);
    }
    return (void*)srwLock;
}

void   lock_read(void* v_lock) {
    SRWLOCK* srwLock = (SRWLOCK*)v_lock;
    if (srwLock) {
        AcquireSRWLockShared(srwLock);
    }
}

void   lock_write(void* v_lock) {
    SRWLOCK* srwLock = (SRWLOCK*)v_lock;
    if (srwLock) {
        AcquireSRWLockExclusive(srwLock);
    }
}

void   unlock_read(void* v_lock) {
    SRWLOCK* srwLock = (SRWLOCK*)v_lock;
    if (srwLock) {
        ReleaseSRWLockShared(srwLock);
    }
}

void   unlock_write(void* v_lock) {
    SRWLOCK* srwLock = (SRWLOCK*)v_lock;
    if (srwLock) {
        ReleaseSRWLockExclusive(srwLock);
    }
}
