#include "synth/SampleZone.h"

int SampleZone::gRev = 0;

SampleZone::SampleZone(Hmx::Object* obj) : mSample(obj, 0), mVolume(0.0f), mPan(0.0f), mCenterNote(0x24), mMinNote(0), mMaxNote(0x7f), mMinVel(0), mMaxVel(0x7f), mFXCore(kFXCoreNone) {

}

BinStream& operator>>(BinStream& bs, SampleZone& zone){
    zone.Load(bs);
    return bs;
}

void SampleZone::Load(BinStream& bs){
    bs >> mSample;
    bs >> mVolume >> mPan >> mCenterNote >> mMinNote >> mMaxNote;
    int num;
    bs >> num;
    mFXCore = (FXCore)num;
    bs >> mADSR;
    if(gRev >= 2){
        bs >> mMinVel >> mMaxVel;
    }
}

bool SampleZone::Includes(unsigned char uc1, unsigned char uc2){
    bool ret = false;
    if(mMinNote <= uc1 && uc1 <= mMaxNote && mMinVel <= uc2 && uc2 <= mMaxVel) ret = true;
    return ret;
}