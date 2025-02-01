#include "char/CharBlendBone.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"

INIT_REVS(CharBlendBone)

CharBlendBone::CharBlendBone()
    : mTargets(this), mSrc1(this), mSrc2(this), mTransX(0), mTransY(0), mTransZ(0),
      mRotation(0) {}

// fn_804A4D38 - poll
void CharBlendBone::Poll() {
    for (ObjList<ConstraintSystem>::iterator it = mTargets.begin(); it != mTargets.end();
         ++it) {
        RndTransformable *target = (*it).mTarget;
        if (target && mSrc1 && mSrc2) {
            Transform &xfm1 = mSrc1->WorldXfm();
            Transform &xfm2 = mSrc2->WorldXfm();
            Transform tf48(target->WorldXfm());
            if (mTransX || mTransY || mTransZ) {
                if (mTransX) {
                    Interp(xfm1.v.x, xfm2.v.x, (*it).mWeight, tf48.v.x);
                }
                if (mTransY) {
                    float f24;
                    Interp(xfm1.v.y, xfm2.v.y, (*it).mWeight, tf48.v.y);
                }
                if (mTransZ) {
                    float f24;
                    Interp(xfm1.v.z, xfm2.v.z, (*it).mWeight, tf48.v.z);
                }
            }
            if (mRotation) {
                Interp(xfm1.m, xfm2.m, (*it).mWeight, tf48.m);
            }
            target->SetWorldXfm(tf48);
        }
    }
}

void CharBlendBone::PollDeps(
    std::list<Hmx::Object *> &changedBy, std::list<Hmx::Object *> &change
) {
    changedBy.push_back(mSrc1);
    changedBy.push_back(mSrc2);
    for (ObjList<ConstraintSystem>::iterator it = mTargets.begin(); it != mTargets.end();
         ++it) {
        change.push_back((*it).mTarget);
    }
}

SAVE_OBJ(CharBlendBone, 0x44)

BEGIN_LOADS(CharBlendBone)
    LOAD_REVS(bs)
    ASSERT_REVS(3, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mTargets;
    bs >> mSrc1;
    bs >> mSrc2;
    bs >> mTransX;
    bs >> mTransY;
    bs >> mTransZ;
    bs >> mRotation;
END_LOADS

BEGIN_COPYS(CharBlendBone)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharBlendBone)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mTargets)
        COPY_MEMBER(mSrc1)
        COPY_MEMBER(mSrc2)
        COPY_MEMBER(mTransX)
        COPY_MEMBER(mTransY)
        COPY_MEMBER(mTransZ)
        COPY_MEMBER(mRotation)
    END_COPYING_MEMBERS
END_COPYS

CharBlendBone::ConstraintSystem::ConstraintSystem(Hmx::Object *o)
    : mTarget(o), mWeight(0.5f) {}

BinStream &operator>>(BinStream &bs, CharBlendBone::ConstraintSystem &cs) {
    bs >> cs.mTarget;
    bs >> cs.mWeight;
    return bs;
}

BEGIN_HANDLERS(CharBlendBone)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x8F)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(CharBlendBone::ConstraintSystem)
    SYNC_PROP(target, o.mTarget)
    SYNC_PROP(weight, o.mWeight)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharBlendBone)
    SYNC_PROP(targets, mTargets)
    SYNC_PROP(src_one, mSrc1)
    SYNC_PROP(src_two, mSrc2)
    SYNC_PROP(trans_x, mTransX)
    SYNC_PROP(trans_y, mTransY)
    SYNC_PROP(trans_z, mTransZ)
    SYNC_PROP(rotation, mRotation)
END_PROPSYNCS