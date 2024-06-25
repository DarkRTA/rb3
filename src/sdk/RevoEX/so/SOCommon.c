#include "revolution/os/OSInterrupt.h"
#include "revolution/rvl/so.h"
#include "revolution/OS.h"

unsigned char soState;
int soError, soRegistered;
SOSysWork soWork;

int SOiPrepare(const char *c, s32 *i) {
    /*BOOL ints = OSDisableInterrupts();



    OSRestoreInterrupts(ints);*/
    int result = SO_OK;
    int enabled = OSDisableInterrupts();
    SOSysWork* sw;

    switch (soState) {
    case SO_INTERNAL_STATE_TERMINATED:
        result = SO_ENETRESET;
        break;
    case SO_INTERNAL_STATE_READY:
    default:
        result = SO_EINVAL;
        break;
    case SO_INTERNAL_STATE_ACTIVE:
        sw = &soWork;
        if (sw->rmState < SO_INTERNAL_RM_STATE_OPENED) {
            result = SO_EBUSY;
            break;
        } else if (!OSGetCurrentThread()) {
            result = SO_EFATAL;
            break;
        }
        *i = sw->rmFd;
        break;
    }

    if (result != SO_OK) {
        OSThread *cur = OSGetCurrentThread();
        if (cur)
            cur->error = result;
        else
            soError = result;
    }
    (void)OSRestoreInterrupts(enabled);
    return result;
}

int SOiConclude(const char *funcName, int result) {
    int enabled = OSDisableInterrupts();
    OSThread *cur = OSGetCurrentThread();
    if (cur)
        cur->error = result;
    else
        soError = result;
    (void)OSRestoreInterrupts(enabled);
    return result;
}
