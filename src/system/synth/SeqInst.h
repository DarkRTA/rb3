#ifndef SYNTH_SEQINST_H
#define SYNTH_SEQINST_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"

class Sequence;
class WaitSeq;
class GroupSeq;
class RandomGroupSeq;
class RandomIntervalGroupSeq;
class SerialGroupSeq;
class ParallelGroupSeq;

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

    NEW_POOL_OVERLOAD(SeqInst);
    DELETE_POOL_OVERLOAD(SeqInst);

    Sequence* mOwner; // 0x1c
    float mRandVol; // 0x20
    float mRandPan; // 0x24
    float mRandTp; // 0x28
    float mVolume; // 0x2c
    bool mStarted; // 0x30
};

class WaitSeqInst : public SeqInst {
public:
    WaitSeqInst(WaitSeq*);
    virtual ~WaitSeqInst(){}
    virtual void Stop();
    virtual bool IsRunning();
    virtual void UpdateVolume();
    virtual void SetPan(float);
    virtual void SetTranspose(float);
    virtual void StartImpl();

    NEW_POOL_OVERLOAD(WaitSeqInst);
    DELETE_POOL_OVERLOAD(WaitSeqInst);

    float mWaitMs; // 0x34
    float mEndTime; // 0x38
};

class GroupSeqInst : public SeqInst {
public:
    GroupSeqInst(GroupSeq*, bool);
    virtual ~GroupSeqInst();
    virtual void UpdateVolume();
    virtual void SetPan(float);
    virtual void SetTranspose(float);
    virtual void Poll(){}

    ObjVector<ObjPtr<SeqInst, class ObjectDir> > mSeqs; // 0x34
};

class RandomGroupSeqInst : public GroupSeqInst {
public:
    RandomGroupSeqInst(RandomGroupSeq*);
    virtual ~RandomGroupSeqInst();
    virtual void Stop();
    virtual bool IsRunning();
    virtual void Poll();
    virtual void StartImpl();

    NEW_POOL_OVERLOAD(RandomGroupSeqInst);
    DELETE_POOL_OVERLOAD(RandomGroupSeqInst);

    int mNumSeqs; // 0x40
    ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator mIt; // 0x44
};

class RandomIntervalGroupSeqInst : public GroupSeqInst {
public:
    RandomIntervalGroupSeqInst(RandomIntervalGroupSeq*);
    virtual ~RandomIntervalGroupSeqInst();
    virtual void Stop();
    virtual bool IsRunning();
    virtual void Poll();
    virtual void StartImpl();

    void ComputeNextTime();

    NEW_POOL_OVERLOAD(RandomIntervalGroupSeqInst);
    DELETE_POOL_OVERLOAD(RandomIntervalGroupSeqInst);

    int unk40;
    int unk44;
    int unk48;
    std::vector<int> unk4c;
    bool unk54;
};

class SerialGroupSeqInst : public GroupSeqInst {
public:
    SerialGroupSeqInst(SerialGroupSeq*);
    virtual ~SerialGroupSeqInst(){}
    virtual void Stop();
    virtual bool IsRunning();
    virtual void Poll();
    virtual void StartImpl();

    NEW_POOL_OVERLOAD(SerialGroupSeqInst);
    DELETE_POOL_OVERLOAD(SerialGroupSeqInst);

    ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator mIt; // 0x40
};

class ParallelGroupSeqInst : public GroupSeqInst {
public:
    ParallelGroupSeqInst(ParallelGroupSeq*);
    virtual ~ParallelGroupSeqInst();
    virtual void Stop();
    virtual bool IsRunning();
    virtual void Poll();
    virtual void StartImpl();

    NEW_POOL_OVERLOAD(ParallelGroupSeqInst);
    DELETE_POOL_OVERLOAD(ParallelGroupSeqInst);

    ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator mIt; // 0x40
};

#endif
