#ifndef RNDOBJ_FUR_H
#define RNDOBJ_FUR_H
#include "milo_types.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Tex.h"

class RndFur : public Hmx::Object {
public:
    RndFur();
    virtual ~RndFur(){}
    OBJ_CLASSNAME(Fur);
    OBJ_SET_TYPE(Fur);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    void operator delete(void* v){
        _MemFree(v);
    }

    static ushort gRev;
    static ushort gAltRev;
};

#endif
