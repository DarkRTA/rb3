#ifndef CHAR_CHARBLENDBONE_H
#define CHAR_CHARBLENDBONE_H
#include "char/CharPollable.h"
#include "rndobj/Trans.h"
#include "obj/ObjList.h"

class CharBlendBone : public CharPollable {
public:

    class ConstraintSystem {
    public:
        ObjPtr<RndTransformable, ObjectDir> mTarget;
        float mWeight;
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

    ObjList<ConstraintSystem> mTargets;
    ObjPtr<RndTransformable, ObjectDir> mSrc1;
    ObjPtr<RndTransformable, ObjectDir> mSrc2;
    bool mTransX;
    bool mTransY;
    bool mTransZ;
    bool mRotation;
};

#endif
