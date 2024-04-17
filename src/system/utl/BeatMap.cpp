#include "utl/BeatMap.h"

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
        BeatInfo info;
        info.mTick = tick;
        info.mLevel = level;
        mInfos.push_back(info);
        return true;
    }
    else return false;
}