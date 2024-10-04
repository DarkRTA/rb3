#include "bandobj/GemTrackDir.h"
#include "bandobj/BandButton.h"
#include "bandobj/GemTrackResourceManager.h"
#include "obj/ObjVersion.h"
#include "math/Rand.h"
#include "beatmatch/RGUtl.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(GemTrackDir)
bool kKeyShifting = true;

#pragma push
#pragma dont_inline on
GemTrackDir::GemTrackDir() : BandTrack(this), mNumTracks(1), unk488(-1), mGemTrackDirID(-1), mKickPassCounter(0), unk494(0), mStreakMeterOffset(2.25f), mStreakMeterTilt(0), mTrackPitch(0),
    mEffectSelector(this, 0), mRotater(this, 0), mSurfaceTexture(this, 0), mSurfaceMesh(this, 0), mSurfaceMat(this, 0), mTrackEnv(this, 0), mTrackMissGemsEnv(this, 0), mGameCam(this, 0),
    mPeakStateOnTrig(this, 0), mPeakStateOffTrig(this, 0), mPeakStopImmediateTrig(this, 0), mBassSuperStreakOnTrig(this, 0), mBassSuperStreakOffTrig(this, 0), mBassSSOffImmediateTrig(this, 0), mKickDrummerTrig(this, 0),
    mKickDrummerResetTrig(this, 0), mSpotlightPhraseSuccessTrig(this, 0), mDrumFillResetTrig(this, 0), mDrumMash2ndPassActivateAnim(this, 0), mDrumMashHitAnimGrp(this, 0),
    mFillColorsGrp(this, 0), mLodAnim(this, 0), mSmasherPlate(this, 0), mGlowWidgets(this, kObjListNoNull), unk600(this, 0), unk60c(this, 0), unk618(this, 0),
    unk624(this, 0), mGemWhiteMesh(this, 0), mMissOutofRangeRightTrig(this, 0), mMissOutofRangeLeftTrig(this, 0), unk654(this, 0), mKeysShiftAnim(this, 0), mKeysMashAnim(this, 0), mKeyRange(-1.0f), mKeyOffset(-1.0f),
    mFingerShape(0), mChordLabelPosOffset(0), mChordShapeGen(this, 0), mArpShapePool(0), unk6e8(0)
#ifdef MILO_DEBUG
    , mFakeFingerShape(0), mCycleFakeFingerShapes(0), mRandomShapeFrameCount(0x96)
#endif
{
    ObjPtr<RndPropAnim, ObjectDir> propAnim(this, 0);
    ObjPtr<EventTrigger, ObjectDir> trig(this, 0);
    for(int i = 0; i < 6; i++){
        mGemMashAnims.push_back(propAnim);
        mDrumMashAnims.push_back(propAnim);
        mFillLaneAnims.push_back(propAnim);
        mRealGuitarMashAnims.push_back(propAnim);
        mDrumRollTrigs.push_back(std::make_pair(trig, trig));
        mTrillTrigs.push_back(std::make_pair(trig, trig));
    }
    for(int i = 0; i < 3; i++){
        mFillHitTrigs.push_back(trig);
    }
    for(int i = 0; i < 5; i++){
        mFretPosOffsets.push_back(0);
    }
#ifdef MILO_DEBUG
    DataArray* cfg = SystemConfig();
    DataArray* arr = cfg->FindArray("fake_finger_shape", false);
    if(arr){
        for(int i = 0; i < 6; i++){
            mRGState.FretDown(i, arr->Int(i + 1));
        }
        mFakeFingerShape = true;
        if(arr->Size() > 7) mCycleFakeFingerShapes = arr->Int(7);
    }
#endif
}

GemTrackDir::~GemTrackDir(){
    RELEASE(mArpShapePool);
    RELEASE(mFingerShape);
}
#pragma pop

BEGIN_COPYS(GemTrackDir)
    COPY_SUPERCLASS(TrackDir)
    CREATE_COPY(GemTrackDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mNumTracks)
        COPY_MEMBER(mSurfaceTexture)
        COPY_MEMBER(mSurfaceMesh)
        COPY_MEMBER(mEffectSelector)
        COPY_MEMBER(mSurfaceMat)
        COPY_MEMBER(mTrackEnv)
        COPY_MEMBER(mTrackMissGemsEnv)
        COPY_MEMBER(mGameCam)
        COPY_MEMBER(mPeakStateOnTrig)
        COPY_MEMBER(mPeakStateOffTrig)
        COPY_MEMBER(mBassSuperStreakOnTrig)
        COPY_MEMBER(mBassSuperStreakOffTrig)
        COPY_MEMBER(mKickDrummerTrig)
        COPY_MEMBER(mKickDrummerResetTrig)
        COPY_MEMBER(mSpotlightPhraseSuccessTrig)
        COPY_MEMBER(mGemMashAnims)
        COPY_MEMBER(mDrumMashAnims)
        COPY_MEMBER(mFillLaneAnims)
        COPY_MEMBER(mRealGuitarMashAnims)
        COPY_MEMBER(mFillHitTrigs)
        COPY_MEMBER(mDrumFillResetTrig)
        COPY_MEMBER(mDrumMash2ndPassActivateAnim)
        COPY_MEMBER(mDrumMashHitAnimGrp)
        COPY_MEMBER(mFillColorsGrp)
        COPY_MEMBER(mLodAnim)
        COPY_MEMBER(mGlowWidgets)
        COPY_MEMBER(mStreakMeterOffset)
        COPY_MEMBER(mStreakMeterTilt)
        COPY_MEMBER(mFretPosOffsets)
        COPY_MEMBER(mChordLabelPosOffset)
        CopyTrack(c);
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(GemTrackDir, 0xBC)

#ifdef MILO_DEBUG
DECOMP_FORCEACTIVE(GemTrackDir, "ObjPtr_p.h", "f.Owner()", "")
#else
DECOMP_FORCEACTIVE(GemTrackDir, "")
#endif

