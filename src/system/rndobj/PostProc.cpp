#include "rndobj/PostProc.h"
#include "decomp.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Rnd.h"
#include "rndobj/HiResScreen.h"
#include "math/Utl.h"
#include "math/Rand.h"
#include "obj/Task.h"
#include "rndobj/Utl.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

RndPostProc *RndPostProc::sCurrent = 0;
DOFOverrideParams RndPostProc::sDOFOverride;

INIT_REVS(RndPostProc)

RndPostProc::RndPostProc()
    : mPriority(1.0f), mBloomColor(1.0f, 1.0f, 1.0f, 0.0f), mBloomThreshold(4.0f),
      mBloomIntensity(0.0f), mBloomGlare(0), mBloomStreak(0),
      mBloomStreakAttenuation(0.9f), mBloomStreakAngle(0.0f), mLuminanceMap(this, 0),
      mForceCurrentInterp(0), mColorXfm(), mPosterLevels(0.0f), mPosterMin(1.0f),
      mKaleidoscopeComplexity(0.0f), mKaleidoscopeSize(0.5f), mKaleidoscopeAngle(0.0f),
      mKaleidoscopeRadius(0.0f), mKaleidoscopeFlipUVs(1), mFlickerModBounds(0.0f, 0.0f),
      mFlickerTimeBounds(0.001f, 0.007f), mFlickerSeconds(0.0f, 0.0f),
      mColorModulation(1.0f), mNoiseBaseScale(32.0f, 24.0f), mNoiseTopScale(1.35914f),
      mNoiseIntensity(0.0f), mNoiseStationary(0), mNoiseMidtone(1), mNoiseMap(this, 0),
      mTrailThreshold(1.0f), mTrailDuration(0.0f), mBlendVec(1.0f, 1.0f, 0.0f),
      mEmulateFPS(30.0f), mLastRender(0.0f), mHallOfTimeType(0), mHallOfTimeRate(0.0f),
      mHallOfTimeColor(1.0f, 1.0f, 1.0f, 0.0f), mHallOfTimeMix(0.0f),
      mMotionBlurWeight(1.0f, 1.0f, 1.0f, 0.0f), mMotionBlurBlend(0.0f),
      mMotionBlurVelocity(1), mGradientMap(this, 0), mGradientMapOpacity(0.0f),
      mGradientMapIndex(0.0f), mGradientMapStart(0.0f), mGradientMapEnd(1.0f),
      mRefractMap(this, 0), mRefractDist(0.05f), mRefractScale(1.0f, 1.0f),
      mRefractPanning(0.0f, 0.0f), mRefractVelocity(0.0f, 0.0f), mRefractAngle(0.0f),
      mChromaticAberrationOffset(0.0f), mChromaticSharpen(0),
      mVignetteColor(0.0f, 0.0f, 0.0f, 0.0f), mVignetteIntensity(0.0f) {
    mColorXfm.Reset();
}

RndPostProc::~RndPostProc() {
    Unselect();
    if (TheRnd->GetPostProcOverride() == this)
        TheRnd->SetPostProcOverride(0);
}

void RndPostProc::Select() {
    if (sCurrent != this) {
        if (sCurrent)
            sCurrent->OnUnselect();
        sCurrent = this;
        OnSelect();
    }
}

void RndPostProc::Unselect() {
    if (sCurrent == this) {
        sCurrent->OnUnselect();
        sCurrent = 0;
    }
}

void RndPostProc::Reset() {
    if (sCurrent) {
        sCurrent->OnUnselect();
        sCurrent = 0;
    }
}

void RndPostProc::OnSelect() {
    TheRnd->RegisterPostProcessor(this);
    Handle(selected_msg, false);
}

void RndPostProc::OnUnselect() {
    TheRnd->UnregisterPostProcessor(this);
    Handle(unselected_msg, false);
}

RndPostProc *RndPostProc::Current() { return sCurrent; }

float RndPostProc::BloomIntensity() const {
    if (mBloomGlare != 0 && TheHiResScreen.mActive != 0) {
        return mBloomIntensity / 3.0f;
    }
    return mBloomIntensity;
}

bool RndPostProc::DoGradientMap() const {
    bool ret = false;

    if ((mGradientMapOpacity > 0.0f) && mGradientMap.mPtr != 0) {
        ret = 1;
    }
    return ret;
}

bool RndPostProc::DoRefraction() const {
    bool ret = false;

    if (mRefractMap.mPtr != 0 && (0.0f != mRefractDist)) {
        ret = 1;
    }
    return ret;
}

