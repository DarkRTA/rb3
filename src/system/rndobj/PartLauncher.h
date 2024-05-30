#ifndef RNDOBJ_PARTLAUNCHER_H
#define RNDOBJ_PARTLAUNCHER_H
#include "rndobj/Poll.h"

class RndPartLauncher : public RndPollable {
public:
    RndPartLauncher();
    OBJ_CLASSNAME(PartLauncher);
    OBJ_SET_TYPE(PartLauncher);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~RndPartLauncher();
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
};

#endif