BEGIN_LOADS(GemTrackDir)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void GemTrackDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0xC, 0);
    if(gRev < 9){
        int i68 = 0;
        bs >> i68;
        bs >> mEffectSelector;
        if(gRev < 1){
            if(gLoadingProxyFromDisk){
                ObjPtr<RndTex, ObjectDir> tex(0, 0);
                bs >> tex;
            }
            else bs >> mSurfaceTexture;
        }
    }
    if(!IsProxy()){
        if(gRev >= 9) bs >> mEffectSelector;
        bs >> mSurfaceMesh;
        bs >> mSurfaceMat;
        bs >> mTrackEnv;
        bs >> mGameCam;
        bs >> mBassSuperStreakOnTrig;
        bs >> mBassSuperStreakOffTrig;
        bs >> mKickDrummerTrig;
        bs >> mSpotlightPhraseSuccessTrig;
        if(gRev < 0xC){
            ObjPtr<EventTrigger, ObjectDir> trig(this, 0);
            bs >> trig;
        }
        bs >> mDrumFillResetTrig;
        bs >> mDrumMash2ndPassActivateAnim;
        bs >> mDrumMashHitAnimGrp;
        bs >> mFillColorsGrp;
        bs >> mLodAnim;
        bs >> mRotater;
        bs >> mGlowWidgets;

        for(int i = 0; i < 5; i++){
            bs >> mGemMashAnims[i];
        }

        if(gRev >= 6 && gRev <= 10){
            ObjPtr<RndAnimatable, ObjectDir> anim(this, 0);
            bs >> anim;
        }

        for(int i = 1; i < 5; i++){
            bs >> mDrumMashAnims[i];
        }
        for(int i = 0; i < 3; i++){
            bs >> mFillHitTrigs[i];
        }
        if(gRev >= 11){
            for(int i = 0; i < 6; i++){
                bs >> mRealGuitarMashAnims[i];
            }
        }
        if(gRev >= 2) bs >> mStreakMeterOffset;
        if(gRev >= 3) bs >> mStreakMeterTilt;
        if(gRev >= 4){
            int oldsize = mFretPosOffsets.size();
            bs >> mFretPosOffsets;
            while(mFretPosOffsets.size() < oldsize){
                mFretPosOffsets.push_back(0);
            }
            while(mFretPosOffsets.size() > oldsize){
                mFretPosOffsets.pop_back();
            }
        }
        if(gRev >= 5) bs >> mKickDrummerResetTrig;
        if(gRev >= 7) bs >> mChordLabelPosOffset;
        if(gRev >= 8){
            if(gRev < 10){
                ObjPtr<EventTrigger, ObjectDir> trig(this, 0);
                bs >> trig;
                bs >> trig;
            }
            bs >> mPeakStateOnTrig;
            bs >> mPeakStateOffTrig;
        }
        if(gRev >= 12){
            for(int i = 1; i < 5; i++){
                bs >> mFillLaneAnims[i];
            }
        }
    }
    LoadTrack(bs, IsProxy(), gLoadingProxyFromDisk, false);
    PushRev(packRevs(gAltRev, gRev), this);
    TrackDir::PreLoad(bs);
}

void GemTrackDir::PostLoad(BinStream& bs){
    TrackDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
}

void GemTrackDir::SyncFingerFeedback(){
    RndDir* outlinedir = Find<RndDir>("chord_shape_outline", true);
    if(!mFingerShape) mFingerShape = new FingerShape(outlinedir);
}

