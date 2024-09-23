#include "bandobj/PitchArrow.h"
#include "utl/Symbols.h"

INIT_REVS(PitchArrow)

PitchArrow::PitchArrow() : unk18c(0), mScore(0), mHarmonyFX(0), mVolume(1.0f), mTilt(0), mVocalHUDColor(kVocalColorInvalid), mColorFade(0), mSpotlight(0), mDeploying(0), mPitched(1), unk1ab(0),
    mTestColor("white"), mArrowStyle(0), mScoreAnim(this, 0), mHarmonyFXAnim(this, 0), mVolumeAnim(this, 0), mTiltAnim(this, 0), mColorAnim(this, 0), mColorFadeAnim(this, 0),
    mSplitAnim(this, 0), mArrowStyleAnim(this, 0), mSetPitchedTrig(this, 0), mSetUnpitchedTrig(this, 0), mSpotlightStartTrig(this, 0), mSpotlightEndTrig(this, 0),
    mDeployStartTrig(this, 0), mDeployEndTrig(this, 0), mGhostGrp(this, 0), mGhostFadeAnim(this, 0), mArrowFXGrp(this, 0),
    unk280(0), mSpinSpeed(0), mSpinAnim(this, 0), mSpinRestFrame(0), mSpinBeginFrame(0), mSpinEndFrame(0) {

}

void PitchArrow::SyncObjects(){
    mScoreAnim = Find<RndPropAnim>("score.anim", false);
    mHarmonyFXAnim = Find<RndPropAnim>("harmony_fx.anim", false);
    mVolumeAnim = Find<RndPropAnim>("volume.anim", false);
    mTiltAnim = Find<RndPropAnim>("tilt.anim", false);
    mColorAnim = Find<RndPropAnim>("color.anim", false);
    mColorFadeAnim = Find<RndPropAnim>("color_fade.anim", false);
    mSetPitchedTrig = Find<EventTrigger>("set_pitched.trig", false);
    mSetUnpitchedTrig = Find<EventTrigger>("set_unpitched.trig", false);
    mSpotlightStartTrig = Find<EventTrigger>("spotlight_start.trig", false);
    mSpotlightEndTrig = Find<EventTrigger>("spotlight_end.trig", false);
    mDeployStartTrig = Find<EventTrigger>("deploy_start.trig", false);
    mDeployEndTrig = Find<EventTrigger>("deploy_end.trig", false);
    mGhostGrp = Find<RndGroup>("ghost.grp", false);
    mGhostFadeAnim = Find<RndPropAnim>("ghost_fade.anim", false);
    mArrowFXGrp = Find<RndGroup>("arrow_fx.grp", false);
    mSplitAnim = Find<RndPropAnim>("split.anim", false);
    mArrowStyleAnim = Find<RndPropAnim>("arrow_style.anim", false);
    if(!mScoreAnim || !mHarmonyFXAnim || !mVolumeAnim || !mTiltAnim || !mColorAnim || !mColorFadeAnim ||
        !mSetPitchedTrig || !mSetUnpitchedTrig || !mSpotlightStartTrig || !mSpotlightEndTrig || !mDeployStartTrig || !mDeployEndTrig){
        MILO_WARN("Some expected rnd objects are missing from pitch arrow");
    }
    RndDir::SyncObjects();
}

void PitchArrow::Reset(RndGroup* grp){
    if(mPitched) mSetPitchedTrig->Trigger();
    else mSetUnpitchedTrig->Trigger();
    if(mDeploying) mDeployStartTrig->Trigger();
    else mDeployEndTrig->Trigger();
    if(mSpotlight) mSpotlightStartTrig->Trigger();
    else mSpotlightEndTrig->Trigger();
    mTiltAnim->SetFrame(mTilt / 90.0f + 1.0f, 1.0f);
    float score = mScore;
    mScoreAnim->Animate(score, score, mScoreAnim->Units(), 0, 0);
    mHarmonyFXAnim->SetFrame(mHarmonyFX, 1.0f);
    if(mVocalHUDColor != kVocalColorInvalid){
        mColorFadeAnim->SetFrame(0, 1.0f);
        mColorAnim->SetFrame(mVocalHUDColor, 1.0f);
        mColorFadeAnim->SetKey(0);
    }
    mColorFadeAnim->SetFrame(mColorFade, 1.0f);
    if(grp && !ObjectDir::Main()->FindObject("milo", false)){
        RndGroup* tiltgrp = Find<RndGroup>("tilt.grp", true);
        tiltgrp->RemoveObject(mArrowFXGrp);
        grp->AddObject(mArrowFXGrp, 0);
    }
    if(mSplitAnim) mSplitAnim->SetFrame(0, 1.0f);
    if(mGhostGrp){
        mGhostGrp->SetTransParent(TransParent(), false);
        mGhostGrp->SetLocalXfm(LocalXfm());
    }
    SetArrowStyle(mArrowStyle);
    if(TheLoadMgr.EditMode()){
        SetColor(GetVocalHUDColor(mTestColor));
        if(mColorFadeAnim) mColorFadeAnim->SetFrame(mColorFade, 1.0f);
    }
    mVolume = 0;
    mVolumeAnim->SetFrame(0, 1.0f);
}

