#include "char/Character.h"
#include "char/CharacterTest.h"
#include "char/CharPollable.h"
#include "rndobj/Mesh.h"
#include "utl/STLHelpers.h"
#include "rndobj/Utl.h"
#include "char/CharDriver.h"
#include "obj/ObjVersion.h"
#include "char/Waypoint.h"
#include "char/CharInterest.h"
#include "char/CharServoBone.h"
#include "char/CharEyes.h"
#include "utl/Symbols.h"

INIT_REVS(Character)

Character* gCharMe;
int CharPollableSorter::sSearchID;

BinStream& operator>>(BinStream&, Character::Lod&);

Character::Lod::Lod(Hmx::Object* obj) : mScreenSize(0.0f), mGroup(obj, 0), mTransGroup(obj, 0) {

}

Character::Lod::Lod(const Character::Lod& lod) : mScreenSize(lod.mScreenSize), mGroup(lod.mGroup), mTransGroup(lod.mTransGroup) {

}

Character::Lod& Character::Lod::operator=(const Character::Lod& lod){
    mScreenSize = lod.mScreenSize;
    mGroup = lod.mGroup;
    mTransGroup = lod.mTransGroup;
    return *this;
}

// fn_8049C858 - charpollablesorter::sort
void CharPollableSorter::Sort(std::vector<RndPollable*>& polls){
    std::vector<Dep*> deps;
    deps.reserve(polls.size());
    int i = polls.size() - 1;
    int old_i = i;
    for(; i >= 0; i--){
        CharPollable* cpoll = dynamic_cast<CharPollable*>(polls[i]);
        if(cpoll){
            Dep dep;
            deps.push_back(&dep);
        }
        else {
            polls[old_i--] = polls[i];
        }
    }
    if(deps.empty()) return;
    else {

    }
}

bool CharPollableSorter::ChangedBy(Dep* d1, Dep* d2){
    if(d1 == d2) return false;
    sSearchID++;
    mTarget = d1;
    return ChangedByRecurse(d2);
}

bool CharPollableSorter::ChangedByRecurse(Dep* d){
    if(!d) return false;
    else if(d == mTarget) return true;
    else if(d->searchID == sSearchID) return false;
    else {
        d->searchID = sSearchID;
        for(std::list<Dep*>::iterator it = d->changedBy.begin(); it != d->changedBy.end(); ++it){
            if(ChangedByRecurse(*it)) return true;
        }
        return false;
    }
}

// fn_8049DD04
void CharPollableSorter::AddDeps(Dep* me, const std::list<Hmx::Object*>& odeps, std::list<Dep*>& toDo, bool changedBy){
    for(std::list<Hmx::Object*>::const_iterator it = odeps.begin(); it != odeps.end(); ++it){
        if(*it){

        }
    }
}

void Character::Init(){ Register(); }
void Character::Terminate(){}

Character::Character() : mLods(this), mLastLod(0), mMinLod(0), mShadow(this, 0), mTransGroup(this, 0), mDriver(0),
    mSelfShadow(0), mSpotCutout(0), mFloorShadow(1), mSphereBase(this, this), mBounding(), mPollState(kCharCreated), mTest(new CharacterTest(this)),
    mFrozen(0), mDrawMode(kCharDrawAll), unk1f4(1), mInterestToForce(), unk1fc(this, 0), mDebugDrawInterestObjects(0) {

}

Character::~Character(){
    UnhookShadow();
    delete mTest;
}

void Character::Enter(){
    mPollState = kCharEntered;
    mMinLod = -1;
    mFrozen = false;
    mLastLod = 0;
    unk1f4 = true;
    mInterestToForce = Symbol();
    RndDir::Enter();
}

void Character::Exit(){
    mPollState = kCharExited;
    RndDir::Exit();
}

void Character::Poll(){
    START_AUTO_TIMER("char_poll");
    if(!mFrozen){
#ifdef VERSION_SZBE69_B8
        if(TheLoadMgr.EditMode()) mTest->Poll();
#endif
        RndDir::Poll();
        unk1f4 = false;
        mPollState = kCharPolled;
    }
}

CharEyes* Character::GetEyes(){
    return Find<CharEyes>("CharEyes.eyes", false);
}

