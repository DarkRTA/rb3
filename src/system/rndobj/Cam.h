#ifndef RNDOBJ_CAM_H
#define RNDOBJ_CAM_H
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

    static RndCam* sCurrent;

    DELETE_OVERLOAD;

    Transform mInvWorldXfm; // offset 0xC0, size 0x40
    Transform mLocalProjectXfm; // offset 0x100, size 0x40
    Transform mInvLocalProjectXfm; // offset 0x140, size 0x40
    Transform mWorldProjectXfm; // offset 0x180, size 0x40
    Transform mInvWorldProjectXfm; // offset 0x1C0, size 0x40
    Frustum mLocalFrustum; // offset 0x200, size 0x60
    Frustum mWorldFrustum; // offset 0x260, size 0x60
    float mNearPlane; // offset 0x2C0, size 0x4
    float mFarPlane; // offset 0x2C4, size 0x4
    float mYFov; // offset 0x2C8, size 0x4
    Vector2 mZRange; // offset 0x2CC, size 0x8
    Hmx::Rect mScreenRect; // offset 0x2D4, size 0x10
    ObjPtr<RndTex, ObjectDir> mTargetTex; // offset 0x2E4, size 0xC
};

#endif
