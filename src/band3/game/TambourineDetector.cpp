#include "game/TambourineDetector.h"
#include "game/Singer.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "synth/MicManagerInterface.h"
#include "utl/TimeConversion.h"

MicClientID sNullClientID(-1, -1);

TambourineDetector::TambourineDetector(TambourineManager &mgr, Singer *singer)
    : mManager(mgr), mSinger(singer), unk8(0), unkc(0), unk10(1.0f) {
    MILO_ASSERT(mSinger, 0x1C);
    DataArray *cfg = SystemConfig("scoring", "vocals");
    mEnergyDropThreshold = cfg->FindFloat("tambourine_energy_drop_threshold");
    mEnergyRiseThreshold = cfg->FindFloat("tambourine_energy_rise_threshold");
    mLagMsOffset = cfg->FindInt("tambourine_ms_offset");
}

TambourineDetector::~TambourineDetector() {}

void TambourineDetector::CheckForSwing(float f1, float f2) {
    float sub = f1 - mLagMsOffset;
    int tick = MsToTickInt(sub);
    bool set8 = unk8;
    if (set8) {
        unkc = Max(unkc, f2);
        if (f2 < unkc - mEnergyDropThreshold) {
            unk10 = f2;
            set8 = false;
        }
    } else {
        unk10 = Min(unk10, f2);
        if (f2 > unk10 + mEnergyRiseThreshold) {
            set8 = true;
            unkc = f2;
        }
    }
    bool b1 = set8 && !unk8;
    unk8 = set8;
    if (b1 && mManager.TambourineSwing(tick) != 0) {
        mSinger->NoteTambourineSwing(sub);
    }
}