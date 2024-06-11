#include "rndobj/Mat.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"

INIT_REVS(RndMat)

MatShaderOptions::MatShaderOptions() : i4(1), i1(1), b(0) {

}

MatPerfSettings::MatPerfSettings() : mRecvProjLights(0), mRecvPointCubeTex(0), mPS3ForceTrilinear(0) {

}

RndMat::RndMat() : mDiffuseTex(this, 0), mAlphaThresh(0), mNextPass(this, 0), mEmissiveMap(this, 0), mRefractStrength(0.0f), mRefractNormalMap(this, 0),
    mIntensify(0), mUseEnviron(1), mPreLit(0), mAlphaCut(0), mAlphaWrite(0), mCull(1), mPerPixelLit(0), mScreenAligned(0),
    mRefractEnabled(0), mPointLights(0), mFog(0), mFadeout(0), mColorAdjust(0), mBlend(kDest), mTexGen(kTexGenNone) {
    mEmissiveMultiplier = 1.0f;
    mTexXfm.Reset();
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
    int bs_ac; bs >> bs_ac;
    mBlend = (Blend)bs_ac;
    bs >> mColor;
    bool bs_a9_1; bs >> bs_a9_1;
    mUseEnviron = bs_a9_1;
    bool bs_a9_2; bs >> bs_a9_2;
    mPreLit = bs_a9_2;

    int bs_b0_1; bs >> bs_b0_1;
    unkacp3 = bs_b0_1;
    
    bool bs_a9_3; bs >> bs_a9_3;
    mAlphaCut = bs_a9_3;
    if(gRev > 0x25) bs >> mAlphaThresh;
    bool bs_a9_4; bs >> bs_a9_4;
    mAlphaWrite = bs_a9_4;
    int bs_ac_2; bs >> bs_ac_2;
    mTexGen = (TexGen)bs_ac_2;

    int bs_b0_0; bs >> bs_b0_0;
    unkacp2 = bs_b0_0;

    bs >> mTexXfm;
    bs >> mDiffuseTex;
    bs >> mNextPass;
    bool bs_ac_3; bs >> bs_ac_3;
    mIntensify = bs_ac_3;
    unkb0p3 = 3;

    Hmx::Color loc_color;
    bool asdf; bs >> asdf;
    mCull = asdf;
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
        int bs_b0_2;
        bs >> bs_b0_2;
        unkb0p0 = bs_b0_2;
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
            bool b;
            bs >> b;
            mPointLights = b;
        }
        else {
            int i;
            bs >> i;
            mPointLights = i;
        }
        if(gRev < 0x3F){
            bool b; bs >> b;
        }
        bool b2a_1;
        bs >> b2a_1;
        mFog = b2a_1;
        bool b2a_2;
        bs >> b2a_2;
        mFadeout = b2a_2;
        if((u16)(gRev - 0x2C) <= 1){
            bool b; bs >> b;
        }
        if(gRev > 0x2E){
            bool b;
            bs >> b;
            mColorAdjust = b;
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
        bool uc;
        bs >> uc;
        mScreenAligned = uc;
    }
    if(gRev == 0x32){
        bool uc;
        bs >> uc;
        if(uc){
            unkb0p1 = 1;
        }
    }
    if(gRev > 0x32){
        int i;
        bs >> i;
        unkb0p1 = i;
        Hmx::Color col32;
        bs >> col32;
    }
    ResetColors(unk98, 3);
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
        unka0.mPS3ForceTrilinear = b;
    }
    if(gRev == 0x38){
        int i, j;
        bs >> i >> j;
    }
    if(gRev > 0x3E){
        unka0.Load(bs);
    }
    if(gRev > 0x3F){
        bool b;
        bs >> b;
        mRefractEnabled = b;
        bs >> mRefractStrength;
        bs >> mRefractNormalMap;
        if (gRev < 0x41) {
            if(mRefractEnabled) mRefractStrength *= 0.15f;
            else mRefractStrength = 0;
        } 
    }
END_LOADS

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
                unkb4p1 = 0;
            }
            return ret;
        }
    }
    SYNC_PROP_MODIFY_ALT(color, mColor, unkb4p1 = 0)
    SYNC_PROP_MODIFY(alpha, mColor.alpha, unkb4p1 = 0)
    {
        static Symbol _s("use_environ");
        bool bit = mUseEnviron;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mUseEnviron = bit;
            if(!(_op & (kPropSize|kPropGet))){
                unkb4p1 = 0;
            }
            return ret;
        }
    }
    {
        static Symbol _s("blend");
        Blend bit = mBlend;
        if(sym == _s){
            bool ret = PropSync((int&)bit, _val, _prop, _i + 1, _op);
            mBlend = bit;
            if(!(_op & (kPropSize|kPropGet))){
                unkb4p1 = 0;
            }
            return ret;
        }
    }
    {
        static Symbol _s("z_mode");
        int bit = unkb0p2;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            unkb0p2 = bit;
            if(!(_op & (kPropSize|kPropGet))){
                unkb4p1 = 0;
            }
            return ret;
        }
    }
END_PROPSYNCS
#pragma pop