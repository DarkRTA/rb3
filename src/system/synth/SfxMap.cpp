#include "synth/SfxMap.h"

int SfxMap::gRev = 0;

SfxMap::SfxMap(Hmx::Object* obj) : mSynthPtr(obj, 0), unkc(0.0f), unk10(0.0f), unk14(0.0f), unk18(-1) {

}

BinStream& operator>>(BinStream& bs, SfxMap& smap){
    smap.Load(bs);
    return bs;
}

void SfxMap::Load(BinStream& bs){
    bs >> mSynthPtr;
    if(gRev > 2){
        bs >> unkc >> unk10 >> unk14;
        int num;
        bs >> num;
        unk18 = num;
        if(gRev >= 4) bs >> adsr;
    }
}