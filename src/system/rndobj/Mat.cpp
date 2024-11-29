#include "rndobj/Mat.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "rndobj/Utl.h"
#include "rndobj/Rnd.h"
#include "utl/Symbols.h"

INIT_REVS(RndMat)

MatShaderOptions::MatShaderOptions() : mTempMat(0) {
    pack = mTempMat | 0x12;
}

RndMat* LookupOrCreateMat(const char* shader, ObjectDir* dir){
    const char* c = MakeString("%s.mat", FileGetBase(shader, 0));
    RndMat* mat = dir->Find<RndMat>(c, false);
    if(!mat){
        mat = dir->Find<RndMat>(FileGetBase(shader, 0), false);
        if(!mat){
            bool editmode = TheLoadMgr.EditMode();
            TheLoadMgr.SetEditMode(true);
            mat = dir->New<RndMat>(c);
            TheLoadMgr.SetEditMode(editmode);
        }
    }
    return mat;
}

MatPerfSettings::MatPerfSettings() : mRecvProjLights(0), mRecvPointCubeTex(0), mPS3ForceTrilinear(0) {

}

void MatPerfSettings::Load(BinStream& bs){
    LOAD_BITFIELD(bool, mRecvProjLights)
    LOAD_BITFIELD(bool, mPS3ForceTrilinear)
    if(RndMat::gRev > 65) LOAD_BITFIELD(bool, mRecvPointCubeTex)
}

RndMat::RndMat() : mColor(1.0f,1.0f,1.0f,1.0f), mDiffuseTex(this), mAlphaThresh(0), mNextPass(this), mEmissiveMap(this), mRefractStrength(0.0f), 
    mRefractNormalMap(this), mIntensify(0), mUseEnviron(1), mPreLit(0), mAlphaCut(0), mAlphaWrite(0), mCull(1), mPerPixelLit(0), mScreenAligned(0),
    mRefractEnabled(0), mPointLights(0), mFog(0), mFadeout(0), mColorAdjust(0), mBlend(kBlendSrc), mTexGen(kTexGenNone), mTexWrap(kTexWrapRepeat),
    mZMode(kZModeNormal), mStencilMode(kStencilIgnore), mShaderVariation(kShaderVariationNone), mColorModFlags(kColorModNone), mDirty(3) {
    mEmissiveMultiplier = 1.0f;
    mTexXfm.Reset();
    ResetColors(mColorMod, 3);
}

SAVE_OBJ(RndMat, 159)

bool RndMat::IsNextPass(RndMat* m) {
    for(RndMat* it = this; it != nullptr; it = it->NextPass()){
        if(it == m) return true;
    }
    return false;
}

