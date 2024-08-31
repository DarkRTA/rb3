#include "world/Spotlight.h"
#include "rndobj/Mat.h"
#include "rndobj/Flare.h"
#include "rndobj/Lit.h"
#include "rndobj/Mesh.h"
#include "rndobj/Group.h"
#include "world/SpotlightDrawer.h"
#include "world/LightPreset.h"
#include "math/Rot.h"
#include "utl/Symbols.h"

RndEnviron* Spotlight::sEnviron;

INIT_REVS(Spotlight)

const Vector2& Spotlight::BeamDef::NGRadii() const {
    float exp = mExpand;
    float f1 = mTopRadius * exp;
    float f2 = mBottomRadius * exp;
    if(!mIsCone){
        f2 = f2 * -(mBottomSideBorder * 0.7f - 1.0f);
        f1 = f1 * -(mTopSideBorder * 0.7f - 1.0f);
    }
    return Vector2(f1, f2);
}

void Spotlight::Init(){
    Register();
    sEnviron = Hmx::Object::New<RndEnviron>();
    BuildBoard();
}

Spotlight::Spotlight() : mDiscMat(this, 0), mFlare(Hmx::Object::New<RndFlare>()), mFlareOffset(0.0f), mSpotScale(30.0f), mSpotHeight(0.25f), mColor(-1), mIntensity(1.0f),
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
    if(gRev > 9) bs >> mIntensity;
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

void Spotlight::Replace(Hmx::Object* from, Hmx::Object* to){
    RndTransformable::Replace(from, to);
    if(mColorOwner == from){
        mColorOwner = dynamic_cast<Spotlight*>(to);
    }
    if(!mColorOwner){
        mColorOwner = this;
    }
}

SAVE_OBJ(Spotlight, 0x16D)

void Spotlight::BeamDef::Load(BinStream& bs){
    bs >> mIsCone;
    bs >> mLength;
    bs >> mBottomRadius;
    bs >> mTopRadius;
    bs >> mTopSideBorder;
    bs >> mBottomSideBorder;
    bs >> mBottomBorder;
    bs >> mMat;
    if(gRev == 0x12){
        char buf[0x80];
        bs.ReadString(buf, 0x80);
    }
    bs >> mOffset;
    if(gRev < 10){
        Hmx::Color col; bs >> col;
    }
    bs >> mTargetOffset;
    if(gRev > 0x14){
        bs >> mBrighten;
        bs >> mXSection;
    }
    if(gRev > 0x17) bs >> mExpand;
    if(gRev > 0x1A) bs >> mShape;
    if(gRev > 0x18) bs >> mCutouts;
    if(gRev > 0x1F){
        bs >> mNumSections;
        bs >> mNumSegments;
    }
}

BEGIN_COPYS(Spotlight)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndTransformable)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(Spotlight)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            mFlare->Copy(this, kCopyDeep);
            COPY_MEMBER(mFlareOffset)
            COPY_MEMBER(mLightCanMesh)
            COPY_MEMBER(mTarget)
            COPY_MEMBER(mSpotTarget)
            COPY_MEMBER(mSpotScale)
            COPY_MEMBER(mSpotHeight)
            // ...
            COPY_MEMBER(mDiscMat)
            COPY_MEMBER(mDampingConstant)
            COPY_MEMBER(mLensSize)
            COPY_MEMBER(mLensOffset)
            COPY_MEMBER(mLensMaterial)
            COPY_MEMBER(mLightCanOffset)
            COPY_MEMBER(mLightCanSort)
            COPY_MEMBER(mFlareEnabled)
            COPY_MEMBER(mFlareVisibilityTest)
            UpdateFlare();
            COPY_MEMBER(mTargetShadow)
            COPY_MEMBER(mAnimateColorFromPreset)
            COPY_MEMBER(mAnimateOrientationFromPreset)
            COPY_MEMBER(mAdditionalObjects)
            COPY_MEMBER(mSlaves)
            COPY_MEMBER(mBeam.mIsCone)
            COPY_MEMBER(mBeam.mLength)
            COPY_MEMBER(mBeam.mBottomRadius)
            COPY_MEMBER(mBeam.mTopRadius)
            COPY_MEMBER(mBeam.mTopSideBorder)
            COPY_MEMBER(mBeam.mBottomSideBorder)
            COPY_MEMBER(mBeam.mBottomBorder)
            COPY_MEMBER(mBeam.mMat)
            COPY_MEMBER(mBeam.mTargetOffset)
            COPY_MEMBER(mBeam.mBrighten)
            COPY_MEMBER(mBeam.mExpand)
            COPY_MEMBER(mBeam.mShape)
            COPY_MEMBER(mBeam.mXSection)
            COPY_MEMBER(mBeam.mCutouts)
            COPY_MEMBER(mBeam.mOffset)
            COPY_MEMBER(mBeam.mNumSections)
            COPY_MEMBER(mBeam.mNumSegments)
            if(c->mBeam.mBeam){
                mBeam.mBeam = Hmx::Object::New<RndMesh>();
                mBeam.mBeam->Copy(c->mBeam.mBeam, kCopyDeep);
            }
        }
    END_COPYING_MEMBERS
