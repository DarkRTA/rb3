#include "bandobj/BandCrowdMeter.h"

BandCrowdMeter::BandCrowdMeter() : unk194(0), unk198(1.0f), unk19c(0), unk1a8(2), unk1ac(0), unk1b0(this, kObjListNoNull), unk1c0(this, 0), unk1cc(this, 0),
    unk1d8(this, 0), unk1e4(this, 0), unk1f0(this, 0), unk1fc(this, 0), unk210(this, 0), unk21c(this, 0), unk228(this, 0), unk234(2), unk238(this, 0), unk244(0.5f) {
    for(int i = 0; i < 5; i++) unk1a0.push_back(Hmx::Color(0));
    for(int i = 0; i < 5; i++) unk248[i] = 0.5f;
}

BandCrowdMeter::~BandCrowdMeter(){

}

BandCrowdMeter::IconData::IconData(BandCrowdMeter* bcm, CrowdMeterIcon* icon, RndGroup* grp) : unk0(bcm, icon), unkc(bcm, grp),
    unk18(0), unk19(0), unk1a(0), unk1b(0), unk1c(0), unk20(0) {

}