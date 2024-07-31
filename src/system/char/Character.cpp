#include "char/Character.h"
#include "char/CharacterTest.h"
#include "char/CharPollable.h"
#include "rndobj/Mesh.h"
#include "utl/STLHelpers.h"
#include "rndobj/Utl.h"
#include "char/CharDriver.h"
#include "obj/ObjVersion.h"
// #include "char/CharEyes.h"

INIT_REVS(Character)

Character* gCharMe;

BinStream& operator>>(BinStream&, Character::Lod&);

Character::Lod::Lod(Hmx::Object* obj) : mScreenSize(0.0f), mGroup(obj, 0), mGroup2(obj, 0) {

}

Character::Lod::Lod(const Character::Lod& lod) : mScreenSize(lod.mScreenSize), mGroup(lod.mGroup), mGroup2(lod.mGroup2) {
    
}

Character::Lod& Character::Lod::operator=(const Character::Lod& lod){
    mScreenSize = lod.mScreenSize;
    mGroup = lod.mGroup;
    mGroup2 = lod.mGroup2;
    return *this;
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
        if(TheLoadMgr.EditMode()) mTest->Poll();
        RndDir::Poll();
        unk1f4 = false;
        mPollState = kCharPolled;
    }
}

CharEyes* Character::GetEyes(){
    // return Find<CharEyes>("CharEyes.eyes", false);
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
    DeleteRange(mShadowBones.begin(), mShadowBones.end());
    mShadowBones.clear();
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
        RndGroup* grp2 = mLods[i].mGroup2;
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
    mSphere = c->mSphere;
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