void PitchArrow::SetPitched(bool b){
    if(b != mPitched && mSetPitchedTrig && mSetUnpitchedTrig){
        if(b) mSetPitchedTrig->Trigger();
        else mSetUnpitchedTrig->Trigger();
        mPitched = b;
    }
}

void PitchArrow::SetSpotlight(bool b){
    if(b != mSpotlight && mSpotlightStartTrig && mSpotlightEndTrig){
        if(b) mSpotlightStartTrig->Trigger();
        else mSpotlightEndTrig->Trigger();
        mSpotlight = b;
    }
}

void PitchArrow::SetDeploying(bool b){
    if(b != mDeploying && mDeployStartTrig && mDeployEndTrig){
        if(b) mDeployStartTrig->Trigger();
        else mDeployEndTrig->Trigger();
        mDeploying = b;
    }
}

void PitchArrow::SetTiltDegrees(float f){
    if(mTilt != f && mTiltAnim){
        mTiltAnim->SetFrame(f / 90.0f + 1.0f, 1.0f);
        mTilt = f;
    }
}

VocalHUDColor GetVocalHUDColor(Symbol s){
    if(s == green) return kVocalColorGreen;
    else if(s == yellow) return kVocalColorYellow;
    else if(s == orange) return kVocalColorOrange;
    else if(s == brown) return kVocalColorBrown;
    else if(s == purple) return kVocalColorPurple;
    else if(s == blue) return kVocalColorBlue;
    else if(s == white) return kVocalColorWhite;
    else {
        MILO_NOTIFY_ONCE("Unhandled vocal HUD color %s\n", s.Str());
        return kVocalColorInvalid;
    }
}

void PitchArrow::SetColor(VocalHUDColor col){
    if(col != kVocalColorInvalid && col != mVocalHUDColor && mColorAnim && mColorFadeAnim){
        mColorAnim->SetFrame(col, 1.0f);
        mVocalHUDColor = col;
        if(col != kVocalColorWhite){
            if((float)col != mArrowFXGrp->mOrder){
                mArrowFXGrp->SetOrder(col);
                unk280 = true;
            }
        }
    }
}

void PitchArrow::Clear(){
    mPitched = true;
    mDeploying = false;
    mSpotlight = false;
    mScore = 0;
    mHarmonyFX = 0;
    mTilt = 0;
    mVolume = 0;
    mColorFade = 1.0f;
    Reset(0);
}

void PitchArrow::ClearParticles(){
    for(ObjDirItr<RndParticleSys> it(this, false); it != 0; ++it){
        it->FreeAllParticles();
    }
}

void PitchArrow::Poll(){
    if(mSpinAnim) PollHelix();
    RndDir::Poll();
}

void PitchArrow::SetGhostFade(float f){
    if(mGhostFadeAnim) mGhostFadeAnim->SetFrame(f * 10.0f, 1.0f);
}

bool PitchArrow::NeedSort(PitchArrow* arrow){
    return arrow && arrow->unk280;
}

void PitchArrow::SetArrowStyle(int i){
    if(mArrowStyleAnim){
        mArrowStyleAnim->SetFrame(i, 1.0f);
        mArrowStyle = i;
    }
}

