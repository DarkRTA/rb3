#include "bandobj/PitchArrow.h"
#include "utl/Symbols.h"

PitchArrow::PitchArrow() : unk18c(0), mScore(0), mHarmonyFX(0), mVolume(1.0f), mTilt(0), unk1a0(-1), mColorFade(0), mSpotlight(0), mDeploying(0), mPitched(1), unk1ab(0),
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