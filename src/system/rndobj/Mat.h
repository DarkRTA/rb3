#pragma once

#include <vector>
#include "math/Color.h"
#include "math/Mtx.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Tex.h"

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
            int mHasAOCalc : 1;
            int mHasBones : 1;
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
    }; // 0x0
    bool mTempMat; // 0x4

    // TODO: rename this once you have a better idea of what it does
    void SetLast5(int mask){
        pack = (pack & ~0x1f) | (mask & 0x1f);
    }

    void SetHasBones(bool bones){    
        shader_struct.mHasBones = 0;
        shader_struct.mHasBones = bones;
    }

    void SetHasAOCalc(bool calc){
        shader_struct.mHasAOCalc = 0;
        shader_struct.mHasAOCalc = calc;
    }
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
    TexWrap GetTexWrap() const { return mTexWrap; }
    Blend GetBlend() const { return mBlend; }
    ZMode GetZMode() const { return mZMode; }
    RndMat* NextPass() const { return mNextPass; }
    const Transform& TexXfm() const { return mTexXfm; }
    void SetTexXfm(const Transform& tf){
        mTexXfm = tf;
        mDirty |= 2;
    }
    void SetZMode(ZMode mode){
        mZMode = mode;
        mDirty |= 2;
    }
    void SetDiffuseTex(RndTex* tex){
        mDiffuseTex = tex;
        mDirty |= 2;
    }
    RndTex* GetDiffuseTex() const { return mDiffuseTex; }
    const Hmx::Color& GetColor() const { return mColor; }
    float Alpha() const { return mColor.alpha; }
    void SetAlpha(float f){
        mColor.alpha = f;
        mDirty |= 1;
    }
    void SetColor(const Hmx::Color& col){
        mColor.Set(col.red, col.green, col.blue);
        mDirty |= 1;
    }
    void SetUseEnv(bool use_env){
        mUseEnviron = use_env;
        mDirty |= 2;
    }
    void SetPreLit(bool lit){
        mPreLit = lit;
        mDirty |= 2;
    }
    void SetBlend(Blend blend){
        mBlend = blend;
        mDirty |= 2;
    }
    void SetAlphaCut(bool cut){
        mAlphaCut = cut;
        mDirty |= 2;
    }
    void SetCull(bool cull){
        mCull = cull;
        mDirty |= 2;
    }
    void SetAlphaThreshold(int thresh){
        mAlphaThresh = thresh;
    }
    void SetTexWrap(TexWrap wrap){
        mTexWrap = wrap;
        mDirty |= 2;
    }
    void SetPerPixelLit(bool lit){
        mPerPixelLit = lit;
        mDirty |= 2;
    }
    void SetPointLights(bool lit){
        mPointLights = lit;
    }

    DataNode OnAllowedNextPass(const DataArray*);
    DataNode OnAllowedNormalMap(const DataArray*);

    DECLARE_REVS
    NEW_OVERLOAD
    NEW_OBJ(RndMat)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndMat)
    }

    /** "Base material color" */
    Hmx::Color mColor; // 0x1c

    /** "Transform for coordinate generation" */
    Transform mTexXfm; // 0x2c

    /** "Base texture map, modulated with color and alpha" */
    ObjPtr<RndTex, class ObjectDir> mDiffuseTex; // 0x5c

    /** "Alpha level below which gets cut" */
    int mAlphaThresh; // 0x68

    /** "Next material for object" */
    ObjPtr<RndMat, class ObjectDir> mNextPass; // 0x6c

    /** "Multiplier to apply to emission" */
    float mEmissiveMultiplier; // 0x78

    /** "Map for self illumination" */
    ObjPtr<RndTex, class ObjectDir> mEmissiveMap; // 0x7c

    /** "The scale of the refraction of the screen under the material." */
    float mRefractStrength; // 0x88

    /** "This is a normal map used to distort the screen under the material. If none is specified, the regular normal map will be used." */
    ObjPtr<RndTex, class ObjectDir> mRefractNormalMap; // 0x8c

    std::vector<Hmx::Color> mColorMod; // 0x98
    MatPerfSettings mPerfSettings; // 0xa0
    MatShaderOptions mShaderOptions; // 0xa4

    // 0xac
    /** "Double the intensity of base map" */
    bool mIntensify : 1;

    /** "Modulate with environment ambient and lights" */
    bool mUseEnviron : 1;

    /** "Use vertex color and alpha for base or ambient" */
    bool mPreLit : 1;

    /** "Cut zero alpha pixels from z-buffer" */
    bool mAlphaCut : 1;

    /** "Write pixel alpha to screen" */
    bool mAlphaWrite : 1;

    /** "Cull backface polygons" */
    bool mCull : 1;

    /** "Use per-pixel lighting" */
    bool mPerPixelLit : 1;

    /** "Projected material from camera's POV" */
    bool mScreenAligned : 1;

    // 0xad
    /** "When enabled, this material will refract the screen under the material" */
    bool mRefractEnabled : 1;

    /** "Is the Mat lit with point lights?" */
    bool mPointLights : 1;

    /** "Is the Mat affected by fog?" */
    bool mFog : 1;

    /** "Is the Mat affected its Environment's fade_out?" */
    bool mFadeout : 1;

    /** "Is the Mat affected its Environment's color adjust?" */
    bool mColorAdjust : 1;

    unsigned char unkbool : 3;
    
    // 0xb0
    /** "How to blend poly into screen" */
    Blend mBlend : 8;

    /** "How to generate texture coordinates" */
    TexGen mTexGen : 8;

    /** "Texture mapping mode" */
    TexWrap mTexWrap : 8;

    /** "How to read and write z-buffer" */
    ZMode mZMode : 8;
    
    // 0xb4
    /** "How to read and write the stencil buffer" */
    StencilMode mStencilMode : 8;

    /** "Select a variation on the shader to enable a new range of rendering features." */
    ShaderVariation mShaderVariation : 8;

    int unkb0p2 : 8;
    int mDirty : 8;
};

RndMat* LookupOrCreateMat(const char*, ObjectDir*);