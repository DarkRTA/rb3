#include "bandobj/BandTrack.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

INIT_REVS(BandTrack);

BandTrack::BandTrack(Hmx::Object* o) : mDisabled(0), mSimulatedNet(0), mInstrument(""), unk14(4), unk18(0), unk19(0), unk1a(0), unk1b(0), unk1c(0), mInUse(0), unk1e(0), unk1f(0),
    mPlayerIntro(o, 0), mStarPowerMeter(o, 0), mStreakMeter(o, 0), mPopupObject(o, 0), mPlayerFeedback(o, 0), mFailedFeedback(o, 0), mUnisonIcon(o, 0), unk74(""), unk78(0),
    mEndgameFeedback(o, 0), unk88(0), unk8c(0), mParent(o, 0), mRetractTrig(o, 0), mResetTrig(o, 0), mDeployTrig(o, 0), mStopDeployTrig(o, 0), mIntroTrig(o, 0), unkd8(o, 0),
    unke4(o, 0), unkf0(o, 0), unkfc(this, 0), unk108(1), unk109(1), unk10c(-1) {

}

BEGIN_COPYS(BandTrack)
END_COPYS

BEGIN_LOADS(BandTrack)
END_LOADS

void BandTrack::Save(BinStream&){}

DECOMP_FORCEACTIVE(BandTrack, __FILE__, "0")

void BandTrack::LoadTrack(BinStream& bs, bool b1, bool b2, bool b3){
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    if(b2){
        Symbol s;
        bool bbb;
        bs >> bbb;
        bs >> s;
    }
    else {
        bs >> mSimulatedNet;
        bs >> mInstrument;
    }
    if(gRev >= 1 && !b1){
        bs >> mStarPowerMeter;
        bs >> mStreakMeter;
    }
    bool finalbool;
    if(gRev < 3){
        finalbool = false;
        if(!b3 || !b1) finalbool = true;
    }
    else finalbool = !b1;
    if(finalbool){
        bs >> mPlayerIntro;
        if(gRev < 1){
            bs >> mStarPowerMeter;
            bs >> mStreakMeter;
        }
        bs >> mPopupObject;
        bs >> mPlayerFeedback;
        bs >> mFailedFeedback;
        if(gRev >= 2) bs >> mEndgameFeedback;
    }
    if(!b1){
        bs >> mRetractTrig;
        bs >> mResetTrig;
        bs >> mDeployTrig;
        bs >> mStopDeployTrig;
        bs >> mIntroTrig;
    }
}

void BandTrack::CopyTrack(const BandTrack* c){
    COPY_MEMBER(mDisabled)
    COPY_MEMBER(mSimulatedNet)
    COPY_MEMBER(mInstrument)
    COPY_MEMBER(mPlayerIntro)
    COPY_MEMBER(mStarPowerMeter)
    COPY_MEMBER(mStreakMeter)
    COPY_MEMBER(mPopupObject)
    COPY_MEMBER(mPlayerFeedback)
    COPY_MEMBER(mFailedFeedback)
    COPY_MEMBER(mEndgameFeedback)
    COPY_MEMBER(mRetractTrig)
    COPY_MEMBER(mResetTrig)
    COPY_MEMBER(mDeployTrig)
    COPY_MEMBER(mStopDeployTrig)
    COPY_MEMBER(mIntroTrig)
}

void BandTrack::Init(Hmx::Object* o){
    if(o) mParent = dynamic_cast<TrackInterface*>(o);
    Reset();
}

void BandTrack::ResetStreakMeter(){
    if(mStreakMeter){
        mStreakMeter->Reset();
        if(mParent && mParent->HasPlayer()){
            mStreakMeter->SetShowing(true);
        }
        SetStreak(0, 1, 1, true);
    }
}

void BandTrack::Reset(){
    if(mStarPowerMeter){
        mStarPowerMeter->Reset();
        if(mParent && mParent->HasPlayer() && !unk1b){
            mStarPowerMeter->SetShowing(unk108);
        }
        if(mParent) mParent->SetCanDeploy(false);
    }
    ResetStreakMeter();
    if(mPlayerFeedback){
        mPlayerFeedback->HandleType(reset_msg);
        SendTrackerDisplayMessage(disable_msg);
    }
    if(mFailedFeedback){
        mFailedFeedback->HandleType(reset_msg);
        if(mParent){
            if(mParent->GetNoBackFromBrink()){
                mFailedFeedback->SetProperty(no_saving, DataNode(1));
            }
        }
        delete unkf0;
    }
    ClearFinaleHelp();
    if(mParent){
        mParent->SetBonusGems(false);
        FillReset();
    }
    if(!mResetTrig) mResetTrig = ThisDir()->Find<EventTrigger>("reset.trig", false);
    if(mResetTrig) mResetTrig->Trigger();
    unk1c = false;
    TrackReset();
    StopDeploy();
    if(mStreakMeter){
        mStreakMeter->SetBandMultiplier(1);
        mStreakMeter->EndOverdrive();
    }
    if(mPopupObject){
        ResetPopup();
        if(mParent){
            mPopupObject->SetProperty("popup_help_disabled", DataNode(mParent->ShouldDisablePopupHelp() || unk1e));
        }
    }
    SetupPlayerIntro();
    if(mParent && mParent->InGame()){
        SetupCrowdMeter();
    }
    ResetEffectSelector();
}

