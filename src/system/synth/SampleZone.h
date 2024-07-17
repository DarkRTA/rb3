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

    ObjPtr<SynthSample, ObjectDir> mSynthPtr;
    float unkc;
    float unk10;
    int unk14;
    int unk18;
    int unk1c;
    int unk20;
    int unk24;
    FXCore unk28;
    ADSR adsr;
};

BinStream& operator>>(BinStream&, SampleZone&);
bool PropSync(SampleZone&, DataNode&, DataArray*, int, PropOp);

#endif
