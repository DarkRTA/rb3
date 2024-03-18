#ifndef RNDOBJ_SOFTPARTICLES_H
#define RNDOBJ_SOFTPARTICLES_H
#include "rndobj/Draw.h"

class RndSoftParticles : public RndDrawable {
public:
    RndSoftParticles();
    OBJ_CLASSNAME(SoftParticles);
    OBJ_SET_TYPE(SoftParticles);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndSoftParticles(){}

    DELETE_OVERLOAD;

    static unsigned short gRev;
    static unsigned short gAltRev;
};

#endif
