#pragma once
#include "rndobj/Trans.h"
#include "obj/ObjPtr_p.h"
#include "char/CharEyeDartRuleset.h"

/** "An interest object for a character to look at" */
class CharInterest : public RndTransformable {
public:
    CharInterest();
    OBJ_CLASSNAME(CharInterest);
    OBJ_SET_TYPE(CharInterest);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~CharInterest();
    virtual void Highlight();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharInterest)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharInterest)
    }

    int CategoryFlags() const { return mCategoryFlags; }
    bool ShouldOverrideMinTargetDistance() const { return mOverrideMinTargetDistance; }
    float MinTargetDistanceOverride() const { return mMinTargetDistanceOverride; }
    void SyncMaxViewAngle();
    CharEyeDartRuleset* GetDartRulesetOverride() const;
    bool IsMatchingFilterFlags(int);
    bool IsWithinViewCone(const Vector3&, const Vector3&);
    float ComputeScore(const Vector3&, const Vector3&, const Vector3&, float, int, bool);

    /** "In degrees, the maximum view cone angle for this object to be 'seen'". Ranges from 0 to 90. */
    float mMaxViewAngle; // 0x90
    /** "An extra weight applied during scoring of this interest - use this to make it more or less important overall". Ranges from 0 to 5. */
    float mPriority; // 0x94
    /** "The minimum time you have to look at this object when its selected". Ranges from 0 to 100. */
    float mMinLookTime; // 0x98
    /** "The maximum allowable time to look at this object". Ranges from 0 to 100. */
    float mMaxLookTime; // 0x9C
    /** "In secs, how long until this object can be looked at again". Ranges from 0 to 100. */
    float mRefractoryPeriod; // 0xA0
    /** "if set, this dart ruleset will override the default one when looking at this interest object" */
    ObjPtr<CharEyeDartRuleset> mDartOverride; // 0xA4
    int mCategoryFlags; // 0xB0
    /** "if true, we will override the minimum distance this target can be from the eyes using the value below" */
    bool mOverrideMinTargetDistance; // 0xB4
    /** "the minimum distance, in inches, that this interest can be from the eyes.  only applied if overrides_min_target_dist is true..." */
    float mMinTargetDistanceOverride; // 0xB8
    float mMaxViewAngleCos; // 0xBC

    DECLARE_REVS
};
