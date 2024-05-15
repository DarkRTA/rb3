#include "char/CharLookAt.h"

CharLookAt::CharLookAt() : mSource(this, 0), mPivot(this, 0), mDest(this, 0), mHalfTime(0.0f), mMinYaw(-80.0f), mMaxYaw(80.0f), mMinPitch(-80.0f), mMaxPitch(80.0f),
    mMinWeightYaw(-1.0f), mMaxWeightYaw(1.0f), mWeightYawSpeed(10000.0f), unk6c(1e+29f), unk70(0.0f), unk74(0.0f), unk78(1.0f), mSourceRadius(0.0f), vec80(0.0f, 0.0f, 0.0f),
    mShowRange(0), mTestRange(0), mTestRangePitch(0.5f), mTestRangeYaw(0.5f), mAllowRoll(1), unkb1(0), mEnableJitter(0), mYawJitterLimit(0.0f), mPitchJitterLimit(0.0f) {
    SyncLimits();
}