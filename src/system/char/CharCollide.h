#ifndef CHAR_CHARCOLLIDE_H
#define CHAR_CHARCOLLIDE_H
#include "rndobj/Trans.h"
#include "rndobj/Mesh.h"
#include "obj/ObjPtr_p.h"

class CharCollide : public RndTransformable {
public:
    enum Shape {
        kPlane = 0,
        kSphere = 1,
        kInsideSphere = 2,
        kCigar = 3,
        kInsideCigar = 4,
    };

    CharCollide();
    OBJ_CLASSNAME(CharCollide)
    OBJ_SET_TYPE(CharCollide)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~CharCollide();
    virtual void Highlight();

    Shape mShape;
    int mFlags;
    ObjPtr<RndMesh, ObjectDir> mMesh; // 0x98
    // float mRadius;
    // float mMaxLength;
    // float mMinLength;
    // float mCurRadius;

    // radius0 at 0x138
    // radius1 at 0x13c
    // length0 at 0x140
    // length1 at 0x144
    // mesh y bias at 0x188
};

#endif
