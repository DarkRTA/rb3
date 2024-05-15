#ifndef CHAR_CHARCUFF_H
#define CHAR_CHARCUFF_H
#include "rndobj/Trans.h"
#include "rndobj/Mesh.h"
#include "obj/ObjPtr_p.h"

struct Shape {
    float offset;
    float radius;
};

class CharCuff : public RndTransformable {
public:
    CharCuff();
    OBJ_CLASSNAME(CharCuff)
    OBJ_SET_TYPE(CharCuff)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~CharCuff();
    virtual void Highlight();

    Shape mShape[3];
    float mOuterRadius;
    // offset0, radius0, offset1, radius1, offset2, radius2, outer_radius
    bool mOpenEnd;
    ObjPtrList<RndMesh, ObjectDir> mIgnore;
    ObjPtr<RndTransformable, ObjectDir> mBone;
    float mEccentricity;
    Symbol mCategory;
};

#endif
