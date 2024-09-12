#include "bandobj/BandCrowdMeter.h"
#include "bandobj/TrackPanelDirBase.h"
#include "utl/Symbols.h"

BandCrowdMeter::BandCrowdMeter() : mMaxed(0), mPeakValue(1.0f), mDisabled(0), unk1a8(2), unk1ac(0), unk1b0(this, kObjListNoNull), mBandEnergyDeployTrig(this, 0),
    mBandEnergyStopTrig(this, 0), mDisabledStartTrig(this, 0), mDisabledStopTrig(this, 0), mShowPeakArrowTrig(this, 0), mHidePeakArrowTrig(this, 0),
    mCanJoinTrig(this, 0), mCannotJoinTrig(this, 0), mJoinInvalidTrig(this, 0), unk234(2), mCrowdMeterAnim(this, 0), mValue(0.5f) {
    for(int i = 0; i < 5; i++) mLevelColors.push_back(Hmx::Color(0));
    for(int i = 0; i < 5; i++) mIconValues[i] = 0.5f;
}

BandCrowdMeter::~BandCrowdMeter(){

}

TrackInstrument GetTrackInstrument(Symbol);

BandCrowdMeter::IconData::IconData(BandCrowdMeter* bcm, CrowdMeterIcon* icon, RndGroup* grp) : unk0(bcm, icon), unkc(bcm, grp),
    unk18(0), unk19(0), unk1a(0), unk1b(0), unk1c(0), unk20(0) {

}

BEGIN_PROPSYNCS(BandCrowdMeter)
    SYNC_PROP(peak_value, mPeakValue)
    SYNC_PROP_MODIFY(value, mValue, SetCrowd(mValue))
    SYNC_PROP_MODIFY(icon_0_val, mIconValues[0], SetIconVal(0, mIconValues[0]))
    SYNC_PROP_MODIFY(icon_1_val, mIconValues[1], SetIconVal(1, mIconValues[1]))
    SYNC_PROP_MODIFY(icon_2_val, mIconValues[2], SetIconVal(2, mIconValues[2]))
    SYNC_PROP_MODIFY(icon_3_val, mIconValues[3], SetIconVal(3, mIconValues[3]))
    SYNC_PROP_MODIFY(icon_4_val, mIconValues[4], SetIconVal(4, mIconValues[4]))
    SYNC_PROP_MODIFY(maxed, mMaxed, SetMaxed(mMaxed))
    SYNC_PROP(level_colors, mLevelColors)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

BEGIN_HANDLERS(BandCrowdMeter)
    HANDLE_EXPR(get_peak_value, GetPeakValue())
    HANDLE_ACTION(reset_crowd_meter, Reset())
    HANDLE_EXPR(is_enabled, mDisabled == 0)
    HANDLE_ACTION(update_excitement, UpdateExcitement(true))
    HANDLE_ACTION(set_player_icon_state, SetPlayerIconState(GetTrackInstrument(_msg->Sym(2)), (CrowdMeterState)_msg->Int(3)))
    HANDLE_ACTION(deploy, Deploy(GetTrackInstrument(_msg->Sym(2))))
    HANDLE_ACTION(stop_deploy, StopDeploy(GetTrackInstrument(_msg->Sym(2))))
    HANDLE_ACTION(enable_player, EnablePlayer(GetTrackInstrument(_msg->Sym(2))))
    HANDLE_ACTION(disable_player, DisablePlayer(GetTrackInstrument(_msg->Sym(2))))
    HANDLE_ACTION(show_peak_arrow, ShowPeakArrow(true))
    HANDLE_ACTION(hide_peak_arrow, ShowPeakArrow(false))
    HANDLE_ACTION(reset, Reset())
    HANDLE_ACTION(worst_case, OnShowWorstCase())
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x249)
END_HANDLERS

#pragma push
#pragma dont_inline on
void BandCrowdMeter::SyncObjects(){
    if(!mBandEnergyDeployTrig) mBandEnergyDeployTrig = Find<EventTrigger>("band_energy_deploy.trig", true);
    if(!mBandEnergyStopTrig) mBandEnergyStopTrig = Find<EventTrigger>("band_energy_stop.trig", true);
    if(!mDisabledStartTrig) mDisabledStartTrig = Find<EventTrigger>("disabled_start.trig", true);
    if(!mDisabledStopTrig) mDisabledStopTrig = Find<EventTrigger>("disabled_stop.trig", true);
    if(!mShowPeakArrowTrig) mShowPeakArrowTrig = Find<EventTrigger>("show_peak_arrow.trig", true);
    if(!mHidePeakArrowTrig) mHidePeakArrowTrig = Find<EventTrigger>("hide_peak_arrow.trig", true);
    if(!mCrowdMeterAnim) mCrowdMeterAnim = Find<RndMatAnim>("crowd_meter.mnm", true);
    if(!mCanJoinTrig) mCanJoinTrig = Find<EventTrigger>("can_join.trig", true);
    if(!mCannotJoinTrig) mCannotJoinTrig = Find<EventTrigger>("cannot_join.trig", true);
    if(!mJoinInvalidTrig) mJoinInvalidTrig = Find<EventTrigger>("join_invalid.trig", true);
    if(mIcons.size() != 5){
        mIcons.clear();
        for(int i = 0; i < 5; i++){
            mIcons.push_back(IconData(this, Find<CrowdMeterIcon>(MakeString("icon_%1d", i), true), Find<RndGroup>(MakeString("icon_%d.grp", i), true)));
        }
    }
    if(mExcitementTrigs.size() != 5){
        mExcitementTrigs.clear();
        mExcitementTrigs.push_back(ObjPtr<EventTrigger, ObjectDir>(this, Find<EventTrigger>("excitement_boot.trig", true)));
        mExcitementTrigs.push_back(ObjPtr<EventTrigger, ObjectDir>(this, Find<EventTrigger>("excitement_bad.trig", true)));
        mExcitementTrigs.push_back(ObjPtr<EventTrigger, ObjectDir>(this, Find<EventTrigger>("excitement_okay.trig", true)));
        mExcitementTrigs.push_back(ObjPtr<EventTrigger, ObjectDir>(this, Find<EventTrigger>("excitement_great.trig", true)));
        mExcitementTrigs.push_back(ObjPtr<EventTrigger, ObjectDir>(this, Find<EventTrigger>("excitement_peak.trig", true)));
    }
    RndDir::SyncObjects();
}
#pragma pop