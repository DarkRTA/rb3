
#include "os/CritSec.h"
#include "os/Debug.h"
#include "revolution/mem/mem_expHeap.h"
#include "revolution/os/OSArena.h"
#include "revolution/os/OSError.h"
#include "revolution/os/OSThread.h"
#include "utl/MemMgr.h"

bool gHeapInitialized = false;
MEMiHeapHead *gMEM1Heap = NULL;
MEMiHeapHead *gMEM2Heap = NULL;

void InitDefaultHeap() {
    CritSecTracker cst(gMemLock);
    if (!gHeapInitialized) {
        OSReport("Init: OS initialization\n");
        OSInit();
        void *mem1lo = (void *)(uint(OSGetMEM1ArenaLo()) + 31 & ~31);
        void *mem1hi = (void *)(uint(OSGetMEM1ArenaHi()) & ~31);
        void *mem2lo = (void *)(uint(OSGetMEM2ArenaLo()) + 31 & ~31);
        void *mem2hi = (void *)(uint(OSGetMEM2ArenaHi()) & ~31);

        OSReport(
            "Init: heap initialization\n\tarena1: %p - %p (%d)\n\tarena2: %p - %p (%d)\n",
            mem1lo,
            mem1hi,
            uint(mem1hi) - uint(mem1lo),
            mem2lo,
            mem2hi,
            uint(mem2hi) - uint(mem2lo)
        );
        OSThread *thread = OSGetCurrentThread();
        if (thread != NULL) {
            OSReport(
                "\tstack:  %p - %p (%d)\n",
                thread->stackEnd,
                thread->stackBase,
                uint(thread->stackEnd) - uint(thread->stackBase)
            );
        }
        gMEM1Heap = MEMCreateExpHeapEx(mem1lo, uint(mem1hi) - uint(mem1lo), 0);
        OSSetMEM1ArenaLo(mem1hi);
        gMEM2Heap = MEMCreateExpHeapEx(mem2lo, uint(mem2hi) - uint(mem2lo), 0);
        OSSetMEM2ArenaLo(mem2hi);
        gHeapInitialized = true;
    }
}

extern "C" void *__sys_alloc(int siz) { return _MemAlloc(siz, 0); }
extern "C" void __sys_free(void *buf) { _MemFree(buf); }

extern "C" void *WiiAllocHeapAlign(int *size, int membank, u32 align) {
    if (!gHeapInitialized)
        InitDefaultHeap();
    MILO_ASSERT_RANGE(membank, 0, 2, 92);
    MEMiHeapHead *heap = membank == 0 ? gMEM1Heap : gMEM2Heap;
    CritSecTracker cst(gMemLock);
    uint max = MEMGetAllocatableSizeForExpHeapEx(heap, 4);
    if (*size > max) {
        *size = max & ~31;
    }
    MILO_ASSERT(*size > 0, 102);
    return MEMAllocFromExpHeapEx(heap, *size, align);
}

extern "C" void *WiiMalloc(int size) {
    if (!gHeapInitialized)
        InitDefaultHeap();
    CritSecTracker cst(gMemLock);
    return MEMAllocFromExpHeapEx(gMEM2Heap, size, 32);
}

extern "C" void WiiFree(void *buf) {
    MEMiHeapHead *heap = (uint)buf < 0x90000000 == 0 ? gMEM2Heap : gMEM1Heap;
    CritSecTracker cst(gMemLock);
    MEMFreeToExpHeap(heap, buf);
}
