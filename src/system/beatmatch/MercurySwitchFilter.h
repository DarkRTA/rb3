#ifndef BEATMATCH_MERCURYSWITCHFILTER_H
#define BEATMATCH_MERCURYSWITCHFILTER_H
#include "obj/Data.h"

class MercurySwitchFilter {
public:
    MercurySwitchFilter(){}
    virtual ~MercurySwitchFilter(){}
    virtual bool Poll(float, float) = 0;
    virtual void Reset() = 0;
};

class AnySignMercurySwitchFilter : public MercurySwitchFilter {
public:
    AnySignMercurySwitchFilter(DataArray* arr) : mWindow(arr->FindFloat("window") * 1000.0f), 
        mNumFramesThreshold(arr->FindInt("num_frames")), mThreshold(arr->FindFloat("threshold")) {
        Reset();
    }
    virtual ~AnySignMercurySwitchFilter(){}
    virtual bool Poll(float, float);
    virtual void Reset();

    float mWindow;
    float mLastOn;
    int mNumFrames;
    int mNumFramesThreshold;
    float mThreshold;
};

class LowPassMercurySwitchFilter : public MercurySwitchFilter {
public:
    LowPassMercurySwitchFilter(DataArray* arr) : mSensitivity(arr->FindFloat("sensitivity")), 
        mOnThreshold(arr->FindFloat("on_threshold")), mOffThreshold(arr->FindFloat("off_threshold")),
        mState(false), mLastPoll(0.0f) {

    }

    virtual ~LowPassMercurySwitchFilter(){}
    virtual bool Poll(float, float);
    virtual void Reset();

    float mSensitivity;
    float mOnThreshold;
    float mOffThreshold;
    bool mState;
    float mLastPoll;
    float mAccum;
};

MercurySwitchFilter* NewMercurySwitchFilter(DataArray*);

#endif
