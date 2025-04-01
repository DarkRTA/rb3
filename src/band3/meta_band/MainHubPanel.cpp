#include "meta_band/MainHubPanel.h"
#include "BandMachine.h"
#include "MainHubPanel.h"
#include "OvershellPanel.h"
#include "OvershellSlot.h"
#include "bandobj/BandLabel.h"
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/NetGameMsgs.h"
#include "meta_band/BandMachine.h"
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
#include "net/NetSession.h"
#include "net/Server.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "utl/Locale.h"
#include "utl/Messages.h"
#include "utl/Messages3.h"
#include "utl/Messages4.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

namespace {
    class MainHubAdvanceMsg : public NetMessage {
    public:
        MainHubAdvanceMsg() {}
        MainHubAdvanceMsg(NetUIState state, const char *name) : unk4(state), unk8(name) {}
        virtual ~MainHubAdvanceMsg() {}
        virtual void Save(BinStream &bs) const {
            bs << (unsigned char)unk4;
            bs << unk8;
        }
        virtual void Load(BinStream &bs) {
            unsigned char state;
            bs >> state;
            unk4 = (NetUIState)state;
            bs >> unk8;
        }
        virtual void Dispatch() {
            MainHubPanel *panel =
                ObjectDir::Main()->Find<MainHubPanel>(unk8.c_str(), true);
            static Message advanceMsg("advance", 0);
            advanceMsg[0] = unk4;
            panel->HandleType(advanceMsg);
        }
        NETMSG_BYTECODE(MainHubAdvanceMsg);
        NETMSG_NAME(MainHubAdvanceMsg);

        NETMSG_NEWNETMSG(MainHubAdvanceMsg);

