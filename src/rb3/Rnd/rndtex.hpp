#ifndef RND_RNDTEX_HPP
#define RND_RNDTEX_HPP

#include "rb3/hmx/object.hpp"
#include "rb3/data.hpp"
#include "rb3/binstream.hpp"
#include "types.h"

class RndTex : Hmx::Object {
    typedef u32 Type;
    RndTex();
    virtual ~RndTex();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol *);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, uint) // uint should be
                                                                  // PropOp; TODO figure
                                                                  // out PropOp
    virtual void Save(BinStream &);
    virtual void Copy(Hmx::Object *, int);
    virtual void Load(BinStream &);
    virtual void Print();
    virtual void PreLoad(BinStream &);
    virtual void PostLoad(BinStream &);

    Symbol StaticClassName();
    RndTex NewObject();
};

#endif // RND_RNDTEX_HPP
