#include "synth/Sequence.h"
#include "synth/SeqInst.h"
#include "math/Rand.h"
#include "utl/Symbols.h"

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

void Sequence::Stop(bool b){
    if(mCanStop || b){

    }
}

Sequence::~Sequence(){

}

SAVE_OBJ(Sequence, 0xCF)

void Sequence::Load(BinStream& bs){
    int rev;
    bs >> rev;
    if(rev > 3) MILO_WARN("Can't load new Sequence");
    else {
        if(rev > 2) Hmx::Object::Load(bs);
        bs >> mAvgVol >> mVolSpread >> mAvgTranspose >> mTransposeSpread >> mAvgPan >> mPanSpread;
        if(rev >= 2) bs >> mCanStop;
    }
}

BEGIN_COPYS(Sequence)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY(Sequence)
    if(c && ty != kCopyFromMax){
        COPY_MEMBER(mAvgVol)
        COPY_MEMBER(mVolSpread)
        COPY_MEMBER(mAvgTranspose)
        COPY_MEMBER(mTransposeSpread)
        COPY_MEMBER(mAvgPan)
        COPY_MEMBER(mPanSpread)
        COPY_MEMBER(mCanStop)
    }
END_COPYS

DataNode Sequence::OnPlay(DataArray* arr){
    float fvol = 0.0f;
    float fpan = 0.0f;
    float ftrans = 0.0f;
    arr->FindData(volume, fvol, false);
    arr->FindData(pan, fpan, false);
    arr->FindData(transpose, ftrans, false);
    Play(fvol, fpan, ftrans);
    return DataNode(0);
}

void Sequence::OnTriggerSound(int i){
    switch(i){
        case 0:
            Stop(false);
            break;
        case 1:
            Play(0.0f, 0.0f, 0.0f);
            break;
        case 2:
            
            break;
        default: break;
    }
}

BEGIN_HANDLERS(Sequence)
    HANDLE(play, OnPlay)
    HANDLE_ACTION(stop, Stop(_msg->Size() == 4 ? _msg->Int(3) : 0))
    HANDLE_ACTION(add_fader, mFaders.Add(_msg->Obj<Fader>(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x144)
END_HANDLERS

BEGIN_PROPSYNCS(Sequence)
    SYNC_PROP(avg_volume, mAvgVol)
    SYNC_PROP(volume_spread, mVolSpread)
    SYNC_PROP(avg_transpose, mAvgTranspose)
    SYNC_PROP(transpose_spread, mTransposeSpread)
    SYNC_PROP(avg_pan, mAvgPan)
    SYNC_PROP(pan_spread, mPanSpread)
    SYNC_PROP(can_stop, mCanStop)
    SYNC_PROP_METHOD(trigger_sound, 0, OnTriggerSound(_val.Int(0)))
END_PROPSYNCS

WaitSeq::WaitSeq() : mAvgWaitSecs(0.0f), mWaitSpread(0.0f) {

}

SeqInst* WaitSeq::MakeInstImpl(){
    return new WaitSeqInst(this);
}

SAVE_OBJ(WaitSeq, 0x166)

void WaitSeq::Load(BinStream& bs){
    int rev;
    bs >> rev;
    if(rev > 2) MILO_WARN("Can't load new WaitSeq");
    else {
        Sequence::Load(bs);
        bs >> mAvgWaitSecs;
        if(rev >= 2) bs >> mWaitSpread;
    }
}

BEGIN_COPYS(WaitSeq)
    COPY_SUPERCLASS(Sequence)
    GET_COPY(WaitSeq)
    if(c && ty != kCopyFromMax){
        COPY_MEMBER(mAvgWaitSecs)
        COPY_MEMBER(mWaitSpread)
    }
END_COPYS

BEGIN_PROPSYNCS(WaitSeq)
    SYNC_PROP(avg_wait_seconds, mAvgWaitSecs)
    SYNC_PROP(wait_spread, mWaitSpread)
    SYNC_SUPERCLASS(Sequence)
END_PROPSYNCS

GroupSeq::GroupSeq() : mChildren(this, kObjListNoNull) {

}

BEGIN_COPYS(GroupSeq)
    COPY_SUPERCLASS(Sequence)
    GET_COPY(GroupSeq)
    if(c && ty != kCopyFromMax){
        COPY_MEMBER(mChildren)
    }
END_COPYS

SAVE_OBJ(GroupSeq, 0x322)

void GroupSeq::Load(BinStream& bs){
    int rev;
    bs >> rev;
    if(rev > 3) MILO_WARN("Can't load new SfxSeq");
    else {
        if(rev > 1) Sequence::Load(bs);
        if(rev < 3){

        }
        else bs >> mChildren;
    }
}

BEGIN_PROPSYNCS(GroupSeq)
    SYNC_PROP(children, mChildren)
    SYNC_SUPERCLASS(Sequence)
END_PROPSYNCS

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

WaitSeqInst::WaitSeqInst(WaitSeq* seq) : SeqInst(seq), mEndTime(-1.0f) {
    float rand = RandomVal(seq->mAvgWaitSecs, seq->mWaitSpread);
    mWaitMs = rand * 1000.0f;
}

void WaitSeqInst::Stop(){
    mEndTime = -1.0f;
}

GroupSeqInst::GroupSeqInst(GroupSeq* seq, bool b) : SeqInst(seq), mSeqs(this) {

}