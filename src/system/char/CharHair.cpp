#include "char/CharHair.h"
#include "char/CharCollide.h"
#include "rndobj/Trans.h"
#include "rndobj/Wind.h"
#include "char/Character.h"

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