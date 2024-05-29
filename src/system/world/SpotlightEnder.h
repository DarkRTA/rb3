#ifndef WORLD_SPOTLIGHTENDER_H
#define WORLD_SPOTLIGHTENDER_H
#include "rndobj/Draw.h"

class SpotlightEnder : public RndDrawable {
public:
    SpotlightEnder();
    OBJ_CLASSNAME(SpotlightEnder);
    OBJ_SET_TYPE(SpotlightEnder);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~SpotlightEnder();

    DECLARE_REVS;
    DELETE_OVERLOAD;
};

#endif
