#include "rndobj/Cam.h"
#include "utl/Symbols.h"

RndCam* RndCam::sCurrent = 0;

void RndCam::SetTargetTex(RndTex* tex){
    if(sCurrent == this && mTargetTex){
        mTargetTex->FinishDrawTarget();
    }
    mTargetTex = tex;
    UpdateLocal();
}

SAVE_OBJ(RndCam, 0x8F);

BEGIN_COPYS(RndCam)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    GET_COPY(RndCam)
    if(c && ty != kCopyFromMax){
        COPY_MEMBER(mNearPlane)
        COPY_MEMBER(mFarPlane)
        COPY_MEMBER(mYFov)
        COPY_MEMBER(mScreenRect)
        COPY_MEMBER(mZRange)
        COPY_MEMBER(mTargetTex)
    }
    UpdateLocal();
END_COPYS

RndCam::RndCam() : mNearPlane(1.0f), mFarPlane(1000.0f), mYFov(0.6024178f), mUnknownFloat(1.0f), mZRange(0.0f, 1.0f), mScreenRect(0.0f, 0.0f, 1.0f, 1.0f), mTargetTex(this, 0) {
    UpdateLocal();
}

RndCam::~RndCam(){
    if(sCurrent == this) sCurrent = 0;
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
    float nearPlane, farPlane, yFov;
    if(!da->FindData(near_plane, nearPlane, false))
        nearPlane = mNearPlane;
    if(!da->FindData(far_plane, farPlane, false))
        farPlane = mFarPlane;
    if(da->FindData(y_fov, yFov, false)) yFov *= 0.017453292f;
    else yFov = mYFov;
    SetFrustum(nearPlane, farPlane, yFov, 1.0f);
    return DataNode(0);
}

DataNode RndCam::OnSetZRange(const DataArray* da){
    mZRange.Set(da->Float(2), da->Float(3));
    return DataNode(0);
}

DataNode RndCam::OnSetScreenRect(const DataArray* da){
    mScreenRect.Set(da->Float(2), da->Float(3), da->Float(4), da->Float(5));
    UpdateLocal();
    return DataNode(0);
}

DataNode RndCam::OnFarPlane(const DataArray*){
    return DataNode(mFarPlane);
}