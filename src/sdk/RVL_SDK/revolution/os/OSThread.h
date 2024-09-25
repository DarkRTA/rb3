#ifndef RVL_SDK_OS_THREAD_H
#define RVL_SDK_OS_THREAD_H

#include "revolution/os/OSContext.h"
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_PRIORITY_MIN 0
#define OS_PRIORITY_MAX 31

#define OS_THREAD_STACK_MAGIC 0xDEADBABE

typedef enum {
    OS_THREAD_STATE_EXITED = 0,
    OS_THREAD_STATE_READY = 1,
    OS_THREAD_STATE_RUNNING = 2,
    OS_THREAD_STATE_SLEEPING = 4,
    OS_THREAD_STATE_MORIBUND = 8
} OSThreadState;

typedef u16 OSThreadFlags;
enum OSThreadFlags_et {
    OS_THREAD_NO_FLAGS = 0,
    OS_THREAD_DETACHED = (1 << 0),
};

typedef struct OSThreadLink {
    struct OSThread *next;  // size 0x04, offset 0x00
    struct OSThread *prev;  // size 0x04, offset 0x04
} OSThreadLink; // size 0x08

typedef struct OSThreadQueue {
    struct OSThread *head; // at 0x0
    struct OSThread *tail; // at 0x4
} OSThreadQueue;

typedef struct OSMutexLink
{
    struct OSMutex *next;  // size 0x04, offset 0x00
    struct OSMutex *prev;  // size 0x04, offset 0x04
} OSMutexLink; // size 0x08

typedef struct OSMutexQueue {
    struct OSMutex *head;  // at 0x0
    struct OSMutex *tail;  // at 0x4
} OSMutexQueue;

typedef struct OSThread {
    OSContext       context;        // size 0x2c8, offset 0x000
    u16             state;          // size 0x002, offset 0x2c8
    u16             attr;           // size 0x002, offset 0x2ca
    s32             suspend;        // size 0x004, offset 0x2cc
    s32             priority;       // size 0x004, offset 0x2d0
    s32             base;           // size 0x004, offset 0x2d4
    void            *val;           // size 0x004, offset 0x2d8
    OSThreadQueue   *queue;         // size 0x004, offset 0x2dc
    OSThreadLink    link;           // size 0x008, offset 0x2e0
    OSThreadQueue   queueJoin;      // size 0x008, offset 0x2e8
    struct OSMutex  *mutex;         // size 0x004, offset 0x2f0
    OSMutexQueue    queueMutex;     // size 0x008, offset 0x2f4
    OSThreadLink    linkActive;     // size 0x008, offset 0x2fc
    u8              *stackBase;     // size 0x004, offset 0x304
    u32             *stackEnd;      // size 0x004, offset 0x308
    s32             error;          // size 0x004, offset 0x30c
    void            *specific[2];   // size 0x008, offset 0x310
} OSThread; // size 0x318

typedef struct OSMutex {
    OSThreadQueue   queue;    // size 0x08, offset 0x00
    OSThread        *thread;  // size 0x04, offset 0x08
    s32             count;    // size 0x04, offset 0x0c
    OSMutexLink     link;     // size 0x08, offset 0x10
} OSMutex; // size 0x18

typedef struct OSCond {
    OSThreadQueue queue;
} OSCond;

typedef void (*OSSwitchThreadCallback)(OSThread* currThread,
                                       OSThread* newThread);
typedef void* (*OSThreadFunc)(void* arg);

OSSwitchThreadCallback
OSSetSwitchThreadCallback(OSSwitchThreadCallback callback);
void __OSThreadInit(void);
void OSSetCurrentThread(OSThread* thread);
void OSInitMutexQueue(OSMutexQueue* queue);
void OSInitThreadQueue(OSThreadQueue* queue);
OSThread* OSGetCurrentThread(void);
BOOL OSIsThreadTerminated(OSThread* thread);
s32 OSDisableScheduler(void);
s32 OSEnableScheduler(void);
s32 __OSGetEffectivePriority(OSThread* thread);
void __OSPromoteThread(OSThread* thread, s32 prio);
void __OSReschedule(void);
void OSYieldThread(void);
BOOL OSCreateThread(OSThread* thread, OSThreadFunc func, void* funcArg,
                    void* stackBegin, u32 stackSize, s32 prio, u16 flags);
void OSExitThread(OSThread* thread);
void OSCancelThread(OSThread* thread);
BOOL OSJoinThread(OSThread* thread, void* val);
void OSDetachThread(OSThread* thread);
s32 OSResumeThread(OSThread* thread);
s32 OSSuspendThread(OSThread* thread);
void OSSleepThread(OSThreadQueue* queue);
void OSWakeupThread(OSThreadQueue* queue);
BOOL OSSetThreadPriority(OSThread* thread, s32 prio);
s32 OSGetThreadPriority(OSThread* thread);
void OSClearStack(u8 val);
void OSSleepTicks(s64 ticks);

void OSInitMutex(OSMutex* mutex);
void OSLockMutex(OSMutex* mutex);
void OSUnlockMutex(OSMutex* mutex);
void __OSUnlockAllMutex(OSThread* thread);
BOOL OSTryLockMutex(OSMutex* mutex);

void OSInitCond(OSCond* cond);
void OSWaitCond(OSCond* cond, OSMutex* mutex);
void OSSignalCond(OSCond* cond);

#ifdef __cplusplus
}
#endif
#endif
