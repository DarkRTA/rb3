#ifndef SYNTH_SFXMAP_H
#define SYNTH_SFXMAP_H
#include "obj/Object.h"
#include "synth/SynthSample.h"
#include "obj/ObjPtr_p.h"
#include "synth/ADSR.h"

class SfxMap {
public:
    SfxMap(Hmx::Object*);
    void Load(BinStream&);

    static int gRev;

    ObjPtr<SynthSample, ObjectDir> mSynthPtr;
    float unkc;
    float unk10;
    float unk14;
    int unk18;
    ADSR adsr;
};

BinStream& operator>>(BinStream&, SfxMap&);

#endif
