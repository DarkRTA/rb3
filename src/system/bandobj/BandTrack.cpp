#include "bandobj/BandTrack.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include <os/Debug.h>

INIT_REVS(BandTrack);

BandTrack::BandTrack(Hmx::Object *o)
    : mDisabled(0), mSimulatedNet(0), mInstrument(""), unk14(4), unk18(0), unk19(0),
      unk1a(0), unk1b(0), unk1c(0), mInUse(0), unk1e(0), mSoloDisplay(0), mPlayerIntro(o, 0),
      mStarPowerMeter(o, 0), mStreakMeter(o, 0), mPopupObject(o, 0),
      mPlayerFeedback(o, 0), mFailedFeedback(o, 0), mUnisonIcon(o, 0), unk74(""),
      unk78(0), mEndgameFeedback(o, 0), unk88(0), unk8c(0), mParent(o, 0),
      mRetractTrig(o, 0), mResetTrig(o, 0), mDeployTrig(o, 0), mStopDeployTrig(o, 0),
      mIntroTrig(o, 0), unkd8(o, 0), unke4(o, 0), unkf0(o, 0), mBeatAnimsGrp(this, 0),
      mShowOverDriveMeter(1), mShowCrowdMeter(1), mTrackIdx(-1) {}

BEGIN_COPYS(BandTrack)
END_COPYS

BEGIN_LOADS(BandTrack)
END_LOADS

void BandTrack::Save(BinStream &) {}

DECOMP_FORCEACTIVE(BandTrack, __FILE__, "0")

void BandTrack::LoadTrack(BinStream &bs, bool b1, bool b2, bool b3) {
    LOAD_REVS(bs);
    ASSERT_REVS(3, 0);
    if (b2) {
        Symbol s;
        bool bbb;
        bs >> bbb;
        bs >> s;
    } else {
        bs >> mSimulatedNet;
        bs >> mInstrument;
    }
    if (gRev >= 1 && !b1) {
        bs >> mStarPowerMeter;
        bs >> mStreakMeter;
    }
    bool finalbool;
    if (gRev < 3) {
        finalbool = false;
        if (!b3 || !b1)
            finalbool = true;
    } else
        finalbool = !b1;
    if (finalbool) {
        bs >> mPlayerIntro;
        if (gRev < 1) {
            bs >> mStarPowerMeter;
            bs >> mStreakMeter;
        }
        bs >> mPopupObject;
        bs >> mPlayerFeedback;
        bs >> mFailedFeedback;
        if (gRev >= 2)
            bs >> mEndgameFeedback;
    }
    if (!b1) {
        bs >> mRetractTrig;
        bs >> mResetTrig;
        bs >> mDeployTrig;
        bs >> mStopDeployTrig;
        bs >> mIntroTrig;
    }
}

