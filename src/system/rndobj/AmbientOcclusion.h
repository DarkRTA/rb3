#ifndef RNDOBJ_AMBIENTOCCLUSION_H
#define RNDOBJ_AMBIENTOCCLUSION_H
#include "obj/Object.h"

class RndAmbientOcclusion : public Hmx::Object {
public:
    RndAmbientOcclusion();
    virtual ~RndAmbientOcclusion(){}
    OBJ_CLASSNAME(AmbientOcclusion);
    OBJ_SET_TYPE(AmbientOcclusion);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DELETE_OVERLOAD;

    static unsigned short gRev;
    static unsigned short gAltRev;

};

#endif
