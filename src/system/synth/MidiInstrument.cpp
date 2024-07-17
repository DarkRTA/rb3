#include "synth/MidiInstrument.h"
#include "synth/Synth.h"
#include "synth/SampleInst.h"
#include "math/Decibels.h"
#include "synth/Utl.h"
#include "utl/Symbols.h"

NoteVoiceInst::NoteVoiceInst(MidiInstrument* minst, SampleZone* zone, unsigned char uc1, unsigned char uc2, int i1, int i2, float f) : 
    mSample(0), mVolume(0), mStartProgress(0), mTriggerNote(uc1), mCenterNote(zone->mCenterNote), mStarted(0), mStopped(0), mGlideID(i2), mGlideFrames(0),
    mGlideToNote(0), mGlideFromNote(0), mGlideFramesLeft(-1), mFineTune(f), mDurationFramesLeft(i1), mOwner(minst) {
    if(zone->mSample){
        mSample = zone->mSample->NewInst();
        mSample->SetBankVolume(zone->mVolume + RatioToDb(uc2 / 127.0f));
        mSample->SetBankPan(zone->mPan);
        mSample->SetBankSpeed(CalcSpeedFromTranspose(mFineTune / 100.0f + (mTriggerNote - mCenterNote)));
        mSample->SetFXCore(zone->mFXCore);
        mSample->SetADSR(zone->mADSR);
        mSample->SetSend(minst->mSend);
    }
}

NoteVoiceInst::~NoteVoiceInst(){
    delete mSample;
    mSample = 0;
}

void NoteVoiceInst::Start(){
    mStarted = true;
    mSample->SetStartProgress(mStartProgress);
    mSample->Start();
}

void NoteVoiceInst::Stop(){
    mStopped = true;
    mSample->Stop();
}

bool NoteVoiceInst::IsRunning(){
    return mSample->IsPlaying();
}

void NoteVoiceInst::Pause(bool b){
    mSample->Pause(b);
}

void NoteVoiceInst::SetSend(FxSend* send){
    mSample->SetSend(send);
}

void NoteVoiceInst::SetReverbMixDb(float f){
    mSample->SetReverbMixDb(f);
}

void NoteVoiceInst::SetReverbEnable(bool b){
    mSample->SetReverbEnable(b);
}

void NoteVoiceInst::SetSpeed(float f){
    mSample->SetSpeed(f);
}

void NoteVoiceInst::SetTranspose(float f){
    SetSpeed(CalcSpeedFromTranspose(f));
}

void NoteVoiceInst::SetVolume(float f){
    mVolume = f;
    UpdateVolume();
}

void NoteVoiceInst::UpdateVolume(){
    mSample->SetVolume(mVolume + mOwner->mFaders.GetVal());
}

void NoteVoiceInst::SetPan(float f){
    mSample->SetPan(f);
}

MidiInstrument::MidiInstrument() : mMultiSampleMap(this), mPatchNumber(0), mSend(this, 0), mReverbMixDb(-96.0f), mReverbEnable(0), 
    mActiveVoices(this, kObjListNoNull), mFaders(this), mFineTuneCents(0.0f) {
    mFaders.Add(TheSynth->unk4c);
    mFaders.Add(TheSynth->unk54);
}

void MidiInstrument::Poll(){
    if(mActiveVoices.size() != 0){
        for(ObjPtrList<NoteVoiceInst, ObjectDir>::iterator it = mActiveVoices.begin(); it != mActiveVoices.end(); it){
            NoteVoiceInst* theinst = *it++;
            theinst->Poll();
            if(theinst->Started() && !theinst->IsRunning()){
                delete theinst;
            }
        }
        if(mFaders.Dirty()){
            for(ObjPtrList<NoteVoiceInst, ObjectDir>::iterator it = mActiveVoices.begin(); it != mActiveVoices.end(); ++it){
                (*it)->UpdateVolume();
            }
        }
    }
}

BEGIN_HANDLERS(MidiInstrument)
    HANDLE_ACTION(add_map, mMultiSampleMap.push_back(SampleZone(this)));
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xFE)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(SampleZone)
    SYNC_PROP(sample, o.mSample)
    SYNC_PROP(volume, o.mVolume)
    SYNC_PROP(pan, o.mPan)
    SYNC_PROP(centernote, o.mCenterNote)
    SYNC_PROP(minnote, o.mMinNote)
    SYNC_PROP(maxnote, o.mMaxNote)
    SYNC_PROP(minvelo, o.mMinVel)
    SYNC_PROP(maxvelo, o.mMaxVel)
    SYNC_PROP(fx_core, (int&)o.mFXCore)
    SYNC_PROP(adsr, o.mADSR)
END_CUSTOM_PROPSYNC

SAVE_OBJ(MidiInstrument, 0x125)

BEGIN_LOADS(MidiInstrument)
    int rev;
    bs >> rev;
    if(rev > 3) MILO_WARN("Can't load new MidiInstrument");
    else {
        SampleZone::gRev = rev;
        LOAD_SUPERCLASS(Hmx::Object)
        bs >> mMultiSampleMap;
        bs >> mSend;
        bs >> mPatchNumber;
        mFaders.Load(bs);
        if(rev >= 3){
            bs >> mReverbMixDb;
            bs >> mReverbEnable;
        }
    }
END_LOADS