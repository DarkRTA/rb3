#include "char/CharInterest.h"
#include "math/MathFuncs.h"

CharInterest::CharInterest() : mMaxViewAngle(20.0f), mPriority(1.0f), mMinLookTime(1.0f), mMaxLookTime(3.0f), mRefractoryPeriod(6.1f), mDartOverride(this, 0), mCategoryFlags(0), mOverrideMinTargetDistance(0), mMinTargetDistanceOverride(35.0f) {
    SyncMaxViewAngle();
}

CharInterest::~CharInterest(){
    
}

void CharInterest::SyncMaxViewAngle(){
    mMaxViewAngleCos = cos_f(mMaxViewAngle * 0.017453292f);
}

SAVE_OBJ(CharInterest, 0x52);

BEGIN_HANDLERS(CharInterest)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x141)
END_HANDLERS
