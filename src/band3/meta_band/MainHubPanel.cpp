#include "meta_band/MainHubPanel.h"
#include "MainHubPanel.h"
#include "OvershellPanel.h"
#include "OvershellSlot.h"
#include "bandobj/BandLabel.h"
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "meta_band/BandProfile.h"
#include "meta_band/BandUI.h"
#include "meta_band/LockStepMgr.h"
#include "meta_band/Matchmaker.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/MainHubMessageProvider.h"
#include "meta_band/UIEventMgr.h"
#include "net/NetMessage.h"
#include "net/Server.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Msg.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
#include "utl/Messages3.h"
#include "utl/Symbol.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

namespace {
    class MainHubAdvanceMsg : public NetMessage {
    public:
        MainHubAdvanceMsg() {}
        virtual ~MainHubAdvanceMsg() {}
        virtual void Save(BinStream &bs) const {
            bs << unk4;
            bs << unk8;
        }
        virtual void Load(BinStream &bs) {
            bs >> unk4;
            bs >> unk8;
        }
        virtual void Dispatch();
        NETMSG_BYTECODE(MainHubAdvanceMsg);
        NETMSG_NAME(MainHubAdvanceMsg);

        NETMSG_NEWNETMSG(MainHubAdvanceMsg);

        bool unk4;
        String unk8;
    };

    NetMessage *MainHubAdvanceMsg::NewNetMessage() { return new MainHubAdvanceMsg(); }
}

MainHubPanel::MainHubPanel()
    : mHubState(kMainHubState_Main), mHubOverride(kMainHubOverride_None),
      mMessageProvider(0), mCurrentMessage(0), mMessageRotationMs(3000.0f), unkb8(0),
      unkbc(0), unkc0(kScoreBand) {
    mMachineMgr = TheSessionMgr->mMachineMgr;
    mWaitingStateLock = new LockStepMgr("main_hub_waiting", this);
    MainHubAdvanceMsg::Register();
}

MainHubPanel::~MainHubPanel() {
    delete mMessageProvider;
    delete mWaitingStateLock;
}

void MainHubPanel::Enter() {
    TheProfileMgr.AddSink(this, PrimaryProfileChangedMsg::Type());
    TheSessionMgr->AddSink(this);
    TheSessionMgr->GetMatchmaker()->AddSink(this);
    mMachineMgr->AddSink(this);
    TheBandUI.GetOvershell()->AddSink(this, OvershellOverrideEndedMsg::Type());
    DataArray *rotMsArr = TypeDef()->FindArray(message_rotation_ms, false);
    if (rotMsArr)
        mMessageRotationMs = rotMsArr->Float(1);
    mMessageProvider = new MainHubMessageProvider(this);
    TheServer->AddSink(this, UserLoginMsg::Type());
    UIPanel::Enter();
    RefreshData();
    SetMainHubOverride(kMainHubOverride_None);
    UpdateStateView(mHubState, kMainHubState_None, mHubOverride, kMainHubOverride_None);
}

void MainHubPanel::Poll() {
    UIPanel::Poll();
    if (mMessageTimer.Running() && mMessageTimer.SplitMs() > mMessageRotationMs) {
        mMessageTimer.Restart();
        int num = mMessageProvider->NumData();
        if (num == 0) {
            mMessageTimer.Stop();
            mCurrentMessage = 0;
            PrepareProfilesAndMessages();
        } else {
            mCurrentMessage = (mCurrentMessage + 1) % num;
            UpdateHeader();
        }
    }
}

void MainHubPanel::CycleNextMessage() {
    mMessageTimer.Restart();
    if (mMessageProvider->NumData() > 0) {
        mCurrentMessage++;
        mCurrentMessage %= mMessageProvider->NumData();
    }
    UpdateHeader();
}

