#include "char/CharHair.h"
#include "char/CharCollide.h"
#include "rndobj/Trans.h"
#include "rndobj/Wind.h"
#include "char/Character.h"

INIT_REVS(CharHair)

CharHair::CharHair() : mStiffness(0.04f), mTorsion(0.1f), mInertia(0.7f), mGravity(1.0f), mWeight(0.5f), mFriction(0.3f), mMinSlack(0.0f), mMaxSlack(0.0f),
    mStrands(this), mReset(1), mSimulate(1), mUsePostProc(1), mMe(this, 0), mWind(this, 0), mCollide(this, kObjListNoNull), unk6c(0) {

}

CharHair::Strand::~Strand(){
    
}

CharHair::~CharHair(){

}

CharHair::Strand::Strand(Hmx::Object* o) : mShowSpheres(0), mShowCollide(0), mShowPose(0), mRoot(o, 0), mAngle(0.0f), mPoints(o), mHookupFlags(0) {
    mBaseMat.Identity();
    mRootMat.Identity();
}

void CharHair::Strand::Load(BinStream& bs){
    bs >> mRoot;
    bs >> mAngle;
    bs >> mPoints;
    bs >> mBaseMat >> mRootMat;
    if(CharHair::gRev > 2){
        bs >> mHookupFlags;
    }
    else mHookupFlags = 0;
}

SAVE_OBJ(CharHair, 0x41B)

void CharHair::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(11, 0);
    Hmx::Object::Load(bs);
    bs >> mStiffness >> mTorsion >> mInertia >> mGravity >> mWeight >> mFriction;
    if(gRev < 8){
        mMinSlack = 0.0f;
        mMaxSlack = 0.0f;
    }
    else bs >> mMinSlack >> mMaxSlack;
    bs >> mStrands;
    bs >> mSimulate;
    if(gRev > 10) bs >> mWind;
}