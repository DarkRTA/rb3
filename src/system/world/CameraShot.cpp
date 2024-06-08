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

#pragma push
#pragma dont_inline on
BEGIN_COPYS(CamShot)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    CREATE_COPY(CamShot)
    BEGIN_COPYING_MEMBERS
        mKeyFrames.clear();
        for(int i = 0; i != c->mKeyFrames.size(); i++){
            mKeyFrames.push_back(CamShotFrame(this, c->mKeyFrames[i]));
        }
        mCrowds.clear();
        for(int i = 0; i != c->mCrowds.size(); i++){
            mCrowds.push_back(CamShotCrowd(this, c->mCrowds[i]));
        }
        COPY_MEMBER(mNear)
        COPY_MEMBER(mFar)
        COPY_MEMBER(mUseDepthOfField)
        COPY_MEMBER(mFilter)
        COPY_MEMBER(mClampHeight)
        COPY_MEMBER(mPath)
        COPY_MEMBER(mPlatformOnly)
        COPY_MEMBER(mCategory)
        COPY_MEMBER(unk5c)
        COPY_MEMBER(unk6c)
        COPY_MEMBER(unk6c)
        COPY_MEMBER(unk64)
        COPY_MEMBER(mLooping)
        COPY_MEMBER(mLoopKeyframe)
        COPY_MEMBER(mGlowSpot)
        COPY_MEMBER(mDrawOverrides)
        COPY_MEMBER(mPostProcOverrides)
        COPY_MEMBER(mPS3PerPixel)
        COPY_MEMBER(unk11c)
        COPY_MEMBER(mAnims)
        CacheFrames();
    END_COPYING_MEMBERS
END_COPYS
#pragma pop