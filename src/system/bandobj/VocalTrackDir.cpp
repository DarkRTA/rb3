#include "bandobj/VocalTrackDir.h"
#include "bandobj/TrackInterface.h"
#include "utl/Symbols.h"

VocalTrackDir::VocalTrackDir() : BandTrack(this), mHiddenPartAlpha(0.3f), unk2a4(1), unk2a5(1), mIsTop(1), unk2a7(0), mFeedbackStateLead(0), mFeedbackStateHarm1(0), mFeedbackStateHarm2(0),
    mVocalMics(this, 0), unk2f0(this, 0), mMinPitchRange(12.0f), mPitchDisplayMargin(3.0f), mArrowSmoothing(0.85f), mConfigurableObjects(this, kObjListNoNull), mVoxCfg(this, 0),
    mTambourineSmasher(this, 0), mTambourineNowShowTrig(this, 0), mTambourineNowHideTrig(this, 0), mLeadPhraseFeedbackBottomLbl(this, 0), mPhraseFeedbackTrig(this, 0),
    mSpotlightSparklesOnlyTrig(this, 0), mSpotlightPhraseSuccessTrig(this, 0), mPitchArrow1(this, 0), mPitchArrow2(this, 0), mPitchArrow3(this, 0), mPitchWindow(1),
    mPitchWindowHeight(2.5f), mPitchWindowMesh(this, 0), mPitchWindowOverlay(this, 0), mLeadLyrics(1), mLeadLyricHeight(0.4f), mLeadLyricMesh(this, 0), mHarmLyrics(1),
    mHarmLyricHeight(0.4f), mHarmLyricMesh(this, 0), mLeftDecoMesh(this, 0), mRightDecoMesh(this, 0), mNowBarWidth(0.2f), mNowBarMesh(this, 0), mRemoteVocals(0),
    mTrackLeftX(-20.0f), mTrackRightX(20.0f), mTrackBottomZ(0.0f), mTrackTopZ(10.0f), mPitchBottomZ(0.0f), mPitchTopZ(2.0f), mNowBarX(-10.0f), unk42c(0), mPitchGuides("harmonic"),
    mTubeStyle(this, 0), mArrowStyle(this, 0), mFontStyle(this, 0), unk458(this, 0), unk464(this, 0), unk470(this, 0), unk47c(this, 0), mLastMin(36.0f), mLastMax(84.0f), mMiddleCZPos(0),
    mTonic(0x3c), mRangeScaleAnim(this, 0), mRangeOffsetAnim(this, 0), unk4b0(1), unk4b4(2), mLeftTrans(0), mRightTrans(0), mBottomTrans(0), mTopTrans(0),
    mPitchBottomTrans(0), mPitchTopTrans(0), mPitchMidTrans(0), mNowTrans(0), mTubeRangeGrp(this, 0), mTubeSpotlightGrp(this, 0), mTubeBack0Grp(this, 0), mTubeBack1Grp(this, 0),
    mTubeBack2Grp(this, 0), mTubeFront0Grp(this, 0), mTubeFront1Grp(this, 0), mTubeFront2Grp(this, 0), mTubeGlow0Grp(this, 0), mTubeGlow1Grp(this, 0), mTubeGlow2Grp(this, 0),
    mTubePhoneme0Grp(this, 0), mTubePhoneme1Grp(this, 0), mTubePhoneme2Grp(this, 0), unk580(this, 0), unk58c(this, 0), unk598(this, 0), unk5a4(this, 0), unk5b0(this, 0), unk5bc(this, 0),
    unk5c8(this, 0), unk5d4(this, 0), unk5e0(this, 0), unk5ec(this, 0), unk5f8(this, 0), unk604(this, 0), unk610(this, 0), mVocalsGrp(this, 0), mScroller(this, 0), mLeadLyricScroller(this, 0),
    mHarmonyLyricScroller(this, 0), mBREGrp(this, 0), mLeadBREGrp(this, 0), mHarmonyBREGrp(this, 0), mPitchScrollGroup(this, 0), mLeadLyricScrollGroup(this, 0),
    mHarmonyLyricScrollGroup(this, 0), unk694(0), unk698(0), unk69c(0), unk6a0(0), mLeadDeployMat(this, 0), mHarmDeployMat(this, 0), unk6bc(-1.0f), unk6c0(0.3f),
    unk6c4(-1), unk6c8(0), mArrowFXDrawGrp(this, 0), unk6d8(18.0f), unk6dc(48.0f), unk6e0(0) {

}

