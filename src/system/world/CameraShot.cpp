#include "world/CameraShot.h"
#include "world/Spotlight.h"
#include "world/Crowd.h"
#include "rndobj/Trans.h"

CamShot::CamShot() : mKeyFrames(this), mLoopKeyframe(0), mNear(1.0f), mFar(1000.0f), mFilter(0.9f), mClampHeight(-1.0f), mCategory(), 
    mAnims(this, kObjListNoNull), mPath(this, 0), mDrawOverrides(this, kObjListNoNull), mPathFrame(-1.0f), mPlatformOnly(0),
    mPostProcOverrides(this, kObjListNoNull), mCrowds(this), mGlowSpot(this, 0), unkc4(0.0f, 0.0f, 0.0f), unkd0(0.0f, 0.0f, 0.0f),
    unkdc(0.0f, 0.0f, 0.0f), unke8(0.0f, 0.0f, 0.0f), unkf4(0.0f, 0.0f, 0.0f), unk100(0.0f, 0.0f, 0.0f), unk10c(0), unk110(0),
    mDuration(0.0f), mDisabled(0), unk11c(0), mLooping(1), mUseDepthOfField(0), mPS3PerPixel(0) {

}