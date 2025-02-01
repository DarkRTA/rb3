#pragma once
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

/** "<p>Does all interpolation for the upperarm, assuming
 *      upperArm, upperTwist1 and 2 are under clavicle. Rotation about x is
 *      evenly distributed from clavicle->twist1->twist2->upperarm</p>
 *  Feeds the bones when executed." */
class CharUpperTwist : public CharPollable {
public:
    CharUpperTwist();
    OBJ_CLASSNAME(CharUpperTwist);
    OBJ_SET_TYPE(CharUpperTwist);
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll();
    virtual ~CharUpperTwist();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharUpperTwist)
    static void Init() { REGISTER_OBJ_FACTORY(CharUpperTwist) }

    /** "The upper arm bone" */
    ObjPtr<RndTransformable> mUpperArm; // 0x8
    /** "The upper arm twist1 bone" */
    ObjPtr<RndTransformable> mTwist1; // 0x14
    /** "The upper arm twist2 bone" */
    ObjPtr<RndTransformable> mTwist2; // 0x20
};
