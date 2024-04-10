#ifndef BEATMATCH_MERCURYSWITCHFILTER_H
#define BEATMATCH_MERCURYSWITCHFILTER_H
#include "obj/Data.h"
#include "rndobj/Overlay.h"
#include "os/Debug.h"

namespace {
    RndOverlay* gGuitarOverlay;
}

class MercurySwitchFilter {
public:
    MercurySwitchFilter(){}
    virtual ~MercurySwitchFilter(){}
    virtual bool Poll(float, float) = 0;
    virtual void Reset() = 0;
};

class LowPassMercurySwitchFilter : public MercurySwitchFilter {
public:
    LowPassMercurySwitchFilter(DataArray* arr) : mSensitivity(arr->FindFloat("sensitivity")), 
        mOnThreshold(arr->FindFloat("on_threshold")), mOffThreshold(arr->FindFloat("off_threshold")),
        mState(false), mLastPoll(0.0f) {

    }

    virtual ~LowPassMercurySwitchFilter(){}
    virtual bool Poll(float, float);
    virtual void Reset(){
        mLastPoll = 0.0f;
    }

    float mSensitivity;
    float mOnThreshold;
    float mOffThreshold;
    bool mState;
    float mLastPoll;
    float mAccum;
};

class AnySignMercurySwitchFilter : public MercurySwitchFilter {
public:
    AnySignMercurySwitchFilter(DataArray* arr) : mWindow(arr->FindFloat("window") * 1000.0f), 
        mNumFramesThreshold(arr->FindInt("num_frames")), mThreshold(arr->FindFloat("threshold")) {
        Reset();
    }
    virtual ~AnySignMercurySwitchFilter(){}
    virtual bool Poll(float f1, float f2){
        if(f2 >= mThreshold) mNumFrames++;
        else mNumFrames = 0;

        if(mNumFrames >= mNumFramesThreshold) mLastOn = f1;
        bool asdf = f1 - mLastOn < mWindow;
        if(gGuitarOverlay && gGuitarOverlay->mShowing){
            *gGuitarOverlay << MakeString(" val %4.2f    frames %4d   ->   %d\n", f2, mNumFrames, asdf);
        }
        return asdf;
    }

    virtual void Reset(){
        mNumFrames = 0;
        mLastOn = mWindow * -2.0f;
    }

    float mWindow;
    float mLastOn;
    int mNumFrames;
    int mNumFramesThreshold;
    float mThreshold;
};

MercurySwitchFilter* NewMercurySwitchFilter(DataArray*);

#endif
