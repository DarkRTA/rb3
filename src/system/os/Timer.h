#ifndef OS_TIMER_H
#define OS_TIMER_H
#include "utl/Symbol.h"
#include "obj/Data.h"

#include "macros.h"

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
    float GetLastMs() { return mLastMs; }
    void SetLastMs(float ms);
};

typedef void (*StupidAutoTimerFunc)(float, void*);

class AutoTimer {
public:

    AutoTimer(Timer* t, float f, StupidAutoTimerFunc s, void* v) {
        mTimer = t; 
        if (!t) return;
        unk_0x4 = f; unk_0x8 = s; unk_0xC = v;
        mTimer->Start(); 
    }

    ~AutoTimer() { if (mTimer) mTimer->fn_800A8898(); }

    Timer* mTimer; // 0x0
    float unk_0x4;
    StupidAutoTimerFunc unk_0x8; // ???
    void* unk_0xC;

    static Timer* GetTimer(Symbol);
};

#define TIMER_THING(name, func) {\
    static Timer* _t = AutoTimer::GetTimer(name); \
    AutoTimer t(_t, 50.0f, NULL, NULL); \
    func; \
    }

#define TIMER_THING_NODEL(name, func) \
    static Timer* _t = AutoTimer::GetTimer(name); \
    AutoTimer t(_t, 50.0f, NULL, NULL); \
    func; 
    

#endif
