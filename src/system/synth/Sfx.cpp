#include "synth/SfxInst.h"
#include "synth/MoggClipMap.h"
#include "synth/SfxMap.h"
#include "synth/FxSend.h"
#include "synth/SampleInst.h"
#include "synth/Synth.h"
#include "synth/Sfx.h"
#include "synth/Utl.h"
#include "utl/Symbols.h"

SfxInst::SfxInst(Sfx* sfx) : SeqInst(sfx), mMoggClips(this, kObjListNoNull), mStartProgress(0.0f) {
    for(ObjVector<SfxMap>::iterator it = sfx->mMaps.begin(); it != sfx->mMaps.end(); it++){
        SampleInst* inst = 0;
        SynthSample* smp = (*it).mSample;
        if(smp) inst = smp->NewInst();
        if(inst){
            inst->SetBankVolume((*it).mVolume + mRandVol);
            inst->SetBankPan((*it).mPan + mRandPan);
            inst->SetBankSpeed(CalcSpeedFromTranspose((*it).mTranspose + mRandTp));
            inst->SetFXCore((*it).mFXCore);
            inst->SetADSR((*it).mADSR);
            inst->SetSend(sfx->mSend);
            inst->SetReverbMixDb(sfx->mReverbMixDb);
            inst->SetReverbEnable(sfx->mReverbEnable);
            mSamples.push_back(inst);
        }
    }
    for(ObjVector<MoggClipMap>::iterator it = sfx->mMoggClipMaps.begin(); it != sfx->mMoggClipMaps.end(); it++){
        mMoggClips.push_back(&*it);
    }
}

SfxInst::~SfxInst(){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        delete *it;
    }
    mSamples.clear();
}

void SfxInst::StartImpl(){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        (*it)->SetStartProgress(mStartProgress);
        (*it)->Start();
    }
    for(ObjPtrList<MoggClipMap, ObjectDir>::iterator it = mMoggClips.begin(); it != mMoggClips.end(); ++it){
        MoggClipMap* moggClipMap = *it;
        MILO_ASSERT(moggClipMap, 0x53);
        MoggClip* clp = moggClipMap->mMoggClip;
        if(clp){
            clp->SetVolume(moggClipMap->mVolume);
            clp->SetupPanInfo(moggClipMap->mPan, moggClipMap->mPanWidth, moggClipMap->mIsStereo);
            clp->Play();
        }
    }
}

void SfxInst::Stop(){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        (*it)->Stop();
    }
    for(ObjPtrList<MoggClipMap, ObjectDir>::iterator it = mMoggClips.begin(); it != mMoggClips.end(); ++it){
        MoggClipMap* moggClipMap = *it;
        MILO_ASSERT(moggClipMap, 0x68);
        MoggClip* clp = moggClipMap->mMoggClip;
        if(clp) clp->Stop();
    }
}

bool SfxInst::IsRunning(){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        if((*it)->IsPlaying()) return true;
    }
    for(ObjPtrList<MoggClipMap, ObjectDir>::iterator it = mMoggClips.begin(); it != mMoggClips.end(); ++it){
        MoggClipMap* moggClipMap = *it;
        MILO_ASSERT(moggClipMap, 0x7F);
        MoggClip* clp = moggClipMap->mMoggClip;
        if(clp){
            if(clp->mStream) return true;
        }
    }
    return false;
}

void SfxInst::Pause(bool b){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        (*it)->Pause(b);
    }
    for(ObjPtrList<MoggClipMap, ObjectDir>::iterator it = mMoggClips.begin(); it != mMoggClips.end(); ++it){
        MoggClipMap* moggClipMap = *it;
        MILO_ASSERT(moggClipMap, 0x95);
        MoggClip* clp = moggClipMap->mMoggClip;
        if(clp) clp->Pause(b);
    }
}

void SfxInst::SetSend(FxSend* send){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        (*it)->SetSend(send);
    }
}

void SfxInst::SetReverbMixDb(float f){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        (*it)->SetReverbMixDb(f);
    }
}

void SfxInst::SetReverbEnable(bool b){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        (*it)->SetReverbEnable(b);
    }
}

void SfxInst::SetSpeed(float f){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        (*it)->SetSpeed(f);
    }
}

void SfxInst::SetTranspose(float f){
    SetSpeed(CalcSpeedFromTranspose(f));
}

void SfxInst::UpdateVolume(){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        (*it)->SetVolume(mVolume + mOwner->mFaders.GetVal());
    }
    for(ObjPtrList<MoggClipMap, ObjectDir>::iterator it = mMoggClips.begin(); it != mMoggClips.end(); ++it){
        MoggClipMap* moggClipMap = *it;
        MILO_ASSERT(moggClipMap, 0xCB);
        MoggClip* clp = moggClipMap->mMoggClip;
        if(clp) clp->SetControllerVolume(mRandVol + mVolume + mOwner->mFaders.GetVal());
    }
}

void SfxInst::SetPan(float f){
    for(std::vector<SampleInst*>::iterator it = mSamples.begin(); it != mSamples.end(); it++){
        (*it)->SetPan(f);
    }
}

