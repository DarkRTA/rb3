#include "synth/Sequence.h"
#include "synth/SeqInst.h"
#include "math/Rand.h"
#include "obj/ObjVector.h"
#include "obj/Task.h"
#include "utl/Symbols.h"

bool sForceSerialSequences;

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
        for(ObjPtrList<SeqInst, class ObjectDir>::iterator it = mInsts.begin(); it != mInsts.end(); ++it){
            // ptmf_scall (*it)
        }
    }
}

Sequence::~Sequence(){
    while(!mInsts.empty()){
        delete mInsts.front();
    }
}

void Sequence::SynthPoll(){
    for(ObjPtrList<SeqInst, class ObjectDir>::iterator it = mInsts.begin(); it != mInsts.end(); it){
        SeqInst* curSeq = *it++;
        curSeq->Poll();
        if(curSeq->mStarted && !curSeq->IsRunning()){
            delete curSeq;
        }
    }
    if(mFaders.Dirty()){
        for(ObjPtrList<SeqInst, class ObjectDir>::iterator it = mInsts.begin(); it != mInsts.end(); ++it){
            (*it)->UpdateVolume();
        }
    }
    if(mInsts.empty()) CancelPolling();
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
    CREATE_COPY(Sequence)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mAvgVol)
            COPY_MEMBER(mVolSpread)
            COPY_MEMBER(mAvgTranspose)
            COPY_MEMBER(mTransposeSpread)
            COPY_MEMBER(mAvgPan)
            COPY_MEMBER(mPanSpread)
            COPY_MEMBER(mCanStop)
        }
    END_COPYING_MEMBERS
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
            ObjPtrList<SeqInst, class ObjectDir>::iterator it = mInsts.begin();
            for(; it != mInsts.end(); ++it){
                if((*it)->IsRunning()) break;
            }
            if(!(it != mInsts.end())) Play(0.0f, 0.0f, 0.0f);
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
    SYNC_PROP_SET(trigger_sound, 0, OnTriggerSound(_val.Int()))
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
    CREATE_COPY(WaitSeq)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mAvgWaitSecs)
            COPY_MEMBER(mWaitSpread)
        }
    END_COPYING_MEMBERS
END_COPYS

BEGIN_PROPSYNCS(WaitSeq)
    SYNC_PROP(avg_wait_seconds, mAvgWaitSecs)
    SYNC_PROP(wait_spread, mWaitSpread)
    SYNC_SUPERCLASS(Sequence)
END_PROPSYNCS

RandomGroupSeq::RandomGroupSeq() : mNumSimul(1), mAllowRepeats(0), mNextIndex(-1), mForceChooseIndex(-1) {

}

SeqInst* RandomGroupSeq::MakeInstImpl(){
    return new RandomGroupSeqInst(this);
}

int RandomGroupSeq::NextIndex(){
    if(mNextIndex == -1 && !mChildren.empty()) PickNextIndex();
    return mNextIndex;
}

void RandomGroupSeq::PickNextIndex(){
    MILO_ASSERT(GetNumSimul() == 1 || Children().size() == 1, 0x1C0);
    if(!sForceSerialSequences) mNextIndex = RandomInt(0, Children().size());
    else mNextIndex = (mNextIndex + 1) % Children().size();
}

void RandomGroupSeq::ForceNextIndex(int i){
    MILO_ASSERT(GetNumSimul() == 1 || Children().size() == 1, 0x1EE);
    if(i < 0 || i > Children().size() - 1){
        MILO_FAIL("index out of bounds for ForceNextIndex (index = %d)", i);
    }
    else {
        for(std::list<int>::iterator it = mPlayHistory.begin(); it != mPlayHistory.end(); it){
            if(mNextIndex == *it++){
                it = mPlayHistory.erase(it);
            }
        }
        mNextIndex = i;
    }
}

BEGIN_COPYS(RandomGroupSeq)
    COPY_SUPERCLASS(GroupSeq)
    CREATE_COPY(RandomGroupSeq)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mNumSimul)
            COPY_MEMBER(mAllowRepeats)
        }
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(RandomGroupSeq, 0x217)

BEGIN_LOADS(RandomGroupSeq)
    int rev;
    bs >> rev;
    if(rev > 2) MILO_WARN("Can't load new RandomGroupSeq");
    else {
        LOAD_SUPERCLASS(GroupSeq)
        bs >> mNumSimul;
        if(rev >= 2) bs >> mAllowRepeats;
    }
END_LOADS

BEGIN_PROPSYNCS(RandomGroupSeq)
    SYNC_PROP(num_simul, mNumSimul)
    SYNC_PROP(allow_repeats, mAllowRepeats)
    SYNC_PROP(force_choose_index, mForceChooseIndex)
    SYNC_SUPERCLASS(GroupSeq)
