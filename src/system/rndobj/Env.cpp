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
int ENVIRON_REV = 15;

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
    unk5c = 0;
    ReclassifyLights();
}

RndEnviron::RndEnviron() : mLightsReal(this, kObjListNoNull), mLightsApprox(this, kObjListNoNull), mLightsOld(this, kObjListNoNull), mAmbientColor(0.0f, 0.0f, 0.0f),
    unk5c(0), mNumLightsReal(0), mNumLightsApprox(0), mNumLightsPoint(0), mNumLightsProj(0), mHasPointCubeTex(false), mAmbientFogOwner(this, this), 
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
        sCurrentPos.Zero();
    }
}

SAVE_OBJ(RndEnviron, 119)

BEGIN_LOADS(RndEnviron)
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, ENVIRON_REV)
    if(rev > 1) LOAD_SUPERCLASS(Hmx::Object)
    if(rev < 3) RndDrawable::DumpLoad(bs);
    if(rev < 0xF) bs >> mLightsOld;
    else {
        bs >> mLightsReal;
        bs >> mLightsApprox;
    }
    bs >> mAmbientColor >> mFogStart >> mFogEnd;
    if(rev < 1){
        int dummy;
        bs >> dummy;
    }
    bs >> mFogColor;
    if(rev < 1){
        int enabled;
        bs >> enabled;
        mFogEnable = enabled;
    }
    else bs >> mFogEnable;
    if(rev > 3) bs >> mAnimateFromPreset;
    if(rev > 4){
        bs >> mFadeOut >> mFadeStart >> mFadeEnd;
        if(rev > 5) bs >> mFadeMax;
    }
    if(rev > 8){
        bs >> mFadeRef >> mLRFade;
    }
    if(rev > 6){
        bs >> mAmbientFogOwner;
        if(!mAmbientFogOwner){
            mAmbientFogOwner = this;
        }
    }
    if(rev > 7){
        bs >> mUseColorAdjust;
        mColorXfm.Load(bs);
    }
    if(rev > 9){
        if(rev < 0xD){
            int dummy;
            bs >> dummy;
        }
        bs >> mAOStrength;
    }
    if(rev > 10){
        bs >> mIntensityRate >> mExposure >> mWhitePoint >> mUseToneMapping;
    }
    if(rev == 0xB){
        int dummy;
        bs >> dummy;
    }
    else if(rev - 0xC <= 1U){
        int dummy;
        bs >> dummy;
    }
END_LOADS

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
    for(ObjPtrList<RndLight, ObjectDir>::iterator it = pList.begin(); it != pList.end(); ++it){
        RndLight* itLight = *it;
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
    SYNC_PROP(ambient_color, mAmbientFogOwner->mAmbientColor)
    SYNC_PROP(ambient_alpha, mAmbientFogOwner->mAmbientColor.alpha)
    SYNC_PROP(fog_enable, mAmbientFogOwner->mFogEnable)
    SYNC_PROP(fog_start, mAmbientFogOwner->mFogStart)
    SYNC_PROP(fog_end, mAmbientFogOwner->mFogEnd)
    SYNC_PROP(fog_color, mAmbientFogOwner->mFogColor)
    SYNC_PROP(ambient_fog_owner, mAmbientFogOwner)
    SYNC_PROP(fade_out, mFadeOut)
    SYNC_PROP(fade_start, mFadeStart)
    SYNC_PROP(fade_end, mFadeEnd)
    SYNC_PROP(fade_max, mFadeMax)
    SYNC_PROP(fade_ref, mFadeRef)
    SYNC_PROP(left_out, mLRFade.x)
    SYNC_PROP(left_opaque, mLRFade.y)
    SYNC_PROP(right_opaque, mLRFade.z)
    SYNC_PROP(right_out, mLRFade.w)
    SYNC_PROP(ao_strength, mAOStrength)
    SYNC_PROP(intensity_rate, mIntensityRate)
    SYNC_PROP(exposure, mExposure)
    SYNC_PROP(white_point, mWhitePoint)
    SYNC_PROP(tone_map, mUseToneMapping)
    SYNC_PROP(use_color_adjust, mUseColorAdjust)
    SYNC_PROP_MODIFY(hue, mColorXfm.mHue, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY(saturation, mColorXfm.mSaturation, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY(lightness, mColorXfm.mLightness, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY(brightness, mColorXfm.mBrightness, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY(contrast, mColorXfm.mContrast, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(in_lo, mColorXfm.mLevelInLo, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(in_hi, mColorXfm.mLevelInHi, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(out_lo, mColorXfm.mLevelOutLo, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(out_hi, mColorXfm.mLevelOutHi, mColorXfm.AdjustColorXfm())
    SYNC_PROP(animate_from_preset, mAnimateFromPreset)
END_PROPSYNCS

bool RndEnviron::HasPointCubeTex() const {
    return mHasPointCubeTex;
}
