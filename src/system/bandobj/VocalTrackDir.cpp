#include "bandobj/VocalTrackDir.h"
#include "utl/Symbols.h"

VocalTrackDir::VocalTrackDir() : BandTrack(this), mHiddenPartAlpha(0.3f), unk2a4(1), unk2a5(1), mIsTop(1), unk2a7(0), mFeedbackStateLead(0), mFeedbackStateHarm1(0), mFeedbackStateHarm2(0), unk2e4(this, 0), unk2f0(this, 0),
    mMinPitchRange(12.0f), mPitchDisplayMargin(3.0f), mArrowSmoothing(0.85f), mConfigurableObjects(this, kObjListNoNull), mVoxCfg(this, 0), unk324(this, 0), unk330(this, 0), unk33c(this, 0), unk348(this, 0), mPhraseFeedbackTrig(this, 0),
    mSpotlightSparklesOnlyTrig(this, 0), mSpotlightPhraseSuccessTrig(this, 0), unk378(this, 0), unk384(this, 0), unk390(this, 0), mPitchWindow(1), mPitchWindowHeight(2.5f), mPitchWindowMesh(this, 0), mPitchWindowOverlay(this, 0), mLeadLyrics(1), mLeadLyricHeight(0.4f),
    mLeadLyricMesh(this, 0), mHarmLyrics(1), mHarmLyricHeight(0.4f), mHarmLyricMesh(this, 0), mLeftDecoMesh(this, 0), mRightDecoMesh(this, 0), mNowBarWidth(0.2f), mNowBarMesh(this, 0), mRemote(0), mTrackLeft(-20.0f), mTrackRight(20.0f),
    mTrackBottom(0.0f), mTrackTop(10.0f), mPitchBottom(0.0f), mPitchTop(2.0f), mNowBar(-10.0f), unk42c(0), mPitchGuides("harmonic"), mTubeStyle(this, 0), mArrowStyle(this, 0), mFontStyle(this, 0), unk458(this, 0),
    unk464(this, 0), unk470(this, 0), unk47c(this, 0), mLastMin(36.0f), mLastMax(84.0f), mMiddleCZPos(0), mTonic(0x3c), mRangeScaleAnim(this, 0), mRangeOffsetAnim(this, 0), unk4b0(1), unk4b4(2), unk4b8(0),
    unk4bc(0), unk4c0(0), unk4c4(0), unk4c8(0), unk4cc(0), unk4d0(0), unk4d4(0), unk4d8(this, 0), unk4e4(this, 0), unk4f0(this, 0), unk4fc(this, 0), unk508(this, 0), unk514(this, 0),
    unk520(this, 0), unk52c(this, 0), unk538(this, 0), unk544(this, 0), unk550(this, 0), unk55c(this, 0), unk568(this, 0), unk574(this, 0), unk580(this, 0), unk58c(this, 0),
    unk598(this, 0), unk5a4(this, 0), unk5b0(this, 0), unk5bc(this, 0), unk5c8(this, 0), unk5d4(this, 0), unk5e0(this, 0), unk5ec(this, 0), unk5f8(this, 0), unk604(this, 0),
    unk610(this, 0), unk61c(this, 0), unk628(this, 0), unk634(this, 0), unk640(this, 0), unk64c(this, 0), unk658(this, 0), unk664(this, 0), unk670(this, 0), unk67c(this, 0),
    unk688(this, 0), unk694(0), unk698(0), unk69c(0), unk6a0(0), mLeadDeployMat(this, 0), mHarmDeployMat(this, 0), unk6bc(-1.0f), unk6c0(0.3f), unk6c4(-1), unk6c8(0), unk6cc(this, 0),
    unk6d8(18.0f), unk6dc(48.0f), unk6e0(0) {

}

#pragma push
#pragma dont_inline on
BEGIN_PROPSYNCS(VocalTrackDir)
    SYNC_PROP(is_top, mIsTop)
    SYNC_PROP(feedback_state_lead, mFeedbackStateLead)
    SYNC_PROP(feedback_state_harm_1, mFeedbackStateHarm1)
    SYNC_PROP(feedback_state_harm_2, mFeedbackStateHarm2)
    SYNC_PROP(lead_coming, unk2b4[5])
    SYNC_PROP(lead_now, unk2b4[6])
    SYNC_PROP(lead_past, unk2b4[7])
    SYNC_PROP(lead_od_coming, unk2b4[0x15])
    SYNC_PROP(lead_od_now, unk2b4[0x16])
    SYNC_PROP(lead_od_past, unk2b4[0x17])
    SYNC_PROP(harmony_coming, unk2b4[1])
    SYNC_PROP(harmony_now, unk2b4[2])
    SYNC_PROP(harmony_past, unk2b4[3])
    SYNC_PROP(harmony_od_coming, unk2b4[0x11])
    SYNC_PROP(harmony_od_now, unk2b4[0x12])
    SYNC_PROP(harmony_od_past, unk2b4[0x13])
    SYNC_PROP(lead_static_preview, unk2b4[0xC])
    SYNC_PROP(lead_static_coming, unk2b4[0xD])
    SYNC_PROP(lead_static_now, unk2b4[0xE])
    SYNC_PROP(lead_static_past, unk2b4[0xF])
    SYNC_PROP(lead_static_od_preview, unk2b4[0x1C])
    SYNC_PROP(lead_static_od_coming, unk2b4[0x1D])
    SYNC_PROP(lead_static_od_now, unk2b4[0x1E])
    SYNC_PROP(lead_static_od_past, unk2b4[0x1F])
    SYNC_PROP(harmony_static_preview, unk2b4[8])
    SYNC_PROP(harmony_static_coming, unk2b4[9])
    SYNC_PROP(harmony_static_now, unk2b4[0xA])
    SYNC_PROP(harmony_static_past, unk2b4[0xB])
    SYNC_PROP(harmony_static_od_preview, unk2b4[0x18])
    SYNC_PROP(harmony_static_od_coming, unk2b4[0x19])
    SYNC_PROP(harmony_static_od_now, unk2b4[0x1A])
    SYNC_PROP(harmony_static_od_past, unk2b4[0x1B])
    SYNC_PROP(scrolling_coming_alpha, unk2cc[1])
    SYNC_PROP(scrolling_now_alpha, unk2cc[2])
    SYNC_PROP(scrolling_past_alpha, unk2cc[3])
    SYNC_PROP(static_preview_alpha, unk2cc[8])
    SYNC_PROP(static_coming_alpha, unk2cc[9])
    SYNC_PROP(static_now_alpha, unk2cc[0xA])
    SYNC_PROP(static_past_alpha, unk2cc[0xB])
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
    SYNC_PROP(remote, mRemote)
    SYNC_PROP(track_left, mTrackLeft)
    SYNC_PROP(track_right, mTrackRight)
    SYNC_PROP(track_bottom, mTrackBottom)
    SYNC_PROP(track_top, mTrackTop)
    SYNC_PROP(pitch_bottom, mPitchBottom)
    SYNC_PROP(pitch_top, mPitchTop)
    SYNC_PROP(now_bar, mNowBar)
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
#pragma pop