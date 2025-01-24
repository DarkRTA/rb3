#pragma once
#include "beatmatch/FillInfo.h"

class DrumFillInfo : public FillInfo {
public:
    DrumFillInfo(){}
    virtual ~DrumFillInfo(){}
};

class DrumMap : public DrumFillInfo {
public:
    DrumMap();
    virtual ~DrumMap(){}

    int mCurrentLanes;
};