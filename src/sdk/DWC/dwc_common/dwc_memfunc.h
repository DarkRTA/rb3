#pragma once
#include <types.h>

typedef void *(*DWCAllocFunc)(int, size_t);
typedef void *(*DWCAllocExFunc)(int, size_t, int);
typedef void (*DWCFreeFunc)(int, void*, int);

void DWCi_SetMemFunc(DWCAllocExFunc alloc, DWCFreeFunc free);
void* DWC_Alloc(int, size_t);
void* DWC_AllocEx(int, size_t, int);
void DWC_Free(int, void*, int);
