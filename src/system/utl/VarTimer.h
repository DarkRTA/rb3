#ifndef UTL_VARTIMER_H
#define UTL_VARTIMER_H
#include "os/Timer.h"

class VarTimer {
public:
    Timer mRawTimer;
    float mAccumMs;
    float mSpeed;

    VarTimer();
    void Start();
    void Stop();
    void Reset(float);
    void SetSpeed(float);
    float Ms();

};

#endif
