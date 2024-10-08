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
    const TempoInfoPoint* pt = PointForTick(tick);
    if(pt != mTempoPoints.end()) return (float)pt->mTempo / 1000.0f;
    else return 800.0f;
}

int MultiTempoTempoMap::GetTempoInMicroseconds(int tick) const {
    const TempoInfoPoint* pt = PointForTick(tick);
    if(pt != mTempoPoints.end()) return pt->mTempo;
    else return 800000;
}

float MultiTempoTempoMap::GetTempoBPM(int tick) const {
    return 60000.0f / GetTempo(tick);
}

// float ConvertTimeBase(float value, float srcStart, float srcEnd, float destStart, float destEnd,) {
//     float loopTickLength = srcEnd - srcStart;
//     float loopTick = value - srcEnd;
//     float loopPercent = std::floor(loopTick / loopTickLength);

//     float loopTimeLength = destEnd - destStart;
//     float loopTime = loopTimeLength * loopPercent + destEnd;
//     loopTime += TickToTime(srcStart + -(loopTickLength * loopPercent - loopTick)) - destStart;
//     return loopTime;
// }

float MultiTempoTempoMap::TickToTime(float tick) const {
    if(tick == 0.0f) return 0.0f;

    // need to load up-front to prevent a re-load of the value in the `else` block
    float startTick = mStartLoopTick;

    if(startTick < 0.0f || tick <= mEndLoopTick){
        const TempoInfoPoint* pt = PointForTick(tick);
        if(pt == mTempoPoints.end()) return 0.0f;
        else return pt->mMs + (pt->mTempo * ((tick - (float)pt->mTick) / 480.0f) / 1000.0f);
    } else {
        float loopTickLength = mEndLoopTick - startTick;
        float loopTick = tick - mEndLoopTick;
        float loopPercent = std::floor(loopTick / loopTickLength);

        float loopTimeLength = mEndLoopTime - mStartLoopTime;
        float loopTime = loopTimeLength * loopPercent + mEndLoopTime;
        loopTime += TickToTime(startTick + -(loopTickLength * loopPercent - loopTick)) - mStartLoopTime;
        return loopTime;
    }
}

float MultiTempoTempoMap::TimeToTick(float time) const {
    if(time == 0.0f) return 0.0f;

    // need to load up-front to prevent re-loads in the `else` block
    float startTick; // = mStartLoopTick;
    float endTick; // = mEndLoopTick;
    float endTime; // = mEndLoopTime;

    if((startTick = mStartLoopTick) < 0.0f || time < (endTick = mEndLoopTick) || time <= (endTime = mEndLoopTime)){
        const TempoInfoPoint* pt = PointForTime(time);
        return pt->mTick + ((time - pt->mMs) * 1000.0f / (float)pt->mTempo) * 480.0f;
    } else {
        // float loopTimeLength = endTime - mStartLoopTime;
        // float loopTime = time - endTime;
        // float loopPercent = std::floor(loopTime / loopTimeLength);

        // float a = time + -(loopTimeLength * loopPercent - loopTime);

        // float loopTickLength = endTick - startTick;
        // float loopTick = endTick + (loopTickLength * loopPercent);
        // loopTick += TimeToTick(a) - startTick;

        // return loopTick;

        float startTime = mStartLoopTime;

        float loopTimeLength = endTime - startTime;
        float loopTime = time - endTime;
        float loopPercent = std::floor(loopTime / loopTimeLength);

        float loopTickLength = endTick - startTick;
        float loopTick = loopTickLength * loopPercent + endTick;
        loopTick += TimeToTick(startTime + -(loopTimeLength * loopPercent - loopTime)) - mStartLoopTick;
        return loopTick;
    }
}

// fn_80358694
bool MultiTempoTempoMap::AddTempoInfoPoint(int tick, int tempo){
    if (mTempoPoints.empty()) {
        if (tick != 0) {
            return false;
        }
    } else if (tick < mTempoPoints.back().mTick) {
        return false;
    }

    MemDoTempAllocations tmp(true, false);
    mTempoPoints.push_back(TempoInfoPoint(TickToTime(tick), tick, tempo));
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

int MultiTempoTempoMap::GetLoopTick(int tick, int& asdf) const {
    if (mStartLoopTick < 0.0f) {
        return tick;
    }

    int startTick = mStartLoopTick;
    int endTick = mEndLoopTick;

    asdf = 0;
    if (tick > mEndLoopTick) {
        if (mStartLoopTick == mEndLoopTick) {
            return tick;
        }

        int loopTick = tick - startTick;
        int loopLength = endTick - startTick;
        int newTick = loopTick - (loopTick / loopLength) * loopLength + startTick;
        asdf = tick - newTick;
        return newTick;
    }
}

int MultiTempoTempoMap::GetLoopTick(int tick) const {
    int ok;
    return GetLoopTick(tick, ok);
}

float MultiTempoTempoMap::GetTimeInLoop(float time){
    if (mStartLoopTick == -1.0f) {
        return time;
    }

    float startTime = TickToTime(mStartLoopTick);
    if (time < startTime) {
        return time;
    }

    float endTime = TickToTime(mEndLoopTick);

    float loopLength = endTime - startTime;
    float timeFromStart = time - startTime;
    MILO_ASSERT(timeFromStart >= 0.0f, 0xE3);

    float a = std::floor(timeFromStart / loopLength);
    return startTime + -(loopLength * a - timeFromStart);
}

int MultiTempoTempoMap::GetNumTempoChangePoints() const { return mTempoPoints.size(); }

int MultiTempoTempoMap::GetTempoChangePoint(int index) const {
    MILO_ASSERT(index < mTempoPoints.size(), 0xF7);
    return mTempoPoints[index].mTick;
}

void MultiTempoTempoMap::Finalize(){
    std::vector<TempoInfoPoint> v(mTempoPoints);
    mTempoPoints.swap(v);
}

const MultiTempoTempoMap::TempoInfoPoint* MultiTempoTempoMap::PointForTick(float tick) const {
    TempoInfoPoint pt;
    pt.mMs = tick;

    if(mTempoPoints.empty()){
        MILO_WARN("Tempo map is empty; at least one tempo map entry is required");
        return mTempoPoints.end();
    }

    const TempoInfoPoint* pt2 = std::upper_bound(mTempoPoints.begin(), mTempoPoints.end(), pt.mMs, CompareTick);
    if (pt2 != mTempoPoints.begin()) {
        pt2--;
    }

    return pt2;
}

const MultiTempoTempoMap::TempoInfoPoint* MultiTempoTempoMap::PointForTime(float time) const {
    TempoInfoPoint pt;
    pt.mMs = time;
    MILO_ASSERT(mTempoPoints.size() >= 1, 0x121);

    const TempoInfoPoint* pt2 = std::upper_bound(mTempoPoints.begin(), mTempoPoints.end(), pt.mMs, CompareTime);
    if (pt2 != mTempoPoints.begin()) {
        pt2--;
    }

    return pt2;
}

bool MultiTempoTempoMap::CompareTick(float tick, const MultiTempoTempoMap::TempoInfoPoint& pt){
    return tick < pt.mTick;
}

bool MultiTempoTempoMap::CompareTime(float time, const MultiTempoTempoMap::TempoInfoPoint& pt){
    return time < pt.mMs;
}
