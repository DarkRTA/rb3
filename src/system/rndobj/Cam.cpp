#include "rndobj/Cam.h"
#include "math/Rot.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Draw.h"
#include "rndobj/Rnd.h"
#include "rndobj/Trans.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

RndCam* RndCam::sCurrent = 0;
int CAM_REV = 12;
Transform sFlipYZ;

float RndCam::WorldToScreen(const Vector3& w, Vector2& s) const {
    s = mZRange;
}

void RndCam::Select() {
    if (sCurrent && sCurrent->mTargetTex.mPtr && sCurrent != this) {
        sCurrent->mTargetTex->FinishDrawTarget();
    }
    if (mCache->mFlags & 1) WorldXfm_Force();
    sCurrent = this;
    Rnd::Aspect a = TheRnd->mAspect;
    if (mAspect != a) UpdateLocal();
}

void RndCam::SetTargetTex(RndTex* tex){
    if(sCurrent == this && mTargetTex){
        mTargetTex->FinishDrawTarget();
    }
    mTargetTex = tex;
    UpdateLocal();
}

SAVE_OBJ(RndCam, 0x8F)

void RndCam::Load(BinStream& bs) {
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, CAM_REV)
    if (rev > 10) Hmx::Object::Load(bs);
    RndTransformable::Load(bs);
    if (rev < 10) RndDrawable::DumpLoad(bs);
    if (rev == 8) {
        ObjPtrList<Hmx::Object, class ObjectDir> d(this, kObjListNoNull); int x;
        bs >> x >> d;
    }
    bs >> mNearPlane >> mFarPlane >> mYFov;
    if (rev < 12) mYFov = ConvertFov(mYFov, 0.75);
    if (rev < 2) { int x; bs >> x; }
    bs >> mScreenRect;
    if (uint(rev - 1) <= 1) { int x; bs >> x; }
    if (rev > 3) bs >> mZRange;
    if (rev > 4) bs >> mTargetTex;
    if (rev == 6) { int x; bs >> x; }
    UpdateLocal();
}

BEGIN_COPYS(RndCam)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    CREATE_COPY(RndCam)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mNearPlane)
            COPY_MEMBER(mFarPlane)
            COPY_MEMBER(mYFov)
            COPY_MEMBER(mScreenRect)
            COPY_MEMBER(mZRange)
            COPY_MEMBER(mTargetTex)
        }
    END_COPYING_MEMBERS
    UpdateLocal();
END_COPYS

RndCam::RndCam() : mNearPlane(1.0f), mFarPlane(1000.0f), mYFov(0.6024178f), mUnknownFloat(1.0f), mZRange(0.0f, 1.0f), mScreenRect(0.0f, 0.0f, 1.0f, 1.0f), mTargetTex(this, 0) {
    UpdateLocal();
}

RndCam::~RndCam(){
    if(sCurrent == this) sCurrent = 0;
}

void RndCam::SetFrustum(float f1, float f2, float f3, float f4) {
    if (f2 - 0.0001f > f1 * 1000) {
        MILO_NOTIFY_ONCE("%s: %f/%f plane ratio exceeds 1000", mName, f2, f1);
        if (f2 == mFarPlane) f1 = f2 / 1000;
        if (f2 != mFarPlane) f2 = f1 * 1000;
    }
    mNearPlane = f1; mFarPlane = f2; mYFov = f3; mUnknownFloat = f4;
    UpdateLocal();
}

BEGIN_HANDLERS(RndCam)
    HANDLE(set_frustum, OnSetFrustum)
    HANDLE(set_z_range, OnSetZRange)
    HANDLE(far_plane, OnFarPlane)
    HANDLE(set_screen_rect, OnSetScreenRect)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1DB)
END_HANDLERS

DataNode RndCam::OnSetFrustum(const DataArray* da){
    float nearPlane, farPlane, yFov, temp;
    if(!da->FindData(near_plane, nearPlane, false))
        nearPlane = mNearPlane;
    if(!da->FindData(far_plane, farPlane, false))
        farPlane = mFarPlane;
    if(da->FindData(y_fov, yFov, false)) temp = yFov * DEG2RAD;
    else temp = mYFov;
    yFov = temp;
    SetFrustum(nearPlane, farPlane, yFov, 1.0f);
    return DataNode(0);
}

void RndCam::UpdateLocal() {

}

DataNode RndCam::OnSetZRange(const DataArray* da){
    SetZRange(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndCam::OnSetScreenRect(const DataArray* da){
    Hmx::Rect r(da->Float(2), da->Float(3), da->Float(4), da->Float(5));
    SetScreenRect(r);
    return DataNode(0);
}

DataNode RndCam::OnFarPlane(const DataArray*){
    return DataNode(mFarPlane);
}

BEGIN_PROPSYNCS(RndCam)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_PROP_SET(near_plane, mNearPlane, SetFrustum(_val.Float(), mFarPlane, mYFov, 1))
    SYNC_PROP_SET(far_plane, mFarPlane, SetFrustum(mNearPlane, _val.Float(), mYFov, 1))
    SYNC_PROP_SET(y_fov, mYFov * RAD2DEG, SetFrustum(mNearPlane, mFarPlane, _val.Float() * DEG2RAD, 1))
    SYNC_PROP(z_range, mZRange)
    SYNC_PROP_MODIFY_ALT(screen_rect, mScreenRect, UpdateLocal())
END_PROPSYNCS
