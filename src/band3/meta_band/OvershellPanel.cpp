#include "meta_band/OvershellPanel.h"
#include "OvershellPanel.h"
#include "OvershellSlot.h"
#include "bandobj/OvershellDir.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameMic.h"
#include "game/GameMicManager.h"
#include "game/GameMode.h"
#include "game/UISyncNetMsgs.h"
#include "meta/ConnectionStatusPanel.h"
#include "meta/Profile.h"
#include "meta/WiiProfileMgr.h"
#include "meta_band/BandMachine.h"
#include "meta_band/BandUI.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/InputMgr.h"
#include "meta_band/Matchmaker.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/OvershellSlot.h"
#include "meta_band/OvershellSlotState.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/UIEventMgr.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/WiiFriendMgr.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/JoypadMsgs.h"
#include "os/Joypad_Wii.h"
#include "os/PlatformMgr.h"
#include "os/VirtualKeyboard.h"
#include "rndobj/Rnd.h"
#include "synth/MicManagerInterface.h"
#include "ui/UIComponent.h"
#include "ui/UIList.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "ui/UISlider.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

MicClientID sNullMicClientID;

NewOvershellLocalUserMsg::NewOvershellLocalUserMsg(LocalBandUser *user)
    : Message(Type(), user) {}

LocalBandUser *NewOvershellLocalUserMsg::GetBandUser() const {
    return mData->Obj<LocalBandUser>(2);
}

OvershellOverrideEndedMsg::OvershellOverrideEndedMsg(OvershellOverrideFlow f, bool b)
    : Message(Type(), f, b) {}

OvershellOverrideFlow OvershellOverrideEndedMsg::GetOverrideFlowType() const {
    return (OvershellOverrideFlow)mData->Int(2);
}

bool OvershellOverrideEndedMsg::Cancelled() const { return mData->Int(3); }

OvershellAllowingInputChangedMsg::OvershellAllowingInputChangedMsg(BandUser *u)
    : Message(Type(), u) {}

OvershellPanel::OvershellPanel(SessionMgr *smgr, BandUserMgr *umgr)
    : Synchronizable("overshell"), mPanelOverrideFlow(kOverrideFlow_None),
      mActiveStatus(kOvershellInactive), mSongOptionsRequired(0), unk89(0), unk8a(1),
      mPartRestrictedUser(0), mPartRestriction(kTrackNone),
      mMinimumDifficulty(kDifficultyEasy), mPartResolver(0), unk4b8(0), unk4bc(0),
      unk4c8(0) {
    if (smgr)
        mSessionMgr = smgr;
    else {
        MILO_ASSERT(TheSessionMgr, 0x73);
        mSessionMgr = TheSessionMgr;
    }
    if (umgr)
        mBandUserMgr = umgr;
    else {
        MILO_ASSERT(TheBandUserMgr, 0x7D);
        mBandUserMgr = TheBandUserMgr;
    }

    if (TheGameMicManager) {
        TheGameMicManager->AddSink(this, GameMicsChangedMsg::Type());
    }
    mSessionMgr->AddSink(this);
    mSessionMgr->GetMatchmaker()->AddSink(this);
    mSessionMgr->GetMachineMgr()->AddSink(this);
    ThePlatformMgr.AddSink(this);
    TheRockCentral.AddSink(this);
    ThePlatformMgr.AddSink(this, InviteReceivedMsg::Type());
    ThePlatformMgr.AddSink(this, InviteExpiredMsg::Type());
    ThePlatformMgr.AddSink(this, NetStartUtilityFinishedMsg::Type());
    TheServer->AddSink(this, UserNameNewlyProfaneMsg::Type());
}

OvershellPanel::~OvershellPanel() {
    ClearSlots();
    TheRockCentral.RemoveSink(this);
    ThePlatformMgr.RemoveSink(this);
    mSessionMgr->GetMachineMgr()->RemoveSink(this);
    mSessionMgr->GetMatchmaker()->RemoveSink(this);
    mSessionMgr->RemoveSink(this);
    if (TheGameMicManager) {
        TheGameMicManager->RemoveSink(this, GameMicsChangedMsg::Type());
    }
    TheWiiFriendMgr.RemoveSink(this, InviteReceivedMsg::Type());
    TheWiiFriendMgr.RemoveSink(this, InviteExpiredMsg::Type());
    ThePlatformMgr.RemoveSink(this, NetStartUtilityFinishedMsg::Type());
    TheServer->RemoveSink(this, UserNameNewlyProfaneMsg::Type());
}

bool SignInUser(User *u, unsigned long ul) {
    static OvershellPanel *pOvershellPanel =
        ObjectDir::Main()->Find<OvershellPanel>("overshell", true);
    LocalBandUser *user = dynamic_cast<LocalBandUser *>(u);
    if (user) {
        OvershellSlot *slot = pOvershellPanel->FindSlotForUser(user);
        if (slot->GetUser() == user) {
            slot->ShowWiiProfileSelector((ul >> 1) & 1);
            return true;
        }
    }
    return false;
}

void OvershellPanel::Init() { ThePlatformMgr.RegisterSignInserCallback(SignInUser); }

void OvershellPanel::SetActiveStatus(OvershellActiveStatus status) {
    if (status != mActiveStatus) {
        MILO_ASSERT(!InOverrideFlow(kOverrideFlow_SongSettings), 0xD5);
        if (status == kOvershellInShell) {
            SetSongOptionsRequired(false);
        }
        for (int i = 0; i < mSlots.size(); i++) {
            BandUser *curUser = mSlots[i]->GetUser();
            if (curUser && curUser->IsLocal()) {
                if (mSlots[i]->InOverrideFlow(kOverrideFlow_SongSettings)) {
                    if (!mSlots[i]->mSongOptionsRequired) {
                        mSlots[i]->EndOverrideFlow(kOverrideFlow_SongSettings, true);
                    }
                } else if (mSlots[i]->InOverrideFlow(kOverrideFlow_RegisterOnline)) {
                    EndOverrideFlow(kOverrideFlow_RegisterOnline, true);
                    mSessionMgr->Disconnect();
                } else {
                    mSlots[i]->LeaveOptions();
                }
            }
        }
        if (GetState() == kUp) {
            Exit();
        }
    }
    mActiveStatus = status;
    static OvershellActiveStatusChangedMsg msg;
    MsgSource::Handle(msg, false);
    if (status != kOvershellInactive && GetState() == kDown) {
        Enter();
    }
    SetInGame(status == kOvershellInSong || status == kOvershellInGameShell);
    SetAutohide(status == kOvershellInSong);
    if (status != kOvershellInactive) {
        AddQueuedJoinUsers();
    }
    UpdateAll();
}

