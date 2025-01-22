#pragma once
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

/** "Copies local xfm from one bone to another at poll time" */
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

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS;
    NEW_OBJ(CharTransCopy)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharTransCopy)
    }

    /** "Object to copy the local xfm from" */
    ObjPtr<RndTransformable> mSrc; // 0x8
    /** "Object to copy the local xfm to" */
    ObjPtr<RndTransformable> mDest; // 0x14
};
