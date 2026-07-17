#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

#include <atomic>
#include <mutex>
#include <stdlib.h>   /* free() -- used by free_lock() on every platform */

#include "locker.h"


void* create_lock() {
#ifdef WIN32
    SRWLOCK * srwLock = (SRWLOCK *)calloc(1, sizeof(SRWLOCK));
    if (srwLock) {
        InitializeSRWLock(srwLock);
    }
#else
    pthread_rwlock_t * srwLock = (pthread_rwlock_t *)calloc(1, sizeof(pthread_rwlock_t));
    pthread_rwlock_init(srwLock, NULL);
#endif
    return (void*)srwLock;
}

void free_lock(void* v_lock) {
    if (!v_lock) { return; }
#ifndef WIN32
    /* A Windows SRWLOCK needs no explicit destroy; POSIX rwlocks do. */
    pthread_rwlock_destroy((pthread_rwlock_t*)v_lock);
#endif
    free(v_lock);
}

/* Resettable process-wide singleton lock.
 *
 * A function-local `static` (C++11 "magic static") would give thread-safe
 * once-init for free, but it can never be reset. To support reset_lock() we use
 * a correct C++11 double-checked lock instead: the fast path is a single atomic
 * acquire-load (same cost as the magic static), and first-time creation is
 * serialized by an init mutex. Pre-C++11 this idiom was broken; std::atomic's
 * acquire/release ordering is what makes it correct now. */
static std::atomic<void*> the_lock{ nullptr };
static std::mutex         the_lock_init;

void* ensure_lock() {
    void* p = the_lock.load(std::memory_order_acquire);   /* fast path */
    if (p != nullptr) { return p; }

    std::lock_guard<std::mutex> guard(the_lock_init);
    p = the_lock.load(std::memory_order_relaxed);         /* re-check under mutex */
    if (p == nullptr) {
        p = create_lock();
        the_lock.store(p, std::memory_order_release);
    }
    return p;
}

void reset_lock() {
    std::lock_guard<std::mutex> guard(the_lock_init);
    void* p = the_lock.exchange(nullptr, std::memory_order_acq_rel);
    free_lock(p);
}

/* Count of environments the loader is currently installed into (see locker.h). */
static std::atomic<long> the_active_envs{ 0 };

long loader_env_register(void)   { return the_active_envs.fetch_add(1, std::memory_order_acq_rel) + 1; }
long loader_env_unregister(void) { return the_active_envs.fetch_sub(1, std::memory_order_acq_rel) - 1; }
long loader_env_active(void)     { return the_active_envs.load(std::memory_order_acquire); }

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