bool RndPostProc::DoVignette() const { return mVignetteIntensity != 0.0f; }

bool RndPostProc::HallOfTime() const { return mHallOfTimeRate != 0.0f; }

// fn_80624B04
void RndPostProc::UpdateTimeDelta() {
    float secs = TheTaskMgr.Seconds(TaskMgr::kRealTime);
    float val150 = secs - mLastRender;
    mDeltaSecs = val150;
    mDeltaSecs = Clamp(0.0f, 1.0f, val150);
    mLastRender = secs;
}

void RndPostProc::DoPost() {
    UpdateTimeDelta();
    UpdateColorModulation();
    UpdateBlendPrevious();
}

// fn_80624BB4
void RndPostProc::UpdateColorModulation() {
    if (mFlickerTimeBounds.x > 0 && mFlickerTimeBounds.y > 0 && mFlickerModBounds.y > 0) {
        if (mFlickerSeconds.x >= mFlickerSeconds.y) {
            float unk108diff = mFlickerSeconds.x - mFlickerSeconds.y;
            mFlickerSeconds.x = unk108diff;
            float maxed = Max(unk108diff, 0.0f);
            mFlickerSeconds.x = maxed;
            mColorModulation =
                1.0f - RandomFloat(mFlickerModBounds.x, mFlickerModBounds.y);
            mFlickerSeconds.y = RandomFloat(mFlickerTimeBounds.x, mFlickerTimeBounds.y);
            float maxed2 = Max(mFlickerSeconds.x, mFlickerSeconds.y);
            mFlickerSeconds.y = maxed2;
        }
        mFlickerSeconds.x += mDeltaSecs;
    } else
        mColorModulation = 1.0f;
}

void RndPostProc::UpdateBlendPrevious() {
    bool shouldBlend =
        mTrailThreshold < 1.0f && mTrailDuration > 0.0f && !TheHiResScreen.IsActive();
    if (shouldBlend) {
        MILO_ASSERT(mTrailDuration > 0.f, 0xf6);
        mBlendVec.x = mTrailThreshold;
        mBlendVec.y = mDeltaSecs / mTrailDuration;
        mBlendVec.z = 0.3333333333f;
    }
    return;
}

bool RndPostProc::BlendPrevious() const {
    return mTrailThreshold < 1.0f && mTrailDuration > 0.0f && !TheHiResScreen.IsActive();
}

DataNode RndPostProc::OnAllowedNormalMap(const DataArray *) {
    return GetNormalMapTextures(Dir());
}

SAVE_OBJ(RndPostProc, 524)

BEGIN_COPYS(RndPostProc)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(RndPostProc)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mPriority)
        COPY_MEMBER(mBloomIntensity)
        COPY_MEMBER(mBloomColor)
        COPY_MEMBER(mBloomThreshold)
        COPY_MEMBER(mBloomGlare)
        COPY_MEMBER(mBloomStreak)
        COPY_MEMBER(mBloomStreakAttenuation)
        COPY_MEMBER(mBloomStreakAngle)
        COPY_MEMBER(mLuminanceMap)
        COPY_MEMBER(mColorXfm)
        COPY_MEMBER(mFlickerModBounds)
        COPY_MEMBER(mFlickerTimeBounds)
        COPY_MEMBER(mNoiseBaseScale)
        COPY_MEMBER(mNoiseTopScale)
        COPY_MEMBER(mNoiseIntensity)
        COPY_MEMBER(mNoiseStationary)
        COPY_MEMBER(mNoiseMap)
        COPY_MEMBER(mNoiseMidtone)
        COPY_MEMBER(mTrailDuration)
        COPY_MEMBER(mTrailThreshold)
        COPY_MEMBER(mEmulateFPS)
        COPY_MEMBER(mPosterLevels)
        COPY_MEMBER(mPosterMin)
        COPY_MEMBER(mKaleidoscopeComplexity)
        COPY_MEMBER(mKaleidoscopeSize)
        COPY_MEMBER(mKaleidoscopeAngle)
        COPY_MEMBER(mKaleidoscopeRadius)
        COPY_MEMBER(mKaleidoscopeFlipUVs)
        COPY_MEMBER(mHallOfTimeRate)
        COPY_MEMBER(mHallOfTimeColor)
        COPY_MEMBER(mHallOfTimeMix)
        COPY_MEMBER(mHallOfTimeType)
        COPY_MEMBER(mMotionBlurBlend)
        COPY_MEMBER(mMotionBlurWeight)
        COPY_MEMBER(mMotionBlurVelocity)
        COPY_MEMBER(mGradientMap)
        COPY_MEMBER(mGradientMapIndex)
        COPY_MEMBER(mGradientMapOpacity)
        COPY_MEMBER(mGradientMapStart)
        COPY_MEMBER(mGradientMapEnd)
        COPY_MEMBER(mRefractMap)
        COPY_MEMBER(mRefractDist)
        COPY_MEMBER(mRefractScale)
        COPY_MEMBER(mRefractPanning)
        COPY_MEMBER(mRefractVelocity)
        COPY_MEMBER(mRefractAngle)
        COPY_MEMBER(mChromaticAberrationOffset)
        COPY_MEMBER(mChromaticSharpen)
        COPY_MEMBER(mVignetteColor)
        COPY_MEMBER(mVignetteIntensity)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_LOADS(RndPostProc)
    LOAD_REVS(bs)
    ASSERT_REVS(37, 0)
    if (gRev == 16) {
        int dRev;
        bs >> dRev;
        MILO_ASSERT(dRev == 3, 667);
        bool x;
        Sphere s;
        int i;
        bs >> x >> s >> i;
    } else
        LOAD_SUPERCLASS(Hmx::Object)
    LoadRev(bs, gRev);
