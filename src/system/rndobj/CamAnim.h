#ifndef RNDOBJ_CAMANIM_H
#define RNDOBJ_CAMANIM_H
#include "rndobj/Anim.h"
#include "rndobj/Cam.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/PropKeys.h"

class RndCamAnim : public RndAnimatable {
public:
    RndCamAnim();
    OBJ_CLASSNAME(CamAnim);
    OBJ_SET_TYPE(CamAnim);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndCamAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual Hmx::Object* AnimTarget(){ return mCam; }
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndCamAnim)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndCamAnim)
    }

    ObjPtr<RndCam, ObjectDir> mCam;
    Keys<float, float> mFovKeys;
    ObjOwnerPtr<RndCamAnim, ObjectDir> mKeysOwner;
};

#endif
