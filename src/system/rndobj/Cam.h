#ifndef RNDOBJ_CAM_H
#define RNDOBJ_CAM_H
#include "obj/Object.h"
#include "rndobj/Trans.h"
#include "math/Mtx.h"
#include "math/Vec.h"
#include "math/Geo.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Rnd.h"
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
    float WorldToScreen(const Vector3&, Vector2&) const;
    void ScreenToWorld(const Vector2&, float, Vector3&) const;
    void UpdateLocal();
    DataNode OnSetFrustum(const DataArray*);
    DataNode OnSetZRange(const DataArray*);
    DataNode OnSetScreenRect(const DataArray*);
    DataNode OnFarPlane(const DataArray*);
    
    float NearPlane() const { return mNearPlane; }
    float FarPlane() const { return mFarPlane; }
    float YFov() const { return mYFov; }
    RndTex* TargetTex(){ return mTargetTex; }
    void SetZRange(float f1, float f2){ mZRange.Set(f1, f2); }
    
    bool CompareSphereToWorld(const Sphere& s) const {
        return s > mWorldFrustum;
    }

    void SetScreenRect(const Hmx::Rect& rect){
        mScreenRect = rect;
        UpdateLocal();
    }

    static RndCam* sCurrent;
    static RndCam* Current(){ return sCurrent; }

    NEW_OBJ(RndCam)
    DELETE_OVERLOAD;
    static void Init(){
        REGISTER_OBJ_FACTORY(RndCam)
    }

    Transform mInvWorldXfm; // 0x90
    Transform mLocalProjectXfm; // 0xC0
    Transform mInvLocalProjectXfm; // 0xF0
    Transform mWorldProjectXfm; // 0x120
    Transform mInvWorldProjectXfm; // 0x150
    Frustum mLocalFrustum; // 0x180
    Frustum mWorldFrustum; // 0x1E0
    float mNearPlane; // 0x240
    float mFarPlane; // 0x244
    float mYFov; // 0x248
    float mUnknownFloat; // 0x24C
    Vector2 mZRange; // 0x250
    Hmx::Rect mScreenRect; // 0x258
    ObjPtr<RndTex, class ObjectDir> mTargetTex; // 0x268
    Rnd::Aspect mAspect; // 0x274
};

#endif