// retail work: https://decomp.me/scratch/WpG47
BEGIN_LOADS(RndMat)
    LOAD_REVS(bs)
    ASSERT_REVS(68, 0)
    ASSERT_OLD_REV(25)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_BITFIELD_ENUM(int, mBlend, Blend)
    bs >> mColor;
    LOAD_BITFIELD(bool, mUseEnviron)
    LOAD_BITFIELD(bool, mPreLit)
    LOAD_BITFIELD_ENUM(int, mZMode, ZMode)
    LOAD_BITFIELD(bool, mAlphaCut)
    if(gRev > 0x25) bs >> mAlphaThresh;
    LOAD_BITFIELD(bool, mAlphaWrite)
    LOAD_BITFIELD_ENUM(int, mTexGen, TexGen)
    LOAD_BITFIELD_ENUM(int, mTexWrap, TexWrap)
    bs >> mTexXfm >> mDiffuseTex;
    bs >> mNextPass;
    LOAD_BITFIELD(bool, mIntensify)
    mDirty = 3;
    Hmx::Color loc_color;
    LOAD_BITFIELD(bool, mCull)
    bs >> mEmissiveMultiplier >> loc_color;
    {
        MemDoTempAllocations tmp(true, false);
        ObjPtr<RndTex> texPtr(this);
        bs >> texPtr;
    }
    bs >> mEmissiveMap;
    {
        MemDoTempAllocations tmp(true, false);
        ObjPtr<RndTex> texPtr(this);
        bs >> texPtr;
    }
    if(gRev < 0x33){
        ObjPtr<RndTex> texPtr(this);
        bs >> texPtr;
    }
    {
        MemDoTempAllocations tmp(true, false);
        ObjPtr<RndTex> texPtr(this);
        bs >> texPtr;
    }
    if(gRev > 0x3C){
        bool b;
        bs >> b;
        if(gRev > 0x42){
            bool b2;
            bs >> b2;
        }
    }
    if(gRev > 0x19){
        bool b;
        bs >> b;
        mPerPixelLit = b;
        mPerPixelLit = 0;
    }
    if(gRev >= 27 && gRev <= 49){
        bool b;
        bs >> b;
    }
    if(gRev > 0x1B){
        LOAD_BITFIELD_ENUM(int, mStencilMode, StencilMode)
    }
    if(gRev >= 29 && gRev <= 40){
        Symbol sym;
        bs >> sym;
    }
    {
        MemDoTempAllocations tmp(true, false);
        ObjPtr<RndTex> texPtr(this);
        bs >> texPtr;
    }
    if(gRev >= 34 && gRev <= 48){
        Hmx::Color color2;
        bool b;
        bs >> b >> color2;
        if(gRev > 0x22){
            MemDoTempAllocations tmp(true, false);
            ObjPtr<RndTex> texPtr(this);
            bs >> texPtr;
        }
    }
    if(gRev > 0x23){
        int i;
        bs >> i;
        bs >> i;
    }
    if(gRev > 0x26){
        if(gRev < 0x2A){
            bool b;
            bs >> b;
        }
        int i;
        bs >> i >> i;
        if(gRev < 0x2A){
            Hmx::Color color2;
            int b2;
            bs >> b2 >> color2;
        }
        {
            MemDoTempAllocations tmp(true, false);
            ObjPtr<RndTex> texPtr(this);
            bs >> texPtr;
        }
        if(gRev < 0x2A){
            ObjPtr<RndTex> texPtr(this);
            bs >> texPtr;
        }
    }
    if(gRev > 0x2A){
        if(gRev > 0x2C){
            LOAD_BITFIELD(bool, mPointLights)
        }
        else {
            int i;
            bs >> i;
            mPointLights = i > 1;
        }
        if(gRev < 0x3F){
            bool b; bs >> b;
        }
        LOAD_BITFIELD(bool, mFog)
        LOAD_BITFIELD(bool, mFadeout)
        if(gRev == 44 || gRev == 45){
            bool b; bs >> b;
        }
        if(gRev > 0x2E){
            LOAD_BITFIELD(bool, mColorAdjust)
        }
    }
    if(gRev > 0x2F){
        {
            MemDoTempAllocations tmp(true, false);
            Hmx::Color color2f;
            ObjPtr<RndTex> texPtr(this);
            bs >> color2f;
            bs >> texPtr;
            if(gRev > 0x39){
                bool b;
                bs >> b;
            }
            else {
                bool b;
                bs >> b;
            }
        }
    }
    if(gRev > 0x30){
        LOAD_BITFIELD(bool, mScreenAligned)
    }
    if(gRev == 0x32){
        bool uc;
        bs >> uc;
        if(uc){
            mShaderVariation = kShaderVariationSkin;
        }
    }
    if(gRev > 0x32){
        LOAD_BITFIELD_ENUM(int, mShaderVariation, ShaderVariation)
        Hmx::Color col32;
        bs >> col32;
    }
    ResetColors(mColorMod, 3);
    if(gRev >= 52 && gRev <= 67){
        std::vector<Hmx::Color> vec;
        Hmx::Color col34;
        if(gRev < 0x35){
            bool b;
            bs >> b;
        }
        else {
            int i;
            bs >> i;
        }
        if(gRev >= 53 && gRev <= 59){
            bs >> col34;
        }
        if(gRev >= 0x3C){
            MemDoTempAllocations tmp(true, false);
            bs >> vec;
        }
    }
    if(gRev >= 54 && gRev <= 61){
        ObjPtr<Hmx::Object> objPtr(this);
        bs >> objPtr;
    }
    if(gRev >= 55 && gRev <= 62){
        bool b;
        bs >> b;
        mPerfSettings.SetPS3ForceTrilinear(b);
    }
    if(gRev == 0x38){
        int i, j;
        bs >> i;
        bs >> j;
    }
    if(gRev > 0x3E){
        mPerfSettings.Load(bs);
    }
    if(gRev > 0x3F){
        LOAD_BITFIELD(bool, mRefractEnabled)
        bs >> mRefractStrength;
        bs >> mRefractNormalMap;
        if (gRev < 0x41) {
            if(mRefractEnabled) mRefractStrength *= 0.15f;
            else mRefractStrength = 0;
        }
    }
