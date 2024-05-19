#include "char/CharIKFingers.h"

CharIKFingers::CharIKFingers() : mHand(this, 0), mElbow(this, 0), mShoulder(this, 0), mBlendInFrames(0), mBlendOutFrames(0), mResetHandDest(1), mResetCurHandTrans(1),
    mFingerCurledLength(0.85f), mHandMoveForward(1.0f), mHandPinkyRotation(-0.06f), mHandThumbRotation(0.23f), mHandDestOffset(-0.4f),
    mIsRightHand(1), mMoveHand(0), mIsSetup(0), mOutputTrans(this, 0), mKeyboardRefBone(this, 0) {
    mCurHandTrans.Zero();
    mDestHandTrans.Zero();
    mHandKeyboardOffset.Set(0.3f, -6.0f, 0.4f);
}