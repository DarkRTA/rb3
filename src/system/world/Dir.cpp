#include "world/Dir.h"
#include "math/Utl.h"
#include "obj/ObjMacros.h"
#include "os/Timer.h"
#include "rndobj/Draw.h"
#include "rndobj/Env.h"
#include "world/CameraShot.h"
#include "world/Crowd.h"
#include "world/LightPreset.h"
#include "world/Spotlight.h"
#include "world/SpotlightDrawer.h"
#include "rndobj/Mat.h"
#include "rndobj/Cam.h"
#include "rndobj/Rnd.h"
#include "string.h"
#include "obj/ObjVersion.h"
#include "ui/UI.h"
#include "utl/Std.h"
#include "utl/Messages.h"

INIT_REVS(WorldDir)

WorldDir *TheWorld;
WorldDir *gLastWorld;
std::vector<FilePath> gOldChars;
ObjectDir *gOldTexDir;

WorldDir::WorldDir()
    : mPresetOverrides(this), mBitmapOverrides(this), mMatOverrides(this),
      mHideOverrides(this), mCamShotOverrides(this), mPS3PerPixelShows(this),
      mPS3PerPixelHides(this), mCrowds(this), mFakeHudDir(0), mShowFakeHud(0), mHud(this),
      mCameraManager(this), mPresetManager(this), mEchoMsgs(0), mFirstPoll(0),
      mPollCamera(1), mTestPreset1(this), mTestPreset2(this), mTestAnimationTime(10.0f) {
    mGlowMat = Hmx::Object::New<RndMat>();
    mGlowMat->SetBlend(RndMat::kBlendSrcAlpha);
    mGlowMat->SetZMode(RndMat::kZModeDisable);
    mGlowMat->SetPreLit(true);
    ClearDeltas();
}

#pragma push
#pragma pool_data off
void SetTheWorld(WorldDir *dir) {
    static DataNode &world = DataVariable("world");
    world = dir;
    TheWorld = dir;
    if (dir)
        gLastWorld = dir;
}
#pragma pop

void WorldDir::Init() {
    Register();
    SetTheWorld(nullptr);
}

WorldDir::~WorldDir() {
    delete mFakeHudDir;
    delete mGlowMat;
    SpotlightDrawer::sCurrent->ClearLights();
    if (TheWorld == this)
        SetTheWorld(nullptr);
}

void WorldDir::Enter() {
    if (!TheWorld) {
        SetTheWorld(this);
        static DataNode &n = DataVariable("world.last_entered");
        n = this;
    }
    mPresetManager.Enter();
    mCameraManager.Enter();
    PanelDir::Enter();
    ClearDeltas();
    mFirstPoll = true;
    TheRnd->SetProcAndLock(false);
    TheRnd->ResetProcCounter();
    mDrawItr = mDraws.begin();
    if (TheWorld == this)
        SetTheWorld(nullptr);
}

void WorldDir::ClearDeltas() {
    for (int i = 0; i < 4; i++)
        mDeltaSincePoll[i] = 0;
}

void WorldDir::AccumulateDeltas(float *deltas) {
    for (int i = 0; i < 4; i++) {
        deltas[i] = TheTaskMgr.DeltaTime((TaskUnits)i);
        mDeltaSincePoll[i] += deltas[i];
    }
}

void WorldDir::ExtendDeltas() {
    for (int i = 0; i < 4; i++) {
        TheTaskMgr.SetDeltaTime((TaskUnits)i, mDeltaSincePoll[i]);
    }
}

void WorldDir::RestoreDeltas(float *f) {
    for (int i = 0; i < 4; i++) {
        mDeltaSincePoll[i] = 0;
        TheTaskMgr.SetDeltaTime((TaskUnits)i, f[i]);
    }
}

void WorldDir::Poll() {
    START_AUTO_TIMER("world_poll");
    if (TheWorld && TheWorld != this)
        RndDir::Poll();
    else {
        SetTheWorld(this);
        float deltas[4];
        AccumulateDeltas(deltas);
        bool b = true;
        if (!mFirstPoll && !(TheRnd->ProcCmds() & kProcessPost))
            b = false;
        mFirstPoll = false;
        if (b) {
            ExtendDeltas();
            HandleType(select_camera_msg);
            if (mPollCamera)
                mCameraManager.PrePoll();
            mPresetManager.Poll();
            RndDir::Poll();
            if (mPollCamera)
                mCameraManager.Poll();
            RestoreDeltas(deltas);
        }
        SetTheWorld(nullptr);
    }
}

SAVE_OBJ(WorldDir, 0xFC);

