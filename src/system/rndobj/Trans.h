/*#ifndef RNDOBJ_TRANS_H
#define RNDOBJ_TRANS_H*/
#pragma once
#include "milo_types.h"
#include "math/Mtx.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Highlightable.h"
#include <list>
#include <vector>

class DirtyCache {
public:
    DirtyCache(){}
    ~DirtyCache(){}
    void SetDirty_Force(); // fn_8064E044

    // Set and SetDirty are unknown method names
    void Set(unsigned int ui){
        mFlags = ui | (mFlags & 1);
    }

    void SetDirty(){
        if(mFlags & 1) return;
        SetDirty_Force();
    }

    void SetLastBit(unsigned int ui){
        mFlags = mFlags & 0xfffffffe | ui;
    }

    NEW_POOL_OVERLOAD(DirtyCache);
    DELETE_POOL_OVERLOAD(DirtyCache);

    std::vector<DirtyCache*> mChildren;
    unsigned int mFlags; // maybe not a field for flags - perhaps cache id/key/tag?
};

class RndTransformable : public virtual RndHighlightable {
public:

    enum Constraint {
        kNone = 0,
        kLocalRotate = 1,
        kParentWorld = 2,
        kLookAtTarget = 3,
        kShadowTarget = 4,
        kBillboardZ = 5,
        kBillboardXZ = 6,
        kBillboardXYZ = 7,
        kFastBillboardXYZ = 8,
        kTargetWorld = 9
    };

    RndTransformable();
    OBJ_CLASSNAME(Trans)
    OBJ_SET_TYPE(Trans)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~RndTransformable();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Highlight();
    virtual void Print();
    virtual void UpdatedWorldXfm();

    void SetWorldXfm(const Transform&);
    void SetWorldPos(const Vector3&);
    void SetTransParent(RndTransformable*, bool);
    void SetTransConstraint(Constraint, RndTransformable*, bool);
    RndTransformable* TransParent() const { return mParent; }
    void DistributeChildren(bool, float);
    Transform& WorldXfm_Force();
    void SetLocalRot(Vector3);
    void TransformTransAnims(const Transform&);
    void ApplyDynamicConstraint();

    bool HasDynamicConstraint(){
        bool ret = true;
        if(mConstraint < kBillboardZ){
            bool ret2 = false;
            if(mConstraint >= kLookAtTarget && mTarget) ret2 = true;
            if(!ret2) ret = false;
        }
        return ret;
    }

    std::vector<RndTransformable*>& TransChildren(){ return mChildren; }

    void SetDirty(){
        if(mCache->mFlags & 1) return;
        mCache->SetDirty_Force();
    }

    Transform& WorldXfm(){
        if(mCache->mFlags & 1) return WorldXfm_Force();
        else return mWorldXfm;
    }

    void ResetLocalXfm(){
        SetDirty();
        mLocalXfm.Reset();
    }

    void SetLocalXfm(const Transform& tf){
        mLocalXfm = tf;
        SetDirty();
    }

    // TODO: at some point we need to replace calls to this SetLocalPos
    // to the one that takes in a Vector3& - we're using this one
    // because for whatever reason the Vector3& one doesn't inline nicely
    // and results in a stack related mismatch
    void SetLocalPos(float x, float y, float z){
        mLocalXfm.v.Set(x, y, z);
        SetDirty();
    }

    void SetLocalPos(const Vector3& vec){
        mLocalXfm.v.x = vec.x;
        mLocalXfm.v.y = vec.y;
        mLocalXfm.v.z = vec.z;
        SetDirty();
    }

    const Transform& LocalXfm() const {
        return mLocalXfm;
    }

    Transform& DirtyLocalXfm(){
        SetDirty();
        return mLocalXfm;
    }

    // here be the handlers. there is no fame, no honor to be wrought here. turn back now, lest you suffer the same fate of others
    DataNode OnCopyLocalTo(const DataArray*);
    DataNode OnGetLocalPos(const DataArray*);
    DataNode OnGetLocalPosIndex(const DataArray*);
    DataNode OnGetLocalRot(const DataArray*);
    DataNode OnGetLocalRotIndex(const DataArray*);
    DataNode OnSetLocalPos(const DataArray*);
    DataNode OnSetLocalPosIndex(const DataArray*);
    DataNode OnSetLocalRot(const DataArray*);
    DataNode OnSetLocalRotIndex(const DataArray*);
    DataNode OnSetLocalRotMat(const DataArray*);
    DataNode OnSetTransConstraint(const DataArray*);
    DataNode OnSetLocalScale(const DataArray*);
    DataNode OnSetLocalScaleIndex(const DataArray*);
    DataNode OnGetLocalScale(const DataArray*);
    DataNode OnGetLocalScaleIndex(const DataArray*);
    DataNode OnGetWorldForward(const DataArray*);
    DataNode OnGetWorldPos(const DataArray*);
    DataNode OnGetWorldRot(const DataArray*);
    DataNode OnGetChildren(const DataArray*);

    static void Init();
    
    NEW_OBJ(RndTransformable)
    static void Register(){
        REGISTER_OBJ_FACTORY(RndTransformable)
    }

    ObjOwnerPtr<RndTransformable, class ObjectDir> mParent; // 0x8
    std::vector<RndTransformable*> mChildren; // 0x14
    Transform mLocalXfm; // 0x1c
    Transform mWorldXfm; // 0x4c
    DirtyCache* mCache; // 0x7c
    u16 mConstraint; Constraint TransConstraint() { return (Constraint) mConstraint; } // 0x80
    bool mPreserveScale; // 0x82
    ObjPtr<RndTransformable, class ObjectDir> mTarget; // 0x84

    static ushort gRev;
    static ushort gAltRev;
    static Plane sShadowPlane;

    NEW_OVERLOAD
    DELETE_OVERLOAD
};

/*#endif*/
