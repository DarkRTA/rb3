#include "bandobj/BandCrowdMeter.h"
#include "bandobj/TrackPanelDirBase.h"
#include "bandobj/TrackPanelInterface.h"
#include "rndobj/Utl.h"
#include "utl/Symbols.h"
#include <algorithm>

INIT_REVS(BandCrowdMeter);

BandCrowdMeter::BandCrowdMeter() : mMaxed(0), mPeakValue(1.0f), mDisabled(0), unk1a8(2), mTrackPanel(0), mOrderedPeaks(this, kObjListNoNull), mBandEnergyDeployTrig(this, 0),
    mBandEnergyStopTrig(this, 0), mDisabledStartTrig(this, 0), mDisabledStopTrig(this, 0), mShowPeakArrowTrig(this, 0), mHidePeakArrowTrig(this, 0),
    mCanJoinTrig(this, 0), mCannotJoinTrig(this, 0), mJoinInvalidTrig(this, 0), unk234(2), mCrowdMeterAnim(this, 0), mValue(0.5f) {
    for(int i = 0; i < 5; i++) mLevelColors.push_back(Hmx::Color(0));
    for(int i = 0; i < 5; i++) mIconValues[i] = 0.5f;
}

BandCrowdMeter::~BandCrowdMeter(){

}

void BandCrowdMeter::IconData::Reset(){
    unk0->Reset();
    unk0->ArrowShow(true);
    SetUsed(false);
    unk1c = 0;
    unk18 = 0;
    unk1a = 0;
    unk19 = 0;
}

void BandCrowdMeter::IconData::SetVal(float val){
    if(val != unk1c){
        unk1c = val;
        unk20 = true;
    }
}

void BandCrowdMeter::IconData::SetUsed(bool used){
    mUsed = used;
    unk0->SetShowing(used);
}

float BandCrowdMeter::InitialCrowdRating() const {
    if(mTrackPanel) return mTrackPanel->CrowdRatingDefaultVal(easy);
    else return 0.5f;
}

void BandCrowdMeter::Reset(){
    mOrderedPeaks.clear();
    ShowPeakArrow(false);
    bool editmode = TheLoadMgr.EditMode();
    for(int i = 0; i < mIconData.size(); i++){
        mIconData[i].Reset();
        mIconData[i].unkc->SetFrame(InitialCrowdRating(), 1.0f);
        if(editmode){
            mIconData[i].SetUsed(true);
        }
    }
    mDisabledStopTrig->Trigger();
    UpdateExcitement(true);
    unk234 = 2;
}

void BandCrowdMeter::UpdatePlayers(const std::vector<TrackInstrument>& insts){
    bool draining = Draining();
    bool deploying = Deploying();
    for(int i = 0; i < insts.size(); i++){
        IconData& curicon = mIconData[i];
        bool curused = curicon.Used();
        bool i10 = 0;
        if(insts[i] != kInstNone && insts[i] != kInstPending){
            if(curicon.unk0->HasIcon()) i10 = 1;
        }
        if(i10 != curused){
            curicon.SetUsed(i10);
            if(!i10){
                curicon.unk18 = 0;
                curicon.unk1a = 0;
                if(curicon.unk19){
                    curicon.unk19 = 0;
                    mOrderedPeaks.remove(curicon.unkc);
                }
            }
        }
    }
    if(draining && !Draining()){
        mDisabledStopTrig->Trigger();
        UpdateExcitement(true);
    }
    if(deploying && !Deploying()){
        mBandEnergyStopTrig->Trigger();
    }
}

void BandCrowdMeter::Poll(){
    RndDir::Poll();
    if(!mDisabled && !TheLoadMgr.EditMode()){
        int oldgrpsize = mOrderedPeaks.size();
        float f13 = GetPeakValue();
        for(int i = 0; i < mIconData.size(); i++){
            IconData& curicon = mIconData[i];
            if(curicon.Used() && curicon.unk20){
                float f15 = curicon.unk1c;
                curicon.unkc->GetFrame();
                if(f13 >= f15){
                    if(!curicon.unk19){
                        curicon.unk19 = 1;
                        mOrderedPeaks.push_back(curicon.unkc);
                        curicon.unk0->ArrowShow(false);
                    }
                }
                else {
                    if(curicon.unk19){
                        curicon.unk19 = 0;
                        mOrderedPeaks.remove(curicon.unkc);
                        curicon.unk0->ArrowShow(true);
                    }
                    curicon.unkc->SetFrame(curicon.unk1c, 1.0f);
                }
                curicon.unk20 = 0;
            }
        }
        int idx = 0;
        for(ObjPtrList<RndGroup, ObjectDir>::iterator it = mOrderedPeaks.begin(); it != mOrderedPeaks.end(); ++it, ++idx){
            float loc80 = idx + 2.0f;
            RndGroup* curgrp = *it;
            float d15 = curgrp->GetFrame();
            if(d15 < loc80){
                float max = std::max(1.0f, loc80 - d15);
                float min = std::min(loc80, d15 + (max * 0.1f));
                curgrp->SetFrame(max, 1.0f);              
            }
            else if(d15 > loc80){
                float max = std::max(1.0f, d15 - loc80);
                max = std::max(loc80, d15 + (max * -0.1f));
                curgrp->SetFrame(max, 1.0f);
            }
        }
        std::sort(mDraws.begin(), mDraws.end(), SortDraws);
        if(mOrderedPeaks.size() != oldgrpsize){
            ShowPeakArrow(mOrderedPeaks.size());
        }
    }
}

