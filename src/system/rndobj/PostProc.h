#pragma once
#include <revolution/OS.h>
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Tex.h"
#include "rndobj/ColorXfm.h"
#include "rndobj/DOFProc.h"
#include "rndobj/Draw.h"
#include "math/Vec.h"

class ProcCounter {
public:
    ProcCounter();
    void SetProcAndLock(bool);
    void SetEvenOddDisabled(bool);
    int ProcCommands();

    bool mProcAndLock;
    int mCount;
    int mSwitch;
    int mOdd;
    int mFPS;
    bool mEvenOddDisabled;
    bool mTriFrameRendering;
};

class PostProcessor {
public:
    PostProcessor() {}
    virtual ~PostProcessor() {}
    virtual void BeginWorld() {}
    virtual void EndWorld() {}
    virtual void DoPost() {}
    virtual void OnGPHangRecover() {
        OSReport("Base PostProcessor::OnGPHangRecover called.\n");
    }
    virtual float Priority() { return 1.0f; }
};

class RndPostProc : public Hmx::Object, public PostProcessor {
public:
    RndPostProc();
    virtual ~RndPostProc();
    OBJ_CLASSNAME(PostProc);
    OBJ_SET_TYPE(PostProc);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    virtual void Select();
    virtual void Unselect();
    virtual void EndWorld() {}
    virtual void DoPost();
    virtual void OnGPHangRecover() {}
    virtual void SetPriority(float f) { mPriority = f; }
    virtual float Priority() { return mPriority; }
    virtual void QueueMotionBlurObject(RndDrawable *) {}
    virtual void SetBloomColor() {}
    virtual void OnSelect();
    virtual void OnUnselect();

    float BloomIntensity() const;
    bool DoGradientMap() const;
    bool DoRefraction() const;
    bool DoVignette() const;
    bool HallOfTime() const;
    void UpdateTimeDelta();
    void UpdateColorModulation();
    void UpdateBlendPrevious();
    void Interp(const RndPostProc *, const RndPostProc *, float);
    void LoadRev(BinStream &, int);
    DataNode OnAllowedNormalMap(const DataArray *);
    bool BlendPrevious() const;
    float EmulateFPS() const { return mEmulateFPS; }

    static void Reset();
    static RndPostProc *sCurrent;
    static RndPostProc *Current();
    static DOFOverrideParams sDOFOverride;
    static DOFOverrideParams &DOFOverrides() { return sDOFOverride; }

    NEW_OVERLOAD
    DELETE_OVERLOAD
    DECLARE_REVS
    NEW_OBJ(RndPostProc)
    static void Init() { REGISTER_OBJ_FACTORY(RndPostProc) }

    float mPriority; // 0x20
    Hmx::Color mBloomColor; // 0x24
    float mBloomThreshold; // 0x34
    float mBloomIntensity; // 0x38
    bool mBloomGlare; // 0x3C
    bool mBloomStreak; // 0x3D
    float mBloomStreakAttenuation; // 0x40
    float mBloomStreakAngle; // 0x44
    ObjPtr<RndTex> mLuminanceMap; // 0x48
    bool mForceCurrentInterp; // 0x54
    RndColorXfm mColorXfm; // 0x58
    float mPosterLevels; // 0xdc
    float mPosterMin; // 0xe0
    float mKaleidoscopeComplexity; // 0xe4
    float mKaleidoscopeSize; // 0xe8
    float mKaleidoscopeAngle; // 0xec
    float mKaleidoscopeRadius; // 0xf0
    bool mKaleidoscopeFlipUVs; // 0xf4
    Vector2 mFlickerModBounds; // 0xf8
    Vector2 mFlickerTimeBounds; // 0x100
    Vector2 mFlickerSeconds; // 0x108
    float mColorModulation; // 0x110
    Vector2 mNoiseBaseScale; // 0x114
    float mNoiseTopScale; // 0x11c
    float mNoiseIntensity; // 0x120
    bool mNoiseStationary; // 0x124
    bool mNoiseMidtone; // 0x125
    ObjPtr<RndTex> mNoiseMap; // 0x128
    float mTrailThreshold; // 0x134
    float mTrailDuration; // 0x138
    Vector3 mBlendVec; // 0x13c
    float mEmulateFPS; // 0x148
    float mLastRender; // 0x14c
    float mDeltaSecs; // 0x150
    int mHallOfTimeType; // 0x154
    float mHallOfTimeRate; // 0x158
    Hmx::Color mHallOfTimeColor; // 0x15c
    float mHallOfTimeMix; // 0x16c
    Hmx::Color mMotionBlurWeight; // 0x170
    float mMotionBlurBlend; // 0x180
    bool mMotionBlurVelocity; // 0x184
    ObjPtr<RndTex> mGradientMap; // 0x188
    float mGradientMapOpacity; // 0x194
    float mGradientMapIndex; // 0x198
    float mGradientMapStart; // 0x19c
    float mGradientMapEnd; // 0x1a0
    ObjPtr<RndTex> mRefractMap; // 0x1a4
    float mRefractDist; // 0x1b0
    Vector2 mRefractScale; // 0x1b4
    Vector2 mRefractPanning; // 0x1bc
    Vector2 mRefractVelocity; // 0x1c4
    float mRefractAngle; // 0x1cc
    float mChromaticAberrationOffset; // 0x1d0
    bool mChromaticSharpen; // 0x1d4
    Hmx::Color mVignetteColor; // 0x1d8
    float mVignetteIntensity; // 0x1e8
};
