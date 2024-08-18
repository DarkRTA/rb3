#include "char/CharEyeDartRuleset.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

#include "decomp.h"

unsigned short CharEyeDartRuleset::gRev = 0;
unsigned short CharEyeDartRuleset::gAltRev = 0;

CharEyeDartRuleset::CharEyeDartRuleset(){
    
}

CharEyeDartRuleset::~CharEyeDartRuleset(){

}

void CharEyeDartRuleset::EyeDartRulesetData::ClearToDefaults(){
    mMinRadius = 0.5f;
    mMaxRadius = 3.0f;
    mOnTargetAngleThresh = 5.0f;
    mMinDartsPerSequence = 2;
    mMaxDartsPerSequence = 5;
    mMinSecsBetweenDarts = 0.25f;
    mMaxSecsBetweenDarts = 0.65f;
    mMinSecsBetweenSequences = 1.0f;
    mMaxSecsBetweenSequences = 2.0f;
    mScaleWithDistance = true;
    mReferenceDistance = 70.0f;
}

SAVE_OBJ(CharEyeDartRuleset, 0x2B)

void CharEyeDartRuleset::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    bs >> mData.mMinRadius >> mData.mMaxRadius >> mData.mOnTargetAngleThresh >> mData.mMinDartsPerSequence >> mData.mMaxDartsPerSequence >>
        mData.mMinSecsBetweenDarts >> mData.mMaxSecsBetweenDarts >> mData.mMinSecsBetweenSequences >> mData.mMaxSecsBetweenSequences >> mData.mScaleWithDistance >> mData.mReferenceDistance;
}

BEGIN_COPYS(CharEyeDartRuleset)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(CharEyeDartRuleset)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mData.mMinRadius)
        // COPY_MEMBER(mData.mMaxRadius)
        mData.mMaxRadius = c->mData.mMinRadius;
        COPY_MEMBER(mData.mOnTargetAngleThresh)
        COPY_MEMBER(mData.mMinDartsPerSequence)
        COPY_MEMBER(mData.mMaxDartsPerSequence)
        COPY_MEMBER(mData.mMinSecsBetweenDarts)
        COPY_MEMBER(mData.mMaxSecsBetweenDarts)
        COPY_MEMBER(mData.mMinSecsBetweenSequences)
        COPY_MEMBER(mData.mMaxSecsBetweenSequences)
        COPY_MEMBER(mData.mScaleWithDistance)
        COPY_MEMBER(mData.mReferenceDistance)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_PROPSYNCS(CharEyeDartRuleset)
    SYNC_PROP(min_radius, mData.mMinRadius)
    SYNC_PROP(max_radius, mData.mMaxRadius)
    SYNC_PROP(on_target_angle_thresh, mData.mOnTargetAngleThresh)
    SYNC_PROP(min_darts_per_sequence, mData.mMinDartsPerSequence)
    SYNC_PROP(max_darts_per_sequence, mData.mMaxDartsPerSequence)
    SYNC_PROP(min_secs_between_darts, mData.mMinSecsBetweenDarts)
    SYNC_PROP(max_secs_between_darts, mData.mMaxSecsBetweenDarts)
    SYNC_PROP(min_secs_between_sequences, mData.mMinSecsBetweenSequences)
    SYNC_PROP(max_secs_between_sequences, mData.mMaxSecsBetweenSequences)
    SYNC_PROP(scale_with_distance, mData.mScaleWithDistance)
    SYNC_PROP(reference_distance, mData.mReferenceDistance)
END_PROPSYNCS

DECOMP_FORCEACTIVE(CharEyeDartRuleset,
    "min_radius", "max_radius",
    "min_darts_per_sequence", "max_darts_per_sequence",
    "min_time_between_darts", "max_time_between_darts",
    "min_time_between_sequences", "max_time_between_sequences",
    "scale_with_distance",
    "reference_distance"
)

BEGIN_HANDLERS(CharEyeDartRuleset)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xD4)
END_HANDLERS
