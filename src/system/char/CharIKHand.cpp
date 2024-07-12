#include "char/CharIKHand.h"
#include "math/Rot.h"

CharIKHand::CharIKHand() : mHand(this, 0), mFinger(this, 0), mTargets(this), mOrientation(1), mStretch(1), mScalable(0), mMoveElbow(1),
    mElbowSwing(0.0f), mAlwaysIKElbow(0), mAAPlusBB(0.0f), mConstrainWrist(0), mWristRadians(0.0f), mElbowCollide(this, 0), mClockwise(0) {

}

CharIKHand::~CharIKHand(){

}

#pragma push
#pragma dont_inline on
void CharIKHand::Poll(){
    float charWeight = Weight();
    RndTransformable* trans = mHand;
    if(!trans || mTargets.empty()) return;
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
        float sumfloat = 0.0f;
        float* locfloats;
        float* startlocfloats = locfloats;
        for(std::vector<IKTarget>::iterator it = mTargets.begin(); it != mTargets.end(); it++){
            RndTransformable* itTrans = (*it).mTarget;
            float itExtent = (*it).mExtent;
            if(itTrans){
                Vector3 vec(itTrans->WorldXfm().v);
                if(itExtent <= 0.0f){
                    *locfloats = 144.0f / Max(0.001f, LengthSquared(vec));
                }
                else if(itExtent < -vec.z){
                    *locfloats = 0.001f;
                }
                else {
                    vec.z = 0.0f;
                    *locfloats = 144.0f / Max(0.001f, LengthSquared(vec));
                }

                sumfloat += *locfloats++;
            }
        }
        if(sumfloat < 1.0f){
            charWeight = charWeight - (charWeight * (1.0f - sumfloat));
        }

        locfloats = startlocfloats;
        for(std::vector<IKTarget>::iterator it = mTargets.begin(); it != mTargets.end(); it++){
            RndTransformable* itTrans = (*it).mTarget;
            if(itTrans){
                float curFloat = *locfloats;
                const Transform& worldtf = itTrans->WorldXfm();
                ScaleAddEq(vec, worldtf.v, curFloat / sumfloat);
                if(mOrientation){
                    Hmx::Matrix3 m100;
                    Normalize(worldtf.m, m100);
                    Hmx::Quat q268(m100);
                    ScaleAddEq(quat, q268, curFloat / sumfloat);
                }
            }
            locfloats++;
        }
        if(mOrientation) Normalize(quat,quat);
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
    RndTransformable* parent2 = 0;
    RndTransformable* parent1 = mHand->TransParent();
    if(!mMoveElbow) parent1 = 0;
    if(charWeight != 0 || mAlwaysIKElbow){
        if(parent1){
            parent2 = parent1->TransParent();
            if(!parent2) parent1 = 0;
        }
        IKElbow(parent1, parent2);
    }
    if(charWeight != 0 && (!parent1 || mOrientation || mStretch)){
        Transform tf(mHand->WorldXfm());
        if(!parent1 || mStretch){
            tf.v = mWorldDst;
        }
        if(mOrientation){
            if(charWeight < 1.0f){
                Hmx::Quat q(mHand->WorldXfm().m);
                Interp(q, quat, charWeight, quat);
            }
            MakeRotMatrix(quat, tf.m);
        }
        mHand->SetWorldXfm(tf);
    }

    if(mConstrainWrist && charWeight > 0.0f && parent1){
        Vector3 v284(mFinger->WorldXfm().v);
        Hmx::Matrix3 m1b4(parent1->WorldXfm().m);
        Hmx::Matrix3 m1d8(mHand->WorldXfm().m);
        Vector3 v290, v29c, v2a8;
        v290 = m1d8.x;
        v29c = m1d8.y;
        v2a8 = m1d8.z;
        float acosdot = std::acos(Dot(m1b4.x, v2a8)) - 1.570796370506287f;
        float rads = mWristRadians;
        if(Abs(acosdot) > rads){
            if(acosdot > 0.0f) acosdot -= rads;
            else acosdot += rads;
            Hmx::Quat q2b8;
            Transform tf208;
            Hmx::Matrix3 m22c;
            q2b8.Set(v29c, acosdot);
            MakeRotMatrix(q2b8, m22c);
            Multiply(v290, m22c, v290);
            Cross(v290, v29c, v2a8);
            tf208.m.Set(v290, v29c, v2a8);
            tf208.v = mHand->WorldXfm().v;
            mHand->SetWorldXfm(tf208);
            Vector3 v2c8(mFinger->WorldXfm().v);
            Subtract(v2c8, v284, v2c8);
            Subtract(tf208.v, v2c8, tf208.v);
            mHand->SetWorldXfm(tf208);
            mWorldDst = tf208.v;
            IKElbow(parent1, parent2);
            mHand->SetWorldXfm(tf208);
        }
    }
}
#pragma pop