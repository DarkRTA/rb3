#include "char/CharIKHead.h"
#include "decomp.h"
#include "math/Mtx.h"
#include "math/Rot.h"
#include "math/Vec.h"
#include "obj/Task.h"
#include "rndobj/Rnd.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKHead)

DECOMP_FORCEACTIVE(CharIKHead, "%.2f")

CharIKHead::CharIKHead() : mPoints(this), mHead(this), mSpine(this), mMouth(this), mTarget(this), mHeadFilter(0.0f, 0.0f, 0.0f), mTargetRadius(0.75f), 
    mHeadMat(0.5f), mOffset(this), mOffsetScale(1.0f, 1.0f, 1.0f), mUpdatePoints(1), mMe(this) {

}

CharIKHead::~CharIKHead(){
    
}

void CharIKHead::SetName(const char* name, ObjectDir* dir){
    Hmx::Object::SetName(name, dir);
    mMe = dynamic_cast<Character*>(dir);
}

void CharIKHead::Poll(){
    if(!mHead || !mTarget || !mSpine) return;
    UpdatePoints(false);
    if(mMe && mMe->Teleported()){
        mHeadFilter = mHead->WorldXfm().v;
    }
    else if(TheTaskMgr.DeltaSeconds() > 0){
        Interp(mHeadFilter, mHead->WorldXfm().v, 0.5f, mHeadFilter);
    }
    float weight = Weight();
    if(weight != 0){
        Hmx::Matrix3 m58(mHead->WorldXfm().m);
        Vector3 vec;
        Subtract(mHead->WorldXfm().v, mHeadFilter, vec);
        Vector3 vf8 = mTarget->WorldXfm().v;
        float lenec = Length(vec);
        if(lenec > 0){
            float f10 = Min(lenec, mTargetRadius * weight);
            ScaleAddEq(vf8, vec, f10 / lenec);
        }
        Interp(mPoints[0].unk0->WorldXfm().v, vf8, weight, vf8);
        Vector3 v104;
        Subtract(vf8, mSpine->TransParent()->WorldXfm().v, v104);
        float lensq = LengthSquared(v104);
        if(lensq > mSpineLength * mSpineLength){
            ScaleAdd(mSpine->TransParent()->WorldXfm().v, v104, mSpineLength / std::sqrt(lensq), vf8);
        }
        Subtract(vf8, mPoints[0].unk0->WorldXfm().v, v104);
        for(int i = 0; i < mPoints.size(); i++){
            Point& curPt = mPoints[i];
            ScaleAdd(curPt.unk0->WorldXfm().v, v104, curPt.unk1c, curPt.unkc);
        }
        Vector3 v110(0,0,0);
        for(int i = 1; i < mPoints.size(); i++){
            mPoints[i].unkc += v110;
            Vector3 v11c;
            Subtract(mPoints[i].unkc, mPoints[i-1].unkc, v11c);
            v110 -= v11c;
            ScaleToMagnitude(v11c, mPoints[i-1].unk18, v11c);
            v110 += v11c;
            ::Add(mPoints[i-1].unkc, v11c, mPoints[i].unkc);
        }
        for(int i = 1; i < mPoints.size(); i++){
            ScaleAddEq(mPoints[i].unkc, v110, mPoints[i].unk1c - 1.0f);
        }
        for(int i = mPoints.size() - 1; i >= 0; i--){
            Transform tf88(mPoints[i].unk0->WorldXfm().m, mPoints[i].unkc);
            if(i > 0){
                Vector3 v128;
                Hmx::Quat q138;
                Multiply(mPoints[i - 1].unk0->mLocalXfm.v, tf88.m, v128);
                Vector3 v148;
                Subtract(mPoints[i - 1].unkc, mPoints[i].unkc, v148);
                MakeRotQuat(v128, v148, q138);
                Hmx::Matrix3 mb0;
                MakeRotMatrix(q138, mb0);
                Multiply(tf88.m, mb0, tf88.m);
            }
            else {
                Interp(tf88.m, m58, mHeadMat, tf88.m);
            }
            mPoints[i].unk0->SetWorldXfm(tf88);
        }
        if(mOffset){
            Transform tfe0(mOffset->WorldXfm());
            v104 *= mOffsetScale;
            tfe0.v += v104;
            mOffset->SetWorldXfm(tfe0);
        }
    }
}