float BandCrowdMeter::GetPeakValue(){
    float f3 = 1.0f;
    if(mOrderedPeaks.size() <= 0) return f3;
    for(int i = 0; i < mIconData.size(); i++){
        if(mIconData[i].mUsed && mIconData[i].unk1c >= 1.0f) return mPeakValue;
    }
    return f3;
}

TrackInstrument GetTrackInstrument(Symbol s){
    if(s == guitar) return kInstGuitar;
    else if(s == drum) return kInstDrum;
    else if(s == bass) return kInstBass;
    else if(s == vocals) return kInstVocals;
    else if(s == keys) return kInstKeys;
    else if(s == real_guitar) return kInstRealGuitar;
    else if(s == real_bass) return kInstRealBass;
    else if(s == real_keys) return kInstRealKeys;
    else if(s == pending) return kInstPending;
    else if(s == pending_vocals) return kInstVocals;
    else {
        MILO_NOTIFY_ONCE("invalid instrument name '%s', defaulting to guitar", s.Str());
        return kInstGuitar;
    }
}

void BandCrowdMeter::SetPlayerValue(int trackIdx, float val){
    MILO_ASSERT(( 0) <= (trackIdx) && (trackIdx) < ( mIconData.size()), 0x13F);
    mIconData[trackIdx].SetVal(val);
}

void BandCrowdMeter::Disable(){
    mDisabled = true;
}

bool BandCrowdMeter::Draining() const {
    if(mDisabled) return false;
    for(int i = 0; i < mIconData.size(); i++){
        if(mIconData[i].mUsed && mIconData[i].unk18) return true;
    }
    return false;
}

bool BandCrowdMeter::Deploying() const {
    if(mDisabled) return false;
    for(int i = 0; i < mIconData.size(); i++){
        if(mIconData[i].mUsed && mIconData[i].unk1a) return true;
    }
    return false;
}

void BandCrowdMeter::Enable(){
    mDisabled = false;
}

bool BandCrowdMeter::Disabled() const {
    return mDisabled || mIconData.empty();
}

void BandCrowdMeter::SetCrowd(float f){
    if(mCrowdMeterAnim) mCrowdMeterAnim->SetFrame(f, 1.0f);
    UpdateExcitement(false);
}

void BandCrowdMeter::UpdateExcitement(bool b){
    if(!mDisabled){
        int i = unk1a8;
        if(mTrackPanel) i = mTrackPanel->GetGameExcitement();
        if(i != unk1a8 || b){
            unk1a8 = i;
            bool peak = unk1a8 == 4;
            if(mMaxed != peak){
                SetMaxed(peak);
            }
            if(!Draining()) mExcitementTrigs[unk1a8]->Trigger();
        }
    }
}

void BandCrowdMeter::SetPlayerIconState(int trackIdx, CrowdMeterState cstate){
    MILO_ASSERT(( 0) <= (trackIdx) && (trackIdx) < ( mIconData.size()), 0x193);
    mIconData[trackIdx].unk0->SetState(cstate, false);
}

void BandCrowdMeter::SetPlayerQuarantined(int trackIdx, bool b){
    MILO_ASSERT(( 0) <= (trackIdx) && (trackIdx) < ( mIconData.size()), 0x199);
    mIconData[trackIdx].unk0->SetQuarantined(b);
}

void BandCrowdMeter::DropInPlayer(int trackIdx){
    MILO_ASSERT(( 0) <= (trackIdx) && (trackIdx) < ( mIconData.size()), 0x19F);
    mIconData[trackIdx].unk0->DropIn();
}

void BandCrowdMeter::DropOutPlayer(int trackIdx){
    MILO_ASSERT(( 0) <= (trackIdx) && (trackIdx) < ( mIconData.size()), 0x1A5);
    mIconData[trackIdx].unk0->DropOut();
}