void MainHubPanel::Exit() {
    Matchmaker *matchmaker = TheSessionMgr->GetMatchmaker();
    if (matchmaker->IsFinding()) {
        matchmaker->CancelFind();
    }
    if (mHubOverride == kMainHubOverride_ChooseBand && TheSessionMgr->IsLocal()) {
        SetMainHubOverride(kMainHubOverride_None);
    }
    UIPanel::Exit();
    mMachineMgr->RemoveSink(this);
    TheSessionMgr->GetMatchmaker()->RemoveSink(this);
    TheSessionMgr->RemoveSink(this);
    TheProfileMgr.RemoveSink(this, PrimaryProfileChangedMsg::Type());
    TheServer->RemoveSink(this, UserLoginMsg::Type());
    TheBandUI.GetOvershell()->RemoveSink(this, "override_ended");
    unkbc = 0;
    unkc0 = kScoreBand;
}

void MainHubPanel::Unload() {
    UIPanel::Unload();
    RELEASE(mMessageProvider);
}

void MainHubPanel::RefreshData() { PrepareProfilesAndMessages(); }

void MainHubPanel::ReloadMessages() {
    unkb8 = false;
    UpdateMessageProvider();
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    if (profile) {
        LocalBandUser *user = TheBandUserMgr->GetUserFromPad(profile->GetPadNum());
        if (user) {
            if (TheServer->GetPlayerID(profile->GetPadNum())) {
                TrackType ty = user->GetTrackType();
                if (ty - 10U <= 2) {
                    ty = ControllerTypeToTrackType(
                        user->ConnectedControllerType(), RandomInt(0, 2)
                    );
                }
                ScoreType sty = TrackTypeToScoreType(
                    ty,
                    user->GetPreferredScoreType() == 4,
                    user->GetPreferredScoreType() == 6
                );
                if (profile && (profile != unkbc || sty != unkc0)) {
                    unkbc = profile;
                    unkc0 = sty;
                    TheRockCentral.GetTickerInfo(profile, sty, mLabelUpdateResults, this);
                }
            }
        }
    }
}

void MainHubPanel::PrepareProfilesAndMessages() {
    ReloadMessages();
    if (mMessageProvider->NumData() != 0) {
        mCurrentMessage = 0;
        if (mMessageProvider->NumData() > 1) {
            mMessageTimer.Start();
        }
    } else {
        mCurrentMessage = 0;
        HandleType(refresh_message_provider_msg);
    }
    UpdateHeader();
}

bool MainHubPanel::CheckProfileForTicker() {
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    if (profile && TheServer->IsConnected()) {
        if (TheServer->GetPlayerID(profile->GetPadNum()))
            return true;
    }
    return false;
}

void MainHubPanel::UpdateHeader() {
    BandLabel *label = mDir->Find<BandLabel>("message.lbl", true);
    if (mMessageProvider->NumData() != 0) {
        mMessageProvider->SetMessageLabel((AppLabel *)label, mCurrentMessage);
    } else
        label->SetTextToken(gNullStr);
    static Message msg("update_message_counter", 0, 0);
    msg[0] = mCurrentMessage + 1;
    msg[1] = mMessageProvider->NumData();
    HandleType(msg);
}

void MainHubPanel::UpdatePoolInfo() {
    static Message update_pool_info("update_pool_info", 0, 0, 0, 0, 0);
    MatchmakerPoolStats *stats = TheSessionMgr->GetMatchmaker()->mPoolStats;
    update_pool_info[0] = stats->HasCurrentStats();
    if (stats->HasCurrentStats()) {
        for (int i = 0; i < 4; i++) {
            update_pool_info[i + 1] = stats->GetSlotRating(i);
        }
    }
    HandleType(update_pool_info);
}

void MainHubPanel::SetMainHubState(MainHubState state) {
    MainHubState old = mHubState;
    mHubState = state;
    if (GetState() == kUp) {
        UpdateStateView(state, old, mHubOverride, mHubOverride);
    }
}

