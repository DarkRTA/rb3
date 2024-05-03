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

RndEnviron::RndEnviron() : mLightsReal(this, kObjListNoNull), mLightsApprox(this, kObjListNoNull), mLightsOld(this, kObjListNoNull), mAmbientColor(0.0f, 0.0f, 0.0f),
    i0(0), i1(0), i2(0), i3(0), i4(0), mHasPointCubeTex(false), mOwner(this, this), 
    mFog(0), f1(0.0f), f2(1.0f), f3(1.0f), f4(1.0f), f5(1.0f), f6(1.0f), unk9c(0), unka0(0.0f), unka4(1000.0f), unka8(1.0f),
    mTrans(this, NULL), 
    unkb8(0.0f), unkbc(0.0f), unkc0(0.0f), unkc4(0.0f),
    mColorXfm(),
    unk14c(0), unk14d(1), unk14e(1), unk150(1.0f), mTimer(), unk188(0.0f), unk18c(0.1f), unk190(1.0f), unk194(1.0f), b(0), mAnimateFromPreset(1), mAmbientOcclusion(1) {
    mTimer.Restart();
}

RndEnviron::~RndEnviron() {
    if (sCurrent == this) {
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

bool RndEnviron::IsValidRealLight(const RndLight*) const {
    bool ret = false; if (mTimer.mRunning != 0) {
        if (mTimer.mRunning != 2) return ret;
    }
    ret = true;
    return ret;
}

bool RndEnviron::IsFake(RndLight* l) const {
    return IsLightInList(l, mLightsApprox);
}

bool RndEnviron::IsReal(RndLight* l) const {
    return IsLightInList(l, mLightsReal);
}

bool RndEnviron::FogEnable() const {
    return mOwner->mFog;
}

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

void RndEnviron::ApplyApproxLighting(const _GXColor*) { }

BEGIN_PROPSYNCS(RndEnviron)
    SYNC_PROP(lights_real, mLightsReal)
    SYNC_PROP(lights_approx, mLightsApprox)
    SYNC_PROP(ambient_color, mOwner)

    SYNC_PROP(contrast, mColorXfm.mContrast)
    // SYNC_PROP(in_lo, mColorXfm.mLevelInLo)
    if (sym == in_lo) {
        if (PropSync(mColorXfm.mLevelInLo, _val, _prop, _i + 1, _op)) {
            if (!(_op & 0x11)) mColorXfm.AdjustColorXfm();
            return true;
        }
        return false;
    }
    // SYNC_PROP(in_hi, mColorXfm.mLevelInHi)
    if (sym == in_hi) {
        if (PropSync(mColorXfm.mLevelInHi, _val, _prop, _i + 1, _op)) {
            if (!(_op & 0x11)) mColorXfm.AdjustColorXfm();
            return true;
        }
        return false;
    }
    // SYNC_PROP_ACTION(out_lo, mColorXfm.mLevelOutLo, 0x11, mColorXfm.AdjustColorXfm())
    if (sym == out_lo) {
        if (PropSync(mColorXfm.mLevelOutLo, _val, _prop, _i + 1, _op)) {
            if (!(_op & 0x11)) mColorXfm.AdjustColorXfm();
            return true;
        }
        return false;
    }
    // SYNC_PROP_ACTION(out_hi, mColorXfm.mLevelOutHi, 0x11, mColorXfm.AdjustColorXfm())
    if (sym == out_hi) {
        if (PropSync(mColorXfm.mLevelOutHi, _val, _prop, _i + 1, _op)) {
            if (!(_op & 0x11)) mColorXfm.AdjustColorXfm();
            return true;
        }
        return false;
    }
    SYNC_PROP(animate_from_preset, mAnimateFromPreset)
END_PROPSYNCS

bool RndEnviron::HasPointCubeTex() const {
    return mHasPointCubeTex;
}
