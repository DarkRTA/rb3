#pragma once
#include <vector>
#include "math/Color.h"
#include "math/Mtx.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Tex.h"

enum StencilMode {
    kStencilIgnore = 0,
    kStencilWrite = 1,
    kStencilTest = 2,
};
enum TexGen {
    /** "use vertex UV unchanged" */
    kTexGenNone = 0,
    /** "transform vertex UV about center with stage xfm" */
    kTexGenXfm = 1,
    /** "sphere map that rotates around object with camera, xfm is direction of map, fast
     * on gs slow on cpu, flips at poles" */
    kTexGenSphere = 2,
    /** "project from direction of stage xfm in world coords" */
    kTexGenProjected = 3,
    /** "like Xfm but about origin rather than center" */
    kTexGenXfmOrigin = 4,
    /** "reflection map, like sphere map but perspective correct and does not flip, fast
     * on cpu but slow on gs" */
    kTexGenEnviron = 5,
};
enum TexWrap {
    /** "UVs outside the range [0,1] are clamped" */
    kTexWrapClamp = 0,
    /** "The image repeats itself across the surface" */
    kTexWrapRepeat = 1,
    /** "texels outside the UV range [0,1] are black" */
    kTexBorderBlack = 2,
    /** "texels outside the UV range [0,1] are white" */
    kTexBorderWhite = 3,
    /** "The image repeats itself, but is flipped every other repetition" */
    kTexWrapMirror = 4
};
enum ShaderVariation {
    kShaderVariationNone = 0,
    kShaderVariationSkin = 1,
    kShaderVariationHair = 2
};

/** Toggles pertaining to RndMat performance. */
struct MatPerfSettings {
    MatPerfSettings();
    void Load(BinStream &);
    void SetPS3ForceTrilinear(bool set) { mPS3ForceTrilinear = set; }

    /** "Check this option to allow the material to receive projected lighting" */
    bool mRecvProjLights : 1;
    /** "Check this option to allow the material to receive projected cube maps from a
     * point light" */
    bool mRecvPointCubeTex : 1;
    /** "Force trilinear filtering of diffuse map (PS3 only)" */
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
    void SetLast5(int mask) { pack = (pack & ~0x1f) | (mask & 0x1f); }

    void SetHasBones(bool bones) {
        shader_struct.mHasBones = 0;
        shader_struct.mHasBones = bones;
    }

    void SetHasAOCalc(bool calc) {
        shader_struct.mHasAOCalc = 0;
        shader_struct.mHasAOCalc = calc;
    }
};

/**
 * @brief A class for material.
 * Original _objects description:
 * "Material objects determine texturing, blending, and the
 * effect of lighting on drawn polys."
 */
class RndMat : public Hmx::Object {
public:
    enum ColorModFlags {
        kColorModNone = 0,
        kColorModAlphaPack = 1,
        kColorModAlphaUnpackModulate = 2,
        kColorModModulate = 3,
        kColorModNum = 3
    };

    enum Blend {
        /** "Don't show this material at all; just show the frame buffer" */
        kBlendDest = 0,
        /** "Don't blend this material at all" */
        kBlendSrc = 1,
        /** "Output is material + frame buffer" */
        kBlendAdd = 2,
        /** "Output is (material x mat alpha) + (frame buffer x (1 - mat alpha))" */
        kBlendSrcAlpha = 3,
        /** "Output is (material x mat alpha) + frame buffer" */
        kBlendSrcAlphaAdd = 4,
        /** "Output is frame buffer - material" */
        kBlendSubtract = 5,
        /** "Output is frame buffer x material" */
        kBlendMultiply = 6,
        /** "Output is material + (frame buffer x (1 - mat alpha)" */
        kPreMultAlpha = 7,
    };
    enum ZMode {
        /** "always draw but don't update z-buffer" */
        kZModeDisable = 0,
        /** "draw and update z-buffer if closer than z-buffer" */
        kZModeNormal = 1,
        /** "draw if closer than or equal z-buffer but don't update z-buffer. Often used
         * with SrcAlpha or Add blending so those objects don't occlude other similar
         * objects" */
        kZModeTransparent = 2,
        /** "always draw and update z-buffer" */
        kZModeForce = 3,
        /** "draw and update z-buffer if closer than or equal to z-buffer" */
        kZModeDecal = 4,
    };

