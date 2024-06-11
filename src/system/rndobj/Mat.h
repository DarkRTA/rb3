#ifndef RNDOBJ_MAT_H
#define RNDOBJ_MAT_H
#include "rndobj/Tex.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "math/Color.h"
#include "math/Mtx.h"
#include <vector>

enum Blend {
    kDest = 0,
    kSrc = 1,
    kAdd = 2,
    kSrcAlpha = 3,
    kSrcAlphaAdd = 4,
    kSubtract = 5,
    kMultiply = 6,
    kPreMultAlpha = 7,
};
enum ZMode {
    kDisable = 0,
    kNormal = 1,
    kTransparent = 2,
    kForce = 3,
    kDecal = 4,
};
enum StencilMode {
    kIgnore = 0,
    kWrite = 1,
    kTest = 2,
};
enum TexGen {
    kTexGenNone,
    kXfm,
    kSphere,
    kProjected,
    kXfmOrigin,
    kEnviron,
};
enum TexWrap {
    kClamp = 0,
    kRepeat = 1,
    kBorderBlack = 2,
    kBorderWhite = 3,
};
enum ShaderVariation {
    kShaderVariation_None,
    kShaderVariation_Skin,
    kShaderVariation_Hair
};

struct MatPerfSettings {
    MatPerfSettings();
    void Load(BinStream&);
    
    bool mRecvProjLights : 1;
    bool mRecvPointCubeTex : 1;
    bool mPS3ForceTrilinear : 1;
    // bool b3 : 1;
    // bool b4 : 1;
    // bool b5 : 1;
    // bool b6 : 1;
    // bool b7 : 1;
};

struct MatShaderOptions {
    MatShaderOptions();
    uint itop : 24;
    uint i7 : 1;
    uint i6 : 1;
    uint i5 : 1;
    uint i4 : 1;
    uint i3 : 1;
    uint i2 : 1;
    uint i1 : 1;
    uint i0 : 1;
    bool b; 
};

class RndMat : public Hmx::Object {
public:
    RndMat();
    virtual ~RndMat();
    OBJ_CLASSNAME(Mat);
    OBJ_SET_TYPE(Mat);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    bool IsNextPass(RndMat*);
    void SetColorMod(const Hmx::Color&, int);

    DECLARE_REVS
    NEW_OVERLOAD
    NEW_OBJ(RndMat)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMat)
    }

    Hmx::Color mColor; // 0x1c
    Transform mTexXfm; // 0x2c
    ObjPtr<RndTex, class ObjectDir> mDiffuseTex; // 0x5c
    int mAlphaThresh; // 0x68
    ObjPtr<RndMat, class ObjectDir> mNextPass; // 0x6c
    float mEmissiveMultiplier; // 0x78
    ObjPtr<RndTex, class ObjectDir> mEmissiveMap; // 0x7c
    float mRefractStrength; // 0x88
    ObjPtr<RndTex, class ObjectDir> mRefractNormalMap; // 0x8c
    std::vector<Hmx::Color> mColorMod; // 0x98
    MatPerfSettings mPerfSettings; // 0xa0
    MatShaderOptions mShaderOptions; // 0xa4

    // 0xac
    bool mIntensify : 1;
    bool mUseEnviron : 1;
    bool mPreLit : 1;
    bool mAlphaCut : 1;
    bool mAlphaWrite : 1;
    bool mCull : 1;
    bool mPerPixelLit : 1;
    bool mScreenAligned : 1;

    // 0xad
    bool mRefractEnabled : 1;
    bool mPointLights : 1;
    bool mFog : 1;
    bool mFadeout : 1;
    bool mColorAdjust : 1;
    unsigned char unkbool : 3;
    // bool unk_aa_1 : 1;
    // bool unk_aa_2 : 1;
    // bool unk_0xaa_5 : 1;
    
    // 0xb0
    Blend mBlend : 8;
    TexGen mTexGen : 8;
    TexWrap mTexWrap : 8;
    ZMode mZMode : 8;
    
    // 0xb4
    StencilMode mStencilMode : 8;
    ShaderVariation mShaderVariation : 8;
    int unkb0p2 : 8;
    int mDirty : 8;
};

#endif

// class RndMat : public Object {
//     // total size: 0x120
// protected:
//     unsigned char mIntensify; // offset 0x28, size 0x1
//     enum Blend mBlend; // offset 0x2C, size 0x4
//     class Color mColor; // offset 0x30, size 0x10
//     unsigned char mUseEnviron; // offset 0x40, size 0x1
//     enum ZMode mZMode; // offset 0x44, size 0x4
//     enum StencilMode mStencilMode; // offset 0x48, size 0x4
//     enum TexGen mTexGen; // offset 0x4C, size 0x4
//     enum TexWrap mTexWrap; // offset 0x50, size 0x4
//     class Transform mTexXfm; // offset 0x60, size 0x40
//     class ObjPtr mDiffuseTex; // offset 0xA0, size 0xC
//     unsigned char mPrelit; // offset 0xAC, size 0x1
//     unsigned char mAlphaCut; // offset 0xAD, size 0x1
//     int mAlphaThresh; // offset 0xB0, size 0x4
//     unsigned char mAlphaWrite; // offset 0xB4, size 0x1
//     class ObjPtr mNextPass; // offset 0xB8, size 0xC
//     unsigned char mCull; // offset 0xC4, size 0x1
//     unsigned char mNormalize; // offset 0xC5, size 0x1
//     class ObjPtr mCustomDiffuseMap; // offset 0xC8, size 0xC
//     unsigned char mTwoColor; // offset 0xD4, size 0x1
//     class ObjPtr mTwoColorMask; // offset 0xD8, size 0xC
//     class Color mColor1; // offset 0xF0, size 0x10
//     class Color mColor2; // offset 0x100, size 0x10
//     unsigned char mPointLights; // offset 0x110, size 0x1
//     unsigned char mProjLights; // offset 0x111, size 0x1
//     unsigned char mFog; // offset 0x112, size 0x1
//     unsigned char mFadeout; // offset 0x113, size 0x1
//     unsigned char mColorXfm; // offset 0x114, size 0x1
//     struct MatShaderOptions mShaderOptions; // offset 0x118, size 0x4
//     int mDirty; // offset 0x11C, size 0x4
// };