END_PROPSYNCS

BEGIN_HANDLERS(RandomGroupSeq)
    HANDLE_EXPR(get_next_play_index, NextIndex())
    HANDLE_ACTION(force_next_play_index, ForceNextIndex(_msg->Int(2)))
    HANDLE_SUPERCLASS(Sequence)
    HANDLE_CHECK(0x241)
END_HANDLERS

RandomIntervalGroupSeq::RandomIntervalGroupSeq() : mAvgIntervalSecs(4.0f), mIntervalSpread(2.0f), mMaxSimultaneous(8) {

}

SeqInst* RandomIntervalGroupSeq::MakeInstImpl(){
    return new RandomIntervalGroupSeqInst(this);
}

BEGIN_COPYS(RandomIntervalGroupSeq)
    COPY_SUPERCLASS(GroupSeq)
    CREATE_COPY(RandomIntervalGroupSeq)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mAvgIntervalSecs)
            COPY_MEMBER(mIntervalSpread)
            COPY_MEMBER(mMaxSimultaneous)
        }
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(RandomIntervalGroupSeq, 0x266)

BEGIN_LOADS(RandomIntervalGroupSeq)
    int rev;
    bs >> rev;
    if(rev > 1) MILO_WARN("Can't load new RandomGroupSeq");
    else {
        LOAD_SUPERCLASS(GroupSeq)
        bs >> mAvgIntervalSecs >> mIntervalSpread >> mMaxSimultaneous;
    }
END_LOADS

BEGIN_PROPSYNCS(RandomIntervalGroupSeq)
    SYNC_PROP(max_simul, mMaxSimultaneous)
    SYNC_PROP(avg_interval_secs, mAvgIntervalSecs)
    SYNC_PROP(interval_spread, mIntervalSpread)
    SYNC_SUPERCLASS(GroupSeq)
END_PROPSYNCS

SeqInst* SerialGroupSeq::MakeInstImpl(){
    return new SerialGroupSeqInst(this);
}

SAVE_OBJ(SerialGroupSeq, 0x299)

BEGIN_LOADS(SerialGroupSeq)
    int rev;
    bs >> rev;
    if(rev > 1) MILO_WARN("Can't load new SerialGroupSeq");
    else LOAD_SUPERCLASS(GroupSeq)
END_LOADS

SeqInst* ParallelGroupSeq::MakeInstImpl(){
    return new ParallelGroupSeqInst(this);
}

SAVE_OBJ(ParallelGroupSeq, 0x2BC)

BEGIN_LOADS(ParallelGroupSeq)
    int rev;
    bs >> rev;
    if(rev > 1) MILO_WARN("Can't load new ParallelGroupSeq");
    else LOAD_SUPERCLASS(GroupSeq)
END_LOADS

GroupSeq::GroupSeq() : mChildren(this, kObjListNoNull) {

}

BEGIN_COPYS(GroupSeq)
    COPY_SUPERCLASS(Sequence)
    CREATE_COPY(GroupSeq)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mChildren)
        }
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(GroupSeq, 0x322)

