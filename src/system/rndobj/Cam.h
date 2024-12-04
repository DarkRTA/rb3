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

/**
 * @brief A camera that renders the scene.
 * Original _objects description:
 * "A Camera object is drawable and transformable. When drawn
 * it sets up projection and clipping parameters for
 * subsequent draw siblings."
 */
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
    virtual u32 ProjectZ(float){ return 0; }

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
    const Transform& LocalProjectXfm() const { return mLocalProjectXfm; }
    
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

    /**
     * @brief The near-clipping plane.
     * Original _objects description:
     * "The distance in world coordinates to the near clipping
     * plane. The near/far ratio is limited to 1:1000 to preserve
     * Z-buffer resolution."
     */
    float mNearPlane; // 0x240

    /**
     * @brief The far-clipping plane.
     * Original _object description:
     * "The distance in world coordinates to the far clipping
     * plane. The near/far ratio is limited to 1:1000 to preserve
     * Z-buffer resolution. Note that on the PS2, object polys are
     * culled rather than clipped to the far plane."
     */
    float mFarPlane; // 0x244
    
    float mYFov; // 0x248
    float mUnknownFloat; // 0x24C

    /**
     * @brief 
     * Original _objects description:
     * "The part of the Z-buffer to use, in normalized
     * coordinates. It can be useful to draw a scene where the near
     * and far planes must exceed the 1:1000 ratio (so multiple
     * cameras are used to draw farthest to nearest objects, each
     * using a closer range of the z-buffer) or to leave some
     * z-buffer for HUD overlay objects."
     */
    Vector2 mZRange; // 0x250

    /**
     * @brief The segment of the screen to draw to.
     * Original _objects description:
     * "The area of the screen in normalized coordinates
     * (0 to 1) to draw into."
     */
    Hmx::Rect mScreenRect; // 0x258

    ObjPtr<RndTex> mTargetTex; // 0x268
    Rnd::Aspect mAspect; // 0x274
};

#endif
