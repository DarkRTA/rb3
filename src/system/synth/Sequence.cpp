#include "synth/Sequence.h"
#include "math/Rand.h"

namespace {
    float RandomVal(float f1, float f2){
        if(f2 == 0.0f) return f1;
        else return RandomFloat(f1 - f2, f1 + f2);
    }
}

Sequence::Sequence() : mInsts(this, kObjListNoNull), mAvgVol(0.0f), mVolSpread(0.0f), mAvgTranspose(0.0f), 
    mTransposeSpread(0.0f), mAvgPan(0.0f), mPanSpread(0.0f), mFaders(this), mCanStop(true) {

}

SeqInst* Sequence::MakeInst(){
    SeqInst* seq = MakeInstImpl();
    if(seq){
        mInsts.push_back(seq);
        StartPolling();
    }
    return seq;
}

SeqInst* Sequence::Play(float f1, float f2, float f3){
    SeqInst* seq = MakeInst();
    if(seq){
        seq->SetVolume(f1);
        seq->SetPan(f2);
        seq->SetTranspose(f3);
        seq->Start();
    }
    return seq;
}

Sequence::~Sequence(){

}

SAVE_OBJ(Sequence, 0xCF)

SeqInst::SeqInst(Sequence* seq) : mOwner(seq), mVolume(0.0f), mStarted(false) {
    mRandVol = RandomVal(mOwner->mAvgVol, mOwner->mVolSpread);
    mRandPan = RandomVal(mOwner->mAvgPan, mOwner->mPanSpread);
    mRandTp = RandomVal(mOwner->mAvgTranspose, mOwner->mTransposeSpread);
}

SeqInst::~SeqInst(){

}

void SeqInst::Start(){
    mStarted = true;
    StartImpl();
}

void SeqInst::SetVolume(float f){
    mVolume = f;
    UpdateVolume();
}