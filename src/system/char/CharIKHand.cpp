#include "char/CharIKHand.h"

CharIKHand::CharIKHand() : mHand(this, 0), mFinger(this, 0), mTargets(this), mConstrainWrist(0), mWristRadians(0.0f), mElbowCollide(this, 0), mClockwise(0) {

}

CharIKHand::~CharIKHand(){

}

#pragma push
#pragma dont_inline on
void CharIKHand::Poll(){
    float charWeight = Weight();
    RndTransformable* trans = mHand;
    if(trans && !mTargets.empty()){
        Vector3 vec(0.0f, 0.0f, 0.0f);
        Hmx::Quat quat(0.0f, 0.0f, 0.0f, 0.0f);
        UpdateHands();
        if(mTargets.size() == 1){
            RndTransformable* frontTrans = mTargets.front().mTarget;
            if(frontTrans){
                
            }
        }
    }
}
#pragma pop