#ifndef UTL_MEMMGR_H
#define UTL_MEMMGR_H
#include "utl/PoolAlloc.h"

void* operator new(unsigned long);
void operator delete(void*);
void* operator new[](unsigned long);
void operator delete[](void*);

void* _MemAlloc(int, int);
void _MemFree(void*);

void* _MemOrPoolAlloc(int, PoolType);
void _MemOrPoolFree(int, PoolType, void*);
void* _MemOrPoolAllocSTL(int, PoolType);
void _MemOrPoolFreeSTL(int, PoolType, void*);

#endif
