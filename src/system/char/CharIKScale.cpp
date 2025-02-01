#include "char/CharIKScale.h"
#include "char/CharWeightable.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"

INIT_REVS(CharIKScale)

CharIKScale::CharIKScale()
    : mDest(this), mScale(1.0f), mSecondaryTargets(this), mBottomHeight(0.0f),
      mTopHeight(0.0f), mAutoWeight(0) {}

CharIKScale::~CharIKScale() {}

// fn_804E75B8 in retail
void CharIKScale::Poll() {
    float weight = Weight();
    if (mDest && weight != 0) {
        if (mAutoWeight) {
            float f1 = mDest->mLocalXfm.v.z;
            float f2 = mBottomHeight;
            if (f1 < f2)
                weight = 0;
            else if (f1 > mTopHeight)
                weight = 1;
            else
                weight = (f1 - f2) / (mTopHeight - f2);
        }
        if (weight != 0) {
            Transform tf48(mDest->WorldXfm());
            tf48.v = mDest->mLocalXfm.v;
            tf48.v.z *= Interp(1.0f, mScale, weight);
            Vector3 v24;
            if (mDest->TransParent()) {
                Multiply(tf48.v, mDest->TransParent()->WorldXfm(), v24);
            }
            mDest->SetWorldXfm(tf48);
            if (mSecondaryTargets.size() > 0) {
                tf48.v.z = mDest->mLocalXfm.v.z * mScale;
                Vector3 v90;
                Multiply(tf48.v, mDest->TransParent()->WorldXfm(), v90);
                Vector3 v9c = v24;
                v9c -= v90;
                for (ObjPtrList<RndTransformable>::iterator it =
                         mSecondaryTargets.begin();
                     it != mSecondaryTargets.end();
                     ++it) {
                    RndTransformable *cur = *it;
                    Transform tf78(cur->WorldXfm());
                    tf78.v -= v9c;
                    cur->SetWorldXfm(tf78);
                }
            }
        }
    }
}

void CharIKScale::CaptureBefore() {
    if (mDest)
        mScale = mDest->mLocalXfm.v.z;
}

void CharIKScale::CaptureAfter() {
    if (mDest)
        mScale = mDest->mLocalXfm.v.z / mScale;
}

void CharIKScale::PollDeps(
    std::list<Hmx::Object *> &changedBy, std::list<Hmx::Object *> &change
) {
    change.push_back(mDest);
    for (ObjPtrList<RndTransformable, class ObjectDir>::iterator it =
             mSecondaryTargets.begin();
         it != mSecondaryTargets.end();
         ++it) {
        change.push_back(*it);
    }
    changedBy.push_back(mDest);
}

SAVE_OBJ(CharIKScale, 0x93)

BEGIN_LOADS(CharIKScale)
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(CharWeightable)
    bs >> mDest;
    bs >> mScale;
    if (gRev > 1)
        bs >> mSecondaryTargets;
    if (gRev > 2) {
        bs >> mAutoWeight >> mBottomHeight >> mTopHeight;
    }
END_LOADS

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
    HANDLE_CHECK(0xCC)
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