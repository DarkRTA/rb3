#include "rndobj/Mat.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"

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
    Hmx::Object::Load(bs);
    int x; bs >> x;
    mBlend = (Blend)x;
    bs >> mColor;
    bool y; bs >> y;
    mColorAdjust = y;


    bs >> mRefractNormalMap;
    if (gRev < 0x41) {
        mRefractStrength *= 0.15;
    } else mRefractStrength = 0;
END_LOADS


BEGIN_PROPSYNCS(RndMat)
    if (sym == "intensify") { bool x = mIntensify; return PropSync(x, _val, _prop, _i + 1, _op); }
END_PROPSYNCS
