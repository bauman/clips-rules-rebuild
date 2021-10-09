#ifndef LOCKER_H
#define LOCKER_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif


EXTERNC void * create_lock();
EXTERNC void   lock_read(void* v_lock);
EXTERNC void   lock_write(void* v_lock);
EXTERNC void   unlock_read(void* v_lock);
EXTERNC void   unlock_write(void* v_lock);


#endif