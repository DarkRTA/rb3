#include "world/CameraShot.h"
#include "world/Spotlight.h"
#include "world/Crowd.h"
#include "rndobj/Trans.h"
#include "rndobj/TransProxy.h"
#include "rndobj/Utl.h"
#include "obj/PropSync_p.h"
#include "world/Dir.h"
#include "math/Interp.h"
#include "math/MathFuncs.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

Hmx::Object* CamShot::sAnimTarget;

INIT_REVS(CamShot);

CamShot::CamShot() : mKeyFrames(this), mLoopKeyframe(0), mNear(1.0f), mFar(1000.0f), mFilter(0.9f), mClampHeight(-1.0f), mCategory(), 
    mAnims(this, kObjListNoNull), mPath(this, 0), mDrawOverrides(this, kObjListNoNull), mPathFrame(-1.0f), mPlatformOnly(0),
    mPostProcOverrides(this, kObjListNoNull), mCrowds(this), mGlowSpot(this, 0), unkc4(0.0f, 0.0f, 0.0f), unkd0(0.0f, 0.0f, 0.0f),
    unkdc(0.0f, 0.0f, 0.0f), unke8(0.0f, 0.0f, 0.0f), unkf4(0.0f, 0.0f, 0.0f), unk100(0.0f, 0.0f, 0.0f), unk10c(0), unk110(0),
    mDuration(0.0f), mDisabled(0), mFlags(0), mLooping(1), mUseDepthOfField(0), mPS3PerPixel(0) {

}

CamShot::~CamShot(){

}

void CamShot::Init(){
    Register();
    sAnimTarget = Hmx::Object::New<Hmx::Object>();
}

void CamShot::ListAnimChildren(std::list<RndAnimatable*>& animlist) const {
    for(ObjPtrList<RndAnimatable, ObjectDir>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        animlist.push_back(*it);
    }
}

Hmx::Object* CamShot::AnimTarget(){ return sAnimTarget; }

void CamShot::StartAnim(){
    START_AUTO_TIMER("cam_switch");
    HandleType(start_shot_msg);
    WorldDir* wdir = dynamic_cast<WorldDir*>(Dir());
    if(wdir) wdir->SetCrowds(mCrowds);
    unk10c = 0;
    unk110 = 0;
    unkc4.Zero();
    unkdc.Zero();
    unkf4.Zero();
    unkd0.Zero();
    unke8.Zero();
    unk100.Zero();
    for(ObjPtrList<RndAnimatable, ObjectDir>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        (*it)->StartAnim();
    }
    for(int i = 0; i != mCrowds.size(); i++){
        mCrowds[i].Set3DCrowd();
    }
}

void CamShot::EndAnim(){
    UnHide();
    HandleType(stop_shot_msg);
    for(ObjPtrList<RndAnimatable, ObjectDir>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        (*it)->EndAnim();
    }
}

void CamShot::DoHide(){
    if(!mHidden){
        unkb4.clear();
        unkbc.clear();
        unkbc.reserve(unk5c.size() + unk6c.size() + 3);
        unkb4.reserve(unk64.size());
        for(std::vector<RndDrawable*>::iterator it = unk5c.begin(); it != unk5c.end(); ++it){
            if((*it)->Showing()){
                (*it)->SetShowing(false);
                unkbc.push_back(*it);
            }
        }
        for(std::vector<RndDrawable*>::iterator it = unk6c.begin(); it != unk6c.end(); ++it){
            if((*it)->Showing()){
                (*it)->SetShowing(false);
                unkbc.push_back(*it);
            }
        }
        mHidden = true;
    }
}

void CamShot::UnHide(){
    if(mHidden){
        for(std::vector<RndDrawable*>::iterator it = unkb4.begin(); it != unkb4.end(); ++it){
            (*it)->SetShowing(false);
        }
        for(std::vector<RndDrawable*>::iterator it = unkbc.begin(); it != unkbc.end(); ++it){
            (*it)->SetShowing(true);
        }
        unkb4.clear();
        unkbc.clear();
        mHidden = false;
    }
}

