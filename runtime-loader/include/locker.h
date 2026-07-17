#ifndef LOCKER_H
#define LOCKER_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif


EXTERNC void * create_lock();
/* Returns the process-wide loader lock, created exactly once in a thread-safe
   way (no create-check-assign race). Use this instead of a lazily-initialized
   global for shared state that outlives any single environment. */
EXTERNC void * ensure_lock();
/* Destroy a lock previously returned by create_lock(). */
EXTERNC void   free_lock(void* v_lock);
/* Destroy the ensure_lock() singleton so the next ensure_lock() builds a fresh
   one. PRECONDITION: no other thread may be holding or about to take the lock --
   destroying a lock in use is undefined. Intended for a controlled teardown /
   forced reinitialize, not for concurrent use. */
EXTERNC void   reset_lock();

/* Atomic counter of environments the loader is currently installed into.
   setup_dispatcher() increments it once per environment and registers a CLIPS
   environment cleanup function (which cannot be removed through any public API)
   to decrement it at DestroyEnvironment; teardown_dispatcher() refuses while the
   count is non-zero. Backed by a C++11 atomic. */
EXTERNC long   loader_env_register(void);    /* ++count, returns the new value */
EXTERNC long   loader_env_unregister(void);  /* --count, returns the new value */
EXTERNC long   loader_env_active(void);      /* current count */
EXTERNC void   lock_read(void* v_lock);
EXTERNC void   lock_write(void* v_lock);
EXTERNC void   unlock_read(void* v_lock);
EXTERNC void   unlock_write(void* v_lock);


#endif