#pragma push
#pragma dont_inline on
BEGIN_COPYS(WorldDir)
    COPY_SUPERCLASS(PanelDir)
    CREATE_COPY(WorldDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mFakeHudFilename)
        SyncHides(false);
        COPY_MEMBER(mHideOverrides)
        SyncHides(true);
        SyncBitmaps(false);
        COPY_MEMBER(mBitmapOverrides)
        SyncBitmaps(true);
        SyncMats(false);
        COPY_MEMBER(mMatOverrides)
        SyncMats(true);
        SyncPresets(false);
        COPY_MEMBER(mPresetOverrides)
        SyncPresets(true);
        SyncCamShots(false);
        COPY_MEMBER(mCamShotOverrides)
        SyncCamShots(true);
        COPY_MEMBER(mPS3PerPixelHides)
        COPY_MEMBER(mPS3PerPixelShows)
        COPY_MEMBER(mTestPreset1)
        COPY_MEMBER(mTestPreset2)
        COPY_MEMBER(mTestAnimationTime)
        COPY_MEMBER(mHud)
        SyncHUD();
    END_COPYING_MEMBERS
END_COPYS
#pragma pop

// fn_8059A2C8
BinStream &operator>>(BinStream &bs, WorldDir::BitmapOverride &c) {
    bs >> c.original;
    if (gOldTexDir) {
        FilePath bitmap;
        bs >> bitmap;
        if (!bitmap.empty()) {
            const char *chr = strrchr(bitmap.c_str(), 0x2F);
            chr = chr ? chr + 1 : bitmap.c_str();
            c.replacement = gOldTexDir->Find<RndTex>(chr, false);
            if (!c.replacement) {
                MILO_WARN(
                    "Loading %s synchronously, please resave %s",
                    chr,
                    gOldTexDir->mLoader->mFile
                );
                c.replacement = gOldTexDir->New<RndTex>(chr);
                c.replacement->SetBitmap(bitmap);
            } else {
                MILO_ASSERT(c.replacement->File() == bitmap, 0x152);
            }
        } else
            c.replacement = nullptr;
    } else
        bs >> c.replacement;
    return bs;
}

void WorldDir::PreLoad(BinStream &bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(0x19, 0);
    MILO_ASSERT(gRev >= 4, 0x163);
    if (gRev != 0 && gRev < 5) {
        ObjPtr<RndCam> ptr(this);
        bs >> ptr;
    }
    if (gRev >= 2 && gRev <= 20) {
        int i, j;
        bs >> i >> j;
    }
    if (gRev > 9)
        bs >> mFakeHudFilename;
    if (gRev < 9) {
        if (gRev > 7)
            OldLoadProxies(bs, 0);
        else if (gRev > 2)
            bs >> gOldChars;
    }
    PushRev(packRevs(gAltRev, gRev), this);
    PanelDir::PreLoad(bs);
}

// fn_8059A600
void WorldDir::PostLoad(BinStream &bs) {
    PanelDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if (gRev == 5) {
        ObjPtr<RndCam> camPtr(this);
        bs >> camPtr;
        SetCam(camPtr);
    }
    if (gRev < 8) {
        for (int i = 0; i < gOldChars.size(); i++) {
            RndDir *p = dynamic_cast<RndDir *>(
                Hmx::Object::NewObject(DirLoader::GetDirClass(gOldChars[i].c_str()))
            );
            MILO_ASSERT(p, 0x199);
            p->SetProxyFile(gOldChars[i], 0);
            char buf[0x80];
            bs.ReadString(buf, 0x80);
            p->SetName(buf, this);
            p->RndTransformable::Load(bs);
            bool showing;
            bs >> showing;
            float fff;
            bs >> fff;
            if (p) {
                p->SetShowing(showing);
                p->SetOrder(fff);
            }
            bs.ReadString(buf, 0x80);
            if (p && *buf != '\0') {
                p->SetEnv(Find<RndEnviron>(buf, true));
            }
        }
        gOldChars.clear();
    }
    if (gRev < 0x19) {
        if (gRev > 0xA) {
            Transform tf;
            bs >> tf;
        } else if (gRev > 6 && mCam) {
            mCam->RndTransformable::Load(bs);
        }
    }
    if (gRev > 0xB) {
        SyncHides(false);
        bs >> mHideOverrides;
        SyncHides(true);
        SyncBitmaps(false);
        gOldTexDir = gRev > 0xC ? 0 : Dir();
        bs >> mBitmapOverrides;
        SyncBitmaps(true);
    }
    if (gRev > 0xD) {
        SyncMats(false);
        bs >> mMatOverrides;
        SyncMats(true);
    }
    if (gRev > 0xE) {
        SyncPresets(false);
        bs >> mPresetOverrides;
        SyncPresets(true);
    }
    if (gRev > 0xF) {
        SyncCamShots(false);
        mCamShotOverrides.Load(bs, false);
        SyncCamShots(true);
    }
    if (gRev > 0x10 && gRev != 0x17) {
        bs >> mPS3PerPixelHides >> mPS3PerPixelShows;
    }
    if (gRev >= 0x12 && gRev <= 0x15) {
        Symbol s;
        bs >> s;
    }
    if (gRev > 0x12) {
        bs >> mTestPreset1 >> mTestPreset2 >> mTestAnimationTime;
    }
    if (gRev > 0x13)
        bs >> mHud;
    SyncHUD();
}

