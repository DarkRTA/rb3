#include "dwc_memfunc.h"
#include "dwc_report.h"

static DWCFreeFunc s_free = NULL;
static DWCAllocExFunc s_alloc = NULL;

void DWCi_SetMemFunc(DWCAllocExFunc alloc, DWCFreeFunc free) {
    s_alloc = alloc;
    s_free = free;
}

void* DWC_Alloc(int id, size_t size) {
    void* mem = (*s_alloc)(id, size + 0x20, 0x20);
    void* mem2;
    if (mem == NULL) {
        DWC_Printf(
            8, 
            "Failed to alloc memory. Original requested size: %d, Required size: %d, align: %d.\n", 
            size, 
            size + 0x20, 
            0x20
                );
        mem2 = NULL;
    } else {
        mem2 = (void*)((int)mem + 0x20);
        *(u32*)mem = 0x4457434d;
        ((u32*)mem)[1] = size;
    }
    return mem2;
}

void* DWC_AllocEx(int id, size_t size, int alignment) {
    void* mem = (*s_alloc)(id, size + 0x20, alignment);
    void* mem2;
    if (mem == NULL) {
        DWC_Printf(
            8, 
            "Failed to alloc memory. Original requested size: %d, Required size: %d, align: %d.\n", 
            size, 
            size + 0x20, 
            alignment
                );
        return NULL;
    } else {
        *(u32*)mem = 0x4457434d; // DWCM
        ((u32*)mem)[1] = size;
        mem = (void*)((int)mem + 0x20);
    }
    return mem;
}

void DWC_Free(int id, void* mem, int alignment) {
    if (mem != NULL) {
        (*s_free)(id, (void*)((int)mem - 0x20), alignment);
    }
}