FORCE_LOCAL_INLINE
bool OvershellPanel::InOverrideFlow(OvershellOverrideFlow flow) {
    return mPanelOverrideFlow == flow;
}
END_FORCE_LOCAL_INLINE

void OvershellPanel::SetSongOptionsRequired(bool b1) {
    mSongOptionsRequired = b1;
    if (HasSyncPermission()) {
        SetSyncDirty(-1, false);
    }
    UpdateAll();
}

void OvershellPanel::SetUseExtendedMicArrows(bool b1) {
    unk89 = b1;
    UpdateAll();
}

void OvershellPanel::SetAllowsButtonPulse(bool b1) { unk8a = b1; }

void OvershellPanel::AddQueuedJoinUsers() {
    MILO_ASSERT(mActiveStatus != kOvershellInactive, 0x126);
    for (int i = 0; i < mQueuedJoinUsers.size(); i++) {
        LocalBandUser *curUser = mQueuedJoinUsers[i];
        if (!curUser->IsParticipating()) {
            AttemptToAddUser(curUser);
        }
    }
    mQueuedJoinUsers.clear();
}

void OvershellPanel::QueueUserToJoin(LocalBandUser *user) {
    MILO_ASSERT(user != NULL, 0x138);
    MILO_ASSERT(mActiveStatus == kOvershellInactive, 0x139);

    bool b1 = false;
    for (int i = 0; i < mQueuedJoinUsers.size(); i++) {
        if (mQueuedJoinUsers[i] == user) {
            b1 = true;
            break;
        }
    }
    if (!b1) {
        mQueuedJoinUsers.push_back(user);
    }
}

void OvershellPanel::AttemptToAddUser(LocalBandUser *user) {
    MILO_ASSERT(!user->IsParticipating(), 0x14D);
    if (mActiveStatus == kOvershellInactive) {
        QueueUserToJoin(user);
    } else {
        OvershellSlot *slot = FindSlotForUser(user);
        if (slot) {
            JoinState state;
            if (slot->LookupUserInJoinList(user, &state) && state == kMetaJoinOK) {
                slot->AddUser(user);
            }
        }
    }
}

void OvershellPanel::RemoveUsersWithoutOnlinePrivilege() {
    for (int i = 0; i < mSlots.size(); i++) {
        BandUser *user = mSlots[i]->GetUser();
        if (user && user->IsLocal()) {
            if (!user->GetLocalUser()->HasOnlinePrivilege()) {
                mSlots[i]->RemoveUser();
            }
        }
    }
}

void OvershellPanel::RemoveUsersRequiringSongOptions() {
    for (int i = 0; i < mSlots.size(); i++) {
        BandUser *user = mSlots[i]->GetUser();
        if (user && user->IsLocal() && mSlots[i]->mSongOptionsRequired) {
            mSlots[i]->RemoveUser();
        }
    }
}

void OvershellPanel::BeginOverrideFlow(OvershellOverrideFlow type) {
    MILO_ASSERT(InOverrideFlow(kOverrideFlow_None), 0x192);
    MILO_ASSERT(type != kOverrideFlow_None, 0x193);
    mPanelOverrideFlow = type;
    if (mSessionMgr->IsLeaderLocal()) {
        unk4b8 = RandomInt();
    }
    SetSyncDirty(-1, false);
    UpdateAll();
}

void OvershellPanel::EndOverrideFlow(OvershellOverrideFlow type, bool b2) {
    MILO_ASSERT(InOverrideFlow(type), 0x1B0);
    mPanelOverrideFlow = kOverrideFlow_None;
    if (type == kOverrideFlow_SongSettings && !b2) {
        SetSongOptionsRequired(true);
    }
    OvershellOverrideEndedMsg msg(type, b2);
    Export(msg, true);
    SetSyncDirty(-1, false);
    UpdateAll();
}

DECOMP_FORCEACTIVE(OvershellPanel, "!playableTracks.empty()", "!resolvingUsers.empty()")

DataNode OvershellPanel::OnMsg(const SessionReadyMsg &msg) {
    if (mPanelOverrideFlow == kOverrideFlow_RegisterOnline) {
        if (msg->Int(2)) {
            unk4c8 = true;
        } else {
            for (int i = 0; i < mSlots.size(); i++) {
                if (mSlots[i]->GetUser()) {
                    mSlots[i]->ShowState(kState_SignInFailRetry);
                }
            }
        }
    }
    return 1;
}

DataNode OvershellPanel::OnMsg(const SessionDisconnectedMsg &) {
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const JoypadConnectionMsg &) {
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const GameMicsChangedMsg &) {
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const MatchmakerChangedMsg &) {
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const ServerStatusChangedMsg &msg) {
    if (unk4cc == 2) {
        if (!msg->Int(2)) {
            TheBandUI.ShowNetError();
            if (mPanelOverrideFlow == kOverrideFlow_RegisterOnline) {
                EndOverrideFlow(kOverrideFlow_RegisterOnline, true);
            }
        }
    }
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const ConnectionStatusChangedMsg &) {
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const NetStartUtilityFinishedMsg &msg) {
    if (unk4cc == 2) {
        if (!msg->Int(2)) {
            TheBandUI.ShowNetError();
            if (mPanelOverrideFlow == kOverrideFlow_RegisterOnline) {
                EndOverrideFlow(kOverrideFlow_RegisterOnline, true);
            }
        }
    }
    UpdateAll();
    return 1;
}

void OvershellPanel::ClearSlots() {
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0x32B);
        delete pSlot;
    }
    mSlots.clear();
}

void OvershellPanel::AddSlot(OvershellSlot *slot, int i2) {
    mSlots.push_back(slot);
    mSlotPriorities.push_back(i2);
}

bool OvershellPanel::IsFinding() const {
    return mSessionMgr->GetMatchmaker()->IsFinding();
}

bool OvershellPanel::IsFull() const {
    for (int i = 0; i < mSlots.size(); i++) {
        if (!mSlots[i]->GetUser())
            return false;
    }
    return true;
}

FORCE_LOCAL_INLINE
bool OvershellPanel::InSong() const { return mActiveStatus == kOvershellInSong; }
END_FORCE_LOCAL_INLINE

