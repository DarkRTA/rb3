#pragma once
#include "synth/Sequence.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "synth/MoggClipMap.h"
#include "synth/SfxMap.h"
#include "synth/SfxInst.h"

class FxSend;

/** "Basic sound effect object.  Plays several samples with a given volume, pan, transpose, and envelope settings." */
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
    FxSend* GetSend() const { return mSend; }
    float GetReverbMixDb() const { return mReverbMixDb; }
    bool GetReverbEnable() const { return mReverbEnable; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(Sfx);
    static void Init(){
        REGISTER_OBJ_FACTORY(Sfx)
    }

    void Pause(bool);

    ObjVector<SfxMap> mMaps; // 0x68
    ObjVector<MoggClipMap> mMoggClipMaps; // 0x74
    /** "Effect chain to use" */
    ObjPtr<FxSend> mSend; // 0x80
    /** "Reverb send for this sfx" */
    float mReverbMixDb; // 0x8c
    /** "Enable reverb send" */
    bool mReverbEnable; // 0x90
    ObjPtrList<SfxInst> mSfxInsts; // 0x94
};
