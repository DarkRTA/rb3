#ifndef OS_TIMER_H
#define OS_TIMER_H
#include "utl/Symbol.h"
#include "obj/Data.h"

#define ASM_BLOCK asm
#define TIMER_GET_CYCLES(name) \
    register int name; \
    ASM_BLOCK(mftb name)

class Timer {
public:
    unsigned int mStart; // 0x00
    // padding, 0x04
    long long mCycles; // 0x08
    float mLastMs; // 0x10
    float mWorstMs; // 0x14
    int mWorstMsFrame; // 0x18
    int mFrame; // 0x1c
    Symbol mName; // 0x20
    int mRunning; // 0x24
    float mBudget; // 0x28
    bool mDraw; // 0x2c

    // Seems these fields no longer exist
    // int mCount; // 0x30
    // int mLastCount; // 0x34

    static float sLowCycles2Ms;
    static float sHighCycles2Ms;

    static void Init();
    static void Sleep(int);

    static float CyclesToMs(long long cycles) {
        unsigned long lowCycles = cycles;
        long highCycles = cycles >> 32;
        return (lowCycles * sLowCycles2Ms) + (highCycles * sHighCycles2Ms);
    }

    Timer();
    Timer(DataArray*);

    void Start() {
        if (mRunning++ != 0)
            return;
    
        TIMER_GET_CYCLES(cycle);
        mStart = cycle;
    }

    // Function addresses from retail, not sure what these do yet
    long long fn_800A8898() {
        long long cycles = 0;
    
        mRunning--; // Must be outside the if to match
        if (mRunning == 0) {
            TIMER_GET_CYCLES(cycle);
            cycles = cycle - mStart;
            mCycles += cycles;
        }
    
        return cycles;
    }

    void fn_80306184() {
        if (mRunning >= 0) {
            return;
        }
    
        mRunning = -mRunning;
    
        TIMER_GET_CYCLES(cycle);
        mStart = cycle;
    }

    void fn_803061A4() {
        if (mRunning <= 0) {
            return;
        }
    
        mRunning = -mRunning;
    
        TIMER_GET_CYCLES(cycle);
        mCycles += cycle - mStart;
    }

    bool Running() { return mRunning > 0; }

    void Split() {
        if (mRunning <= 0)
            return;
    
        TIMER_GET_CYCLES(cycle);

        mCycles += cycle - mStart;
        mStart = cycle;
    }

    float SplitMs() {
        Split();
        return Ms();
    }

    void Reset();
    void Restart();

    float Ms() { return CyclesToMs(mCycles); }
    void SetLastMs(float ms);
};

#endif
