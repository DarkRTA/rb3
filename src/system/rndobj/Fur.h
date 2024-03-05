#ifndef RNDOBJ_FUR_H
#define RNDOBJ_FUR_H
#include "obj/Object.h"

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
};

#endif
