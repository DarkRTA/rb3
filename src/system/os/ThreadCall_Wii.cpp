#include "ThreadCall.h"
#include "os/Debug.h"

#include <revolution/OS.h>
#include <memory>

OSThread *gMainThreadID;

namespace {
    u8 *gThreadStack;
    OSThread gThread;
    ThreadCallData gData[12];
    uint gCurCall;
    uint gFreeCall;

    bool gCallDone;
    bool gTerminate;

    void *MyThreadFunc(void *arg);
}

void ThreadCallPreInit() {
    gMainThreadID = OSGetCurrentThread();
}

void ThreadCallInit() {
    gCurCall = 0;
    gFreeCall = 0;

    memset(&gData, 0, 0xF0);

    gThreadStack = (u8 *)_MemAlloc(0x10000, 0x20);

    OSCreateThread(&gThread, MyThreadFunc, NULL, gThreadStack + 0x10000, 0x10000, 0xC, 0);
    gThread.specific[0] = (void *)"ThreadCallInit";
    OSResumeThread(&gThread);
}

void ThreadCallTerminate() {
    gTerminate = true;
    if (!gThreadStack) {
        return;
    }

    OSResumeThread(&gThread);
}

void ThreadCall(int (*Func)(void), void (*Callback)(int)) {
    ThreadCallData &data = gData[gFreeCall];
    MILO_ASSERT(data.mType == kTCDT_None, 85);

    data.mType = kTCDT_Func;

    data.mFunc = Func;
    data.mCallback = Callback;
    data.mClass = NULL;

    // Not sure about this.
    int ivar3 = gFreeCall + 1;
    uint ivar1 = ivar3 / 0xC;
    gFreeCall = ivar3 - ivar1 * 0xC;

    OSResumeThread(&gThread);
}

void ThreadCall(ThreadCallback *CB) {
    ThreadCallData &data = gData[gFreeCall];
    MILO_ASSERT(data.mType == kTCDT_None, 101);

    data.mType = kTCDT_Class;

    data.mFunc = NULL;
    data.mCallback = NULL;
    data.mClass = CB;

    // Not sure about this.
    int ivar3 = gFreeCall + 1;
    uint ivar1 = ivar3 / 0xC;
    gFreeCall = ivar3 - ivar1 * 0xC;

    OSResumeThread(&gThread);
}

void ThreadCallPoll() {}

namespace {
    void *MyThreadFunc(void *arg) {
        while (!gTerminate) {
            ThreadCallData &data = gData[gCurCall];
            MILO_ASSERT(data.mType != kTCDT_None, 165);

            switch (data.mType) {
            case kTCDT_Func:
                data.mArg = data.mFunc();
                gCallDone = true;
                break;
            case kTCDT_Class:
                data.mClass->ThreadStart();
                gCallDone = true;
                break;
            default:
            case kTCDT_None:
                MILO_ASSERT(false, 180);
            }

            OSSuspendThread(&gThread);
        }

        return 0;
    }
}
