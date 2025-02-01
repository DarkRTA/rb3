#pragma once
#include "rndobj/Anim.h"
#include "rndobj/Cam.h"
#include "obj/ObjPtr_p.h"
#include "math/Key.h"

/**
 * @brief A class for animating Cams.
 * Original _objects description:
 * "A CamAnim object animates Camera properties."
 */
class RndCamAnim : public RndAnimatable {
public:
    RndCamAnim();
    OBJ_CLASSNAME(CamAnim);
    OBJ_SET_TYPE(CamAnim);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~RndCamAnim();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual Hmx::Object *AnimTarget() { return mCam; }
    virtual void SetKey(float);
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void Print();

    Keys<float, float> &FovKeys() { return mKeysOwner->mFovKeys; }
    RndCamAnim *KeysOwner() const { return mKeysOwner; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndCamAnim)
    static void Init() { REGISTER_OBJ_FACTORY(RndCamAnim) }

    /** The Cam to animate. */
    ObjPtr<RndCam> mCam; // 0x10
    /** The collection of FOV keys. */
    Keys<float, float> mFovKeys; // 0x1c
    /** The CamAnim that owns all of these keys. */
    ObjOwnerPtr<RndCamAnim> mKeysOwner; // 0x24
};