void GemTrackDir::SyncObjects(){
    TrackDir::SyncObjects();
    if(!mBeatAnimsGrp) mBeatAnimsGrp = Find<RndGroup>("beat_anims.grp", false);
    if(!mPeakStopImmediateTrig) mPeakStopImmediateTrig = Find<EventTrigger>("peak_stop_immediate.trig", false);
    if(!mBassSSOffImmediateTrig) mBassSSOffImmediateTrig = Find<EventTrigger>("BassSuperStreak_OFF_immediate.trig", false);
    if(!mTrackMissGemsEnv) mTrackMissGemsEnv = Find<RndEnviron>("track_miss_gems.env", false);
    if(!mGemWhiteMesh) mGemWhiteMesh = Find<RndMesh>("gem_white.mesh", false);
    if(!mMissOutofRangeRightTrig) mMissOutofRangeRightTrig = Find<EventTrigger>("miss_outofrange_right.trig", false);
    if(!mMissOutofRangeLeftTrig) mMissOutofRangeLeftTrig = Find<EventTrigger>("miss_outofrange_left.trig", false);
    if(!mKeysMashAnim) mKeysMashAnim = Find<RndPropAnim>("keys_mash.anim", false);
    if(!mUnisonIcon) mUnisonIcon = Find<UnisonIcon>("unison_icon", false);
    if(!mDrumRollTrigs[1].first) mDrumRollTrigs[1].first = Find<EventTrigger>("drum_roll_start1.trig", false);
    if(!mDrumRollTrigs[1].second) mDrumRollTrigs[1].second = Find<EventTrigger>("drum_roll_stop1.trig", false);
    if(!mDrumRollTrigs[2].first) mDrumRollTrigs[2].first = Find<EventTrigger>("drum_roll_start2.trig", false);
    if(!mDrumRollTrigs[2].second) mDrumRollTrigs[2].second = Find<EventTrigger>("drum_roll_stop2.trig", false);
    if(!mDrumRollTrigs[3].first) mDrumRollTrigs[3].first = Find<EventTrigger>("drum_roll_start3.trig", false);
    if(!mDrumRollTrigs[3].second) mDrumRollTrigs[3].second = Find<EventTrigger>("drum_roll_stop3.trig", false);
    if(!mDrumRollTrigs[4].first) mDrumRollTrigs[4].first = Find<EventTrigger>("drum_roll_start4.trig", false);
    if(!mDrumRollTrigs[4].second) mDrumRollTrigs[4].second = Find<EventTrigger>("drum_roll_stop4.trig", false);
    if(!mTrillTrigs[0].first) mTrillTrigs[0].first = Find<EventTrigger>("trill_start0.trig", false);
    if(!mTrillTrigs[0].second) mTrillTrigs[0].second = Find<EventTrigger>("trill_stop0.trig", false);
    if(!mTrillTrigs[1].first) mTrillTrigs[1].first = Find<EventTrigger>("trill_start1.trig", false);
    if(!mTrillTrigs[1].second) mTrillTrigs[1].second = Find<EventTrigger>("trill_stop1.trig", false);
    if(!mTrillTrigs[2].first) mTrillTrigs[2].first = Find<EventTrigger>("trill_start2.trig", false);
    if(!mTrillTrigs[2].second) mTrillTrigs[2].second = Find<EventTrigger>("trill_stop2.trig", false);
    if(!mTrillTrigs[3].first) mTrillTrigs[3].first = Find<EventTrigger>("trill_start3.trig", false);
    if(!mTrillTrigs[3].second) mTrillTrigs[3].second = Find<EventTrigger>("trill_stop3.trig", false);
    if(!mTrillTrigs[4].first) mTrillTrigs[4].first = Find<EventTrigger>("trill_start4.trig", false);
    if(!mTrillTrigs[4].second) mTrillTrigs[4].second = Find<EventTrigger>("trill_stop4.trig", false);
    if(!mTrillTrigs[5].first) mTrillTrigs[5].first = Find<EventTrigger>("trill_start4.trig", false);
    if(!mTrillTrigs[5].second) mTrillTrigs[5].second = Find<EventTrigger>("trill_stop4.trig", false);
    if(!mKeysShiftAnim) mKeysShiftAnim = Find<RndAnimatable>("keys_shift.anim", false);
    if(!mChordShapeGen) mChordShapeGen = Find<RndDir>("RG_chord_generator", true)->Find<ChordShapeGenerator>("ChordShapeGenerator01", true);
    bool b1 = true;
    if(mTrackInstrument != kInstRealBass && mTrackInstrument != kInstRealGuitar) b1 = false;
    if(!mFingerShape && b1){
        SyncFingerFeedback();
        RndDir* outlinedir = Find<RndDir>("chord_shape_outline", true);
        RndGroup* outline = outlinedir->Find<RndGroup>("outline.grp", true);
        RndGroup* smash = Find<RndGroup>("rg_smasher_glow.grp", true);
        for(int i = 0; i < 6; i++){
            RndMesh* mesh = outlinedir->Find<RndMesh>(MakeString("gem_smasher_glow_%d.mesh", i), true);
            outline->RemoveObject(mesh);
            smash->AddObject(mesh, 0);
        }
    }
    if(!mArpShapePool && b1){
        ObjectDir* arpdir = Find<ObjectDir>("arpeggio_source", true);
        RndGroup* shapesgrp = Find<RndGroup>("arpeggio_shapes.grp", true);
        mArpShapePool = new ArpeggioShapePool(arpdir, shapesgrp, 15);
    }
}

void GemTrackDir::Poll(){
    TrackDir::Poll();
    if(mSmasherPlate) mSmasherPlate->Poll();
}

void GemTrackDir::SetPitch(float pitch){
    if(TheLoadMgr.EditMode() || mTrackPitch != pitch){
        mTrackPitch = pitch;
        Hmx::Matrix3 mtx;
        Vector3 v;
        MakeEuler(mRotater->LocalXfm().m, v);
        v.x = pitch * DEG2RAD;
        MakeRotMatrix(v, mtx, true);
        mRotater->SetLocalRot(mtx);
        mStreakMeter->SetPitch(pitch + 90.0f + mStreakMeterTilt);
        // Clamp(5.0f, 2.0f, -(pitch + 30.0f));
        RndGroup* grp = Find<RndGroup>("streak.grp", true);
        float sined = std::sin((-pitch + 30.0f) * DEG2RAD);
        Vector3 v58(grp->mLocalXfm.v);
        v58.y = -mStreakMeterOffset / sined;
        grp->SetLocalPos(v58);
    }
}

void GemTrackDir::SetFade(float f1, float f2){
    float frange = f1 + f2;
    if(mTrackEnv){
        RndPropAnim* anim = Find<RndPropAnim>("intro_fade.anim", true);
        anim->SetFrame(10.0f, 1.0f);
        mTrackEnv->SetFadeRange(f1, frange);
        anim->SetKey(10.0f);
    }
    if(GetCam()){
        GetCam()->SetFrustum(GetCam()->mNearPlane, frange, GetCam()->mYFov, 1.0f);
    }
}

void GemTrackDir::SetFOV(float fov){
    RndCam* cam = GetCam();
    if(cam){
        cam->SetFrustum(cam->mNearPlane, cam->mFarPlane, fov * DEG2RAD, 1.0f);
    }
}

void GemTrackDir::SetCamPos(float x, float y, float z){
    if(GetCam()){
        GetCam()->SetLocalPos(x, y, z);
    }
}

void GemTrackDir::UpdateSurfaceTexture(){
    if(mSurfaceMat && mSurfaceTexture){
        mSurfaceMat->SetDiffuseTex(mSurfaceTexture);
    }
}

void GemTrackDir::OnUpdateFx(int fx){
    delete unk600;
    if(mEffectSelector && (mTrackInstrument == kInstBass || mTrackInstrument == kInstGuitar)){
        mEffectSelector->SetShowing(true);
        for(int i = 0; i < 5; i++){
            BandButton* btn = mEffectSelector->Find<BandButton>(MakeString("guitar_fx_%1d.btn", i), false);
            if(btn) btn->SetState((UIComponent::State)(i == fx));
        }
        static Message hide("set_showing", 0);
        unk600 = new MessageTask(mEffectSelector, hide);
        TheTaskMgr.Start(unk600, kTaskUISeconds, 1.0f);
    }
}

