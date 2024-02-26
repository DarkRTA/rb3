#ifndef OS_CRITSEC_H
#define OS_CRITSEC_H
#include <revolution/os.h>

class CriticalSection {
public:
    int mEntryCount;
    OSMutex mCritSec;

    CriticalSection();
    ~CriticalSection();
    void Enter();
    void Exit();
    void Abandon();
};

#endif
