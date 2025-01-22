#pragma once
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "math/Geo.h"

/** "Forces the targets to be within a world space bounding box relative to source." */
class CharPosConstraint : public CharPollable {
public:
    CharPosConstraint();
    OBJ_CLASSNAME(CharPosConstraint);
    OBJ_SET_TYPE(CharPosConstraint);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharPosConstraint();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharPosConstraint)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharPosConstraint)
    }

    /** "Bone to be higher than" */
    ObjPtr<RndTransformable> mSrc; // 0x8
    /** "Bones to constrain" */
    ObjPtrList<RndTransformable> mTargets; // 0x14
    /** "Bounding box, make min > max to ignore that dimension" */
    Box mBox; // 0x24
};
