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

    OBJ_CLASSNAME(RndTransformable)
    OBJ_SET_TYPE(RndTransformable)

    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Highlight();
    virtual void Print();
    virtual void UpdatedWorldXfm();

    static void Init();
    static Hmx::Object* NewObject();

    ObjOwnerPtr<RndTransformable, ObjectDir> mParent;
    std::vector<int> mChildren;
    Transform mLocalXfm; // 0x20
    Transform mWorldXfm;
    // vector pointer - 0x7c
    // some short at 0x80
    // some bool at 0x82
    // then mTarget at 0x84
    std::vector<int>* vptr;
    short idk;
    bool idkbool;
    // bool mDirty, mPreserveScale;
    // Constraint mConstraint;
    ObjPtr<RndTransformable, ObjectDir> mTarget;

    static ushort gRev;
    static ushort gAltRev;
    static Plane sShadowPlane;
};

#endif