END_COPYS

void Spotlight::ListDrawChildren(std::list<RndDrawable*>& draws){
    if(mLightCanMesh) draws.push_back(mLightCanMesh);
    for(ObjPtrList<RndDrawable, ObjectDir>::iterator it = mAdditionalObjects.begin(); it != mAdditionalObjects.end(); ++it){
        draws.push_back(*it);
    }
}

RndDrawable* Spotlight::CollideShowing(const Segment& s, float& f, Plane& pl){
    Hmx::Matrix3 m50;
    m50.Identity();
    Hmx::Matrix3 m74(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f));
    if(mLightCanMesh){
        mLightCanMesh->SetWorldXfm(mLightCanXfm);
        bool oldshowing = mLightCanMesh->Showing();
        mLightCanMesh->SetShowing(true);
        bool coll = mLightCanMesh->Collide(s, f, pl);
        mLightCanMesh->SetShowing(oldshowing);
        if(coll) return this;
    }
    return 0;
}

int Spotlight::CollidePlane(const Plane& pl){
    Hmx::Matrix3 m40;
    m40.Identity();
    Hmx::Matrix3 m64(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f));
    if(mLightCanMesh){
        mLightCanMesh->SetWorldXfm(mLightCanXfm);
        bool oldshowing = mLightCanMesh->Showing();
        mLightCanMesh->SetShowing(true);
        int coll = mLightCanMesh->CollidePlane(pl);
        mLightCanMesh->SetShowing(oldshowing);
        if(coll) return coll;
    }
    return -1;
}

void Spotlight::CloseSlaves(){
    for(ObjPtrList<RndLight, ObjectDir>::iterator it = mSlaves.begin(); it != mSlaves.end(); ++it){
        RndLight* lit = *it;
        if(lit) lit->SetShadowOverride(0);
    }
}

void Spotlight::UpdateSlaves(){
    if(!mSlaves.empty()){
        for(ObjPtrList<RndLight, ObjectDir>::iterator it = mSlaves.begin(); it != mSlaves.end(); ++it){
            RndLight* lit = *it;
            Transform tf40(WorldXfm());
            if(lit->TransParent()){
                Transform tf70;
                Invert(lit->TransParent()->WorldXfm(), tf70);
                Multiply(WorldXfm(), tf70, tf40);
            }
            lit->SetLocalXfm(tf40);
            lit->SetShadowOverride(&mBeam.mCutouts);
            lit->SetShowing(Showing());
        }
    }
}

void Spotlight::CalculateDirection(RndTransformable* trans, Hmx::Matrix3& mtx){
    Vector3 v20;
    Subtract(trans->WorldXfm().v, WorldXfm().v, v20);
    Vector3 v2c;
    Cross(v20, Vector3(1.0f, 0.0f, 0.0f), v2c);
    Normalize(v2c, v2c);
    MakeRotMatrix(v20, v2c, mtx);
}

