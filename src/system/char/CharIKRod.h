#ifndef CHAR_CHARIKROD_H
#define CHAR_CHARIKROD_H
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

class CharIKRod : public CharPollable {
public:
    CharIKRod();
    OBJ_CLASSNAME(Poll);
    OBJ_SET_TYPE(Poll);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharIKRod();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DELETE_OVERLOAD;

    ObjPtr<RndTransformable, ObjectDir> mLeftEnd;
    ObjPtr<RndTransformable, ObjectDir> mRightEnd;
    float mDestPos;
    ObjPtr<RndTransformable, ObjectDir> mSideAxis;
    bool mVertical;
    ObjPtr<RndTransformable, ObjectDir> mDest;
    Transform mXfm;
};

#endif
