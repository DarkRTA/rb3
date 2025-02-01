#pragma once
#include "char/CharPollable.h"
#include "rndobj/Trans.h"
#include "obj/ObjList.h"

/** "Set up a constraint between a series of target bones" */
class CharBlendBone : public CharPollable {
public:
    class ConstraintSystem {
    public:
        ConstraintSystem();
        ConstraintSystem(Hmx::Object *);

        /** "object to constrain" */
        ObjPtr<RndTransformable> mTarget; // 0x0
        /** "influence value, from 0 to 1" */
        float mWeight; // 0xc
    };

    CharBlendBone();
    OBJ_CLASSNAME(CharBlendBone);
    OBJ_SET_TYPE(CharBlendBone);
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll();
    virtual ~CharBlendBone() {}
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharBlendBone)
    static void Init() { REGISTER_OBJ_FACTORY(CharBlendBone) }

    ObjList<ConstraintSystem> mTargets; // 0x8
    /** "Source object to drive constraint" */
    ObjPtr<RndTransformable> mSrc1; // 0x14
    /** "Source object to drive constraint" */
    ObjPtr<RndTransformable> mSrc2; // 0x20
    /** "Apply x translation?" */
    bool mTransX; // 0x2c
    /** "Apply y translation?" */
    bool mTransY; // 0x2d
    /** "Apply z translation?" */
    bool mTransZ; // 0x2e
    /** "Apply rotation constraint?" */
    bool mRotation; // 0x2f
};

BinStream &operator>>(BinStream &, CharBlendBone::ConstraintSystem &);
