#include "char/CharIKHead.h"

INIT_REVS(CharIKHead)

CharIKHead::CharIKHead() : mPoints(this), mHead(this, 0), mSpine(this, 0), mMouth(this, 0), mTarget(this, 0), mHeadFilter(0.0f, 0.0f, 0.0f), mTargetRadius(0.75f), 
    mHeadMat(0.5f), mOffset(this, 0), mOffsetScale(1.0f, 1.0f, 1.0f), mUpdatePoints(1), mMe(this, 0) {

}

CharIKHead::~CharIKHead(){
    
}

SAVE_OBJ(CharIKHead, 0xF8)

BEGIN_LOADS(CharIKHead)
    LOAD_REVS(bs)
    ASSERT_REVS(3, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(CharWeightable)
    bs >> mHead;
    bs >> mSpine;
    bs >> mMouth;
    bs >> mTarget;
    if(gRev > 1){
        bs >> mTargetRadius;
        bs >> mHeadMat;
    }
    if(gRev > 2){
        bs >> mOffset;
        bs >> mOffsetScale;
    }
    mUpdatePoints = true;
END_LOADS