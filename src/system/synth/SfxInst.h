#pragma once
#include "synth/SeqInst.h"
#include "synth/MoggClipMap.h"
#include "synth/SampleInst.h"

class Sfx;

class SfxInst : public SeqInst {
public:
    SfxInst(Sfx*);
    virtual ~SfxInst();
    virtual void Stop();
    virtual bool IsRunning();
    virtual void UpdateVolume();
    virtual void SetPan(float);
    virtual void SetTranspose(float);
    virtual void StartImpl();

    void SetSend(FxSend*);
    void SetReverbMixDb(float);
    void SetReverbEnable(bool);
    void SetSpeed(float);

    void Pause(bool);

    NEW_POOL_OVERLOAD(SfxInst);
    DELETE_POOL_OVERLOAD(SfxInst);

    std::vector<SampleInst*> mSamples; // 0x34
    ObjPtrList<MoggClipMap> mMoggClips; // 0x3c
    float mStartProgress; // 0x4c
};
