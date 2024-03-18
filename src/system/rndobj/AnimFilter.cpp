#include "rndobj/AnimFilter.h"

void RndAnimFilter::SetAnim(RndAnimatable* anim){
    mAnim = anim;
    if(mAnim.operator->()){
        mRate = mAnim->mRate;
        mStart = StartFrame();
        mEnd = mAnim->EndFrame();
    }
}


RndAnimFilter::RndAnimFilter() : mAnim(this, 0), mPeriod(0.0f), mStart(0.0f), mEnd(0.0f), mScale(1.0f), mOffset(0.0f), mSnap(0.0f), mJitter(0.0f), mJitterFrame(0.0f), mType(kRange) {
    
}

SAVE_OBJ(RndAnimFilter, 0x4A)
