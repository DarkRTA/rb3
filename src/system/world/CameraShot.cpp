#include "world/CameraShot.h"
#include "bandobj/BandCharacter.h"
#include "bandobj/BandWardrobe.h"
#include "decomp.h"
#include "math/Rand.h"
#include "obj/Data.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/System.h"
#include "os/Timer.h"
#include "rndobj/Anim.h"
#include "rndobj/Cam.h"
#include "rndobj/Draw.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/MultiMeshProxy.h"
#include "rndobj/PostProc.h"
#include "stl/_pair.h"
#include "utl/Loader.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "world/Spotlight.h"
#include "world/Crowd.h"
#include "rndobj/Trans.h"
#include "rndobj/TransProxy.h"
#include "rndobj/Utl.h"
#include "obj/PropSync_p.h"
#include "world/Dir.h"
#include "math/Interp.h"
#include "math/Utl.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

bool AutoPrepTarget::sChanging = false;

Hmx::Object* CamShot::sAnimTarget;

INIT_REVS(CamShot);

CamShot::CamShot() : mKeyframes(this), mLoopKeyframe(0), mNear(1.0f), mFar(1000.0f), mFilter(0.9f), mClampHeight(-1.0f), mCategory(),
    mAnims(this, kObjListNoNull), mPath(this), mDrawOverrides(this, kObjListNoNull), mPathFrame(-1.0f), mPlatformOnly(kPlatformNone),
    mPostProcOverrides(this, kObjListNoNull), mCrowds(this), mGlowSpot(this), mLastShakeOffset(0,0,0), mLastShakeAngOffset(0,0,0),
    mLastDesiredShakeOffset(0,0,0), mLastDesiredShakeAngOffset(0,0,0), mShakeVelocity(0,0,0), mShakeAngVelocity(0,0,0), mLastNext(0), mLastPrev(0),
    mDuration(0), mDisabled(0), mFlags(0), mLooping(0), mUseDepthOfField(1), mPS3PerPixel(1), unk120p4(1), mShotOver(0), mHidden(0), unk120p1(0) {

}

CamShot::~CamShot(){

}

void CamShot::Init(){
    Register();
    sAnimTarget = Hmx::Object::New<Hmx::Object>();
}

void CamShot::ListAnimChildren(std::list<RndAnimatable*>& animlist) const {
    for(ObjPtrList<RndAnimatable>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        animlist.push_back(*it);
    }
}

Hmx::Object* CamShot::AnimTarget(){ return sAnimTarget; }

void CamShot::StartAnim(){
    START_AUTO_TIMER("cam_switch");
    HandleType(start_shot_msg);
    WorldDir* wdir = dynamic_cast<WorldDir*>(Dir());
    if(wdir) wdir->SetCrowds(mCrowds);
    unk120p4 = true;
    mShotOver = false;
    mLastNext = nullptr;
    mLastPrev = nullptr;
    mLastShakeOffset.Zero();
    mLastDesiredShakeOffset.Zero();
    mShakeVelocity.Zero();
    mLastShakeAngOffset.Zero();
    mLastDesiredShakeAngOffset.Zero();
    mShakeAngVelocity.Zero();
    for(ObjPtrList<RndAnimatable>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        (*it)->StartAnim();
    }
    for(int i = 0; i != mCrowds.size(); i++){
        mCrowds[i].Set3DCrowd();
    }
}

void CamShot::EndAnim(){
    UnHide();
    HandleType(stop_shot_msg);
    for(ObjPtrList<RndAnimatable>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
        (*it)->EndAnim();
    }
}

void CamShot::DoHide(){
    if(!mHidden){
        mEndHideList.clear();
        mEndShowList.clear();
        mEndShowList.reserve(mHideList.size() + mShowList.size() + 3);
        mEndHideList.reserve(unk64.size());
        for(std::vector<RndDrawable*>::iterator it = mHideList.begin(); it != mHideList.end(); ++it){
            RndDrawable* curDraw = *it;
            if(curDraw->Showing()){
                curDraw->SetShowing(false);
                mEndShowList.push_back(curDraw);
            }
        }
        for(std::vector<RndDrawable*>::iterator it = mShowList.begin(); it != mShowList.end(); ++it){
            RndDrawable* curDraw = *it;
            if(curDraw->Showing()){
                curDraw->SetShowing(false);
                mEndShowList.push_back(curDraw);
            }
        }
        for(std::vector<Symbol>::iterator it = unk74.begin(); it != unk74.end(); ++it){
            BandCharacter* targetChar = TheBandWardrobe->FindTarget(*it);
            if(!targetChar && unk74.size() == 1){
                if(*it == player_bass0){
                    targetChar = TheBandWardrobe->FindTarget(player_keyboard0);
                }
                else if(*it == player_guitar0){
                    targetChar = TheBandWardrobe->FindTarget(player_keyboard0);
                }
                else if(*it == player_keyboard0){
                    targetChar = TheBandWardrobe->FindTarget(player_bass0);
                }

                if(!targetChar){
                    if(*it == player_bass0){
                        targetChar = TheBandWardrobe->FindTarget(player_guitar0);
                    }
                    else if(*it == player_guitar0){
                        targetChar = TheBandWardrobe->FindTarget(player_bass0);
                    }
                    else if(*it == player_keyboard0){
                        targetChar = TheBandWardrobe->FindTarget(player_guitar0);
                    }
                }
            }
            if(targetChar){
                RndDrawable* drawChar = targetChar;
                if(drawChar && drawChar->Showing()){
                    drawChar->SetShowing(false);
                    mEndShowList.push_back(drawChar);
                }
            }
        }
        for(std::vector<RndDrawable*>::iterator it = unk64.begin(); it != unk64.end(); ++it){
            RndDrawable* curDraw = *it;
            if(!curDraw->Showing()){
                curDraw->SetShowing(true);
                mEndHideList.push_back(curDraw);
            }
        }
        mHidden = true;
    }
}

