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

struct bf {
    uint val;
};

struct MatShaderOptions {
    MatShaderOptions();
    union {
        struct {
            int itop : 24;
            int i7 : 1;
            int i6 : 1;
            int i5 : 1;
            int i4 : 1;
            int i3 : 1;
            int i2 : 1;
            int i1 : 1;
            int i0 : 1;
        } shader_struct;
        u32 pack;

        // from bank 5
        uint value;
        bf shaderType;
        bf billboard;
        bf skinned;
        bf useAO;
    };

    bool mTempMat;
};

class RndMat : public Hmx::Object {
public:
    RndMat();
    virtual ~RndMat(){}
    OBJ_CLASSNAME(Mat);
    OBJ_SET_TYPE(Mat);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    bool IsNextPass(RndMat*);
    void SetColorMod(const Hmx::Color&, int);
    bool GetRefractEnabled(bool);
    RndTex* GetRefractNormalMap();
    float GetRefractStrength();
    float GetAlpha(){ return mColor.alpha; }
    void SetAlpha(float f){
        mColor.alpha = f;
        mDirty |= 1;
    }
    void SetColor(const Hmx::Color& col){
        mColor.red = col.red;
        mColor.green = col.green;
        mColor.blue = col.blue;
        mDirty |= 1;
    }

    DataNode OnAllowedNextPass(const DataArray*);
    DataNode OnAllowedNormalMap(const DataArray*);

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

RndMat* LookupOrCreateMat(const char*, ObjectDir*);