void VocalTrackDir::SyncObjects(){
    RndDir::SyncObjects();
    if(!mLeftTrans) mLeftTrans = Find<RndTransformable>("track_left.trans", false);
    if(!mRightTrans) mRightTrans = Find<RndTransformable>("track_right.trans", false);
    if(!mBottomTrans) mBottomTrans = Find<RndTransformable>("track_bottom.trans", false);
    if(!mTopTrans) mTopTrans = Find<RndTransformable>("track_top.trans", false);
    if(!mPitchBottomTrans) mPitchBottomTrans = Find<RndTransformable>("pitch_bottom.trans", false);
    if(!mPitchTopTrans) mPitchTopTrans = Find<RndTransformable>("pitch_top.trans", false);
    if(!mPitchMidTrans) mPitchMidTrans = Find<RndTransformable>("pitch_mid.trans", false);
    if(!mNowTrans) mNowTrans = Find<RndTransformable>("now_bar.trans", false);
    if(!mPitchArrow1) mPitchArrow1 = Find<PitchArrow>("pitch_arrow_1", false);
    if(!mPitchArrow2) mPitchArrow2 = Find<PitchArrow>("pitch_arrow_2", false);
    if(!mPitchArrow3) mPitchArrow3 = Find<PitchArrow>("pitch_arrow_3", false);
    if(!mTubeRangeGrp) mTubeRangeGrp = Find<RndGroup>("tubes.grp", false);
    if(!mTubeSpotlightGrp) mTubeSpotlightGrp = Find<RndGroup>("spotlight.grp", false);
    if(!mTubeBack0Grp) mTubeBack0Grp = Find<RndGroup>("back0.grp", false);
    if(!mTubeBack1Grp) mTubeBack1Grp = Find<RndGroup>("back1.grp", false);
    if(!mTubeBack2Grp) mTubeBack2Grp = Find<RndGroup>("back2.grp", false);
    if(!mTubeFront0Grp) mTubeFront0Grp = Find<RndGroup>("front0.grp", false);
    if(!mTubeFront1Grp) mTubeFront1Grp = Find<RndGroup>("front1.grp", false);
    if(!mTubeFront2Grp) mTubeFront2Grp = Find<RndGroup>("front2.grp", false);
    if(!mTubeGlow0Grp) mTubeGlow0Grp = Find<RndGroup>("glow0.grp", false);
    if(!mTubeGlow1Grp) mTubeGlow1Grp = Find<RndGroup>("glow1.grp", false);
    if(!mTubeGlow2Grp) mTubeGlow2Grp = Find<RndGroup>("glow2.grp", false);
    if(!mTubePhoneme0Grp) mTubePhoneme0Grp = Find<RndGroup>("phoneme0.grp", false);
    if(!mTubePhoneme1Grp) mTubePhoneme1Grp = Find<RndGroup>("phoneme1.grp", false);
    if(!mTubePhoneme2Grp) mTubePhoneme2Grp = Find<RndGroup>("phoneme2.grp", false);
    if(!mVocalsGrp) mVocalsGrp = Find<RndGroup>("vocals.grp", false);
    if(!mScroller) mScroller = Find<RndTransformable>("scroller.trans", false);
    if(!mLeadLyricScroller) mLeadLyricScroller = Find<RndTransformable>("lead_lyric_scroller.trans", false);
    if(!mHarmonyLyricScroller) mHarmonyLyricScroller = Find<RndTransformable>("harmony_lyric_scroller.trans", false);
    if(!mBREGrp) mBREGrp = Find<RndGroup>("bre.grp", false);
    if(!mLeadBREGrp) mLeadBREGrp = Find<RndGroup>("lead_bre.grp", false);
    if(!mHarmonyBREGrp) mHarmonyBREGrp = Find<RndGroup>("harmony_bre.grp", false);
    if(!mPitchScrollGroup) mPitchScrollGroup = Find<RndGroup>("pitch_scroll.grp", false);
    if(!mLeadLyricScrollGroup) mLeadLyricScrollGroup = Find<RndGroup>("lead_lyric_scroll.grp", false);
    if(!mHarmonyLyricScrollGroup) mHarmonyLyricScrollGroup = Find<RndGroup>("harmony_lyric_scroll.grp", false);
    if(!mBeatAnimsGrp) mBeatAnimsGrp = Find<RndGroup>("beat_anims.grp", false);
    if(!mArrowFXDrawGrp) mArrowFXDrawGrp = Find<RndGroup>("arrow_fx_draw.grp", false);
    if(!mTambourineSmasher) mTambourineSmasher = Find<RndDir>("tambourine_smasher", false);
    if(!mTambourineNowShowTrig) mTambourineNowShowTrig = Find<EventTrigger>("tambourine_now_show.trig", false);
    if(!mTambourineNowHideTrig) mTambourineNowHideTrig = Find<EventTrigger>("tambourine_now_hide.trig", false);
    if(!mVocalMics) mVocalMics = Find<RndDir>("vocals_mics", false);
    if(!mLeadPhraseFeedbackBottomLbl) mLeadPhraseFeedbackBottomLbl = Find<BandLabel>("lead_phrase_feedback_bottom.lbl", false);
    UpdateTubeStyle();
}

