#ifndef RNDOBJ_FONT_H
#define RNDOBJ_FONT_H

#include "obj/Object.h"
#include "utl/MemMgr.h"

class RndFont : public Hmx::Object {
public:
    RndFont();
    virtual ~RndFont();
    OBJ_CLASSNAME(Font);
    OBJ_SET_TYPE(Font);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Print();

    NEW_OVERLOAD;
    NEW_OBJ(RndFont)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndFont)
    }
}; 

#endif // RNDOBJ_FONT_H
