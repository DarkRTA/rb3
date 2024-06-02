#ifndef RNDOBJ_TEXBLENDER_H
#define RNDOBJ_TEXBLENDER_H
#include "rndobj/Draw.h"
#include "rndobj/Tex.h"
#include "rndobj/TexBlendController.h"
#include "obj/ObjPtr_p.h"

class RndTexBlender : public RndDrawable {
public:
    RndTexBlender();
    OBJ_CLASSNAME(TexBlender);
    OBJ_SET_TYPE(TexBlender);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual float GetDistanceToPlane(const Plane&, Vector3&);
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void DrawShowing(){}
    virtual ~RndTexBlender(){}

    DataNode OnGetRenderTextures(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndTexBlender)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndTexBlender)
    }

    ObjPtr<RndTex, class ObjectDir> mBaseMap;
    ObjPtr<RndTex, class ObjectDir> mNearMap;
    ObjPtr<RndTex, class ObjectDir> mFarMap;
    ObjPtr<RndTex, class ObjectDir> mOutputTextures;
    ObjPtrList<RndTexBlendController, class ObjectDir> mControllerList;
    ObjPtr<RndDrawable, class ObjectDir> mOwner;
    float mControllerInfluence;
    int unk70;
};

#endif
