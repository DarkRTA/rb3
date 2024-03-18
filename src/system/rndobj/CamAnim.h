#ifndef RNDOBJ_CAMANIM_H
#define RNDOBJ_CAMANIM_H
#include "rndobj/Anim.h"
#include "rndobj/Cam.h"
#include "obj/ObjPtr_p.h"

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
    virtual RndAnimatable* AnimTarget(); // weak
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Print();

    ObjPtr<RndCam, ObjectDir> mCam;
    char mFovKeys[0x8]; // supposedly a Keys? which derives from vector
    ObjOwnerPtr<RndCamAnim, ObjectDir> mKeysOwner;
};

#endif
