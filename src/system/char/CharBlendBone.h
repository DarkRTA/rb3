#ifndef CHAR_CHARBLENDBONE_H
#define CHAR_CHARBLENDBONE_H
#include "char/CharPollable.h"
#include "rndobj/Trans.h"
#include "obj/ObjList.h"

class CharBlendBone : public CharPollable {
public:

    class ConstraintSystem {
    public:
        ConstraintSystem();
        ConstraintSystem(Hmx::Object*);
        ObjPtr<RndTransformable, ObjectDir> mTarget; // 0x0
        float mWeight; // 0xc
    };

    CharBlendBone();
    OBJ_CLASSNAME(CharBlendBone);
    OBJ_SET_TYPE(CharBlendBone);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharBlendBone(){}
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjList<ConstraintSystem> mTargets; // 0x8
    ObjPtr<RndTransformable, ObjectDir> mSrc1; // 0x14
    ObjPtr<RndTransformable, ObjectDir> mSrc2; // 0x20
    bool mTransX; // 0x2c
    bool mTransY; // 0x2d
    bool mTransZ; // 0x2e
    bool mRotation; // 0x2f
};

BinStream& operator>>(BinStream&, CharBlendBone::ConstraintSystem&);

#endif