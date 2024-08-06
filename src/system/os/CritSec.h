#ifndef OS_CRITSEC_H
#define OS_CRITSEC_H
#include <revolution/OS.h>
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

    NEW_POOL_OVERLOAD(CriticalSection)
    DELETE_POOL_OVERLOAD(CriticalSection)
};

class CritSecTracker {
public:
    CriticalSection* mCritSec;

    CritSecTracker(CriticalSection* section) {
        mCritSec = section;
        if (section != 0) {
            section->Enter();
        }
    }

    ~CritSecTracker() {
        if (mCritSec != 0) {
            mCritSec->Exit();
        }
    }
};

#endif