void CharIKHead::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    changedBy.push_back(mMouth);
    changedBy.push_back(mHead);
    changedBy.push_back(mTarget);
    if(GenerationCount(mSpine, mHead) != 0){
        for(RndTransformable* t = mHead; t != 0 && t != mSpine->TransParent(); t = t->TransParent()){
            change.push_back(t);
        }
    }
    change.push_back(mOffset);
}

void CharIKHead::Highlight(){
#ifdef MILO_DEBUG
    float weight = Weight();
    if(weight == 0 || !mHead || !mTarget || !mSpine) return;
    else {
        UtilDrawSphere(mDebugTarget, mTargetRadius, Hmx::Color(0,1,0));
        UtilDrawString(MakeString("%.2f", weight), mDebugTarget, Hmx::Color(1,1,1));
        for(int i = 1; i < mPoints.size(); i++){
            TheRnd->DrawLine(mPoints[i].unk20, mPoints[i-1].unk20, Hmx::Color(1,0,0), false);
            TheRnd->DrawLine(mPoints[i].unkc, mPoints[i-1].unkc, Hmx::Color(0,1,0), false);
        }
    }
#endif
}

// fn_804E3858 - updatepoints
void CharIKHead::UpdatePoints(bool b){
    if(b || mUpdatePoints){
        mUpdatePoints = false;
        mPoints.clear();
        int gencnt = GenerationCount(mSpine, mHead);
        if(gencnt != 0){
            mPoints.resize(gencnt + 1);
            float f1 = 0.0f;
            int i;
            RndTransformable* curtrans = mHead;
            for(i = 0; i < mPoints.size(); i++){
                Point& pt = mPoints[i];
                pt.unk0 = curtrans;
                pt.unk18 = Length(curtrans->mLocalXfm.v);
                curtrans = curtrans->TransParent();
                f1 += pt.unk18;
            }
            mSpineLength = f1;
            float f2 = 1.0f / f1;
            for(int i = 0; i < mPoints.size(); i++){
                Point& curPt = mPoints[i];
                curPt.unk1c = f1 * f2;
                f1 = f1 - mPoints[i].unk18;
            }
        }
    }
}

SAVE_OBJ(CharIKHead, 0xF8)

BEGIN_LOADS(CharIKHead)
    LOAD_REVS(bs)
    ASSERT_REVS(3, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(CharWeightable)
    bs >> mHead;
    bs >> mSpine;
    bs >> mMouth;
    bs >> mTarget;
    if(gRev > 1){
        bs >> mTargetRadius;
        bs >> mHeadMat;
    }
    if(gRev > 2){
        bs >> mOffset;
        bs >> mOffsetScale;
    }
    mUpdatePoints = true;
END_LOADS

BEGIN_COPYS(CharIKHead)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharIKHead)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mHead)
        COPY_MEMBER(mSpine)
        COPY_MEMBER(mMouth)
        COPY_MEMBER(mTarget)
        COPY_MEMBER(mTargetRadius)
        COPY_MEMBER(mHeadMat)
        COPY_MEMBER(mOffset)
        COPY_MEMBER(mOffsetScale)
        mUpdatePoints = true;
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharIKHead)
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x138)
END_HANDLERS

BEGIN_PROPSYNCS(CharIKHead)
    SYNC_PROP_MODIFY_ALT(head, mHead, UpdatePoints(true))
    SYNC_PROP_MODIFY_ALT(spine, mSpine, UpdatePoints(true))
    SYNC_PROP(mouth, mMouth)
    SYNC_PROP(target, mTarget)
    SYNC_PROP(target_radius, mTargetRadius)
    SYNC_PROP(head_mat, mHeadMat)
    SYNC_PROP(offset, mOffset)
    SYNC_PROP(offset_scale, mOffsetScale)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS