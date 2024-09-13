#include "bandobj/GemTrackDir.h"
#include "utl/Symbols.h"

#pragma push
#pragma dont_inline on
GemTrackDir::GemTrackDir() : BandTrack(this), mNumTracks(1), unk488(-1), mGemTrackDirID(-1), mKickPassCounter(0), unk494(0), mStreakMeterOffset(2.25f), mStreakMeterTilt(0), mTrackPitch(0),
    mEffectSelector(this, 0), mRotater(this, 0), mSurfaceTexture(this, 0), mSurfaceMesh(this, 0), mSurfaceMat(this, 0), mTrackEnv(this, 0), unk4ec(this, 0), mGameCam(this, 0),
    mPeakStateOnTrig(this, 0), mPeakStateOffTrig(this, 0), unk51c(this, 0), mBassSuperStreakOnTrig(this, 0), mBassSuperStreakOffTrig(this, 0), unk540(this, 0), mKickDrummerTrig(this, 0),
    mKickDrummerResetTrig(this, 0), mSpotlightPhraseSuccessTrig(this, 0), mDrumFillResetTrig(this, 0), mDrumMash2ndPassActivateAnim(this, 0), mDrumMashHitAnimGrp(this, 0),
    mFillColorsGrp(this, 0), mLodAnim(this, 0), mSmasherPlate(this, 0), mGlowWidgets(this, kObjListNoNull), unk600(this, 0), unk60c(this, 0), unk618(this, 0),
    unk624(this, 0), unk630(this, 0), unk63c(this, 0), unk648(this, 0), unk654(this, 0), unk660(this, 0), unk66c(this, 0), unk678(-1.0f), unk67c(-1.0f),
    unk698(0), mChordLabelPosOffset(0), unk6a8(this, 0), mArpShapePool(0), unk6e8(0), mFakeFingerShape(0), mCycleFakeFingerShapes(0), mRandomShapeFrameCount(0x96) {
    ObjPtr<RndPropAnim, ObjectDir> propAnim(this, 0);
    ObjPtr<EventTrigger, ObjectDir> trig(this, 0);
    for(int i = 0; i < 6; i++){
        mGemMashAnims.push_back(propAnim);
        mDrumMashAnims.push_back(propAnim);
        mFillLaneAnims.push_back(propAnim);
        mRGMashAnims.push_back(propAnim);
        unk590.push_back(std::make_pair(trig, trig));
        unk598.push_back(std::make_pair(trig, trig));
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
    RELEASE(unk698);
}
#pragma pop

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