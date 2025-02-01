#include "beatmatch/DrumMap.h"

DrumMap::DrumMap() : mCurrentLanes(0) { mLanes.AddInfo(0, 0); }

bool DrumMap::LaneOn(int tick, int i2) {
    int mask = 1 << i2;
    if (mCurrentLanes & mask)
        return false;
    else {
        UpdateLanes(tick, mCurrentLanes | mask);
        return true;
    }
}

bool DrumMap::LaneOff(int tick, int i2) {
    int mask = 1 << i2;
    if (!(mCurrentLanes & mask))
        return false;
    else {
        UpdateLanes(tick, mCurrentLanes & ~mask);
        return true;
    }
}

void DrumMap::UpdateLanes(int tick, int newLaneMask) {
    mCurrentLanes = newLaneMask;
    if (!mLanes.mInfos.empty() && tick == mLanes.mInfos.back().mTick) {
        mLanes.mInfos.back().mInfo = newLaneMask;
    } else
        mLanes.AddInfo(tick, newLaneMask);
}