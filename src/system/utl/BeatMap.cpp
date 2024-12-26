#include "utl/BeatMap.h"
#include <algorithm>

BeatMap gDefaultBeatMap;
BeatMap* TheBeatMap = &gDefaultBeatMap;

void SetTheBeatMap(BeatMap* bmap){
    TheBeatMap = bmap;
}

void ResetTheBeatMap(){
    TheBeatMap = &gDefaultBeatMap;
}

bool BeatInfoCmp(const BeatInfo& info, int tick){
    return info.mTick < tick;
}

BeatMap::BeatMap(){
    
}

bool BeatMap::AddBeat(int tick, int level){
    if(mInfos.empty() || mInfos.back().mTick < tick){
        mInfos.push_back(BeatInfo(tick, level));
        return true;
    }
    else return false;
}

float BeatMap::Beat(int tick) const {
    if(mInfos.empty()) return (float)tick / 480.0f;
    else {
        int i2;
        if(tick <= mInfos[0].mTick) i2 = 0;
        else {
            i2 = mInfos.size();
            if(tick >= mInfos[i2 - 1].mTick) i2 = mInfos.size() - 2;
            else {
                const BeatInfo& frontInfo = mInfos.front();
                const BeatInfo* lowerInfo = std::lower_bound(mInfos.begin(), mInfos.end(), tick, BeatInfoCmp);
                i2 = lowerInfo - &frontInfo - 1;
            }
        }
        return Interpolate(tick, i2);
    }
}

float BeatMap::Beat(float tick) const {
    if(mInfos.empty()) return tick / 480.0f;
    else {
        int i2 = tick;
        if(tick < mInfos[0].mTick) i2 = 0;
        else {
            i2 = mInfos.size();
            if(tick > mInfos[i2 - 1].mTick) i2 = mInfos.size() - 2;
            else {
                const BeatInfo& frontInfo = mInfos.front();
                const BeatInfo* lowerInfo = std::lower_bound(mInfos.begin(), mInfos.end(), tick, BeatInfoCmp);
                i2 = lowerInfo - &frontInfo - 1;
            }
        }
        return Interpolate(tick, i2);
    }
}
