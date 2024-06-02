#ifndef RNDOBJ_MOTIONBLUR_H
#define RNDOBJ_MOTIONBLUR_H
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"

class RndMotionBlur : public RndDrawable {
public:
    RndMotionBlur();
    OBJ_CLASSNAME(MotionBlur);
    OBJ_SET_TYPE(MotionBlur);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing(){}
    virtual ~RndMotionBlur(){}

    bool CanMotionBlur(RndDrawable*);
    DataNode OnAllowedDrawable(const DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndMotionBlur)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMotionBlur)
    }

    ObjPtrList<RndDrawable, class ObjectDir> mDrawList;
};

#endif
