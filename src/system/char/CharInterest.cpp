#include "char/CharInterest.h"
#include "math/MathFuncs.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/PropSync_p.h"
#include "rndobj/Trans.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

INIT_REVS(CharInterest)

CharInterest::CharInterest() : mMaxViewAngle(20.0f), mPriority(1.0f), mMinLookTime(1.0f), mMaxLookTime(3.0f), mRefractoryPeriod(6.1f), mDartOverride(this, 0), mCategoryFlags(0), mOverrideMinTargetDistance(0), mMinTargetDistanceOverride(35.0f) {
    SyncMaxViewAngle();
}

CharInterest::~CharInterest(){
    
}

void CharInterest::SyncMaxViewAngle(){
    mMaxViewAngleCos = cos_f(mMaxViewAngle * 0.017453292f);
}

SAVE_OBJ(CharInterest, 0x52);

BEGIN_LOADS(CharInterest)
    LOAD_REVS(bs)
    ASSERT_REVS(6, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndTransformable)
    bs >> mMaxViewAngle;
    bs >> mPriority;
    bs >> mMinLookTime;
    bs >> mMaxLookTime;
    bs >> mRefractoryPeriod;
    u32 temp = gRev + 0x10000;
    if (u16(temp - 2) <= 3) {
        ObjPtr<Hmx::Object, ObjectDir> obj(this, NULL);
        bs >> obj;
    } else if (temp > 5) { bs >> mDartOverride; } 
    if (gRev > 2) {
        bs >> mCategoryFlags;
        if (gRev == 3) {
            u8 x;
            bs >> x;
        } 
    }
    if (gRev > 4) {
        bs >> mOverrideMinTargetDistance;
        bs >> mMinTargetDistanceOverride;
    }
    SyncMaxViewAngle();
END_LOADS

BEGIN_COPYS(CharInterest)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    CREATE_COPY(CharInterest)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mMaxViewAngle)
        COPY_MEMBER(mPriority)
        COPY_MEMBER(mMinLookTime)
        COPY_MEMBER(mMaxLookTime)
        COPY_MEMBER(mRefractoryPeriod)
        COPY_MEMBER(mDartOverride)
        COPY_MEMBER(mCategoryFlags)
        COPY_MEMBER(mOverrideMinTargetDistance)
        COPY_MEMBER(mMinTargetDistanceOverride)
        SyncMaxViewAngle();
    END_COPYING_MEMBERS
END_COPYS

BEGIN_PROPSYNCS(CharInterest)
    SYNC_PROP_MODIFY(max_view_angle, mMaxViewAngle, SyncMaxViewAngle())
    SYNC_PROP(priority, mPriority)
    SYNC_PROP(min_look_time, mMinLookTime)
    SYNC_PROP(max_look_time, mMaxLookTime)
    SYNC_PROP(refractory_period, mRefractoryPeriod)
    SYNC_PROP(dart_ruleset_override, mDartOverride)
    SYNC_PROP_STATIC("category_flags", mCategoryFlags)
    SYNC_PROP(overrides_min_target_dist, mOverrideMinTargetDistance)
    SYNC_PROP(min_target_dist_override, mMinTargetDistanceOverride)

    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS

BEGIN_HANDLERS(CharInterest)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x141)
END_HANDLERS
