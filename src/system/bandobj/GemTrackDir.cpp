#include "bandobj/GemTrackDir.h"
#include "utl/Symbols.h"

#pragma push
#pragma dont_inline on
GemTrackDir::GemTrackDir() : BandTrack(this), mNumTracks(1), unk488(-1), mGemTrackDirID(-1), mKickPassCounter(0), unk494(0), mStreakMeterOffset(2.25f), mStreakMeterTilt(0), mTrackPitch(0),
    mEffectSelector(this, 0), mRotater(this, 0), mSurfaceTexture(this, 0), mSurfaceMesh(this, 0), mSurfaceMat(this, 0), mTrackEnv(this, 0), mTrackMissGemsEnv(this, 0), mGameCam(this, 0),
    mPeakStateOnTrig(this, 0), mPeakStateOffTrig(this, 0), mPeakStopImmediateTrig(this, 0), mBassSuperStreakOnTrig(this, 0), mBassSuperStreakOffTrig(this, 0), mBassSSOffImmediateTrig(this, 0), mKickDrummerTrig(this, 0),
    mKickDrummerResetTrig(this, 0), mSpotlightPhraseSuccessTrig(this, 0), mDrumFillResetTrig(this, 0), mDrumMash2ndPassActivateAnim(this, 0), mDrumMashHitAnimGrp(this, 0),
    mFillColorsGrp(this, 0), mLodAnim(this, 0), mSmasherPlate(this, 0), mGlowWidgets(this, kObjListNoNull), unk600(this, 0), unk60c(this, 0), unk618(this, 0),
    unk624(this, 0), mGemWhiteMesh(this, 0), mMissOutofRangeRightTrig(this, 0), mMissOutofRangeLeftTrig(this, 0), unk654(this, 0), mKeysShiftAnim(this, 0), mKeysMashAnim(this, 0), unk678(-1.0f), unk67c(-1.0f),
    mFingerShape(0), mChordLabelPosOffset(0), mChordShapeGen(this, 0), mArpShapePool(0), unk6e8(0), mFakeFingerShape(0), mCycleFakeFingerShapes(0), mRandomShapeFrameCount(0x96) {
    ObjPtr<RndPropAnim, ObjectDir> propAnim(this, 0);
    ObjPtr<EventTrigger, ObjectDir> trig(this, 0);
    for(int i = 0; i < 6; i++){
        mGemMashAnims.push_back(propAnim);
        mDrumMashAnims.push_back(propAnim);
        mFillLaneAnims.push_back(propAnim);
        mRGMashAnims.push_back(propAnim);
        mDrumRollTrigs.push_back(std::make_pair(trig, trig));
        mTrillTrigs.push_back(std::make_pair(trig, trig));
    }
    for(int i = 0; i < 3; i++){
        mFillHitTrigs.push_back(trig);
    }
    for(int i = 0; i < 5; i++){
        mFretPosOffsets.push_back(0);
    }
    DataArray* cfg = SystemConfig();
    DataArray* arr = cfg->FindArray("fake_finger_shape", false);
    if(arr){
        for(int i = 0; i < 6; i++){
            unk6f0.FretDown(i, arr->Int(i + 1));
        }
        mFakeFingerShape = true;
        if(arr->Size() > 7) mCycleFakeFingerShapes = arr->Int(7);
    }
}

GemTrackDir::~GemTrackDir(){
    RELEASE(mArpShapePool);
    RELEASE(mFingerShape);
}
#pragma pop

SAVE_OBJ(GemTrackDir, 0xBC)

DECOMP_FORCEACTIVE(GemTrackDir, "ObjPtr_p.h", "f.Owner()", "")

void GemTrackDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0xC, 0);
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
    if(unk10 != 6 && unk10 != 5) b1 = false;
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
    HANDLE_ACTION(toggle_key_shifting, ToggleKeyShifting())
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
    SYNC_PROP(real_guitar_mash_0_anim, mRGMashAnims[0])
    SYNC_PROP(real_guitar_mash_1_anim, mRGMashAnims[1])
    SYNC_PROP(real_guitar_mash_2_anim, mRGMashAnims[2])
    SYNC_PROP(real_guitar_mash_3_anim, mRGMashAnims[3])
    SYNC_PROP(real_guitar_mash_4_anim, mRGMashAnims[4])
    SYNC_PROP(real_guitar_mash_5_anim, mRGMashAnims[5])
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
    SYNC_PROP(fake_finger_shape, mFakeFingerShape)
    SYNC_PROP(cycle_fake_finger_shapes, mCycleFakeFingerShapes)
    SYNC_PROP(random_shape_frame_count, mRandomShapeFrameCount)
    SYNC_SUPERCLASS(BandTrack)
    SYNC_SUPERCLASS(TrackDir)
END_PROPSYNCS