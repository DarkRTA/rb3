#include "char/CharIKHand.h"
#include "math/Rot.h"

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
                vec = frontTrans->WorldXfm().v;
                if(mOrientation){
                    Hmx::Matrix3 mtx;
                    Normalize(frontTrans->WorldXfm().m, mtx);
                    quat.Set(mtx);
                }
            }
        }
        else {
            for(std::vector<IKTarget>::iterator it = mTargets.begin(); it != mTargets.end(); it++){
                RndTransformable* itTrans = (*it).mTarget;
                float itExtent = (*it).mExtent;
                if(itTrans){
                    Vector3 vec(itTrans->WorldXfm().v);
                    // more stuff happens here
                }
            }
            // more stuff also happens here
        }
        if(mFinger){
            Transform tf;
            tf.v = vec;
            MakeRotMatrix(quat, tf.m);
            Transform tf2;
            Invert(mFinger->WorldXfm(), tf2);
            Multiply(mHand->WorldXfm(), tf2, tf2);
            Multiply(tf2, tf, tf);
            vec = tf.v;
            quat.Set(tf.m);
        }
        Interp(mHand->WorldXfm().v, vec, charWeight, mWorldDst);
    }
}
#pragma pop