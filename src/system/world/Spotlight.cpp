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

Spotlight::BeamDef::BeamDef(Hmx::Object* obj) : mBeam(0), mIsCone(0), mLength(100.0f), mTopRadius(4.0f), mRadius(30.0f), mTopSideBorder(0.1f), mBottomSideBorder(0.3f),
    mBottomBorder(0.5f), mOffset(0.0f), mTargetOffset(0.0f, 0.0f), mBrighten(1.0f), mExpand(1.0f), mShape(0), mNumSections(0), mNumSegments(0),
    mXSection(obj, 0), mCutouts(obj, kObjListNoNull), mMat(obj, 0) {

}

Spotlight::BeamDef::~BeamDef(){
    delete mBeam;
    mBeam = 0;
}

void Spotlight::BeamDef::OnSetMat(RndMat* mat){
    mMat = mat;
    if(mBeam) mBeam->SetMat(mMat);
}