CharServoBone* Character::BoneServo(){
    if(mDriver) return dynamic_cast<CharServoBone*>(mDriver->mBones.Ptr());
    else return 0;
}

void Character::SetSphereBase(RndTransformable* trans){
    if(!trans) trans = this;
    Sphere s18;
    MakeWorldSphere(s18, false);
    Multiply(trans->WorldXfm(), s18.center, s18.center);
    SetSphere(s18);
    mSphereBase = trans;
}

void Character::SetInterestObjects(const ObjPtrList<CharInterest, ObjectDir>& oList, ObjectDir* dir){
    CharEyes* eyes = GetEyes();
    if(eyes){
        eyes->ClearAllInterestObjects();
        for(ObjPtrList<CharInterest, ObjectDir>::iterator it = oList.begin(); it != oList.end(); ++it){
            if(ValidateInterest(*it, dir ? dir : (*it)->Dir())) eyes->AddInterestObject(*it);
        }
    }
}

void Character::ForceBlink(){
    CharEyes* eyes = GetEyes();
    if(eyes) eyes->ForceBlink();
}

void Character::EnableBlinks(bool b1, bool b2){
    CharEyes* eyes = GetEyes();
    if(eyes) eyes->SetEnableBlinks(b1, b2);
}

bool Character::SetFocusInterest(CharInterest* interest, int i){
    CharEyes* eyes = GetEyes();
    if(eyes) return eyes->SetFocusInterest(interest, i);
    else return false;
}

void Character::SetInterestFilterFlags(int flags){
    CharEyes* eyes = GetEyes();
    if(eyes){
        eyes->mInterestFilterFlags = flags;
        eyes->unk15c = true;
    }
}

void Character::ClearInterestFilterFlags(){
    CharEyes* eyes = GetEyes();
    if(eyes){
        eyes->mInterestFilterFlags = eyes->mDefaultFilterFlags;
    }
}

ShadowBone* Character::AddShadowBone(RndTransformable* trans){
    if(!trans) return 0;
    else {
        for(int i = 0; i < mShadowBones.size(); i++){
            if(mShadowBones[i]->mParent == trans) return mShadowBones[i];
        }
        mShadowBones.push_back(new ShadowBone());
        mShadowBones.back()->mParent = trans;
        return mShadowBones.back();
    }
}

void Character::UnhookShadow(){
    for(int i = 0; i < mShadowBones.size(); i++){

    }
    DeleteAll(mShadowBones);
}

void Character::Replace(Hmx::Object* from, Hmx::Object* to){
    RndDir::Replace(from, to);
    if(from == mSphereBase){
        mSphereBase = dynamic_cast<RndTransformable*>(to);
        if(!mSphereBase) mSphereBase = this;
    }
}

void Character::SyncShadow(){
    UnhookShadow();
    if(mShadow){
        if(GetGfxMode() == kOldGfx){
            for(std::vector<RndDrawable*>::iterator it = mShadow->mDraws.begin(); it != mShadow->mDraws.end(); ++it){
                RndMesh* mesh = dynamic_cast<RndMesh*>(*it);
                if(mesh){
                    if(!mesh->mBones.empty()){
                        for(int i = 0; i < mesh->mBones.size(); i++){
                            mesh->SetBone(i, AddShadowBone(mesh->mBones[i]), false);
                        }
                    }
                    else {
                        mesh->SetTransParent(AddShadowBone(mesh), false);
                    }
                }
            }
        }
        VectorRemove(mDraws, mShadow);
    }
}

void Character::SyncObjects(){
    mPollState = kCharSyncObject;
    if(Find<RndMesh>("bone_pelvis.mesh", false)) ConvertBonesToTranses(this, false);
    RndDir::SyncObjects();
    VectorRemove(mDraws, mTransGroup);
    for(int i = 0; i < mLods.size(); i++){
        RndGroup* grp = mLods[i].mGroup;
        VectorRemove(mDraws, grp);
        RndGroup* grp2 = mLods[i].mTransGroup;
        VectorRemove(mDraws, grp2);
    }
    SyncShadow();
    CharPollableSorter sorter;
    sorter.Sort(mPolls);
}

void Character::RemoveFromPoll(RndPollable* poll){
    VectorRemove(mPolls, poll);
}