void Spotlight::UpdateSphere(){
    Sphere s48;
    MakeWorldSphere(s48, true);
    Transform tf38;
    FastInvert(WorldXfm(), tf38);
    Multiply(s48, tf38, s48);
    SetSphere(s48);
}

bool Spotlight::MakeWorldSphere(Sphere& s, bool b){
    if(b){
        s.Zero();
        if(mBeam.mBeam){
            Sphere s28;
            if(mBeam.mBeam->MakeWorldSphere(s28, true)){
                s.GrowToContain(s28);
            }
        }
        if(DoFloorSpot()){
            Sphere s38;
            sDiskMesh->SetWorldXfm(mFloorSpotXfm);
            if(sDiskMesh->MakeWorldSphere(s38, true)){
                s.GrowToContain(s38);
            }
        }
        if(mFlare){
            Sphere s48;
            if(mFlare->MakeWorldSphere(s48, true)){
                s.GrowToContain(s48);
            }
        }
        if(mLightCanMesh){
            Sphere s58;
            mLightCanMesh->SetWorldXfm(mLightCanXfm);
            if(mLightCanMesh->MakeWorldSphere(s58, true)){
                s.GrowToContain(s58);
            }
        }
        return true;
    }
    else {
        if(&mSphere){ // fix this line
            Multiply(mSphere, WorldXfm(), s);
            return true;
        }
        else return false;
    }
}

void Spotlight::SetColorIntensity(const Hmx::Color& col, float f){
    Hmx::Color c20(col);
    Multiply(c20, f, c20);
    Hmx::Color c30(Color());
    Multiply(c30, Intensity(), c30);
    mColorOwner->mColor = Hmx::Color32(col.Pack());
    mColorOwner->mIntensity = f;
}

void Spotlight::SetColor(int packed){
    Hmx::Color color;
    color.Unpack(packed);
    color.alpha = 1.0f;
    SetColorIntensity(color, Intensity());
}

void Spotlight::SetIntensity(float f){
    SetColorIntensity(Hmx::Color(Color()), f);
}

void Spotlight::UpdateBounds(){
    UpdateTransforms();
    UpdateSphere();
}

void Spotlight::UpdateTransforms(){
    START_AUTO_TIMER("spotlight_xfm");
    Transform& thetf = WorldXfm();
    mLightCanXfm = thetf;
    Vector3 vcc(mLightCanXfm.m.y);
    vcc *= mLightCanOffset;
    ::Add(mLightCanXfm.v, vcc, mLightCanXfm.v);
    static Hmx::Matrix3 ident(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    static Hmx::Matrix3 rot(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f));
    if(mLensMaterial){
        Vector3 vd8(0.0f, mLensOffset, 0.0f);
        Multiply(vd8, thetf.m, vd8);
        ::Add(vd8, thetf.v, vd8);
        Hmx::Matrix3 m48;
        m48.Set(Vector3(-mLensSize, 0.0f, 0.0f), Vector3(0.0f, 0.0f, mLensSize), Vector3(0.0f, mLensSize, 0.0f));
        Multiply(m48, thetf.m, m48);
        mLensXfm = Transform(m48, vd8);
    }
    if(mBeam.mBeam){
        Vector3 ve4(0.0f, mBeam.mOffset, 0.0f);
        mBeam.mBeam->SetLocalPos(ve4);
        Hmx::Matrix3 m6c(mBeam.mIsCone ? rot : ident);
        Hmx::Matrix3 m90;
        MakeRotMatrix(Vector3(mBeam.mTargetOffset.x * DEG2RAD, 0.0f, mBeam.mTargetOffset.y * DEG2RAD), m90, true);
        Multiply(m6c, m90, m6c);
        mBeam.mBeam->SetLocalRot(m6c);
    }
    if(mFlare && mFlare->GetMat()){
        Vector3 vf0(0.0f, mFlareOffset, 0.0f);
        mFlare->SetLocalPos(vf0);
        mFlare->SetLocalRot(ident);
    }
    UpdateFloorSpotTransform(thetf);
    UpdateSlaves();
}

