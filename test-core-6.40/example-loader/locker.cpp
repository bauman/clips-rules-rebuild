#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#include <stdlib.h>
#endif

#include "locker.h"


void* create_lock() {
#ifdef WIN32
    SRWLOCK * srwLock = (SRWLOCK *)calloc(1, sizeof(SRWLOCK));
    if (srwLock) {
        InitializeSRWLock(srwLock);
    }
#else
    pthread_rwlock_t * srwLock = (pthread_rwlock_t *)calloc(1, sizeof(pthread_rwlock_t));
    *srwLock = PTHREAD_RWLOCK_INITIALIZER;
#endif
    return (void*)srwLock;
}

void   lock_read(void* v_lock) {
#ifdef WIN32
    SRWLOCK* srwLock = (SRWLOCK*)v_lock;
    if (srwLock) {
        AcquireSRWLockShared(srwLock);
    }
#else
    if (v_lock){
        pthread_rwlock_rdlock((pthread_rwlock_t *)v_lock);
    }
#endif
}

void   lock_write(void* v_lock) {
#ifdef WIN32
    SRWLOCK* srwLock = (SRWLOCK*)v_lock;
    if (srwLock) {
        AcquireSRWLockExclusive(srwLock);
    }
#else
    if(v_lock){
        pthread_rwlock_wrlock((pthread_rwlock_t *)v_lock);
    }
#endif
}

void   unlock_read(void* v_lock) {
#ifdef WIN32
    SRWLOCK* srwLock = (SRWLOCK*)v_lock;
    if (srwLock) {
        ReleaseSRWLockShared(srwLock);
    }
#else
    if(v_lock){
        pthread_rwlock_unlock((pthread_rwlock_t *)v_lock);
    }
#endif
}

void   unlock_write(void* v_lock) {
#ifdef WIN32
    SRWLOCK* srwLock = (SRWLOCK*)v_lock;
    if (srwLock) {
        ReleaseSRWLockExclusive(srwLock);
    }
#else
    if(v_lock){
        pthread_rwlock_unlock((pthread_rwlock_t *)v_lock);
    }
#endif
}
