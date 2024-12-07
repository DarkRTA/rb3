#ifndef CHAR_CHARBONETWIST_H
#define CHAR_CHARBONETWIST_H
#include "char/CharPollable.h"
#include "char/CharWeightable.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "utl/MemMgr.h"

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

    ObjPtr<RndTransformable, ObjectDir> mBone; // 0x20
    ObjPtrList<RndTransformable, ObjectDir> mTargets; // 0x2c
};

#endif
