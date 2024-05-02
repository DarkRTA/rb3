#include "synth/SampleZone.h"

int SampleZone::gRev = 0;

SampleZone::SampleZone(Hmx::Object* obj) : mSynthPtr(obj, 0), unkc(0.0f), unk10(0.0f), unk14(0x24), unk18(0), unk1c(0x7f), unk20(0), unk24(0x7f), unk28(-1) {

}

BinStream& operator>>(BinStream& bs, SampleZone& zone){
    zone.Load(bs);
    return bs;
}

void SampleZone::Load(BinStream& bs){
    bs >> mSynthPtr;
    bs >> unkc >> unk10 >> unk14 >> unk18 >> unk1c;
    int num;
    bs >> num;
    unk28 = num;
    bs >> adsr;
    if(gRev >= 2){
        bs >> unk20 >> unk24;
    }
}

bool SampleZone::Includes(unsigned char uc1, unsigned char uc2){
    bool ret = false;
    if(unk18 <= uc1 && uc1 <= unk1c && unk20 <= uc2 && uc2 <= unk24) ret = true;
    return ret;
}