void Spotlight::CheckFloorSpotTransform(){
    if(DoFloorSpot()){
        if(GetFloorSpotTarget()->WorldXfm().v.z != unk22c){
            UpdateFloorSpotTransform(WorldXfm());
        }
    }
}

void Spotlight::UpdateFloorSpotTransform(const Transform& tf){
    mFloorSpotXfm.Reset();
    if(DoFloorSpot()){
        float f1 = GetFloorSpotTarget()->WorldXfm().v.z;
        Vector3 vac(tf.m.y);
        if(vac.x != 0){
            float absed = std::fabs(((f1 - tf.v.z) / vac.x) / (f1 - tf.v.z));
            vac = tf.m.y;
            float curx = vac.x;
            vac.x = 0;
            Hmx::Matrix3 m70;
            if(curx > -0.9999999f && curx < 0.9999999f)
                MakeRotMatrix(vac, Vector3(0.0f, 0.0f, 1.0f), m70);
            else m70.Identity();
            vac.Set(mSpotScale, mSpotScale * absed, 1.0f);
            Scale(vac, m70, m70);
            float scalar = (f1 + mSpotHeight - tf.v.z) / curx;
            vac = tf.m.y;
            vac *= scalar;
            ::Add(vac, tf.v, vac);
            mFloorSpotXfm = Transform(m70, vac);
        }
        unk22c = f1;
    }
}

void Spotlight::BuildShaft(Spotlight::BeamDef& def){
    if(def.mIsCone) BuildCone(def);
    else BuildBeam(def);
}

Spotlight::BeamDef::BeamDef(Hmx::Object* obj) : mBeam(0), mIsCone(0), mLength(100.0f), mTopRadius(4.0f), mBottomRadius(30.0f), mTopSideBorder(0.1f), mBottomSideBorder(0.3f),
    mBottomBorder(0.5f), mOffset(0.0f), mTargetOffset(0.0f, 0.0f), mBrighten(1.0f), mExpand(1.0f), mShape(0), mNumSections(0), mNumSegments(0),
    mXSection(obj, 0), mCutouts(obj, kObjListNoNull), mMat(obj, 0) {

}

Spotlight::BeamDef::BeamDef(const Spotlight::BeamDef& def) : mBeam(0), mIsCone(def.mIsCone), mLength(def.mLength), mTopRadius(def.mTopRadius), mBottomRadius(def.mBottomRadius),
    mTopSideBorder(def.mTopSideBorder), mBottomSideBorder(def.mBottomSideBorder), mBottomBorder(def.mBottomBorder), mOffset(def.mOffset), mTargetOffset(def.mTargetOffset),
    mBrighten(def.mBrighten), mExpand(def.mExpand), mShape(def.mShape), mNumSections(def.mNumSections), mNumSegments(def.mNumSegments),
    mXSection(def.mXSection.Owner(), def.mXSection.Ptr()), mCutouts(def.mCutouts), mMat(def.mMat.Owner(), def.mMat.Ptr()) {
    if(def.mBeam){
        mBeam = Hmx::Object::New<RndMesh>();
        mBeam->Copy(def.mBeam, kCopyDeep);
    }
}

Spotlight::BeamDef::~BeamDef(){
    RELEASE(mBeam);
}

void Spotlight::BeamDef::OnSetMat(RndMat* mat){
    mMat = mat;
    if(mBeam) mBeam->SetMat(mMat);
}

RndTransformable* Spotlight::ResolveTarget(){
    if(!unk286) return 0;
    if(mTarget) return mTarget;
    return 0;
}

void Spotlight::PropogateToPresets(int i){
    for(ObjDirItr<LightPreset> it(Dir(), false); it != 0; ++it){
        it->SetSpotlight(this, i);
    }
}

BEGIN_HANDLERS(Spotlight)
    HANDLE_ACTION(propogate_targeting_to_presets, PropogateToPresets(2))
    HANDLE_ACTION(propogate_coloring_to_presets, PropogateToPresets(1))
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x71D)
END_HANDLERS