void GemTrackDir::PlayIntro(){
    mResetTrig->Trigger();
    BandTrack::PlayIntro();
    if(!BandTrack::mParent || (!BandTrack::mParent->PlayerDisconnected() && !BandTrack::mParent->FailedAtStart())){
        bool b2 = false;
        if(BandTrack::mParent){
            if(!BandTrack::mParent->InGameMode(h2h)) b2 = true;
        }
        float f1;
        if(b2) f1 = mTrackIdx / 4.0f + 0.05f;
        else f1 = 0.55f;

        unk624 = new MessageTask(mIntroTrig, trigger_msg);
        TheTaskMgr.Start(unk624, kTaskUISeconds, f1);
    }
    if(BandTrack::mParent) BandTrack::mParent->PlayKeyIntros();
}

void GemTrackDir::TrackReset(){
    UpdateSurfaceTexture();
    ClearAllWidgets();
    if(BandTrack::mParent) BandTrack::mParent->RebuildBeats();
    ResetSmashers(true);
    if(BandTrack::mParent) BandTrack::mParent->UpdateGems();
    RndPropAnim* anim = Find<RndPropAnim>("instrument_setup.anim", false);
    if(anim) anim->SetFrame(mTrackInstrument, 1.0f);
    ResetEffectSelector();
    if(!BandTrack::mParent || !BandTrack::mParent->FailedAtStart()){
        EnablePlayer();
    }
    mKickPassCounter = 0;
    unk494 = 0;
}

void GemTrackDir::SetupSmasherPlate(){
    if(mSmasherPlate) MILO_FAIL("Trying to acquire a new smasher plate when we already have one!");
    GemTrackResourceManager* mgr = MyTrackPanelDir()->GetGemTrackResourceManager();
    if(!mgr) MILO_WARN("GemTrackResourceManager not available!");
    else {
        mSmasherPlate = mgr->GetFreeSmasherPlate(mTrackInstrument);
        if(mSmasherPlate){
            RndGroup* smashergrp = Find<RndGroup>("smashers.grp", true);
            RndGroup* keygrp = Find<RndGroup>("key_shift_stationary_middle.grp", true);
            if(mTrackInstrument == kInstRealKeys) keygrp->AddObject(mSmasherPlate, 0);
            else smashergrp->AddObject(mSmasherPlate, 0);
            if(!TheLoadMgr.EditMode() || IsProxy()){
                RndGroup* grptoadd = mTrackInstrument == kInstRealKeys ? Find<RndGroup>("key_shift_stationary_front.grp", true) : Find<RndGroup>("smasher_fx.grp", true);
                RndGroup* after = mSmasherPlate->Find<RndGroup>("after_gems.grp", false);
                if(after) after->AddObject(grptoadd, 0);
                RndGroup* keysback = Find<RndGroup>("key_shift_stationary_back.grp", true);
                RndGroup* keylanes = mSmasherPlate->Find<RndGroup>("key_lanes.grp", false);
                if(keylanes) keysback->AddObject(keylanes, 0);
                RndGroup* afterhide = mSmasherPlate->Find<RndGroup>("after_hide.grp", false);
                if(afterhide) afterhide->SetShowing(false);
            }
            if(mTrackInstrument == kInstRealKeys){
                unk654 = mSmasherPlate->Find<RndAnimatable>("shift.anim", true);
                unk680.clear();
                unk688.clear();
                unk690.clear();
                DataArray* proparr = mSmasherPlate->Property(smasher_list, true)->Array(0);
                for(int i = 0; i < proparr->Size(); i++){
                    RndDir* curdir = proparr->Obj<RndDir>(i);
                    unk680.push_back(curdir);
                    unk688.push_back(curdir->Find<EventTrigger>("show.trig", true));
                    unk690.push_back(curdir->Find<EventTrigger>("hide.trig", true));
                }
                SetupKeyShifting(mSmasherPlate);
            }
            mSmasherPlate->HandleType(reset_msg);
        }
    }
}

void GemTrackDir::ReleaseSmasherPlate(){
    if(mSmasherPlate){
        GemTrackResourceManager* mgr = MyTrackPanelDir()->GetGemTrackResourceManager();
        if(!mgr) MILO_WARN("GemTrackResourceManager not available!");
        else {
            RndGroup* smashergrp = Find<RndGroup>("smashers.grp", true);
            RndGroup* keygrp = Find<RndGroup>("key_shift_stationary_middle.grp", true);
            if(!TheLoadMgr.EditMode() || IsProxy()){
                RndGroup* smashgrp = Find<RndGroup>("smasher_fx.grp", true);
                RndGroup* keyfrontgrp = Find<RndGroup>("key_shift_stationary_front.grp", true);
                RndGroup* after = mSmasherPlate->Find<RndGroup>("after_gems.grp", false);
                if(after){
                    smashgrp->RemoveObject(after);
                    keyfrontgrp->RemoveObject(after);
                }
                RndGroup* keysback = Find<RndGroup>("key_shift_stationary_back.grp", true);
                RndGroup* keylanes = mSmasherPlate->Find<RndGroup>("key_lanes.grp", false);
                if(keylanes) keysback->RemoveObject(keylanes);
            }
            smashergrp->RemoveObject(mSmasherPlate);
            keygrp->RemoveObject(mSmasherPlate);
            mgr->ReleaseSmasherPlate(mSmasherPlate);
            ResetKeyShifting();
            mSmasherPlate = 0;
        }
    }
}

void GemTrackDir::ResetSmashers(bool b){
    if(BandTrack::mParent){
        BandTrack::mParent->ResetSmashers(reset_particles_msg);
    }
    mKickDrummerTrig->BasicReset();
    mKickDrummerResetTrig->Trigger();
    if(mFingerShape) mFingerShape->Reset(true);
}

void GemTrackDir::ResetEffectSelector(){
    if(mEffectSelector){
        mEffectSelector->SetShowing(false);
        if(!TheLoadMgr.EditMode()){
            DataArray* cfg = SystemConfig("track_graphics", "effects");
            DataArray* instarr = cfg->FindArray(mInstrument, false);
            if(instarr){
                for(int i = 0; i < 5; i++){
                    BandButton* btn = mEffectSelector->Find<BandButton>(MakeString("guitar_fx_%1d.btn", i), true);
                    btn->SetTextToken(instarr->Sym(i + 1));
                }
            }
        }
    }
}

