#include "Env.h"
#include "obj/Object.h"
#include "revolution/gx/GXTypes.h"
#include "rndobj/BoxMap.h"
#include "rndobj/Draw.h"
#include "utl/Std.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

RndEnviron *RndEnviron::sCurrent;
bool RndEnviron::sCurrentPosSet;
Vector3 RndEnviron::sCurrentPos = Vector3(0, 0, 0);
BoxMapLighting RndEnviron::sGlobalLighting;
int ENVIRON_REV = 15;

void RndEnviron::Select(const Vector3 *v) {
    sCurrent = this;
    sCurrentPosSet = (int)v;
    if (v) {
        sCurrentPos = *v;
    } else {
#ifdef MILO_DEBUG
        sCurrentPos.z = 0;
        sCurrentPos.y = 0;
        sCurrentPos.x = 0;
#else
        sCurrentPos.Zero();
#endif
    }
    mNumLightsReal = 0;
    mNumLightsApprox = 0;
    mNumLightsPoint = 0;
    mNumLightsProj = 0;
    mHasPointCubeTex = false;
    unk5c = 0;
    ReclassifyLights();
}

RndEnviron::RndEnviron()
    : mLightsReal(this), mLightsApprox(this), mLightsOld(this), mAmbientColor(0, 0, 0, 1),
      unk5c(0), mNumLightsReal(0), mNumLightsApprox(0), mNumLightsPoint(0),
      mNumLightsProj(0), mHasPointCubeTex(false), mAmbientFogOwner(this, this),
      mFogEnable(0), mFogStart(0), mFogEnd(1), mFogColor(1, 1, 1), mFadeOut(0),
      mFadeStart(0), mFadeEnd(1000), mFadeMax(1), mFadeRef(this), mLRFade(0, 0, 0, 0),
      mColorXfm(), mUseColorAdjust(0), mAnimateFromPreset(1), mAOEnabled(1),
      mAOStrength(1), mUpdateTimer(), mIntensityAverage(0), mIntensityRate(0.1f),
      mExposure(1), mWhitePoint(1), mUseToneMapping(0), mUseApprox_Local(1),
      mUseApprox_Global(1) {
    mUpdateTimer.Restart();
}

RndEnviron::~RndEnviron() {
    if (sCurrent == this) {
        sCurrent = nullptr;
        sCurrentPosSet = nullptr;
        sCurrentPos.Zero();
    }
}

SAVE_OBJ(RndEnviron, 119)

BEGIN_LOADS(RndEnviron)
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, ENVIRON_REV)
    if (rev > 1)
        LOAD_SUPERCLASS(Hmx::Object)
    if (rev < 3)
        RndDrawable::DumpLoad(bs);
    if (rev < 0xF)
        bs >> mLightsOld;
    else {
        bs >> mLightsReal;
        bs >> mLightsApprox;
    }
    bs >> mAmbientColor >> mFogStart >> mFogEnd;
    if (rev < 1) {
        int dummy;
        bs >> dummy;
    }
    bs >> mFogColor;
    if (rev < 1) {
        int enabled;
        bs >> enabled;
        mFogEnable = enabled;
    } else
        bs >> mFogEnable;
    if (rev > 3)
        bs >> mAnimateFromPreset;
    if (rev > 4) {
        bs >> mFadeOut >> mFadeStart >> mFadeEnd;
        if (rev > 5)
            bs >> mFadeMax;
    }
    if (rev > 8) {
        bs >> mFadeRef >> mLRFade;
    }
    if (rev > 6) {
        bs >> mAmbientFogOwner;
        if (!mAmbientFogOwner) {
            mAmbientFogOwner = this;
        }
    }
    if (rev > 7) {
        bs >> mUseColorAdjust;
        bs >> mColorXfm;
    }
    if (rev > 9) {
        if (rev < 0xD) {
            int dummy;
            bs >> dummy;
        }
        bs >> mAOStrength;
    }
    if (rev > 10) {
        bs >> mIntensityRate >> mExposure >> mWhitePoint >> mUseToneMapping;
    }
    if (rev == 0xB) {
        int dummy;
        bs >> dummy;
    } else if (rev - 0xC <= 1U) {
        int dummy;
        bs >> dummy;
    }
END_LOADS

DECOMP_FORCEACTIVE(Env, "e")

BEGIN_COPYS(RndEnviron)
    COPY_SUPERCLASS(Hmx::Object)
    if (ty != kCopyFromMax) {
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
            if (ty == kCopyShallow || ty == kCopyFromMax && c->mAmbientFogOwner != c) {
                COPY_MEMBER(mAmbientFogOwner)
            } else {
                mAmbientFogOwner = this;
                mAmbientColor = c->mAmbientFogOwner->mAmbientColor;
                mFogColor = c->mAmbientFogOwner->mFogColor;
                mFogStart = c->mAmbientFogOwner->mFogStart;
                mFogEnd = c->mAmbientFogOwner->mFogEnd;
                mFogEnable = c->mAmbientFogOwner->mFogEnable;
            }
        END_COPYING_MEMBERS
    }
END_COPYS

bool RndEnviron::IsValidRealLight(const RndLight *l) const {
    bool ret = false;
    RndLight::Type ty = l->GetType();
    if (ty == RndLight::kPoint || ty == RndLight::kFakeSpot)
        ret = true;
    return ret;
}

// fn_805D7EB8 - actually calls ObjPtrList::find
bool RndEnviron::IsLightInList(const RndLight *light, const ObjPtrList<RndLight> &pList)
    const {
    if (light == nullptr)
        return 0;
    return pList.find(light) != pList.end();
}