END_LOADS

BEGIN_COPYS(RndMat)
    CREATE_COPY_AS(RndMat, m)
    MILO_ASSERT(m, 0x287);
    COPY_SUPERCLASS(Hmx::Object)
    if(ty == kCopyFromMax){
        if(!mDiffuseTex != !m->mDiffuseTex){
            COPY_MEMBER_FROM(m, mDiffuseTex)
        }
    }
    else {
        COPY_MEMBER_FROM(m, mZMode)
        COPY_MEMBER_FROM(m, mStencilMode)
        COPY_MEMBER_FROM(m, mBlend)
        COPY_MEMBER_FROM(m, mColor)
        COPY_MEMBER_FROM(m, mPreLit)
        COPY_MEMBER_FROM(m, mUseEnviron)
        COPY_MEMBER_FROM(m, mAlphaCut)
        COPY_MEMBER_FROM(m, mAlphaThresh)
        COPY_MEMBER_FROM(m, mAlphaWrite)
        COPY_MEMBER_FROM(m, mTexGen)
        COPY_MEMBER_FROM(m, mTexWrap)
        COPY_MEMBER_FROM(m, mTexXfm)
        COPY_MEMBER_FROM(m, mDiffuseTex)
        COPY_MEMBER_FROM(m, mNextPass)
        COPY_MEMBER_FROM(m, mCull)
        COPY_MEMBER_FROM(m, mEmissiveMultiplier)
        COPY_MEMBER_FROM(m, mEmissiveMap)
        COPY_MEMBER_FROM(m, mIntensify)
        COPY_MEMBER_FROM(m, mPerPixelLit)
        COPY_MEMBER_FROM(m, mPointLights)
        COPY_MEMBER_FROM(m, mFog)
        COPY_MEMBER_FROM(m, mFadeout)
        COPY_MEMBER_FROM(m, mColorAdjust)
        COPY_MEMBER_FROM(m, mScreenAligned)
        COPY_MEMBER_FROM(m, mShaderVariation)
        COPY_MEMBER_FROM(m, mShaderOptions)
        COPY_MEMBER_FROM(m, mColorModFlags) // color mod flags
        COPY_MEMBER_FROM(m, mColorMod)
        COPY_MEMBER_FROM(m, mPerfSettings)
        COPY_MEMBER_FROM(m, mRefractEnabled)
        COPY_MEMBER_FROM(m, mRefractStrength)
        COPY_MEMBER_FROM(m, mRefractNormalMap)
    }
    mDirty = 3;
END_COPYS

#define kColorModNum 3 // hack

void RndMat::SetColorMod(const Hmx::Color& col, int index){
    MILO_ASSERT(index >= 0 && index < kColorModNum, 0x2D4);
    mColorMod[index] = col;
    mDirty |= 2;
}

bool RndMat::GetRefractEnabled(bool b){
    bool ret = false;
    if(mRefractEnabled == 1 && mRefractStrength > 0.0f && mRefractNormalMap){
        if(b || TheRnd->GetCurrentFrameTex(false)){
            ret = true;
        }
    }
    return ret;
}

RndTex* RndMat::GetRefractNormalMap(){ return mRefractNormalMap; }
float RndMat::GetRefractStrength(){ return mRefractStrength; }

BEGIN_HANDLERS(RndMat)
    HANDLE(allowed_next_pass, OnAllowedNextPass)
    HANDLE(allowed_normal_map, OnAllowedNormalMap)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x305)
END_HANDLERS

DataNode RndMat::OnAllowedNextPass(const DataArray*){
    int matcount = 0;
    for(ObjDirItr<RndMat> it(Dir(), true); it != 0; ++it){
        matcount++;
    }
    DataArrayPtr ptr(new DataArray(matcount + 2));
    int idx = 0;
    ptr->Node(idx++) = NULL_OBJ;
    if(NextPass()){
        ptr->Node(idx++) = NextPass();
    }
    for(ObjDirItr<RndMat> it(Dir(), true); it != 0; ++it){
        if(!IsNextPass(it)){
            ptr->Node(idx++) = DataNode(it);
        }
    }
    ptr->Resize(idx);
    return ptr;
}