void WorldDir::SyncObjects() {
    PanelDir::SyncObjects();
    mCameraManager.SyncObjects();
    mPresetManager.SyncObjects();
    mCrowds.clear();
    for (ObjDirItr<WorldCrowd> it(this, true); it; ++it) {
        mCrowds.push_back(it);
    }
    FOREACH (it, mCrowds) {
        (*it)->CleanUpCrowdFloor();
    }
    if (mHud)
        VectorRemove(mDraws, mHud);
    mDrawItr = mDraws.begin();
}

CamShotCrowd *FindCrowd(ObjVector<CamShotCrowd> &vec, WorldCrowd *crowd) {
    FOREACH (it, vec) {
        if (crowd == it->mCrowd)
            return it;
    }
    return vec.end();
}

void WorldDir::SetCrowds(ObjVector<CamShotCrowd> &crowdvec) {
    bool found = false;
    FOREACH (it, mCrowds) {
        WorldCrowd *curWorldCrowd = *it;
        CamShotCrowd *curCrowd = FindCrowd(crowdvec, curWorldCrowd);
        if (curCrowd != crowdvec.end()) {
            found = true;
            curWorldCrowd->SetShowing(true);
            curWorldCrowd->SetCrowdRotate(curCrowd->mCrowdRotate);
        } else {
            curWorldCrowd->SetShowing(false);
        }
    }
    if (!found) {
        FOREACH (it, crowdvec) {
            WorldCrowd *crowd = it->mCrowd;
            if (crowd) {
                MILO_FAIL(
                    "Crowd %s not found in world %s", PathName(crowd), PathName(this)
                );
            }
        }
    }
}

#pragma push
#pragma auto_inline on
void WorldDir::DrawShowing() {
    START_AUTO_TIMER("world_draw");
    if (TheWorld) {
        if (Showing())
            DrawSplitWorld();
    } else {
        SetTheWorld(this);
        CamShot *shot = mCameraManager.MiloCamera();
        if (!shot)
            shot = mCameraManager.CurrentShot();
        if (shot)
            shot = shot->CurrentShot();
        RndCam *cam2 = CamOverride();
        RndCam *cam7 = RndCam::sCurrent;
        if (cam2) {
            cam2->Select();
            cam7 = cam2;
        }
        RndEnviron *env = GetEnv() ? GetEnv() : TheUI.GetEnv();
        env->Select(0);
        if (TheRnd->ProcCmds() & kProcessWorld && shot && !shot->mDrawOverrides.empty()) {
            FOREACH (it, shot->mDrawOverrides) {
                (*it)->DrawShowing();
            }
        }
        if (!shot || shot->mDrawOverrides.empty()) {
            RndDir::DrawShowing();
        }
        if (TheRnd->ProcCmds() & kProcessWorld && shot) {
            Spotlight *spot = shot->GlowSpot();
            if (spot && spot->Showing() && spot->Intensity() > 0) {
                Hmx::Rect rect(0, 0, TheRnd->Width(), TheRnd->Height());
                Hmx::Color color(spot->Color());
                color.alpha = 0.25f;
                TheRnd->DrawRect(rect, color, mGlowMat, 0, 0);
            }
        }
        TheRnd->CopyWorldCam(TheWorld->GetCam());
        TheRnd->EndWorld();
        if (shot) {
            cam7->Select();
            env->Select(0);
            FOREACH (it, shot->mPostProcOverrides) {
                (*it)->DrawShowing();
            }
        }
        if (mFakeHudDir)
            mFakeHudDir->DrawShowing();
        if (mHud && mHud->Showing()) {
            START_AUTO_TIMER("hud_draw");
            mHud->DrawShowing();
        }
        if (TheRnd->ProcCmds() & kProcessPost && SpotlightDrawer::sCurrent) {
            SpotlightDrawer::sCurrent->DeSelect();
        }
        SetTheWorld(0);
    }
}
#pragma pop

