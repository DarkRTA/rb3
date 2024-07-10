#include "world/Instance.h"
#include "rndobj/Group.h"
#include "obj/ObjVersion.h"

INIT_REVS(WorldInstance)

void SharedGroup::TryPoll(WorldInstance* inst){
    if(!mPollMaster) mPollMaster = inst;
    else if(mPollMaster != inst) return;
    for(std::list<RndPollable*>::iterator it = mPolls.begin(); it != mPolls.end(); it++){
        (*it)->Poll();
    }
}

void SharedGroup::TryEnter(WorldInstance* inst){
    if(!mPollMaster) mPollMaster = inst;
    else if(mPollMaster != inst) return;
    for(std::list<RndPollable*>::iterator it = mPolls.begin(); it != mPolls.end(); it++){
        (*it)->Enter();
    }
    MsgSource* src = dynamic_cast<MsgSource*>(mPollMaster->Dir());
    if(src){
        MsgSource* src2 = dynamic_cast<MsgSource*>(mGroup->Dir());
        if(src2) src2->ChainSource(src, 0);
    }
}

void SharedGroup::Draw(const Transform& tf){
    mGroup->SetWorldXfm(tf);
    mGroup->Draw();
}

bool SharedGroup::Collide(const Transform& tf, const Segment& s, float& f, Plane& pl){
    mGroup->SetWorldXfm(tf);
    return mGroup->Collide(s, f, pl);
}

float SharedGroup::DistanceToPlane(const Transform& tf, const Plane& pl, Vector3& v){
    mGroup->SetWorldXfm(tf);
    return mGroup->GetDistanceToPlane(pl, v);
}

bool SharedGroup::MakeWorldSphere(const Transform& tf, Sphere& s){
    mGroup->SetWorldXfm(tf);
    return mGroup->MakeWorldSphere(s, true);
}

SharedGroup::SharedGroup(RndGroup* group) : mGroup(group), mPollMaster(this, 0) {
    AddPolls(group);
}

SharedGroup::~SharedGroup(){
    
}

void SharedGroup::AddPolls(RndGroup* grp){
    for(ObjPtrList<Hmx::Object, ObjectDir>::iterator it = grp->mObjects.begin(); it != grp->mObjects.end(); ++it){
        RndPollable* poll = dynamic_cast<RndPollable*>(*it);
        if(poll) mPolls.push_back(poll);
        else {
            RndGroup* group = dynamic_cast<RndGroup*>(*it);
            if(group) AddPolls(group);
        }
    }
}

void SharedGroup::ClearPollMaster(){
    mPollMaster = 0;
}

WorldInstance::WorldInstance() : mDir(), mSharedGroup(0), mSharedGroup2(0) {

}

WorldInstance::~WorldInstance(){
    if(mSharedGroup2) mSharedGroup2->ClearPollMaster();
    delete mSharedGroup2;
}

void WorldInstance::Poll(){
    if(mSharedGroup) mSharedGroup->TryPoll(this);
    RndDir::Poll();
}

void WorldInstance::Enter(){
    if(mSharedGroup) mSharedGroup->TryEnter(this);
    RndDir::Enter();
}

void WorldInstance::DrawShowing(){
    RndDir::DrawShowing();
    if(mSharedGroup) mSharedGroup->Draw(WorldXfm());
}

SAVE_OBJ(WorldInstance, 0x10A)

void WorldInstance::PreSave(BinStream& bs){}

void WorldInstance::PreLoad(BinStream& bs){
    if(IsProxy()) DeleteObjects();
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    if(gRev != 0){
        FilePath fp;
        bs >> fp;
        PreLoadInlined(fp, true, kInline3);
    }
    else bs >> mDir;
    PushRev(packRevs(gAltRev, gRev), this);
    RndDir::PreLoad(bs);
    if(mProxyFile.length() != 0){
        MILO_WARN("WorldInstance %s was created as RndDir. Object needs to be deleted and recreated.", Name());
    }
}

void WorldInstance::Replace(Hmx::Object* from, Hmx::Object* to){
    RndDir::Replace(from, to);
}

BEGIN_HANDLERS(WorldInstance)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x308)
END_HANDLERS