bool RndEnviron::IsFake(RndLight *l) const { return IsLightInList(l, mLightsApprox); }

bool RndEnviron::IsReal(RndLight *l) const { return IsLightInList(l, mLightsReal); }

bool RndEnviron::FogEnable() const { return mAmbientFogOwner->mFogEnable; }

void RndEnviron::Replace(Hmx::Object *from, Hmx::Object *to) {
    Hmx::Object::Replace(from, to);
    if (mAmbientFogOwner == from) {
        RndEnviron *env = dynamic_cast<RndEnviron *>(to);
        if (env)
            mAmbientFogOwner = env->mAmbientFogOwner;
        else
            mAmbientFogOwner = this;
    }
}

void RndEnviron::AddLight(RndLight *l) {
    if (IsLightInList(l, mLightsReal) || IsLightInList(l, mLightsApprox)) {
        MILO_WARN("%s already in %s", l->Name(), Name());
    } else {
        if (IsValidRealLight(l))
            mLightsReal.push_back(l);
        else
            mLightsApprox.push_back(l);
    }
}

// fn_805D8118
void RndEnviron::RemoveLight(RndLight *l) {
    mLightsReal.remove(l);
    mLightsApprox.remove(l);
}

// fn_805D81CC
#pragma push
#pragma auto_inline on
const Transform &RndEnviron::ColorXfm() const {
    static Vector3 x(1, 0, 0);
    static Vector3 y(0, 1, 0);
    static Vector3 z(0, 0, 1);
    static Transform ident(Hmx::Matrix3(x, y, z), Vector3(0, 0, 0));
    if (mUseColorAdjust)
        return mColorXfm.mColorXfm;
    else
        return ident;
}
#pragma pop

void RndEnviron::ReclassifyLights() {
    if (!mLightsOld.empty()) {
        FOREACH (it, mLightsOld) {
            AddLight(*it);
        }
        mLightsOld.clear();
    }
}

BEGIN_HANDLERS(RndEnviron)
    HANDLE_ACTION(remove_all_lights, OnRemoveAllLights())
    HANDLE_ACTION(toggle_ao, mAOEnabled = !mAOEnabled)
    HANDLE_ACTION(remove_light, RemoveLight(_msg->Obj<RndLight>(2)))
    HANDLE(allowable_lights_real, OnAllowableLights_Real)
    HANDLE(allowable_lights_approx, OnAllowableLights_Approx)
    HANDLE_ACTION(select, Select(nullptr))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(582)
END_HANDLERS

void RndEnviron::OnRemoveAllLights() {
    mLightsReal.clear();
    mLightsApprox.clear();
    mLightsOld.clear();
}

// fn_805D86B8
DataNode RndEnviron::OnAllowableLights_Real(const DataArray *da) {
    DataArrayPtr ptr;
    for (ObjDirItr<RndLight> it(Dir(), true); it != nullptr; ++it) {
        if (!IsLightInList(it, mLightsReal) && !IsLightInList(it, mLightsApprox)
            && IsValidRealLight(it) == 1U) {
            ptr->Insert(ptr->Size(), &*it);
        }
    }
    static DataNode &milo_prop_path = DataVariable("milo_prop_path");
    if (milo_prop_path.Type() == kDataArray) {
        if (milo_prop_path.Array()->Size() == 2) {
            ptr->Insert(
                ptr->Size(), *NextItr(mLightsReal.begin(), milo_prop_path.Array()->Int(1))
            );
        }
    }
    return ptr;
}

DataNode RndEnviron::OnAllowableLights_Approx(const DataArray *da) {
    DataArrayPtr ptr;
    for (ObjDirItr<RndLight> it(Dir(), true); it != 0; ++it) {
        if (!IsLightInList(it, mLightsReal) && !IsLightInList(it, mLightsApprox)) {
            ptr->Insert(ptr->Size(), &*it);
        }
    }
    static DataNode &milo_prop_path = DataVariable("milo_prop_path");
    if (milo_prop_path.Type() == kDataArray) {
        if (milo_prop_path.Array()->Size() == 2) {
            ptr->Insert(
                ptr->Size(),
                *NextItr(mLightsApprox.begin(), milo_prop_path.Array()->Int(1))
            );
        }
    }
    return ptr;
}

#pragma push
#pragma auto_inline on
void RndEnviron::UpdateApproxLighting(const Vector3 *v3, _GXColor *gxColor) {
    mNumLightsApprox = 0;
    if (UsesApproxes()) {
        static BoxMapLighting boxLight;
        static Hmx::Color boxResults[6];
        for (int i = 0; i < 6; i++) {
            boxResults[i].Set(0, 0, 0);
        }
        if (UsesApproxLocal()) {
            boxLight.Clear();
            FOREACH (it, mLightsReal) {
                if (boxLight.QueueLight(*it, 1))
                    mNumLightsApprox++;
            }
            boxLight.ApplyQueuedLights(boxResults, v3);
        }
        if (UsesApproxGlobal()) {
            unsigned int num = sGlobalLighting.NumQueuedLights();
            if (num != 0) {
                mNumLightsApprox += num;
                sGlobalLighting.ApplyQueuedLights(boxResults, v3);
            }
        }
        if (gxColor) {
            for (int i = 0; i < 6; i++) {
            }
            ApplyApproxLighting(gxColor);
        } else {
            _GXColor color;
            for (int i = 0; i < 6; i++) {
            }
            ApplyApproxLighting(&color);
        }
    }
}
#pragma pop

void RndEnviron::ApplyApproxLighting(const _GXColor *) {}

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