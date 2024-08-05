#include "char/CharIKHead.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKHead)

CharIKHead::CharIKHead() : mPoints(this), mHead(this, 0), mSpine(this, 0), mMouth(this, 0), mTarget(this, 0), mHeadFilter(0.0f, 0.0f, 0.0f), mTargetRadius(0.75f), 
    mHeadMat(0.5f), mOffset(this, 0), mOffsetScale(1.0f, 1.0f, 1.0f), mUpdatePoints(1), mMe(this, 0) {

}

CharIKHead::~CharIKHead(){
    
}

void CharIKHead::SetName(const char* name, ObjectDir* dir){
    Hmx::Object::SetName(name, dir);
    mMe = dynamic_cast<Character*>(dir);
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

// fn_804E3858 - updatepoints
void CharIKHead::UpdatePoints(bool b){
    if(b || mUpdatePoints){
        mUpdatePoints = false;
        mPoints.clear();
        int gencnt = GenerationCount(mSpine, mHead);
        if(gencnt != 0){
            mPoints.resize(gencnt + 1);
            float f1 = 0.0f;
            RndTransformable* curtrans = mHead;
            for(int i = 0; i < mPoints.size(); i++){
                Point& pt = mPoints[i];
                pt.unk0 = curtrans;
                pt.unk18 = Length(curtrans->LocalXfm().v);
                curtrans = curtrans->TransParent();
                f1 += pt.unk18;
            }
            mSpineLength = f1;
            float f2 = 1.0f / f1;
            for(int i = 0; i < mPoints.size(); i++){
                mPoints[i].unk1c = f1 * f2;
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