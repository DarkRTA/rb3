#include "char/CharBone.h"
#include "rndobj/TransRemover.h"

INIT_REVS(CharBone);

CharBone::CharBone() : mPositionContext(0), mScaleContext(0), mRotation(TYPE_END), mRotationContext(0), mTarget(this, 0), mWeights(), mTrans(this, 0), mBakeOutAsTopLevel(0) {

}

BEGIN_LOADS(CharBone)
    LOAD_REVS(bs);
    ASSERT_REVS(10, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev < 9){
        RndTransformableRemover remover;
        remover.Load(bs);
    }
    if(gRev > 6) bs >> mPositionContext;
    else {
        bool b;
        bs >> b;
        mPositionContext = b;
    }
    if(gRev > 6) bs >> mScaleContext;
    else if(gRev > 1){
        bool b;
        bs >> b;
        mScaleContext = b;
    }
    bs >> (int&)mRotation;
    if(gRev < 5){
        int i; bs >> i;
    }
    if(gRev < 2){
        mScaleContext = 0;
        mRotation = (CharBone::Type)(mRotation + 1);
    }
    if(gRev < 5 && mRotation > TYPE_END){
        mRotation = TYPE_END;
    }
    if(gRev > 6) bs >> mRotationContext;
    else mRotationContext = mRotation != TYPE_END;
    if(gRev == 3 || gRev == 4 || gRev == 5 || gRev == 6 || gRev == 7){
        int i; bs >> i;
    }
    if(gRev > 3) bs >> mTarget;
    if(gRev == 6){
        int ctx; bs >> ctx;
        if(mPositionContext != 0) mPositionContext = ctx;
        if(mScaleContext != 0) mScaleContext = ctx;
        if(mRotationContext != 0) mRotationContext = ctx;
    }
    if(gRev > 7) bs >> mWeights;
    if(gRev > 8) bs >> mTrans;
    if(gRev > 9) bs >> mBakeOutAsTopLevel;
END_LOADS