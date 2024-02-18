#ifndef RND_RNDAMBIENTOCCLUSION_HPP
#define RND_RNDAMBIENTOCCLUSION_HPP
#include "obj/Object.h"

class RndAmbientOcclusion : public Hmx::Object {
public:
    RndAmbientOcclusion();
    virtual ~RndAmbientOcclusion();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    static Symbol StaticClassName();
};

#endif
