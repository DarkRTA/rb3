#ifndef CHAR_CHARUPPERTWIST_H
#define CHAR_CHARUPPERTWIST_H
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

class CharUpperTwist : public CharPollable {
public:
    CharUpperTwist();
    OBJ_CLASSNAME(CharUpperTwist);
    OBJ_SET_TYPE(CharUpperTwist);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharUpperTwist();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;
    DELETE_OVERLOAD;

    ObjPtr<RndTransformable, ObjectDir> mUpperArm;
    ObjPtr<RndTransformable, ObjectDir> mTwist1;
    ObjPtr<RndTransformable, ObjectDir> mTwist2;
};

#endif
