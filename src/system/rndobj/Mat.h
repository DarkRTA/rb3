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
    std::vector<Hmx::Color> unk98;
    MatPerfSettings unka0;
    MatShaderOptions unka4;
    bool mIntensify : 1; // 0xa9?_0
    bool mUseEnviron : 1; // 0xa9_1
    bool mPreLit : 1; // 0xa9_2
    bool mAlphaCut : 1; // 0xa9_3
    bool mAlphaWrite : 1; // 0xa9_4
    bool mCull : 1; // 0xa9_5
    bool mPerPixelLit : 1; // 0xa9_6
    bool mScreenAligned : 1; // 0xa9_7

    bool mRefractEnabled : 1; // 0xaa_0
    bool mPointLights : 1;
    bool mFog : 1;
    bool mFadeout : 1;
    bool mColorAdjust : 1;
    bool unk_0xaa_5 : 3;
    
    Blend mBlend : 8; // 0xac
    TexGen mTexGen : 8;
    int unkacp2 : 8;
    int unkacp3 : 8;
    // unkac also has mBlend, texgen but bit shifted?
    // blend = (int)(*(uint *)(this + 0xac) << 0x10 | *(uint *)(this + 0xac) >> 0x10) >> 0x18
    // texgen = (int)(*(uint *)(this + 0xac) << 0x18 | *(uint *)(this + 0xac) >> 8) >> 0x18;

    // b0 = zMode and stencil mode, texwrap, shader_variation
    // zmode = (int)(*(uint *)(this + 0xb0) << 8 | *(uint *)(this + 0xb0) >> 0x18) >> 0x18;
    // stencil mode = (int)(*(uint *)(this + 0xb0) << 0x10 | *(uint *)(this + 0xb0) >> 0x10) >> 0x18;
    // texwrap = *(int *)(this + 0xb0) >> 0x18;
    // shader variation = (int)(*(uint *)(this + 0xb0) << 0x18 | *(uint *)(this + 0xb0) >> 8) >> 0x18
    int unkb0p0 : 8;
    int unkb0p1 : 8;
    int unkb0p2 : 8;
    int unkb0p3 : 8;
    int unkb4p0 : 8;
    int unkb4p1 : 8;
    int unkb4p2 : 8;
    int unkb4p3 : 8;
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