void GemTrackDir::SetupInstrument(){
    RndPropAnim* anim = Find<RndPropAnim>("instrument_setup.anim", false);
    if(anim){
        if(mInstrument == "bass") anim->SetFrame(0, 1.0f);
        else if(mInstrument == "drum") anim->SetFrame(1.0f, 1.0f);
        else if(mInstrument == "guitar" || mInstrument == "keys") anim->SetFrame(2.0f, 1.0f);
        else if(mInstrument == "real_keys") anim->SetFrame(7.0f, 1.0f);
        else if(mInstrument == "real_guitar" || mInstrument == "real_bass") anim->SetFrame(5.0f, 1.0f);
        else MILO_ASSERT(0, 0x35F);
    }
}

bool GemTrackDir::IsActiveInSession() const { return mInUse; }

void GemTrackDir::GameWon(){
    Find<EventTrigger>("win_retract.trig", true)->Trigger();
    BandTrack::GameWon();
}

void GemTrackDir::Extend(bool b){
    Reset();
    RndGroup* grp = Find<RndGroup>("intro_anim.grp", false);
    if(grp){
        if(b) grp->SetFrame(grp->EndFrame(), 1.0f);
        else grp->Animate(grp->StartFrame(), grp->EndFrame(), grp->Units(), 0, 0);
    }
    TrackWidget* widget = Find<TrackWidget>("guitar_solo_mask.wid", false);
    if(widget) widget->Clear();
}

void GemTrackDir::Retract(bool b){
    BandTrack::Retract(b);
    if(unk624) delete unk624;
    if(!b){
        unk60c = new MessageTask(this, clear_all_msg);
        TheTaskMgr.Start(unk60c, kTaskSeconds, 1.0f);
    }
    else {
        RndGroup* grp = Find<RndGroup>("intro_anim.grp", false);
        if(grp) grp->SetFrame(grp->StartFrame(), 1.0f);
    }
    if(mEffectSelector) mEffectSelector->SetShowing(false);
}

void GemTrackDir::SetStreak(int i1, int i2, int i3, bool b){
    BandTrack::SetStreak(i1, i2, i3, b);
    if(mStreakMeter){
        float f1 = 1.0f;
        if(i2 < unk14){
            if(i1 == 0 || i1 % i3){
                f1 = (i1 % i3) / (float)i3;
            }
        }
        mStreakMeter->SetWipe(f1);
    }
}

void GemTrackDir::RefreshStreakMeter(int i1, int i2, int i3){
    BandTrack::RefreshStreakMeter(i1, i2, i3);
    if(mStreakMeter){
        float f38 = 1.0f;
        if(i2 < unk14){
            if(i1 == 0 || i1 % i3){
                f38 = (i1 % i3) / (float)i3;
            }
        }
        Message msg("set_wipe", f38);
        TheTaskMgr.Start(new MessageTask(mStreakMeter, msg), kTaskSeconds, 0.01f);
    }
}

void GemTrackDir::PeakState(bool b1, bool b2){
    if(b1 != unk1a){
        if(b1) mPeakStateOnTrig->Trigger();
        else if(b2 && mPeakStopImmediateTrig) mPeakStopImmediateTrig->Trigger();
        else mPeakStateOffTrig->Trigger();
    }
    BandTrack::PeakState(b1, b2);
}

void GemTrackDir::SuperStreak(bool b1, bool b2){
    if(b1 != unk19){
        if(b1) mBassSuperStreakOnTrig->Trigger();
        else if(b2 && mBassSSOffImmediateTrig) mBassSSOffImmediateTrig->Trigger();
        else mBassSuperStreakOffTrig->Trigger();
        Message msg(b1 ? "start_super_streak" : "end_super_streak");
        if(mPlayerFeedback && !unk1e && !b2){
            mPlayerFeedback->Handle(msg, true);
        }
    }
    BandTrack::SuperStreak(b1, b2);
}

void GemTrackDir::Deploy(){
    BandTrack::Deploy();
    if(mTrackInstrument == kInstDrum && BandTrack::mParent){
        unk618 = new MessageTask(BandTrack::mParent, update_gems_msg);
        TheTaskMgr.Start(unk618, kTaskSeconds, 0.0f);
    }
}

void GemTrackDir::EnterCoda(){
    BandTrack::EnterCoda();
    if(mPlayerFeedback){
        mPlayerFeedback->HandleType(reset_msg);
    }
    if(BandTrack::mParent){
        DataNode* prop = FindObject("gamemode", true)->Property("is_practice", true);
        if(!prop){
            BandTrack::mParent->SetGemsEnabled(TheTaskMgr.Seconds(TaskMgr::b) * 1000.0f);
        }
    }
}

void GemTrackDir::DisablePlayer(int i){
    if(!mDisabled && MyTrackPanelDir()){
        MyTrackPanelDir()->UnisonEnd();
    }
    if(unk624) delete unk624;
    BandTrack::DisablePlayer(i);
}

DECOMP_FORCEACTIVE(GemTrackDir, "drum_fill.mesh", "guitar_fill.mesh", "unison_mask.mesh", "guitar_solo_mask.mesh", "bar_blue_beat.wid")

void GemTrackDir::GemPass(int i1, int i2){
    unk494++;
    if((i2 & 1U) && mTrackInstrument == kInstDrum){
        TrackInterface* par = BandTrack::mParent;
        if(par){
            mKickPassCounter++;
            if(mKickPassCounter >= 8){
                float kickms = par->NextKickNoteMs();
                if(mKickPassCounter == 8){
                    if(kickms > 5000.0f) mKickPassCounter = 7;
                    else PopupHelp("kick", true);
                }
                else if(kickms > 5000.0f){
                    PopupHelp("kick", false);
                    mKickPassCounter = 7;
                }
            }
        }
    }
}

