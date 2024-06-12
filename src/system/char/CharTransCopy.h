#ifndef CHAR_CHARTRANSCOPY_H
#define CHAR_CHARTRANSCOPY_H
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

class CharTransCopy : public CharPollable {
public:
    CharTransCopy();
    OBJ_CLASSNAME(CharTransCopy);
    OBJ_SET_TYPE(CharTransCopy);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharTransCopy();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DELETE_OVERLOAD;
    DECLARE_REVS;

    ObjPtr<RndTransformable, class ObjectDir> mSrc; // 0x8
    ObjPtr<RndTransformable, class ObjectDir> mDest; // 0x14
};

#endif
