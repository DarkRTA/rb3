#ifndef RNDOBJ_CAM_H
#define RNDOBJ_CAM_H
#include "obj/Object.h"
#include "rndobj/Trans.h"
#include "math/Mtx.h"
#include "math/Vec.h"
#include "math/Geo.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Tex.h"

class RndCam : public RndTransformable {
public:
    RndCam();
    OBJ_CLASSNAME(Cam);
    OBJ_SET_TYPE(Cam);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndCam();
    virtual void UpdatedWorldXfm();
    virtual void Select();
    virtual int ProjectZ(float){ return 0; }

    void SetFrustum(float, float, float, float);
    void SetTargetTex(RndTex*);
    void WorldToScreen(const Vector3&, Vector2&) const;  
    void UpdateLocal();
    DataNode OnSetFrustum(const DataArray*);
    DataNode OnSetZRange(const DataArray*);
    DataNode OnSetScreenRect(const DataArray*);
    DataNode OnFarPlane(const DataArray*);

    static RndCam* sCurrent;
    NEW_OBJ(RndCam)
    DELETE_OVERLOAD;
    static void Init(){
        REGISTER_OBJ_FACTORY(RndCam)
    }

    Transform mInvWorldXfm;
    Transform mLocalProjectXfm;
    Transform mInvLocalProjectXfm;
    Transform mWorldProjectXfm;
    Transform mInvWorldProjectXfm;
    Frustum mLocalFrustum; // 0x180
    Frustum mWorldFrustum; // 0x1E0
    float mNearPlane; // 0x240
    float mFarPlane; // 0x244
    float mYFov; // 0x248
    float mUnknownFloat; // 0x24C
    Vector2 mZRange; // 0x250
    Hmx::Rect mScreenRect; // 0x258
    ObjPtr<RndTex, class ObjectDir> mTargetTex; // 0x268
    int asdf; // 0x274
};

#endif
