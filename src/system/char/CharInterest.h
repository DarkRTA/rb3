#ifndef CHAR_CHARINTEREST_H
#define CHAR_CHARINTEREST_H
#include "rndobj/Trans.h"
#include "obj/ObjPtr_p.h"
#include "char/CharEyeDartRuleset.h"

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

    int CategoryFlags() const { return mCategoryFlags; }
    void SyncMaxViewAngle();
    CharEyeDartRuleset* GetDartRulesetOverride() const;
    bool IsMatchingFilterFlags(int);
    bool IsWithinViewCone(const Vector3&, const Vector3&);
    float ComputeScore(const Vector3&, const Vector3&, const Vector3&, float, int, bool);

    float mMaxViewAngle; // 0x90
    float mPriority; // 0x94
    float mMinLookTime; // 0x98
    float mMaxLookTime; // 0x9C
    float mRefractoryPeriod; // 0xA0
    ObjPtr<CharEyeDartRuleset, ObjectDir> mDartOverride; // 0xA4
    int mCategoryFlags; // 0xB0
    bool mOverrideMinTargetDistance; // 0xB4
    float mMinTargetDistanceOverride; // 0xB8
    float mMaxViewAngleCos; // 0xBC

    DECLARE_REVS
};

#endif