END_LOADS

DECOMP_FORCEACTIVE(PostProc, "%s can't load new %s version")

void RndPostProc::LoadRev(BinStream &bs, int rev) {
    if (rev > 4) {
        if (rev > 10) {
            bs >> mBloomColor;
            if (rev < 24) {
                int x;
                bs >> x;
            }
            bs >> mBloomIntensity;
            bs >> mBloomThreshold;
        } else {
            Hmx::Color c;
            bs >> c;
        }
    }
    if (rev > 5)
        bs >> mLuminanceMap;

    if (rev > 7) {
        bs >> mTrailThreshold;
        bs >> mTrailDuration;
        bs >> mEmulateFPS;
    }

    if (rev > 9) {
        if (rev > 0x12) {
            // color correction stuff?
        }
        bs >> mPosterLevels;
    }

    if (rev >> 13)
        bs >> mPosterMin;

    if (rev > 32)
        bs >> mBloomGlare;
    if (rev > 35) {
        bs >> mBloomStreak;
        bs >> mBloomStreakAttenuation;
        bs >> mBloomStreakAngle;
    }
}

BEGIN_HANDLERS(RndPostProc)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_ACTION(select, Select())
    HANDLE_ACTION(unselect, Unselect())
    HANDLE_ACTION(multi_select, OnSelect())
    HANDLE_ACTION(multi_unselect, OnUnselect())
    HANDLE_ACTION(
        interp,
        Interp(_msg->Obj<RndPostProc>(2), _msg->Obj<RndPostProc>(3), _msg->Float(4))
    )
    HANDLE(allowed_normal_map, OnAllowedNormalMap)
    HANDLE_CHECK(0x3BB)
END_HANDLERS