void CamShot::UnHide(){
    if(mHidden){
        for(std::vector<RndDrawable*>::iterator it = mEndHideList.begin(); it != mEndHideList.end(); ++it){
            (*it)->SetShowing(false);
        }
        for(std::vector<RndDrawable*>::iterator it = mEndShowList.begin(); it != mEndShowList.end(); ++it){
            (*it)->SetShowing(true);
        }
        mEndHideList.clear();
        mEndShowList.clear();
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

// matches on retail
void CamShot::SetFrame(float frame, float blend){
    START_AUTO_TIMER("camera");
    if(!unk120p1){
        RndAnimatable::SetFrame(frame, blend);
        RndCam* cam = GetCam();
        if(cam){
            for(ObjPtrList<RndAnimatable>::iterator it = mAnims.begin(); it != mAnims.end(); ++it){
                (*it)->SetFrame(frame, 1.0f);
            }
            if(!mKeyframes.empty()){
                mPathFrame = -1.0f;
                unk120p1 = true;
                float endframe = EndFrame();
                static CamShotFrame nullFrame(nullptr);
                nullFrame.mCamShot = this;
                float f48 = 1.0f;
                CamShotFrame* frame4c = nullptr;
                CamShotFrame* frame50 = nullptr;
                GetKey(frame, frame4c, frame50, f48);
                if(mDisabled != 0){
                    frame50->UpdateTarget();
                    if(frame4c) frame4c->UpdateTarget();
                    unk120p1 = false;
                }
                else {
                    if(frame50 != mLastNext){
                        frame50->UpdateTarget();
                    }
                    if(!frame4c){
                        nullFrame.Interp(*frame50, 1.0f, blend, cam);
                    }
                    else {
                        if(frame4c != mLastPrev){
                            if(frame4c != mLastNext){
                                frame4c->UpdateTarget();
                            }
                            mLastPrev = frame4c;
                        }
                        frame4c->Interp(*frame50, f48, blend, cam);
                    }
                    mLastNext = frame50;
                    if(CheckShotStarted()){
                        HandleType(shot_started_msg);
                        unk120p4 = false;
                    }
                    if(CheckShotOver(frame)){
                        SetShotOver();
                    }
                    unk120p1 = false;
                }
            }
        }
    }
}

float CamShot::EndFrame(){ return mDuration; }

void CamShot::SetShotOver(){
    HandleType(shot_over_msg);
    mShotOver = true;
}

bool CamShot::CheckShotStarted(){ return unk120p4; }

bool CamShot::CheckShotOver(float f){
    return !mShotOver && !mLooping && f >= mDuration;
}

// matches in retail
void CamShot::Shake(float freq, float amp, const Vector2& ang, Vector3& output, Vector3& eulerOutput){
    if(TheTaskMgr.DeltaSeconds() > 0 && !AutoPrepTarget::sChanging){
        Vector2 localAng = ang;
        localAng *= DEG2RAD;
        if(RandomFloat() < freq){
            float f5 = RandomFloat(0.0f, 6.2831855f);
            float f6 = amp * RandomFloat();
            float f1 = f6 * Cosine(f5);
            mLastDesiredShakeOffset.x += f1;
            mLastDesiredShakeOffset.y += f1 * 0.333f;
            mLastDesiredShakeOffset.z += f6 * Sine(f5);
            mLastDesiredShakeAngOffset.x += RandomFloat(-localAng.x, localAng.x);
            mLastDesiredShakeAngOffset.y = 0;
            mLastDesiredShakeAngOffset.z += RandomFloat(-localAng.y, localAng.y);
        }
        float lenamp = Length(mLastDesiredShakeOffset) - amp;
        if(lenamp > 0){
            Normalize(mLastDesiredShakeOffset, mLastDesiredShakeOffset);
            mLastDesiredShakeOffset *= amp - lenamp;
        }
        float fabs1 = std::fabs(mLastDesiredShakeAngOffset.x) - localAng.x;
        if(fabs1 > 0){
            if(mLastDesiredShakeAngOffset.x > 0){
                fabs1 *= -1.0f;
            }
            mLastDesiredShakeAngOffset.x += fabs1;
        }

        float fabs2 = std::fabs(mLastDesiredShakeAngOffset.z) - localAng.y;
        if(fabs2 > 0){
            if(mLastDesiredShakeAngOffset.z > 0){
                fabs2 *= -1.0f;
            }
            mLastDesiredShakeAngOffset.z += fabs2;
        }

        Vector3 v58;
        Subtract(mLastDesiredShakeOffset, mLastShakeOffset, v58);
        bool usePPFPS = false;
        if(RndPostProc::Current() && RndPostProc::Current()->EmulateFPS() > 0) usePPFPS = true;
        float emulateFPS = usePPFPS ? RndPostProc::Current()->EmulateFPS() : 60.0f;
        float fps = 60.0f / emulateFPS;
        v58 *= 0.02f;
        Vector3 v64 = mShakeVelocity;
        v64 *= fps;
        ::Add(mLastShakeOffset, v64, mLastShakeOffset);
        ::Add(mShakeVelocity, v58, mShakeVelocity);
        ::Add(mLastShakeOffset, v58, mLastShakeOffset);
        float powed = std::pow(0.9f, fps);
        mShakeVelocity *= powed;
        Subtract(mLastDesiredShakeAngOffset, mLastShakeAngOffset, v58);
        v58 *= 0.02f;
        Vector3 v70 = mShakeAngVelocity;
        v70 *= fps;
        ::Add(mLastShakeAngOffset, v70, mLastShakeAngOffset);
        ::Add(mShakeAngVelocity, v58, mShakeAngVelocity);
        ::Add(mLastShakeAngOffset, v58, mLastShakeAngOffset);
        mShakeAngVelocity *= powed;
    }
    output = mLastShakeOffset;
    eulerOutput = mLastShakeAngOffset;
}

// matches in retail with the right inline settings: https://decomp.me/scratch/Tvtaz
void CamShot::GetKey(float frame, CamShotFrame*& prev, CamShotFrame*& next, float& keyBlend){
    MILO_ASSERT(!mKeyframes.empty(), 0x29B);
    if(frame <= 0 || mDuration <= 0){
        prev = nullptr;
        next = mKeyframes.begin();
        keyBlend = 1.0f;
        return;
    }
    if(frame >= mKeyframes.back().mFrame){
        if(mLooping && (mLoopKeyframe < mKeyframes.size() && mLoopKeyframe >= 0)){
            if(frame >= mDuration){
                float duration = mDuration - mKeyframes[mLoopKeyframe].mFrame;
                frame -= mDuration;
                MILO_ASSERT(duration > 0, 0x2AF);
                float f9 = std::fmod(frame, duration);
                frame = f9 + mKeyframes[mLoopKeyframe].mFrame;
            }
            if(frame >= mKeyframes.back().mFrame){
                if(mKeyframes.back().mBlend <= 0){
                    prev = nullptr;
                    next = &mKeyframes.back();
                    keyBlend = 1.0f;
                    return;
                }
                float fvar1 = mKeyframes.back().mFrame + mKeyframes.back().mDuration;
                if(frame > fvar1){
                    MILO_ASSERT(mKeyframes.back().mBlend > 0, 0x2C4);
                    prev = &mKeyframes.back();
                    next = &mKeyframes[mLoopKeyframe];
                    keyBlend = (frame - fvar1) / mKeyframes.back().mBlend;
                    return;
                }
                prev = nullptr;
                next = &mKeyframes.back();
                keyBlend = 1.0f;
                return;
            }
        } else {
            prev = nullptr;
            next = &mKeyframes.back();
            keyBlend = 1.0f;
            return;
        }
    }
    int before = 0;
    int after = mKeyframes.size() - 1;
    while(after > before + 1){
        int avg = (before + after) >> 1;
        float curFrame = mKeyframes[avg].mFrame;
        if(frame == curFrame){
            prev = nullptr;
            next = &mKeyframes[avg];
            keyBlend = 1.0f;
            return;
        }
        if(frame > curFrame) {
            before = avg;
        }
        if(!(frame > curFrame)) { 
            after = avg;
        }
    }
    MILO_ASSERT(frame >= mKeyframes[before].mFrame && frame < mKeyframes[after].mFrame, 0x2F4);
    float fvar1 = mKeyframes[before].mFrame + mKeyframes[before].mDuration;
    if(frame > fvar1){
        MILO_ASSERT(mKeyframes[before].mBlend > 0, 0x2F9);
        prev = &mKeyframes[before];
        next = &mKeyframes[after];
        keyBlend = (frame - fvar1) / mKeyframes[before].mBlend;
    }
    else {
        prev = nullptr;
        next = &mKeyframes[before];
        keyBlend = 1.0f;
    }
}

void CamShot::CacheFrames(){
    float frames = 0.0f;
    for(int i = 0; i != mKeyframes.size(); i++){
        CamShotFrame& curframe = mKeyframes[i];
        curframe.mFrame = frames;
        frames += curframe.mDuration + curframe.mBlend;
    }
    mDuration = frames;
}

bool CamShot::SetPos(CamShotFrame& frame, RndCam* cam){
    cam = cam ? cam : GetCam();
    if(!cam) return false;
    else {
        Transform tf40(cam->WorldXfm());
        if(frame.HasTargets()){
            Vector3 ve0;
            frame.GetCurrentTargetPosition(ve0);
            cam->WorldToScreen(ve0, frame.mScreenOffset);
            frame.mScreenOffset += Vector2(-0.5f, -0.5f);
            frame.mScreenOffset.x *= 2.0f;
            frame.mScreenOffset.y *= -2.0f;
            Vector3 vec;
            Subtract(ve0, tf40.v, vec);
            Vector3 vf8(cam->WorldXfm().m.y);
            vf8 *= Dot(vec, cam->WorldXfm().m.y);
            Vector3 v104;
            ::Add(cam->WorldXfm().v, vf8, v104);
            Vector3 v110;
            Subtract(ve0, v104, v110);
            ::Add(tf40.v, v110, tf40.v);
        }
        else frame.mScreenOffset.Zero();

        frame.SetFieldOfView(cam->YFov());
        RndTransformable* frameParent = frame.mParent;
        if(frameParent){
            Transform tf70(frameParent->WorldXfm());
            if(!frame.mUseParentNotation){
                tf70.m.Identity();
            }
            Transform tfa0;
            FastInvert(tf70, tfa0);
            Multiply(tf40, tfa0, tf40);
        }
        if(mPath && &mKeyframes[0] == &frame){
            Transform tfd0;
            mPath->MakeTransform(0, tfd0, true, 1.0f);
            tf40.v -= tfd0.v;
            if(!frame.HasTargets()){
                tf40.m.Identity();
            }
        }
        frame.mWorldOffset.Set(tf40);
        return true;
    }
}

bool CamShot::PlatformOk() const {
    if(LOADMGR_EDITMODE || mPlatformOnly == kPlatformNone || TheLoadMgr.GetPlatform() == kPlatformNone) return true;
    Platform plat = TheLoadMgr.GetPlatform();
    if(TheLoadMgr.GetPlatform() == kPlatformPC) plat = kPlatformXBox;
    return plat == mPlatformOnly;
}

bool CamShot::ShotOk(CamShot* shot){
    static Message msg("shot_ok", 0);
    msg[0] = shot;
    DataNode handled = HandleType(msg);
    if(handled.Type() != kDataUnhandled){
        if(handled.Type() == kDataString){
#ifdef MILO_DEBUG
            if(DataVariable("camera_spew") != 0)
#endif
                MILO_LOG("Shot %s rejected: %s.\n", Name(), handled.Str());
            return false;
        }
        else if(handled.Int() == 0){
#ifdef MILO_DEBUG
            if(DataVariable("camera_spew") != 0)
#endif
                MILO_LOG("Shot %s rejected: not ok.\n", Name());
            return false;
        }
        else {
            return true;
        }
    }
    else return true;
}

#pragma push
#pragma dont_inline on
BEGIN_COPYS(CamShot)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    CREATE_COPY(CamShot)
    BEGIN_COPYING_MEMBERS
        mKeyframes.clear();
        for(int i = 0; i != c->mKeyframes.size(); i++){
            mKeyframes.push_back(CamShotFrame(this, c->mKeyframes[i]));
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
        COPY_MEMBER(mHideList)
        COPY_MEMBER(mShowList)
        COPY_MEMBER(mShowList)
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
    RndTransformable* foundTrans = shot->Dir()->Find<RndTransformable>(str.c_str(), false);
    if(sym.Null()){
        if(foundTrans) return foundTrans;
        MILO_LOG("%s could not find %s, assuming character, attaching to base\n", PathName(shot), str);
    }
    char buf[256];
    strcpy(buf, sym.Str());
    char* buf_ptr = strchr(buf, '.');
    if(buf_ptr) *buf_ptr = '\0';
    else if(buf[0] == '\0'){
        strcpy(buf, "base");
    }
    const char* search = MakeString("%s_%s.tp", str, buf);
    RndTransProxy* proxy = shot->Dir()->Find<RndTransProxy>(search, false);
    if(!proxy){
        proxy = Hmx::Object::New<RndTransProxy>();
        proxy->SetName(search, shot->Dir());
        proxy->SetProxy(dynamic_cast<ObjectDir*>(foundTrans));
        proxy->SetPart(sym);
    }
    return proxy;
}

void LoadDrawables(BinStream& bs, std::vector<RndDrawable*>& vec, ObjectDir* dir){
    MILO_ASSERT(dir, 0x3F9);
    vec.clear();
    int count;
    bs >> count;
    vec.reserve(count);
    for(; count != 0; count--){
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        RndDrawable* draw = dir->Find<RndDrawable>(buf, false);
        if(draw) vec.push_back(draw);
    }
}

SAVE_OBJ(CamShot, 0x409);

#pragma push
#pragma dont_inline on
BEGIN_LOADS(CamShot)
    LOAD_REVS(bs)
    ASSERT_REVS(50, 1)
    bool bitfield_bool;
    bool hidden = mHidden;
    if(hidden) UnHide();
    float somefloat = 0.0f;
    if(gRev != 0){
        LOAD_SUPERCLASS(Hmx::Object)
        LOAD_SUPERCLASS(RndAnimatable)
    }
    if(gRev > 0xC){
        bs >> mKeyframes;
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
        ObjPtrList<RndTransformable> pList(this, kObjListNoNull);
        ObjPtr<RndTransformable> ptr(this, 0);
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
            csf1.mWorldOffset.Set(tf1);
            csf1.mScreenOffset = vec1;
            csf1.SetFieldOfView(fov1);
            csf1.SetBlurDepth(someotherfloat);
            csf1.SetMaxBlur(1.0f);
            csf1.SetMinBlur(0.0f);
            csf1.mFocusBlurMultiplier = 0.0f;
            csf1.mTargets = pList;
            csf1.mParent = ptr;
            csf1.mUseParentNotation = somebool;
            mKeyframes.push_back(csf1);
        }
        csf2.mDuration = 0.0f;
        csf2.mBlend = 0.0f;
        csf2.mWorldOffset.Set(tf2);
        csf2.mScreenOffset = vec2;
        csf2.SetFieldOfView(fov2);
        csf2.SetBlurDepth(someotherfloat);
        csf2.SetMaxBlur(1.0f);
        csf2.SetMinBlur(0.0f);
        csf2.mFocusBlurMultiplier = 0.0f;
        csf2.mTargets = pList;
        csf2.mParent = ptr;
        csf2.mUseParentNotation = somebool;
        mKeyframes.push_back(csf2);
    }
    bs >> mPath;
    if(gRev >= 2 && gRev <= 44){
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
    if(gRev > 0x22) bs >> (int&)mPlatformOnly;
    else if(gRev > 0x21){
        int state;
        bs >> state;
        if(state == 1) mPlatformOnly = kPlatformXBox;
        else if(state == 2) mPlatformOnly = kPlatformPS3;
        else mPlatformOnly = kPlatformNone;
    }
    if(gRev < 1) LOAD_SUPERCLASS(RndAnimatable)
    CamShotCrowd csc(this);
    if(gRev >= 5 && gRev <= 41){
        bs >> csc.unk10;
    }
    int loc240 = -1;
    if(gRev >= 8 && gRev <= 41) bs >> loc240;
    if(gRev > 5){
        mShowList.clear();
        mShowList.clear();
        mHideList.clear();
        if(gRev <= 0x2F || (bs.Cached() && gRev < 0x32)){
            LoadDrawables(bs, mHideList, Dir());
        }
        else {
            LoadDrawables(bs, mHideList, Dir());
            LoadDrawables(bs, mShowList, Dir());
        }
    }
    if(gRev > 0x1B) LoadDrawables(bs, unk64, Dir());
    if(gRev > 0xB){
        if(gRev < 0x2A) bs >> csc.mCrowd;
    }
    else {
        DataNode* prop = Property("hide_crowd", false);
        if(!prop || prop->Int() == 0){
            ObjDirItr<WorldCrowd> iter(Dir(), true);
            if(iter){
                csc.mCrowd = iter;
            }
        }
    }
    if(gRev >= 33 && gRev <= 41) bs >> (int&)csc.mCrowdRotate;
    if(gRev >= 8 && gRev <= 41){
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
    if(gRev == 16 || gRev == 17){
        float f250, f254;
        bs >> f250;
        bs >> f254;
        for(int i = 0; i != mKeyframes.size(); i++){
            mKeyframes[i].mShakeNoiseAmp = f254;
            mKeyframes[i].mShakeNoiseFreq = f250;
        }
    }
    if(gRev > 0x10 && gRev < 0x12){
        Vector2 v210;
        bs >> v210;
        for(int i = 0; i != mKeyframes.size(); i++){
            mKeyframes[i].SetMaxAngularOffset(v210);
        }
    }
    if(gRev > 0x13) bs >> mGlowSpot;
    if(gRev > 0x1D) bs >> mDrawOverrides;
    if(gRev > 0x1F) bs >> mPostProcOverrides;
    if(gRev > 0x23 && (gRev - 47 > 1U)){
        bs >> bitfield_bool;
        mPS3PerPixel = bitfield_bool;
    }
    if(gRev > 0x24) bs >> mFlags;
    Symbol s258;
    if(gRev == 40 || gRev == 41 || gRev == 42) bs >> s258;
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

CamShotFrame::CamShotFrame(Hmx::Object* o) : mDuration(0), mBlend(0), mBlendEase(0), mFrame(-1.0f), mShakeNoiseAmp(0), mShakeNoiseFreq(0), mFocusBlurMultiplier(0),
    mTargets(o, kObjListNoNull), mCamShot(dynamic_cast<CamShot*>(o)), mParent(o), mFocusTarget(o),
    mZoomFOV(0), mMaxBlur(0xFF), mMinBlur(0),
    mBlendEaseMode(0), mUseParentNotation(0), mParentFirstFrame(0) {
    mMaxAngularOffsetY = 0;
    mMaxAngularOffsetX = 0;
    SetBlurDepth(0.34999999f);
    SetFieldOfView(1.2217305f);
    mWorldOffset.Reset();
    mScreenOffset.Zero();
    mLastTargetPos.x = 1e+30f;
}

CamShotFrame::CamShotFrame(Hmx::Object* o, const CamShotFrame& frame) : mDuration(frame.mDuration), mBlend(frame.mBlend), mBlendEase(frame.mBlendEase),
    mWorldOffset(frame.mWorldOffset), mScreenOffset(frame.mScreenOffset), mShakeNoiseAmp(frame.mShakeNoiseAmp), mShakeNoiseFreq(frame.mShakeNoiseFreq), mFocusBlurMultiplier(frame.mFocusBlurMultiplier),
    mTargets(frame.mTargets), mCamShot(dynamic_cast<CamShot*>(o)), mParent(frame.mParent), mFocusTarget(frame.mFocusTarget), mFOV(frame.mFOV), mZoomFOV(frame.mZoomFOV),
    mBlurDepth(frame.mBlurDepth), mMaxBlur(frame.mMaxBlur), mMinBlur(frame.mMinBlur), mBlendEaseMode(frame.mBlendEaseMode), mUseParentNotation(frame.mUseParentNotation), mParentFirstFrame(0) {
    mMaxAngularOffsetX = frame.mMaxAngularOffsetX;
    mMaxAngularOffsetY = frame.mMaxAngularOffsetY;
}

void CamShotFrame::Load(BinStream& bs){
    bs >> mDuration;
    bs >> mBlend;
    bs >> mBlendEase;
    if(CamShot::gRev > 0x2D){
        int b; bs >> b;
        mBlendEaseMode = b;
    }
    float fov; bs >> fov;
    SetFieldOfView(fov);
    Transform tf40;
    tf40.Zero();
    Transform tf70;
    bs >> tf70;
    if(tf40 == tf70) mWorldOffset.Reset();
    else mWorldOffset.Set(tf70);
    bs >> mScreenOffset;
    float blurdepth; bs >> blurdepth;
    if(CamShot::gRev < 0x17){
        SetBlurDepth(1.0f - blurdepth);
        int i; bs >> i;
    }
    else SetBlurDepth(blurdepth);
    if(CamShot::gRev > 0x17){
        float b; bs >> b;
        SetMaxBlur(b);
    }
    else mMaxBlur = 0xff;
    if(CamShot::gRev > 0x1C){
        float b; bs >> b;
        SetMinBlur(b);
    }
    else mMinBlur = 0;
    if(CamShot::gRev > 0x14) bs >> mFocusBlurMultiplier;
    else mFocusBlurMultiplier = 0;
    if(CamShot::gRev < 0x17){ int i; bs >> i; }
    if(CamShot::gRev > 0x2B) bs >> mTargets;
    else {
        int count; bs >> count;
        mTargets.clear();
        for(int i = 0; i < count; i++){
            RndTransformable* part = LoadSubPart(bs, mCamShot);
            if(part) mTargets.push_back(part);
        }
    }
    if(CamShot::gRev > 0x1A){
        if(CamShot::gRev > 0x2B) bs >> mFocusTarget;
        else mFocusTarget = LoadSubPart(bs, mCamShot);
    }
    if(CamShot::gRev > 0x2B) bs >> mParent;
    else mParent = LoadSubPart(bs, mCamShot);
    bool b1; bs >> b1;
    mUseParentNotation = b1;
    if(CamShot::gRev > 0x11){
        bs >> mShakeNoiseAmp;
        bs >> mShakeNoiseFreq;
        Vector2 v; bs >> v;
        SetMaxAngularOffset(v);
    }
    if(CamShot::gRev > 0x15){
        float zoomfov; bs >> zoomfov;
        SetZoomFieldOfView(zoomfov);
    }
    if(CamShot::gRev > 0x28){
        bool b0; bs >> b0;
        mParentFirstFrame = b0;
    }
}

bool CamShotFrame::OnSyncTargets(ObjPtrList<RndTransformable>& transList, DataNode& node, DataArray* prop, int i, PropOp op){
    bool synced;
    if(op != kPropGet && op != kPropSize){
        AutoPrepTarget target(*this);
        synced = PropSync(transList, node, prop, i, op);
    }
    else synced = PropSync(transList, node, prop, i, op);
    return synced;
}

bool CamShotFrame::SameTargets(const CamShotFrame& frame) const {
    if(mTargets.size() != frame.mTargets.size()) return false;
    for(ObjPtrList<RndTransformable>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
        ObjPtrList<RndTransformable>::iterator otherIt = frame.mTargets.begin();
        for(; otherIt != frame.mTargets.end(); ++otherIt){
            if(*it == *otherIt) break;
        }
        if(otherIt == frame.mTargets.end()) return false;
    }
    return true;
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
    cam->SetFrustum(mCamShot->mNear, mCamShot->mFar, interp2, 1.0f);
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
                tf160.LookAt(mLastTargetPos, tf130.m.z);
            }
            if(thasTarget){
                tf190.LookAt(frame.mLastTargetPos, tf130.m.z);
            }
            ::Interp(tf160.m, tf190.m, d11, tf130.m);
        }
        Vector2 v1e0;
        if(hasTarget && !thasTarget){
            f1fc = Distance(mLastTargetPos, tf130.v);
            v1e0 = mScreenOffset;
        }
        else if(!hasTarget && thasTarget){
            f1fc = Distance(frame.mLastTargetPos, tf130.v);
            v1e0 = frame.mScreenOffset;
        }
        else {
            float dist13 = Distance(frame.mLastTargetPos, tf130.v);
            float dist14 = Distance(mLastTargetPos, tf130.v);
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
    cam->SetFrustum(mCamShot->mNear, mCamShot->mFar, interp2 + f200, 1.0f);
    RndTransformable* focus = mFocusTarget;
    RndTransformable* towardFocus = frame.mFocusTarget;
    bool b10 = false;
    if(mCamShot->mUseDepthOfField && (focus || hasTarget || towardFocus || thasTarget)){
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
            if(hasTarget) d10 = Distance(mLastTargetPos, tf130.v);
        }
        if(towardFocus){
            d9 = Distance(towardFocus->WorldXfm().v, tf130.v);
        }
        else {
            if(thasTarget) d9 = Distance(frame.mLastTargetPos, tf130.v);
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
    mCamShot->Shake(f218, f214, v1e8, v1cc, v1d8);
    Multiply(v1cc, tf130, tf130.v);
    Hmx::Matrix3 m1b4;
    MakeRotMatrix(v1d8, m1b4, true);
    Multiply(tf130.m, m1b4, tf130.m);
    cam->SetLocalXfm(tf130);
}
#pragma pop

void CamShotFrame::UpdateTarget() const {
    CamShotFrame* usable = const_cast<CamShotFrame*>(this);
    GetCurrentTargetPosition(usable->mLastTargetPos);
    if(mParent){
        usable->unk44.Set(mParent->WorldXfm());
    }
}

void CamShotFrame::GetCurrentTargetPosition(Vector3& v) const {
    v.Zero();
    int count = 0;
    for(ObjPtrList<RndTransformable>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
        RndTransformable* cur = *it;
        if(cur){
            count++;
            Add(v, cur->WorldXfm().v, v);
        }
    }
    if(count > 0) v *= (1.0f / (float)count);
}

bool CamShotFrame::HasTargets() const {
    for(ObjPtrList<RndTransformable>::iterator it = mTargets.begin(); it != mTargets.end(); ++it){
        if(*it) return true;
    }
    return false;
}

void CamShotFrame::BuildTransform(RndCam* cam, Transform& tf, bool b3) const {
    MILO_ASSERT(mLastTargetPos.x != kHugeFloat, 0x855);
}

DataNode CamShot::OnGetOccluded(DataArray* da){
    return 0;
}

DataNode CamShot::OnSetAllCrowdChars3D(DataArray* da){
    return 0;
}

CamShotCrowd::CamShotCrowd(Hmx::Object* o) : mCrowd(o, 0), mCrowdRotate(kCrowdRotateNone), unk18(dynamic_cast<CamShot*>(o)) {}
CamShotCrowd::CamShotCrowd(Hmx::Object* o, const CamShotCrowd& crowd) : mCrowd(crowd.mCrowd),
    mCrowdRotate(crowd.mCrowdRotate), unk10(crowd.unk10), unk18(dynamic_cast<CamShot*>(o)) {}

void CamShotCrowd::Load(BinStream& bs){
    bs >> mCrowd;
    bs >> (int&)mCrowdRotate;
    bs >> unk10;
    int num;
    bs >> num;
    if(!mCrowd || num == mCrowd->unk88) unk10.resize(num);
    else unk10.clear();
}

void CamShotCrowd::Set3DCrowd(){
    if(mCrowd){
        mCrowd->Set3DCharList(unk10, unk18);
    }
}

void CamShotCrowd::ClearCrowdList(){ unk10.clear(); }
void CamShotCrowd::OnCrowdChanged(){ ClearCrowdList(); }

void CamShotCrowd::ClearCrowdChars(){
    ClearCrowdList();
    if(!mCrowd) MILO_WARN("No crowd selected");
    mCrowd->Set3DCharList(unk10, unk18);
}

void CamShotCrowd::SetCrowdChars(){
    std::list<std::pair<RndMultiMesh*, std::list<RndMultiMesh::Instance>::iterator> > meshlist;
    GetSelectedCrowd(meshlist);
    if(meshlist.begin() == meshlist.end()){
        MILO_WARN("No selected crowd members in this crowd");
    }
    else {
        ClearCrowdChars();
        AddCrowdChars(meshlist);
    }
}

void CamShotCrowd::AddCrowdChars(){
    std::list<std::pair<RndMultiMesh*, std::list<RndMultiMesh::Instance>::iterator> > meshlist;
    GetSelectedCrowd(meshlist);
    if(meshlist.begin() == meshlist.end()){
        MILO_WARN("No selected crowd members in this crowd");
    }
    else AddCrowdChars(meshlist);
}

void CamShotCrowd::GetSelectedCrowd(std::list<std::pair<RndMultiMesh*, std::list<RndMultiMesh::Instance>::iterator> >& crowdChars){
    for(std::list<std::pair<class RndMultiMeshProxy*, int> >::iterator it = RndMultiMesh::sProxyPool.begin(); it != RndMultiMesh::sProxyPool.end(); ++it){
        RndMultiMeshProxy* proxy = it->first;
        MILO_ASSERT(proxy, 0xB8F);
        RndMultiMesh* multiMesh = proxy->GetMultiMesh();
        if(!proxy->mRefs.empty() && multiMesh){
            crowdChars.push_back(std::make_pair(multiMesh, proxy->mIndex));
            proxy->SetMultiMesh(0, 0);
        }
    }
}

DECOMP_FORCEACTIVE(CameraShot, "ki != mmesh->Instances().size()")

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
    return mKeyframes[da->Int(2)].HasTargets();
}

DataNode CamShot::OnSetPos(DataArray* da){
    int idx = da->Int(2);
    return SetPos(mKeyframes[idx], RndCam::Current());
}

DataNode CamShot::OnClearCrowdChars(DataArray* da){
    int idx = da->Int(2);
    MILO_ASSERT(idx < mCrowds.size(), 0xC82);
    mCrowds[idx].ClearCrowdChars();
    return 0;
}

DataNode CamShot::OnAddCrowdChars(DataArray* da){
    int idx = da->Int(2);
    MILO_ASSERT(idx < mCrowds.size(), 0xC8A);
    mCrowds[idx].AddCrowdChars();
    return 0;
}

DataNode CamShot::OnSetCrowdChars(DataArray* da){
    int idx = da->Int(2);
    MILO_ASSERT(idx < mCrowds.size(), 0xC92);
    mCrowds[idx].SetCrowdChars();
    return 0;
}

DataNode CamShot::OnRadio(DataArray* da){
    int i2 = da->Int(2);
    int i3 = da->Int(3);
    if(mFlags & i2){
        mFlags = mFlags & ~i3 | i2;
    }
    return 0;
}

bool CamShotFrame::OnSyncParent(ObjPtr<RndTransformable>& parent, DataNode& node, DataArray* prop, int i, PropOp op){
    bool synced;
    if(op != kPropGet){
        AutoPrepTarget target(*this);
        synced = PropSync(parent, node, prop, i, op);
    }
    else synced = PropSync(parent, node, prop, i, op);
    return synced;
}

inline float ComputeFOVScale(float fov){
    return 24.0f / (std::tan(fov / 2.0f) * 2.0f);
}

inline float ScaleToFOV(float scale){
    return std::atan(24.0f / (scale * 2.0f)) * 2.0f;
}

Symbol FOV_to_LensSym(float fov){
    float scaled = ComputeFOVScale(fov);
    if(ApproxEq(scaled, 15.0f)) return "15mm";
    else if(ApproxEq(scaled, 20.0f)) return "20mm";
    else if(ApproxEq(scaled, 24.0f)) return "24mm";
    else if(ApproxEq(scaled, 28.0f)) return "28mm";
    else if(ApproxEq(scaled, 35.0f)) return "35mm";
    else if(ApproxEq(scaled, 50.0f)) return "50mm";
    else if(ApproxEq(scaled, 85.0f)) return "85mm";
    else if(ApproxEq(scaled, 135.0f)) return "135mm";
    else if(ApproxEq(scaled, 200.0f)) return "200mm";
    else return "Custom";
}

float LensSym_to_FOV(Symbol sym){
    String lensStr = sym.mStr;
    unsigned int idx = lensStr.find("mm");
    if(idx != String::npos){
        float scale = atof(lensStr.substr(0, idx).c_str());
        return ScaleToFOV(scale);
    }
    else return -1.0f;
}

BEGIN_CUSTOM_PROPSYNC(CamShotCrowd)
    SYNC_PROP_MODIFY_ALT(crowd, o.mCrowd, o.OnCrowdChanged())
    SYNC_PROP(crowd_rotate, (int&)o.mCrowdRotate)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(CamShotFrame)
    SYNC_PROP(duration, o.mDuration)
    SYNC_PROP(blend, o.mBlend)
    SYNC_PROP(blend_ease, o.mBlendEase)
    SYNC_PROP_SET(blend_ease_mode, o.mBlendEaseMode, o.mBlendEaseMode = _val.Int())
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
    SYNC_PROP_SET(use_parent_rotation, o.mUseParentNotation, o.mUseParentNotation = _val.Int())
    SYNC_PROP_SET(parent_first_frame, o.mParentFirstFrame, o.mParentFirstFrame = _val.Int())
    SYNC_PROP_SET(field_of_view, o.FieldOfView() * RAD2DEG, o.SetFieldOfView(_val.Float() * DEG2RAD))
    SYNC_PROP_SET(lens_mm, ComputeFOVScale(o.FieldOfView()), o.SetFieldOfView(ScaleToFOV(_val.Float())))
    SYNC_PROP_SET(lens_preset, FOV_to_LensSym(o.FieldOfView()), 
        { 
            float fov = LensSym_to_FOV(_val.Sym());
            if(fov != -1.0f) o.SetFieldOfView(fov);
            else o.SetFieldOfView(o.FieldOfView() + 0.00010011921f);
        }
    )
    SYNC_PROP_SET(blur_depth, o.BlurDepth(), o.SetBlurDepth(_val.Float()))
    SYNC_PROP_SET(max_blur, o.MaxBlur(), o.SetMaxBlur(_val.Float()))
    SYNC_PROP_SET(min_blur, o.MinBlur(), o.SetMinBlur(_val.Float()))
    SYNC_PROP(focus_blur_multiplier, o.mFocusBlurMultiplier)
    SYNC_PROP(shake_noisefreq, o.mShakeNoiseFreq)
    SYNC_PROP(shake_noiseamp, o.mShakeNoiseAmp)
    SYNC_PROP_SET(zoom_fov, o.ZoomFieldOfView() * RAD2DEG, o.SetZoomFieldOfView(_val.Float() * DEG2RAD))
END_CUSTOM_PROPSYNC

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(CamShot)
    SYNC_PROP_MODIFY_ALT(keyframes, mKeyframes, CacheFrames())
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
    SYNC_PROP_SET(category, mCategory, mCategory = _val.ForceSym())
    SYNC_PROP(filter, mFilter)
    SYNC_PROP(clamp_height, mClampHeight)
    SYNC_PROP(near_plane, mNear)
    SYNC_PROP(far_plane, mFar)
    SYNC_PROP_STATIC(duration, mDuration)
    SYNC_PROP_SET(use_depth_of_field, mUseDepthOfField, mUseDepthOfField = _val.Int())
    SYNC_PROP(path, mPath)
    SYNC_PROP(path_frame, mPathFrame)
    SYNC_PROP(platform_only, (int&)mPlatformOnly)
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