BEGIN_PROPSYNCS(Spotlight)
    SYNC_PROP_MODIFY(length, mBeam.mLength, Generate())
    SYNC_PROP_MODIFY(top_radius, mBeam.mTopRadius, Generate())
    SYNC_PROP_MODIFY(bottom_radius, mBeam.mBottomRadius, Generate())
    SYNC_PROP_MODIFY(top_side_border, mBeam.mTopSideBorder, Generate())
    SYNC_PROP_MODIFY(bottom_side_border, mBeam.mBottomSideBorder, Generate())
    SYNC_PROP_MODIFY(bottom_border, mBeam.mBottomBorder, Generate())
    SYNC_PROP_SET(material, mBeam.mMat, mBeam.OnSetMat(_val.Obj<RndMat>(0)))
    SYNC_PROP_MODIFY(offset, mBeam.mOffset, Generate())
    SYNC_PROP_MODIFY_ALT(angle_offset, mBeam.mTargetOffset, Generate())
    SYNC_PROP_MODIFY(is_cone, mBeam.mIsCone, Generate())
    SYNC_PROP(brighten, mBeam.mBrighten)
    SYNC_PROP_MODIFY(expand, mBeam.mExpand, Generate())
    SYNC_PROP_MODIFY(shape, mBeam.mShape, Generate())
    SYNC_PROP(xsection, mBeam.mXSection)
    SYNC_PROP(cutouts, mBeam.mCutouts)
    SYNC_PROP_MODIFY(sections, mBeam.mNumSections, Generate())
    SYNC_PROP_MODIFY(segments, mBeam.mNumSegments, Generate())
    SYNC_PROP_MODIFY_ALT(light_can, mLightCanMesh, UpdateBounds())
    SYNC_PROP_MODIFY(light_can_offset, mLightCanOffset, UpdateBounds())
    SYNC_PROP(light_can_sort, mLightCanSort)
    SYNC_PROP_MODIFY_ALT(target, mTarget, UpdateTransforms())
    SYNC_PROP(target_shadow, mTargetShadow)
    SYNC_PROP_SET(flare_material, mFlare->GetMat(), mFlare->SetMat(_val.Obj<RndMat>(0)))
    SYNC_PROP(flare_size, mFlare->mSizes)
    SYNC_PROP(flare_range, mFlare->mRange)
    SYNC_PROP_SET(flare_steps, mFlare->GetSteps(), mFlare->SetSteps(_val.Int(0)))
    SYNC_PROP_MODIFY(flare_offset, mFlareOffset, UpdateBounds())
    SYNC_PROP_MODIFY(flare_enabled, mFlareEnabled, UpdateFlare())
    SYNC_PROP_SET(flare_visibility_test, mFlareVisibilityTest == 0, SetFlareIsBillboard(_val.Int(0) == 0))
    SYNC_PROP_MODIFY_ALT(spot_target, mSpotTarget, UpdateBounds())
    SYNC_PROP_MODIFY(spot_scale, mSpotScale, UpdateBounds())
    SYNC_PROP_MODIFY(spot_height, mSpotHeight, UpdateBounds())
    SYNC_PROP_MODIFY_ALT(spot_material, mDiscMat, UpdateBounds())
    SYNC_PROP_SET(color, Color().Opaque(), SetColor(_val.Int(0))) // there are color32 inlines here - fix!
    SYNC_PROP_SET(intensity, Intensity(), SetIntensity(_val.Float(0)))
    SYNC_PROP(color_owner, mColorOwner)
    SYNC_PROP(damping_constant, mDampingConstant)
    SYNC_PROP_MODIFY(lens_size, mLensSize, UpdateBounds())
    SYNC_PROP_MODIFY(lens_offset, mLensOffset, UpdateBounds())
    SYNC_PROP_MODIFY_ALT(lens_material, mLensMaterial, UpdateBounds())
    SYNC_PROP(additional_objects, mAdditionalObjects)
    SYNC_PROP(slaves, mSlaves)
    SYNC_PROP(animate_orientation_from_preset, mAnimateOrientationFromPreset)
    SYNC_PROP(animate_color_from_preset, mAnimateColorFromPreset)
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS