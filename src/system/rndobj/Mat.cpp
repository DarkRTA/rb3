#include "rndobj/Mat.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
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
    unkb0p1 = bs_b0_1;
    bool bs_a9_3; bs >> bs_a9_3;
    mAlphaCut = bs_a9_3;
    if(gRev > 0x25) bs >> mAlphaThresh;
    bool bs_a9_4; bs >> bs_a9_4;
    mAlphaWrite = bs_a9_4;
    int bs_ac_2; bs >> bs_ac_2;
    mTexGen = (TexGen)bs_ac_2;
    int bs_b0_0; bs >> bs_b0_0;
    unkb0p0 = bs_b0_0;

    bs >> mTexXfm;
    bs >> mDiffuseTex;
    bs >> mNextPass;
    bool bs_ac_3; bs >> bs_ac_3;
    unkb4p1 = 3;
    unkacp2 = bs_ac_3; // wrong

    Hmx::Color loc_color;
    bs >> mEmissiveMultiplier;
    bs >> loc_color;
    {
        MemDoTempAllocations(true, false);
        ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
        bs >> texPtr;
    }
    bs >> mEmissiveMap;
    {
        MemDoTempAllocations(true, false);
        ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
        bs >> texPtr;
    }
    if(gRev < 0x33){
        ObjPtr<RndTex, ObjectDir> texPtr(this, 0);
        bs >> texPtr;
    }

    bs >> mRefractNormalMap;
    if (gRev < 0x41) {
        mRefractStrength *= 0.15f;
    } else mRefractStrength = 0;
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