void GroupSeq::Load(BinStream& bs){
    int rev;
    bs >> rev;
    if(rev > 3) MILO_WARN("Can't load new SfxSeq");
    else {
        if(rev >= 2) Sequence::Load(bs);
        if(rev < 3){
            mChildren.clear();
            ObjVector<ObjPtr<Sequence, ObjectDir> > oVec(this);
            bs >> oVec;
            for(int i = 0; i < oVec.size(); i++){
                mChildren.push_back(oVec[i]);
            }
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

void WaitSeqInst::StartImpl(){
    mEndTime = TheTaskMgr.Seconds(TaskMgr::b) * 1000.0f + mWaitMs;
}

void WaitSeqInst::Stop(){
    mEndTime = -1.0f;
}

bool WaitSeqInst::IsRunning(){
    return TheTaskMgr.Seconds(TaskMgr::b) * 1000.0f < mEndTime;
}

GroupSeqInst::GroupSeqInst(GroupSeq* seq, bool b) : SeqInst(seq), mSeqs(this) {
    mSeqs.push_back(ObjPtr<SeqInst, class ObjectDir>(this, 0));
}

GroupSeqInst::~GroupSeqInst(){
    for(ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator it = mSeqs.begin(); it != mSeqs.end(); it++){
        delete *it;
    }
}

void GroupSeqInst::UpdateVolume(){
    for(ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator it = mSeqs.begin(); it != mSeqs.end(); it++){
        if(*it){
            (*it)->SetVolume(mVolume + mRandVol + mOwner->mFaders.GetVal());
        }
    }
}

void GroupSeqInst::SetPan(float f){
    for(ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator it = mSeqs.begin(); it != mSeqs.end(); it++){
        if(*it){
            (*it)->SetPan(f + mRandPan);
        }
    }
}

void GroupSeqInst::SetTranspose(float f){
    for(ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator it = mSeqs.begin(); it != mSeqs.end(); it++){
        if(*it){
            (*it)->SetTranspose(f + mRandTp);
        }
    }
}

SerialGroupSeqInst::SerialGroupSeqInst(SerialGroupSeq* seq) : GroupSeqInst(seq, true), mIt(mSeqs.end()) {

}

void SerialGroupSeqInst::StartImpl(){
    mIt = mSeqs.begin();
    if(*mIt) (*mIt)->Start();
}

void SerialGroupSeqInst::Stop(){
    if(mIt != mSeqs.end()){
        if(*mIt) (*mIt)->Stop();
    }
    ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator curIt = mIt;
    if(curIt != mSeqs.end()) curIt++;
    while(curIt != mSeqs.end()){
        delete *curIt++;
    }
}

bool SerialGroupSeqInst::IsRunning(){
    return mIt != mSeqs.end();
}

void SerialGroupSeqInst::Poll(){
    while(mIt != mSeqs.end()){
        if((*mIt) && (*mIt)->IsRunning()) return;
        if(mIt++ != mSeqs.end()){
            SeqInst* si = (*mIt);
            if(si) si->Start();
        }
    }
}

ParallelGroupSeqInst::ParallelGroupSeqInst(ParallelGroupSeq* seq) : GroupSeqInst(seq, true), mIt(mSeqs.end()) {

}

ParallelGroupSeqInst::~ParallelGroupSeqInst(){

}

void ParallelGroupSeqInst::StartImpl(){
    for(ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator it = mSeqs.begin(); it != mSeqs.end(); it++){
        if(*it) (*it)->Start();
    }
    for(mIt = mSeqs.begin(); mIt != mSeqs.end(); mIt++){
        if((*mIt) && (*mIt)->IsRunning()) return;
    }
}

void ParallelGroupSeqInst::Stop(){
    for(ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator it = mIt; it != mSeqs.end(); it++){
        if(*it) (*it)->Stop();
    }
}

bool ParallelGroupSeqInst::IsRunning(){
    return mIt != mSeqs.end();
}

void ParallelGroupSeqInst::Poll(){
    for(; mIt != mSeqs.end(); mIt++){
        if((*mIt) && (*mIt)->IsRunning()) return;
    }
}

RandomGroupSeqInst::RandomGroupSeqInst(RandomGroupSeq* seq) : GroupSeqInst(seq, true), mIt(mSeqs.end()) {
    mNumSeqs = seq->GetNumSimul();
    int childrenSize = seq->Children().size();
    if(childrenSize < mNumSeqs) mNumSeqs = childrenSize;
    if(mNumSeqs == 1){
        int next = seq->NextIndex();
        seq->PickNextIndex();
        int n = 0;
        for(ObjPtrList<Sequence, class ObjectDir>::iterator it = seq->Children().begin(); it != seq->Children().end(); ++it){
            if(n == next % childrenSize){
                SeqInst* si = (*it)->MakeInst();
                if(si) mSeqs.push_back(ObjPtr<SeqInst, ObjectDir>(si, 0));
                break;
            }
            n++;
        }
        mIt = mSeqs.begin();
    }
    else {
        if(mNumSeqs != 0){

        }
        mIt = mSeqs.begin();
    }
}

RandomGroupSeqInst::~RandomGroupSeqInst(){

}

void RandomGroupSeqInst::StartImpl(){
    for(ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator it = mIt; it != mSeqs.end(); it++){
        if(*it) (*it)->Start();
    }
}

void RandomGroupSeqInst::Stop(){
    for(ObjVector<ObjPtr<SeqInst, class ObjectDir> >::iterator it = mIt; it != mSeqs.end(); it++){
        if(*it) (*it)->Stop();
    }
}

bool RandomGroupSeqInst::IsRunning(){
    return mIt != mSeqs.end();
}

void RandomGroupSeqInst::Poll(){
    for(; mIt != mSeqs.end(); mIt++){
        if((*mIt) && (*mIt)->IsRunning()) return;
    }
}

RandomIntervalGroupSeqInst::RandomIntervalGroupSeqInst(RandomIntervalGroupSeq* seq) : GroupSeqInst(seq, true) {

}

RandomIntervalGroupSeqInst::~RandomIntervalGroupSeqInst(){

}

void Sequence::Init(){
    SfxSeq::Init();
    WaitSeq::Init();
    RandomGroupSeq::Init();
    SerialGroupSeq::Init();
    ParallelGroupSeq::Init();
    RandomIntervalGroupSeq::Init();
}

SfxSeq::SfxSeq(){}

SAVE_OBJ(SfxSeq, 0x511)
