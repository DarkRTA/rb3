#ifndef CHAR_CHARCOLLIDE_H
#define CHAR_CHARCOLLIDE_H
#include "rndobj/Trans.h"

enum Shape {
    kPlane = 0,
    kSphere = 1,
    kInsideSphere = 2,
    kCigar = 3,
    kInsideCigar = 4,
};

class CharCollide : public RndTransformable {
public:
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

    Shape mShape; // offset 0xB8, size 0x4
    float mRadius; // offset 0xBC, size 0x4
    float mMaxLength; // offset 0xC0, size 0x4
    float mMinLength; // offset 0xC4, size 0x4
    float mCurRadius; // offset 0xC8, size 0x4
    int mFlags; // offset 0xCC, size 0x4
};

#endif
