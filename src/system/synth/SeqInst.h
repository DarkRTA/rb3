#ifndef SYNTH_SEQINST_H
#define SYNTH_SEQINST_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"

class Sequence;
class WaitSeq;
class GroupSeq;

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

    void* operator new(size_t s){
        return _PoolAlloc(s, 0x3c, FastPool);
    }

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

class WaitSeqInst : public SeqInst {
public:
    WaitSeqInst(WaitSeq*);
    virtual ~WaitSeqInst();
    virtual void Stop();
    virtual bool IsRunning();
    virtual void UpdateVolume();
    virtual void SetPan(float);
    virtual void SetTranspose(float);
    virtual void StartImpl();

    float mWaitMs;
    float mEndTime;
};

class GroupSeqInst : public SeqInst {
public:
    GroupSeqInst(GroupSeq*, bool);
    virtual ~GroupSeqInst();
    virtual void UpdateVolume();
    virtual void SetPan(float);
    virtual void SetTranspose(float);
    virtual void Poll();

    ObjVector<ObjPtr<SeqInst, class ObjectDir> > mSeqs;
};

#endif
