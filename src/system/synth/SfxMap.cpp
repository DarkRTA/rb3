#include "synth/SfxMap.h"

int SfxMap::gRev = 0;

SfxMap::SfxMap(Hmx::Object* obj) : mSample(obj, 0), mVolume(0.0f), mPan(0.0f), mTranspose(0.0f), mFXCore(kFXCoreNone) {

}

BinStream& operator>>(BinStream& bs, SfxMap& smap){
    smap.Load(bs);
    return bs;
}

void SfxMap::Load(BinStream& bs){
    bs >> mSample;
    if(gRev > 2){
        bs >> mVolume >> mPan >> mTranspose;
        int num;
        bs >> num;
        mFXCore = (FXCore)num;
        if(gRev >= 4) bs >> mADSR;
    }
}