#include "rndobj/Mat.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(RndMat)

MatShaderOptions::MatShaderOptions() : i4(1), i1(1), b(0) {

}

DECOMP_FORCEACTIVE(Mat, "%s.mat")

MatPerfSettings::MatPerfSettings() : mRecvProjLights(0), mRecvPointCubeTex(0), mPS3ForceTrilinear(0) {

}

void MatPerfSettings::Load(BinStream& bs){
    LOAD_BITFIELD(bool, mRecvProjLights)
    LOAD_BITFIELD(bool, mPS3ForceTrilinear)
    if(RndMat::gRev > 0x41) LOAD_BITFIELD(bool, mRecvPointCubeTex)
}

RndMat::RndMat() : mDiffuseTex(this, 0), mAlphaThresh(0), mNextPass(this, 0), mEmissiveMap(this, 0), mRefractStrength(0.0f), mRefractNormalMap(this, 0),
    mIntensify(0), mUseEnviron(1), mPreLit(0), mAlphaCut(0), mAlphaWrite(0), mCull(1), mPerPixelLit(0), mScreenAligned(0),
    mRefractEnabled(0), mPointLights(0), mFog(0), mFadeout(0), mColorAdjust(0), mBlend(kDest), mTexGen(kTexGenNone) {
    mEmissiveMultiplier = 1.0f;
    mTexXfm.Reset();
    ResetColors(mColorMod, 3);
}

SAVE_OBJ(RndMat, 159)

bool RndMat::IsNextPass(RndMat* m) {
    RndMat* m2;
    while (m2 != NULL){
        if (m2 == m) return true;
        m2 = m2->mNextPass;
    }
    return false;
}

BEGIN_LOADS(RndMat)
    LOAD_REVS(bs)
    ASSERT_REVS(68, 0) // SIXTY EIGHT???
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
    bs >> mTexXfm;
    bs >> mDiffuseTex;
    bs >> mNextPass;
    LOAD_BITFIELD(bool, mIntensify)
    mDirty = 3;

    Hmx::Color loc_color;
    LOAD_BITFIELD(bool, mCull)
    bs >> mEmissiveMultiplier;
    bs >> loc_color;
    {
        MemDoTempAllocations tmp(true, false);
        ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
        bs >> texPtr;
    }
    bs >> mEmissiveMap;
    {
        MemDoTempAllocations tmp(true, false);
        ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
        bs >> texPtr;
    }
    if(gRev < 0x33){
        ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
        bs >> texPtr;
    }
    {
        MemDoTempAllocations tmp(true, false);
        ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
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
        mScreenAligned = b;
    }
    if((unsigned short)(gRev - 0x1B) <= 0x16U){
        bool b;
        bs >> b;
    }
    if(gRev > 0x1B){
        LOAD_BITFIELD_ENUM(int, mStencilMode, StencilMode)
    }
    if((u16)(gRev - 0x1D) <= 0xB){
        Symbol sym;
        bs >> sym;
    }
    {
        MemDoTempAllocations tmp(true, false);
        ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
        bs >> texPtr;
    }
    if((u16)(gRev - 0x22) <= 0xE){
        Hmx::Color color2;
        bool b;
        bs >> b >> color2;
        if(gRev > 0x22){
            MemDoTempAllocations tmp(true, false);
            ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
            bs >> texPtr;
        }
    }
    if(gRev > 0x23){
        int i;
        bs >> i >> i;
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
            ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
            bs >> texPtr;
        }
        if(gRev < 0x2A){
            ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
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
            mPointLights = i;
        }
        if(gRev < 0x3F){
            bool b; bs >> b;
        }
        LOAD_BITFIELD(bool, mFog)
        LOAD_BITFIELD(bool, mFadeout)
        if((u16)(gRev - 0x2C) <= 1){
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
            ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
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
            mShaderVariation = kShaderVariation_Skin;
        }
    }
    if(gRev > 0x32){
        LOAD_BITFIELD_ENUM(int, mShaderVariation, ShaderVariation)
        Hmx::Color col32;
        bs >> col32;
    }
    ResetColors(mColorMod, 3);
    if((u16)(gRev - 0x34) <= 0xF){
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
        if((u16)(gRev - 0x35) <= 6){
            bs >> col34;
        }
        if(gRev >= 0x3C){
            MemDoTempAllocations tmp(true, false);
            bs >> vec;
        }
    }
    if((u16)(gRev - 0x36) <= 7){
        ObjPtr<Hmx::Object, ObjectDir> objPtr(this, 0);
        bs >> objPtr;
    }
    if((u16)(gRev - 0x37) <= 7){
        bool b;
        bs >> b;
        mPerfSettings.mPS3ForceTrilinear = b;
    }
    if(gRev == 0x38){
        int i, j;
        bs >> i >> j;
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

// temporary
DECOMP_FORCEACTIVE(Mat, "m", "index >= 0 && index < kColorModNum", "%s(%d): %s unhandled msg: %s")

#define kColorModNum 2 // hack

void RndMat::SetColorMod(const Hmx::Color& col, int index){
    MILO_ASSERT(index >= 0 && index < kColorModNum, 0x2D4);
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
            if(_op == kPropSet) mPointLights = _val.Int(0);
            else _val = DataNode(mPointLights);
            return true;
        }
    }
    {
        static Symbol _s("fog");
        if(sym == _s){
            if(_op == kPropSet) mFog = _val.Int(0);
            else _val = DataNode(mFog);
            return true;
        }
    }
    {
        static Symbol _s("fade_out");
        if(sym == _s){
            if(_op == kPropSet) mFadeout = _val.Int(0);
            else _val = DataNode(mFadeout);
            return true;
        }
    }
    {
        static Symbol _s("color_adjust");
        if(sym == _s){
            if(_op == kPropSet) mColorAdjust = _val.Int(0);
            else _val = DataNode(mColorAdjust);
            return true;
        }
    }
    SYNC_PROP_SET(recv_proj_lights, mPerfSettings.mRecvProjLights, mPerfSettings.mRecvProjLights = _val.Int(0) > 0)
    SYNC_PROP_SET(recv_point_cube_tex, mPerfSettings.mRecvPointCubeTex, mPerfSettings.mRecvPointCubeTex = _val.Int(0) > 0)
    SYNC_PROP_SET(ps3_force_trilinear, mPerfSettings.mPS3ForceTrilinear, mPerfSettings.mPS3ForceTrilinear = _val.Int(0) > 0)
END_PROPSYNCS
#pragma pop