OvershellSlot *OvershellPanel::GetSlot(int slot) {
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0x35D);
        if (slot == pSlot->GetSlotNum())
            return pSlot;
    }
    return nullptr;
}

OvershellSlot *OvershellPanel::GetSlot(BandUser *user) {
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0x36D);
        if (pSlot->GetUser() == user)
            return pSlot;
    }
    return nullptr;
}

BandUser *OvershellPanel::GetPartRestrictedUser() const { return mPartRestrictedUser; }
TrackType OvershellPanel::GetPartRestriction() const { return mPartRestriction; }
Difficulty OvershellPanel::GetMinimumDifficulty() const { return mMinimumDifficulty; }

bool OvershellPanel::AllSlotsReadyToPlay() const {
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0x38C);
        if (!pSlot->GetState()->IsReadyToPlay())
            return false;
    }
    return true;
}

bool OvershellPanel::ShouldPause() const {
    bool b1 = true;
    bool b6 = false;
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0x39F);
        if (pSlot->GetUser()) {
            b1 = false;
            if (pSlot->GetState()->IsReadyToPlay()) {
                b6 = true;
            }
        }
        if (!pSlot->GetState()->IsReadyToPlay())
            return true;
    }
    return b1 || !b6;
}

void OvershellPanel::SetAutohide(bool b1) {
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0x3C9);
        pSlot->EnableAutohide(b1);
    }
    static Message autohideMsg("autohide_msg", b1);
    autohideMsg[0] = b1;
    HandleType(autohideMsg);
}

void OvershellPanel::SetBlockAllInput(bool b1) {
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0x3D7);
        pSlot->SetBlockAllInput(b1);
    }
}

void OvershellPanel::SetInGame(bool b1) {
    static Message msgMoveSlots("move_slots", 1);
    msgMoveSlots[0] = b1 && mActiveStatus != kOvershellInGameShell ? 1 : 0;
    HandleType(msgMoveSlots);
    if (b1) {
        SetSongOptionsRequired(true);
    }
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0x3EA);
        pSlot->SetInGame(b1);
        pSlot->SetInTrackMode(b1 && mActiveStatus != kOvershellInGameShell);
        if (!b1) {
            pSlot->ResetSlotCamera();
        }
    }
}

void OvershellPanel::UpdateAll() {
    RefreshJoinableUsers();
    for (int i = 0; i < mSlots.size(); i++) {
        mSlots[i]->UpdateState();
    }
    ResolveSlotStates();
    for (int i = 0; i < mSlots.size(); i++) {
        mSlots[i]->UpdateView();
    }
    CheckForControllerDisconnects();
    bool active = mActiveStatus != kOvershellInactive;
    static Message msgUpdate("update", 0);
    msgUpdate[0] = active;
    UIPanel::Handle(msgUpdate, false);
}

void OvershellPanel::RefreshJoinableUsers() {
    std::vector<OvershellSlot *> slots;
    MILO_ASSERT(mSlotPriorities.size() == mSlots.size(), 0x41C);
    int i13 = 0;
    int i12 = 0;
    for (int i = 0; i < mSlots.size(); i++) {
        OvershellSlot *curSlot = mSlots[mSlotPriorities[i]];
        curSlot->ClearPotentialUsers();
        BandUser *curUser = curSlot->GetUser();
        if (!curUser)
            slots.push_back(curSlot);
        else if (curUser->GetControllerType() == 1)
            i13++;
        else if (curUser->GetControllerType() == 4)
            i12++;
    }
    if (mSessionMgr->IsBusy())
        return;
    if (InGame()) {
        if (TheGameMode->Property("prevent_in_game_drop_in")->Int())
            return;
    }
    std::vector<LocalBandUser *> users;
    mBandUserMgr->GetLocalUsersNotInSessionWithAnyController(users);
    std::vector<OvershellSlot *> vec50;
    FOREACH (it, users) {
        vec50.clear();
        ControllerType ct = (*it)->ConnectedControllerType();
        if ((ct != kControllerGuitar || i12 <= 0 || i13 + i12 < 2)
            && (ct != kControllerRealGuitar || i13 + i12 < 2)) {
            for (int i = 0; i < slots.size(); i++) {
                if (slots[i]->IsValidControllerType(ct)) {
                    vec50.push_back(slots[i]);
                }
            }
            if (!vec50.empty()) {
                int i14 = 0;
                for (int i = 1; i < vec50.size(); i++) {
                    if (vec50[i]->NumPotentialUsers() < vec50[i14]->NumPotentialUsers()) {
                        i14 = i;
                    }
                }
                AddJoinUserEntryToSlot(*it, vec50[i14]);
            }
        }
    }
}

void OvershellPanel::AddJoinUserEntryToSlot(LocalBandUser *user, OvershellSlot *) {
    MILO_ASSERT(user, 0x46D);
}

bool OvershellPanel::IsAnySlotAllowingInputToShell() {
    for (int i = 0; i < mSlots.size(); i++) {
        if (mSlots[i]->GetState()->AllowsInputToShell())
            return true;
    }
    return false;
}

BandUser *OvershellPanel::GetFirstUserAllowingInputToShell() {
    for (int i = 0; i < mSlots.size(); i++) {
        BandUser *user = mSlots[i]->GetUser();
        if (user) {
            if (mSlots[i]->GetState()->AllowsInputToShell())
                return user;
        }
    }
    return nullptr;
}

bool OvershellPanel::IsAnyLocalSlotAllowingInputToShell() {
    for (int i = 0; i < mSlots.size(); i++) {
        BandUser *user = mSlots[i]->GetUser();
        if (user && user->IsLocal()) {
            if (mSlots[i]->GetState()->AllowsInputToShell())
                return true;
        }
    }
    return false;
}

bool OvershellPanel::AreAllLocalSlotsAllowingInputToShell() {
    bool ret = true;
    for (int i = 0; i < mSlots.size(); i++) {
        BandUser *user = mSlots[i]->GetUser();
        if (user && user->IsLocal()) {
            if (!mSlots[i]->GetState()->AllowsInputToShell()) {
                ret = false;
                break;
            }
        }
    }
    return ret;
}

bool OvershellPanel::IsAnySlotJoinable() const {
    for (int i = 0; i < mSlots.size(); i++) {
        if (mSlots[i]->GetState()->GetStateID() == 1)
            return true;
    }
    return false;
}

bool OvershellPanel::IsNonVocalistInVocalsSlot() const {
    BandUser *user = mSlots[2]->GetUser();
    return user && user->GetControllerType() != 2;
}

