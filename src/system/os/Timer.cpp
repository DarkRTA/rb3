#include "os/Timer.h"
#include "decomp.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "os/Debug.h"
#include "math/Utl.h"
#include "os/System.h"
#include "revolution/os/OSTime.h"
#include "stl/_pair.h"
#include <list>

std::vector<std::pair<Timer, TimerStats> > AutoTimer::sTimers;
int AutoTimer::sCritFrameCount;

float Timer::sLowCycles2Ms;
float Timer::sHighCycles2Ms;
double Timer::sDoubleCycles2Ms;

Timer Timer::sSlowFrameTimer;
float Timer::sSlowFrameWaiver;
int AutoSlowFrame::sDepth;
const char *Timer::sSlowFrameReason;

bool AutoTimer::sCriticalFrame;
bool AutoTimer::sCollectingStats;
bool gGlitchCallback;

static DataArray *tempArray = new DataArray(1);
static std::list<Symbol> sConditionalTimersEnabled;

Timer::Timer()
    : mStart(0), mCycles(0), mLastMs(0.0f), mWorstMs(0.0f), mWorstMsFrame(0), mFrame(0),
      mName(), mRunning(0), mBudget(0.0f), mDraw(true) {}

Timer::Timer(DataArray *config)
    : mStart(0), mCycles(0), mLastMs(0.0f), mWorstMs(0.0f), mWorstMsFrame(0), mFrame(0),
      mName(config->Sym(0)), mRunning(0), mBudget(0.0f), mDraw(true) {
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

TimerStats::TimerStats(DataArray *cfg)
    : mCount(0), mAvgMs(0.0f), mStdDevMs(0.0f), mMaxMs(0.0f), mNumOverBudget(0),
      mBudget(0.0f), mCritical(0), mNumCritOverBudget(0), mAvgMsInCrit(0.0f) {
    cfg->FindData("budget", mBudget, false);
    cfg->FindData("critical", mCritical, false);
    for (int i = 0; i < MAX_TOP_VALS; i++)
        mTopValues[i] = 0.0f;
}

void TimerStats::CollectStats(float ms, bool critical, int critCount) {
    static int temp;
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
        MILO_LOG(
            "   %dth pctile:   <%.2f THIS IS AN OVERESTIMATE.  For accurate percentile, increase MAX_TOP_VALS in Timer.h\n",
            a,
            top
        );
    } else {
        MILO_LOG("   %dth pctile:   %.2f\n", a, top);
    }
}

void TimerStats::Dump(const char *tag, int critCount) {
    if (mCount != 0) {
        MILO_LOG(
            "%s\t(%2.2f, %2.2f), %4.2f, [>%.1f] %.2f {%2.2f} %.1f\n",
            tag,
            mAvgMs,
            mStdDevMs,
            mMaxMs,
            mBudget,
            (float)(mNumOverBudget * 100) / mCount,
            mAvgMsInCrit,
            (float)(mNumCritOverBudget * 100) / critCount
        );
        PrintPctile(0.99);
    } else {
        MILO_LOG("%s <no data>\n", tag);
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

DECOMP_FORCEACTIVE(Timer, "Adding AutoTimer %s\n")

Timer *AutoTimer::GetTimer(Symbol name) {
    FOREACH (it, sTimers) {
        if (it->first.mName == name) {
            return &it->first;
        }
    }
    return nullptr;
}

void Timer::Init() {
    Timer::sDoubleCycles2Ms = OSTicksToSeconds(1000.0);
    Timer::sLowCycles2Ms = (float)Timer::sDoubleCycles2Ms;
    Timer::sHighCycles2Ms = (float)(Timer::sDoubleCycles2Ms * UINT_MAX);
}

void AutoTimer::SetCollectStats(bool b1, bool b2) {
    sCollectingStats = b1;
    if (b2 && !sCollectingStats) {
        DumpTimerStats();
    }
}

bool AutoTimer::CollectingStats() { return sCollectingStats; }

void AutoTimer::ComputeCriticalFrame() {
    sCriticalFrame = 0;
    FOREACH (it, sTimers) {
        if (it->second.mCritical && it->first.mLastMs > it->first.mBudget) {
            sCriticalFrame = true;
            sCritFrameCount++;
            return;
        }
    }
}

void AutoTimer::CollectTimerStats() {
    if (sCollectingStats) {
        ComputeCriticalFrame();
        FOREACH (it, sTimers) {
            if (it->first.mDraw) {
                it->second.CollectStats(
                    it->first.mLastMs, sCriticalFrame, sCritFrameCount
                );
            }
        }
    }
}

void AutoTimer::DumpTimerStats() {
    if (!sCritFrameCount)
        sCritFrameCount = true;
    MILO_LOG(
        "SONG TIMER STATS: (mean, SD), max, [>budget] pct overbudget {mean in critical frames} pct of crit frames overbudget\n"
    );
    FOREACH (it, sTimers) {
        TimerStats &stats = it->second;
        if (it->first.mDraw) {
            stats.Dump(it->first.mName.mStr, sCritFrameCount);
        }
        stats.Clear();
    }
    sCritFrameCount = 0;
}

static DataNode OnPrintTimers(DataArray *a) {
    AutoTimer::PrintTimers(a->Int(1));
    return 0;
}

void AutoTimer::PrintTimers(bool worst) {
    MILO_LOG("%s TIMES:\n", worst ? "WORST" : "LAST");
    FOREACH (it, sTimers) {
        if (it->first.mDraw) {
            const char *msStr =
                MakeString("%.2f", worst ? it->first.mWorstMs : it->first.mLastMs);
            MILO_LOG("%s\t%s\n", it->first.mName, msStr);
        }
    }
}

static DataNode ShowTimer(DataArray *arr) {
    Timer *timer = AutoTimer::GetTimer(arr->Sym(1));
    if (timer) {
        timer->mDraw = arr->Int(2);
    }
    return 0;
}

static DataNode SetTimerMs(DataArray *arr) {
    Timer *timer = AutoTimer::GetTimer(arr->Sym(1));
    if (timer) {
        timer->SetLastMs(arr->Float(2));
    }
    return 0;
}

static DataNode TimerMs(DataArray *arr) {
    Timer *timer = AutoTimer::GetTimer(arr->Sym(1));
    if (timer)
        return timer->GetLastMs();
    else
        return 0;
}

void AutoTimer::Init() {
    DataRegisterFunc("show_tier", ShowTimer);
    DataRegisterFunc("set_timer_ms", SetTimerMs);
    DataRegisterFunc("timer_ms", TimerMs);
    DataRegisterFunc("print_timers", OnPrintTimers);
    DataArray *cfg = SystemConfig("timer");
    for (int i = 1; i < cfg->Size(); i++) {
        DataArray *arr = cfg->Array(i);
        bool enabled = false;
        arr->FindData("enable", enabled, false);
        if (enabled) {
            sTimers.push_back(std::pair<Timer, TimerStats>(Timer(arr), TimerStats(arr)));
        }
    }
}

void TimerSymbolListPlaceholderFunc(std::list<Symbol> &syms) { syms.sort(); }

void AutoGlitchReport::EnableCallback() { gGlitchCallback = true; }

const char *FormatTime(float f1) { return MakeString("%.2f", f1); }