#pragma push
#pragma pool_data off
RndCam* CamShot::GetCam(){
    RndCam* ret = 0;
    PanelDir* pdir = dynamic_cast<PanelDir*>(Dir());
    if(pdir){
        ret = pdir->mCam;
        if(!ret) MILO_NOTIFY_ONCE("%s: paneldir but no cam", PathName(pdir));
    }
    else {
        MILO_NOTIFY_ONCE("%s: no world, or paneldir so no cam", PathName(this));
    }
    return ret;
}
#pragma pop

void CamShot::SetShotOver(){
    HandleType(shot_over_msg);
    mShotOver = true;
}

bool CamShot::CheckShotStarted(){ return unk120p4; }

bool CamShot::CheckShotOver(float f){
    return !mShotOver && !mLooping && f >= mDuration;
}

#pragma push
#pragma dont_inline on
BEGIN_COPYS(CamShot)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    CREATE_COPY(CamShot)
    BEGIN_COPYING_MEMBERS
        mKeyFrames.clear();
        for(int i = 0; i != c->mKeyFrames.size(); i++){
            mKeyFrames.push_back(CamShotFrame(this, c->mKeyFrames[i]));
        }
        mCrowds.clear();
        for(int i = 0; i != c->mCrowds.size(); i++){
            mCrowds.push_back(CamShotCrowd(this, c->mCrowds[i]));
        }
        COPY_MEMBER(mNear)
        COPY_MEMBER(mFar)
        COPY_MEMBER(mUseDepthOfField)
        COPY_MEMBER(mFilter)
        COPY_MEMBER(mClampHeight)
        COPY_MEMBER(mPath)
        COPY_MEMBER(mPlatformOnly)
        COPY_MEMBER(mCategory)
        COPY_MEMBER(unk5c)
        COPY_MEMBER(unk6c)
        COPY_MEMBER(unk6c)
        COPY_MEMBER(unk64)
        COPY_MEMBER(mLooping)
        COPY_MEMBER(mLoopKeyframe)
        COPY_MEMBER(mGlowSpot)
        COPY_MEMBER(mDrawOverrides)
        COPY_MEMBER(mPostProcOverrides)
        COPY_MEMBER(mPS3PerPixel)
        COPY_MEMBER(mFlags)
        COPY_MEMBER(mAnims)
        CacheFrames();
    END_COPYING_MEMBERS
END_COPYS
#pragma pop

RndTransformable* LoadSubPart(BinStream& bs, CamShot* shot){
    if(CamShot::gRev < 0x2B){
        int dummy;
        bs >> dummy;
    }
    String str;
    bs >> str;
    Symbol sym;
    bs >> sym;
    if(str.empty()) return 0;
    RndTransformable* foundTrans = dynamic_cast<RndTransformable*>(shot->Dir()->FindObject(str.c_str(), false));
    if(sym.Null()){
        if(foundTrans) return foundTrans;
        TheDebug << MakeString("%s could not find %s, assuming character, attaching to base\n", PathName(shot), str);
    }
    char buf[256];
    strcpy(buf, sym.Str());
    char* buf_ptr = strchr(buf, '.');
    if(buf_ptr) *buf_ptr = '\0';
    else if(buf[0] == '\0'){
        strcpy(buf, "base");
    }
    const char* search = MakeString("%s_%s.tp", str, buf);
    RndTransProxy* proxy = dynamic_cast<RndTransProxy*>(shot->Dir()->FindObject(search, false));
    if(!proxy){
        proxy = Hmx::Object::New<RndTransProxy>();
        proxy->SetName(search, shot->Dir());
        proxy->SetProxy(dynamic_cast<ObjectDir*>(foundTrans));
        proxy->SetPart(sym);
    }
    return proxy;
}

SAVE_OBJ(CamShot, 0x409);

