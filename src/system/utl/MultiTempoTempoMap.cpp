#include "utl/MultiTempoTempoMap.h"
#include "os/Debug.h"
#include <algorithm>

MultiTempoTempoMap::MultiTempoTempoMap() : mStartLoopTick(-1.0f), mEndLoopTick(-1.0f) {
    
}

MultiTempoTempoMap::~MultiTempoTempoMap(){
    
}

float MultiTempoTempoMap::GetTempo(int tick) const {
    TempoInfoPoint* pt = PointForTick(tick);
    if(pt != mTempoPoints.end()) return (float)pt->mTempo / 1000.0f;
    else return 800.0f;
}

int MultiTempoTempoMap::GetTempoInMicroseconds(int tick) const {
    TempoInfoPoint* pt = PointForTick(tick);
    if(pt != mTempoPoints.end()) return pt->mTempo;
    else return 800000;
}

float MultiTempoTempoMap::GetTempoBPM(int tick) const {
    return 60000.0f / GetTempo(tick);
}



// MultiTempoTempoMap::TempoInfoPoint* MultiTempoTempoMap::PointForTick(float tick) const {
//     TempoInfoPoint pt;
//     pt.mMs = tick;
//     if(mTempoPoints.empty()){
//         MILO_WARN("Tempo map is empty; at least one tempo map entry is required");
//         return (TempoInfoPoint*)mTempoPoints.end();
//     }
//     else {
//         const TempoInfoPoint* pt2 = std::upper_bound(mTempoPoints.begin(), mTempoPoints.end(), pt, CompareTick);
//     }
// }

bool MultiTempoTempoMap::CompareTick(float tick, const MultiTempoTempoMap::TempoInfoPoint& pt){
    return tick < pt.mTick;
}

bool MultiTempoTempoMap::CompareTime(float time, const MultiTempoTempoMap::TempoInfoPoint& pt){
    return time < pt.mMs;
}