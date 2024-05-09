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
    void UpdateLocal();
    DataNode OnSetFrustum(const DataArray*);
    DataNode OnSetZRange(const DataArray*);
    DataNode OnSetScreenRect(const DataArray*);
    DataNode OnFarPlane(const DataArray*);

    static RndCam* sCurrent;
    NEW_OBJ(RndCam)
    DELETE_OVERLOAD;

    Transform mInvWorldXfm;
    Transform mLocalProjectXfm;
    Transform mInvLocalProjectXfm;
    Transform mWorldProjectXfm;
    Transform mInvWorldProjectXfm;
    Frustum mLocalFrustum;
    Frustum mWorldFrustum;
    float mNearPlane;
    float mFarPlane;
    float mYFov;
    float mUnknownFloat;
    Vector2 mZRange;
    Hmx::Rect mScreenRect;
    ObjPtr<RndTex, class ObjectDir> mTargetTex;
    int asdf;
};

#endif
