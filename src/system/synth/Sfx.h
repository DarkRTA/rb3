#ifndef SYNTH_SFX_H
#define SYNTH_SFX_H
#include "synth/Sequence.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "synth/MoggClipMap.h"
#include "synth/SfxMap.h"
#include "synth/SfxInst.h"

class FxSend;

class Sfx : public Sequence {
public:
    Sfx();
    virtual ~Sfx(){}
    OBJ_CLASSNAME(Sfx);
    OBJ_SET_TYPE(Sfx);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();
    virtual void SynthPoll();

    void SetSend(FxSend*);
    void SetReverbMixDb(float);
    void SetReverbEnable(bool);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    void Pause(bool);

    ObjVector<SfxMap> mMaps; // 0x68
    ObjVector<MoggClipMap> mMoggClipMaps; // 0x74
    ObjPtr<FxSend, ObjectDir> mSend; // 0x80
    float mReverbMixDb; // 0x8c
    bool mReverbEnable; // 0x90
    ObjPtrList<SfxInst, ObjectDir> mSfxInsts; // 0x94
};

#endif