void BandTrack::PracticeReset(){
    ThisDir()->Find<EventTrigger>("reset_practice.trig", true)->Trigger();
}

void BandTrack::ShowOverdriveMeter(bool show){
    unk108 = show;
    mStarPowerMeter->SetShowing(show);
}

void BandTrack::SetMaxMultiplier(int mult){
    unk14 = mult;
    if(mStreakMeter) mStreakMeter->mMaxMultiplier = mult;
}

void BandTrack::SetupPlayerIntro(){
    if(mPlayerIntro){
        mPlayerIntro->HandleType(reset_msg);
        if(unk10 <= 7){
            static Message setIcon = Message("set_icon", DataNode("G"));
            if(mParent){
                setIcon[0] = DataNode(mParent->GetTrackIcon());
                mParent->SetUserNameLabel(mPlayerIntro, "player_name.lbl");
            }
            mPlayerIntro->HandleType(setIcon);
        }
    }
}

void BandTrack::SetupCrowdMeter(){
    static Hmx::Object* gameMode = ThisDir()->FindObject("gamemode", true);
    unk109 = gameMode->Property("update_crowd_meter", true)->Int(0);
    BandCrowdMeter* meter = GetCrowdMeter();
    const char* icon = mParent ? mParent->GetTrackIcon() : MakeString("G");
    if(meter && !meter->Disabled() && unk10c > -1){
        CrowdMeterIcon* micon = meter->PlayerIcon(unk10c);
        micon->SetIcon(icon);
        micon->unk240 = dynamic_cast<TrackPanelDirBase*>(ThisDir());
    }
    if(mUnisonIcon) mUnisonIcon->SetIcon(icon);
}

void BandTrack::Retract(bool b){
    if(b){
        Reset();
        EventTrigger* trig = ThisDir()->Find<EventTrigger>("immediate_retract.trig", false);
        if(trig) trig->Trigger();
    }
    else {
        if(!mRetractTrig) mRetractTrig = ThisDir()->Find<EventTrigger>("retract.trig", false);
        if(mRetractTrig) mRetractTrig->Trigger();
        if(mPlayerFeedback){
            mPlayerFeedback->HandleType(reset_msg);
            SendTrackerDisplayMessage(disable_msg);
        }
    }
}

void BandTrack::StartFinale(unsigned int ui){
    unk88 = ui;
    unk8c = true;
    GameWon();
    bool bbb = false;
    if(mParent && mParent->HasLocalPlayer()) bbb = true;
    if(bbb){
        if(mEndgameFeedback){
            static Message finale_start("end_game_start_inst", DataNode(""));
            finale_start[0] = DataNode(mInstrument);
            mEndgameFeedback->HandleType(finale_start);
        }
    }
}

void BandTrack::GameWon(){
    if(mPlayerFeedback){
        mPlayerFeedback->HandleType(reset_msg);
        SendTrackerDisplayMessage(disable_msg);
    }
    GameOver();
}

void BandTrack::GameOver(){
    if(mPlayerIntro) mPlayerIntro->HandleType(reset_msg);
    ResetPopup();
    if(mFailedFeedback) mFailedFeedback->HandleType(reset_msg);
    Retract(false);
    delete unkf0;
}

void BandTrack::SpotlightFail(bool guilty){
    if(guilty){
        EventTrigger* trig = ThisDir()->Find<EventTrigger>("spotlight_fail_guilty.trig", false);
        if(trig) trig->Trigger();
        if(mUnisonIcon) mUnisonIcon->Fail();
    }
    else {
        EventTrigger* trig = ThisDir()->Find<EventTrigger>("spotlight_fail.trig", false);
        if(trig) trig->Trigger();
    }
}

void BandTrack::SpotlightPhraseSuccess(){
    if(dynamic_cast<TrackPanelDirBase*>(ThisDir())){
        if(dynamic_cast<TrackPanelDirBase*>(ThisDir())->GetEndingBonus()){

        }
    }
}

void BandTrack::FillReset(){
    EventTrigger* trig = ThisDir()->Find<EventTrigger>("solo_reset.trig", false);
    if(trig) trig->Trigger();
}

// void __thiscall BandTrack::FillReset(BandTrack *this)

// {
//   ObjectDir *this_00;
//   undefined4 uVar1;
//   int iVar2;
  
//   this_00 = (ObjectDir *)(**(code **)(*(int *)(this + 4) + 0x6c))();
//   uVar1 = ObjectDir::FindObject(this_00,s_solo_reset.trig_80bf2e8d,false);
//   iVar2 = __dynamic_cast(uVar1,0,&EventTrigger::__RTTI,&Hmx::Object::__RTTI,0);
//   if (iVar2 != 0) {
//     (**(code **)(*(int *)(iVar2 + 4) + 0x50))();
//   }
//   return;
// }