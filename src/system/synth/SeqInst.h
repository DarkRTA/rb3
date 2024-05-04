#ifndef SYNTH_SEQINST_H
#define SYNTH_SEQINST_H
#include "obj/Object.h"

class Sequence;

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