Sfx::Sfx() : mMaps(this), mMoggClipMaps(this), mSend(this), mReverbMixDb(-96.0f), mReverbEnable(0), mSfxInsts(this, kObjListNoNull) {
    mFaders.Add(TheSynth->unk4c);
    mFaders.Add(TheSynth->unk50);
}

void Sfx::SynthPoll(){ Sequence::SynthPoll(); }

void Sfx::Pause(bool b){
    for(ObjPtrList<SfxInst, ObjectDir>::iterator it = mSfxInsts.begin(); it != mSfxInsts.end(); ++it){
        (*it)->Pause(b);
    }
}

SeqInst* Sfx::MakeInstImpl(){
    SfxInst* inst = new SfxInst(this);
    mSfxInsts.push_back(inst);
    return inst;
}

DECOMP_FORCEFUNC(Sfx, SynthSample, LengthMs)

BEGIN_HANDLERS(Sfx)
    HANDLE_ACTION(add_map, mMaps.push_back(SfxMap(this)))
    HANDLE_SUPERCLASS(Sequence)
    HANDLE_CHECK(0x147)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(ADSR)
    SYNC_PROP(attack_mode, (int&)o.mAttackMode)
    SYNC_PROP(attack_rate, o.mAttackRate)
    SYNC_PROP(decay_rate, o.mDecayRate)
    SYNC_PROP(sustain_mode, (int&)o.mSustainMode)
    SYNC_PROP(sustain_rate, o.mSustainRate)
    SYNC_PROP(sustain_level, o.mSustainLevel)
    SYNC_PROP(release_mode, (int&)o.mReleaseMode)
    SYNC_PROP(release_rate, o.mReleaseRate)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(SfxMap)
    SYNC_PROP(sample, o.mSample)
    SYNC_PROP(volume, o.mVolume)
    SYNC_PROP(pan, o.mPan)
    SYNC_PROP(transpose, o.mTranspose)
    SYNC_PROP(fx_core, (int&)o.mFXCore)
    SYNC_PROP(adsr, o.mADSR)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(MoggClipMap)
    SYNC_PROP(moggclip, o.mMoggClip)
    SYNC_PROP(volume, o.mVolume)
    SYNC_PROP(pan, o.mPan)
    SYNC_PROP(pan_width, o.mPanWidth)
    SYNC_PROP(is_stereo, o.mIsStereo)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(Sfx)
    SYNC_PROP(sfxmaps, mMaps)
    SYNC_PROP(moggclip_maps, mMoggClipMaps)
    SYNC_PROP_SET(send, (Hmx::Object*)mSend, SetSend(_val.Obj<FxSend>(0)))
    SYNC_PROP_SET(reverb_mix_db, mReverbMixDb, SetReverbMixDb(_val.Float(0)))
    SYNC_PROP_SET(reverb_enable, mReverbEnable, SetReverbEnable(_val.Int(0)))
    SYNC_PROP(faders, mFaders)
    SYNC_SUPERCLASS(Sequence)
END_PROPSYNCS

SAVE_OBJ(Sfx, 0x17C)

BEGIN_LOADS(Sfx)
    int rev;
    bs >> rev;
    if(rev > 0xC) MILO_WARN("Can't load new Sfx");
    else {
        if(rev >= 6) LOAD_SUPERCLASS(Sequence)
        else if(rev >= 2) LOAD_SUPERCLASS(Hmx::Object)
        SfxMap::gRev = rev;
        bs >> mMaps;
        if(rev >= 10){
            MoggClipMap::sRev = rev;
            bs >> mMoggClipMaps;
        }
        if(rev > 4){
            bs >> mSend;
            if(rev <= 7){
                int i;
                bs >> i;
            }
        }
        if(rev >= 9) mFaders.Load(bs);
        if(rev >= 0xC){
            bs >> mReverbMixDb >> mReverbEnable;
        }
    }
END_LOADS

BEGIN_COPYS(Sfx)
    COPY_SUPERCLASS(Sequence)
    CREATE_COPY(Sfx)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mMaps)
            COPY_MEMBER(mMoggClipMaps)
        }
        COPY_MEMBER(mSend)
        COPY_MEMBER(mReverbMixDb)
        COPY_MEMBER(mReverbEnable)
    END_COPYING_MEMBERS
END_COPYS

void Sfx::SetSend(FxSend* send){
    mSend = send;
    for(ObjPtrList<SfxInst, ObjectDir>::iterator it = mSfxInsts.begin(); it != mSfxInsts.end(); ++it){
        (*it)->SetSend(mSend);
    }
}

void Sfx::SetReverbMixDb(float f){
    mReverbMixDb = f;
    for(ObjPtrList<SfxInst, ObjectDir>::iterator it = mSfxInsts.begin(); it != mSfxInsts.end(); ++it){
        (*it)->SetReverbMixDb(mReverbMixDb);
    }
}

void Sfx::SetReverbEnable(bool b){
    mReverbEnable = b;
    for(ObjPtrList<SfxInst, ObjectDir>::iterator it = mSfxInsts.begin(); it != mSfxInsts.end(); ++it){
        (*it)->SetReverbEnable(mReverbEnable);
    }
}