#pragma push
#pragma dont_inline on
BEGIN_PROPSYNCS(VocalTrackDir)
    SYNC_PROP(is_top, mIsTop)
    SYNC_PROP(feedback_state_lead, mFeedbackStateLead)
    SYNC_PROP(feedback_state_harm_1, mFeedbackStateHarm1)
    SYNC_PROP(feedback_state_harm_2, mFeedbackStateHarm2)
    SYNC_PROP(lead_coming, mLyricColorMap[5])
    SYNC_PROP(lead_now, mLyricColorMap[6])
    SYNC_PROP(lead_past, mLyricColorMap[7])
    SYNC_PROP(lead_od_coming, mLyricColorMap[0x15])
    SYNC_PROP(lead_od_now, mLyricColorMap[0x16])
    SYNC_PROP(lead_od_past, mLyricColorMap[0x17])
    SYNC_PROP(harmony_coming, mLyricColorMap[1])
    SYNC_PROP(harmony_now, mLyricColorMap[2])
    SYNC_PROP(harmony_past, mLyricColorMap[3])
    SYNC_PROP(harmony_od_coming, mLyricColorMap[0x11])
    SYNC_PROP(harmony_od_now, mLyricColorMap[0x12])
    SYNC_PROP(harmony_od_past, mLyricColorMap[0x13])
    SYNC_PROP(lead_static_preview, mLyricColorMap[0xC])
    SYNC_PROP(lead_static_coming, mLyricColorMap[0xD])
    SYNC_PROP(lead_static_now, mLyricColorMap[0xE])
    SYNC_PROP(lead_static_past, mLyricColorMap[0xF])
    SYNC_PROP(lead_static_od_preview, mLyricColorMap[0x1C])
    SYNC_PROP(lead_static_od_coming, mLyricColorMap[0x1D])
    SYNC_PROP(lead_static_od_now, mLyricColorMap[0x1E])
    SYNC_PROP(lead_static_od_past, mLyricColorMap[0x1F])
    SYNC_PROP(harmony_static_preview, mLyricColorMap[8])
    SYNC_PROP(harmony_static_coming, mLyricColorMap[9])
    SYNC_PROP(harmony_static_now, mLyricColorMap[0xA])
    SYNC_PROP(harmony_static_past, mLyricColorMap[0xB])
    SYNC_PROP(harmony_static_od_preview, mLyricColorMap[0x18])
    SYNC_PROP(harmony_static_od_coming, mLyricColorMap[0x19])
    SYNC_PROP(harmony_static_od_now, mLyricColorMap[0x1A])
    SYNC_PROP(harmony_static_od_past, mLyricColorMap[0x1B])
    SYNC_PROP(scrolling_coming_alpha, mLyricAlphaMap[1])
    SYNC_PROP(scrolling_now_alpha, mLyricAlphaMap[2])
    SYNC_PROP(scrolling_past_alpha, mLyricAlphaMap[3])
    SYNC_PROP(static_preview_alpha, mLyricAlphaMap[8])
    SYNC_PROP(static_coming_alpha, mLyricAlphaMap[9])
    SYNC_PROP(static_now_alpha, mLyricAlphaMap[0xA])
    SYNC_PROP(static_past_alpha, mLyricAlphaMap[0xB])
    SYNC_PROP(min_pitch_range, mMinPitchRange)
    SYNC_PROP(pitch_display_margin, mPitchDisplayMargin)
    SYNC_PROP(arrow_smoothing, mArrowSmoothing)
    SYNC_PROP(configurable_objects, mConfigurableObjects)
    SYNC_PROP(phrase_feedback_trig, mPhraseFeedbackTrig)
    SYNC_PROP(spotlight_sparkles_only_trig, mSpotlightSparklesOnlyTrig)
    SYNC_PROP(spotlight_phrase_success_trig, mSpotlightPhraseSuccessTrig)
    SYNC_PROP(vox_configuration, mVoxCfg)
    SYNC_PROP(pitch_window, mPitchWindow)
    SYNC_PROP(pitch_window_height, mPitchWindowHeight)
    SYNC_PROP(pitch_window_mesh, mPitchWindowMesh)
    SYNC_PROP(pitch_window_overlay, mPitchWindowOverlay)
    SYNC_PROP(lead_lyrics, mLeadLyrics)
    SYNC_PROP(lead_lyric_height, mLeadLyricHeight)
    SYNC_PROP(lead_lyric_mesh, mLeadLyricMesh)
    SYNC_PROP(harmony_lyrics, mHarmLyrics)
    SYNC_PROP(harmony_lyric_height, mHarmLyricHeight)
    SYNC_PROP(harmony_lyric_mesh, mHarmLyricMesh)
    SYNC_PROP(left_deco_mesh, mLeftDecoMesh)
    SYNC_PROP(right_deco_mesh, mRightDecoMesh)
    SYNC_PROP(now_bar_width, mNowBarWidth)
    SYNC_PROP(now_bar_mesh, mNowBarMesh)
    SYNC_PROP(remote, mRemoteVocals)
    SYNC_PROP(track_left, mTrackLeftX)
    SYNC_PROP(track_right, mTrackRightX)
    SYNC_PROP(track_bottom, mTrackBottomZ)
    SYNC_PROP(track_top, mTrackTopZ)
    SYNC_PROP(pitch_bottom, mPitchBottomZ)
    SYNC_PROP(pitch_top, mPitchTopZ)
    SYNC_PROP(now_bar, mNowBarX)
    SYNC_PROP(pitch_guides, mPitchGuides)
    SYNC_PROP(tube_style, mTubeStyle)
    SYNC_PROP(arrow_style, mArrowStyle)
    SYNC_PROP(font_style, mFontStyle)
    SYNC_PROP(last_min, mLastMin)
    SYNC_PROP(last_max, mLastMax)
    SYNC_PROP(middle_c_z_pos, mMiddleCZPos)
    SYNC_PROP(tonic, mTonic)
    SYNC_PROP(range_scale_anim, mRangeScaleAnim)
    SYNC_PROP(range_offset_anim, mRangeOffsetAnim)
    SYNC_PROP(lead_deploy_mat, mLeadDeployMat)
    SYNC_PROP(harmony_deploy_mat, mHarmDeployMat)
    SYNC_PROP(hidden_part_alpha, mHiddenPartAlpha)
    SYNC_PROP(overdrive_meter, mStarPowerMeter)
    SYNC_SUPERCLASS(BandTrack)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(VocalTrackDir)
    HANDLE_ACTION(set_vox_configuration, SetConfiguration(_msg->Obj<Hmx::Object>(2), (HarmonyShowingState)2))
    HANDLE_ACTION(update_configuration, UpdateConfiguration())
    HANDLE(display_mode, OnGetDisplayMode)
    HANDLE(set_display_mode, OnSetDisplayMode)
    HANDLE_ACTION(set_feedback_state, ShowPhraseFeedback(_msg->Int(2), _msg->Int(3), _msg->Int(4), false))
    HANDLE_ACTION(set_phrase_meter, SetStreakPct(_msg->Float(2)))
    HANDLE_ACTION(spotlight_phrase_success, SpotlightPhraseSuccess())
    HANDLE_ACTION(set_enable_vocals_options, SetEnableVocalsOptions(_msg->Int(2)))
    HANDLE(foreach_configurable_object, DataForEachConfigObj)
    HANDLE_ACTION(rebuild_hud, if(BandTrack::mParent) BandTrack::mParent->RebuildVocalHUD())
    HANDLE_ACTION(apply_font_style, ApplyFontStyle(_msg->Obj<Hmx::Object>(2)))
    HANDLE_ACTION(apply_arrow_style, ApplyArrowStyle(_msg->Obj<Hmx::Object>(2)))
    HANDLE(set_lyric_color, OnSetLyricColor)
    HANDLE_ACTION(track_in, Extend(false))
    HANDLE_ACTION(track_in_now, Extend(true))
    HANDLE_ACTION(track_out, Retract(false))
    HANDLE_ACTION(track_out_now, Retract(true))
    HANDLE(isolate_vocal_part, OnIsolatePart)
    HANDLE_ACTION(show_all_parts, SetIsolatedPart(-1))
    HANDLE_EXPR(num_vocal_parts, NumVocalParts())
    HANDLE_ACTION(set_range, SetRange(_msg->Float(2), _msg->Float(3), _msg->Int(4), false))
    HANDLE_EXPR(num_vocal_parts, NumVocalParts())
    HANDLE_SUPERCLASS(BandTrack)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x71C)
END_HANDLERS
#pragma pop