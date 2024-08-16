#ifndef OS_TIMER_H
#define OS_TIMER_H
#include "utl/Symbol.h"
#include "obj/Data.h"
#include "os/OSFuncs.h"
#include <vector>
#include "decomp.h"

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
    static double sDoubleCycles2Ms;

    static Timer sSlowFrameTimer;
    static float sSlowFrameWaiver;
    static const char* sSlowFrameReason;

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
    long long Stop() {
        long long cycles = 0;

        mRunning--; // Must be outside the if to match
        if (mRunning == 0) {
            TIMER_GET_CYCLES(cycle);
            cycles = cycle - mStart;
            mCycles += cycles;
        }

        return cycles;
    }

    void Pause() {
        if (mRunning <= 0) {
            return;
        }

        mRunning = -mRunning;

        TIMER_GET_CYCLES(cycle);
        mCycles += cycle - mStart;
    }

    void Resume() {
        if (mRunning >= 0) {
            return;
        }

        mRunning = -mRunning;

        TIMER_GET_CYCLES(cycle);
        mStart = cycle;
    }

    bool Running() {
        return mRunning > 0;
    }

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

#define MAX_TOP_VALS 128

class TimerStats {
public:
    TimerStats(DataArray*);

    void CollectStats(float, bool, int);
    void PrintPctile(float);
    void Dump(const char*, int);
    void Clear();

    int mCount; // 0x0
    float mAvgMs; // 0x4
    float mStdDevMs; // 0x8
    float mMaxMs; // 0xc
    int mNumOverBudget; // 0x10
    float mBudget; // 0x14
    bool mCritical; // 0x18
    int mNumCritOverBudget; // 0x1c
    float mAvgMsInCrit; // 0x20
    float mTopValues[MAX_TOP_VALS]; // 0x24
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

    ~AutoTimer() { if (mTimer) mTimer->Stop(); }

    Timer* mTimer; // 0x0
    float unk_0x4;
    StupidAutoTimerFunc unk_0x8; // ???
    void* unk_0xC;

    static int sCritFrameCount;
    static std::vector<std::pair<Timer, TimerStats> > sTimers;

    static Timer* GetTimer(Symbol);
};

#ifdef MILO_DEBUG
#define START_AUTO_TIMER(name) \
    static Timer* _t = AutoTimer::GetTimer(name); \
    AutoTimer t(_t, 50.0f, NULL, NULL)
#else
#define START_AUTO_TIMER(name) (void)0
#endif

#define TIMER_ACTION(name, action) { \
    START_AUTO_TIMER(name); \
    action; \
}

class AutoSlowFrame {
public:
    static int sDepth;

    AutoSlowFrame(const char* reason) {
        if (!MainThread()) {
            return;
        }

        sDepth++;
        Timer::sSlowFrameReason = reason;
        Timer::sSlowFrameWaiver += 10.0f;
        Timer::sSlowFrameTimer.Start();
    }

    ~AutoSlowFrame() {
        if (!MainThread()) {
            return;
        }

        sDepth--;
        Timer::sSlowFrameTimer.Stop();
    }
};

#endif
