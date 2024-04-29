#ifndef UTL_GLITCHFINDER_H
#define UTL_GLITCHFINDER_H
#include "os/Timer.h"
#include "utl/TextStream.h"
#include <vector>

class GlitchAverager {
public:
    void PushInstance(float, bool);

    float mAvg;
    float mMax;
    int mCount;
    float mGlitchAvg;
    int mGlitchCount;
};

class GlitchPoker {
public:
    GlitchPoker();
    ~GlitchPoker(){}

    void ClearData();
    bool OverBudget();
    void PrintNestedStartTimes(TextStream&, float);
    void PrintResult(TextStream&);
    void Dump(TextStream&, int);
    void PollAveragesRecurse(bool);

    char mName[64];
    float mTime;
    float mTimeEnd;
    std::vector<GlitchPoker*> mChildren;
    GlitchPoker* mParent;
    float mBudget;
    GlitchAverager* mAvg;

    static std::vector<float> smNestedStartTimes;
    static float smLastDumpTime;
    static float smThreshold;
    static float smTotalLeafTime;
    static bool smDumpLeaves;
};

class GlitchFinder {
public:
    GlitchFinder();
    ~GlitchFinder();

    static void Init();
    static DataNode OnGlitchFind(DataArray*);
    static DataNode OnGlitchFindBudget(DataArray*);
    static DataNode OnGlitchFindLeaves(DataArray*);
    static DataNode OnGlitchFindPoke(DataArray*);
    
    void Poke(const char*, unsigned int);
    void PokeStart(const char*, unsigned int, float, float, GlitchAverager*);
    void PokeEnd(unsigned int);
    GlitchPoker* NewPoker();
    void Reset();

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
