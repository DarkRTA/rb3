#include "utl/BeatMap.h"
#include <algorithm>

BeatMap gDefaultBeatMap;
BeatMap *TheBeatMap = &gDefaultBeatMap;

void SetTheBeatMap(BeatMap *bmap) { TheBeatMap = bmap; }

void ResetTheBeatMap() { TheBeatMap = &gDefaultBeatMap; }

bool BeatInfoCmp(const BeatInfo &info, int tick) { return info.mTick < tick; }

BeatMap::BeatMap() {}

bool BeatMap::AddBeat(int tick, int level) {
    if (mInfos.empty() || mInfos.back().mTick < tick) {
        mInfos.push_back(BeatInfo(tick, level));
        return true;
    } else
        return false;
}

// https://decomp.me/scratch/h18a4
// matches in retail with the right inline settings
float BeatMap::Beat(int tick) const {
    if (mInfos.empty())
        return (float)tick / 480.0f;
    else {
        int i2;
        if (tick <= mInfos[0].mTick)
            i2 = 0;
        else {
            i2 = mInfos.size();
            if (tick >= mInfos[i2 - 1].mTick)
                i2 = mInfos.size() - 2;
            else {
                const BeatInfo *lowerInfo =
                    std::lower_bound(mInfos.begin(), mInfos.end(), tick, BeatInfoCmp);
                i2 = lowerInfo - &mInfos.front() - 1;
            }
        }
        return Interpolate(tick, i2);
    }
}

// also matches in retail with the right inline settings
float BeatMap::Beat(float tick) const {
    if (mInfos.empty())
        return tick / 480.0f;

    int firstTick = mInfos[0].mTick;
    int i2 = tick;
    if (i2 <= firstTick)
        i2 = 0;
    else if (i2 >= mInfos[mInfos.size() - 1].mTick)
        i2 = mInfos.size() - 2;
    else {
        const BeatInfo &frontInfo = mInfos.front();
        int sp08 = i2;
        const BeatInfo *lowerInfo =
            std::lower_bound(mInfos.begin(), mInfos.end(), sp08, BeatInfoCmp);
        i2 = lowerInfo - &frontInfo - 1;
    }
    return Interpolate(tick, i2);
}

float BeatMap::BeatToTick(float f1) const {
    if (mInfos.empty())
        return f1 * 480.0f;
    else {
        int i2;
        if (f1 < 0) {
            i2 = 0;
        } else {
            if (f1 > mInfos.size() - 2) {
                i2 = mInfos.size() - 2;
            } else {
                i2 = f1;
            }
        }

        const BeatInfo &r30 = mInfos[i2];
        const BeatInfo &r31 = mInfos[i2 + 1];
        int k1 = mInfos[i2].mTick;
        return static_cast<float>(f1 - i2) * static_cast<float>(r31.mTick - r30.mTick)
            + k1;
    }
}

bool BeatMap::IsDownbeat(int i1) const {
    if (mInfos.empty())
        return i1 % 4 == 0;
    else if (i1 >= mInfos.size()) {
        return false;
    } else
        return mInfos[i1].mLevel > 0;
}