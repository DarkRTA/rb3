#include "char/CharIKScale.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKScale)

CharIKScale::CharIKScale() : mDest(this, 0), mScale(1.0f), mSecondaryTargets(this, kObjListNoNull), mBottomHeight(0.0f), mTopHeight(0.0f), mAutoWeight(0) {

}

CharIKScale::~CharIKScale(){

}

void CharIKScale::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mDest);
    for(ObjPtrList<RndTransformable, class ObjectDir>::iterator it = mSecondaryTargets.begin(); it != mSecondaryTargets.end(); ++it){
        change.push_back(*it);
    }
    changedBy.push_back(mDest);
}

SAVE_OBJ(CharIKScale, 0x93)

void CharIKScale::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    Hmx::Object::Load(bs);
    CharWeightable::Load(bs);
    bs >> mDest;
    bs >> mScale;
    if(gRev > 1) bs >> mSecondaryTargets;
    if(gRev > 2){
        bs >> mAutoWeight >> mBottomHeight >> mTopHeight;
    }
}

BEGIN_COPYS(CharIKScale)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharIKScale)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mDest)
        COPY_MEMBER(mScale)
        COPY_MEMBER(mSecondaryTargets)
        COPY_MEMBER(mAutoWeight)
        COPY_MEMBER(mBottomHeight)
        COPY_MEMBER(mTopHeight)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharIKScale)
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_ACTION(capture_before, CaptureBefore())
    HANDLE_ACTION(capture_after, CaptureAfter())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x99)
END_HANDLERS

BEGIN_PROPSYNCS(CharIKScale)
    SYNC_PROP(dest, mDest)
    SYNC_PROP(scale, mScale)
    SYNC_PROP(secondary_targets, mSecondaryTargets)
    SYNC_PROP(auto_weight, mAutoWeight)
    SYNC_PROP(bottom_height, mBottomHeight)
    SYNC_PROP(top_height, mTopHeight)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS