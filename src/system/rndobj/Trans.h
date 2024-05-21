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

    void* operator new(size_t s){
        return _PoolAlloc(s, sizeof(DirtyCache), FastPool);
    }

    void operator delete(void* v){
        _PoolFree(sizeof(DirtyCache), FastPool, v);
    }

    std::vector<DirtyCache*> mChildren;
    int mFlags; // maybe not a field for flags - perhaps cache id/key/tag?
};

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

class RndTransformable : public virtual RndHighlightable {
public:
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

    void SetTransParent(RndTransformable*, bool);
    RndTransformable* TransParent() const;

    // here be the handlers. there is no fame, no honor to be wrought here. turn back now, lest you suffer the same fate of others
    DataNode OnCopyLocalTo(const DataArray*);
    DataNode OnGetLocalPos(const DataArray*);
    DataNode OnGetLocalRot(const DataArray*);
    DataNode OnGetLocalRotIndex(const DataArray*);
    DataNode OnSetLocalPos(const DataArray*);
    DataNode OnSetLocalRot(const DataArray*);
    DataNode OnSetLocalRotIndex(const DataArray*);
    DataNode OnSetLocalRotMat(const DataArray*);
    DataNode OnSetTransConstraint(const DataArray*);

    static void Init();
    static Hmx::Object* NewObject();

    ObjOwnerPtr<RndTransformable, class ObjectDir> mParent;
    std::vector<RndTransformable*> mChildren;
    Transform mLocalXfm; // 0x1c
    Transform mWorldXfm; // 0x4c
    DirtyCache* mCache; // 0x7c
    u16 mConstraint; Constraint TransConstraint() { return (Constraint) mConstraint; }
    bool mPreserveScale;
    ObjPtr<RndTransformable, class ObjectDir> mTarget;

    static ushort gRev;
    static ushort gAltRev;
    static Plane sShadowPlane;

    NEW_OVERLOAD
    DELETE_OVERLOAD
};

#endif
