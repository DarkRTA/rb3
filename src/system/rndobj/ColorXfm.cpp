#include "rndobj/ColorXfm.h"

RndColorXfm::RndColorXfm() : mHue(0.0f), mSaturation(0.0f), mLightness(0.0f), mContrast(0.0f), mBrightness(0.0f),
    mLevelInLo(0.0f, 0.0f, 0.0f), mLevelInHi(1.0f, 1.0f, 1.0f), mLevelOutLo(0.0f, 0.0f, 0.0f), mLevelOutHi(1.0f, 1.0f, 1.0f) {
      Reset();
}

void RndColorXfm::Reset(){
    mColorXfm.Reset();
}

int ModChan(int chan){
    int i = chan % 3;
    if(i < 0) return i + 3;
    else return i;
}

void RndColorXfm::AdjustColorXfm(){
    mColorXfm.Reset();
    AdjustHue();
    AdjustSaturation();
    AdjustLightness();
    AdjustContrast();
    AdjustBrightness();
    AdjustLevels();
}

bool RndColorXfm::Load(BinStream& bs){
    int rev;
    bs >> rev;
    if(rev > 0) return false;
    else {
        bs >> mColorXfm;
        bs >> mHue >> mSaturation >> mLightness >> mContrast >> mBrightness;
        bs >> mLevelInLo >> mLevelInHi >> mLevelOutLo >> mLevelOutHi;
        return true;
    }
}
