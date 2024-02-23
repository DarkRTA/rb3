#include "os/Timer.h"

Timer::Timer() : mStart(0), mCycles(0), mLastMs(0.0f), mWorstMs(0.0f), mWorstMsFrame(0), mFrame(0), mName(), mRunning(0), mBudget(0.0f), mDraw(true) {
    
}

Timer::Timer(DataArray* config) : mStart(0), mCycles(0), mLastMs(0.0f), mWorstMs(0.0f), mWorstMsFrame(0), mFrame(0), mName(config->Sym(0)), mRunning(0), mBudget(0.0f), mDraw(true) {
    config->FindData("budget", mBudget, false);
    config->FindData("draw", mDraw, false);
}