DataNode RndMat::OnAllowedNormalMap(const DataArray*){
    return GetNormalMapTextures(Dir());
}

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(RndMat)
    {
        static Symbol _s("intensify");
        bool bit = mIntensify;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mIntensify = bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    SYNC_PROP_MODIFY_ALT(color, mColor, mDirty |= 1)
    SYNC_PROP_MODIFY(alpha, mColor.alpha, mDirty |= 1)
    {
        static Symbol _s("use_environ");
        bool bit = mUseEnviron;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mUseEnviron = bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    {
        static Symbol _s("blend");
        int bit = mBlend;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mBlend = (Blend)bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    {
        static Symbol _s("z_mode");
        int bit = mZMode;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mZMode = (ZMode)bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    {
        static Symbol _s("stencil_mode");
        int bit = mStencilMode;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mStencilMode = (StencilMode)bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    {
        static Symbol _s("tex_gen");
        int bit = mTexGen;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mTexGen = (TexGen)bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    {
        static Symbol _s("tex_wrap");
        int bit = mTexWrap;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mTexWrap = (TexWrap)bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    {
        static Symbol _s("shader_variation");
        int bit = mShaderVariation;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mShaderVariation = (ShaderVariation)bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    SYNC_PROP_MODIFY_ALT(tex_xfm, mTexXfm, mDirty |= 2)
    SYNC_PROP_MODIFY_ALT(diffuse_tex, mDiffuseTex, mDirty |= 2)
    {
        static Symbol _s("prelit");
        bool bit = mPreLit;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mPreLit = bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    {
        static Symbol _s("alpha_cut");
        bool bit = mAlphaCut;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mAlphaCut = bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    SYNC_PROP_MODIFY(alpha_threshold, mAlphaThresh, mDirty |= 2)
    {
        static Symbol _s("alpha_write");
        bool bit = mAlphaWrite;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mAlphaWrite = bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    SYNC_PROP(next_pass, mNextPass)
    {
        static Symbol _s("cull");
        bool bit = mCull;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mCull = bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    {
        static Symbol _s("per_pixel_lit");
        bool bit = mPerPixelLit;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mPerPixelLit = bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    SYNC_PROP_MODIFY(emissive_multiplier, mEmissiveMultiplier, mDirty |= 2)
    SYNC_PROP_MODIFY_ALT(emissive_map, mEmissiveMap, mDirty |= 2)
    {
        static Symbol _s("refract_enabled");
        bool bit = mRefractEnabled;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mRefractEnabled = bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    SYNC_PROP_MODIFY(refract_strength, mRefractStrength, mDirty |= 2)
    SYNC_PROP_MODIFY_ALT(refract_normal_map, mRefractNormalMap, mDirty |= 2)
    {
        static Symbol _s("screen_aligned");
        bool bit = mScreenAligned;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mScreenAligned = bit;
            if(!(_op & (kPropSize|kPropGet))){
                mDirty |= 2;
            }
            return ret;
        }
    }
    {
        static Symbol _s("point_lights");
        if(sym == _s){
            if(_op == kPropSet) mPointLights = _val.Int();
            else _val = DataNode(mPointLights);
            return true;
        }
    }
    {
        static Symbol _s("fog");
        if(sym == _s){
            if(_op == kPropSet) mFog = _val.Int();
            else _val = DataNode(mFog);
            return true;
        }
    }
    {
        static Symbol _s("fade_out");
        if(sym == _s){
            if(_op == kPropSet) mFadeout = _val.Int();
            else _val = DataNode(mFadeout);
            return true;
        }
    }
    {
        static Symbol _s("color_adjust");
        if(sym == _s){
            if(_op == kPropSet) mColorAdjust = _val.Int();
            else _val = DataNode(mColorAdjust);
            return true;
        }
    }
    SYNC_PROP_SET(recv_proj_lights, mPerfSettings.mRecvProjLights, mPerfSettings.mRecvProjLights = _val.Int() > 0)
    SYNC_PROP_SET(recv_point_cube_tex, mPerfSettings.mRecvPointCubeTex, mPerfSettings.mRecvPointCubeTex = _val.Int() > 0)
    SYNC_PROP_SET(ps3_force_trilinear, mPerfSettings.mPS3ForceTrilinear, mPerfSettings.mPS3ForceTrilinear = _val.Int() > 0)
END_PROPSYNCS
#pragma pop
