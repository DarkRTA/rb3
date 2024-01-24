#ifndef RND_RNDANIMATABLE_HPP
#define RND_RNDANIMATABLE_HPP
#include "hmx/object.hpp"

class RndFur : public Hmx::Object {
public:
    RndFur();
    virtual ~RndFur();
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
