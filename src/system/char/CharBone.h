#pragma once
#include "char/CharBones.h"
#include "obj/Object.h"
#include <vector>
#include "rndobj/Trans.h"

/** "A Character system bone, conveys degrees of freedom to animate in a CharClip, lives in CharBoneDir" */
class CharBone : public Hmx::Object {
public:

    class WeightContext {
    public:
        WeightContext() : mContext(0), mWeight(0) {}

        /** "context for this bone weight" */
        int mContext; // 0x0
        /** "bone weight for this context" */
        float mWeight; // 0x4
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
    void SetTrans(RndTransformable* t){ mTrans = t; }
    bool BakeOutAsTopLevel() const { return mBakeOutAsTopLevel; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharBone)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharBone)
    }
    
    /** "when to animate position" */
    int mPositionContext; // 0x1c
    /** "when to animate scale" */
    int mScaleContext; // 0x20
    /** "what axis or axes to animate". Types are: kRotNone, kRotFull, kRotX, kRotY, kRotZ (???) */
    CharBones::Type mRotation; // 0x24
    /** "when to use this rotation context" */
    int mRotationContext; // 0x28
    /** "If set will exactly track this target during keyframe acquisition, used for IK bones" */
    ObjPtr<CharBone> mTarget; // 0x2c
    /** "array of contexts and corresponding bone weights" */
    std::vector<WeightContext> mWeights; // 0x38
    /** "Object to specify trans info" */
    ObjPtr<RndTransformable> mTrans; // 0x40
    /** "When baking out facing, use this as a top-level bone (like the pelvis)" */
    bool mBakeOutAsTopLevel; // 0x4c
};

BinStream& operator>>(BinStream&, CharBone::WeightContext&);
