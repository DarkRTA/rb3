#include "char/Character.h"
#include "char/CharacterTest.h"

Character::Lod::Lod(Hmx::Object* obj) : mScreenSize(0.0f), mGroup(obj, 0), mGroup2(obj, 0) {

}

Character::Lod::Lod(const Character::Lod& lod) : mScreenSize(lod.mScreenSize), mGroup(lod.mGroup.Owner(), lod.mGroup.Ptr()), mGroup2(lod.mGroup2.Owner(), lod.mGroup2.Ptr()) {
    
}

Character::Lod& Character::Lod::operator=(const Character::Lod& lod){
    mScreenSize = lod.mScreenSize;
    mGroup = lod.mGroup;
    mGroup2 = lod.mGroup2;
    return *this;
}

Character::Character() : mLods(this), mLastLod(0), mMinLod(0), mShadow(this, 0), mTransGroup(this, 0), mDriver(0), 
    mSelfShadow(0), mSpotCutout(0), mFloorShadow(1), mSphereBase(this, this), mBounding(), mPollState(0), mTest(new CharacterTest(this)), 
    mFrozen(0), unk1f0(3), unk1f4(1), mInterestToForce(), unk1fc(this, 0), mDebugDrawInterestObjects(0) {

}

Character::~Character(){
    UnhookShadow();
    delete mTest;
}