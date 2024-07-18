#ifndef UTL_MEMMGR_H
#define UTL_MEMMGR_H
#include <stddef.h>
#include "utl/PoolAlloc.h"

class MemDoTempAllocations {
public:
    MemDoTempAllocations(bool, bool);
    ~MemDoTempAllocations();
};

class MemHandle {
public:
    MemHandle(void*);
    void Lock();
    void Unlock();
};

void MemFreeH(MemHandle*);

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
int MemNumHeaps();
int MemFindAddrHeap(void*);
const char* MemHeapName(int);
void MemFreeBlockStats(int, int&, int&, int&, int&);

#define NEW_OVERLOAD \
    void* operator new(size_t t) {return _MemAlloc(t, 0);}

#define DELETE_OVERLOAD \
    void operator delete(void* v){ _MemFree(v); }

#endif
