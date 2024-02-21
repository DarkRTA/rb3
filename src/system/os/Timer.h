#ifndef OS_TIMER_H
#define OS_TIMER_H
#include "utl/Symbol.h"
#include "obj/Data.h"

class Timer {
public:
    unsigned int mStart;
    long long mCycles;
    float mLastMs;
    float mWorstMs;
    int mWorstMsFrame;
    int mFrame;
    Symbol mName;
    int mRunning;
    float mBudget;
    bool mDraw;
    int mCount;
    int mLastCount;

    Timer();
    Timer(DataArray*);
    void Restart();
};

#endif
