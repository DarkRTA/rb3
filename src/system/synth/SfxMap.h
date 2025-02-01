#pragma once
#include "obj/Object.h"
#include "synth/SynthSample.h"
#include "obj/ObjPtr_p.h"
#include "synth/SampleInst.h"
#include "synth/ADSR.h"

class SfxMap {
public:
    SfxMap(Hmx::Object *);
    void Load(BinStream &);

    static int gRev;

    /** "Which sample to play" */
    ObjPtr<SynthSample> mSample; // 0x0
    /** "Volume in dB (0 is full volume, -96 is silence)" */
    float mVolume; // 0xc
    /** "Surround pan, between -4 and 4" */
    float mPan; // 0x10
    /** "Transpose in half steps" */
    float mTranspose; // 0x14
    /** "Which core's digital FX should be used in playing this sample" */
    FXCore mFXCore; // 0x18
    ADSR mADSR; // 0x1c
};

BinStream &operator>>(BinStream &, SfxMap &);