void GemTrackDir::GemHit(int i){
    unk494 = 0;
    if(mTrackInstrument != kInstDrum) return;
    if(!(i & 1U)) return;
    mKickPassCounter = 0;
}

void GemTrackDir::SeeKick(){
    if(mPopupObject) mPopupObject->Handle(kick_note_msg, true);
}

void GemTrackDir::KickSwing(){
    PopupHelp("kick", false);
    mKickPassCounter = 0;
}

void GemTrackDir::SpotlightPhraseSuccess(){
    mSpotlightPhraseSuccessTrig->Trigger();
    BandTrack::SpotlightPhraseSuccess();
}

void GemTrackDir::SetPerformanceMode(bool b){
    SetShowing(!b);
    BandTrack::SetPerformanceMode(b);
}

void GemTrackDir::Mash(int slot){
    RndAnimatable* anim;
    if(mTrackInstrument != kInstDrum || (slot != 0)){
        if(mTrackInstrument == kInstDrum){
            if(BandTrack::mParent && BandTrack::mParent->Lefty()){
                slot = 5 - slot;
            }
            MILO_ASSERT((slot > 0) && (slot < mDrumMashAnims.size()), 0x479);
            anim = mDrumMashAnims[slot];
        }
        else if(mTrackInstrument == kInstRealGuitar || mTrackInstrument == kInstRealBass){
            MILO_ASSERT(slot < mRealGuitarMashAnims.size(), 0x47F);
            anim = mRealGuitarMashAnims[slot];
        }
        else if(mTrackInstrument == kInstRealKeys) anim = mKeysMashAnim;
        else {
            MILO_ASSERT(slot < mGemMashAnims.size(), 0x488);
            anim = mGemMashAnims[slot];
        }
        anim->Animate(0, false, 0);
    }
}

void GemTrackDir::FillMash(int slot){
    MILO_ASSERT(mTrackInstrument == kInstDrum, 0x491);
    if(slot != 0){
        if(BandTrack::mParent && BandTrack::mParent->Lefty()){
            slot = 5 - slot;
        }
        MILO_ASSERT((slot > 0) && (slot < mFillLaneAnims.size()), 0x49B);
        mFillLaneAnims[slot]->Animate(0, false, 0);
    }
}

void GemTrackDir::FillHit(int numNotes){
    if(numNotes <= mFillHitTrigs.size()){
        MILO_ASSERT(numNotes > 0, 0x4A4);
        if(numNotes > 0) mFillHitTrigs[numNotes - 1]->Trigger();
    }
}

void GemTrackDir::ResetDrumFill(){
    mDrumFillResetTrig->Trigger();
    float delay = 1.0f - (std::floor(TheTaskMgr.Beat()) - TheTaskMgr.Beat()) - 0.2f;
    if(mDrumMash2ndPassActivateAnim){
        if(delay < 0.0f) delay += 1.0f;
        mDrumMash2ndPassActivateAnim->Animate(0, true, delay, mDrumMash2ndPassActivateAnim->GetRate(), 0.0f, 1.0f, 0.0f, 1.0f, loop);
    }
}

void GemTrackDir::ResetCoda(){
    mDrumMashHitAnimGrp->SetFrame(mDrumMashHitAnimGrp->EndFrame(), 1.0f);
    mFillColorsGrp->SetFrame(mFillColorsGrp->EndFrame(), 1.0f);
}

void GemTrackDir::CrashFill(){
    if(BandTrack::mParent){
        BandTrack::mParent->GetSmasher(4)->Handle(drum_fill_complete_msg, true);
    }
}

void GemTrackDir::SetInstrument(TrackInstrument inst){
    BandTrack::SetInstrument(inst);
    TrackReset();
}

DECOMP_FORCEACTIVE(GemTrackDir, "game.cam")

void GemTrackDir::SetPlayerLocal(float f){
    bool b2 = true;
    bool b1 = false;
    if(BandTrack::mParent && BandTrack::mParent->HasNetPlayer()) b1 = true;
    if(!b1 && !mSimulatedNet) b2 = false;
    if(b2) Find<EventTrigger>("network_remote.trig", true)->Trigger();
    else Find<EventTrigger>("network_local.trig", true)->Trigger();
}

void GemTrackDir::SetDisplayRange(float f){
    if(f != 10.0f) MILO_WARN("keyboard range must be 10 white keys inclusive");
    mSmasherPlate->SetProperty(range, f);
    mSmasherPlate->HandleType(update_range_msg);
    if(BandTrack::mParent) BandTrack::mParent->UpdateSlotXfms();
    mKeyRange = f;
}

enum {
    kWhiteKeyC = 0,
    kWhiteKeyD = 1,
    kWhiteKeyE = 2,
    kWhiteKeyF = 3,
    kWhiteKeyG = 4,
    kWhiteKeyA = 5,
    kWhiteKeyB = 6,
    kNumWhiteKeys = 7
} WhiteKey;

enum {
    kNoteC = 0,
    kNoteCSharp = 1,
    kNoteDFlat = 1,
    kNoteD = 2,
    kNoteDSharp = 3,
    kNoteEFlat = 3,
    kNoteE = 4,
    kNoteF = 5,
    kNoteFSharp = 6,
    kNoteGFlat = 6,
    kNoteG = 7,
    kNoteGSharp = 8,
    kNoteAFlat = 8,
    kNoteA = 9,
    kNoteASharp = 10,
    kNoteBFlat = 10,
    kNoteB = 11,
    kNumSemitones = 12
} SemitoneName;

