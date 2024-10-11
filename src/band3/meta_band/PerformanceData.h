#ifndef METABAND_PERFORMANCEDATA_H
#define METABAND_PERFORMANCEDATA_H
#include "system/obj/Object.h"
#include "system/meta/FixedSizeSaveable.h"
#include "band3/game/Defines.h"
#include "band3/game/Stats.h"

class PerformanceData : public Hmx::Object, public FixedSizeSaveable {
public:
    PerformanceData();
    virtual ~PerformanceData();
    virtual DataNode Handle(DataArray*, bool);
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void Prune(Stats&);
    void InitializeStatsVectors();
    void Initialize(const Stats&, int, ScoreType, Difficulty, Symbol, int, int, bool);

    // Located in RockCentral.cpp
    Symbol GetMode() const;
    int GetSongID() const;
    bool IsPlaytest() const;
    bool IsOnline() const;
    bool IsCheating() const;
    ScoreType GetScoreType() const;
    Difficulty GetDifficulty() const;
    int GetTimeStamp() const;
    Stats GetStats() const;
    int GetStars() const;
    int GetBattleID() const;

    static int SaveSize(int);

    int m0x24;
    bool m0x28;
    bool mIsOnline;         // 0x29
    bool mIsPlaytest;       // 0x2a 
    bool mIsCheating;       // 0x2b
    int mSongId;            // 0x2c
    ScoreType mScoreType;   // 0x30
    Difficulty mDifficulty; // 0x34
    int mStars;             // 0x38
    int mBattleId;          // 0x3c
    int mTimestamp;         // 0x40
    Symbol mMode;           // 0x44
    Stats mStats;           // 0x48

};

#endif // METABAND_PERFORMANCEDATA_H