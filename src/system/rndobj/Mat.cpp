#include "rndobj/Mat.h"

MatShaderOptions::MatShaderOptions() : b(0), i(0x12) {

}

MatPerfSettings::MatPerfSettings() : mRecvProjLights(0), mRecvPointCubeTex(0), mPS3ForceTrilinear(0) {

}

RndMat::RndMat() : mDiffuseTex(this, 0), mAlphaThresh(0), mNextPass(this, 0), mEmissiveMap(this, 0), mRefractStrength(0.0f), mRefractNormalMap(this, 0),
    mIntensify(0), mUseEnviron(1), mPreLit(0), mAlphaCut(0), mAlphaWrite(0), mCull(1), mPerPixelLit(0), mScreenAligned(0),
    mRefractEnabled(0), mPointLights(0), mFog(0), mFadeout(0), mColorAdjust(0), mBlend(kDest), mTexGen(kNone) {
    mEmissiveMultiplier = 1.0f;
    mTexXfm.Reset();
}
