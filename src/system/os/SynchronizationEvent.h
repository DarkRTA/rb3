#ifndef OS_SYNCHRONIZATIONEVENT_H
#define OS_SYNCHRONIZATIONEVENT_H
#include <revolution/os.h>

class SynchronizationEvent {
public:
    OSMutex mMutex;
    OSCond mCond;
    bool mSignal;

    SynchronizationEvent();
    ~SynchronizationEvent();
    void Set();
    bool Wait(int);
};

#endif
