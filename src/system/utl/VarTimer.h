#ifndef UTL_VARTIMER_H
#define UTL_VARTIMER_H
#include "os/Timer.h"

class VarTimer {
public:
    Timer mRawTimer; // 0x0
    float mAccumMs; // 0x30
    float mSpeed; // 0x34

    VarTimer();
    void Start();
    void Stop();
    void Reset(float);
    void SetSpeed(float);
    float Ms();
    float GetSpeed() const { return mSpeed; }
};

#endif
