#include "world/Spotlight.h"
#include "rndobj/Mat.h"
#include "rndobj/Flare.h"
#include "rndobj/Lit.h"
#include "rndobj/Mesh.h"
#include "rndobj/Group.h"
#include "world/SpotlightDrawer.h"

RndEnviron* Spotlight::sEnviron;

INIT_REVS(Spotlight)

void Spotlight::Init(){
    Register();
    sEnviron = Hmx::Object::New<RndEnviron>();
    BuildBoard();
}

Spotlight::Spotlight() : mDiscMat(this, 0), mFlare(Hmx::Object::New<RndFlare>()), mFlareOffset(0.0f), mSpotScale(30.0f), mSpotHeight(0.25f), unk138(1.0f),
    mColorOwner(this, this), mLensSize(0.0f), mLensOffset(0.0f), mLensMaterial(this, 0), mBeam(this), mSlaves(this, kObjListNoNull), mLightCanOffset(0.0f),
    mLightCanMesh(this, 0), mTarget(this, 0), mSpotTarget(this, 0), unk22c(-1e+33f), mDampingConstant(1.0f), mAdditionalObjects(this, kObjListNoNull),
    mFlareEnabled(1), mFlareVisibilityTest(1), unk286(1), mTargetShadow(0), mLightCanSort(0), unk289(1), mAnimateColorFromPreset(1), mAnimateOrientationFromPreset(1), unk28c(0) {
    mFlare->SetTransParent(this, false);
    mFloorSpotXfm.Reset();
    mLensXfm.Reset();
    mLightCanXfm.Reset();
    unk230.Identity();
    unk268.Zero();
    unk274.Reset();
    SetOrder(-1000.0f);
}

Spotlight::~Spotlight(){
    CloseSlaves();
    SpotlightDrawer::RemoveFromLists(this);
    RELEASE(mFlare);
}

void Spotlight::SetFlareEnabled(bool b){
    mFlareEnabled = b;
    UpdateFlare();
}

void Spotlight::SetFlareIsBillboard(bool b){
    mFlareVisibilityTest = b;
    UpdateFlare();
}

void Spotlight::UpdateFlare(){
    if(!mFlareEnabled){
        mFlare->SetVisible(false);
        mFlare->SetPointTest(false);
    }
    else if(mFlareVisibilityTest){
        mFlare->SetVisible(true);
        mFlare->SetPointTest(false);
    }
    else mFlare->SetPointTest(true);
}

void Spotlight::ConvertGroupToMesh(RndGroup* grp){
    if(grp){
        int count = 0;
        std::vector<RndDrawable*>::iterator it = grp->mDraws.begin();
        std::vector<RndDrawable*>::iterator itEnd = grp->mDraws.end();
        for(; it != itEnd; it++){
            RndMesh* cur = dynamic_cast<RndMesh*>(*it);
            if(cur){
                count++;
                if(mLightCanMesh) mLightCanMesh = cur;
            }
        }
        if(count > 1){
            MILO_WARN("Multiple meshes (%d) found converting light can group %s to mesh", count, grp->Name());
        }
    }
}

BEGIN_LOADS(Spotlight)
    LOAD_REVS(bs)
    ASSERT_REVS(0x21, 0)
    if(gRev < 9){
        MILO_FAIL("Unsupported spotlight version");
        return;
    }
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndDrawable)
    LOAD_SUPERCLASS(RndTransformable)
    bs >> mSpotScale;
    bs >> mSpotHeight;
    if(gRev > 0x16) bs >> mBeam;
    else {
        ObjVector<BeamDef> beams(this);
        bs >> beams;
        MILO_ASSERT(beams.size() <= 1, 0xC9);
        if(beams.size() != 0) mBeam = beams[0];
        else mBeam.mLength = 0;
    }
    if(gRev > 0x15) bs >> mLightCanMesh;
    else {
        ObjPtr<RndGroup, ObjectDir> grpPtr(this, 0);
        bs >> grpPtr;
        ConvertGroupToMesh(grpPtr);
    }
    if(!mTarget.Load(bs, false, 0)) unk286 = false;
    if(gRev > 0x1C) bs >> mSpotTarget;
    bs >> mLightCanOffset;
    if(gRev > 0x1E) bs >> mLightCanSort;
    bs >> mColor;
    mColor.SetAlpha(1.0f);
    if(gRev > 9) bs >> unk138;
    bs >> mDiscMat;
    if(gRev == 0x12){
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        if(!mDiscMat && buf[0] != '\0'){
            mDiscMat = LookupOrCreateMat(buf, Dir());
        }
    }
    bs >> mDampingConstant;
    if(gRev < 0x21){
        Symbol sym; bs >> sym;
    }
    if(gRev > 10){
        ObjPtr<RndMat, ObjectDir> matPtr(this, 0);
        bs >> matPtr;
        mFlare->SetMat(matPtr);
        if(gRev > 0x11 && gRev < 0x13){
            char buf[0x80];
            bs.ReadString(buf, 0x80);
            if(!matPtr && buf[0] != '\0'){
                matPtr = LookupOrCreateMat(buf, Dir());
                mFlare->SetMat(matPtr);
            }
        }
        bs >> mFlare->mSizes;
        bs >> mFlare->mRange;
        int steps;
        bs >> steps;
        mFlare->SetSteps(steps);
        bs >> mFlareOffset;
    }
    if(gRev > 0xD) bs >> mFlareEnabled;
    if(gRev > 0xE) bs >> mFlareVisibilityTest;
    UpdateFlare();
    if(gRev > 0xB){
        bs >> mLensSize;
        bs >> mLensOffset;
        bs >> mLensMaterial;
    }
    if(gRev == 0x12){
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        if(!mLensMaterial && buf[0] != '\0'){
            mLensMaterial = LookupOrCreateMat(buf, Dir());
        }
    }
    if(gRev > 0xC) bs >> mAdditionalObjects;
    if(gRev > 0x1B) bs >> mSlaves;
    if(gRev > 0xF) bs >> mTargetShadow;
    if(gRev > 0x19){
        bs >> mAnimateColorFromPreset;
        bs >> mAnimateOrientationFromPreset;
    }
    else if(gRev > 0x10){
        bs >> mAnimateColorFromPreset;
        mAnimateOrientationFromPreset = mAnimateColorFromPreset;
    }
    if(gRev > 0x1D){
        bs >> mColorOwner;
        if(!mColorOwner) mColorOwner = this;
    }
    Generate();
END_LOADS

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