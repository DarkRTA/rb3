#include "synth/SampleInst.h"
#include "math/Decibels.h"

SampleInst::SampleInst() : mVolume(1.0f), mBankVolume(1.0f), mPan(0.0f), mBankPan(0.0f), mSpeed(1.0f), mBankSpeed(1.0f), mSend(this, 0) {
    
}

SampleInst::~SampleInst(){
    
}

void SampleInst::Start(){
    Stop();
    StartImpl();
}

void SampleInst::Stop(){
    if(IsPlaying()){
        StopImpl();
    }
}

void SampleInst::SetVolume(float vol){
    mVolume = DbToRatio(vol);
    UpdateVolume();
}

void SampleInst::SetBankVolume(float vol){
    mBankVolume = DbToRatio(vol);
    UpdateVolume();
}

void SampleInst::UpdateVolume(){
    SetVolumeImpl(mVolume * mBankVolume);
}

void SampleInst::SetSend(FxSend* send){
    mSend = send;
    SetSendImpl(send);
}

void SampleInst::SetReverbMixDb(float db){
    mReverbMixDb = db;
    SetReverbMixDbImpl(mReverbMixDb);
}

void SampleInst::SetReverbEnable(bool b){
    mReverbEnabled = b;
    SetReverbEnableImpl(mReverbEnabled);
}

void SampleInst::SetPan(float pan){
    mPan = pan;
    SetPanImpl(mPan + mBankPan);
}

void SampleInst::SetBankPan(float bpan){
    mBankPan = bpan;
    SetPanImpl(mPan + mBankPan);
}

void SampleInst::SetSpeed(float spd){
    mSpeed = spd;
    SetSpeedImpl(mSpeed * mBankSpeed);
}

void SampleInst::SetBankSpeed(float bspd){
    mBankSpeed = bspd;
    SetSpeedImpl(mSpeed * mBankSpeed);
}
