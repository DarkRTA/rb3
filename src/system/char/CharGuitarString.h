#ifndef CHAR_CHARGUITARSTRING_H
#define CHAR_CHARGUITARSTRING_H
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include <list>

class RndTransformable;

class CharGuitarString : public CharPollable {
public:
    CharGuitarString();
    OBJ_CLASSNAME(CharGuitarString);
    OBJ_SET_TYPE(CharGuitarString);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharGuitarString();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    
    DELETE_OVERLOAD;

    static unsigned short gRev;
    static unsigned short gAltRev;

    bool mOpen;
    ObjPtr<RndTransformable, class ObjectDir> mNut;
    ObjPtr<RndTransformable, class ObjectDir> mBridge;
    ObjPtr<RndTransformable, class ObjectDir> mBend;
    ObjPtr<RndTransformable, class ObjectDir> mTarget;

};

#endif