int WhiteKeyToSemitone(int whiteKey){
    MILO_ASSERT(whiteKey > -1, 0x557);
    int semitone = 0;
    while(whiteKey >= kNumWhiteKeys){
        whiteKey -= kNumWhiteKeys;
        semitone += kNumSemitones;
    }
    switch(whiteKey){
        case kWhiteKeyC:
            semitone += kNoteC;
            break;
        case kWhiteKeyD:
            semitone += kNoteD;
            break;
        case kWhiteKeyE:
            semitone += kNoteE;
            break;
        case kWhiteKeyF:
            semitone += kNoteF;
            break;
        case kWhiteKeyG:
            semitone += kNoteG;
            break;
        case kWhiteKeyA:
            semitone += kNoteA;
            break;
        case kWhiteKeyB:
            semitone += kNoteB;
            break;
        default:
            MILO_FAIL("unexpected white key %d", whiteKey);
            break;
    }
    return semitone;
}

float GemTrackDir::GetFretPosOffset(int idx) const {
    float f;
    if(idx > mFretPosOffsets.size()){
        if(idx > 0) MILO_WARN("fret position %d is unhandled - must be in [-1,%d]", idx, mFretPosOffsets.size() - 1);
        f = 0;
    }
    else f = mFretPosOffsets[idx];
    return f;
}

float GemTrackDir::GetKeyRange(){ return mKeyRange; }
float GemTrackDir::GetKeyOffset(){ return mKeyOffset; }

void GemTrackDir::UpdateFingerFeedback(const RGState& state){
#ifdef MILO_DEBUG
    static int count;
    const RGState& touse = mFakeFingerShape ? mRGState : state;
    if(mCycleFakeFingerShapes){
        count++;
        if(count == mRandomShapeFrameCount){
            for(int i = 0; i < 6; i++){
                mRGState.FretDown(i, RandomInt(0, 5));
            }
            count = 0;
        }
    }
    if(mFingerShape) mFingerShape->Update(touse, true, false);
#else    
    if(mFingerShape) mFingerShape->Update(state, true, false);
#endif
}

void GemTrackDir::UpdateLeftyFlip(bool b){
    if(mFingerShape) mFingerShape->UpdateLeftyFlip(b);
}

void GemTrackDir::KeyMissRight(){
    if(mMissOutofRangeRightTrig) mMissOutofRangeRightTrig->Trigger();
}

void GemTrackDir::KeyMissLeft(){
    if(mMissOutofRangeLeftTrig) mMissOutofRangeLeftTrig->Trigger();
}

void GemTrackDir::SetUnisonProgress(float f){
    if(mUnisonIcon) mUnisonIcon->SetProgress(f);
}

#define kNumRGStrings 6

void GemTrackDir::AddChordRepImpl(RndMesh* mesh, TrackWidget* widget1, TrackWidget* widget2, TrackWidget* widget3,
    float f, const std::vector<int>& fretNums, String chordLabel){
    float secy = SecondsToY(f);
    if(widget1 && mesh){
        Transform tf60;
        tf60.Reset();
        tf60.v.y = secy;
        widget1->AddMeshInstance(tf60, mesh, 0.0f);
    }
    if(widget2){
        MILO_ASSERT(fretNums.size() == kNumRGStrings, 0x71F);
        for(int i = 0; i < 6; i++){
            int curi = fretNums[i];
            if(curi > -1){
                Transform tf90 = SlotAt(i);
                tf90.v.y = secy;
                widget2->AddTextInstance(tf90, String(RGFretNumberToString(curi)), false);
            }
        }
    }
    if(widget3){
        MILO_ASSERT(!chordLabel.empty(), 0x72F);
        Transform tfc0;
        tfc0.Reset();
        tfc0.v.y = secy;
        tfc0.v.x = GetCurrentChordLabelPosOffset();
        widget3->AddTextInstance(tfc0, chordLabel, false);
    }
}

float GemTrackDir::GetCurrentChordLabelPosOffset() const {
    if(BandTrack::mParent){
        if(BandTrack::mParent->Lefty()) return -mChordLabelPosOffset;
        else return mChordLabelPosOffset;
    }
    else return mChordLabelPosOffset;
}

DataNode GemTrackDir::OnDrawSampleChord(DataArray* da){
    RndMesh* mesh = da->Obj<RndMesh>(2);
    TrackWidget* widget1 = da->Obj<TrackWidget>(3);
    TrackWidget* widget2 = da->Obj<TrackWidget>(4);
    TrackWidget* widget3 = da->Obj<TrackWidget>(5);
    int i6 = da->Int(6);
    int i7 = da->Int(7);
    RndTransformable* trans = da->Obj<RndTransformable>(8);
    Transform tf68(trans->WorldXfm());
    String str78(da->Str(9));
    static std::vector<int> fretNums;
    if(fretNums.empty()) fretNums.resize(6);
    for(int i = 0; i < 6; i++){
        if(i == i6) fretNums[i] = i7;
        else fretNums[i] = -1;
    }
    AddChordImpl(mesh, widget1, widget2, widget3, 0, fretNums, str78);
    return 0;
}

