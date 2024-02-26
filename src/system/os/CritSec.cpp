#include "os/CritSec.h"


void CriticalSection::Abandon(){
    while(1 < mEntryCount) Exit();
    Exit();
}

CriticalSection::CriticalSection(){
    mEntryCount = 0;
    OSInitMutex(&mCritSec);
}

CriticalSection::~CriticalSection(){
    
}

void CriticalSection::Enter(){
    OSLockMutex(&mCritSec);
    mEntryCount++;
}

void CriticalSection::Exit(){
    mEntryCount--;
    OSUnlockMutex(&mCritSec);
}