#pragma push
#pragma dont_inline on
BEGIN_LOADS(CamShot)
    LOAD_REVS(bs)
    ASSERT_REVS(0x32, 1)
    bool bitfield_bool;
    bool hidden = mHidden;
    if(hidden) UnHide();
    float somefloat = 0.0f;
    if(gRev != 0){
        LOAD_SUPERCLASS(Hmx::Object)
        LOAD_SUPERCLASS(RndAnimatable)
    }
    if(gRev > 0xC){
        bs >> mKeyFrames;
        bs >> bitfield_bool;
        mLooping = bitfield_bool;
        if(gRev > 0x1E) bs >> mLoopKeyframe;
        else mLoopKeyframe = 0;
        if(gRev < 0x28) bs >> somefloat;
        bs >> mNear;
        bs >> mFar;
        bs >> bitfield_bool;
        mUseDepthOfField = bitfield_bool;
        bs >> mFilter;
        bs >> mClampHeight;
    }
    else {
        mLoopKeyframe = 0;
        mLooping = false;
        float fov1, fov2;
        bs >> fov1;
        bs >> fov2;
        if(gRev < 9){
            fov1 = ConvertFov(fov1, 0.75f);
            fov2 = ConvertFov(fov2, 0.75f);
        }
        Transform tf1;
        Transform tf2;
        bs >> tf1;
        bs >> tf2;
        Vector2 vec1;
        Vector2 vec2;
        bs >> vec1;
        bs >> vec2;
        if(gRev < 0x28) bs >> somefloat;
        float fdummy1;
        bool usedof;
        bs >> fdummy1;
        bs >> mNear;
        bs >> mFar;
        bs >> usedof;
        mUseDepthOfField = usedof;
        float someotherfloat = 1.0f;
        if(gRev > 9){
            float newblurdepth;
            float ff, ff2;
            bs >> newblurdepth;
            bs >> ff;
            bs >> ff2;
            someotherfloat = 1.0f - newblurdepth;
        }
        if(gRev < 4){
            bool ratebool;
            bs >> ratebool;
            SetRate((Rate)!ratebool);
        }
        bs >> mFilter;
        if(gRev < 7) mFilter = 0.9f;
        bs >> mClampHeight;
        ObjPtrList<RndTransformable, ObjectDir> pList(this, kObjListNoNull);
        ObjPtr<RndTransformable, ObjectDir> ptr(this, 0);
        int listsize;
        bs >> listsize;
        for(int i = 0; i < listsize; i++){
            RndTransformable* subpart = LoadSubPart(bs, this);
            if(subpart) pList.push_back(subpart);
        }
        ptr = LoadSubPart(bs, this);
        bool somebool = false;
        if(gRev > 10) bs >> somebool;
        CamShotFrame csf1(this);
        CamShotFrame csf2(this);
        if(fdummy1 > 0.0f){
            csf1.mDuration = 0.0f;
            csf1.mBlend = fdummy1;
            csf1.unk10.Set(tf1);
            csf1.mScreenOffset = vec1;
            csf1.SetFieldOfView(fov1);
            csf1.SetBlurDepth(someotherfloat);
            csf1.SetMaxBlur(1.0f);
            csf1.SetMinBlur(0.0f);
            csf1.mFocusBlurMultiplier = 0.0f;
            csf1.mTargets = pList;
            csf1.mParent = ptr;
            mKeyFrames.push_back(csf1);
        }
        csf2.mDuration = 0.0f;
        csf2.mBlend = 0.0f;
        csf2.unk10.Set(tf2);
        csf2.mScreenOffset = vec2;
        csf2.SetFieldOfView(fov2);
        csf2.SetBlurDepth(someotherfloat);
        csf2.SetMaxBlur(1.0f);
        csf2.SetMinBlur(0.0f);
        csf2.mFocusBlurMultiplier = 0.0f;
        csf2.mTargets = pList;
        csf2.mParent = ptr;
        mKeyFrames.push_back(csf2);
    }
    bs >> mPath;
    if(gRev - 2 <= 42U){
        float f2b;
        bs >> f2b;
    }
    if(gRev > 2){
        bs >> mCategory;
        if(gRev < 0x26){
            float f26;
            bs >> f26;
        }
    }
    if(gRev > 0x22) bs >> mPlatformOnly;
    else if(gRev > 0x21){
        int state;
        bs >> state;
        if(state == 1) mPlatformOnly = 2;
        else if(state == 2) mPlatformOnly = 4;
        else mPlatformOnly = 0;
    }
    if(gRev < 1) LOAD_SUPERCLASS(RndAnimatable)
    CamShotCrowd csc(this);
    if(gRev - 5 < 0x25U){
        bs >> csc.unk10;
    }
    int loc240 = -1;
    if(gRev - 8 < 0x22U){
        bs >> loc240;
    }
    if(gRev > 5){
        unk6c.clear();
        unk6c.clear();
        unk5c.clear();
        if(gRev <= 0x2F || (bs.Cached() && gRev < 0x32)){
            LoadDrawables(bs, unk5c, Dir());
        }
        else {
            LoadDrawables(bs, unk5c, Dir());
            LoadDrawables(bs, unk6c, Dir());
        }
    }
    if(gRev > 0x1B) LoadDrawables(bs, unk64, Dir());
    if(gRev <= 0xB){
        DataNode* prop = Property("hide_crowd", false);
        if(!prop || prop->Int(0) == 0){
            ObjDirItr<WorldCrowd> iter(Dir(), true);
            if(iter){
                csc.mCrowd = iter;
            }
        }
    }
    else if(gRev < 0x2A) bs >> csc.mCrowd;
    if(gRev - 0x21 < 9) bs >> csc.mCrowdRotate;
    if(gRev - 8 < 0x22){
        if(csc.mCrowd){
            if(loc240 != csc.mCrowd->GetModifyStamp()){
                csc.unk10.clear();
                goto next;
            }
        }
        if(!csc.mCrowd && loc240 != -1) csc.unk10.clear();
    }
