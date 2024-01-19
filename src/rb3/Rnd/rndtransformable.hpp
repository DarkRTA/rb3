#ifndef RND_RNDTRANSFORMABLE_HPP
#define RND_RNDTRANSFORMABLE_HPP
#include "rndhighlightable.hpp"
#include "rb3/hmx/object.hpp"
#include "rb3/data.hpp"

class RndTransformable : public RndHighlightable {
public:
    RndTransformable();
    virtual ~RndTransformable();

    virtual Symbol ClassName();
    virtual void SetType(Symbol *);
    virtual DataNode Handle(DataArray *, int);
    virtual int SyncProperty(DataNode *, DataArray *, int, int);
    virtual void Save(BinStream &);
    virtual void Copy(BinStream &);
    virtual void Load(BinStream &);
    virtual void Replace(char *, Hmx::Object *);
    virtual void Highlight();
    virtual void Print();
    virtual void UpdatedWorldXfm(); // links to fn_8076F540_stub, which returns void

    Symbol StaticClassName();
};

#endif
