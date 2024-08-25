#ifndef CHAR_CHARBONE_H
#define CHAR_CHARBONE_H
#include "char/CharBones.h"
#include "obj/Object.h"
#include <vector>
#include "rndobj/Trans.h"

class CharBone : public Hmx::Object {
public:

    class WeightContext {
    public:
        WeightContext() : mContext(0), mWeight(0) {}
        int mContext;
        float mWeight;
    };

    CharBone();
    virtual ~CharBone(){}
    OBJ_CLASSNAME(CharBone);
    OBJ_SET_TYPE(CharBone);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    void StuffBones(std::list<CharBones::Bone>&, int) const;
    float GetWeight(int) const;
    void ClearContext(int);
    const WeightContext* FindWeight(int) const;
    DataNode OnGetContextFlags(DataArray*);
    int PositionContext() const { return mPositionContext; }
    int ScaleContext() const { return mScaleContext; }
    CharBones::Type RotationType() const { return mRotation; }
    int RotationContext() const { return mRotationContext; }
    CharBone* Target() const { return mTarget; }
    void SetTarget(CharBone* b){ mTarget = b; }
    void SetPositionContext(int c){ mPositionContext = c; }
    void SetScaleContext(int c){ mScaleContext = c; }
    void SetRotationContext(int c){ mRotationContext = c; }
    void SetRotationType(CharBones::Type ty){ mRotation = ty; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    
    int mPositionContext; // 0x1c
    int mScaleContext; // 0x20
    CharBones::Type mRotation; // 0x24
    int mRotationContext; // 0x28
    ObjPtr<CharBone, ObjectDir> mTarget; // 0x2c
    std::vector<WeightContext> mWeights; // 0x38
    ObjPtr<RndTransformable, ObjectDir> mTrans; // 0x40
    bool mBakeOutAsTopLevel; // 0x4c
};

BinStream& operator>>(BinStream&, CharBone::WeightContext&);

#endif