    RndMat();
    virtual ~RndMat() {}
    OBJ_CLASSNAME(Mat);
    OBJ_SET_TYPE(Mat);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    /** Determine whether the supplied Mat is in the collection of Mats pertaining to this
     * Object.
     * @param [in] mat The Mat to search for.
     */
    bool IsNextPass(RndMat *mat);
    /** Set the color mod at the supplied index.
     * @param [in] col The color to apply.
     * @param [in] idx The index of the color mod.
     */
    void SetColorMod(const Hmx::Color &col, int idx);
    // getters and setters
    bool GetRefractEnabled(bool);
    RndTex *GetRefractNormalMap();
    float GetRefractStrength();
    TexWrap GetTexWrap() const { return mTexWrap; }
    Blend GetBlend() const { return mBlend; }
    ZMode GetZMode() const { return mZMode; }
    RndMat *NextPass() const { return mNextPass; }
    const Transform &TexXfm() const { return mTexXfm; }
    void SetTexXfm(const Transform &tf) {
        mTexXfm = tf;
        mDirty |= 2;
    }
    void SetZMode(ZMode mode) {
        mZMode = mode;
        mDirty |= 2;
    }
    void SetDiffuseTex(RndTex *tex) {
        mDiffuseTex = tex;
        mDirty |= 2;
    }
    RndTex *GetDiffuseTex() const { return mDiffuseTex; }
    const Hmx::Color &GetColor() const { return mColor; }
    float Alpha() const { return mColor.alpha; }
    void SetAlpha(float f) {
        mColor.alpha = f;
        mDirty |= 1;
    }
    void SetColor(const Hmx::Color &col) {
        mColor.Set(col.red, col.green, col.blue);
        mDirty |= 1;
    }
    void SetUseEnv(bool use_env) {
        mUseEnviron = use_env;
        mDirty |= 2;
    }
    void SetPreLit(bool lit) {
        mPreLit = lit;
        mDirty |= 2;
    }
    void SetBlend(Blend blend) {
        mBlend = blend;
        mDirty |= 2;
    }
    void SetAlphaCut(bool cut) {
        mAlphaCut = cut;
        mDirty |= 2;
    }
    void SetCull(bool cull) {
        mCull = cull;
        mDirty |= 2;
    }
    void SetAlphaThreshold(int thresh) { mAlphaThresh = thresh; }
    void SetTexWrap(TexWrap wrap) {
        mTexWrap = wrap;
        mDirty |= 2;
    }
    void SetPerPixelLit(bool lit) {
        mPerPixelLit = lit;
        mDirty |= 2;
    }
    void SetPointLights(bool lit) { mPointLights = lit; }
    void SetShaderOpts(const MatShaderOptions &opts) { mShaderOptions = opts; }

    void SetColorModFlags(ColorModFlags flags) {
        mColorModFlags = flags;
        mDirty |= 2;
    }

    /** Handler to get all Mats in this Object's Dir that are NOT part of the material
     * list.
     * @returns a DataArray of all Mats that satisfy the above condition.
     * Example usage: {$this allowed_next_pass}
     */
    DataNode OnAllowedNextPass(const DataArray *);
    DataNode OnAllowedNormalMap(const DataArray *);

    DECLARE_REVS
    NEW_OVERLOAD
    NEW_OBJ(RndMat)
    static void Init() { REGISTER_OBJ_FACTORY(RndMat) }

    /** "Base material color" */
    Hmx::Color mColor; // 0x1c
    /** "Transform for coordinate generation" */
    Transform mTexXfm; // 0x2c
    /** "Base texture map, modulated with color and alpha" */
    ObjPtr<RndTex> mDiffuseTex; // 0x5c
    /** "Alpha level below which gets cut". Ranges from 0 to 255. */
    int mAlphaThresh; // 0x68
    /** "Next material for object" */
    ObjPtr<RndMat> mNextPass; // 0x6c
    /** "Multiplier to apply to emission" */
    /* ------------------------------------------------------------------------ */
    /* Emissive Settings:
     * "Settings for manipulating the emissive properties of the material"
     */
    float mEmissiveMultiplier; // 0x78
    /** "Map for self illumination" */
    ObjPtr<RndTex> mEmissiveMap; // 0x7c
    /* ------------------------------------------------------------------------ */
    /* Refraction Settings:
     * "Settings for applying refraction to the material"
     */
    /** "The scale of the refraction of the screen under the material." Ranges from 0 to
     * 100. */
    float mRefractStrength; // 0x88
    /** "This is a normal map used to distort the screen under the material. If none is
     * specified, the regular normal map will be used." */
    ObjPtr<RndTex> mRefractNormalMap; // 0x8c
    /* ------------------------------------------------------------------------ */
    std::vector<Hmx::Color> mColorMod; // 0x98
    /** "Performance options for this material" */
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
    /* ------------------------------------------------------------------------ */
    /* Shader Capabilities:
     * "Defines the capabilities of the shader generated using this material"
     */
    /** "Is the Mat lit with point lights?" */
    bool mPointLights : 1;
    /** "Is the Mat affected by fog?" */
    bool mFog : 1;
    /** "Is the Mat affected its Environment's fade_out?" */
    bool mFadeout : 1;
    /** "Is the Mat affected its Environment's color adjust?" */
    bool mColorAdjust : 1;
    /* ------------------------------------------------------------------------ */

    unsigned char unk_0xAD_5 : 1;
    unsigned char unk_0xAD_6 : 1; // referenced in WiiMat::SetModelviewTexGen
    unsigned char unk_0xAD_7 : 1; // referenced in WiiMat::WiiMat
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
    ColorModFlags mColorModFlags : 8;
    int mDirty : 8;
};

RndMat *LookupOrCreateMat(const char *, ObjectDir *);