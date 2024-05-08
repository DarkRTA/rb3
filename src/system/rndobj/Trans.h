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
    virtual ~RndTransformable();

    OBJ_CLASSNAME(Trans)
    OBJ_SET_TYPE(Trans)

    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Highlight();
    virtual void Print();
    virtual void UpdatedWorldXfm();

    void SetTransParent(RndTransformable*, bool);

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
    std::vector<int> mChildren;
    Transform mLocalXfm; // 0x1c
    Transform mWorldXfm;
    std::vector<int>* vptr; // actually a ptr to DirtyCache? which is a class containing a vector and a char/bool/byte
    short mConstraint;
    bool mPreserveScale;
    ObjPtr<RndTransformable, class ObjectDir> mTarget;

    static ushort gRev;
    static ushort gAltRev;
    static Plane sShadowPlane;

    NEW_OVERLOAD
    DELETE_OVERLOAD
};

#endif
