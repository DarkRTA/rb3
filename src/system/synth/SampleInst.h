#ifndef SYNTH_SAMPLEINST_H
#define SYNTH_SAMPLEINST_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "synth/FxSend.h"
#include "synth/ADSR.h"

enum FXCore {
    kFXCore0 = 0,
    kFXCore1 = 1,
    kFXCoreNone = -1
};

class SampleInst : public Hmx::Object {
public:
    SampleInst();
    virtual ~SampleInst();
    virtual bool IsPlaying() = 0;
    virtual void Pause(bool) = 0;
    virtual void SetADSR(const ADSR&) = 0;
    virtual void SetFXCore(FXCore) = 0;
    virtual float GetProgress(){ return 0.0f; }
    virtual float SetStartProgress(float f){ return f; }
    virtual void StartImpl() = 0;
    virtual void StopImpl() = 0;
    virtual void SetVolumeImpl(float) = 0;
    virtual void SetPanImpl(float) = 0;
    virtual void SetSpeedImpl(float) = 0;
    virtual void SetSendImpl(FxSend*){}
    virtual void SetReverbMixDbImpl(float f){}
    virtual void SetReverbEnableImpl(bool){}
    
    void Start();
    void Stop();
    void SetVolume(float);
    void UpdateVolume();
    void SetBankVolume(float);
    void SetSend(FxSend*);
    void SetReverbMixDb(float);
    void SetReverbEnable(bool);
    void SetPan(float);
    void SetBankPan(float);
    void SetSpeed(float);
    void SetBankSpeed(float);

    float mVolume;
    float mBankVolume;
    float mPan;
    float mBankPan;
    float mSpeed;
    float mBankSpeed;
    ObjPtr<FxSend, ObjectDir> mSend;
    float mReverbMixDb;
    bool mReverbEnabled;
};

#endif
