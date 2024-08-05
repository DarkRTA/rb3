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

    float Eccentricity(const Vector2&) const;

    DECLARE_REVS;

    // offset0, radius0, offset1, radius1, offset2, radius2, outer_radius
    Shape mShape[3]; // 0x90, 0x98, 0xa0
    float mOuterRadius; // 0xa8
    bool mOpenEnd; // 0xac
    ObjPtrList<RndMesh, ObjectDir> mIgnore; // 0xb0
    ObjPtr<RndTransformable, ObjectDir> mBone; // 0xc0
    float mEccentricity; // 0xcc
    Symbol mCategory; // 0xd0
};

#endif
