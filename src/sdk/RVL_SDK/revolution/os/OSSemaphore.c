#include "OSSemaphore.h"
#include "revolution/os/OSInterrupt.h"
#include "revolution/os/OSThread.h"

void OSInitSemaphore(OSSemaphore *sema, s32 active_signals) {
    BOOL status = OSDisableInterrupts();
    OSInitThreadQueue(&sema->threadQueue);
    sema->activeSignals = active_signals;
    OSRestoreInterrupts(status);
}

s32 OSWaitSemaphore(OSSemaphore* sema) {
    BOOL status = OSDisableInterrupts();
    s32 ret;
    while ((ret = sema->activeSignals) <= 0) {
        OSSleepThread(&sema->threadQueue);
    }
    sema->activeSignals--;
    OSRestoreInterrupts(status);
    return ret;
}

s32 OSSignalSemaphore(OSSemaphore* sema) {
    BOOL status = OSDisableInterrupts();
    s32 ret;
    ret = sema->activeSignals++;
    OSWakeupThread(&sema->threadQueue);
    OSRestoreInterrupts(status);
    return ret;
}
