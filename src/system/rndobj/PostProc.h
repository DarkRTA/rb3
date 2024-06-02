#ifndef RNDOBJ_POSTPROC_H
#define RNDOBJ_POSTPROC_H
#include <revolution/OS.h>
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Tex.h"
#include "rndobj/ColorXfm.h"
#include "rndobj/DOFProc.h"
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
    PostProcessor(){}
    virtual ~PostProcessor(){}
    virtual void BeginWorld(){}
    virtual void EndWorld(){}
    virtual void DoPost(){}
    virtual void OnGPHangRecover(){ OSReport("Base PostProcessor::OnGPHangRecover called.\n"); }
    virtual float Priority(){ return 1.0f; }
};

class RndDrawable; // forward dec

class RndPostProc : public Hmx::Object, public PostProcessor {
public:
    RndPostProc();
    virtual ~RndPostProc();
    OBJ_CLASSNAME(Object);
    OBJ_SET_TYPE(Object);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    virtual void Select();
    virtual void Unselect();
    virtual void EndWorld(){}
    virtual void DoPost();
    virtual void OnGPHangRecover(){}
    virtual void SetPriority(float f){ mPriority = f; }
    virtual float Priority(){ return mPriority; }
    virtual void QueueMotionBlurObject(RndDrawable*){}
    virtual void SetBloomColor(){}
    virtual void OnSelect();
    virtual void OnUnselect();
    
    void Interp(const RndPostProc*, const RndPostProc*, float);
    DataNode OnAllowedNormalMap(const DataArray*);

    static void Reset();
    static RndPostProc* sCurrent;
    static RndPostProc* Current(){ return sCurrent; }
    static DOFOverrideParams sDOFOverride;
    static DOFOverrideParams& DOFOverrides(){ return sDOFOverride; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndPostProc)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndPostProc)
    }

    float mPriority;
    Hmx::Color mBloomColor;
    float mBloomThreshold;
    float mBloomIntensity;
    bool mBloomGlare;
    bool mBloomStreak;
    float mBloomStreakAttenuation;
    float mBloomStreakAngle;
    ObjPtr<RndTex, ObjectDir> mLuminanceMap;
    bool mForceCurrentInterp;
    RndColorXfm mColorXfm;
    float mNumLevels;
    float mMinIntensity;
    float mKaleidoscopeComplexity;
    float mKaleidoscopeSize;
    float mKaleidoscopeAngle;
    float mKaleidoscopeRadius;
    bool mKaleidoscopeFlipUVs;
    Vector2 mFlickerIntensity;
    Vector2 mFlickerSecsRange;

    Vector2 unk108;
    float unk110;

    Vector2 mNoiseBaseScale;

    float unk11c;

    float mNoiseIntensity;
    bool mNoiseStationary;
    bool mNoiseMidtone;
    ObjPtr<RndTex, ObjectDir> mNoiseMap;
    float mThreshold;
    float mDuration;

    Vector3 unk13c;
    float mEmulateFPS;
    float unk14c;
    int unk150;

    int mHallOfTimeType;
    float mHallOfTimeRate;
    Hmx::Color mHallOfTimeColor;
    float mHallOfTimeMix;
    Hmx::Color mMotionBlurWeight;
    float mMotionBlurBlend;
    bool mMotionBlurVelocity;
    ObjPtr<RndTex, ObjectDir> mGradientMap;
    float mGradientMapOpacity;
    float mGradientMapIndex;
    float mGradientMapStart;
    float mGradientMapEnd;
    ObjPtr<RndTex, ObjectDir> mRefractMap;
    float mRefractDist;
    Vector2 mRefractScale;
    Vector2 mRefractPanning;
    Vector2 mRefractVelocity;
    float mRefractAngle;
    float mChromaticAberrationOffset;
    bool mChromaticSharpen;
    Hmx::Color mVignetteColor;
    float mVignetteIntensity;
};

#endif
