#include <revolution/os/OSArena.h>
#include <revolution/os/OSExec.h>
#include <revolution/os/OSInterrupt.h>
#include "types.h"

void* SaveStart = NULL;
void* SaveEnd = NULL;

void __OSReboot(u32 a, u32 b) {
    OSDisableInterrupts();
    OSSetArenaLo((void*)0x81280000);
    OSSetArenaHi((void*)0x812F0000);
    u32 x = 0;
    __OSNextPartitionType = *(void**)0x80003194;
    __OSBootDol(b, a | 0x80000000, &x);
}

void OSGetSaveRegion(uint* s, uint* e) {
    *s = (uint)SaveStart;
    *e = (uint)SaveEnd;
}
