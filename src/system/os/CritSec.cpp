#include "os/CritSec.h"
#include "utl/PoolAlloc.h"

void CriticalSection::Abandon(){
    while(1 < mEntryCount) Exit();
    Exit();
}

CriticalSection::CriticalSection(){
    mEntryCount = 0;
    OSInitMutex(&mCritSec);
}

CriticalSection::~CriticalSection(){
    // _PoolFree(0x1C, FastPool, this);
}

void CriticalSection::Enter(){
    OSLockMutex(&mCritSec);
    mEntryCount++;
}

void CriticalSection::Exit(){
    mEntryCount--;
    OSUnlockMutex(&mCritSec);
}
