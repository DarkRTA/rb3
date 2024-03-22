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

    static void Init();
    static Hmx::Object* NewObject();

    ObjOwnerPtr<RndTransformable, class ObjectDir> mParent;
    std::vector<int> mChildren;
    Transform mLocalXfm; // 0x20
    Transform mWorldXfm;
    std::vector<int>* vptr; // actually a ptr to DirtyCache? which is a class containing a vector and a char/bool/byte
    short mConstraint;
    bool mPreserveScale;
    ObjPtr<RndTransformable, class ObjectDir> mTarget;

    static ushort gRev;
    static ushort gAltRev;
    static Plane sShadowPlane;
};

#endif
