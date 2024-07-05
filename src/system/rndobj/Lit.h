#ifndef RNDOBJ_LIT_H
#define RNDOBJ_LIT_H
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
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~RndLight(){}
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void SetColor(const Hmx::Color&);
    virtual void SetLightType(Type);
    virtual void SetRange(float);
    virtual void SetFalloffStart(float);

    void SetTopRadius(float);
    void SetBotRadius(float);
    void SetShadowOverride(ObjPtrList<RndDrawable, class ObjectDir>*);
    float Range() const { return mRange; }
    const Hmx::Color& GetColor() const { return mColorOwner->mColor; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS
    NEW_OBJ(RndLight)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndLight)
    }

    Hmx::Color mColor; // 0x90
    ObjOwnerPtr<RndLight, class ObjectDir> mColorOwner; // 0xA0
    float mRange; // 0xAC
    float mFalloffStart; // 0xB0
    Type mType; // 0xB4
    bool mAnimateColorFromPreset; // 0xB8
    bool mAnimatePositionFromPreset; // 0xB9
    bool mAnimateRangeFromPreset; // 0xBA
    bool mShowing; // 0xBB
    ObjPtr<RndTex, class ObjectDir> mTexture; // 0xBC
    ObjPtrList<RndDrawable, class ObjectDir>* mShadowOverride; // figure this out too - 0xC8
    ObjPtrList<RndDrawable, class ObjectDir> mShadowObjects; // 0xCC
    Transform mTextureXfm; // 0xDC
    float mTopRadius; // 0x10C
    float mBotRadius; // 0x110
    int mProjectedBlend; // 0x114
    bool mOnlyProjection; // 0x118
};

#endif