bool WorldDir::DrawShowingBudget(float fff) {
    Timer timer;
    timer.Start();
    RndEnvironTracker tracker(mEnv, &WorldXfm().v);
    if (TheRnd->ProcCmds() & kProcessWorld) {
        mDrawItr = mDraws.begin();
    }
    for (; mDrawItr != mDraws.end(); ++mDrawItr) {
        float f1 = kHugeFloat;
        if (TheRnd->ProcCmds() & kProcessWorld) {
            float split = timer.SplitMs() - 0.0f;
            f1 = fff - split;
            if (split > fff || std::fabs(f1) <= 1.0f)
                return false;
        }
        if (!(*mDrawItr)->DrawBudget(f1))
            return false;
    }
    return true;
}

void WorldDir::DrawSplitWorld() {
    static Timer *worldTimer = AutoTimer::GetTimer("world");
    if (!worldTimer || TheRnd->ProcCmds() == kProcessAll) {
        RndDir::DrawShowing();
        return;
    }
    if (TheRnd->LastProcCmds() & kProcessWorld) {
        mLastRndTimeWorld = worldTimer->GetLastMs();
    }
    if (TheRnd->LastProcCmds() & kProcessChar) {
        mLastRndTimeChar = worldTimer->GetLastMs();
    }
    if (TheRnd->ProcCmds() == kProcessPost)
        return;
    float f1 = (mLastRndTimeWorld + mLastRndTimeChar) / 2.0f;
    if (f1 < 1.0f)
        f1 = 5.5f;
    DrawBudget(f1);
}

void WorldDir::SyncHUD() {
    RELEASE(mFakeHudDir);
    if (mShowFakeHud && !mFakeHudFilename.empty()) {
        mFakeHudDir = dynamic_cast<RndDir *>(
            DirLoader::LoadObjects(mFakeHudFilename, nullptr, nullptr)
        );
        if (mFakeHudDir)
            mFakeHudDir->Enter();
    }
}

void WorldDir::SyncHides(bool b) {
    FOREACH (it, mHideOverrides) {
        (*it)->SetShowing(!b);
    }
}

void WorldDir::SyncBitmaps(bool b) {
    FOREACH (it, mBitmapOverrides) {
        it->Sync(b);
    }
}

void WorldDir::SyncMats(bool b) {
    FOREACH (it, mMatOverrides) {
        it->Sync(b);
    }
}

void WorldDir::SyncPresets(bool b) {
    FOREACH (it, mPresetOverrides) {
        it->Sync(b);
    }
}

void WorldDir::SyncCamShots(bool b) {
    FOREACH (it, mCamShotOverrides) {
        (*it)->Disable(b, 1);
    }
}

void WorldDir::BitmapOverride::Sync(bool b) {
    if (!original || !replacement)
        return;
    else if (!b) {
        std::vector<ObjRef *> texrefs;
        {
            MemDoTempAllocations m(true, false);
            texrefs = replacement->Refs();
        }
        std::vector<ObjRef *>::const_reverse_iterator rit = texrefs.rbegin();
        std::vector<ObjRef *>::const_reverse_iterator ritEnd = texrefs.rend();
        while (rit != ritEnd) {
            rit++;
            ObjRef *ref = *rit;
            if (ref->RefOwner()->Dir() != replacement->Dir()) {
                ref->Replace(replacement, original);
            }
        }
    } else {
        std::vector<ObjRef *> texrefs;
        {
            MemDoTempAllocations m(true, false);
            texrefs = replacement->Refs();
        }
        std::vector<ObjRef *>::const_reverse_iterator rit = texrefs.rbegin();
        std::vector<ObjRef *>::const_reverse_iterator ritEnd = texrefs.rend();
        while (rit != ritEnd) {
            rit++;
            ObjRef *ref = *rit;
            if (ref->RefOwner() && ref->RefOwner()->Dir() != replacement->Dir()) {
                ref->Replace(original, replacement);
            }
        }
    }
}

void WorldDir::MatOverride::Sync(bool b) {
    if (!mat || !mesh)
        return;
    else if (!b) {
        if (mat2)
            mesh->SetMat(mat2);
    } else {
        mat2 = mesh->Mat();
        mesh->SetMat(mat);
    }
}

void WorldDir::PresetOverride::Sync(bool b) {
    if (preset) {
        LightHue *thehue;
        if (b)
            thehue = hue;
        else
            thehue = 0;
        preset->SetHue(thehue);
    }
}

