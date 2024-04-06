#include "utl/MeasureMap.h"

MeasureMap::MeasureMap() : mTimeSigChanges() {
    TimeSigChange tsc;
    tsc.mMeasure = 0;
    tsc.mNum = 4;
    tsc.mDenom = 4;
    tsc.mTick = 0;
    mTimeSigChanges.push_back(tsc);
}
