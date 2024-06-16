#ifndef SYNTH_SFXMAP_H
#define SYNTH_SFXMAP_H
#include "obj/Object.h"
#include "synth/SynthSample.h"
#include "obj/ObjPtr_p.h"
#include "synth/SampleInst.h"
#include "synth/ADSR.h"

class SfxMap {
public:
    SfxMap(Hmx::Object*);
    void Load(BinStream&);

    static int gRev;

    ObjPtr<SynthSample, ObjectDir> mSample; // 0x0
    float mVolume; // 0xc
    float mPan; // 0x10
    float mTranspose; // 0x14
    FXCore mFXCore; // 0x18
    ADSR mADSR; // 0x1c
};

BinStream& operator>>(BinStream&, SfxMap&);

#endif