next:
    if(gRev == 0xE){
        float f244, f248, f24c;
        bs >> f244;
        bs >> f248;
        bs >> f24c;
    }
    if(gRev - 0x10 < 2){
        float f250, f254;
        bs >> f250;
        bs >> f254;
        for(int i = 0; i != mKeyFrames.size(); i++){
            mKeyFrames[i].mShakeNoiseAmp = f254;
            mKeyFrames[i].mShakeNoiseFreq = f250;
        }
    }
    if(gRev > 0x10 && gRev < 0x12){
        Vector2 v210;
        bs >> v210;
        for(int i = 0; i < mKeyFrames.size(); i++){
            mKeyFrames[i].SetMaxAngularOffset(v210);
        }
    }
    if(gRev > 0x13) bs >> mGlowSpot;
    if(gRev > 0x1D) bs >> mDrawOverrides;
    if(gRev > 0x1F) bs >> mPostProcOverrides;
    if(gRev > 0x23 && gRev - 0x2F > 1){
        bs >> bitfield_bool;
        mPS3PerPixel = bitfield_bool;
    }
    if(gRev > 0x24) bs >> mFlags;
    Symbol s258;
    if(gRev - 0x28 < 3) bs >> s258;
    if(gRev < 0x2A){
        if(csc.mCrowd) mCrowds.push_back(csc);
    }
    else bs >> mCrowds;
    if(gRev > 0x2A) bs >> mAnims;
    if(gAltRev != 0) bs >> unk74;
    if(!s258.Null()){
        mAnims.push_back(Dir()->Find<RndAnimatable>(s258.Str(), false));
    }
    CacheFrames();
    if(hidden) DoHide();
END_LOADS
#pragma pop

float CamShot::GetDurationSeconds() const {
    if(Units() == kTaskBeats){
        return 0.0f;
    }
    else {
        MILO_ASSERT(Units() == kTaskSeconds, 0x613);
        return mDuration / 30.0f;
    }
}

void CamShot::Disable(bool b, int i){
    if(b) mDisabled |= i;
    else mDisabled &= ~i;
}

CamShotFrame::CamShotFrame(Hmx::Object* o) : mDuration(0), mBlend(0), mBlendEase(0), unkc(-1.0f), mShakeNoiseAmp(0), mShakeNoiseFreq(0), mFocusBlurMultiplier(0),
    mTargets(o, kObjListNoNull), unk68(dynamic_cast<CamShot*>(o)), mParent(o, 0), mFocusTarget(o, 0),
    unk85(0), mMaxBlur(0xFF), mMinBlur(0),
    mBlendEaseMode(0), unk8bp1(0), unk8bp0(0) {
    mMaxAngularOffsetY = 0;
    mMaxAngularOffsetX = 0;
    SetBlurDepth(0.34999999f);
    SetFieldOfView(1.2217305f);
    unk10.Reset();
    mScreenOffset.Zero();
    unk34.x = 1e+30f;
}

