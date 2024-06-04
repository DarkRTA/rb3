#ifndef SYNTH_SEQUENCE_H
#define SYNTH_SEQUENCE_H
#include "obj/Object.h"
#include "synth/Pollable.h"
#include "utl/FilePath.h"
#include "obj/ObjPtr_p.h"
#include "synth/Faders.h"
#include <list>

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
    
    virtual const char* GetSoundDisplayName(){ return MakeString("Sequence: %s", Name()); }
    virtual SeqInst* MakeInstImpl() = 0;
    virtual void SynthPoll();

    static void Init();

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

    NEW_OBJ(WaitSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(WaitSeq)
    }

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

    ObjPtrList<Sequence, class ObjectDir>& Children(){ return mChildren; }

    ObjPtrList<Sequence, class ObjectDir> mChildren; // 0x68
};

class RandomGroupSeq : public GroupSeq {
public:
    RandomGroupSeq();
    virtual ~RandomGroupSeq(){}
    OBJ_CLASSNAME(RandomGroupSeq);
    OBJ_SET_TYPE(RandomGroupSeq);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();

    int NextIndex();
    void PickNextIndex();
    void ForceNextIndex(int);
    int GetNumSimul(){ return mNumSimul; }

    NEW_OBJ(RandomGroupSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(RandomGroupSeq)
    }

    int mNumSimul; // 0x78
    bool mAllowRepeats; // 0x7c
    int mNextIndex; // 0x80
    int mForceChooseIndex; // 0x84
    std::list<int> mPlayHistory; // 0x88
};

class RandomIntervalGroupSeq : public GroupSeq {
public:
    RandomIntervalGroupSeq();
    virtual ~RandomIntervalGroupSeq(){}
    OBJ_CLASSNAME(RandomIntervalGroupSeq);
    OBJ_SET_TYPE(RandomIntervalGroupSeq);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();

    NEW_OBJ(RandomIntervalGroupSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(RandomIntervalGroupSeq)
    }

    float mAvgIntervalSecs; // 0x78
    float mIntervalSpread; // 0x7c
    int mMaxSimultaneous; // 0x80
};

class SerialGroupSeq : public GroupSeq {
public:
    SerialGroupSeq(){}
    virtual ~SerialGroupSeq(){}
    OBJ_CLASSNAME(SerialGroupSeq);
    OBJ_SET_TYPE(SerialGroupSeq);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();

    NEW_OBJ(SerialGroupSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(SerialGroupSeq)
    }
};

class ParallelGroupSeq : public GroupSeq {
public:
    ParallelGroupSeq(){}
    virtual ~ParallelGroupSeq(){}
    OBJ_CLASSNAME(ParallelGroupSeq);
    OBJ_SET_TYPE(ParallelGroupSeq);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();

    NEW_OBJ(ParallelGroupSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(ParallelGroupSeq)
    }
};

class SfxSeq : public SerialGroupSeq {
public:
    SfxSeq();
    virtual ~SfxSeq(){}
    OBJ_CLASSNAME(SfxSeq);
    OBJ_SET_TYPE(SfxSeq);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);

    NEW_OBJ(SfxSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(SfxSeq)
    }
};

#endif