FORCE_LOCAL_INLINE
bool OvershellPanel::IsAutoVocalsAllowed() const {
    return !InGame() && !mSongOptionsRequired;
}
END_FORCE_LOCAL_INLINE

void OvershellPanel::EnableAutoVocals() {
    bool b2 = true;
    if (IsAutoVocalsAllowed()) {
        if (!(TheModifierMgr && TheModifierMgr->IsModifierActive(mod_auto_vocals)))
            b2 = false;
    }
    if (b2) {
        UpdateAll();
    } else {
        MILO_ASSERT(IsAutoVocalsAllowed(), 0x50D);
        if (TheModifierMgr) {
            MILO_ASSERT(!TheModifierMgr->IsModifierActive(mod_auto_vocals), 0x512);
            TheModifierMgr->ToggleModifierEnabled(mod_auto_vocals);
        }
        mSessionMgr->Disconnect();
        for (int i = 0; i < mSlots.size(); i++) {
            BandUser *user = mSlots[i]->GetUser();
            if (user && user->GetControllerType() == 2) {
                int i6;
                if (user->GetLocalUser()) {
                    i6 = user->GetLocalBandUser()->GetPadNum();
                } else
                    i6 = -1;
                mSlots[i]->RemoveUser();
                JoypadWiiOnUserLeft(i6, true);
            }
        }
        UpdateAll();
    }
}

bool OvershellPanel::CanGuitarPlayKeys() const {
    std::vector<BandProfile *> profiles = TheProfileMgr.GetSignedInProfiles();
    for (int i = 0; i < profiles.size(); i++) {
        if (profiles[i]->HasCampaignKey(key_keys_on_guitar))
            return true;
    }
    if (TheModifierMgr && TheModifierMgr->IsModifierActive(mod_auto_vocals))
        return true;
    else
        return false;
}

bool OvershellPanel::DoesAnySlotHaveChar(CharData *cd) const {
    for (int i = 0; i < mSlots.size(); i++) {
        BandUser *user = mSlots[i]->GetUser();
        if (user && user->GetChar() == cd)
            return true;
    }
    return false;
}

bool OvershellPanel::IsAnySlotEditingChar(CharData *cd) const {
    for (int i = 0; i < mSlots.size(); i++) {
        if (mSlots[i]->GetState()->InCharEditFlow() && mSlots[i]->mCharForEdit == cd)
            return true;
    }
    return false;
}

void OvershellPanel::ResolveSlotStates() {
    ResolvePartWaitStates();
    ResolveReadyToPlayStates();
    ResolveSignInWaitStates();
    ResolveAutoSignInStates();
    OvershellSlot *curSlot;
    bool b1 = false;
    for (int i = 0; i < mSlots.size(); i++) {
        curSlot = mSlots[i];
        LocalBandUser *curLocalUser;
        if (curSlot->GetUser() && curSlot->GetUser()->IsLocal()) {
            curLocalUser = curSlot->GetUser()->GetLocalBandUser();
        } else {
            if (curSlot->GetState()->GetStateID() == 0)
                b1 = true;
            continue;
        }
        if (curSlot->GetState()->GetStateID() == 0x32) {
            BandUser *pUser = curSlot->GetUser();
            MILO_ASSERT(pUser->IsLocal(), 0x58B);
            if (pUser->GetLocalBandUser()->ConnectedControllerType()
                == pUser->GetControllerType()) {
                curSlot->RevertToOverrideFlowReturnState();
            } else if (mActiveStatus - 1U <= 1) {
                curSlot->AttemptRemoveUser();
            }
        }
        OvershellSlotStateID theID = curLocalUser->GetOvershellState();
        if (!curSlot->GetState()->PreventsOverride()) {
            OvershellSlotStateID ossID;
            if (ShouldSeeRealGuitarPrompt(curLocalUser, ossID)) {
                curLocalUser->SetHasSeenRealGuitarPrompt();
                curSlot->ShowState(ossID);
            } else {
                ClosetMgr *cMgr = ClosetMgr::GetClosetMgr();
                if (curSlot->GetState()->InChooseCharFlow() && cMgr
                    && cMgr->GetUser() == curLocalUser) {
                    curSlot->ShowState((OvershellSlotStateID)0x49);
                } else if (!InOverrideFlow(kOverrideFlow_SongSettings)
                           && !SongOptionsRequired()
                           && mSlots[i]->InOverrideFlow(kOverrideFlow_SongSettings)) {
                    mSlots[i]->EndOverrideFlow(kOverrideFlow_SongSettings, true);
                } else if (curSlot->GetState()->GetStateID() < 200) {
                    if (!TheWiiProfileMgr.IsPadAGuest(curLocalUser->GetPadNum())) {
                        int padIdx =
                            TheWiiProfileMgr.GetIndexForPad(curLocalUser->GetPadNum());
                        if (padIdx >= 0) {
                            if (TheWiiProfileMgr.IsIndexLoaded(padIdx)
                                && !TheWiiProfileMgr.IsIndexLocked(padIdx)) {
                                goto therest;
                            }

                            if (curSlot->GetState()->GetStateID() != 0x81) {
                                curSlot->ShowWaitWii();
                            }
                        }
                    } else {
                    therest:
                        if (curSlot->GetState()->GetStateID() == 0x81) {
                            curSlot->LeaveWaitWii();
                        }
                        if (curSlot->GetState()->InSongSettingsFlow()) {
                            if (!curSlot->InOverrideFlow(kOverrideFlow_SongSettings)) {
                                curSlot->RevertToOverrideFlowReturnState();
                            }
                        } else if (curSlot->InOverrideFlow(kOverrideFlow_SongSettings)) {
                            OvershellSlotStateID o12 = theID;
                            if (curSlot->InGame()) {
                                o12 = kState_JoinedDefault;
                            }
                            curSlot->SetOverrideFlowReturnState((OvershellSlotStateID)o12
                            );
                            curSlot->ShowSongOptions();
                        }

                        if (!curSlot->SongOptionsRequired()) {
                            if (curSlot->GetState()->InRegisterOnlineFlow()) {
                                if (!curSlot->InOverrideFlow(kOverrideFlow_RegisterOnline
                                    )) {
                                    curSlot->RevertToOverrideFlowReturnState();
                                }
                            } else if (curSlot->InOverrideFlow(
                                           kOverrideFlow_RegisterOnline
                                       )) {
                                if (!curSlot->GetState()->InRegisterOnlineFlow()) {
                                    curSlot->SetOverrideFlowReturnState(theID);
                                }
                                curSlot->ShowState((OvershellSlotStateID)0x8B);
                            }
                            if (curSlot->GetState()->RequiresOnlineSession()
                                && !mSessionMgr->IsOnlineEnabled()) {
                                curSlot->LeaveOptions();
                            }
                            if (curSlot->GetState()->RequiresRemoteUsers()
                                && mSessionMgr->IsLocal()) {
                                curSlot->ShowOnlineOptions();
                            }
                            if (curSlot->GetState()->GetStateID() == 0x29) {
                                BandUser *pUser = curSlot->GetState()
                                                      ->Property("kick_user")
                                                      ->Obj<BandUser>();
                                MILO_ASSERT(pUser, 0x632);
                                if (!mSessionMgr->HasUser(pUser)) {
                                    curSlot->LeaveKickConfirmation();
                                }
                            }
                            if (curSlot->GetState()->GetStateID() == 0x1E
                                && !mSessionMgr->AreInvitesAllowed()) {
                                curSlot->ShowOnlineOptions();
                            }
                        }
                    }
                }
            }
        }
    }
    static Message msgHideConnectControllerMesh(hide_connect_controller_mesh, 1);
    msgHideConnectControllerMesh[0] = !b1 || InGame();
    HandleType(msgHideConnectControllerMesh);
}