#pragma push
#pragma dont_inline on
void CamShotFrame::Interp(const CamShotFrame& frame, float f1, float f2, RndCam* cam){
    float d11 = f1;
    float fvar1 = 0;
    if(mBlendEase){
        float fvar2 = 1.0f;
        if(mBlendEaseMode){
            switch(mBlendEaseMode){
                case 1: fvar2 = 2.0f; break;
                case 2: fvar1 = -1.0f; break;
                default:
                    MILO_WARN("Invalid mBlendEaseMode: %d\n", mBlendEaseMode);
                    break;
            }
        }
        ATanInterpolator aint(fvar1, fvar2, fvar1, fvar2, mBlendEase);
        d11 = aint.Eval(f1);
    }
    float interp1 = ::Interp(FieldOfView(), frame.FieldOfView(), d11);
    float interp2 = ::Interp(cam->YFov(), interp1, f2);
    cam->SetFrustum(unk68->mNear, unk68->mFar, interp2, 1.0f);
    bool hasTarget = HasTargets();
    bool thasTarget = frame.HasTargets();
    bool sameTargets = SameTargets(frame);
    Transform tfd0;
    BuildTransform(cam, tfd0, !sameTargets);
    Transform tf100;
    BuildTransform(cam, tf100, !sameTargets);
    Transform tf130;
    ::Interp(tfd0.v, tf100.v, d11, tf130.v);
    ::Interp(tfd0.m, tf100.m, d11, tf130.m);
    float f1fc;
    if(hasTarget || thasTarget){
        if(sameTargets){
            Transform tf160(tf130);
            Transform tf190(tf130);
            if(hasTarget){
                tf160.LookAt(unk34, tf130.m.z);
            }
            if(thasTarget){
                tf190.LookAt(frame.unk34, tf130.m.z);
            }
            ::Interp(tf160.m, tf190.m, d11, tf130.m);
        }
        Vector2 v1e0;
        if(hasTarget && !thasTarget){
            f1fc = Distance(unk34, tf130.v);
            v1e0 = mScreenOffset;
        }
        else if(!hasTarget && thasTarget){
            f1fc = Distance(frame.unk34, tf130.v);
            v1e0 = frame.mScreenOffset;
        }
        else {
            float dist13 = Distance(frame.unk34, tf130.v);
            float dist14 = Distance(unk34, tf130.v);
            ::Interp(dist14, dist13, d11, f1fc);
            ::Interp(mScreenOffset, frame.mScreenOffset, d11, v1e0);
        }
        
        if(sameTargets){
            Vector3 v1c0;
            v1c0.x = (-v1e0.x * f1fc) / cam->LocalProjectXfm().m.x.x;
            v1c0.y = 0.0f;
            v1c0.z = (v1e0.y * f1fc) / cam->LocalProjectXfm().m.z.x;

            Multiply(v1c0, tf130, tf130.v);
        }
    

    }
    float f200;
    ::Interp(ZoomFieldOfView(), frame.ZoomFieldOfView(), d11, f200);
    cam->SetFrustum(unk68->mNear, unk68->mFar, interp2 + f200, 1.0f);
    RndTransformable* focus = mFocusTarget;
    RndTransformable* towardFocus = frame.mFocusTarget;
    bool b10 = false;
    if(unk68->mUseDepthOfField && (focus || hasTarget || towardFocus || thasTarget)){
        b10 = true;
    }
    if(b10){
        float f204;
        float f208;
        ::Interp(BlurDepth(), frame.BlurDepth(), d11, f204);
        float f20c;
        ::Interp(MaxBlur(), frame.MaxBlur(), d11, f20c);
        float f210;
        ::Interp(MinBlur(), frame.MinBlur(), d11, f210);
        ::Interp(mFocusBlurMultiplier, frame.mFocusBlurMultiplier, d11, f208);
        float d9 = 0;
        float d10;
        if(focus){
            d10 = Distance(focus->WorldXfm().v, tf130.v);
        }
        else {
            d10 = d9;
            if(hasTarget) d10 = Distance(unk34, tf130.v);
        }
        if(towardFocus){
            d9 = Distance(towardFocus->WorldXfm().v, tf130.v);
        }
        else {
            if(thasTarget) d9 = Distance(frame.unk34, tf130.v);
        }
        if(!focus && !hasTarget){
            MILO_ASSERT(towardFocus || thasTarget, 0x7D8);
            d10 = d9;
        }
        if(!towardFocus && !thasTarget){
            MILO_ASSERT(focus || hasTarget, 0x7DE);
            d9 = d10;
        }
        float interp9 = ::Interp(d10, d9, d11);
        TheDOFProc->Set(cam, f208 * d9 + d9, f204, f20c, f210);
    }
    else TheDOFProc->UnSet();
    float f214, f218;
    ::Interp(cam->WorldXfm().v, tf130.v, f2, tf130.v);
    ::Interp(cam->WorldXfm().m, tf130.m, f2, tf130.m);
    ::Interp(mShakeNoiseAmp, frame.mShakeNoiseAmp, d11, f214);
    ::Interp(mShakeNoiseFreq, frame.mShakeNoiseFreq, d11, f218);
    Vector2 v1e8;
    ::Interp(MaxAngularOffset(), frame.MaxAngularOffset(), d11, v1e8);
    Vector3 v1cc;
    Vector3 v1d8;
    unk68->Shake(f218, f214, v1e8, v1cc, v1d8);
    Multiply(v1cc, tf130, tf130.v);
    Hmx::Matrix3 m1b4;
    MakeRotMatrix(v1d8, m1b4, true);
    Multiply(tf130.m, m1b4, tf130.m);
    cam->SetLocalXfm(tf130);
}
#pragma pop

