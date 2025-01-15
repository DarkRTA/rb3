#pragma once
#include "char/CharPollable.h"
#include "char/CharWeightable.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "utl/MemMgr.h"

/** "Rotate a bone to point towards targets" */
class CharBoneTwist : public CharPollable, public CharWeightable {
public:
    CharBoneTwist();
    OBJ_CLASSNAME(CharBoneTwist);
    OBJ_SET_TYPE(CharBoneTwist);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharBoneTwist(){}
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    NEW_OBJ(CharBoneTwist)
    DECLARE_REVS
    NEW_OVERLOAD
    DELETE_OVERLOAD
    static void Init() { REGISTER_OBJ_FACTORY(CharBoneTwist) }

    /** "Bone to move" */
    ObjPtr<RndTransformable> mBone; // 0x20
    /** "Targets to average to point bone at" */
    ObjPtrList<RndTransformable> mTargets; // 0x2c
};
