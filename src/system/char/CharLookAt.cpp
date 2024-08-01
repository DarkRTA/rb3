#include "char/CharLookAt.h"
#include "math/MathFuncs.h"
#include "math/Rot.h"
#include "math/Rand.h"
#include "obj/Task.h"

bool CharLookAt::sDisableJitter;

CharLookAt::CharLookAt() : mSource(this, 0), mPivot(this, 0), mDest(this, 0), mHalfTime(0.0f), mMinYaw(-80.0f), mMaxYaw(80.0f), mMinPitch(-80.0f), mMaxPitch(80.0f),
    mMinWeightYaw(-1.0f), mMaxWeightYaw(1.0f), mWeightYawSpeed(10000.0f), unk6c(1e+29f,0.0f,0.0f), unk78(1.0f), mSourceRadius(0.0f), vec80(0.0f, 0.0f, 0.0f),
    mShowRange(0), mTestRange(0), mTestRangePitch(0.5f), mTestRangeYaw(0.5f), mAllowRoll(1), unkb1(0), mEnableJitter(0), mYawJitterLimit(0.0f), mPitchJitterLimit(0.0f) {
    SyncLimits();
}

CharLookAt::~CharLookAt(){

}

// fn_804ED41C
void CharLookAt::Enter(){
    unk6c.Set(1e+29f,0.0f,0.0f);
    if(mPivot){
        mPivot->DirtyLocalXfm().m.Identity();
    }
    RndPollable::Enter();
}

