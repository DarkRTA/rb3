#include "revolution/os/OS.h"
#include <revolution/AX.h>

const char* __AXVersion = "<< RVL_SDK - AX \trelease build: Dec 11 2009 15:55:44 (0x4302_145) >>";
static BOOL __init = FALSE;

void AXInit(void) {
    if (__init == FALSE) {
        OSRegisterVersion(__AXVersion);
        __AXAllocInit();
        __AXVPBInit();
        __AXSPBInit();
        __AXAuxInit();
        __AXClInit();
        __AXOutInit(0);
        __init = TRUE;
    }
}

void AXInitSpecifyMem(u32 a, u32 b) {
    if (__init == FALSE) {
        OSRegisterVersion(__AXVersion);
        __AXAllocInit();
        __AXVPBInitSpecifyMem(a, b);
        __AXSPBInit();
        __AXAuxInit();
        __AXClInit();
        __AXOutInit(0);
        __init = TRUE;
    }
}

void AXQuit(void) {
    if (__init != FALSE) {
        __AXOutQuit();
        __AXAllocQuit();
        __AXVPBQuit();
        __AXSPBQuit();
        __AXAuxQuit();
        __AXClQuit();
        __init = FALSE;
    }
}

BOOL AXIsInit(void) { return __init; }
