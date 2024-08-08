#ifndef OS_SYNCHRONIZATIONEVENT_H
#define OS_SYNCHRONIZATIONEVENT_H
#include <revolution/OS.h>

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