bool GemTrackDir::KeyShifting(){ return kKeyShifting; }
bool GemTrackDir::ToggleKeyShifting(){
    kKeyShifting = kKeyShifting == 0;
    return kKeyShifting;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(GemTrackDir)
    HANDLE_ACTION(set_pitch, SetPitch(_msg->Float(2)))
    HANDLE_ACTION(set_fade, SetFade(_msg->Float(2), _msg->Float(3)))
    HANDLE_ACTION(set_fov, SetFOV(_msg->Float(2)))
    HANDLE_ACTION(set_cam_pos, SetCamPos(_msg->Float(2), _msg->Float(3), _msg->Float(4)))
    HANDLE_ACTION(set_screen_rect_x, SetScreenRectX(_msg->Float(2)))
    HANDLE_ACTION(set_track_offset, SetTrackOffset(_msg->Float(2)))
    HANDLE_ACTION(set_side_angle, SetSideAngle(_msg->Float(2)))
    HANDLE_ACTION(track_in, Extend(false))
    HANDLE_ACTION(track_in_now, Extend(true))
    HANDLE_ACTION(track_out, Retract(false))
    HANDLE_ACTION(track_out_now, Retract(true))
    HANDLE_ACTION(spotlight_phrase_success, SpotlightPhraseSuccess())
    HANDLE_ACTION(mash, Mash(_msg->Int(2)))
    HANDLE_ACTION(crash_fill, CrashFill())
    HANDLE_EXPR(get_smasher_plate, mSmasherPlate.Ptr())
    HANDLE_ACTION(key_miss_right, KeyMissRight())
    HANDLE_ACTION(key_miss_left, KeyMissLeft())
    HANDLE(draw_sample_chord, OnDrawSampleChord)
    HANDLE_ACTION(set_key_range, SetDisplayRange(_msg->Float(2)))
    HANDLE_ACTION(set_key_offset, SetDisplayOffset(_msg->Float(2), false))
#ifdef MILO_DEBUG
    HANDLE_EXPR(toggle_key_shifting, ToggleKeyShifting())
#endif
    HANDLE_SUPERCLASS(BandTrack)
    HANDLE_SUPERCLASS(TrackDir)
    HANDLE_CHECK(0x7B4)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(GemTrackDir)
    SYNC_PROP(num_tracks, mNumTracks)
    SYNC_PROP(kick_pass_counter, mKickPassCounter)
    SYNC_PROP(surface_texture, mSurfaceTexture)
    SYNC_PROP(surface_mesh, mSurfaceMesh)
    SYNC_PROP(effect_selector, mEffectSelector)
    SYNC_PROP(surface_mat, mSurfaceMat)
    SYNC_PROP(track_env, mTrackEnv)
    SYNC_PROP(game_cam, mGameCam)
    SYNC_PROP(peak_state_on_trig, mPeakStateOnTrig)
    SYNC_PROP(peak_state_off_trig, mPeakStateOffTrig)
    SYNC_PROP(bass_super_streak_on_trig, mBassSuperStreakOnTrig)
    SYNC_PROP(bass_super_streak_off_trig, mBassSuperStreakOffTrig)
    SYNC_PROP(kick_drummer_trig, mKickDrummerTrig)
    SYNC_PROP(kick_drummer_reset_trig, mKickDrummerResetTrig)
    SYNC_PROP(spotlight_phrase_success_trig, mSpotlightPhraseSuccessTrig)
    SYNC_PROP(gem_mash_0_anim, mGemMashAnims[0])
    SYNC_PROP(gem_mash_1_anim, mGemMashAnims[1])
    SYNC_PROP(gem_mash_2_anim, mGemMashAnims[2])
    SYNC_PROP(gem_mash_3_anim, mGemMashAnims[3])
    SYNC_PROP(gem_mash_4_anim, mGemMashAnims[4])
    SYNC_PROP(drum_mash_1_anim, mDrumMashAnims[1])
    SYNC_PROP(drum_mash_2_anim, mDrumMashAnims[2])
    SYNC_PROP(drum_mash_3_anim, mDrumMashAnims[3])
    SYNC_PROP(drum_mash_4_anim, mDrumMashAnims[4])
    SYNC_PROP(fill_lane_1_anim, mFillLaneAnims[1])
    SYNC_PROP(fill_lane_2_anim, mFillLaneAnims[2])
    SYNC_PROP(fill_lane_3_anim, mFillLaneAnims[3])
    SYNC_PROP(fill_lane_4_anim, mFillLaneAnims[4])
    SYNC_PROP(real_guitar_mash_0_anim, mRealGuitarMashAnims[0])
    SYNC_PROP(real_guitar_mash_1_anim, mRealGuitarMashAnims[1])
    SYNC_PROP(real_guitar_mash_2_anim, mRealGuitarMashAnims[2])
    SYNC_PROP(real_guitar_mash_3_anim, mRealGuitarMashAnims[3])
    SYNC_PROP(real_guitar_mash_4_anim, mRealGuitarMashAnims[4])
    SYNC_PROP(real_guitar_mash_5_anim, mRealGuitarMashAnims[5])
    SYNC_PROP(fill_hit_1_trig, mFillHitTrigs[0])
    SYNC_PROP(fill_hit_2_trig, mFillHitTrigs[1])
    SYNC_PROP(fill_hit_3_trig, mFillHitTrigs[2])
    SYNC_PROP(drum_fill_reset_trig, mDrumFillResetTrig)
    SYNC_PROP(drum_mash_2nd_pass_activate_anim, mDrumMash2ndPassActivateAnim)
    SYNC_PROP(drum_mash_hit_anim_grp, mDrumMashHitAnimGrp)
    SYNC_PROP(fill_colors_grp, mFillColorsGrp)
    SYNC_PROP(rotater, mRotater)
    SYNC_PROP(lod_anim, mLodAnim)
    SYNC_PROP(glow_widgets, mGlowWidgets)
    SYNC_PROP(streak_meter_offset, mStreakMeterOffset)
    SYNC_PROP(streak_meter_tilt, mStreakMeterTilt)
    SYNC_PROP(track_pitch, mTrackPitch)
    SYNC_PROP(smasher_plate, mSmasherPlate)
    SYNC_PROP(fret_pos_offset_0, mFretPosOffsets[0])
    SYNC_PROP(fret_pos_offset_1, mFretPosOffsets[1])
    SYNC_PROP(fret_pos_offset_2, mFretPosOffsets[2])
    SYNC_PROP(fret_pos_offset_3, mFretPosOffsets[3])
    SYNC_PROP(fret_pos_offset_4, mFretPosOffsets[4])
    SYNC_PROP(chord_label_pos_offset, mChordLabelPosOffset)
    SYNC_PROP(gem_track_dir_id, mGemTrackDirID)
#ifdef MILO_DEBUG
    SYNC_PROP(fake_finger_shape, mFakeFingerShape)
    SYNC_PROP(cycle_fake_finger_shapes, mCycleFakeFingerShapes)
    SYNC_PROP(random_shape_frame_count, mRandomShapeFrameCount)
#endif
    SYNC_SUPERCLASS(BandTrack)
    SYNC_SUPERCLASS(TrackDir)
END_PROPSYNCS