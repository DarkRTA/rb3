#ifndef SYNTH_SAMPLEZONE_H
#define SYNTH_SAMPLEZONE_H
#include "obj/Object.h"
#include "synth/SynthSample.h"
#include "obj/ObjPtr_p.h"
#include "synth/ADSR.h"
#include "synth/SampleInst.h"

class SampleZone {
public:
    SampleZone(Hmx::Object*);
    void Load(BinStream&);
    bool Includes(unsigned char, unsigned char);

    static int gRev;

    ObjPtr<SynthSample, ObjectDir> mSample; // 0x0
    float mVolume; // 0xc
    float mPan; // 0x10
    int mCenterNote; // 0x14
    int mMinNote; // 0x18
    int mMaxNote; // 0x1c
    int mMinVel; // 0x20
    int mMaxVel; // 0x24
    FXCore mFXCore; // 0x28
    ADSR mADSR; // 0x2c
};

BinStream& operator>>(BinStream&, SampleZone&);
bool PropSync(SampleZone&, DataNode&, DataArray*, int, PropOp);

#endif
