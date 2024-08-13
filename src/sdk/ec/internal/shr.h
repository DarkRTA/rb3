#ifndef EC_INTERNAL_SHR_H
#define EC_INTERNAL_SHR_H

#include "types.h"
#include <revolution/OS.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int _SHRBool;

typedef struct _SHRMutex {
    OSMutex osMutex;
    _SHRBool _18;
    OSThread* thread;
    _SHRBool lockCount;
} _SHRMutex;

typedef struct _SHRMessageQueue {
    OSMessageQueue osQueue;
} _SHRMessageQueue;

typedef struct _SHRThread {
    OSThread osThread;
} _SHRThread;

typedef struct _SHRThreadAttr {
    void* stack;
    u32 stackSize;
    s32 priority;
    _SHRBool start;
} _SHRThreadAttr;

int _SHR_mutex_init(_SHRMutex* mutex, _SHRBool a, int b, _SHRBool lock);
int _SHR_mutex_lock(_SHRMutex* mutex);
int _SHR_mutex_unlock(_SHRMutex* mutex);
int _SHR_mutex_destroy(_SHRMutex* mutex);

int _SHR_message_queue_init(_SHRMessageQueue* queue, OSMessage* buffer, s32 capacity);
int _SHR_message_send(_SHRMessageQueue* queue, OSMessage message, u32 flags);
int _SHR_message_receive(_SHRMessageQueue* queue, OSMessage* message, u32 flags);

int _SHR_thread_create(_SHRThread* thread, _SHRThreadAttr* attr, OSThreadFunc func, void* context);
int _SHR_thread_join(_SHRThread* thread, void* context);
int _SHR_thread_sleep(s64 ms);

s64 _SHR_tick_get(void);
s64 _SHR_ticks_to_milliseconds(u64 ticks);

#ifdef __cplusplus
}
#endif

#endif