void BandCrowdMeter::SetMaxed(bool b){
    mMaxed = b;
    if(mTrackPanel) mTrackPanel->PushCrowdReaction(mMaxed);
}

void BandCrowdMeter::Deploy(int trackIdx){
    MILO_ASSERT(( 0) <= (trackIdx) && (trackIdx) < ( mIconData.size()), 0x1B2);
    if(!mDisabled){
        if(!Deploying()) mBandEnergyDeployTrig->Trigger();
        mIconData[trackIdx].unk0->Deploy();
        mIconData[trackIdx].unk1a = true;
    }
}

void BandCrowdMeter::StopDeploy(int trackIdx){
    MILO_ASSERT(( 0) <= (trackIdx) && (trackIdx) < ( mIconData.size()), 0x1C1);
    if(!mDisabled){
        mIconData[trackIdx].unk1a = false;
        if(!Deploying()) mBandEnergyStopTrig->Trigger();
        mIconData[trackIdx].unk0->StopDeploy();
    }
}

void BandCrowdMeter::EnablePlayer(int trackIdx){
    MILO_ASSERT(( 0) <= (trackIdx) && (trackIdx) < ( mIconData.size()), 0x1D0);
    if(mIconData[trackIdx].unk18){
        mIconData[trackIdx].unk18 = false;
        if(!Draining()){
            mDisabledStopTrig->Trigger();
            UpdateExcitement(true);
        }
    }
}

void BandCrowdMeter::DisablePlayer(int trackIdx){
    MILO_ASSERT(( 0) <= (trackIdx) && (trackIdx) < ( mIconData.size()), 0x1DE);
    if(!mIconData[trackIdx].unk18){
        if(mDisabledStartTrig && !Draining()){
            mDisabledStartTrig->Trigger();
        }
        mIconData[trackIdx].unk18 = true;
    }
}

CrowdMeterIcon* BandCrowdMeter::PlayerIcon(int trackIdx){
    MILO_ASSERT(( 0) <= (trackIdx) && (trackIdx) < ( mIconData.size()), 0x1EA);
    return mIconData[trackIdx].unk0;
}

void BandCrowdMeter::ShowPeakArrow(bool b){
    if(b) mShowPeakArrowTrig->Trigger();
    else mHidePeakArrowTrig->Trigger();
}

void BandCrowdMeter::OnShowWorstCase(){
    mIconData[0].unkc->SetFrame(0, 1.0f);
    for(int i = 1; i < mIconData.size(); i++){
        mIconData[i].unkc->SetFrame((float)i + 2.0f, 1.0f);
    }
}

void BandCrowdMeter::SetIconVal(int idx, float f){
    MILO_ASSERT(( 0) <= (idx) && (idx) < ( mIconData.size()), 0x1FF);
    mIconData[idx].SetVal(f);
}

void BandCrowdMeter::UpdateJoinInProgress(bool b1, bool b2){
    if(!b1 != unk234){
        unk234 = !b1;
        if(b1) mCanJoinTrig->Trigger();
        else mCannotJoinTrig->Trigger();
    }
}

void BandCrowdMeter::FailedJoinInProgress(){
    mJoinInvalidTrig->Trigger();
}

BandCrowdMeter::IconData::IconData(BandCrowdMeter* bcm, CrowdMeterIcon* icon, RndGroup* grp) : unk0(bcm, icon), unkc(bcm, grp),
    unk18(0), unk19(0), unk1a(0), mUsed(0), unk1c(0), unk20(0) {

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

SAVE_OBJ(BandCrowdMeter, 0x251)

void BandCrowdMeter::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    if(!IsProxy()){
        if(gRev < 3){
            ObjVector<ObjPtr<RndGroup, ObjectDir> > groupvec(this);
            bs >> groupvec;
        }
        if(gRev >= 2) bs >> mLevelColors;
    }
    if(gRev >= 1) bs >> mPeakValue;
    RndDir::PreLoad(bs);
}

void BandCrowdMeter::PostLoad(BinStream& bs){
    RndDir::PostLoad(bs);
}

BEGIN_COPYS(BandCrowdMeter)
    COPY_SUPERCLASS(RndDir)
    CREATE_COPY(BandCrowdMeter)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax){
            COPY_MEMBER(mAnims)
            COPY_MEMBER(mPeakValue)
            COPY_MEMBER(mLevelColors)
        }
    END_COPYING_MEMBERS
END_COPYS

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
    if(mIconData.size() != 5){
        mIconData.clear();
        for(int i = 0; i < 5; i++){
            mIconData.push_back(IconData(this, Find<CrowdMeterIcon>(MakeString("icon_%1d", i), true), Find<RndGroup>(MakeString("icon_%d.grp", i), true)));
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