#pragma push
#pragma dont_inline on
void CharLookAt::Poll(){
    RndTransformable* srcTrans = GetSource();
    float deltasecs = TheTaskMgr.DeltaSeconds();
    if(mDest && mPivot){
        if(mPivot->TransParent() && srcTrans && deltasecs >= 0.0f){
            Vector3 ve4;
            Subtract(mDest->WorldXfm().v, srcTrans->WorldXfm().v, ve4);
            float charweight = Weight();
            if(mMinWeightYaw >= 0.0f){
                Vector3 vf0(srcTrans->WorldXfm().m.y);
                Normalize(vf0, vf0);
                Vector3 vfc(ve4);
                vfc.z = 0;
                vf0.z = 0;
                float times = (vf0 * vfc);
                float clamped = Clamp(-1.0f,1.0f, times / (Length(vf0) * Length(vfc)));
                float clamped2 = Clamp(0.0f,1.0f, mMaxWeightYaw - (std::acos(clamped) / (mMaxWeightYaw - mMinWeightYaw)));
                float loc13c = (clamped2 - unk78) / deltasecs;
                if(MinEq(loc13c, mWeightYawSpeed)){
                    clamped2 = loc13c * deltasecs + unk78;
                }
                charweight *= clamped2;
                unk78 = clamped2;
            }
            if(charweight != 0.0f){
                Vector3 v108(0.0f,0.0f,0.0f);
                if(mSourceRadius > 0.0f){
                    if(TheTaskMgr.DeltaSeconds() > 0.0f){
                        Interp(vec80, srcTrans->WorldXfm().m.y, 0.1f, vec80);
                    }
                    Subtract(srcTrans->WorldXfm().m.y, vec80, v108);
                    float v108sq = LengthSquared(v108);
                    float srcrad = mSourceRadius * DEG2RAD;
                    if(srcrad * srcrad < v108sq){
                        v108 *= srcrad / std::sqrt(v108sq);
                    }
                }
                if(srcTrans != mPivot){
                    Transform tf90(mPivot->WorldXfm());
                    Hmx::Quat q118;
                    MakeRotQuat(srcTrans->WorldXfm().m.y, ve4, q118);
                    Hmx::Matrix3 mb4;
                    MakeRotMatrix(q118, mb4);
                    Multiply(tf90.m, mb4, tf90.m);
                    mPivot->SetWorldXfm(tf90);
                    Subtract(mDest->WorldXfm().v, srcTrans->WorldXfm().v, ve4);
                    MakeRotQuat(srcTrans->WorldXfm().m.y, ve4, q118);
                    MakeRotMatrix(q118, mb4);
                    Multiply(tf90.m.y, mb4, ve4);
                }
                else Normalize(ve4, ve4);
                Multiply(mPivot->TransParent()->WorldXfm().m, ve4, ve4);
                Normalize(ve4, ve4);
                unkb1 = mBounds.Clamp(ve4);
                Normalize(ve4, ve4);
                if(unk6c.x != 1e+29f && mHalfTime != 0.0f){
                    Interp(unk6c, ve4, deltasecs / (deltasecs + mHalfTime), ve4);
                }
                unk6c = ve4;
                if(mTestRange){
                    float loc140, loc144;
                    Interp(mBounds.mMin.z, mBounds.mMax.z, mTestRangeYaw, loc140);
                    Interp(mBounds.mMin.x, mBounds.mMax.x, mTestRangePitch, loc144);
                    ve4.Set(loc144, mBounds.mMin.y, loc140);
                }
                else if(mShowRange){
                    charweight = 1.0f;
                    switch(((int)TheTaskMgr.Seconds(TaskMgr::b)) & 7){
                        case 0:
                            ve4.Set(mBounds.mMin.x, mBounds.mMin.y, mBounds.mMin.z);
                            break;
                        case 1:
                            ve4.Set(0.0f, mBounds.mMin.z, mBounds.mMax.x);
                            break;
                        case 2:
                            ve4.Set(mBounds.mMax.x, mBounds.mMin.y, mBounds.mMin.z);
                            break;
                        case 3:
                            ve4.Set(mBounds.mMax.x, mBounds.mMin.y, 0.0f);
                            break;
                        case 4:
                            ve4.Set(mBounds.mMax.x, mBounds.mMin.y, mBounds.mMax.z);
                            break;
                        case 5:
                            ve4.Set(0.0f, mBounds.mMin.y, mBounds.mMax.z);
                            break;
                        case 6:
                            ve4.Set(mBounds.mMin.x, mBounds.mMin.y, mBounds.mMax.z);
                            break;
                        case 7:
                            ve4.Set(mBounds.mMin.x, mBounds.mMin.y, 0.0f);
                            break;
                        default: break;
                    }
                }
                static DataNode& disable = DataVariable("cheat.disable_eye_jitter");
                if(mEnableJitter && !sDisableJitter && !disable && deltasecs > 0.0f){
                    ve4.Set(
                        ve4[0] + RandomFloat(-mPitchJitterLimit, mPitchJitterLimit) * DEG2RAD,
                        ve4[1],
                        ve4[2] + RandomFloat(-mYawJitterLimit, mYawJitterLimit) * DEG2RAD
                    );
                }
                if(mSourceRadius > 0.0f){
                    Multiply(mPivot->TransParent()->WorldXfm().m, v108, v108);
                    ve4 -= v108;
                }
                if(mAllowRoll){
                    Hmx::Quat q128;
                    MakeRotQuat(mPivot->LocalXfm().m.y, ve4, q128);
                    FastInterp(Hmx::Quat(0,0,0,1.0f), q128, charweight, q128);
                    Hmx::Matrix3 md8;
                    MakeRotMatrix(q128, md8);
                    if(md8.x.x < -2.0f || md8.x.x > 2.0f){
                        MILO_NOTIFY_ONCE("%s has m.x.x %g, character or target scaled or NAN", PathName(this), md8.x.x);
                        md8.Identity();
                    }
                    Multiply(mPivot->LocalXfm().m, md8, mPivot->DirtyLocalXfm().m);
                }
                else {
                    Hmx::Matrix3& temp_dirty = mPivot->DirtyLocalXfm().m;
                    Interp(temp_dirty.y, ve4, charweight, temp_dirty.y);
                    temp_dirty.z.Set(-1.0f,0.0f,0.0f);
                    Normalize(temp_dirty.y, temp_dirty.y);
                    Cross(temp_dirty.y, temp_dirty.z, temp_dirty.x);
                    Normalize(temp_dirty.x, temp_dirty.x);
                    Cross(temp_dirty.x, temp_dirty.y, temp_dirty.z);
                    if(temp_dirty.x.x < -2.0f || temp_dirty.x.x > 2.0f){
                        MILO_NOTIFY_ONCE("%s has m.x.x %g, character or target scaled or NAN", PathName(this), temp_dirty.x.x);
                        temp_dirty.Identity();
                    }
                }
            }
        }
    }
}
#pragma pop

void CharLookAt::SetMinYaw(float yaw){
    mMinYaw = yaw;
    SyncLimits();
}

void CharLookAt::SetMaxYaw(float yaw){
    mMaxYaw = yaw;
    SyncLimits();
}