BEGIN_HANDLERS(WorldDir)
    HANDLE_LOG_IF(mEchoMsgs, "World msg: %s\n", sym)
    HANDLE_MEMBER_PTR((&mCameraManager)) // ???
    HANDLE_MEMBER_PTR((&mPresetManager)) // ???
    HANDLE_SUPERCLASS(PanelDir)
    HANDLE_CHECK(0x3CB)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(WorldDir::PresetOverride)
    {
        static Symbol _s("preset");
        if (sym == _s) {
            if (!(_op & (kPropSize | kPropGet)))
                o.Sync(false);
            bool synced = PropSync(o.preset, _val, _prop, _i + 1, _op);
            if (synced) {
                if (!(_op & (kPropSize | kPropGet)))
                    o.Sync(true);
                return true;
            } else
                return false;
        }
    }
    {
        static Symbol _s("hue");
        if (sym == _s) {
            if (!(_op & (kPropSize | kPropGet)))
                o.Sync(false);
            bool synced = PropSync(o.hue, _val, _prop, _i + 1, _op);
            if (synced) {
                if (!(_op & (kPropSize | kPropGet)))
                    o.Sync(true);
                return true;
            } else
                return false;
        }
    }
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(WorldDir::BitmapOverride)
    {
        static Symbol _s("original");
        if (sym == _s) {
            if (!(_op & (kPropSize | kPropGet)))
                o.Sync(false);
            bool synced = PropSync(o.original, _val, _prop, _i + 1, _op);
            if (synced) {
                if (!(_op & (kPropSize | kPropGet)))
                    o.Sync(true);
                return true;
            } else
                return false;
        }
    }
    {
        static Symbol _s("replacement");
        if (sym == _s) {
            if (!(_op & (kPropSize | kPropGet)))
                o.Sync(false);
            bool synced = PropSync(o.replacement, _val, _prop, _i + 1, _op);
            if (synced) {
                if (!(_op & (kPropSize | kPropGet)))
                    o.Sync(true);
                return true;
            } else
                return false;
        }
    }
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(WorldDir::MatOverride)
    {
        static Symbol _s("mesh");
        if (sym == _s) {
            if (!(_op & (kPropSize | kPropGet)))
                o.Sync(false);
            bool synced = PropSync(o.mesh, _val, _prop, _i + 1, _op);
            if (synced) {
                if (!(_op & (kPropSize | kPropGet)))
                    o.Sync(true);
                return true;
            } else
                return false;
        }
    }
    {
        static Symbol _s("mat");
        if (sym == _s) {
            if (!(_op & (kPropSize | kPropGet)))
                o.Sync(false);
            bool synced = PropSync(o.mat, _val, _prop, _i + 1, _op);
            if (synced) {
                if (!(_op & (kPropSize | kPropGet)))
                    o.Sync(true);
                return true;
            } else
                return false;
        }
    }
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(WorldDir)
    SYNC_PROP_MODIFY_ALT(hud_filename, mFakeHudFilename, SyncHUD())
    SYNC_PROP_MODIFY(show_hud, mShowFakeHud, SyncHUD())
    SYNC_PROP(echo_msgs, mEchoMsgs) {
        static Symbol _s("hide_overrides");
        if (sym == _s) {
            if (!(_op & (kPropSize | kPropGet)))
                SyncHides(false);
            bool synced = PropSync(mHideOverrides, _val, _prop, _i + 1, _op);
            if (synced) {
                if (!(_op & (kPropSize | kPropGet)))
                    SyncHides(true);
                return true;
            } else
                return false;
        }
    }
    SYNC_PROP(bitmap_overrides, mBitmapOverrides)
    SYNC_PROP(mat_overrides, mMatOverrides)
    SYNC_PROP(preset_overrides, mPresetOverrides) {
        static Symbol _s("camshot_overrides");
        if (sym == _s) {
            if (!(_op & (kPropSize | kPropGet)))
                SyncCamShots(false);
            bool synced = PropSync(mCamShotOverrides, _val, _prop, _i + 1, _op);
            if (synced) {
                if (!(_op & (kPropSize | kPropGet)))
                    SyncCamShots(true);
                return true;
            } else
                return false;
        }
    }
    SYNC_PROP(ps3_per_pixel_hides, mPS3PerPixelHides)
    SYNC_PROP(ps3_per_pixel_shows, mPS3PerPixelShows)
    SYNC_PROP(test_light_preset_1, mTestPreset1)
    SYNC_PROP(test_light_preset_2, mTestPreset2)
    SYNC_PROP(test_animation_time, mTestAnimationTime)
    SYNC_PROP_MODIFY_ALT(hud, mHud, SyncObjects())
    SYNC_SUPERCLASS(PanelDir)
END_PROPSYNCS
