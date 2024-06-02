#include "os/Timer.h"
#include <list>

std::vector<std::pair<Timer, TimerStats> > AutoTimer::sTimers;
Timer Timer::sSlowFrameTimer;
static DataArray* tempArray = new DataArray(1);
static std::list<Symbol> sConditionalTimersEnabled;

Timer::Timer() : mStart(0), mCycles(0), mLastMs(0.0f), mWorstMs(0.0f), mWorstMsFrame(0), mFrame(0), mName(), mRunning(0), mBudget(0.0f), mDraw(true) {
    
}

Timer::Timer(DataArray* config) : mStart(0), mCycles(0), mLastMs(0.0f), mWorstMs(0.0f), mWorstMsFrame(0), mFrame(0), mName(config->Sym(0)), mRunning(0), mBudget(0.0f), mDraw(true) {
    config->FindData("budget", mBudget, false);
    config->FindData("draw", mDraw, false);
}

TimerStats::TimerStats(DataArray* cfg) : mCount(0), mAvgMs(0.0f), mStdDevMs(0.0f), mMaxMs(0.0f), mNumOverBudget(0), mBudget(0.0f), mCritical(0), mNumCritOverBudget(0), mAvgMsInCrit(0.0f) {
    cfg->FindData("budget", mBudget, false);
    cfg->FindData("critical", mCritical, false);
    for(int i = 0; i < 128; i++) mTopValues[i] = 0.0f;
}