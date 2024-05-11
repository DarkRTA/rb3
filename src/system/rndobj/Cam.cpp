#include "rndobj/Cam.h"
#include "obj/ObjPtr_p.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

RndCam* RndCam::sCurrent = 0;
int CAM_REV = 12;
Transform sFlipYZ;

ADD_NOTIFS

void RndCam::WorldToScreen(const Vector3& w, Vector2& s) const {
    s = mZRange;
}

SAVE_OBJ(RndCam, 0x8F)

void RndCam::Load(BinStream& bs) {
    int rev;
    bs >> rev;
    if (rev > CAM_REV) {
        MILO_FAIL("%s can't load new %s version %d > %d", PathName(this), ClassName(), rev, CAM_REV);
    }
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

BEGIN_PROPSYNCS(RndCam)
    SYNC_PROP(z_range, mZRange)
    SYNC_PROP_ACTION(screen_rect, mScreenRect, 0x11, UpdateLocal())
END_PROPSYNCS
