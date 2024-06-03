#ifndef SYNTH_SEQUENCE_H
#define SYNTH_SEQUENCE_H
#include "obj/Object.h"
#include "synth/Pollable.h"
#include "utl/FilePath.h"
#include "obj/ObjPtr_p.h"
#include "synth/Faders.h"

class SeqInst;

class Sequence : public Hmx::Object, public SynthPollable {
public:
    Sequence();
    virtual ~Sequence();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    
    virtual const char* GetSoundDisplayName();
    virtual SeqInst* MakeInstImpl() = 0;
    virtual void SynthPoll();

    SeqInst* MakeInst();
    SeqInst* Play(float, float, float);
    DataNode OnPlay(DataArray*);
    void OnTriggerSound(int);

    void Stop(bool);
    
    ObjPtrList<SeqInst, class ObjectDir> mInsts; // 0x28
    float mAvgVol; // 0x38
    float mVolSpread; // 0x3c
    float mAvgTranspose; // 0x40
    float mTransposeSpread; // 0x44
    float mAvgPan; // 0x48
    float mPanSpread; // 0x4c
    FaderGroup mFaders; // 0x50
    bool mCanStop; // 0x64
};

class WaitSeq : public Sequence {
public:
    WaitSeq();
    virtual ~WaitSeq(){}
    OBJ_CLASSNAME(WaitSeq);
    OBJ_SET_TYPE(WaitSeq);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();

    float mAvgWaitSecs;
    float mWaitSpread;
};

class GroupSeq : public Sequence {
public:
    GroupSeq();
    virtual ~GroupSeq(){}
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    ObjPtrList<Sequence, class ObjectDir> mChildren;
};

#endif
