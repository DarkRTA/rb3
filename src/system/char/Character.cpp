#include "char/Character.h"
#include "char/CharacterTest.h"
#include "char/CharPollable.h"
#include "rndobj/Mesh.h"
#include "utl/STLHelpers.h"
#include "rndobj/Utl.h"
// #include "char/CharEyes.h"

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