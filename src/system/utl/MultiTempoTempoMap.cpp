#include "utl/MultiTempoTempoMap.h"
#include "os/Debug.h"
#include "math/MathFuncs.h"
#include "utl/MemMgr.h"
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

float MultiTempoTempoMap::TickToTime(float tick) const {
    if(!tick) return 0.0f;
    float ret = 0.0f;
    if(mStartLoopTick < 0.0f || tick <= mEndLoopTick){
        TempoInfoPoint* pt = PointForTick(tick);
        if(pt == mTempoPoints.end()) ret = 0.0f;
        else ret = pt->mMs + (pt->mTempo * ((tick - (float)pt->mTick) / 480.0f) / 1000.0f);
    }
    else {
        float floored = floor_f((tick - mEndLoopTick) / (mEndLoopTick - mStartLoopTick));
        float time = TickToTime(mStartLoopTick + -((mEndLoopTick - mStartLoopTick) * floored - (tick - mEndLoopTick)));
        ret = (mEndLoopTime - mStartLoopTime) * floored + mEndLoopTime + (time - mStartLoopTime);
    }
    return ret;
}

// fn_80358694
bool MultiTempoTempoMap::AddTempoInfoPoint(int tick, int tempo){
    if(mTempoPoints.empty() && tick != 0) return false;
    else if(tick < mTempoPoints.back().mTick) return false;
    else {
        MemDoTempAllocations tmp(true, false);
        mTempoPoints.push_back(TempoInfoPoint(TickToTime(tick), tick, tempo));
    }
    return true;
}

void MultiTempoTempoMap::ClearLoopPoints(){
    mStartLoopTick = -1.0f;
    mEndLoopTick = -1.0f;
    mStartLoopTime = -1.0f;
    mEndLoopTime = -1.0f;
}

void MultiTempoTempoMap::SetLoopPoints(int start, int end){
    mStartLoopTick = start;
    mEndLoopTick = end;
    mStartLoopTime = TickToTime(mStartLoopTick);
    mEndLoopTime = TickToTime(mEndLoopTick);
}

MultiTempoTempoMap::TempoInfoPoint* MultiTempoTempoMap::PointForTick(float tick) const {
    TempoInfoPoint pt;
    pt.mMs = tick;
    if(mTempoPoints.empty()){
        MILO_WARN("Tempo map is empty; at least one tempo map entry is required");
        return (TempoInfoPoint*)mTempoPoints.end();
    }
    else {
        // const TempoInfoPoint* pt2 = std::upper_bound(mTempoPoints.begin(), mTempoPoints.end(), pt, CompareTick);
    }
}

bool MultiTempoTempoMap::CompareTick(float tick, const MultiTempoTempoMap::TempoInfoPoint& pt){
    return tick < pt.mTick;
}

bool MultiTempoTempoMap::CompareTime(float time, const MultiTempoTempoMap::TempoInfoPoint& pt){
    return time < pt.mMs;
}