void MainHubPanel::SetMainHubOverride(MainHubOverride oride) {
    MainHubOverride old = mHubOverride;
    mHubOverride = oride;
    UpdateStateView(mHubState, mHubState, oride, old);
    CheckStartWaitingLock();
    if (mHubOverride == kMainHubOverride_Waiting) {
        StartFinding();
    }
    Matchmaker *maker = TheSessionMgr->GetMatchmaker();
    if (mHubOverride != kMainHubOverride_Waiting && maker->IsFinding()) {
        maker->CancelFind();
    }
    OvershellPanel *panel = TheBandUI.GetOvershell();
    if (old == kMainHubOverride_Waiting && mHubOverride != kMainHubOverride_Waiting
        && panel->mPanelOverrideFlow == kOverrideFlow_RegisterOnline) {
        TheSessionMgr->Disconnect();
        if (panel->mPanelOverrideFlow == kOverrideFlow_RegisterOnline)
            panel->EndOverrideFlow(kOverrideFlow_RegisterOnline, true);
    }
    TheSessionMgr->UpdateInvitesAllowed();
}

void MainHubPanel::StartFinding() {
    if (!TheModifierMgr->IsModifierActive(mod_auto_vocals)) {
        Matchmaker *maker = TheSessionMgr->GetMatchmaker();
        OvershellPanel *panel = TheBandUI.GetOvershell();
        if (TheSessionMgr->IsOnlineEnabled() && !maker->IsFinding()) {
            MILO_ASSERT(mHubState == kMainHubState_Quickplay || mHubState == kMainHubState_Tour, 0x192);
            maker->FindPlayers((MatchmakerFindType)(mHubState != kMainHubState_Quickplay)
            );
        } else if (!TheSessionMgr->IsOnlineEnabled()
                   && panel->mPanelOverrideFlow != kOverrideFlow_RegisterOnline) {
            panel->BeginOverrideFlow(kOverrideFlow_RegisterOnline);
        }
    } else {
        SetMainHubOverride(kMainHubOverride_None);
        TheUIEventMgr->TriggerEvent(error_find_players_with_auto_vocals, nullptr);
    }
}

DataNode MainHubPanel::OnMsg(const OvershellOverrideEndedMsg &msg) {
    if (msg.GetOverrideFlowType() == 2 && mHubOverride == kMainHubOverride_Waiting) {
        if (msg.Cancelled()) {
            HandleType(cancel_find_override_msg);
        } else {
            MILO_ASSERT(mHubState == kMainHubState_Quickplay || mHubState == kMainHubState_Tour, 0x1B7);
            TheSessionMgr->GetMatchmaker()->FindPlayers(
                (MatchmakerFindType)(mHubState != kMainHubState_Quickplay)
            );
        }
    }
    return 1;
}

#pragma push
#pragma pool_data off
DataNode MainHubPanel::OnMsg(const SessionDisconnectedMsg &msg) {
    if (mHubOverride == kMainHubOverride_Waiting) {
        if (!ThePlatformMgr.IsAnyUserSignedIntoLive()) {
            static Message init("init", wii_friends_session_ended);
            TheUIEventMgr->TriggerEvent(error_message, init);
        }
        HandleType(cancel_find_override_msg);
    }
    if (mHubOverride == kMainHubOverride_ChooseBand) {
        MILO_ASSERT(!mWaitingStateLock->InLock(), 0x1F2);
        static Message cancel("cancel_waiting_override");
        HandleType(cancel);
    }
    return 1;
}
#pragma pop

void MainHubPanel::UpdateStateView(
    MainHubState s1, MainHubState s2, MainHubOverride o1, MainHubOverride o2
) {
    static Message updateView("update_state_view", 0, 0, 0, 0);
    updateView[0] = s1;
    updateView[1] = s2;
    updateView[2] = o1;
    updateView[3] = o2;
    HandleType(updateView);
}