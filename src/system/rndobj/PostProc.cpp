#include "rndobj/PostProc.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Rnd.h"
#include "rndobj/HiResScreen.h"
#include "math/MathFuncs.h"
#include "math/Rand.h"
#include "obj/Task.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

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
      mFlickerTimeBounds(0.001f, 0.007f), mFlickerSeconds(0.0f, 0.0f), mColorModulation(1.0f),
      mNoiseBaseScale(32.0f, 24.0f), mNoiseTopScale(1.35914f), mNoiseIntensity(0.0f),
      mNoiseStationary(0), mNoiseMidtone(1), mNoiseMap(this, 0), mTrailThreshold(1.0f),
      mTrailDuration(0.0f), mBlendVec(1.0f, 1.0f, 0.0f), mEmulateFPS(30.0f), mLastRender(0.0f),
      mHallOfTimeType(0), mHallOfTimeRate(0.0f), mHallOfTimeColor(1.0f, 1.0f, 1.0f, 0.0f),
      mHallOfTimeMix(0.0f), mMotionBlurWeight(1.0f, 1.0f, 1.0f, 0.0f),
      mMotionBlurBlend(0.0f), mMotionBlurVelocity(1), mGradientMap(this, 0),
      mGradientMapOpacity(0.0f), mGradientMapIndex(0.0f), mGradientMapStart(0.0f),
      mGradientMapEnd(1.0f), mRefractMap(this, 0), mRefractDist(0.05f),
      mRefractScale(1.0f, 1.0f), mRefractPanning(0.0f, 0.0f),
      mRefractVelocity(0.0f, 0.0f), mRefractAngle(0.0f), mChromaticAberrationOffset(0.0f),
      mChromaticSharpen(0), mVignetteColor(0.0f, 0.0f, 0.0f, 0.0f),
      mVignetteIntensity(0.0f) {
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

RndPostProc *RndPostProc::Current() {
    return sCurrent;
}

float RndPostProc::BloomIntensity() const {
    if (mBloomGlare != 0 && TheHiResScreen->mActive != 0) {
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

bool RndPostProc::DoVignette() const {
    return mVignetteIntensity != 0.0f;
}

bool RndPostProc::HallOfTime() const {
    return mHallOfTimeRate != 0.0f;
}

// fn_80624B04
void RndPostProc::UpdateTimeDelta() {
    float secs = TheTaskMgr.Seconds(TaskMgr::b);
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
            mColorModulation = 1.0f - RandomFloat(mFlickerModBounds.x, mFlickerModBounds.y);
            mFlickerSeconds.y = RandomFloat(mFlickerTimeBounds.x, mFlickerTimeBounds.y);
            float maxed2 = Max(mFlickerSeconds.x, mFlickerSeconds.y);
            mFlickerSeconds.y = maxed2;
        }
        mFlickerSeconds.x += mDeltaSecs;
    } else
        mColorModulation = 1.0f;
}

void RndPostProc::UpdateBlendPrevious() {
    bool shouldBlend = mTrailThreshold < 1.0f && mTrailDuration > 0.0f && !TheHiResScreen->IsActive();
    if(shouldBlend) {
        if(mTrailDuration <= 0.0f) {
            MILO_ASSERT(mTrailDuration > 0.0f, 0xf6);
        }
        mBlendVec.x = mTrailThreshold;
        mBlendVec.y = mDeltaSecs / mTrailDuration;
        mBlendVec.z = 0.3333333333f;
    }
    return;
}

bool RndPostProc::BlendPrevious() const {
    return mTrailThreshold < 1.0f && mTrailDuration > 0.0f && !TheHiResScreen->IsActive();
}

SAVE_OBJ(RndPostProc, 524)

BEGIN_LOADS(RndPostProc)
LOAD_REVS(bs)
ASSERT_REVS(37, 0)
if (gRev == 16) {
    int dRev;
    bs >> dRev;
    MILO_ASSERT(dRev == 3, 667);
    bool x;
    bs >> x;
    int a, b, c, d, e;
    bs >> a >> b >> c >> d >> e;
} else
    Hmx::Object::Load(bs);
LoadRev(bs, gRev);
END_LOADS

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

    if (rev > 9 ) {
        if (rev > 0x12) {
            // color correction stuff?
        }
        bs >> mPosterLevels;
    }

    if(rev >> 13)
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
    HANDLE_ACTION(interp, Interp(_msg->Obj<RndPostProc>(2), _msg->Obj<RndPostProc>(3), _msg->Float(4)))
    HANDLE(allowed_normal_map, OnAllowedNormalMap)
    HANDLE_CHECK(0x3BB)
END_HANDLERS

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

int ProcCounter::ProcCommands() {
  int count;
  int retCmd;

  if ((this->mProcAndLock != false) && (this->mCount == 0)) {
    return 0;
  }
  if (this->mEvenOddDisabled == false) {
    count = this->mCount;
    retCmd = 0;
    if (count == -1) {
      this->mCount = -1;
      retCmd = 7;
    }
    else if (count == 0) {
      retCmd = 1;
    }
    else if (count == 1) {
      retCmd = 6;
      if (this->mTriFrameRendering != false) {
        retCmd = 4;
      }
    }
    else if (count == 2) {
      retCmd = 2;
    }
    count = this->mCount + 1;
    this->mCount = count;
    int compare_value = (mTriFrameRendering != 0) ? 2 : 1;

    if (count > compare_value) {
      this->mCount = 0;
    }
    return retCmd;
  }
  return 7;

}

DOFOverrideParams::DOFOverrideParams()
    : mDepthScale(1.0f), mDepthOffset(0.0f), mMinBlurScale(1.0f), mMinBlurOffset(0.0f),
      mMaxBlurScale(1.0f), mMaxBlurOffset(0.0f), mBlurWidthScale(1.0f) {}
