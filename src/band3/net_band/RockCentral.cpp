#include "band3/meta_band/PerformanceData.h"

Symbol PerformanceData::GetMode() const {
    return mMode;
}

int PerformanceData::GetSongID() const {
    return mSongId;
}

bool PerformanceData::IsPlaytest() const {
    return mIsPlaytest;
}

bool PerformanceData::IsOnline() const {
    return mIsOnline;
}

bool PerformanceData::IsCheating() const {
    return mIsCheating;
}

ScoreType PerformanceData::GetScoreType() const {
    return mScoreType;
}

Difficulty PerformanceData::GetDifficulty() const {
    return mDifficulty;
}

int PerformanceData::GetTimeStamp() const {
    return mTimestamp;
}

// Stats& PerformanceData::GetStats() const {
//     return mStats;
// }

int PerformanceData::GetStars() const {
    return mStars;
}

int PerformanceData::GetBattleID() const {
    return mBattleId;
}
