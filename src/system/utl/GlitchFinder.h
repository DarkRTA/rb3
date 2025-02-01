#pragma once
#include "os/Timer.h"
#include "utl/TextStream.h"
#include <vector>

class GlitchAverager {
public:
    void PushInstance(float, bool);

    float mAvg; // 0x0
    float mMax; // 0x4
    int mCount; // 0x8
    float mGlitchAvg; // 0xc
    int mGlitchCount; // 0x10
};

class GlitchPoker {
public:
    GlitchPoker();
    ~GlitchPoker() {}

    void ClearData();
    bool OverBudget();
    void PrintNestedStartTimes(TextStream &, float);
    void PrintResult(TextStream &);
    void Dump(TextStream &, int);
    void PollAveragesRecurse(bool);

    char mName[64]; // 0x0
    float mTime; // 0x40
    float mTimeEnd; // 0x44
    std::vector<GlitchPoker *> mChildren; // 0x48
    GlitchPoker *mParent; // 0x50
    float mBudget; // 0x54
    GlitchAverager *mAvg; // 0x58

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
    static DataNode OnGlitchFind(DataArray *);
    static DataNode OnGlitchFindBudget(DataArray *);
    static DataNode OnGlitchFindLeaves(DataArray *);
    static DataNode OnGlitchFindPoke(DataArray *);

    void Poke(const char *, unsigned int);
    void PokeStart(const char *, unsigned int, float, float, GlitchAverager *);
    void PokeEnd(unsigned int);
    GlitchPoker *NewPoker();
    void Reset();
    void CheckDump();

    int mFrameCount; // 0x0
    int mGlitchCount; // 0x4
    bool mStop; // 0x8
    Timer mTime; // 0x10 - not 0xc because why?
    float mLastTime; // 0x40
    GlitchPoker mPokerPool[8]; // 0x44
    int mPokerIndex; // 0x324
    GlitchPoker *mStartPoker; // 0x328
    GlitchPoker *mCurPoker; // 0x32c
    bool mActive; // 0x330
    bool mDumpLeavesOnly; // 0x331
    float mLeafThreshold; // 0x334
    unsigned int mOverheadCycles; // 0x338
};
