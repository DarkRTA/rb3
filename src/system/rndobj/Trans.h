#ifndef RNDOBJ_TRANS_H
#define RNDOBJ_TRANS_H
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

    void* operator new(size_t s){
        return _PoolAlloc(s, sizeof(DirtyCache), FastPool);
    }

    void operator delete(void* v){
        _PoolFree(sizeof(DirtyCache), FastPool, v);
    }

    std::vector<DirtyCache*> mChildren;
    unsigned int mFlags; // maybe not a field for flags - perhaps cache id/key/tag?
};

class RndTransformable : public virtual RndHighlightable {
public:

    enum Constraint {
        kNone,
        kLocalRotate,
        kParentWorld,
        kLookAtTarget,
        kShadowTarget,
        kBillboardZ,
        kBillboardXZ,
        kBillboardXYZ,
        kTargetWorld
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
    RndTransformable* TransParent() const;
    void DistributeChildren(bool, float);
    Transform& WorldXfm_Force();
    void SetLocalRot(Vector3);

    Transform& DirtyLocalXfm(){
        mCache->SetDirty();
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

    ObjOwnerPtr<RndTransformable, class ObjectDir> mParent;
    std::vector<RndTransformable*> mChildren;
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

template <class T> void RemoveSwap(std::vector<T*>&, T*);

#endif
