#ifndef RNDOBJ_SCREENMASK_H
#define RNDOBJ_SCREENMASK_H
#include "rndobj/Draw.h"
#include "rndobj/Mat.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "math/Geo.h"
#include "math/Color.h"

class RndScreenMask : public RndDrawable {
public:
    RndScreenMask();
    OBJ_CLASSNAME(ScreenMask);
    OBJ_SET_TYPE(ScreenMask);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~RndScreenMask(){}

    DELETE_OVERLOAD;

    ObjPtr<RndMat, class ObjectDir> mMat;
    Hmx::Color mColor;
    Hmx::Rect mRect;
};

#endif