BEGIN_PROPSYNCS(PitchArrow)
    SYNC_PROP(pitched, mPitched)
    SYNC_PROP(spotlight, mSpotlight)
    SYNC_PROP(deploying, mDeploying)
    SYNC_PROP(score, mScore)
    SYNC_PROP(harmony_fx, mHarmonyFX)
    SYNC_PROP(volume, mVolume)
    SYNC_PROP(tilt, mTilt)
    SYNC_PROP(test_color, mTestColor)
    SYNC_PROP(color_fade, mColorFade)
    SYNC_PROP(spin_speed, mSpinSpeed)
    SYNC_PROP(spin_anim, mSpinAnim)
    SYNC_PROP(spin_rest_frame, mSpinRestFrame)
    SYNC_PROP(spin_begin_frame, mSpinBeginFrame)
    SYNC_PROP(spin_end_frame, mSpinEndFrame)
    SYNC_PROP_MODIFY(arrow_style, mArrowStyle, SetArrowStyle(mArrowStyle))
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(PitchArrow)
    HANDLE_ACTION(reset, Reset(0))
    HANDLE_ACTION(toggle_pitched, SetPitched(mPitched == 0))
    HANDLE_ACTION(toggle_spotlight, SetSpotlight(mSpotlight == 0))
    HANDLE_ACTION(toggle_deploying, SetDeploying(mDeploying == 0))
    HANDLE_ACTION(sync_score, mScoreAnim->SetFrame(mScore, 1.0f))
    HANDLE_ACTION(sync_harm_score, mHarmonyFXAnim->SetFrame(mHarmonyFX, 1.0f))
    HANDLE_ACTION(sync_tilt, mTiltAnim->SetFrame((mTilt / 90.0f) + 1.0f, 1.0f))
    HANDLE(sync_color, OnSyncColor)
    HANDLE_ACTION(sync_color_fade, mColorFadeAnim->SetFrame(mColorFade, 1.0f))
    HANDLE_ACTION(sync_volume, mVolumeAnim->SetFrame(mVolume, 1.0f))
    HANDLE(setup_fx, OnSetupFx)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x195)
END_HANDLERS

DataNode PitchArrow::OnSyncColor(DataArray* da){
    SetColor(GetVocalHUDColor(mTestColor));
    if(mColorFadeAnim) mColorFadeAnim->SetFrame(mColorFade, 1.0f);
    return DataNode(0);
}

SAVE_OBJ(PitchArrow, 0x1A1)

void PitchArrow::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    bs >> mPitched;
    bs >> mSpotlight;
    bs >> mDeploying;
    bs >> mScore;
    bs >> mHarmonyFX;
    bs >> mVolume;
    bs >> mTilt;
    if(gRev < 2) bs >> mTestColor;
    bs >> mColorFade;
    if(gRev >= 1 && !IsProxy()){
        bs >> mSpinSpeed;
        bs >> mSpinAnim;
        bs >> mSpinBeginFrame;
        bs >> mSpinEndFrame;
        bs >> mSpinRestFrame;
    }
    if(gRev >= 2){
        if(gLoadingProxyFromDisk){
            Symbol s; int i;
            bs >> i; bs >> s;
        }
        else {
            bs >> mArrowStyle;
            bs >> mTestColor;
        }
    }
    RndDir::PreLoad(bs);
}

void PitchArrow::PostLoad(BinStream& bs){ RndDir::PostLoad(bs); }

BEGIN_COPYS(PitchArrow)
    CREATE_COPY(PitchArrow)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mPitched)
        COPY_MEMBER(mSpotlight)
        COPY_MEMBER(mDeploying)
        COPY_MEMBER(mScore)
        COPY_MEMBER(mHarmonyFX)
        COPY_MEMBER(mVolume)
        COPY_MEMBER(mTilt)
        COPY_MEMBER(mTestColor)
        COPY_MEMBER(mColorFade)
        COPY_MEMBER(mSpinSpeed)
        COPY_MEMBER(mSpinAnim)
        COPY_MEMBER(mSpinBeginFrame)
        COPY_MEMBER(mSpinEndFrame)
        COPY_MEMBER(mSpinRestFrame)
        COPY_MEMBER(mArrowStyle)
    END_COPYING_MEMBERS
    COPY_SUPERCLASS(RndDir)
END_COPYS

DataNode PitchArrow::OnSetupFx(DataArray* da){
    RndGroup* grp = da->Obj<RndGroup>(2);
    if(grp){
        RndGroup* arrowgrp = Find<RndGroup>("arrow_fx.grp", true);
        RndGroup* tiltgrp = Find<RndGroup>("tilt.grp", true);
        tiltgrp->RemoveObject(arrowgrp);
        grp->AddObject(arrowgrp, 0);
    }
    return DataNode(0);
}