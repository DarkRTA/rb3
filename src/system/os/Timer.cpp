#include "os/Timer.h"

#include "os/Debug.h"
#include "math/MathFuncs.h"
#include "revolution/os/OSTime.h"
#include <list>

std::vector<std::pair<Timer, TimerStats> > AutoTimer::sTimers;
int AutoTimer::sCritFrameCount;

float Timer::sLowCycles2Ms;
float Timer::sHighCycles2Ms;
double Timer::sDoubleCycles2Ms;

Timer Timer::sSlowFrameTimer;
float Timer::sSlowFrameWaiver;
const char* Timer::sSlowFrameReason;

static DataArray* tempArray = new DataArray(1);
static std::list<Symbol> sConditionalTimersEnabled;

Timer::Timer() : mStart(0), mCycles(0), mLastMs(0.0f), mWorstMs(0.0f), mWorstMsFrame(0), mFrame(0), mName(), mRunning(0), mBudget(0.0f), mDraw(true) {

}

Timer::Timer(DataArray* config) : mStart(0), mCycles(0), mLastMs(0.0f), mWorstMs(0.0f), mWorstMsFrame(0), mFrame(0), mName(config->Sym(0)), mRunning(0), mBudget(0.0f), mDraw(true) {
    config->FindData("budget", mBudget, false);
    config->FindData("draw", mDraw, false);
}

void Timer::Sleep(int ms) {
    if (ms == 0) {
        OSYieldThread();
        return;
    }

    OSSleepTicks(OSMillisecondsToTicks((long long)ms));
}

void Timer::Reset() {
    SetLastMs(Ms());
    mCycles = 0;
    mRunning = 0;
    // very annoying regswap here
    if (++mFrame > mWorstMsFrame + 60.0f) {
        mWorstMsFrame = 0;
        mWorstMs = 0.0;
    }
}

void Timer::Restart() {
    TIMER_GET_CYCLES(cycle);
    if (mRunning > 0) {
        mCycles += cycle - mStart;
    }

    Reset();

    mRunning = 1;
    mStart = cycle;
}

void Timer::SetLastMs(float ms) {
    mLastMs = ms;
    ms = (double)ms; // ??
    if (ms >= mWorstMs) {
        mWorstMs = ms;
        mWorstMsFrame = mFrame;
    }
}

TimerStats::TimerStats(DataArray* cfg) : mCount(0), mAvgMs(0.0f), mStdDevMs(0.0f), mMaxMs(0.0f), mNumOverBudget(0), mBudget(0.0f), mCritical(0), mNumCritOverBudget(0), mAvgMsInCrit(0.0f) {
    cfg->FindData("budget", mBudget, false);
    cfg->FindData("critical", mCritical, false);
    for(int i = 0; i < MAX_TOP_VALS; i++) mTopValues[i] = 0.0f;
}

void TimerStats::CollectStats(float ms, bool critical, int critCount) {
    if (mCount++ != 0) {
        mAvgMs += (ms - mAvgMs) / mCount;
        mStdDevMs += (ABS(ms - mAvgMs) - mStdDevMs) / mCount;

        if (ms > mMaxMs) {
            mMaxMs = ms;
        }

        if (mBudget > 0.0f && ms > mBudget) {
            mNumOverBudget++;
            if (critical) {
                mNumCritOverBudget++;
                mAvgMsInCrit += (ms - mAvgMsInCrit) / critCount;
            }
        }

        for (int i = 0; i < mCount && i < MAX_TOP_VALS; i++) {
            float top = mTopValues[i];
            if (ms > top) {
                mTopValues[i] = ms;
                ms = top;
            }
        }
    } else {
        mAvgMs = ms;
        mMaxMs = 0.0f;
        mStdDevMs = 0.0f;
    }
}

void TimerStats::PrintPctile(float pctile) {
    float target = mCount * (1.0f - pctile);
    float top;
    for (int i = 0; i < MAX_TOP_VALS; i++) {
        top = mTopValues[i];
        if (i > target) {
            break;
        }
    }

    int a = std::floor(pctile * 100);
    if (target > MAX_TOP_VALS) {
        TheDebug << MakeString("   %dth pctile:   <%.2f THIS IS AN OVERESTIMATE.  For accurate percentile, increase MAX_TOP_VALS in Timer.h\n",
            a, top
        );
    } else {
        TheDebug << MakeString("   %dth pctile:   %.2f\n", a, top);
    }
}

void TimerStats::Dump(const char* tag, int critCount) {
    if (mCount != 0) {
        TheDebug << MakeString("%s\t(%2.2f, %2.2f), %4.2f, [>%.1f] %.2f {%2.2f} %.1f\n",
            tag,
            mAvgMs, mStdDevMs, mMaxMs, mBudget,
            (float)(mNumOverBudget * 100) / mCount,
            mAvgMsInCrit,
            (float)(mNumCritOverBudget * 100) / critCount
        );
        PrintPctile(0.99);
    } else {
        TheDebug << MakeString("s_%s_<no_data>_80bb62eb", tag);
    }
}

void TimerStats::Clear() {
    mCount = 0;
    mAvgMs = 0;
    mStdDevMs = 0;
    mMaxMs = 0;
    mNumOverBudget = 0;
    mNumCritOverBudget = 0;
    mAvgMsInCrit = 0;
    for (int i = 0; i < MAX_TOP_VALS; i++) {
        mTopValues[i] = 0;
    }
}

void Timer::Init() {
    Timer::sDoubleCycles2Ms = OSTicksToSeconds(1000.0);
    Timer::sLowCycles2Ms = (float)Timer::sDoubleCycles2Ms;
    Timer::sHighCycles2Ms = (float)(Timer::sDoubleCycles2Ms * UINT_MAX);
}
