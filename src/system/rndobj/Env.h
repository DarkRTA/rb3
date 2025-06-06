#pragma once
#include "rndobj/Trans.h"
#include "types.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "math/Color.h"
#include "math/Vec.h"
#include "rndobj/BoxMap.h"
#include "rndobj/Lit.h"
#include "rndobj/ColorXfm.h"

class _GXColor;

class RndEnviron : public Hmx::Object {
public:
    RndEnviron();
    virtual ~RndEnviron();
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    OBJ_CLASSNAME(Environ);
    OBJ_SET_TYPE(Environ);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void Select(const Vector3 *);
    virtual void ApplyApproxLighting(const _GXColor *);
    virtual bool HasPointCubeTex() const { return mHasPointCubeTex; }
    virtual bool IsFake(RndLight *) const;
    virtual bool IsReal(RndLight *) const;

    const Transform &ColorXfm() const;
    void AddLight(RndLight *);
    void RemoveLight(RndLight *);
    void ReclassifyLights();
    void OnRemoveAllLights();
    DataNode OnAllowableLights_Real(const DataArray *);
    DataNode OnAllowableLights_Approx(const DataArray *);
    bool FogEnable() const;
    bool IsLightInList(const RndLight *, const ObjPtrList<RndLight> &) const;
    bool IsValidRealLight(const RndLight *) const;
    void UpdateApproxLighting(const Vector3 *, _GXColor *);
    bool GetAnimateFromPreset() const { return mAnimateFromPreset; }

    const Hmx::Color &AmbientColor() const { return mAmbientFogOwner->mAmbientColor; }
    void SetAmbientColor(const Hmx::Color &col) {
        mAmbientFogOwner->mAmbientColor.Set(col.red, col.green, col.blue);
    }

    void SetAmbientAlpha(float alpha) { mAmbientFogOwner->mAmbientColor.alpha = alpha; }

    const Hmx::Color &FogColor() const { return mAmbientFogOwner->mFogColor; }
    void SetFogColor(const Hmx::Color &col) { mAmbientFogOwner->mFogColor = col; }

    float GetFogStart() const { return mAmbientFogOwner->mFogStart; }
    float GetFogEnd() const { return mAmbientFogOwner->mFogEnd; }
    void SetFogRange(float start, float end) {
        mAmbientFogOwner->mFogStart = start;
        mAmbientFogOwner->mFogEnd = end;
    }
    void SetFadeRange(float start, float end) {
        mFadeStart = start;
        mFadeEnd = end;
    }
    void SetUseApproxLocal(bool b) { mUseApprox_Local = b; }
    void SetUseApproxGlobal(bool b) { mUseApprox_Global = b; }
    void SetUseApproxes(bool b) {
        SetUseApproxLocal(b);
        SetUseApproxGlobal(b);
    }
    bool GetUseApprox() const { return mUseApprox_Local || mUseApprox_Global; }
    bool UsesApproxLocal() const { return mUseApprox_Local; }
    bool UsesApproxGlobal() const { return mUseApprox_Global; }
    bool SetFogEnable(bool enable) { mAmbientFogOwner->mFogEnable = enable; }

    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(RndEnviron)
    static void Init() { REGISTER_OBJ_FACTORY(RndEnviron) }

    ObjPtrList<RndLight> mLightsReal; // 0x1c
    ObjPtrList<RndLight> mLightsApprox; // 0x2c
    ObjPtrList<RndLight> mLightsOld; // 0x3c
    Hmx::Color mAmbientColor; // 0x4c
    int unk5c; // 0x5c
    // mNumLightsReal, mNumLightsApprox, mNumLightsPoint, mNumLightsProj
    int mNumLightsReal; // 0x60
    int mNumLightsApprox; // 0x64
    int mNumLightsPoint; // 0x68
    int mNumLightsProj; // 0x6c
    bool mHasPointCubeTex; // 0x70
    ObjOwnerPtr<RndEnviron> mAmbientFogOwner; // 0x74
    bool mFogEnable; // 0x80
    float mFogStart; // 0x84
    float mFogEnd; // 0x88
    Hmx::Color mFogColor; // 0x8c
    bool mFadeOut; // 0x9c
    float mFadeStart; // 0xa0
    float mFadeEnd; // 0xa4
    float mFadeMax; // 0xa8
    ObjPtr<RndTransformable> mFadeRef; // 0xac
    Vector4 mLRFade; // 0xb8 - 0xc4, mLeftOut, mLeftOpaque, mRightOpaque, mRightOut
    RndColorXfm mColorXfm; // 0xc8
    bool mUseColorAdjust; // 0x14c
    bool mAnimateFromPreset; // 0x14d
    bool mAOEnabled; // 0x14e
    float mAOStrength; // 0x150
    Timer mUpdateTimer; // 0x158
    float mIntensityAverage; // 0x188
    float mIntensityRate; // 0x18c
    float mExposure; // 0x190
    float mWhitePoint; // 0x194
    bool mUseToneMapping; // 0x198
    bool mUseApprox_Local; // 0x199
    bool mUseApprox_Global; // 0x19A

    static RndEnviron *sCurrent;
    static Vector3 sCurrentPos;
    static bool sCurrentPosSet;
    static BoxMapLighting sGlobalLighting;
    DECLARE_REVS

    static Vector3 *CurrentPos() {
        if (sCurrentPosSet)
            return &sCurrentPos;
        else
            return nullptr;
    }
};

class RndEnvironTracker {
public:
    RndEnvironTracker(RndEnviron *env, const Vector3 *v3)
        : mOld(RndEnviron::sCurrent), mOldPosSet(RndEnviron::CurrentPos()) {
        if (mOldPosSet) {
            mOldPos = *RndEnviron::CurrentPos();
        } else {
            mOldPos.Zero();
        }
        if (env) {
            if (env != RndEnviron::sCurrent || !VecEqual(v3, RndEnviron::CurrentPos())) {
                env->Select(v3);
            }
        }
    }
    ~RndEnvironTracker() {
        Vector3 *vptr = mOldPosSet ? &mOldPos : nullptr;
        if (mOld) {
            if (mOld != RndEnviron::sCurrent
                || !VecEqual(vptr, RndEnviron::CurrentPos())) {
                mOld->Select(vptr);
            }
        }
    }

    bool VecEqual(const Vector3 *v1, const Vector3 *v2) const {
        if (v1 && v2) {
            return *v1 == *v2;
        } else
            return v1 == v2;
    }

    RndEnviron *mOld; // 0x0
    Vector3 mOldPos; // 0x4
    bool mOldPosSet; // 0x10
};