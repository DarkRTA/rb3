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
    // possibly another pure virtual here?

    SeqInst* MakeInst();
    SeqInst* Play(float, float, float);
    DataNode OnPlay(DataArray*);
    void OnTriggerSound(int);

    void Stop(bool);
    
    ObjPtrList<SeqInst, class ObjectDir> mInsts;
    float mAvgVol;
    float mVolSpread;
    float mAvgTranspose;
    float mTransposeSpread;
    float mAvgPan;
    float mPanSpread;
    FaderGroup mFaders;
    bool mCanStop;
};

class SeqInst : public Hmx::Object {
public:
    SeqInst(Sequence*);
    virtual ~SeqInst();
    virtual void Stop() = 0;
    virtual bool IsRunning() = 0;
    virtual void UpdateVolume() = 0;
    virtual void SetPan(float) = 0;
    virtual void SetTranspose(float) = 0;
    virtual void Poll(){}
    virtual void StartImpl() = 0;

    void Start();
    void SetVolume(float);

    void operator delete(void* v){
        _PoolFree(sizeof(SeqInst), FastPool, v);
    }

    Sequence* mOwner;
    float mRandVol;
    float mRandPan;
    float mRandTp;
    float mVolume;
    bool mStarted;
};

#endif
