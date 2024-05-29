#include "world/Spotlight.h"
#include "rndobj/Mat.h"
#include "rndobj/Flare.h"
#include "rndobj/Lit.h"
#include "rndobj/Mesh.h"

Spotlight::Spotlight() : mDiscMat(this, 0), mFlare(Hmx::Object::New<RndFlare>()), mFlareOffset(0.0f), mSpotScale(30.0f), mSpotHeight(0.25f), unk134(-1), unk138(1.0f),
    mColorOwner(this, this), mLensSize(0.0f), mLensOffset(0.0f), mLensMaterial(this, 0), mBeam(this), mSlaves(this, kObjListNoNull), mLightCanOffset(0.0f),
    mLightCanMesh(this, 0), mTarget(this, 0), mSpotTarget(this, 0), unk22c(-1e+33f), mDampingConstant(1.0f), mAdditionalObjects(this, kObjListNoNull),
    mFlareEnabled(1), mFlareVisibilityTest(1), unk286(1), mTargetShadow(0), mLightCanSort(0), unk289(1), mAnimateColorFromPreset(1), mAnimateOrientationFromPreset(1), unk28c(0) {
    mFlare->SetTransParent(this, false);
    unkd4.Reset();
    unk104.Reset();
    mLightCanXfm.Reset();
    unk230.Identity();
    unk268.Zero();
    unk274.Reset();
    mOrder = -1000.0f;
}