#include "char/CharPosConstraint.h"
#include "utl/Symbols.h"

INIT_REVS(CharPosConstraint)

CharPosConstraint::CharPosConstraint() : mSrc(this, 0), mTargets(this, kObjListNoNull) {
    mBox.mMin.Set(1.0f, 1.0f, 1.0f);
    mBox.mMax.Set(-1.0f, -1.0f, -1.0f);
}

CharPosConstraint::~CharPosConstraint(){
    
}

// fn_804F43F4 - poll
void CharPosConstraint::Poll(){
    if(mSrc){
        Transform& srcTrans = mSrc->WorldXfm();
        for(ObjPtrList<RndTransformable, ObjectDir>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
            RndTransformable* curTrans = *it;
            Transform tf48(curTrans->WorldXfm());
            if(mBox.mMin.x <= mBox.mMax.x){
                float tmp = Clamp(mBox.mMin.x, mBox.mMax.x, tf48.v.x - srcTrans.v.x);
                tf48.v.x = tmp + srcTrans.v.x;
            }
            if(mBox.mMin.y <= mBox.mMax.y){
                float tmp = Clamp(mBox.mMin.y, mBox.mMax.y, tf48.v.y - srcTrans.v.y);
                tf48.v.y = tmp + srcTrans.v.y;
            }
            if(mBox.mMin.z <= mBox.mMax.z){
                float tmp = Clamp(mBox.mMin.z, mBox.mMax.z, tf48.v.z - srcTrans.v.z);
                tf48.v.z = tmp + srcTrans.v.z;
            }
            curTrans->SetWorldXfm(tf48);
        }
    }
}

void CharPosConstraint::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    changedBy.push_back(mSrc);
    for(ObjPtrList<RndTransformable, class ObjectDir>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
        change.push_back(*it);
        changedBy.push_back(*it);
    }
}

SAVE_OBJ(CharPosConstraint, 0x64)

void CharPosConstraint::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    Hmx::Object::Load(bs);
    bs >> mTargets;
    bs >> mSrc;
    if(gRev > 1){
        bs >> mBox;
    }
    else {
        mBox.mMin.Set(1.0f, 1.0f, 0.0f);
        mBox.mMax.Set(-1.0f, -1.0f, 1000.0f);
    }
}

BEGIN_COPYS(CharPosConstraint)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharPosConstraint)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mTargets)
        COPY_MEMBER(mSrc)
        COPY_MEMBER(mBox)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharPosConstraint)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x8B)
END_HANDLERS

BEGIN_PROPSYNCS(CharPosConstraint)
    SYNC_PROP(source, mSrc)
    SYNC_PROP(targets, mTargets)
    SYNC_PROP(box, mBox)
END_PROPSYNCS