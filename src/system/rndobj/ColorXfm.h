#ifndef RNDOBJ_COLORXFM_H
#define RNDOBJ_COLORXFM_H
#include "math/Color.h"
#include "math/Mtx.h"
#include "utl/BinStream.h"

class RndColorXfm {
public:
    float mHue;
    float mSaturation;
    float mLightness;
    float mContrast;
    float mBrightness;
    Hmx::Color mLevelInLo;
    Hmx::Color mLevelInHi;
    Hmx::Color mLevelOutLo;
    Hmx::Color mLevelOutHi;
    Transform mColorXfm;

    RndColorXfm();
    void Reset();
    void AdjustHue();
    void AdjustSaturation();
    void AdjustLightness();
    void AdjustContrast();
    void AdjustBrightness();
    void AdjustLevels();
    void AdjustColorXfm();
    bool Load(BinStream&);
};

#endif
