#include "game/TrainerGemTab.h"
#include "bandobj/BandLabel.h"
#include "rndobj/Dir.h"
#include "os/Debug.h"
#include "rndobj/Anim.h"
#include "rndobj/Group.h"
#include "rndobj/Mesh.h"

// fn_801703DC
TrainerGemTab::TrainerGemTab() : mGemTab(0), mLanes(0), mConfigAnim(0), mVerticalTrans(0), mDrawOrderGroup(0), unk48(0), unk54(0),
    mTrackGroup(0), mGemSustainCyan(0), mStartLabel(0), mFinishLabel(0), unk12c(0), mLefty(0) {
    for(int i = 0; i < 6; i++) mTails[i] = 0;
    for(int i = 0; i < 9; i++) mGems[i] = 0;
    for(int i = 0; i < 25; i++) mInstLanes[i] = 0;
    for(int i = 0; i < 4; i++) mNumLabels[i] = 0;
}

TrainerGemTab::~TrainerGemTab(){
    
}

// fn_80170944
void TrainerGemTab::Init(RndDir* gemTab, TrackType ty){
    MILO_ASSERT(gemTab, 0x3F);
    mGemTab = gemTab;
    mTrackType = ty;
    mConfigAnim = mGemTab->Find<RndAnimatable>("instrument_config.anim", true);
    mDrawOrderGroup = mGemTab->Find<RndGroup>("draw_order.grp", true);
    mTrackGroup = mGemTab->Find<RndGroup>("track.grp", true);
    mVerticalTrans = mGemTab->Find<RndAnimatable>("gem_vertical_trans.anim", true);
    mStartLabel = mGemTab->Find<BandLabel>("start.lbl", true);
    mFinishLabel = mGemTab->Find<BandLabel>("finish.lbl", true);
    mNumLabels[0] = mGemTab->Find<BandLabel>("num_1.lbl", true);
    mNumLabels[1] = mGemTab->Find<BandLabel>("num_2.lbl", true);
    mNumLabels[2] = mGemTab->Find<BandLabel>("num_3.lbl", true);
    mNumLabels[3] = mGemTab->Find<BandLabel>("num_4.lbl", true);
    mGemTab->SetShowing(false);
    for(int i = 0; i < 4; i++){
        mNumLabels[i]->SetInt(i + 1, false);
        mNumLabels[i]->SetShowing(false);
    }
    mGemChord2Lane = mGemTab->Find<RndMesh>("gem_chord_2lane.mesh", true);
    mGemChord3Lane = mGemTab->Find<RndMesh>("gem_chord_3lane.mesh", true);
    mGemChord4Lane = mGemTab->Find<RndMesh>("gem_chord_4lane.mesh", true);
    mGemChord5Lane = mGemTab->Find<RndMesh>("gem_chord_5lane.mesh", true);
    mGemChord6Lane = mGemTab->Find<RndMesh>("gem_chord_6lane.mesh", true);
    mGemSustainCyan = mGemTab->Find<RndMesh>("gem_sustain_cyan.mesh", true);
    switch(ty){
        case kTrackDrum:
            mLanes = 5;
            mGems[0] = mGemTab->Find<RndMesh>("gem_drum_kick.mesh", true);
            mGems[1] = mGemTab->Find<RndMesh>("gem_drum_red.mesh", true);
            mGems[2] = mGemTab->Find<RndMesh>("gem_drum_yellow.mesh", true);
            mGems[3] = mGemTab->Find<RndMesh>("gem_drum_blue.mesh", true);
            mGems[4] = mGemTab->Find<RndMesh>("gem_drum_green.mesh", true);
            mGems[5] = mGemTab->Find<RndMesh>("gem_drum_cymbal_red.mesh", true);
            mGems[6] = mGemTab->Find<RndMesh>("gem_drum_cymbal_yellow.mesh", true);
            mGems[7] = mGemTab->Find<RndMesh>("gem_drum_cymbal_blue.mesh", true);
            mGems[8] = mGemTab->Find<RndMesh>("gem_drum_cymbal_green.mesh", true);
            mInstLanes[0] = 0;
            mInstLanes[1] = mGemTab->Find<RndTransformable>("drum_lane_1.trans", true);
            mInstLanes[2] = mGemTab->Find<RndTransformable>("drum_lane_2.trans", true);
            mInstLanes[3] = mGemTab->Find<RndTransformable>("drum_lane_3.trans", true);
            mInstLanes[4] = mGemTab->Find<RndTransformable>("drum_lane_4.trans", true);
            mConfigAnim->SetFrame(2.0f, 1.0f);
            break;
        case kTrackGuitar:
            mLanes = 5;
            mGems[0] = mGemTab->Find<RndMesh>("gem_green.mesh", true);
            mGems[1] = mGemTab->Find<RndMesh>("gem_red.mesh", true);
            mGems[2] = mGemTab->Find<RndMesh>("gem_yellow.mesh", true);
            mGems[3] = mGemTab->Find<RndMesh>("gem_blue.mesh", true);
            mGems[4] = mGemTab->Find<RndMesh>("gem_orange.mesh", true);
            mTails[0] = mGemTab->Find<RndMesh>("gem_sustain_green.mesh", true);
            mTails[1] = mGemTab->Find<RndMesh>("gem_sustain_red.mesh", true);
            mTails[2] = mGemTab->Find<RndMesh>("gem_sustain_yellow.mesh", true);
            mTails[3] = mGemTab->Find<RndMesh>("gem_sustain_blue.mesh", true);
            mTails[4] = mGemTab->Find<RndMesh>("gem_sustain_orange.mesh", true);
            mInstLanes[0] = mGemTab->Find<RndTransformable>("gtrbass_lane_1.trans", true);
            mInstLanes[1] = mGemTab->Find<RndTransformable>("gtrbass_lane_2.trans", true);
            mInstLanes[2] = mGemTab->Find<RndTransformable>("gtrbass_lane_3.trans", true);
            mInstLanes[3] = mGemTab->Find<RndTransformable>("gtrbass_lane_4.trans", true);
            mInstLanes[4] = mGemTab->Find<RndTransformable>("gtrbass_lane_5.trans", true);
            mConfigAnim->SetFrame(0.0f, 1.0f);
            break;
        case kTrackBass:
            mLanes = 4;
            mGems[0] = mGemTab->Find<RndMesh>("gem_green.mesh", true);
            mGems[1] = mGemTab->Find<RndMesh>("gem_red.mesh", true);
            mGems[2] = mGemTab->Find<RndMesh>("gem_yellow.mesh", true);
            mGems[3] = mGemTab->Find<RndMesh>("gem_blue.mesh", true);
            mTails[0] = mGemTab->Find<RndMesh>("gem_sustain_green.mesh", true);
            mTails[1] = mGemTab->Find<RndMesh>("gem_sustain_red.mesh", true);
            mTails[2] = mGemTab->Find<RndMesh>("gem_sustain_yellow.mesh", true);
            mTails[3] = mGemTab->Find<RndMesh>("gem_sustain_blue.mesh", true);
            mInstLanes[0] = mGemTab->Find<RndTransformable>("gtrbass_lane_1.trans", true);
            mInstLanes[1] = mGemTab->Find<RndTransformable>("gtrbass_lane_2.trans", true);
            mInstLanes[2] = mGemTab->Find<RndTransformable>("gtrbass_lane_3.trans", true);
            mInstLanes[3] = mGemTab->Find<RndTransformable>("gtrbass_lane_4.trans", true);
            mConfigAnim->SetFrame(0.0f, 1.0f);
            break;
        case kTrackKeys:
            break;
        case kTrackRealKeys:
            mLanes = 25;
            mGems[0] = mGemTab->Find<RndMesh>("gem_keys_black.mesh", true);
            mGems[1] = mGemTab->Find<RndMesh>("gem_keys_white.mesh", true);
            mTails[0] = mGemTab->Find<RndMesh>("gem_sustain_black.mesh", true);
            mTails[1] = mGemTab->Find<RndMesh>("gem_sustain_white.mesh", true);
            mInstLanes[0] = mGemTab->Find<RndTransformable>("key_lane_1.trans", true);
            mInstLanes[1] = mGemTab->Find<RndTransformable>("key_rail_1.trans", true);
            mInstLanes[2] = mGemTab->Find<RndTransformable>("key_lane_2.trans", true);
            mInstLanes[3] = mGemTab->Find<RndTransformable>("key_rail_2.trans", true);
            mInstLanes[4] = mGemTab->Find<RndTransformable>("key_lane_3.trans", true);
            mInstLanes[5] = mGemTab->Find<RndTransformable>("key_lane_4.trans", true);
            mInstLanes[6] = mGemTab->Find<RndTransformable>("key_rail_3.trans", true);
            mInstLanes[7] = mGemTab->Find<RndTransformable>("key_lane_5.trans", true);
            mInstLanes[8] = mGemTab->Find<RndTransformable>("key_rail_4.trans", true);
            mInstLanes[9] = mGemTab->Find<RndTransformable>("key_lane_6.trans", true);
            mInstLanes[10] = mGemTab->Find<RndTransformable>("key_rail_5.trans", true);
            mInstLanes[11] = mGemTab->Find<RndTransformable>("key_lane_7.trans", true);
            mInstLanes[12] = mGemTab->Find<RndTransformable>("key_lane_8.trans", true);
            mInstLanes[13] = mGemTab->Find<RndTransformable>("key_rail_6.trans", true);
            mInstLanes[14] = mGemTab->Find<RndTransformable>("key_lane_9.trans", true);
            mInstLanes[15] = mGemTab->Find<RndTransformable>("key_rail_7.trans", true);
            mInstLanes[16] = mGemTab->Find<RndTransformable>("key_lane_10.trans", true);
            mInstLanes[17] = mGemTab->Find<RndTransformable>("key_lane_11.trans", true);
            mInstLanes[18] = mGemTab->Find<RndTransformable>("key_rail_8.trans", true);
            mInstLanes[19] = mGemTab->Find<RndTransformable>("key_lane_12.trans", true);
            mInstLanes[20] = mGemTab->Find<RndTransformable>("key_rail_9.trans", true);
            mInstLanes[21] = mGemTab->Find<RndTransformable>("key_lane_13.trans", true);
            mInstLanes[22] = mGemTab->Find<RndTransformable>("key_rail_10.trans", true);
            mInstLanes[23] = mGemTab->Find<RndTransformable>("key_lane_14.trans", true);
            mInstLanes[24] = mGemTab->Find<RndTransformable>("key_lane_15.trans", true);
            mConfigAnim->SetFrame(4.0f, 1.0f);
            break;
        case kTrackRealGuitar:
            mLanes = 6;
            mGems[0] = mGemTab->Find<RndMesh>("gem_red.mesh", true);
            mGems[1] = mGemTab->Find<RndMesh>("gem_green.mesh", true);
            mGems[2] = mGemTab->Find<RndMesh>("gem_orange.mesh", true);
            mGems[3] = mGemTab->Find<RndMesh>("gem_blue.mesh", true);
            mGems[4] = mGemTab->Find<RndMesh>("gem_yellow.mesh", true);
            mGems[5] = mGemTab->Find<RndMesh>("gem_purple.mesh", true);
            mTails[0] = mGemTab->Find<RndMesh>("gem_sustain_red.mesh", true);
            mTails[1] = mGemTab->Find<RndMesh>("gem_sustain_green.mesh", true);
            mTails[2] = mGemTab->Find<RndMesh>("gem_sustain_orange.mesh", true);
            mTails[3] = mGemTab->Find<RndMesh>("gem_sustain_blue.mesh", true);
            mTails[4] = mGemTab->Find<RndMesh>("gem_sustain_yellow.mesh", true);
            mTails[5] = mGemTab->Find<RndMesh>("gem_sustain_purple.mesh", true);
            mInstLanes[0] = mGemTab->Find<RndTransformable>("rg_lane_1.trans", true);
            mInstLanes[1] = mGemTab->Find<RndTransformable>("rg_lane_2.trans", true);
            mInstLanes[2] = mGemTab->Find<RndTransformable>("rg_lane_3.trans", true);
            mInstLanes[3] = mGemTab->Find<RndTransformable>("rg_lane_4.trans", true);
            mInstLanes[4] = mGemTab->Find<RndTransformable>("rg_lane_5.trans", true);
            mInstLanes[5] = mGemTab->Find<RndTransformable>("rg_lane_6.trans", true);
            mConfigAnim->SetFrame(3.0f, 1.0f);
            break;
        case kTrackRealBass:
            mLanes = 4;
            mGems[0] = mGemTab->Find<RndMesh>("gem_red.mesh", true);
            mGems[1] = mGemTab->Find<RndMesh>("gem_green.mesh", true);
            mGems[2] = mGemTab->Find<RndMesh>("gem_orange.mesh", true);
            mGems[3] = mGemTab->Find<RndMesh>("gem_blue.mesh", true);
            mTails[0] = mGemTab->Find<RndMesh>("gem_sustain_red.mesh", true);
            mTails[1] = mGemTab->Find<RndMesh>("gem_sustain_green.mesh", true);
            mTails[2] = mGemTab->Find<RndMesh>("gem_sustain_orange.mesh", true);
            mTails[3] = mGemTab->Find<RndMesh>("gem_sustain_blue.mesh", true);
            mInstLanes[0] = mGemTab->Find<RndTransformable>("rg_lane_1.trans", true);
            mInstLanes[1] = mGemTab->Find<RndTransformable>("rg_lane_2.trans", true);
            mInstLanes[2] = mGemTab->Find<RndTransformable>("rg_lane_3.trans", true);
            mInstLanes[3] = mGemTab->Find<RndTransformable>("rg_lane_4.trans", true);
            mConfigAnim->SetFrame(3.0f, 1.0f);
            break;
        default:
            MILO_ASSERT(false, 0xEC);
            break;
    }
    mVerticalTrans->SetFrame(10.0f, 1.0f);
    if(mGems[0]){
        unk12c = mGems[0]->WorldXfm().v.z;
    }
}

// enum TrackType {
//     kTrackDrum,
//     kTrackGuitar,
//     kTrackBass,
//     kTrackVocals,
//     kTrackKeys,
//     kTrackRealKeys,
//     kTrackRealGuitar,
//     kTrackRealGuitar22Fret,
//     kTrackRealBass,
//     kTrackRealBass22Fret,
//     kTrackNone,
//     kNumTrackTypes,
//     kTrackPending,
//     kTrackPendingVocals
// };
