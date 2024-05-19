#include "char/CharIKHand.h"

CharIKHand::CharIKHand() : mHand(this, 0), mFinger(this, 0), mTargets(this), mConstrainWrist(0), mWristRadians(0.0f), mElbowCollide(this, 0), mClockwise(0) {

}