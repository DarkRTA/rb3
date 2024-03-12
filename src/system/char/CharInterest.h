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

    void operator delete(void* v){
        _MemFree(v);
    }

    void SyncMaxViewAngle();

    float mMaxViewAngle;
    float mPriority;
    float mMinLookTime;
    float mMaxLookTime;
    float mRefractoryPeriod;
    ObjPtr<CharEyeDartRuleset, ObjectDir> mDartOverride;
    int mCategoryFlags;
    bool mOverrideMinTargetDistance;
    float mMinTargetDistanceOverride;
    float mMaxViewAngleCos;
};

#endif