void Character::AddedObject(Hmx::Object* o){
    if(dynamic_cast<CharPollable*>(o)){
        CharDriver* driver = dynamic_cast<CharDriver*>(o);
        if(driver){
            bool strsmatch = strcmp(driver->Name(), "main.drv") == 0;
            if(strsmatch){
                mDriver = driver;
            }
        }
    }
}

void Character::RemovingObject(Hmx::Object* o){
    if(o == mDriver) mDriver = 0;
    RndDir::RemovingObject(o);
}

void Character::CopyBoundingSphere(Character* c){
    SetSphere(c->mSphere);
    mBounding = c->mBounding;
    if(c->mSphereBase) mSphereBase = c->mSphereBase;
    else mSphereBase = 0;
}

void Character::RepointSphereBase(ObjectDir* dir){
    if(mSphereBase){
        RndTransformable* trans = dir->Find<RndTransformable>(mSphereBase->Name(), false);
        if(trans) mSphereBase = trans;
    }
}

void Character::PreSave(BinStream& bs){ UnhookShadow(); }
SAVE_OBJ(Character, 0x495)

void Character::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0x11, 0);
    if(gRev > 1){
        RndDir::PreLoad(bs);
        if(gRev < 7) mRate = k1_fpb;
    }
    else {
        int somerev;
        bs >> somerev;
        if(somerev > 3){
            RndTransformable::Load(bs);
            RndDrawable::Load(bs);
        }
        ObjectDir::PreLoad(bs);
        PushRev(somerev, this);
    }
    PushRev(packRevs(gAltRev, gRev), this);

}

#pragma push
#pragma dont_inline on
void Character::PostLoad(BinStream& bs){
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    int oldRev = gRev;
    if(gRev > 1){
        RndDir::PostLoad(bs);
        gRev = oldRev;
        if(gRev < 4 || !IsProxy()){
            if(gRev < 9){
                ObjVector<ObjVector<Character::Lod> > ovec(this);
                bs >> ovec;
                if(ovec.size() != 0) mLods = ovec[0];
                else mLods.clear();
            }
            else bs >> mLods;
            bs >> mShadow;
            if(gRev > 2) bs >> mSelfShadow;
            else mSelfShadow = false;
            if(gRev > 4){
                ObjPtr<RndTransformable, ObjectDir> tPtr(this, 0);
                bs >> tPtr;
                mSphereBase = tPtr.Ptr();
            }
            else mSphereBase = this;
            if(gRev > 0xA) bs >> mBounding;
            else mBounding.Zero();
            if(gRev < 0xC){
                if(mSphereBase == this){
                    float rad = mBounding.GetRadius();
                    if(rad == 0.0f){
                        if(GetSphere().GetRadius() != 0.0f){
                            Multiply(GetSphere(), mSphereBase->WorldXfm(), mBounding);
                        }
                    }
                }
            }
            if(gRev > 0xC) bs >> mFrozen;
            if(gRev > 0xE) bs >> mMinLod;
            if(gRev > 0x10) bs >> mTransGroup;
            if(gRev > 9) mTest->Load(bs);
        }
        else if(gRev > 0xF) mTest->Load(bs);
    }
    else {
        int otherrev = PopRev(this);
        int oldotherrev = gRev;
        ObjectDir::PostLoad(bs);
        gRev = oldotherrev;
        if(otherrev > 4) bs >> mEnv;
        if(otherrev > 3){
            gCharMe = otherrev < 6 ? this : 0;
            ObjVector<ObjVector<Character::Lod> > ovec(this);
            bs >> ovec;
            if(ovec.size() != 0) mLods = ovec[0];
            else mLods.clear();
            if(gCharMe){
                for(int i = 0; i < mLods.size(); i++){
                    RndGroup* grp = mLods[i].Group();
                    grp->SetName(MakeString("lod%d.grp", i), this);
                }
            }
            gCharMe = 0;
        }
        else mLods.clear();
        if(otherrev > 6) bs >> mShadow;
    }
    if(gRev < 8){
        float rad = GetSphere().GetRadius();
        for(int i = 0; i < mLods.size(); i++){
            mLods[i].SetScreenSize(mLods[i].ScreenSize() / rad);
        }
    }
}
#pragma pop