void CamShotFrame::UpdateTarget() const {
    // GetCurrentTargetPosition(unk34);
    // if(mParent){
    //     unk44.Set(mParent->WorldXfm());
    // }
}

void CamShotFrame::GetCurrentTargetPosition(Vector3& v) const {
    v.Zero();
    int count = 0;
    for(ObjPtrList<RndTransformable, ObjectDir>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
        RndTransformable* cur = *it;
        if(cur){
            count++;
            Add(v, cur->WorldXfm().v, v);
        }
    }
    if(count > 0) v *= (1.0f / (float)count);
}

bool CamShotFrame::HasTargets() const {
    for(ObjPtrList<RndTransformable, ObjectDir>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
        if(*it) return true;
    }
    return false;
}

DataNode CamShot::OnGetOccluded(DataArray* da){
    return DataNode(0);
}

DataNode CamShot::OnSetAllCrowdChars3D(DataArray* da){
    return DataNode(0);
}

CamShotCrowd::CamShotCrowd(Hmx::Object* o) : mCrowd(o, 0), mCrowdRotate(0), unk18(dynamic_cast<CamShot*>(o)) {}
CamShotCrowd::CamShotCrowd(Hmx::Object* o, const CamShotCrowd& crowd) : mCrowd(crowd.mCrowd),
    mCrowdRotate(crowd.mCrowdRotate), unk10(crowd.unk10), unk18(dynamic_cast<CamShot*>(o)) {}\

void CamShotCrowd::Load(BinStream& bs){
    bs >> mCrowd;
    bs >> mCrowdRotate;
    bs >> unk10;
    int num;
    bs >> num;
    if(!mCrowd || num == mCrowd->unk88) unk10.resize(num);
    else unk10.clear();
}

BEGIN_HANDLERS(CamShot)
    HANDLE(has_targets, OnHasTargets)
    HANDLE(set_pos, OnSetPos)
    HANDLE_EXPR(duration_seconds, GetDurationSeconds())
    HANDLE(set_3d_crowd, OnSetCrowdChars)
    HANDLE(add_3d_crowd, OnAddCrowdChars)
    HANDLE(clear_3d_crowd, OnClearCrowdChars)
    HANDLE_EXPR(gen_hide_list, 0)
    HANDLE_EXPR(clear_hide_list, 0)
    HANDLE(get_occluded, OnGetOccluded)
    HANDLE_EXPR(platform_ok, PlatformOk())
    HANDLE(set_all_to_3D, OnSetAllCrowdChars3D)
    HANDLE(radio, OnRadio)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xC6F)
END_HANDLERS

DataNode CamShot::OnHasTargets(DataArray* da){
    return DataNode(mKeyFrames[da->Int(2)].HasTargets());
}

DataNode CamShot::OnSetPos(DataArray* da){
    int idx = da->Int(2);
    return DataNode(SetPos(mKeyFrames[idx], RndCam::Current()));
}