void OvershellPanel::ResolveSignInWaitStates() {
    if (InOverrideFlow(kOverrideFlow_RegisterOnline)) {
        bool b3 = false;
        bool b2 = true;
        bool b1 = true;
        std::vector<LocalBandUser *> users;
        mBandUserMgr->GetLocalParticipants(users);
        if (!users.empty()) {
            b1 = false;
            for (int i = 0; i < users.size(); i++) {
                LocalBandUser *cur = users[i];
                if (cur->GetOvershellState() == 0x14) {
                    if (!cur->HasOnlinePrivilege()
                        || mBandUserMgr->AllLocalUsersInSessionAreGuests()) {
                        cur->SetOvershellSlotState(kState_SignInToRegister);
                        b3 = true;
                        b2 = false;
                    }
                } else
                    b2 = false;
            }
        }
        if (b1)
            EndOverrideFlow(kOverrideFlow_RegisterOnline, true);
        else if (b2) {
            for (int i = 0; i < users.size(); i++) {
                users[i]->SetOvershellSlotState(kState_RegisteringOnline);
            }
            mSessionMgr->RegisterOnline();
            b3 = true;
        }
        if (b3)
            UpdateAll();
    }
}

void OvershellPanel::ResolveAutoSignInStates() {
    for (int i = 0; i < mSlots.size(); i++) {
        OvershellSlot *curSlot = mSlots[i];
        if (curSlot->GetUser()) {
            if (curSlot->GetUser()->IsLocal()) {
                LocalBandUser *user = curSlot->GetUser()->GetLocalBandUser();
                OvershellSlotStateID ossID = curSlot->GetState()->GetStateID();
                if (ossID == 0x10 && user->IsSignedInOnline()
                    && user->HasOnlinePrivilege()) {
                    curSlot->ShowState(kState_AutoSignInRockCentral);
                } else if (ossID == 0x8B) {
                    if (ThePlatformMgr.IsConnected()) {
                        curSlot->ShowState(kState_AutoSignInRockCentral);
                    } else if (!ThePlatformMgr.mTimer.Running()) {
                        ThePlatformMgr.RunNetStartUtility();
                    }
                } else if (ossID == 0x12 && TheRockCentral.unk3c == 2) {
                    curSlot->ShowState(kState_SignInWait);
                }
            }
        }
    }
}

void OvershellPanel::ExportAll(const Message &msg) {
    if (msg.Type() == update) {
        UpdateAll();
    } else {
        FOREACH (it, mSlots) {
            OvershellSlot *pSlot = *it;
            MILO_ASSERT(pSlot, 0x6D5);
            SlotHandle(pSlot, msg);
        }
    }
}

void OvershellPanel::SetPartRestrictedUser(BandUser *u) { mPartRestrictedUser = u; }
void OvershellPanel::SetPartRestriction(TrackType t) { mPartRestriction = t; }
void OvershellPanel::SetMinimumDifficulty(Difficulty d) { mMinimumDifficulty = d; }

void OvershellPanel::ClearTrackTypesFromUsers() {
    for (int i = 0; i < mSlots.size(); i++) {
        BandUser *user = mSlots[i]->GetUser();
        if (user && user->IsLocal()) {
            user->SetTrackType(kNumTrackTypes);
        }
    }
}

#pragma push
#pragma pool_data off
bool OvershellPanel::ShouldSeeRealGuitarPrompt(
    LocalBandUser *user, OvershellSlotStateID &ossID
) {
    MILO_ASSERT(user, 0x6F7);
    if (user->GetControllerType() != kControllerRealGuitar)
        return false;
    else if (!unk4bc)
        return false;
    else if (user->HasSeenRealGuitarPrompt())
        return false;
    else if (!mSessionMgr->IsLocal())
        return false;
    else if (InOverrideFlow(kOverrideFlow_RegisterOnline))
        return false;
    else {
        static Message first_time_msg("first_time_real_guitar_prompt_reqs", user);
        first_time_msg[0] = user;
        if (HandleType(first_time_msg).Int()) {
            ossID = kState_FirstTimeRG;
            return true;
        } else {
            static Message second_time_msg("second_time_real_guitar_prompt_reqs", user);
            second_time_msg[0] = user;
            if (HandleType(second_time_msg).Int()) {
                ossID = (OvershellSlotStateID)0x38;
                return true;
            } else
                return false;
        }
    }
}
#pragma pop