BEGIN_COPYS(Character)
    COPY_SUPERCLASS(RndDir)
    CREATE_COPY(Character)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mLods)
            COPY_MEMBER(mLastLod)
            COPY_MEMBER(mMinLod)
            COPY_MEMBER(mShadow)
            COPY_MEMBER(mDriver)
            COPY_MEMBER(mSelfShadow)
            COPY_MEMBER(mSphereBase)
            COPY_MEMBER(mFrozen)
            COPY_MEMBER(mMinLod)
            COPY_MEMBER(mTransGroup)
        }
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(Character)
    HANDLE_ACTION(teleport, Teleport(_msg->Obj<Waypoint>(2)))
    HANDLE(play_clip, OnPlayClip)
    HANDLE_ACTION(calc_bounding_sphere, CalcBoundingSphere())
    HANDLE(copy_bounding_sphere, OnCopyBoundingSphere)
    HANDLE_ACTION(find_interest_objects, FindInterestObjects(_msg->Obj<ObjectDir>(2)))
    HANDLE_ACTION(force_interest, SetFocusInterest(_msg->Obj<CharInterest>(2), false))
    HANDLE_ACTION(force_interest_named, SetFocusInterest(_msg->Sym(2), 0))
    HANDLE_ACTION(enable_blink, if(_msg->Size() > 3) EnableBlinks(_msg->Int(2), _msg->Int(3)); else EnableBlinks(_msg->Int(2), false))
#ifdef VERSION_SZBE69_B8
    HANDLE(list_interest_objects, OnGetCurrentInterests)
    HANDLE_MEMBER_PTR(mTest)
#endif
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x57B)
END_HANDLERS

DataNode Character::OnCopyBoundingSphere(DataArray* da){
    Character* c = da->Obj<Character>(2);
    if(c) CopyBoundingSphere(c);
    return DataNode(0);
}

DataNode Character::OnPlayClip(DataArray* msg){
    if(mDriver){
        int playint = msg->Size() > 3 ? msg->Int(3) : 4;
        MILO_ASSERT(msg->Size()<=4, 0x58B);
        return DataNode(mDriver->Play(msg->Node(2), playint, -1.0f, 1e+30f, 0.0f) != 0);
    }
    else return DataNode(0);
}

void Character::SetDebugDrawInterestObjects(bool b){ mDebugDrawInterestObjects = b; }

DataNode Character::OnGetCurrentInterests(DataArray* da){
    int size = 0;
    CharEyes* eyes = GetEyes();
    if(eyes) size = eyes->mInterests.size();
    DataArrayPtr ptr;
    ptr->Resize(size + 1);
    ptr->Node(0) = DataNode(Symbol());
    for(int i = 0; i < size; i++){
        bool within = i < eyes->mInterests.size();
        CharInterest* interest;
        if(!within){
            interest = ObjOwnerPtr<CharInterest, ObjectDir>(0, 0);
        }
        else {
            interest = eyes->mInterests[i].mInterest;
        }
        ptr->Node(i + 1) = DataNode(Symbol(interest->Name()));
    }
    return DataNode(ptr);
}

BEGIN_CUSTOM_PROPSYNC(Character::Lod)
    SYNC_PROP(screen_size, o.mScreenSize)
    SYNC_PROP(group, o.mGroup)
    SYNC_PROP(trans_group, o.mTransGroup)
END_CUSTOM_PROPSYNC

#include "utl/ClassSymbols.h"
BEGIN_PROPSYNCS(Character)
    SYNC_PROP_SET(sphere_base, mSphereBase, SetSphereBase(_val.Obj<RndTransformable>(0)))
    SYNC_PROP(lods, mLods)
    SYNC_PROP(force_lod, mMinLod)
    SYNC_PROP(trans_group, mTransGroup)
    SYNC_PROP(self_shadow, mSelfShadow)
    SYNC_PROP(bounding, mBounding)
    SYNC_PROP(frozen, mFrozen)
    SYNC_PROP_SET(shadow, mShadow, SetShadow(_val.Obj<RndGroup>(0)))
    SYNC_PROP_SET(driver, mDriver, )
    SYNC_PROP_MODIFY(interest_to_force, mInterestToForce, SetFocusInterest(mInterestToForce, 0))
#ifdef VERSION_SZBE69_B8
    SYNC_PROP(debug_draw_interest_objects, mDebugDrawInterestObjects)
    SYNC_PROP(CharacterTesting, *mTest)
#endif
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS
