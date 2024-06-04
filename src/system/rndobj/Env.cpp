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
    mNumLightsReal = 0;
    mNumLightsApprox = 0;
    mNumLightsPoint = 0;
    mNumLightsProj = 0;
    mHasPointCubeTex = false;
    mAmbientAlpha = 0;
    ReclassifyLights();
}

RndEnviron::RndEnviron() : mLightsReal(this, kObjListNoNull), mLightsApprox(this, kObjListNoNull), mLightsOld(this, kObjListNoNull), mAmbientColor(0.0f, 0.0f, 0.0f),
    mAmbientAlpha(0), mNumLightsReal(0), mNumLightsApprox(0), mNumLightsPoint(0), mNumLightsProj(0), mHasPointCubeTex(false), mAmbientFogOwner(this, this), 
    mFogEnable(0), mFogStart(0.0f), mFogEnd(1.0f), mFogColor(), mFadeOut(0), mFadeStart(0.0f), mFadeEnd(1000.0f), mFadeMax(1.0f),
    mFadeRef(this, NULL), mLRFade(0.0f, 0.0f, 0.0f, 0.0f), mColorXfm(),
    mUseColorAdjust(0), mAnimateFromPreset(1), mAOEnabled(1), mAOStrength(1.0f), mUpdateTimer(), mIntensityAverage(0.0f), 
    mIntensityRate(0.1f), mExposure(1.0f), mWhitePoint(1.0f), mUseToneMapping(0), mUseApprox_Local(1), mUseApprox_Global(1) {
    mUpdateTimer.Restart();
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
    bs >> mFadeRef;
}*/

BEGIN_COPYS(RndEnviron)
    COPY_SUPERCLASS(Hmx::Object)
    if(ty != kCopyFromMax){
        CREATE_COPY(RndEnviron)
        BEGIN_COPYING_MEMBERS
            COPY_MEMBER(mLightsReal)
            COPY_MEMBER(mLightsApprox)
            COPY_MEMBER(mLightsOld)
            COPY_MEMBER(mFadeOut)
            COPY_MEMBER(mFadeStart)
            COPY_MEMBER(mFadeEnd)
            COPY_MEMBER(mFadeMax)
            COPY_MEMBER(mFadeRef)
            COPY_MEMBER(mLRFade)
            COPY_MEMBER(mUseColorAdjust)
            COPY_MEMBER(mColorXfm)
            COPY_MEMBER(mAnimateFromPreset)
            COPY_MEMBER(mAOEnabled)
            COPY_MEMBER(mAOStrength)
            COPY_MEMBER(mIntensityRate)
            COPY_MEMBER(mExposure)
            COPY_MEMBER(mWhitePoint)
            COPY_MEMBER(mUseToneMapping)
            if(ty == kCopyShallow || ty == kCopyFromMax && c->mAmbientFogOwner != c){
                COPY_MEMBER(mAmbientFogOwner)
            }
            else {
                mAmbientFogOwner = this;
                mAmbientColor = mAmbientFogOwner->mAmbientColor;
                mFogColor = mAmbientFogOwner->mFogColor;
                mFogStart = mAmbientFogOwner->mFogStart;
                mFogEnd = mAmbientFogOwner->mFogEnd;
                mFogEnable = mAmbientFogOwner->mFogEnable;
            }
        END_COPYING_MEMBERS
    }
END_COPYS

bool RndEnviron::IsValidRealLight(const RndLight*) const {
    bool ret = false; if (mUpdateTimer.mRunning != 0) {
        if (mUpdateTimer.mRunning != 2) return ret;
    }
    ret = true;
    return ret;
}

bool RndEnviron::IsLightInList(const RndLight* light, const ObjPtrList<RndLight, class ObjectDir>& pList) const {
    if(light == 0) return 0;
    for(ObjPtrList<RndLight, class ObjectDir>::Node* it = pList.mNodes; it != 0; it = it->next){
        RndLight* itLight = it->obj;
        if(itLight == light) return itLight;
    }
    return 0;
}

bool RndEnviron::IsFake(RndLight* l) const {
    return IsLightInList(l, mLightsApprox);
}

bool RndEnviron::IsReal(RndLight* l) const {
    return IsLightInList(l, mLightsReal);
}

bool RndEnviron::FogEnable() const {
    return mAmbientFogOwner->mFogEnable;
}

void RndEnviron::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mAmbientFogOwner == from){
        RndEnviron* env = dynamic_cast<RndEnviron*>(to);
        if(env) mAmbientFogOwner = env->mAmbientFogOwner;
        else mAmbientFogOwner = this;
    }
}

void RndEnviron::ReclassifyLights() {

}

BEGIN_HANDLERS(RndEnviron)
    HANDLE_ACTION(remove_all_lights, OnRemoveAllLights())
    HANDLE_ACTION(toggle_ao, mAOEnabled = !mAOEnabled)
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
    SYNC_PROP(ambient_color, mAmbientFogOwner)

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
