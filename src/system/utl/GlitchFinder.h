#ifndef UTL_GLITCHFINDER_H
#define UTL_GLITCHFINDER_H
#include "os/Timer.h"
#include <vector>

class GlitchAverager {
public:
    float mAvg;
    float mMax;
    int mCount;
    float mGlitchAvg;
    int mGlitchCount;
};

class GlitchPoker {
public:
    GlitchPoker();
    ~GlitchPoker();

    void ClearData();
    bool OverBudget();

    char mName[64];
    float mTime;
    float mTimeEnd;
    std::vector<float> mChildren;
    GlitchPoker* mParent;
    float mBudget;
    GlitchAverager* mAvg;

    static std::vector<float> smNestedStartTimes;
};

class GlitchFinder {
public:
    GlitchFinder();
    ~GlitchFinder();
    int mFrameCount;
    int mGlitchCount;
    bool mStop;
    Timer mTime;
    float mLastTime;
    GlitchPoker mPokerPool[8];
    int mPokerIndex;
    GlitchPoker* mStartPoker;
    GlitchPoker* mCurPoker;
    bool mActive;
    bool mDumpLeavesOnly;
    float mLeafThreshold;
    unsigned int mOverheadCycles;
};

#endif
