#ifndef RVL_SDK_OS_SEMAPHORE_H
#define RVL_SDK_OS_SEMAPHORE_H

#include "revolution/os/OSThread.h"
#include "types.h"

typedef struct OSSemaphore {
    vs32 activeSignals; /* 0x0 */
    OSThreadQueue threadQueue; /* 0x4 */
} OSSemaphore;

void OSInitSemaphore(OSSemaphore* sema, s32 active_signals);
s32 OSWaitSemaphore(OSSemaphore* sema);
s32 OSSignalSemaphore(OSSemaphore* sema);

#endif // RVL_SDK_OS_SEMAPHORE_H