        NetUIState unk4;
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
    TheServer.AddSink(this, UserLoginMsg::Type());
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
    TheServer.RemoveSink(this, UserLoginMsg::Type());
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
            if (TheServer.GetPlayerID(profile->GetPadNum())) {
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
    if (profile && TheServer.IsConnected()) {
        if (TheServer.GetPlayerID(profile->GetPadNum()))
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
    if (mHubOverride == kMainHubOverride_Finding) {
        StartFinding();
    }
    Matchmaker *maker = TheSessionMgr->GetMatchmaker();
    if (mHubOverride != kMainHubOverride_Finding && maker->IsFinding()) {
        maker->CancelFind();
    }
    OvershellPanel *panel = TheBandUI.GetOvershell();
    if (old == kMainHubOverride_Finding && mHubOverride != kMainHubOverride_Finding
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
    if (msg.GetOverrideFlowType() == 2 && mHubOverride == kMainHubOverride_Finding) {
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
    if (mHubOverride == kMainHubOverride_Finding) {
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

DataNode MainHubPanel::OnMsg(const PrimaryProfileChangedMsg &) {
    RefreshData();
    return DataNode(kDataUnhandled, 0);
}

DataNode MainHubPanel::OnMsg(const ProcessedJoinRequestMsg &) {
    if (mHubOverride == kMainHubOverride_Finding && TheSessionMgr->IsLeaderLocal()
        && !TheSessionMgr->NumOpenSlots()) {
        AdvanceFromFinding();
    }
    return 1;
}

DataNode MainHubPanel::OnMsg(const NewRemoteMachineMsg &) {
    CheckStartWaitingLock();
    HandleType(update_finding_help_msg);
    return 1;
}

DataNode MainHubPanel::OnMsg(const RemoteMachineLeftMsg &) {
    CheckStartWaitingLock();
    HandleType(update_finding_help_msg);
    return 1;
}

DataNode MainHubPanel::OnMsg(const SessionMgrUpdatedMsg &) {
    HandleType(update_finding_help_msg);
    return 1;
}

DataNode MainHubPanel::OnMsg(const RemoteMachineUpdatedMsg &msg) {
    if (msg.GetMask() & 1) {
        CheckStartWaitingLock();
    }
    return 1;
}

DataNode MainHubPanel::OnMsg(const MatchmakerChangedMsg &) {
    UpdatePoolInfo();
    return 1;
}

DataNode MainHubPanel::OnMsg(const LockStepStartMsg &msg) {
    bool ready = IsWaitingNetUIState(mMachineMgr->GetLocalMachine()->GetNetUIState());
    MILO_ASSERT(ready == (mHubOverride == kMainHubOverride_Waiting), 0x23F);
    mWaitingStateLock->RespondToLock(ready);
    return 1;
}

DataNode MainHubPanel::OnMsg(const LockStepCompleteMsg &) { return 1; }

DataNode MainHubPanel::OnMsg(const ReleasingLockStepMsg &msg) {
    if (msg->Int(2)) {
        AdvanceAll(mMachineMgr->GetLocalMachine()->GetNetUIState());
    }
    return 1;
}

DataNode MainHubPanel::OnMsg(const RockCentralOpCompleteMsg &msg) {
    if (msg.Success() && GetState() == kUp) {
        if (!TheProfileMgr.GetPrimaryProfile())
            return 1;
        unkb8 = true;
        mLabelUpdateResults.Update(nullptr);
        if (mLabelUpdateResults.NumDataResults() > 0) {
            DataResult *res = mLabelUpdateResults.GetDataResult(0);
            DataNode node8b8, node8c0, node8c8, node8d0;
            DataNode node8d8;
            mMessageProvider->ClearData();
            res->GetDataResultValue("motd", node8d8);
            if (node8d8.Str() != "") {
                mMessageProvider->AddUnlinkedMotd(node8d8.Str());
            }
            res->GetDataResultValue("role_id", node8b8);
            res->GetDataResultValue("role_rank", node8c0);
            res->GetDataResultValue("role_is_global", node8c8);
            res->GetDataResultValue("role_is_percentile", node8d0);
            if (node8c0.Int() || node8c8.Int()) {
                mMessageProvider->AddTickerData(
                    (TickerDataType)0,
                    node8b8.Int(),
                    node8c0.Int(),
                    node8c8.Int(),
                    node8d0.Int()
                );
            }
            res->GetDataResultValue("band_id", node8b8);
            res->GetDataResultValue("band_rank", node8c0);
            res->GetDataResultValue("band_is_global", node8c8);
            res->GetDataResultValue("band_is_percentile", node8d0);
            if (node8c0.Int() || node8c8.Int()) {
                mMessageProvider->AddTickerData(
                    (TickerDataType)1,
                    node8b8.Int(),
                    node8c0.Int(),
                    node8c8.Int(),
                    node8d0.Int()
                );
            }
            res->GetDataResultValue("battle_count", node8c0);
            if (node8c0.Int()) {
                mMessageProvider->AddTickerData(
                    (TickerDataType)2, 0, node8c0.Int(), false, false
                );
            }
            mCurrentMessage = 0;
            UpdateMessageProvider();
            UpdateHeader();
        } else
            MILO_WARN("RockCentralOpCompleteMsg to MainHubPanel has empty results!");
    }
    return 1;
}

void MainHubPanel::UpdateMessageProvider() {
    LocalBandUser *user = nullptr;
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    if (profile) {
        user = TheBandUserMgr->GetUserFromPad(profile->GetPadNum());
    }
    static Message update_messages("update_messages", user, unkb8);
    update_messages[0] = user;
    update_messages[1] = unkb8;
    DataNode handled = HandleType(update_messages);
    mMessageProvider->SetData(handled);
    HandleType(refresh_message_provider_msg);
}

DataNode MainHubPanel::OnMsg(const UserLoginMsg &msg) {
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    if (profile) {
        int mypadnum = msg.GetPadNum();
        if (mypadnum == profile->GetPadNum()) {
            ReloadMessages();
        }
    }
    return 1;
}

void MainHubPanel::CheckStartWaitingLock() {
    if (TheSessionMgr->IsLeaderLocal() && !mWaitingStateLock->InLock()) {
        bool b1 = true;
        std::vector<BandMachine *> machines;
        mMachineMgr->GetMachines(machines);
        for (int i = 0; i < machines.size(); i++) {
            if (!IsWaitingNetUIState(machines[i]->GetNetUIState())) {
                b1 = false;
                break;
            }
        }
        if (b1) {
            mWaitingStateLock->StartLock();
        }
    }
}

void MainHubPanel::AdvanceAll(NetUIState state) {
    MainHubAdvanceMsg msg(state, Name());
    TheSessionMgr->SendMsgToAll(msg, kReliable);
    static Message advanceMsg("advance", 0);
    advanceMsg[0] = state;
    HandleType(advanceMsg);
}

void MainHubPanel::AdvanceFromFinding() {
    if (mHubState == kMainHubState_Quickplay) {
        AdvanceAll(kNetUI_WaitingChooseSong);
    } else if (mHubState == kMainHubState_Tour) {
        AdvanceAll(kNetUI_WaitingTour);
    } else
        MILO_FAIL("Trying to advance from finding in invalid state %i\n", mHubState);
}

void MainHubPanel::SetMotd(const char *motd) {
    mMotd = motd;
    if (GetState() == kUp) {
        PrepareProfilesAndMessages();
    }
}

const char *MainHubPanel::GetMotd() {
    const char *motd = mMotd.c_str();
    if (strlen(motd) == 0) {
        if (!ThePlatformMgr.IsEthernetCableConnected()
            || ThePlatformMgr.IsOnlineRestricted()) {
            return Localize(message_motd_noconnection, nullptr);
        } else if (!ThePlatformMgr.IsConnected()) {
            return Localize(message_motd_signin, nullptr);
        } else {
            return Localize(message_motd, nullptr);
        }
    }
    return motd;
}

void MainHubPanel::SetDLCMotd(const char *motd) {
    unk94 = motd;
    if (GetState() == kUp) {
        PrepareProfilesAndMessages();
    }
}

const char *MainHubPanel::GetDLCMotd() {
    const char *motd = unk94.c_str();
    if (strlen(motd) == 0) {
        return Localize(message_latest_dlc, nullptr);
    }
    return motd;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(MainHubPanel)
    HANDLE_EXPR(get_message_provider, GetMessageProvider())
    HANDLE_ACTION(cycle_next_message, CycleNextMessage())
    HANDLE_EXPR(get_state, GetMainHubState())
    HANDLE_ACTION(set_state, SetMainHubState((MainHubState)_msg->Int(2)))
    HANDLE_EXPR(get_override, GetMainHubOverride())
    HANDLE_ACTION(set_override, SetMainHubOverride((MainHubOverride)_msg->Int(2)))
    HANDLE_EXPR(in_waiting_lock, mWaitingStateLock->InLock())
    HANDLE_ACTION(set_motd, SetMotd(_msg->Str(2)))
    HANDLE_EXPR(get_motd, GetMotd())
    HANDLE_ACTION(set_dlcmotd, SetDLCMotd(_msg->Str(2)))
    HANDLE_EXPR(get_dlcmotd, GetDLCMotd())
    HANDLE_ACTION(advance_from_finding, AdvanceFromFinding())
    HANDLE_EXPR(check_profile_for_message_ticker, CheckProfileForTicker())
    HANDLE_EXPR(has_role_info, mMessageProvider->IsTickerDataValid((TickerDataType)0))
    HANDLE_EXPR(has_band_info, mMessageProvider->IsTickerDataValid((TickerDataType)1))
    HANDLE_EXPR(has_battles_info, mMessageProvider->IsTickerDataValid((TickerDataType)2))
    HANDLE_EXPR(has_unlinked_motd, mMessageProvider->IsUnlinkedMotdAvailable())
    HANDLE_MESSAGE(ProcessedJoinRequestMsg)
    HANDLE_MESSAGE(SessionDisconnectedMsg)
    HANDLE_MESSAGE(PrimaryProfileChangedMsg)
    HANDLE_MESSAGE(SessionMgrUpdatedMsg)
    HANDLE_MESSAGE(NewRemoteMachineMsg)
    HANDLE_MESSAGE(RemoteMachineLeftMsg)
    HANDLE_MESSAGE(RemoteMachineUpdatedMsg)
    HANDLE_MESSAGE(LockStepStartMsg)
    HANDLE_MESSAGE(LockStepCompleteMsg)
    HANDLE_MESSAGE(ReleasingLockStepMsg)
    HANDLE_MESSAGE(OvershellOverrideEndedMsg)
    HANDLE_MESSAGE(MatchmakerChangedMsg)
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_MESSAGE(UserLoginMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x35D)
END_HANDLERS
#pragma pop