#ifndef CHAR_CHARBONESBLENDER_H
#define CHAR_CHARBONESBLENDER_H
#include "char/CharBones.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"

class CharBonesBlender : public CharPollable, public CharBonesAlloc {
public:
    CharBonesBlender();
    OBJ_CLASSNAME(CharBonesBlender);
    OBJ_SET_TYPE(CharBonesBlender);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Enter();
    virtual ~CharBonesBlender();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual void ReallocateInternal();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DELETE_OVERLOAD;
    
    ObjPtr<CharBonesObject, ObjectDir> mDest;
    Symbol mClipType;
};

#endif