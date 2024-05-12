#include "char/CharBone.h"

CharBone::CharBone() : mPositionContext(0), mScaleContext(0), mRotation(TYPE_END), mRotationContext(0), mTarget(this, 0), mWeights(), mTrans(this, 0), mBakeOutAsTopLevel(0) {

}