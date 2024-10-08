#include "revolution/axfx/AXFXHooks.h"
#include "revolution/os/OSAlloc.h"
#include <revolution/AXFX.h>

void* __AXFXAllocFunction(u32 size) {
    return OSAllocFromHeap(__OSCurrHeap, size);
}

void __AXFXFreeFunction(void *data) {
    OSFreeToHeap(__OSCurrHeap, data);
}

void AXFXSetHooks(AXFXAlloc alloc, AXFXFree free) {
    __AXFXAlloc = alloc;
    __AXFXFree = free;
}

void AXFXGetHooks(AXFXAlloc* alloc, AXFXFree* free) {
    *alloc = __AXFXAlloc;
    *free = __AXFXFree;
}
