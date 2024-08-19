#include "char/CharIKRod.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKRod)

CharIKRod::CharIKRod() : mLeftEnd(this, 0), mRightEnd(this, 0), mDestPos(0.5f), mSideAxis(this, 0), mVertical(0), mDest(this, 0) {

}

CharIKRod::~CharIKRod(){

}

void CharIKRod::Poll(){
    Transform tf38;
    if(ComputeRod(tf38)){
        Transform tf68;
        Multiply(mXfm, tf38, tf68);
        mDest->SetWorldXfm(tf68);
    }
}

// fn_804E6ACC - compute rod
bool CharIKRod::ComputeRod(Transform& tf){
    if(mDest == 0 || mLeftEnd == 0 || mRightEnd == 0) return false;
    Interp(mLeftEnd->WorldXfm().v, mRightEnd->WorldXfm().v, mDestPos, tf.v);
    if(mVertical) tf.m.x.Set(0.0f, 0.0f, -1.0f);
    else {
        Interp(mLeftEnd->WorldXfm().m.x, mRightEnd->WorldXfm().m.x, mDestPos, tf.m.x);
        Normalize(tf.m.x, tf.m.x);
    }
    if(mSideAxis) tf.m.z = mSideAxis->WorldXfm().m.z;
    else Subtract(mLeftEnd->WorldXfm().v, mRightEnd->WorldXfm().v, tf.m.z);
    Cross(tf.m.z, tf.m.x, tf.m.y);
    Normalize(tf.m.y, tf.m.y);
    Cross(tf.m.x, tf.m.y, tf.m.z);
    return true;
}

void CharIKRod::SyncBones(){
    Transform tf38;
    if(ComputeRod(tf38)){
        Invert(tf38, tf38);
        Multiply(mDest->WorldXfm(), tf38, mXfm);
    }
}

void CharIKRod::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mDest);
    changedBy.push_back(mLeftEnd);
    changedBy.push_back(mRightEnd);
    changedBy.push_back(mSideAxis);
}

SAVE_OBJ(CharIKRod, 0x81)

BEGIN_LOADS(CharIKRod)
    LOAD_REVS(bs)
    ASSERT_REVS(2, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mLeftEnd;
    bs >> mRightEnd;
    bs >> mDestPos;
    bs >> mSideAxis;
    bs >> mVertical;
    bs >> mDest;
    bs >> mXfm;
END_LOADS

BEGIN_COPYS(CharIKRod)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharIKRod)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mLeftEnd)
        COPY_MEMBER(mRightEnd)
        COPY_MEMBER(mDestPos)
        COPY_MEMBER(mSideAxis)
        COPY_MEMBER(mVertical)
        COPY_MEMBER(mDest)
        COPY_MEMBER(mXfm)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharIKRod)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xAF)
END_HANDLERS

BEGIN_PROPSYNCS(CharIKRod)
    SYNC_PROP_MODIFY_ALT(left_end, mLeftEnd, SyncBones())
    SYNC_PROP_MODIFY_ALT(right_end, mRightEnd, SyncBones())
    SYNC_PROP_MODIFY_ALT(dest_pos, mDestPos, SyncBones())
    SYNC_PROP_MODIFY_ALT(side_axis, mSideAxis, SyncBones())
    SYNC_PROP_MODIFY_ALT(vertical, mVertical, SyncBones())
    SYNC_PROP_MODIFY_ALT(dest, mDest, SyncBones())
END_PROPSYNCS