#pragma push
#pragma dont_inline on
BEGIN_PROPSYNCS(RndPostProc)
    SYNC_PROP(priority, mPriority)
    SYNC_PROP(bloom_color, mBloomColor)
    SYNC_PROP(bloom_threshold, mBloomThreshold)
    SYNC_PROP(bloom_intensity, mBloomIntensity)
    SYNC_PROP(bloom_glare, mBloomGlare)
    SYNC_PROP(bloom_streak, mBloomStreak)
    SYNC_PROP(bloom_streak_attenuation, mBloomStreakAttenuation)
    SYNC_PROP(bloom_streak_angle, mBloomStreakAngle)
    SYNC_PROP(luminance_map, mLuminanceMap)
    SYNC_PROP_MODIFY_ALT(hue, mColorXfm.mHue, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(saturation, mColorXfm.mSaturation, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(lightness, mColorXfm.mLightness, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(brightness, mColorXfm.mBrightness, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(contrast, mColorXfm.mContrast, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(in_lo, mColorXfm.mLevelInLo, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(in_hi, mColorXfm.mLevelInHi, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(out_lo, mColorXfm.mLevelOutLo, mColorXfm.AdjustColorXfm())
    SYNC_PROP_MODIFY_ALT(out_hi, mColorXfm.mLevelOutHi, mColorXfm.AdjustColorXfm())
    SYNC_PROP(num_levels, mPosterLevels)
    SYNC_PROP(min_intensity, mPosterMin)
    SYNC_PROP(kaleidoscope_complexity, mKaleidoscopeComplexity)
    SYNC_PROP(kaleidoscope_size, mKaleidoscopeSize)
    SYNC_PROP(kaleidoscope_angle, mKaleidoscopeAngle)
    SYNC_PROP(kaleidoscope_radius, mKaleidoscopeRadius)
    SYNC_PROP(kaleidoscope_flipUVs, mKaleidoscopeFlipUVs)
    SYNC_PROP(flicker_intensity, mFlickerModBounds)
    SYNC_PROP(flicker_secs_range, mFlickerTimeBounds)
    SYNC_PROP(noise_base_scale, mNoiseBaseScale)
    SYNC_PROP(noise_intensity, mNoiseIntensity)
    SYNC_PROP(noise_stationary, mNoiseStationary)
    SYNC_PROP(noise_midtone, mNoiseMidtone)
    SYNC_PROP(noise_map, mNoiseMap)
    SYNC_PROP(threshold, mTrailThreshold)
    SYNC_PROP(duration, mTrailDuration)
    SYNC_PROP(emulate_fps, mEmulateFPS)
    SYNC_PROP(hall_of_time_type, mHallOfTimeType)
    SYNC_PROP(hall_of_time_rate, mHallOfTimeRate)
    SYNC_PROP(hall_of_time_color, mHallOfTimeColor)
    SYNC_PROP(hall_of_time_mix, mHallOfTimeMix)
    SYNC_PROP(motion_blur_blend, mMotionBlurBlend)
    SYNC_PROP(motion_blur_weight, mMotionBlurWeight)
    SYNC_PROP(motion_blur_exposure, mMotionBlurWeight.alpha)
    SYNC_PROP(motion_blur_velocity, mMotionBlurVelocity)
    SYNC_PROP(gradient_map, mGradientMap)
    SYNC_PROP(gradient_map_opacity, mGradientMapOpacity)
    SYNC_PROP(gradient_map_index, mGradientMapIndex)
    SYNC_PROP(gradient_map_start, mGradientMapStart)
    SYNC_PROP(gradient_map_end, mGradientMapEnd)
    SYNC_PROP(refract_map, mRefractMap)
    SYNC_PROP(refract_dist, mRefractDist)
    SYNC_PROP(refract_scale, mRefractScale)
    SYNC_PROP(refract_panning, mRefractPanning)
    SYNC_PROP(refract_velocity, mRefractVelocity)
    SYNC_PROP(refract_angle, mRefractAngle)
    SYNC_PROP(chromatic_aberration_offset, mChromaticAberrationOffset)
    SYNC_PROP(chromatic_sharpen, mChromaticSharpen)
    SYNC_PROP(vignette_color, mVignetteColor)
    SYNC_PROP(vignette_intensity, mVignetteIntensity)
    SYNC_PROP(force_current_interp, mForceCurrentInterp)
END_PROPSYNCS
#pragma pop

ProcCounter::ProcCounter()
    : mProcAndLock(0), mCount(0), mSwitch(0), mOdd(0), mFPS(0), mEvenOddDisabled(0),
      mTriFrameRendering(0) {}

void ProcCounter::SetProcAndLock(bool pandl) {
    mProcAndLock = pandl;
    mCount = -1;
}

void ProcCounter::SetEvenOddDisabled(bool eod) {
    if (mEvenOddDisabled == eod)
        return;
    else
        mEvenOddDisabled = eod;
    if (mEvenOddDisabled)
        mCount = -1;
}

ProcessCmd ProcCounter::ProcCommands() {
    int count;
    int retCmd;

    if ((this->mProcAndLock != false) && (this->mCount == 0)) {
        return kProcessNone;
    }
    if (this->mEvenOddDisabled == false) {
        count = this->mCount;
        retCmd = 0;
        if (count == -1) {
            this->mCount = -1;
            retCmd = 7;
        } else if (count == 0) {
            retCmd = 1;
        } else if (count == 1) {
            retCmd = 6;
            if (this->mTriFrameRendering != false) {
                retCmd = 4;
            }
        } else if (count == 2) {
            retCmd = 2;
        }
        count = this->mCount + 1;
        this->mCount = count;
        int compare_value = (mTriFrameRendering != 0) ? 2 : 1;

        if (count > compare_value) {
            this->mCount = 0;
        }
        return (ProcessCmd)retCmd;
    }
    return kProcessAll;
}

DOFOverrideParams::DOFOverrideParams()
    : mDepthScale(1.0f), mDepthOffset(0.0f), mMinBlurScale(1.0f), mMinBlurOffset(0.0f),
      mMaxBlurScale(1.0f), mMaxBlurOffset(0.0f), mBlurWidthScale(1.0f) {}
