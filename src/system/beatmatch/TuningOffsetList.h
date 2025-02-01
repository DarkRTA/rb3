#pragma once
#include "utl/TickedInfo.h"

class TuningOffsetList : public TickedInfoCollection<float> {
public:
    TuningOffsetList() {
        mInfos.reserve(8);
        mInfos.push_back(TickedInfo<float>(-1, 100.0f));
    }
    ~TuningOffsetList() {}
};