#include "char/CharInterest.h"

CharInterest::CharInterest() : mMaxViewAngle(20.0f), mPriority(1.0f), mMinLookTime(1.0f), mMaxLookTime(3.0f), mRefractoryPeriod(6.1f), mDartOverride(this, 0), mCategoryFlags(0), mOverrideMinTargetDistance(0), mMinTargetDistanceOverride(35.0f) {
    SyncMaxViewAngle();
}

CharInterest::~CharInterest(){
    
}
