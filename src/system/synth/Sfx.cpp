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
        SynthSample* smp = (*it).mSynthPtr;
        if(smp) inst = smp->NewInst();
        if(inst){
            inst->SetBankVolume((*it).unkc + mRandVol);
            inst->SetBankPan((*it).unk10 + mRandPan);
            inst->SetBankSpeed(CalcSpeedFromTranspose((*it).unk14 + mRandTp));
            inst->SetFXCore((FXCore)(*it).unk18);
            inst->SetADSR((*it).adsr);
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
        MoggClip* clp = moggClipMap->mClipPtr;
        if(clp){
            clp->SetVolume(moggClipMap->unk30);
            clp->SetupPanInfo(moggClipMap->unk28, moggClipMap->unk2c, moggClipMap->unk34);
            clp->Play();
        }
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

BEGIN_HANDLERS(Sfx)
    HANDLE_ACTION(add_map, mMaps.push_back(SfxMap(this)))
    HANDLE_SUPERCLASS(Sequence)
    HANDLE_CHECK(0x147)
END_HANDLERS