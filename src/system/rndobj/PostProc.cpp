#include "rndobj/PostProc.h"
#include "utl/Symbols.h"

DOFOverrideParams RndPostProc::sDOFOverride;

RndPostProc::RndPostProc() : mPriority(1.0f), mBloomColor(1.0f, 1.0f, 1.0f, 0.0f), mBloomThreshold(4.0f), mBloomIntensity(0.0f), 
    mBloomGlare(0), mBloomStreak(0), mBloomStreakAttenuation(0.9f), mBloomStreakAngle(0.0f), mLuminanceMap(this, 0), 
    mForceCurrentInterp(0), mColorXfm(), mNumLevels(0.0f), mMinIntensity(1.0f), mKaleidoscopeComplexity(0.0f), 
    mKaleidoscopeSize(0.5f), mKaleidoscopeAngle(0.0f), mKaleidoscopeRadius(0.0f), mKaleidoscopeFlipUVs(1),
    mFlickerIntensity(0.0f, 0.0f), mFlickerSecsRange(0.001f, 0.007f), unk108(0.0f, 0.0f), unk110(1.0f),
    mNoiseBaseScale(32.0f, 24.0f), unk11c(1.35914f), mNoiseIntensity(0.0f), mNoiseStationary(0), mNoiseMidtone(1), mNoiseMap(this, 0), 
    mThreshold(1.0f), mDuration(0.0f), unk13c(1.0f, 1.0f, 0.0f), mEmulateFPS(30.0f), unk14c(0.0f), mHallOfTimeType(0), 
    mHallOfTimeRate(0.0f), mHallOfTimeColor(1.0f, 1.0f, 1.0f, 0.0f), mHallOfTimeMix(0.0f), mMotionBlurWeight(1.0f, 1.0f, 1.0f, 0.0f),
    mMotionBlurBlend(0.0f), mMotionBlurVelocity(1), mGradientMap(this, 0), 
    mGradientMapOpacity(0.0f), mGradientMapIndex(0.0f), mGradientMapStart(0.0f), mGradientMapEnd(1.0f), mRefractMap(this, 0),
    mRefractDist(0.05f), mRefractScale(1.0f, 1.0f), mRefractPanning(0.0f, 0.0f), mRefractVelocity(0.0f, 0.0f), mRefractAngle(0.0f),
    mChromaticAberrationOffset(0.0f), mChromaticSharpen(0), mVignetteColor(0.0f, 0.0f, 0.0f, 0.0f), mVignetteIntensity(0.0f) {
    mColorXfm.Reset();
}

RndPostProc::~RndPostProc(){
    Unselect();
}

BEGIN_HANDLERS(RndPostProc)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_ACTION(select, Select())
    HANDLE_ACTION(unselect, Unselect())
    HANDLE_ACTION(multi_select, OnSelect()) // fix what gets called
    HANDLE_ACTION(multi_unselect, OnUnselect()) // fix what gets called
    HANDLE_ACTION(interp, Interp(_msg->Obj<RndPostProc>(2), _msg->Obj<RndPostProc>(3), _msg->Float(4)))
    HANDLE(allowed_normal_map, OnAllowedNormalMap)
    HANDLE_CHECK(0x3BB)
END_HANDLERS

ProcCounter::ProcCounter() : mProcAndLock(0), mCount(0), mSwitch(0), mOdd(0), mFPS(0), mEvenOddDisabled(0), mTriFrameRendering(0) {
    
}

void ProcCounter::SetProcAndLock(bool pandl){
    mProcAndLock = pandl;
    mCount = -1;
}

void ProcCounter::SetEvenOddDisabled(bool eod){
    if(mEvenOddDisabled == eod) return;
    else mEvenOddDisabled = eod;
    if(mEvenOddDisabled) mCount = -1;
}
