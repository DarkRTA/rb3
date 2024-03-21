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

    DECLARE_REVS;
    DELETE_OVERLOAD;

    Hmx::Color mColor;
    ObjOwnerPtr<RndLight, class ObjectDir> mColorOwner;
    float mRange;
    float mFalloffStart;
    Type mType;
    bool mAnimateColorFromPreset;
    bool mAnimatePositionFromPreset;
    bool mAnimateRangeFromPreset;
    bool mShowing;
    ObjPtr<RndTex, class ObjectDir> mTexture;
    int unknownint; // figure this out too
    ObjPtrList<RndDrawable, class ObjectDir> mShadowObjects;
    Transform mTextureXfm;
    float mTopRadius;
    float mBotRadius;
    int mProjectedBlend;
    bool mOnlyProjection;
};

#endif
