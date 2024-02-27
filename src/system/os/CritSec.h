#ifndef OS_CRITSEC_H
#define OS_CRITSEC_H
#include <revolution/os.h>
#include "utl/PoolAlloc.h"

class CriticalSection {
public:
    int mEntryCount;
    OSMutex mCritSec;

    CriticalSection();
    ~CriticalSection();
    void Enter();
    void Exit();
    void Abandon();

    void operator delete(void* v){
        _PoolFree(0x1C, FastPool, v);
    }
};

#endif
