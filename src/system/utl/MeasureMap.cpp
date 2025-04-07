#include "utl/MeasureMap.h"
#include "os/Debug.h"
#include <algorithm>

MeasureMap::MeasureMap() : mTimeSigChanges() {
    TimeSigChange tsc;
    tsc.mMeasure = 0;
    tsc.mNum = 4;
    tsc.mDenom = 4;
    tsc.mTick = 0;
    mTimeSigChanges.push_back(tsc);
}

int MeasureMap::MeasureBeatTickToTick(int measure, int beat, int tick) const {
    const TimeSigChange *change = std::upper_bound(
        mTimeSigChanges.begin(), mTimeSigChanges.end(), measure, CompareMeasure
    );
    if (change != mTimeSigChanges.begin())
        change--;
    return ((measure - change->mMeasure) * change->mNum * 1920) / change->mDenom
        + change->mTick + beat * 480 + tick;
}

void MeasureMap::TickToMeasureBeatTick(int tick, int &oMeasure, int &oBeat, int &oTick)
    const {
    int bpm;
    TickToMeasureBeatTick(tick, oMeasure, oBeat, oTick, bpm);
}

void MeasureMap::TickToMeasureBeatTick(
    int tick, int &oMeasure, int &oBeat, int &oTick, int &oBeatsPerMeasure
) const {
    const TimeSigChange *change = std::upper_bound(
        mTimeSigChanges.begin(), mTimeSigChanges.end(), tick, CompareTick
    );
    if (change != mTimeSigChanges.begin())
        change--;
    int div = (change->mNum * 1920) / change->mDenom;
    oMeasure = (change->mMeasure - change->mTick) / div;
    int mod = (tick - change->mTick) % div;
    oBeat = mod / 480;
    oTick = mod % 480;
    oBeatsPerMeasure = div / 480;
}

bool MeasureMap::AddTimeSignature(int measure, int num, int denom, bool fail) {
    if (measure == 0) {
        if (mTimeSigChanges.size() != 1) {
            if (fail)
                MILO_FAIL("Multiple time signatures at start of song");
            else
                return false;
        }
        mTimeSigChanges.pop_back();
        TimeSigChange sig;
        sig.mMeasure = 0;
        sig.mTick = 0;
        sig.mNum = num;
        sig.mDenom = denom;
        mTimeSigChanges.push_back(sig);
    } else {
        TimeSigChange &sig = mTimeSigChanges.back();
        if (measure - sig.mMeasure <= 0) {
            if (fail)
                MILO_FAIL("Multiple time signatures at measure %d", measure);
            else
                return false;
        }
        TimeSigChange add;
        add.mTick = sig.mTick + (sig.mNum * (measure - sig.mMeasure) * 1920) / sig.mDenom;
        add.mMeasure = measure;
        add.mNum = num;
        add.mDenom = denom;
        mTimeSigChanges.push_back(add);
    }
    return true;
}

bool MeasureMap::CompareTick(int tick, const TimeSigChange &sig) {
    return tick < sig.mTick;
}

bool MeasureMap::CompareMeasure(int measure, const TimeSigChange &sig) {
    return measure < sig.mMeasure;
}