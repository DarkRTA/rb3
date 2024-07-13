#include "char/CharLookAt.h"
#include "math/MathFuncs.h"
#include "math/Rot.h"
#include "obj/Task.h"

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

RndTransformable* CharLookAt::GetSource() const {
    const ObjPtr<RndTransformable, ObjectDir>& ptr = mSource ? mSource : mPivot;
    return ptr;
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
                static DataNode* disable = DataVariable("cheat.disable_eye_jitter");
            }
        }
    }
}
#pragma pop

//   pRVar1 = (RndTransformable *)GetSource(this);
//   dVar16 = (double)TaskMgr::DeltaSeconds((TaskMgr *)&TheTaskMgr);
    // pRVar3 = (RndTransformable *)ObjPtr<>::operator_->((ObjPtr<> *)(this + 0x34));
    // iVar2 = RndTransformable::TransParent(pRVar3);
    // if ((iVar2 != 0) && ((pRVar1 != (RndTransformable *)0x0 && (dVar16 >= 0.0)))) {

    //     if (@GUARD@Poll__10CharLookAtFv@disable == '\0') {
    //       SVar7.mStr = (char *)Symbol::Symbol(&SStack_148,::@stringBase0);
    //       @LOCAL@Poll__10CharLookAtFv@disable = (DataNode *)DataVariable(SVar7);
    //       @GUARD@Poll__10CharLookAtFv@disable = '\x01';
    //     }

    //     if ((((this[0xb2] != (CharLookAt)0x0) && (sDisableJitter == '\0')) &&
    //         (iVar2 = DataNode::operator_!(@LOCAL@Poll__10CharLookAtFv@disable), iVar2 != 0)) &&
    //        (dVar16 > 0.0)) {
    //       dVar16 = (double)RandomFloat(-*(float *)(this + 0xb4),*(float *)(this + 0xb4));
    //       dVar18 = (double)RandomFloat(-*(float *)(this + 0xb8),*(float *)(this + 0xb8));
    //       pfVar8 = (float *)Vector3::operator_[](&VStack_e4,2);
    //       fVar21 = *pfVar8;
    //       pfVar8 = (float *)Vector3::operator_[](&VStack_e4,1);
    //       pfVar9 = (float *)Vector3::operator_[](&VStack_e4,0);
    //       Vector3::Set(&VStack_e4,(float)(dVar18 * 0.01745329238474369 + (double)*pfVar9),*pfVar8,
    //                    (float)(dVar16 * 0.01745329238474369 + (double)fVar21));
    //     }

    //     if (*(float *)(this + 0x7c) > 0.0) {
    //       pRVar1 = (RndTransformable *)ObjPtr<>::operator_->((ObjPtr<> *)(this + 0x34));
    //       pRVar1 = (RndTransformable *)RndTransformable::TransParent(pRVar1);
    //       pMVar6 = (Matrix3 *)RndTransformable::WorldXfm(pRVar1);
    //       Multiply(pMVar6,&VStack_108,&VStack_108);
    //       Vector3::operator_-=(&VStack_e4,&VStack_108);
    //     }
    
    //     if (this[0xb0] == (CharLookAt)0x0) {
    //       pRVar1 = (RndTransformable *)ObjPtr<>::operator_->((ObjPtr<> *)(this + 0x34));
    //       pMVar6 = (Matrix3 *)RndTransformable::DirtyLocalXfm(pRVar1);
    //       Interp(&pMVar6->y,&VStack_e4,(float)dVar17,&pMVar6->y);
    //       Vector3::Set(&pMVar6->z,-1.0,0.0,0.0);
    //       Normalize(&pMVar6->y,&pMVar6->y);
    //       Cross(&pMVar6->y,&pMVar6->z,(Vector3 *)pMVar6);
    //       Normalize((Vector3 *)pMVar6,(Vector3 *)pMVar6);
    //       Cross((Vector3 *)pMVar6,&pMVar6->y,&pMVar6->z);
    //       fVar21 = (pMVar6->x).x;
    //       if ((fVar21 < -2.0) || (fVar21 > 2.0)) {
    //         if (@GUARD@Poll__10CharLookAtFv@_dw@1 == '\0') {
    //           DebugNotifyOncer::DebugNotifyOncer
    //                     ((DebugNotifyOncer *)&@LOCAL@Poll__10CharLookAtFv@_dw@1);
    //           __register_global_object
    //                     (&@LOCAL@Poll__10CharLookAtFv@_dw@1,DebugNotifyOncer::~DebugNotifyOncer,
    //                      @20750);
    //           @GUARD@Poll__10CharLookAtFv@_dw@1 = '\x01';
    //         }
    //         if (this != (CharLookAt *)0x0) {
    //           this = *(CharLookAt **)this;
    //         }
    //         pcVar12 = (char *)PathName((Object *)this);
    //         pcVar12 = ::MakeString(s_%s_has_m.x.x_%g,_character_or_ta_80c04fe1,pcVar12,(pMVar6->x).x
    //                               );
    //         DebugNotifyOncer::operator_<<
    //                   ((DebugNotifyOncer *)&@LOCAL@Poll__10CharLookAtFv@_dw@1,pcVar12);
    //         Hmx::Matrix3::Identity(pMVar6);
    //       }
    //     }
    //     else {
    //       Hmx::Quat::Quat(aQStack_128);
    //       pRVar1 = (RndTransformable *)ObjPtr<>::operator_->((ObjPtr<> *)(this + 0x34));
    //       iVar2 = RndTransformable::LocalXfm(pRVar1);
    //       MakeRotQuat((Vector3 *)(iVar2 + 0xc),&VStack_e4,aQStack_128);
    //       pQVar10 = (Quat *)Hmx::Quat::Quat(aQStack_138,0.0,0.0,0.0,1.0);
    //       FastInterp(pQVar10,aQStack_128,(float)dVar17,aQStack_128);
    //       Hmx::Matrix3::Matrix3(&local_d8);
    //       MakeRotMatrix(aQStack_128,&local_d8);
    //       if ((local_d8.x.x < -2.0) || (local_d8.x.x > 2.0)) {
    //         if (@GUARD@Poll__10CharLookAtFv@_dw@0 == '\0') {
    //           DebugNotifyOncer::DebugNotifyOncer
    //                     ((DebugNotifyOncer *)&@LOCAL@Poll__10CharLookAtFv@_dw@0);
    //           __register_global_object
    //                     (&@LOCAL@Poll__10CharLookAtFv@_dw@0,DebugNotifyOncer::~DebugNotifyOncer,
    //                      @20741);
    //           @GUARD@Poll__10CharLookAtFv@_dw@0 = '\x01';
    //         }
    //         pOVar11 = (Object *)this;
    //         if (this != (CharLookAt *)0x0) {
    //           pOVar11 = *(Object **)this;
    //         }
    //         pcVar12 = (char *)PathName(pOVar11);
    //         pcVar12 = ::MakeString(s_%s_has_m.x.x_%g,_character_or_ta_80c04fe1,pcVar12,local_d8.x.x)
    //         ;
    //         DebugNotifyOncer::operator_<<
    //                   ((DebugNotifyOncer *)&@LOCAL@Poll__10CharLookAtFv@_dw@0,pcVar12);
    //         Hmx::Matrix3::Identity(&local_d8);
    //       }
    //       pRVar1 = (RndTransformable *)ObjPtr<>::operator_->((ObjPtr<> *)(this + 0x34));
    //       pMVar6 = (Matrix3 *)RndTransformable::DirtyLocalXfm(pRVar1);
    //       pRVar1 = (RndTransformable *)ObjPtr<>::operator_->((ObjPtr<> *)(this + 0x34));
    //       pMVar13 = (Matrix3 *)RndTransformable::LocalXfm(pRVar1);
    //       Multiply(pMVar13,&local_d8,pMVar6);
    //     }
    //   }
    // }

void CharLookAt::SetMinYaw(float yaw){
    mMinYaw = yaw;
    SyncLimits();
}

void CharLookAt::SetMaxYaw(float yaw){
    mMaxYaw = yaw;
    SyncLimits();
}