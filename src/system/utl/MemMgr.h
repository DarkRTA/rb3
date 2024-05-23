#ifndef UTL_MEMMGR_H
#define UTL_MEMMGR_H
#include <stddef.h>
#include "utl/PoolAlloc.h"

class MemDoTempAllocations {
public:
    MemDoTempAllocations(bool, bool);
    ~MemDoTempAllocations();
};

void* operator new(size_t) throw();
void operator delete(void*) throw();
void* operator new[](size_t) throw();
void operator delete[](void*) throw();

void* _MemAlloc(int, int);
void* _MemAllocTemp(int, int);
void* _MemRealloc(void*, int, int);
void _MemFree(void*);

void* _MemOrPoolAlloc(int, PoolType);
void _MemOrPoolFree(int, PoolType, void*);
void* _MemOrPoolAllocSTL(int, PoolType);
void _MemOrPoolFreeSTL(int, PoolType, void*);

int GetCurrentHeapNum();
int MemFindHeap(const char*);
void MemPushHeap(int);
void MemPopHeap();

int MemFindAddrHeap(void*);
const char* MemHeapName(int);

#endif