void BandTrack::CopyTrack(const BandTrack *c) {
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

void BandTrack::Init(Hmx::Object *o) {
    if (o)
        mParent = dynamic_cast<TrackInterface *>(o);
    Reset();
}

void BandTrack::ResetStreakMeter() {
    if (mStreakMeter) {
        mStreakMeter->Reset();
        if (mParent && mParent->HasPlayer()) {
            mStreakMeter->SetShowing(true);
        }
        SetStreak(0, 1, 1, true);
    }
}

void BandTrack::Reset() {
    if (mStarPowerMeter) {
        mStarPowerMeter->Reset();
        if (mParent && mParent->HasPlayer() && !unk1b) {
            mStarPowerMeter->SetShowing(mShowOverDriveMeter);
        }
        if (mParent)
            mParent->SetCanDeploy(false);
    }
    ResetStreakMeter();
    if (mPlayerFeedback) {
        mPlayerFeedback->HandleType(reset_msg);
        SendTrackerDisplayMessage(disable_msg);
    }
    if (mFailedFeedback) {
        mFailedFeedback->HandleType(reset_msg);
        if (mParent) {
            if (mParent->GetNoBackFromBrink()) {
                mFailedFeedback->SetProperty(no_saving, DataNode(1));
            }
        }
        delete unkf0;
    }
    ClearFinaleHelp();
    if (mParent) {
        mParent->SetBonusGems(false);
        FillReset();
    }
    if (!mResetTrig)
        mResetTrig = ThisDir()->Find<EventTrigger>("reset.trig", false);
    if (mResetTrig)
        mResetTrig->Trigger();
    unk1c = false;
    TrackReset();
    StopDeploy();
    if (mStreakMeter) {
        mStreakMeter->SetBandMultiplier(1);
        mStreakMeter->EndOverdrive();
    }
    if (mPopupObject) {
        ResetPopup();
        if (mParent) {
            mPopupObject->SetProperty(
                "popup_help_disabled",
                DataNode(mParent->ShouldDisablePopupHelp() || unk1e)
            );
        }
    }
    SetupPlayerIntro();
    if (mParent && mParent->InGame()) {
        SetupCrowdMeter();
    }
    ResetEffectSelector();
}

int BandTrack::AsRndDir() {
    TheDebug.Fail(MakeString("BandTrack::AsRndDir() base impl should never be called"));
    return 0;
}

void BandTrack::DropIn() {
    BandCrowdMeter *meter = GetCrowdMeter();
    if ((meter != nullptr) && meter->Disabled() == 0 && mTrackIdx > -1) {
        meter->DropInPlayer(mTrackIdx);
    }
}

void BandTrack::DropOut() {
    BandCrowdMeter *meter = GetCrowdMeter();
    if ((meter != nullptr) && meter->Disabled() == 0 && mTrackIdx > -1) {
        meter->DropOutPlayer(mTrackIdx);
    }
    if (mParent != nullptr) {
        mParent->DTSPopup(false);
    }
}

int BandTrack::GetPlayerDifficulty() const {
    if (mParent)
        return mParent->GetPlayerDifficulty();
    return 0;
}

void BandTrack::PeakState(bool enabled, bool b2) {
    if (enabled != unk1a) {
        if ((enabled != false) && (mStreakMeter != nullptr)) {
            mStreakMeter->SetPeakState();
        }
    }
    unk1a = enabled;
}

void BandTrack::PlayerDisabled() {
    if (mParent == nullptr) {
        return;
    }
    mParent->DTSPopup(true);
}

void BandTrack::PlayerSaved() {
    if (mParent == nullptr) {
        return;
    }
    mParent->DTSPopup(false);
}

void BandTrack::SuperStreak(bool enabled, bool b2) {
    if (enabled != unk19) {
        if ((enabled != false) && (mStreakMeter != nullptr)) {
            mStreakMeter->SetPeakState();
        }
    }
    unk19 = enabled;
}

void BandTrack::PracticeReset() {
    ThisDir()->Find<EventTrigger>("reset_practice.trig", true)->Trigger();
}

void BandTrack::ShowOverdriveMeter(bool show) {
    mShowOverDriveMeter = show;
    mStarPowerMeter->SetShowing(show);
}

void BandTrack::SetMaxMultiplier(int mult) {
    unk14 = mult;
    if (mStreakMeter)
        mStreakMeter->mMaxMultiplier = mult;
}

void BandTrack::SetupPlayerIntro() {
    if (mPlayerIntro) {
        mPlayerIntro->HandleType(reset_msg);
        if (mTrackInstrument <= 7) {
            static Message setIcon = Message("set_icon", DataNode("G"));
            if (mParent) {
                setIcon[0] = DataNode(mParent->GetTrackIcon());
                mParent->SetUserNameLabel(mPlayerIntro, "player_name.lbl");
            }
            mPlayerIntro->HandleType(setIcon);
        }
    }
}

void BandTrack::SetupCrowdMeter() {
    static Hmx::Object *gameMode = ThisDir()->FindObject("gamemode", true);
    mShowCrowdMeter = gameMode->Property("update_crowd_meter", true)->Int(0);
    BandCrowdMeter *meter = GetCrowdMeter();
    const char *icon = mParent ? mParent->GetTrackIcon() : MakeString("G");
    if (meter && !meter->Disabled() && mTrackIdx > -1) {
        CrowdMeterIcon *micon = meter->PlayerIcon(mTrackIdx);
        micon->SetIcon(icon);
        micon->unk240 = dynamic_cast<TrackPanelDirBase *>(ThisDir());
    }
    if (mUnisonIcon)
        mUnisonIcon->SetIcon(icon);
}

void BandTrack::SyncInstrument() {
    Symbol instrument = mInstrument;
    if (instrument == guitar) {
        mTrackInstrument = kInstGuitar;
    } else if (instrument == bass) {
        mTrackInstrument = kInstBass;
    } else if (instrument == drums) {
        mTrackInstrument = kInstDrum;
    } else if (instrument == vocals) {
        mTrackInstrument = kInstVocals;
    } else if (instrument == keys) {
        mTrackInstrument = kInstKeys;
    } else if (instrument == real_guitar) {
        mTrackInstrument = kInstRealGuitar;
    } else if (instrument == real_bass) {
        mTrackInstrument = kInstRealBass;
    } else if (instrument == real_keys) {
        mTrackInstrument = kInstRealKeys;
    } else {
        MILO_NOTIFY_ONCE("unexpected instrument symbol \"%s\"", instrument);

        mTrackInstrument = kInstNone;
    }
}

void BandTrack::Retract(bool b) {
    if (b) {
        Reset();
        EventTrigger *trig =
            ThisDir()->Find<EventTrigger>("immediate_retract.trig", false);
        if (trig)
            trig->Trigger();
    } else {
        if (!mRetractTrig)
            mRetractTrig = ThisDir()->Find<EventTrigger>("retract.trig", false);
        if (mRetractTrig)
            mRetractTrig->Trigger();
        if (mPlayerFeedback) {
            mPlayerFeedback->HandleType(reset_msg);
            SendTrackerDisplayMessage(disable_msg);
        }
    }
}

void BandTrack::StartFinale(unsigned int ui) {
    unk88 = ui;
    unk8c = true;
    GameWon();
    bool bbb = false;
    if (mParent && mParent->HasLocalPlayer())
        bbb = true;
    if (bbb) {
        if (mEndgameFeedback) {
            static Message finale_start("end_game_start_inst", DataNode(""));
            finale_start[0] = DataNode(mInstrument);
            mEndgameFeedback->HandleType(finale_start);
        }
    }
}

void BandTrack::GameWon() {
    if (mPlayerFeedback) {
        mPlayerFeedback->HandleType(reset_msg);
        SendTrackerDisplayMessage(disable_msg);
    }
    GameOver();
}

void BandTrack::GameOver() {
    if (mPlayerIntro)
        mPlayerIntro->HandleType(reset_msg);
    ResetPopup();
    if (mFailedFeedback)
        mFailedFeedback->HandleType(reset_msg);
    Retract(false);
    delete unkf0;
}

BandCrowdMeter *BandTrack::GetCrowdMeter() {
    BandCrowdMeter *meter;
    if (mShowCrowdMeter != false) {
        ObjectDir* objDir = ThisDir()->mDir;
        TrackPanelDirBase *tpDirBase = dynamic_cast<TrackPanelDirBase *>(objDir);
        meter = tpDirBase->GetCrowdMeter();
    } else {
        meter = nullptr;
    }

    return meter;
}

void BandTrack::SetSuppressSoloDisplay(bool b) {
    mSoloDisplay = b;
}

void BandTrack::SoloHide() {
    if (mPlayerFeedback != 0) {
        RndPropAnim *hideSoloAnim = ThisDir()->Find<RndPropAnim>("hide_solo.anim", true);
        float endFrame = hideSoloAnim->EndFrame();
        hideSoloAnim->SetFrame(endFrame, 1.0f);
    }
}

void BandTrack::SpotlightFail(bool guilty) {
    if (guilty) {
        EventTrigger *trig =
            ThisDir()->Find<EventTrigger>("spotlight_fail_guilty.trig", false);
        if (trig)
            trig->Trigger();
        if (mUnisonIcon)
            mUnisonIcon->Fail();
    } else {
        EventTrigger *trig = ThisDir()->Find<EventTrigger>("spotlight_fail.trig", false);
        if (trig)
            trig->Trigger();
    }
}

void BandTrack::SpotlightPhraseSuccess() {
    if (dynamic_cast<TrackPanelDirBase *>(ThisDir())) {
        if (dynamic_cast<TrackPanelDirBase *>(ThisDir())->GetEndingBonus()) {
        }
    }
}

void BandTrack::FillReset() {
    EventTrigger *trig = ThisDir()->Find<EventTrigger>("solo_reset.trig", false);
    if (trig)
        trig->Trigger();
}

void BandTrack::UnisonEnd() {
    if (mUnisonIcon)
        mUnisonIcon->UnisonEnd();
}

void BandTrack::UnisonStart() {
    if (mUnisonIcon)
        mUnisonIcon->UnisonStart();
}

BEGIN_PROPSYNCS(BandTrack)
SYNC_PROP_MODIFY(instrument, mInstrument, SyncInstrument())
SYNC_PROP(disabled, mDisabled)
SYNC_PROP(simulated_net, mSimulatedNet)
SYNC_PROP(player_intro, mPlayerIntro)
SYNC_PROP(star_power_meter, mStarPowerMeter)
SYNC_PROP(streak_meter, mStreakMeter)
SYNC_PROP(popup_object, mPopupObject)
SYNC_PROP(player_feedback, mPlayerFeedback)
SYNC_PROP(failed_feedback, mFailedFeedback)
SYNC_PROP(endgame_feedback, mEndgameFeedback)
SYNC_PROP(parent, mParent)
SYNC_PROP(retract_trig, mRetractTrig)
SYNC_PROP(reset_trig, mResetTrig)
SYNC_PROP(deploy_trig, mDeployTrig)
SYNC_PROP(stop_deploy_trig, mStopDeployTrig)
SYNC_PROP(intro_trig, mIntroTrig)
SYNC_PROP(in_use, mInUse)
END_PROPSYNCS

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandTrack)
HANDLE_ACTION(disable_player, DisablePlayer(_msg->Int(2)))
HANDLE_ACTION(init, Init(_msg->Obj<Hmx::Object>(2)))
HANDLE_ACTION(reset, Reset())
HANDLE_ACTION(tut_reset, TutorialReset())
HANDLE_ACTION(setup_player_intro, SetupPlayerIntro())
HANDLE_ACTION(setup_crowd_meter, SetupCrowdMeter())
HANDLE_ACTION(track_reset, TrackReset())
HANDLE_ACTION(retract, Retract(false))
HANDLE_ACTION(immediate_retract, Retract(true))
HANDLE_ACTION(game_won, GameWon())
HANDLE_ACTION(game_over, GameOver())
HANDLE_ACTION(spotlight_fail, SpotlightFail(false))
HANDLE_ACTION(spotlight_fail_guilty, SpotlightFail(true))
HANDLE_ACTION(fill_reset, FillReset())
HANDLE_ACTION(set_streak, SetStreak(_msg->Int(2), _msg->Int(3), _msg->Int(4), false))
HANDLE_ACTION(enable_player, EnablePlayer())
HANDLE_ACTION(save_player, SavePlayer())
HANDLE_ACTION(super_streak, SuperStreak(_msg->Int(2), false))
HANDLE_ACTION(peak_state, PeakState(_msg->Int(2), false))
HANDLE_ACTION(deploy, Deploy())
HANDLE_ACTION(stop_deploy, StopDeploy())
HANDLE_ACTION(play_intro, PlayIntro())
HANDLE_ACTION(set_multiplier, SetMultiplier(_msg->Int(2)))
HANDLE_ACTION(enter_coda, EnterCoda())
HANDLE_ACTION(coda_blown, CodaFail(false))
HANDLE_ACTION(coda_fail, CodaFail(true))
HANDLE_ACTION(coda_success, CodaSuccess())
HANDLE_ACTION(popup_help, PopupHelp(_msg->Sym(2), _msg->Int(3)))
HANDLE_ACTION(player_disabled, PlayerDisabled())
HANDLE_ACTION(player_saved, PlayerSaved())
HANDLE_ACTION(failed_task, FailedTask(_msg->Int(2), _msg->Int(3)))
HANDLE_EXPR(has_net_player, HasNetPlayer())
HANDLE_EXPR(has_local_player, HasLocalPlayer())
HANDLE_EXPR(get_player_difficulty, GetPlayerDifficulty())
HANDLE_ACTION(set_player_local, SetPlayerLocal(_msg->Float(2)))
HANDLE_ACTION(set_tambourine, SetTambourine(_msg->Int(2)))
HANDLE_ACTION(setup_instrument, SetupInstrument())
HANDLE_CHECK(0x5A9)
END_HANDLERS
#pragma pop