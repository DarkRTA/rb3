#include "Env.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

RndEnviron* RndEnviron::sCurrent;
bool RndEnviron::sCurrentPosSet;
Vector3 RndEnviron::sCurrentPos = Vector3(0,0,0);
// BoxMapLighting RndEnviron::sGlobalLighting();
static int ENVIRON_REV = 15;

void RndEnviron::Select(const Vector3* v) {
    sCurrent = this;
    sCurrentPosSet = (int)v;
    if (v) {
        sCurrentPos = *v;
    } else {
        sCurrentPos.z = 0;
        sCurrentPos.y = 0;
        sCurrentPos.x = 0;
    }
    i1 = 0;
    i2 = 0;
    i3 = 0;
    i4 = 0;
    mHasPointCubeTex = false;
    i0 = 0;
    ReclassifyLights();
}

RndEnviron::RndEnviron() : mLightsReal(this, kObjListAllowNull), mLightsApprox(this, kObjListAllowNull), mLights3(this, kObjListAllowNull), f0(0), f1(0), f2(0), f3(1),
                        i0(0), i1(0), i2(0), i3(0), i4(0), mHasPointCubeTex(false), mOwner(this, this), mTrans(this, NULL), mColor() {mTimer.Restart();}

RndEnviron::~RndEnviron() {
    if (this == sCurrent) {
        sCurrent = NULL;
        sCurrentPosSet = NULL;
        sCurrentPos.z = 0;
        sCurrentPos.y = 0;
        sCurrentPos.x = 0;
    }
}

SAVE_OBJ(RndEnviron, 119)

/*void RndEnviron::Load(BinStream& bs) { // some weird shit goin on in here
    LOAD_REVS(bs)
    ASSERT_REVS(ENVIRON_REV, 0)
    if (gRev > 1) Hmx::Object::Load(bs);
    if (gRev < 3) RndDrawable::DumpLoad(bs);
    bs >> mTrans;
}*/

BEGIN_COPYS(RndEnviron)
    COPY_SUPERCLASS(Hmx::Object)
    GET_COPY_AND_ASSERT(RndEnviron, 365)
END_COPYS

void RndEnviron::ReclassifyLights() {

}

BEGIN_HANDLERS(RndEnviron)
    HANDLE_ACTION(remove_all_lights, OnRemoveAllLights())
    HANDLE_ACTION(toggle_ao, mAmbientOcclusion = !mAmbientOcclusion)
    HANDLE_ACTION(remove_light, RemoveLight(_msg->Obj<RndLight>(2)))
    HANDLE(allowable_lights_real, OnAllowableLights_Real)
    HANDLE(allowable_lights_approx, OnAllowableLights_Approx)
    HANDLE_ACTION(select, Select(NULL))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(582)
END_HANDLERS

BEGIN_PROPSYNCS(RndEnviron)
    SYNC_PROP(lights_real, mLightsReal)
    SYNC_PROP(lights_approx, mLightsApprox)
    SYNC_PROP(ambient_color, mOwner)

    SYNC_PROP(contrast, mColor.mContrast)
    // SYNC_PROP(in_lo, mColor.mLevelInLo)
    if (sym == in_lo) {
        if (PropSync(mColor.mLevelInLo, _val, _prop, _i + 1, _op)) {
            if (!(_op & 0x11)) mColor.AdjustColorXfm();
            return true;
        }
        return false;
    }
    // SYNC_PROP(in_hi, mColor.mLevelInHi)
    if (sym == in_hi) {
        if (PropSync(mColor.mLevelInHi, _val, _prop, _i + 1, _op)) {
            if (!(_op & 0x11)) mColor.AdjustColorXfm();
            return true;
        }
        return false;
    }
    // SYNC_PROP_ACTION(out_lo, mColor.mLevelOutLo, 0x11, mColor.AdjustColorXfm())
    if (sym == out_lo) {
        if (PropSync(mColor.mLevelOutLo, _val, _prop, _i + 1, _op)) {
            if (!(_op & 0x11)) mColor.AdjustColorXfm();
            return true;
        }
        return false;
    }
    // SYNC_PROP_ACTION(out_hi, mColor.mLevelOutHi, 0x11, mColor.AdjustColorXfm())
    if (sym == out_hi) {
        if (PropSync(mColor.mLevelOutHi, _val, _prop, _i + 1, _op)) {
            if (!(_op & 0x11)) mColor.AdjustColorXfm();
            return true;
        }
        return false;
    }
    SYNC_PROP(animate_from_preset, mAnimateFromPreset)
END_PROPSYNCS

bool RndEnviron::HasPointCubeTex() const {
    return mHasPointCubeTex;
}
