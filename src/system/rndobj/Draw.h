#ifndef RNDOBJ_DRAW_H
#define RNDOBJ_DRAW_H
#include "rndobj/Highlightable.h"
#include "obj/Object.h"
#include "math/Sphere.h"

class RndDrawable : public virtual RndHighlightable {
public:
    bool mShowing;
    Sphere mSphere;
    float mOrder;

    RndDrawable();
    virtual ~RndDrawable();
    OBJ_CLASSNAME(Draw);
    OBJ_SET_TYPE(Draw);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void UpdateSphere();
    // there's more virtual methods
};

#endif