void OvershellPanel::FinishLoad() {
    UIPanel::FinishLoad();
    DataArray *playerPanelsArr = TypeDef()->FindArray("player_panels", true);
    DataArray *typeArr = playerPanelsArr->FindArray("type", true);
    DataArray *slots = playerPanelsArr->FindArray("slots", false);
    MILO_ASSERT(slots, 0x72F);
    DataArray *validControllers = slots->FindArray("valid_controllers", true);
    MILO_ASSERT(validControllers, 0x731);
    DataArray *normalArr = validControllers->FindArray("normal", true);
    DataArray *voxArr = validControllers->FindArray("auto_vocals", true);
    int size = normalArr->Size() - 1;
    DataArray *priorityArr = slots->FindArray("joining_priority", true);
    ClearSlots();
    mSlots.reserve(size);
    for (int i = 0; i < size; i++) {
        const char *slotName = MakeString("slot%i", i);
        OvershellDir *p = LoadedDir()->Find<OvershellDir>(slotName, true);
        MILO_ASSERT(p, 0x740);
        OvershellSlot *slot = new OvershellSlot(i, this, p, mBandUserMgr, mSessionMgr);
        slot->SetTypeDef(typeArr);
        DataArray *normalArrNext = normalArr->Array(i + 1);
        for (int j = 0; j < normalArrNext->Size(); j++) {
            slot->AddValidController(SymToControllerType(normalArrNext->Sym(j)));
        }
        DataArray *autoVoxArrNext = voxArr->Array(i + 1);
        for (int j = 0; j < autoVoxArrNext->Size(); j++) {
            slot->AddValidController(SymToControllerType(autoVoxArrNext->Sym(j)));
        }
        AddSlot(slot, priorityArr->Int(i + 1));
    }
    UpdateAll();
}

void OvershellPanel::Enter() {
    for (int i = 0; i < mSlots.size(); i++) {
        mSlots[i]->Enter();
    }
    TheNetSession->AddSink(this, RemoteUserUpdatedMsg::Type());
    TheInputMgr->SetInvalidMessageSink(this);
    UIPanel::Enter();
    UpdateAll();
}

void OvershellPanel::Exit() {
    TheInputMgr->ClearInvalidMessageSink();
    TheNetSession->RemoveSink(this, RemoteUserUpdatedMsg::Type());
    UIPanel::Exit();
}

bool OvershellPanel::Exiting() const {
    if (UIPanel::Exiting())
        return true;
    else {
        bool ret = false;
        for (int i = 0; i < mSlots.size(); i++) {
            if (mSlots[i]->GetPanelDir()->Exiting()) {
                ret = true;
                break;
            }
        }
        return ret;
    }
}

void OvershellPanel::Poll() {
    unk4cc = mPanelOverrideFlow;
    if (TheRnd->mProcCmds & kProcessPost) {
        if (unk4c8) {
            MILO_ASSERT(InOverrideFlow(kOverrideFlow_RegisterOnline), 0x794);
        }
    }
}

void OvershellPanel::SyncSave(BinStream &bs, unsigned int) const {
    bs << (unsigned char)mPanelOverrideFlow;
    bs << unk4b8;
    bs << mSongOptionsRequired;
}

void OvershellPanel::SyncLoad(BinStream &bs, unsigned int) {
    unsigned char flow;
    bs >> flow;
    mPanelOverrideFlow = (OvershellOverrideFlow)flow;
    bs >> unk4b8;
    bs >> mSongOptionsRequired;
}

bool OvershellPanel::HasSyncPermission() const { return mSessionMgr->IsLeaderLocal(); }
void OvershellPanel::OnSynchronized(unsigned int) { UpdateAll(); }

DataNode OvershellPanel::OnMsg(const ButtonDownMsg &msg) {
    if (ThePlatformMgr.mHomeMenuWii->mHomeMenuActive
        || TheVirtualKeyboard.IsKeyboardShowing()) {
        return DataNode(kDataUnhandled, 0);
    } else {
        BandUser *pUser = BandUserMgr::GetBandUser(msg.GetUser());
        MILO_ASSERT(pUser->IsLocal(), 0x80C);
        if (TheUIEventMgr->HasActiveDialogEvent()) {
            return DataNode(kDataUnhandled, 0);
        } else
            return ExportButtonMsg(msg, pUser, true);
    }
}

DataNode OvershellPanel::OnMsg(const ButtonUpMsg &msg) {
    if (ThePlatformMgr.mHomeMenuWii->mHomeMenuActive
        || TheVirtualKeyboard.IsKeyboardShowing()) {
        return DataNode(kDataUnhandled, 0);
    } else {
        BandUser *pUser = BandUserMgr::GetBandUser(msg.GetUser());
        MILO_ASSERT(pUser->IsLocal(), 0x81E);
        if (TheUIEventMgr->HasActiveDialogEvent()) {
            return DataNode(kDataUnhandled, 0);
        } else
            return ExportButtonMsg(msg, pUser, false);
    }
}

DataNode OvershellPanel::OnMsg(const UIComponentScrollMsg &msg) {
    if (TheUIEventMgr->HasActiveDialogEvent())
        return DataNode(kDataUnhandled, 0);
    else {
        return ExportToUser(msg, msg.GetUser(), msg.GetUIComponent());
    }
}

DataNode OvershellPanel::OnMsg(const UIComponentSelectMsg &msg) {
    if (TheUIEventMgr->HasActiveDialogEvent())
        return DataNode(kDataUnhandled, 0);
    else {
        return ExportToUser(msg, msg.GetUser(), msg.GetComponent());
    }
}

DataNode OvershellPanel::OnMsg(const UIComponentSelectDoneMsg &msg) {
    if (TheUIEventMgr->HasActiveDialogEvent())
        return DataNode(kDataUnhandled, 0);
    else {
        return ExportToUser(msg, msg.GetUser(), msg.GetComponent());
    }
}

DataNode OvershellPanel::OnMsg(const UIComponentFocusChangeMsg &msg) {
    if (TheUIEventMgr->HasActiveDialogEvent())
        return DataNode(kDataUnhandled, 0);
    else {
        return SlotHandle(msg.GetDir(), msg);
    }
}

DataNode OvershellPanel::OnMsg(const UITransitionCompleteMsg &) {
    UpdateAll();
    return DataNode(kDataUnhandled, 0);
}

DataNode OvershellPanel::OnMsg(const NetComponentSelectMsg &msg) {
    User *u = msg.GetUser();
    MILO_ASSERT(u, 0x854);
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0x859);
        if (pSlot->GetUser() == u) {
            UIComponent *c = pSlot->GetPanelDir()->FindComponent(msg.GetStr());
            if (c) {
                c->MockSelect();
                return 1;
            }
        }
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode OvershellPanel::OnMsg(const NetComponentScrollMsg &msg) {
    User *u = msg.GetUser();
    MILO_ASSERT(u, 0x86F);
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0x874);
        if (pSlot->GetUser() == u) {
            UIComponent *c = pSlot->GetPanelDir()->FindComponent(msg.GetStr());
            UIList *l = dynamic_cast<UIList *>(c);
            if (l) {
                l->SetSelected(msg.GetSelectedPos(), msg.GetFirstShowing());
            } else {
                UISlider *s = dynamic_cast<UISlider *>(c);
                s->SetCurrent(msg.GetSelectedPos());
            }
            return 1;
        }
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode OvershellPanel::OnMsg(const RemoteUserLeftMsg &msg) {
    MILO_ASSERT(IsLoaded(), 0x892);
    BandUser *user = BandUserMgr::GetBandUser(msg.GetUser());
    mBandUserMgr->SetSlot(user, -1);
    UpdateAll();
    return DataNode(kDataUnhandled, 0);
}

