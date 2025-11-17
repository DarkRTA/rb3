#ifndef UTL_MEMMGR_H
#define UTL_MEMMGR_H
#include "os/CritSec.h"
#include <stddef.h>
#include <new>
#include "utl/PoolAlloc.h"

extern CriticalSection *gMemLock;

class MemDoTempAllocations {
public:
    MemDoTempAllocations(bool, bool);
    ~MemDoTempAllocations();

    int mOld; // 0x0
};

class MemHandle {
public:
    MemHandle(void *);
    void *Lock();
    void Unlock();
};

MemHandle *_MemAllocH(int);
void MemFreeH(MemHandle *);

void *operator new(size_t size) throw(std::bad_alloc);
void operator delete(void *) throw();
void *operator new[](size_t size) throw(std::bad_alloc);
void operator delete[](void *) throw();

void *_MemAlloc(int, int);
void *_MemAllocTemp(int, int);
void *_MemRealloc(void *, int, int);
void _MemFree(void *);

void *_MemOrPoolAlloc(int, PoolType);
void _MemOrPoolFree(int, PoolType, void *);
void *_MemOrPoolAllocSTL(int, PoolType);
void _MemOrPoolFreeSTL(int, PoolType, void *);

#define kNoHeap -3
#define kSystemHeap -1

int GetCurrentHeapNum();
int MemFindHeap(const char *);
void MemPushHeap(int);
void MemPopHeap();
int MemNumHeaps();
int MemFindAddrHeap(void *);
const char *MemHeapName(int);
void MemFreeBlockStats(int, int &, int &, int &, int &);
void *MemTruncate(void *, int);
void MemSetAllowTemp(char *, bool);

class MemTempHeap {
public:
    MemTempHeap(int x) { MemPushHeap(x); }
    ~MemTempHeap() { MemPopHeap(); }
};

#define NEW_OVERLOAD                                                                     \
    void *operator new(size_t t) { return _MemAlloc(t, 0); }                             \
    void *operator new(size_t, void *place) { return place; }

#define NEW_ARRAY_OVERLOAD                                                               \
    void *operator new[](size_t t) { return _MemAlloc(t, 0); }                           \
    void *operator new[](size_t, void *place) { return place; }

#define DELETE_OVERLOAD                                                                  \
    void operator delete(void *v) { _MemFree(v); }

#define DELETE_ARRAY_OVERLOAD                                                            \
    void operator delete[](void *v) { _MemFree(v); }

#endif
