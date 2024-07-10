#include "world/Instance.h"
#include "rndobj/Group.h"

void SharedGroup::TryPoll(WorldInstance* inst){
    if(!unkc) unkc = inst;
    else if(unkc != inst) return;
    for(std::list<RndPollable*>::iterator it = mPolls.begin(); it != mPolls.end(); it++){
        (*it)->Poll();
    }
}

void SharedGroup::TryEnter(WorldInstance* inst){
    if(!unkc) unkc = inst;
    else if(unkc != inst) return;
    for(std::list<RndPollable*>::iterator it = mPolls.begin(); it != mPolls.end(); it++){
        (*it)->Enter();
    }
    MsgSource* src = dynamic_cast<MsgSource*>(unkc->Dir());
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

SharedGroup::SharedGroup(RndGroup* group) : mGroup(group), unkc(this, 0) {
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
    unkc = 0;
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

BEGIN_HANDLERS(WorldInstance)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x308)
END_HANDLERS