DataNode OvershellPanel::OnMsg(const RemoteMachineUpdatedMsg &msg) {
    if (msg.GetMask() & 1) {
        MILO_ASSERT(IsLoaded(), 0x8A6);
        UpdateAll();
    }
    return 1;
}

DataNode OvershellPanel::OnMsg(const RemoteUserUpdatedMsg &) {
    MILO_ASSERT(IsLoaded(), 0x8AE);
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const NewRemoteUserMsg &msg) {
    MILO_ASSERT(IsLoaded(), 0x8B5);
    RemoteBandUser *user = BandUserMgr::GetRemoteBandUser(msg.GetUser());
    OvershellSlot *slot = FindSlotForRemoteUser(user);
    MILO_ASSERT(slot, 0x8BA);
    mBandUserMgr->SetSlot(user, slot->GetSlotNum());
    UpdateAll();
    return 1;
}

DECOMP_FORCEACTIVE(OvershellPanel, "pSlotCur")

DataNode OvershellPanel::OnMsg(const SigninChangedMsg &) {
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const PartyMembersChangedMsg &) {
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const InviteReceivedMsg &) {
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const InviteExpiredMsg &) {
    UpdateAll();
    return 1;
}

DataNode OvershellPanel::OnMsg(const UserNameNewlyProfaneMsg &msg) {
    int idx = msg->Int(2);
    if (TheWiiProfileMgr.IsIndexRegistered(idx)) {
        const char *fmt = Localize(wiiprofile_create_error_newly_profane, nullptr);
        const char *name = TheWiiProfileMgr.GetNameForIndex(idx);
        TheWiiProfileMgr.SetIndexRegistered(idx, false);
        char buf[0x100];
        snprintf(buf, 0x100, fmt, name);
        Message msg("show_net_error", buf);
        TheBandUI.Handle(msg, true);
        RemoveUsersWithoutOnlinePrivilege();
        UpdateAll();
    }
    return 1;
}

DataNode OvershellPanel::OnUpdate(DataArray *arr) {
    DataNode &n = arr->Node(2).Evaluate();
    Update(n.Obj<OvershellSlot>());
    return 1;
}

void OvershellPanel::Update(OvershellSlot *slot) {
    if (slot)
        slot->Update();
}

DataNode OvershellPanel::OnExportAll(DataArray *arr) {
    DataNode &n = arr->Node(2);
    if (n.Type() == kDataSymbol) {
        Message msg(n.Sym());
        ExportAll(msg);
    } else {
        ExportAll(Message(arr->Array(2)));
    }
    return 1;
}

DataNode OvershellPanel::ExportButtonMsg(const Message &msg, BandUser *user, bool b3) {
    MILO_ASSERT(!mSlots.empty(), 0x95D);
    DataNode n28;
    if (!user) {
        return DataNode(kDataUnhandled, 0);
    }
    OvershellSlot *slot = FindSlotForUser(user);
    int i5 = msg->Int(4);
    if (slot) {
        UIComponent *c = slot->GetPanelDir()->FocusComponent();
        if (c && c->GetState() == UIComponent::kSelecting) {
            return n28;
        }
        if (slot->GetState()->AllowsInputToShell() && i5 != 4
            && mActiveStatus == kOvershellInSong) {
            return DataNode(kDataUnhandled, 0);
        }
        n28 = SlotHandle(slot, msg);
    } else if (b3) {
        static Message noSlotButtonDownMsg("no_slot_button_down_msg", 0);
        noSlotButtonDownMsg[0] = i5;
        HandleType(noSlotButtonDownMsg);
    }
    return n28;
}

OvershellSlot *OvershellPanel::FindSlotForUser(BandUser *user) {
    FOREACH (it, mSlots) {
        OvershellSlot *pSlotCur = *it;
        MILO_ASSERT(pSlotCur, 0x999);
        if (pSlotCur->GetUser() == user)
            return pSlotCur;
    }
    FOREACH (it, mSlots) {
        OvershellSlot *pSlotCur = *it;
        MILO_ASSERT(pSlotCur, 0x9A5);
        if (pSlotCur->IsValidUser(user))
            return pSlotCur;
    }
    return nullptr;
}

OvershellSlot *OvershellPanel::FindSlotForRemoteUser(RemoteBandUser *user) {
    std::vector<OvershellSlot *> slots;
    for (int i = 0; i < mSlots.size(); i++) {
        if (!mSlots[i]->GetUser()) {
            slots.push_back(mSlots[i]);
        }
    }
    ControllerType c = user->GetControllerType();
    for (int i = 0; i < slots.size(); i++) {
        if (slots[i]->IsValidControllerType(c)) {
            return slots[i];
        }
    }
    return nullptr;
}

void OvershellPanel::LeaveOptions() {
    for (int i = 0; i < mSlots.size(); i++) {
        BandUser *user = mSlots[i]->GetUser();
        if (user && user->IsLocal()) {
            mSlots[i]->LeaveOptions();
        }
    }
}

void OvershellPanel::CheckForControllerDisconnects() {
    if (!DataVariable(fake_controllers).Int()) {
        LocalBandUser *localUser;
        for (int i = 0; i < mSlots.size(); i++) {
            BandUser *user = mSlots[i]->GetUser();
            OvershellSlotStateID id = mSlots[i]->GetState()->GetStateID();
            if (user && user->IsLocal() && user->IsParticipating()) {
                localUser = user->GetLocalBandUser();
                if (localUser->ConnectedControllerType() != user->GetControllerType()
                    && mActiveStatus != kOvershellInactive) {
                    bool b2 = (TheUIEventMgr && TheUIEventMgr->HasDialogEvent(pad_lost));
                    bool removeOnDisconnect =
                        TheGameMode->Property("remove_user_on_disconnect_in_song")->Int();
                    if (InSong() && !removeOnDisconnect) {
                        if (mSlots[i]->GetState()->GetStateID() != 0x32) {
                            mSlots[i]->SetOverrideFlowReturnState(id);
                            mSlots[i]->ShowState((OvershellSlotStateID)0x32);
                        }
                    } else if (!mSlots[i]->GetState()->IsRemoveUserPrompt() && !b2) {
                        mSlots[i]->AttemptRemoveUser();
                    } else if (!b2 && TheUIEventMgr) {
                        static Message pad_lost_init("init", localUser);
                        pad_lost_init[0] = localUser;
                        TheUIEventMgr->TriggerEvent(pad_lost, pad_lost_init);
                        mSlots[i]->LeaveOptions();
                    }
                }
            }
        }
    }
}

