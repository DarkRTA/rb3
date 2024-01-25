#ifndef RND_RNDTRANSPROXY_HPP
#define RND_RNDTRANSPROXY_HPP
#include "rndtransformable.hpp"
#include "objptr.hpp"
#include "symbol.hpp"

class RndTransProxy : public virtual RndTransformable {
public:
    RndTransProxy();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndTransProxy();

    Symbol StaticClassName();

    ObjPtr<ObjectDir, ObjectDir> objdirPtr;
    Symbol sym;
};

#endif