DataNode CamShot::OnClearCrowdChars(DataArray* da){
    int idx = da->Int(2);
    MILO_ASSERT(idx < mCrowds.size(), 0xC82);
    mCrowds[idx].ClearCrowdChars();
    return DataNode(0);
}

DataNode CamShot::OnAddCrowdChars(DataArray* da){
    int idx = da->Int(2);
    MILO_ASSERT(idx < mCrowds.size(), 0xC8A);
    mCrowds[idx].AddCrowdChars();
    return DataNode(0);
}

DataNode CamShot::OnSetCrowdChars(DataArray* da){
    int idx = da->Int(2);
    MILO_ASSERT(idx < mCrowds.size(), 0xC92);
    mCrowds[idx].SetCrowdChars();
    return DataNode(0);
}

DataNode CamShot::OnRadio(DataArray* da){
    int i2 = da->Int(2);
    int i3 = da->Int(3);
    if(mFlags & i2){
        mFlags = mFlags & ~i3 | i2;
    }
    return DataNode(0);
}

BEGIN_CUSTOM_PROPSYNC(CamShotCrowd)
    SYNC_PROP_MODIFY_ALT(crowd, o.mCrowd, o.OnCrowdChanged())
    SYNC_PROP(crowd_rotate, o.mCrowdRotate)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(CamShotFrame)
    SYNC_PROP(duration, o.mDuration)
    SYNC_PROP(blend, o.mBlend)
    SYNC_PROP(blend_ease, o.mBlendEase)
    SYNC_PROP_SET(blend_ease_mode, o.mBlendEaseMode, o.mBlendEaseMode = _val.Int(0))
    SYNC_PROP(screen_offset, o.mScreenOffset)
    {
        static Symbol _s("targets");
        if(sym == _s){
            o.OnSyncTargets(o.mTargets, _val, _prop, _i + 1, _op);
            return true;
        }
    }
    {
        static Symbol _s("parent");
        if(sym == _s){
            o.OnSyncParent(o.mParent, _val, _prop, _i + 1, _op);
            return true;
        }
    }
    SYNC_PROP(focal_target, o.mFocusTarget)
    SYNC_PROP_SET(use_parent_rotation, o.unk8bp1, o.unk8bp1 = _val.Int(0))
    SYNC_PROP_SET(parent_first_frame, o.unk8bp0, o.unk8bp0 = _val.Int(0))
    SYNC_PROP_SET(field_of_view, o.FieldOfView() * RAD2DEG, o.SetFieldOfView(_val.Float(0) * DEG2RAD))
END_CUSTOM_PROPSYNC

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(CamShot)
    SYNC_PROP_MODIFY_ALT(keyframes, mKeyFrames, CacheFrames())
    {
        static Symbol _s("looping");
        bool bit = mLooping;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mLooping = bit;
            return ret;
        }
    }
    SYNC_PROP(loop_keyframe, mLoopKeyframe)
    SYNC_PROP_SET(category, mCategory, mCategory = _val.ForceSym(0))
    SYNC_PROP(filter, mFilter)
    SYNC_PROP(clamp_height, mClampHeight)
    SYNC_PROP(near_plane, mNear)
    SYNC_PROP(far_plane, mFar)
    SYNC_PROP_STATIC(duration, mDuration)
    SYNC_PROP_SET(use_depth_of_field, mUseDepthOfField, mUseDepthOfField = _val.Int(0))
    SYNC_PROP(path, mPath)
    SYNC_PROP(path_frame, mPathFrame)
    SYNC_PROP(platform_only, mPlatformOnly)
    SYNC_PROP(draw_overrides, mDrawOverrides)
    SYNC_PROP(postproc_overrides, mPostProcOverrides)
    SYNC_PROP(glow_spot, mGlowSpot)
    SYNC_PROP(crowds, mCrowds)
    {
        static Symbol _s("ps3_per_pixel");
        bool bit = mPS3PerPixel;
        if(sym == _s){
            bool ret = PropSync(bit, _val, _prop, _i + 1, _op);
            mPS3PerPixel = bit;
            return ret;
        }
    }
    SYNC_PROP(flags, mFlags)
    SYNC_PROP_SET(disabled, mDisabled, )
    SYNC_PROP(anims, mAnims)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
#pragma pop