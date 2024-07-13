#ifndef CHAR_CHARPOSCONSTRAINT_H
#define CHAR_CHARPOSCONSTRAINT_H
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "math/Geo.h"

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
    DELETE_OVERLOAD;

    ObjPtr<RndTransformable, ObjectDir> mSrc; // 0x8
    ObjPtrList<RndTransformable, ObjectDir> mTargets; // 0x14
    Box mBox; // 0x24
};

#endif
