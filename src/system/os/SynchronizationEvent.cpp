#include "os/SynchronizationEvent.h"
#include "os/Debug.h"

SynchronizationEvent::SynchronizationEvent() : mSignal(0) {
    OSInitMutex(&mMutex);
    OSInitCond(&mCond);
}

SynchronizationEvent::~SynchronizationEvent(){
    
}

void SynchronizationEvent::Set(){
    OSLockMutex(&mMutex);
    mSignal = true;
    OSSignalCond(&mCond);
    OSUnlockMutex(&mMutex);
}

bool SynchronizationEvent::Wait(int i){
    bool ret = false;
    OSLockMutex(&mMutex);
    if(!mSignal){
        if(i == 0) goto lol;
        if(i != -1){
            MILO_FAIL("Wii SynchronizationEvent only supports Wait(0) and Wait()");
        }
        OSWaitCond(&mCond, &mMutex);
        MILO_ASSERT(mSignal, 0xC1);
    }
    mSignal = false;
    ret = true;
lol:
    OSUnlockMutex(&mMutex);
    return ret;
}