DataNode
OvershellPanel::ExportToUser(const Message &msg, User *u, UIComponent *required) {
    if (u) {
        FOREACH (it, mSlots) {
            OvershellSlot *pSlot = *it;
            MILO_ASSERT(pSlot, 0xA31);
            BandUser *user = pSlot->GetUser();
            if (user == u) {
                MILO_ASSERT(required, 0xA38);
                if (pSlot->GetPanelDir()->FindComponent(required->Name()) == required) {
                    SlotHandle(pSlot, msg);
                    return 1;
                }
            }
        }
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode OvershellPanel::SlotHandle(PanelDir *dir, const Message &msg) {
    FOREACH (it, mSlots) {
        OvershellSlot *pSlot = *it;
        MILO_ASSERT(pSlot, 0xA4A);
        if (pSlot->GetPanelDir() == dir)
            return SlotHandle(pSlot, msg);
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode OvershellPanel::SlotHandle(OvershellSlot *pSlot, const Message &msg) {
    MILO_ASSERT(pSlot, 0xA57);
    return pSlot->Handle(msg, false);
}

DataNode OvershellPanel::OnMsg(const SessionBusyMsg &) {
    UpdateAll();
    return 1;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(OvershellPanel)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_MESSAGE(UIComponentScrollMsg)
    HANDLE_MESSAGE(UIComponentSelectMsg)
    HANDLE_MESSAGE(UIComponentSelectDoneMsg)
    HANDLE_MESSAGE(UIComponentFocusChangeMsg)
    HANDLE_MESSAGE(UITransitionCompleteMsg)
    HANDLE_MESSAGE(RemoteUserLeftMsg)
    HANDLE_MESSAGE(RemoteUserUpdatedMsg)
    HANDLE_MESSAGE(NewRemoteUserMsg)
    HANDLE_MESSAGE(RemoteMachineUpdatedMsg)
    HANDLE_MESSAGE(NetComponentSelectMsg)
    HANDLE_MESSAGE(NetComponentScrollMsg)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_MESSAGE(JoypadConnectionMsg)
    HANDLE_MESSAGE(GameMicsChangedMsg)
    HANDLE_MESSAGE(MatchmakerChangedMsg)
    HANDLE_MESSAGE(ServerStatusChangedMsg)
    HANDLE_MESSAGE(ConnectionStatusChangedMsg)
    HANDLE_MESSAGE(NetStartUtilityFinishedMsg)
    HANDLE_MESSAGE(PartyMembersChangedMsg)
    HANDLE_MESSAGE(InviteReceivedMsg)
    HANDLE_MESSAGE(InviteExpiredMsg)
    HANDLE_MESSAGE(UserNameNewlyProfaneMsg)
    HANDLE_MESSAGE(NetStartUtilityFinishedMsg)
    HANDLE(export_all, OnExportAll)
    HANDLE_ACTION(update_all, UpdateAll())
    HANDLE(update, OnUpdate)
    HANDLE_EXPR(get_panel_from_slot_num, GetSlot(_msg->Int(2)))
    HANDLE_EXPR(get_slot, GetSlot(_msg->Obj<BandUser>(2)))
    HANDLE_ACTION(set_active_status, SetActiveStatus((OvershellActiveStatus)_msg->Int(2)))
    HANDLE_ACTION(
        begin_override_flow, BeginOverrideFlow((OvershellOverrideFlow)_msg->Int(2))
    )
    HANDLE_ACTION(
        end_override_flow,
        EndOverrideFlow((OvershellOverrideFlow)_msg->Int(2), _msg->Int(3))
    )
    HANDLE_EXPR(in_override_flow, InOverrideFlow((OvershellOverrideFlow)_msg->Int(2)))
    HANDLE_ACTION(set_block_all_input, SetBlockAllInput(_msg->Int(2)))
    HANDLE_EXPR(all_slots_ready_to_play, AllSlotsReadyToPlay())
    HANDLE_EXPR(should_pause, ShouldPause())
    HANDLE_ACTION(attempt_to_add_user, AttemptToAddUser(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(is_any_slot_allowing_input_to_shell, IsAnySlotAllowingInputToShell())
    HANDLE_EXPR(get_first_user_allowing_input_to_shell, GetFirstUserAllowingInputToShell())
    HANDLE_EXPR(
        is_any_local_slot_allowing_input_to_shell, IsAnyLocalSlotAllowingInputToShell()
    )
    HANDLE_EXPR(is_any_slot_joinable, IsAnySlotJoinable())
    HANDLE_EXPR(is_non_vocalist_in_vocals_slot, IsNonVocalistInVocalsSlot())
    HANDLE_ACTION(set_allow_real_guitar_flow, unk4bc = _msg->Int(2))
    HANDLE_ACTION(enable_auto_vocals, EnableAutoVocals())
    HANDLE_ACTION(remove_users_requiring_song_options, RemoveUsersRequiringSongOptions())
    HANDLE_ACTION(set_song_options_required, SetSongOptionsRequired(_msg->Int(2)))
    HANDLE_ACTION(set_autohide, SetAutohide(_msg->Int(2)))
    HANDLE_ACTION(set_use_extended_mic_arrows, SetUseExtendedMicArrows(_msg->Int(2)))
    HANDLE_ACTION(set_allows_button_pulse, SetAllowsButtonPulse(_msg->Int(2)))
    HANDLE_ACTION(leave_options, LeaveOptions())
    HANDLE_EXPR(is_full, IsFull())
    HANDLE_MESSAGE(SessionBusyMsg)
    HANDLE_MESSAGE(SessionReadyMsg)
    HANDLE_MESSAGE(SessionDisconnectedMsg)
    HANDLE(add_sink, OnAddSink)
    HANDLE(remove_sink, OnRemoveSink)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xACC)
END_HANDLERS
#pragma pop