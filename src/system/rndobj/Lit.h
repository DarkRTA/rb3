#pragma once
#include "rndobj/Trans.h"
#include "math/Color.h"
#include "rndobj/Tex.h"
#include "rndobj/Draw.h"

class RndLight : public RndTransformable {
public:
    enum Type {
        kPoint = 0,
        kDirectional = 1,
        kFakeSpot = 2,
        kFloorSpot = 3,
        kShadowRef = 4,
    };
    RndLight();
    OBJ_CLASSNAME(Light)
    OBJ_SET_TYPE(Light)
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, CopyType);
    virtual void Load(BinStream &);
    virtual ~RndLight() {}
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void SetColor(const Hmx::Color &c) { mColorOwner->mColor = c; }
    virtual void SetLightType(Type);
    virtual void SetRange(float r) { mRange = r; }
    virtual void SetFalloffStart(float);

    void SetTopRadius(float);
    void SetBotRadius(float);
    void SetShadowOverride(ObjPtrList<RndDrawable> *);
    float Range() const { return mRange; }
    float FalloffStart() const { return mFalloffStart; }
    const Hmx::Color &GetColor() const { return mColorOwner->mColor; }
    Type GetType() const { return mType; }
    void SetShowing(bool b) { mShowing = b; }
    void SetPackedColor(int, float);
    int PackedColor() const;
    float Intensity() const;
    void SetProjectedBlend(int i) { mProjectedBlend = i; }
    bool GetAnimateFromPreset() const {
        return mAnimateColorFromPreset || mAnimatePositionFromPreset
            || mAnimateRangeFromPreset;
    }
    bool Showing() const { return mShowing; }
    bool AnimatePosFromPreset() const { return mAnimatePositionFromPreset; }
    bool AnimateRangeFromPreset() const { return mAnimateRangeFromPreset; }

    static const char *TypeToStr(Type);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS
    NEW_OBJ(RndLight)
    static void Init() { REGISTER_OBJ_FACTORY(RndLight) }

    Hmx::Color mColor; // 0x90
    ObjOwnerPtr<RndLight> mColorOwner; // 0xA0
    float mRange; // 0xAC
    float mFalloffStart; // 0xB0
    Type mType; // 0xB4
    bool mAnimateColorFromPreset; // 0xB8
    bool mAnimatePositionFromPreset; // 0xB9
    bool mAnimateRangeFromPreset; // 0xBA
    bool mShowing; // 0xBB
    ObjPtr<RndTex> mTexture; // 0xBC
    ObjPtrList<RndDrawable> *mShadowOverride; // figure this out too - 0xC8
    ObjPtrList<RndDrawable> mShadowObjects; // 0xCC
    Transform mTextureXfm; // 0xDC
    float mTopRadius; // 0x10C
    float mBotRadius; // 0x110
    int mProjectedBlend; // 0x114
    bool mOnlyProjection; // 0x118
};
