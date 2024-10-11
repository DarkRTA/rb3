#include "char/CharIKHand.h"
#include "math/Rot.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKHand)

CharIKHand::CharIKHand() : mHand(this, 0), mFinger(this, 0), mTargets(this), mOrientation(1), mStretch(1), mScalable(0), mMoveElbow(1),
    mElbowSwing(0.0f), mAlwaysIKElbow(0), mAAPlusBB(0.0f), mConstrainWrist(0), mWristRadians(0.0f), mElbowCollide(this, 0), mClockwise(0) {

}

CharIKHand::~CharIKHand(){

}

#pragma push
#pragma dont_inline on
// fn_804E02E4
void CharIKHand::Poll(){
    float charWeight = Weight();
    RndTransformable* trans = mHand;
    if(!trans || mTargets.empty()) return;
    Vector3 vec(0.0f, 0.0f, 0.0f);
    Hmx::Quat quat(0.0f, 0.0f, 0.0f, 0.0f);
    UpdateHand();
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

// fn_804E09B4
void CharIKHand::IKElbow(RndTransformable* trans1, RndTransformable* trans2){
    if(!trans1 || !trans2) return;
    Vector3 v100;
    PullShoulder(v100, trans2->WorldXfm(), mWorldDst, mAAPlusBB);
    Transform tf78(trans2->WorldXfm());
    tf78.v += v100;
    trans2->SetWorldXfm(tf78);
    float loc210 = unk64 * (DistanceSquared(trans2->WorldXfm().v, mWorldDst) - mInv2ab);
    ClampEq(loc210, -1.0f,1.0f);
    float sqrted = std::sqrt(-(loc210 * loc210 - 1.0f));
    trans1->DirtyLocalXfm().m.Set(0.0f, 0.0f, 0.0f, -sqrted, 0.0f, 0.0f, sqrted, 0.0f, 1.0f);
    Vector3 v10c, v118;
    Multiply(trans2->WorldXfm(), mHand->WorldXfm().v, v118);
    Multiply(trans2->WorldXfm(), mWorldDst, v10c);
    if(mElbowSwing > 0){
        Vector2 v200(v118.y, v118.z);
        Vector2 v208(v10c.y, v10c.z);
        float max208 = Max(LengthSquared(v208), 16.0f);
        float max200 = Max(LengthSquared(v200), 16.0f);
        float sqrted2 = std::sqrt(max200 * max208);
        float crossed = Cross(v208, v200);
        float clamped = Clamp(-mElbowSwing, mElbowSwing, crossed / sqrted2);
        Transform& dirty_temp = trans1->DirtyLocalXfm();
        RotateAboutX(dirty_temp.m, -clamped, dirty_temp.m);
        Multiply(trans2->WorldXfm(), mHand->WorldXfm().v, v118);
    }
    Hmx::Quat q128;
    MakeRotQuat(v118, v10c, q128);
    Hmx::Matrix3 ma0;
    MakeRotMatrix(q128, ma0);
    Multiply(ma0, trans2->LocalXfm().m, trans2->DirtyLocalXfm().m);
    if(mElbowCollide){
        PullShoulder(v100, trans2->WorldXfm(), mWorldDst, mAAPlusBB);
        Transform tfd0(trans2->WorldXfm());
        tfd0.v += v100;
        trans2->SetWorldXfm(tfd0);
        if(mElbowCollide->GetShape() != CharCollide::kSphere) MILO_WARN("%s: elbow collision object not sphere.\n", Name());
        else {
            Vector3 v134(mElbowCollide->WorldXfm().v);
            float sphereRadius = mElbowCollide->Radius();
            if(Distance(v134, trans1->WorldXfm().v) < sphereRadius){
                Vector3 v140(trans2->WorldXfm().v);
                v140 -= mWorldDst;
                Vector3 v14c, v158;
                Normalize(v140, v158);
                Subtract(trans1->WorldXfm().v, mWorldDst, v14c);
                Scale(v158, Dot(v14c, v158), v140);
                Add(v140, mWorldDst, v140);
                Vector3 v164(trans1->WorldXfm().v);
                v164 -= v140;
                float v164len = Length(v164);
                Vector3 v170(trans2->WorldXfm().v);
                v170 -= v140;
                Normalize(v170, v170);
                Vector3 v17c;
                Add(v140, v170, v17c);
                Subtract(v140, v134, v17c);
                Scale(v170, Dot(v170, v17c), v17c);
                Add(v134, v17c, v17c);
                float a = Distance(v17c, v134);
                MILO_ASSERT(a <= sphereRadius, 0x1A1);
                float sqrted2 = std::sqrt(sphereRadius * sphereRadius - a * a);
                v134.Set(v17c.x, v17c.y, v17c.z);
                float dist134and140 = Distance(v134,v140);
                float d10 = (dist134and140 * dist134and140 + -(a * a - sqrted2 * sqrted2)) / (dist134and140 * 2.0f);
                float sqrted3 = std::sqrt(-(d10 * d10 - sqrted2 * sqrted2));
                float asined = std::asin(sqrted3 / v164len);
                if(IsNaN(asined)) return;
                Vector3 v188(v134);
                v188 -= v140;
                Normalize(v188, v188);
                Scale(v188, v164len, v188);
                double half = asined / 2.0;
                float sine = sin(half);
                float cosine = cos(half);
                Hmx::Quat q198(v188.x, v188.y, v188.z, 0.0f);
                Hmx::Quat q1a8(v170.x * sine, v170.y * sine, v170.z* sine, cosine);
                Hmx::Quat q1b8;
                Multiply(q198, q1a8, q1b8);
                Multiply(q1b8, q1a8, q1b8);
                Vector3 v1c4(q1b8.x, q1b8.y, q1b8.z);
                Add(v1c4, v140, v1c4);
                Multiply(q1a8, q198, q1b8);
                Multiply(q1a8, q1b8, q1b8);
                Vector3 v1d0(q1b8.x, q1b8.y, q1b8.z);
                Add(v1d0, v140, v1d0);
                Vector3 v1dc, v1e8;
                Multiply(trans2->WorldXfm(), trans1->WorldXfm().v, v1e8);
                if(mClockwise) Multiply(trans2->WorldXfm(), v1d0, v1dc);
                else Multiply(trans2->WorldXfm(), v1c4, v1dc);
                Hmx::Quat q1f8;
                MakeRotQuat(v1e8, v1dc, q1f8);
                Hmx::Matrix3 mf4;
                MakeRotMatrix(q1f8, mf4);
                Multiply(mf4, trans2->LocalXfm().m, trans2->DirtyLocalXfm().m);
                Multiply(trans1->WorldXfm(), mHand->WorldXfm().v, v1e8);
                Multiply(trans1->WorldXfm(), mWorldDst, v1dc);
                MakeRotQuat(v1e8, v1dc, q1f8);
                MakeRotMatrix(q1f8, mf4);
                Multiply(mf4, trans1->LocalXfm().m, trans1->DirtyLocalXfm().m);
            }
        }
    }
    PullShoulder(v100, trans2->WorldXfm(), mWorldDst, mAAPlusBB);
    tf78 = trans2->WorldXfm();
    tf78.v += v100;
    trans2->SetWorldXfm(tf78);
}
#pragma pop

void CharIKHand::SetHand(RndTransformable* t){
    mHand = t;
    mHandChanged = true;
}

void CharIKHand::UpdateHand(){
    if(mScalable || mHandChanged){
        MeasureLengths();
        mHandChanged = false;
    }
}

void CharIKHand::MeasureLengths(){
    if(mHand){
        if(mHand->TransParent()){
            if(mHand->TransParent()->TransParent()){
                float len = Length(mHand->mLocalXfm.v);
                float parentlen = Length(mHand->TransParent()->mLocalXfm.v);
                unk64 = len * 2.0f * parentlen;
                mInv2ab = parentlen * parentlen + (len * len + 0.0f);
                if(unk64 != 0.0f) unk64 = 1.0f / unk64;
                mAAPlusBB = len + parentlen;
            }
        }
    }
}

SAVE_OBJ(CharIKHand, 0x2A8)

BEGIN_LOADS(CharIKHand)
    LOAD_REVS(bs)
    ASSERT_REVS(0xC, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(CharWeightable)
    bs >> mHand;
    if(gRev > 4) bs >> mFinger;
    else mFinger = 0;
    if(gRev < 3){
        ObjPtr<RndTransformable, ObjectDir> tPtr(this, 0);
        bs >> tPtr;
        mTargets.clear();
        mTargets.push_back(IKTarget(ObjPtr<RndTransformable, ObjectDir>(tPtr), 0));
    }
    else if(gRev < 0xB){
        ObjPtrList<RndTransformable, ObjectDir> tList(this, kObjListNoNull);
        bs >> tList;
        mTargets.clear();
        for(ObjPtrList<RndTransformable, ObjectDir>::iterator it = tList.begin(); it != tList.end(); ++it){
            ObjPtr<RndTransformable, ObjectDir> tPtr(this, *it);
            mTargets.push_back(IKTarget(ObjPtr<RndTransformable, ObjectDir>(tPtr), 0));
        }
    }
    else bs >> mTargets;

    bs >> mOrientation;
    bs >> mStretch;
    if(gRev > 1) bs >> mScalable;
    else mScalable = false;

    if(gRev > 3) bs >> mMoveElbow;
    else mMoveElbow = true;

    if(gRev > 5) bs >> mElbowSwing;
    else mElbowSwing = 0.0f;

    if(gRev > 6) bs >> mAlwaysIKElbow;
    if(gRev > 7){
        bs >> mConstrainWrist;
        bs >> mWristRadians;
    }
    if(gRev == 9){
        String s;
        bs >> s;
        bool b;
        bs >> b;
    }
    if(gRev > 0xB){
        bs >> mElbowCollide;
        bs >> mClockwise;
    }
    SetHand(mHand);
END_LOADS

BEGIN_COPYS(CharIKHand)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharIKHand)
    BEGIN_COPYING_MEMBERS
        SetHand(c->mHand);
        COPY_MEMBER(mHand)
        COPY_MEMBER(mTargets)
        COPY_MEMBER(mOrientation)
        COPY_MEMBER(mStretch)
        COPY_MEMBER(mScalable)
        COPY_MEMBER(mMoveElbow)
        COPY_MEMBER(mElbowSwing)
        COPY_MEMBER(mAlwaysIKElbow)
        COPY_MEMBER(mConstrainWrist)
        COPY_MEMBER(mTargets)
        COPY_MEMBER(mElbowCollide)
        COPY_MEMBER(mClockwise)
    END_COPYING_MEMBERS
END_COPYS

BinStream& operator>>(BinStream& bs, CharIKHand::IKTarget& t){
    bs >> t.mTarget;
    bs >> t.mExtent;
    return bs;
}

BEGIN_HANDLERS(CharIKHand)
    HANDLE_ACTION(measure_lengths, MeasureLengths())
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x33D)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(CharIKHand::IKTarget)
    SYNC_PROP(target, o.mTarget)
    SYNC_PROP(extent, o.mExtent)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharIKHand)
    SYNC_PROP_SET(hand, mHand, SetHand(_val.Obj<RndTransformable>()))
    SYNC_PROP(finger, mFinger)
    SYNC_PROP(targets, mTargets)
    SYNC_PROP(orientation, mOrientation)
    SYNC_PROP(stretch, mStretch)
    SYNC_PROP(scalable, mScalable)
    SYNC_PROP(move_elbow, mMoveElbow)
    SYNC_PROP(elbow_swing, mElbowSwing)
    SYNC_PROP(always_ik_elbow, mAlwaysIKElbow)
    SYNC_PROP(constrain_wrist, mConstrainWrist)
    SYNC_PROP(wrist_radians, mWristRadians)
    SYNC_PROP(elbow_collide, mElbowCollide)
    SYNC_PROP(clockwise, mClockwise)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS
