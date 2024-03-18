#include "rndobj/AnimFilter.h"

INIT_REVS(RndAnimFilter);

void RndAnimFilter::SetAnim(RndAnimatable* anim){
    mAnim = anim;
    if(mAnim.operator->()){
        mRate = mAnim->mRate;
        mStart = mAnim->StartFrame();
        mEnd = mAnim->EndFrame();
    }
}


RndAnimFilter::RndAnimFilter() : mAnim(this, 0), mPeriod(0.0f), mStart(0.0f), mEnd(0.0f), mScale(1.0f), mOffset(0.0f), mSnap(0.0f), mJitter(0.0f), mJitterFrame(0.0f), mType(kRange) {
    
}

SAVE_OBJ(RndAnimFilter, 0x4A)

void RndAnimFilter::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    Hmx::Object::Load(bs);
    RndAnimatable::Load(bs);
    bs >> mAnim >> mScale >> mOffset >> mStart >> mEnd;
    if(gRev != 0){
        int i;
        bs >> i;
        mType = (RndAnimFilter::Type)i;
        bs >> mScale;
    }
    else {
        unsigned char c;
        bs >> c;
        mType = (RndAnimFilter::Type)(c != 0);
    }
    if(gRev > 1){
        bs >> mSnap >> mJitter;
    }
}
