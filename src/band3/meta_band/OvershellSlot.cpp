#include "meta_band/OvershellSlot.h"
#include "BandProfile.h"
#include "OvershellSlotState.h"
#include "Utl.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameMicManager.h"
#include "meta/WiiProfileMgr.h"
#include "meta_band/BandProfile.h"
#include "meta_band/CharData.h"
#include "meta_band/InputMgr.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/NetSync.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/OvershellSlotState.h"
#include "meta_band/PassiveMessage.h"
#include "meta_band/SaveLoadManager.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/SessionUsersProviders.h"
#include "meta_band/CharProvider.h"
#include "meta_band/OvershellPartSelectProvider.h"
#include "meta_band/CymbalSelectionProvider.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/ProfileMgr.h"
#include "game/GameMode.h"
#include "meta_band/UIEventMgr.h"
#include "meta_band/Utl.h"
#include "net/Server.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Msg.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/Joypad_Wii.h"
#include "os/User.h"
#include "synth/MicManagerInterface.h"
#include "synth/Synth.h"
#include "tour/TourCharLocal.h"
#include "ui/UIComponent.h"
#include "ui/UIList.h"
#include "utl/Messages2.h"
#include "utl/Messages3.h"
#include "utl/Messages4.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include <cstddef>

MicClientID sNullMicClientID;

OvershellSlot::OvershellSlot(
    int i, OvershellPanel *panel, OvershellDir *dir, BandUserMgr *umgr, SessionMgr *smgr
)
    : mStateMgr(new OvershellSlotStateMgr()), mState(0),
      mOverrideFlowReturnState(kState_JoinedDefault), unk28((OvershellSlotStateID)0x82),
      mOvershell(panel), mBandUserMgr(umgr), mSessionMgr(smgr), mSlotNum(i),
      mOvershellDir(dir), mAutohideEnabled(0), mIsLeavingOptions(0),
      mCurrentView(gNullStr), mBlockAllInput(0), mInGame(0), mSongOptionsRequired(0),
      unk80(0), unk81(0), mCharForEdit(0), mCymbalConfiguration(0),
      mSlotOverrideFlow(kOverrideFlow_None) {
    mMessageQueue = new PassiveMessageQueue(this);
    mKickUsersProvider = new SessionUsersProvider(false, true, false);
    mMuteUsersProvider = new SessionUsersProvider(true, true, false);
    mCharProvider = new CharProvider(0, true, false);
    mSwappableProfilesProvider = new OvershellProfileProvider(mBandUserMgr);
    mPartSelectProvider = new OvershellPartSelectProvider(mOvershell);
    mCymbalProvider = new CymbalSelectionProvider(this);
    mSessionMgr->AddSink(this, LocalUserLeftMsg::Type());
    mOvershellDir->HandleType(init_msg);
    static Message setupProviders(9);
    setupProviders.SetType("setup_providers");
    setupProviders[0] = mCharProvider;
    setupProviders[1] = mSwappableProfilesProvider;
    setupProviders[2] = 0;
    setupProviders[3] = mPartSelectProvider;
    setupProviders[4] = mCymbalProvider;
    setupProviders[5] = TheModifierMgr;
    mOvershellDir->HandleType(setupProviders);
    mUserNameLabel = mOvershellDir->Find<BandLabel>("user_name.lbl", true);
    MILO_ASSERT(mUserNameLabel, 0xF1);
    TheServer->AddSink(this, UserLoginMsg::Type());
}

OvershellSlot::~OvershellSlot() {
    mSessionMgr->RemoveSink(this, LocalUserLeftMsg::Type());
    TheServer->RemoveSink(this, UserLoginMsg::Type());
    RELEASE(mSwappableProfilesProvider);
    RELEASE(mCharProvider);
    RELEASE(mMuteUsersProvider);
    RELEASE(mKickUsersProvider);
    RELEASE(mMessageQueue);
    RELEASE(mStateMgr);
    RELEASE(mPartSelectProvider);
    RELEASE(mCymbalProvider);
}

ObjectDir *OvershellSlot::DataDir() { return mOvershellDir; }

void OvershellSlot::SetTypeDef(DataArray *da) {
    if (TypeDef() != da) {
        Hmx::Object::SetTypeDef(da);
        mStateMgr->Init(da->FindArray(state_handlers, true), this);
        float dur = 0;
        if (da->FindData(msg_duration, dur, false)) {
            mMessageQueue->SetMessageDuration(dur);
        }
    }
}

void OvershellSlot::Enter() { Hmx::Object::Handle(enter_msg, false); }

void OvershellSlot::Poll() {
    mMessageQueue->Poll();
    mIsLeavingOptions = false;
}

int OvershellSlot::GetSlotNum() { return mSlotNum; }
PanelDir *OvershellSlot::GetPanelDir() { return mOvershellDir; }

FORCE_LOCAL_INLINE
bool OvershellSlot::IsHidden() const {
    return mAutohideEnabled && mState->AllowsHiding();
}
END_FORCE_LOCAL_INLINE

bool OvershellSlot::IsLeavingOptions() const { return mIsLeavingOptions; }

FORCE_LOCAL_INLINE
Symbol OvershellSlot::GetCurrentView() const { return mCurrentView; }
END_FORCE_LOCAL_INLINE

void OvershellSlot::ClearPotentialUsers() { mPotentialUsers.clear(); }

void OvershellSlot::AddPotentialUser(PotentialUserEntry e) {
    mPotentialUsers.push_back(e);
}

int OvershellSlot::NumPotentialUsers() const { return mPotentialUsers.size(); }

bool OvershellSlot::LookupUserInJoinList(const LocalBandUser *user, JoinState *state) {
    if (user) {
        for (std::vector<PotentialUserEntry>::iterator it = mPotentialUsers.begin();
             it != mPotentialUsers.end();
             ++it) {
            if (it->mUser == user) {
                *state = it->mJoinState;
                return true;
            }
        }
    }
    return false;
}

bool OvershellSlot::IsValidControllerType(ControllerType ty) {
    std::vector<ControllerType> &vec =
        TheModifierMgr && TheModifierMgr->IsModifierActive(mod_auto_vocals) ? unk48
                                                                            : unk40;
    for (int i = 0; i < vec.size(); i++) {
        if (ty == vec[i])
            return true;
    }
    return false;
}

FORCE_LOCAL_INLINE
BandUser *OvershellSlot::GetUser() const {
    return mBandUserMgr->GetUserFromSlot(mSlotNum);
}
END_FORCE_LOCAL_INLINE

OvershellSlotState *OvershellSlot::GetState() {
    MILO_ASSERT(mState, 0x1B2);
    return mState;
}

OvershellSlotState *OvershellSlot::GenerateCurrentState() {
    OvershellSlotStateID id = kState_NoInstrument;
    BandUser *user = GetUser();
    if (user)
        id = user->mOvershellState;
    else {
        if (mOvershell->IsFinding())
            id = kState_Finding;
        else {
            if (mPotentialUsers.empty())
                id = kState_NoInstrument;
            else {
                JoinState jstate = mPotentialUsers[0].mJoinState;
                switch (jstate) {
                case kMetaJoinOK:
                    id = kState_Join;
                    break;
                case kMetaJoinNeedsMic:
                    id = kState_ConnectMic;
                    break;
                case kMetaJoinNeedsOnline:
                    id = kState_SignIn;
                    break;
                case (JoinState)3:
                    id = (OvershellSlotStateID)0x39;
                    break;
                default:
                    MILO_FAIL("Unknown user entry state %i\n", jstate);
                    break;
                }
            }
        }
    }
    return mStateMgr->GetSlotState(id);
}

void OvershellSlot::RemoveUser() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser, 0x1E5);
    LocalBandUser *pLocUser = pUser->GetLocalBandUser();
    MILO_ASSERT(pLocUser, 0x1E7);
    if (TheSaveLoadMgr)
        TheSaveLoadMgr->AutoSaveNow();
    TheWiiProfileMgr.RemovePad(pLocUser->GetPadNum());
    mSessionMgr->RemoveLocalUser(pLocUser);
    ResetSlotCamera();
}

DataNode OvershellSlot::OnMsg(const LocalUserLeftMsg &msg) {
    BandUser *user = GetUser();
    if (user && user->IsLocal()) {
        if (user->GetLocalBandUser() == msg.GetUser()) {
            mSongOptionsRequired = false;
            mBandUserMgr->ClearSlot(user);
            SetOverrideType(kOverrideFlow_None, false);
            JoypadWiiOnUserLeft(user->GetLocalBandUser()->GetPadNum(), false);
            mOvershell->UpdateAll();
        }
    }
    return 1;
}

void OvershellSlot::ShowState(OvershellSlotStateID id) {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x21B);
    if (id == kState_ReconnectController) {
        UILabel *lbl = mOvershellDir->Find<UILabel>("reconnect_controller.lbl", false);
        if (lbl) {
            static Symbol overshell_reconnect_controller("overshell_reconnect_controller"
            );
            static Symbol wii_error_remote_extension_x("wii_error_remote_extension_x");
            int padnum = pUser->GetLocalBandUser()->GetPadNum();
            JoypadType j0 = kJoypadNone;
            JoypadType j1 = kJoypadNone;
            ControllerType cty = pUser->GetControllerType();
            Symbol capsmodesym = overshell_reconnect_controller;
            switch (GetWiiJoypadDisconnectType(padnum, &j0, &j1)) {
            case 1:
                break;
            case 2:
                if (cty == 2)
                    capsmodesym = wii_error_remote_extension_x;
                // break;
            default:
                if (capsmodesym == overshell_reconnect_controller) {
                    lbl->SetCapsMode(RndText::kForceUpper);
                } else {
                    lbl->SetCapsMode(RndText::kCapsModeNone);
                }
                break;
            }
            if (capsmodesym == overshell_reconnect_controller) {
                lbl->SetTextToken(capsmodesym);
            } else {
                Symbol ctysym = ControllerTypeToSym(cty);
                if (!ctysym.Null()) {
                    lbl->SetTokenFmt(capsmodesym, ctysym);
                } else {
                    lbl->SetTextToken(overshell_reconnect_controller);
                }
            }
        }
    }
    pUser->SetOvershellSlotState(id);
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveOptions() {
    ShowState(kState_JoinedDefault);
    mIsLeavingOptions = true;
}

void OvershellSlot::ShowProfiles() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x2A8);
    pUser->SetOvershellSlotState(kState_ChooseProfile);
    mOvershell->UpdateAll();
}

void OvershellSlot::AttemptRegisterOnline() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x2B0);
    if (TheModifierMgr && TheModifierMgr->IsModifierActive(mod_auto_vocals)) {
        pUser->SetOvershellSlotState(kState_RegisterOnlineDenial);
        mOvershell->UpdateAll();
    } else {
        if (mOvershell->mPanelOverrideFlow != 0) {
            mOvershell->UpdateAll();
        } else
            mOvershell->BeginOverrideFlow(kOverrideFlow_RegisterOnline);
    }
}

void OvershellSlot::ShowOnlineOptions() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x2CA);
    pUser->SetOvershellSlotState(kState_OnlineOptions);
    if (mSessionMgr->IsOnlineEnabled())
        mOvershell->UpdateAll();
    else
        AttemptRegisterOnline();
}

void OvershellSlot::ShowSongOptions() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x2DA);
    BandUser *user = mSessionMgr->mCritUserListener->mCriticalUser;
    if (InGame() && !mSongOptionsRequired) {
        pUser->SetOvershellSlotState(kState_ChooseDiff);
    } else {
        if (user && user != pUser) {
            pUser->SetTrackType(kTrackNone);
            pUser->SetOvershellSlotState(kState_ReadyToPlay);
        } else {
            if (TheGameMode->Property("skip_choose_part", true)->Int()) {
                int part = TheGameMode->Property("forced_part", true)->Int();
                if (part == kTrackNone) {
                    part = ControllerTypeToTrackType(pUser->GetControllerType(), false);
                }
                pUser->SetTrackType((TrackType)part);
                pUser->SetOvershellSlotState(kState_ChooseDiff);
            } else
                pUser->SetOvershellSlotState(kState_ChoosePart);
        }
    }
    mOvershell->UpdateAll();
}

void OvershellSlot::SelectPart(TrackType trackType) {
    MILO_ASSERT(trackType != kTrackVocals, 0x2FD);
    MILO_ASSERT(trackType != kTrackDrum, 0x2FE);
    SelectPartImpl(trackType, false, false);
}

void OvershellSlot::SelectVocalPart(bool b) { SelectPartImpl(kTrackVocals, b, false); }

void OvershellSlot::SelectDrumPart(bool b) { SelectPartImpl(kTrackDrum, false, b); }

void OvershellSlot::SelectPartImpl(TrackType track, bool harmony, bool proDrums) {
    MILO_ASSERT(track == kTrackVocals || !harmony, 0x30E);
    MILO_ASSERT(track == kTrackDrum || !proDrums, 0x30F);
    bool b3 = false;
    bool b1 = false;
    bool b2 = false;
    MetaPerformer *perf = MetaPerformer::Current();
    if (perf) {
        b3 = true;
        if (!perf->SetHasMissingPart(TrackTypeToSym(track))) {
            b1 = false;
            if (harmony && perf->SetHasMissingVocalHarmony())
                b1 = true;
            if (!b1)
                b3 = false;
        }
        b1 = true;
        if (perf->PartPlaysInSet(TrackTypeToSym(track))) {
            b2 = false;
            if (harmony && !perf->SetlistHasVocalHarmony()) {
                b2 = true;
            }
            if (!b2)
                b1 = false;
        }
        ScoreType s5 = TrackTypeToScoreType(track, harmony, proDrums);
        b2 = false;
        if (perf->HasBattle() && perf->GetBattleInstrument() != kScoreBand
            && s5 != perf->GetBattleInstrument()) {
            b2 = true;
        }
    }
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser, 0x325);
    MILO_ASSERT(pUser->IsLocal(), 0x326);
    if (mSessionMgr->mCritUserListener->mCriticalUser == pUser && b3) {
        pUser->SetOvershellSlotState(kState_ChoosePartDenial);
    } else if (b1) {
        pUser->SetOvershellSlotState(kState_ChoosePartDenial);
    } else {
        pUser->SetTrackType(track);
        if (harmony) {
            pUser->SetPreferredScoreType(kScoreHarmony);
        } else if (track == kTrackVocals) {
            pUser->SetPreferredScoreType(kScoreVocals);
        }
        if (proDrums) {
            pUser->SetPreferredScoreType(kScoreRealDrum);
        } else if (track == kTrackDrum) {
            pUser->SetPreferredScoreType(kScoreDrum);
        }
        if (b2) {
            pUser->SetOvershellSlotState(kState_NotBattlePartWarn);
        } else if (b3) {
            pUser->SetOvershellSlotState(kState_ChoosePartWarn);
        } else
            ShowChoosePartWait();
    }
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowChoosePartWait() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser, 0x367);
    MILO_ASSERT(pUser->IsLocal(), 0x368);
    bool b1 = pUser->GetTrackType() == kTrackDrum
        && pUser->GetPreferredScoreType() == kScoreRealDrum;
    unsigned int cymbals = TheProfileMgr.GetCymbalConfiguration();
    if (b1 && cymbals == 0) {
        mCymbalConfiguration = cymbals;
        pUser->SetOvershellSlotState(kState_OptionsDrumInSongSettings);
    } else {
        pUser->SetOvershellSlotState(kState_ChoosePartWait);
    }
    mOvershell->UpdateAll();
}

void OvershellSlot::ToggleHiHatPedal() {
    TheProfileMgr.SetSecondPedalHiHat(TheProfileMgr.GetSecondPedalHiHat() == 0);
}

void OvershellSlot::ToggleCymbal(Symbol s) {
    unsigned int cymBit = 0;
    if (s == overshell_yellow_cym)
        cymBit = 4;
    else if (s == overshell_blue_cym)
        cymBit = 8;
    else if (s == overshell_green_cym)
        cymBit = 0x10;
    MILO_ASSERT(cymBit != 0, 0x391);
    mCymbalConfiguration ^= cymBit;
}

bool OvershellSlot::IsCymbalSelected(Symbol s) {
    if (s == overshell_yellow_cym && (mCymbalConfiguration & 4))
        return true;
    else if (s == overshell_blue_cym && (mCymbalConfiguration & 8))
        return true;
    else if (s == overshell_green_cym && (mCymbalConfiguration & 0x10))
        return true;
    else
        return false;
}

void OvershellSlot::FinishCymbalSelect(bool b) {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x3A8);
    if (b) {
        if (InOverrideFlow(kOverrideFlow_SongSettings) == 1U)
            pUser->SetOvershellSlotState(kState_ChoosePart);
    } else {
        TheProfileMgr.SetCymbalConfiguration(mCymbalConfiguration);
        if (InOverrideFlow(kOverrideFlow_SongSettings) == 1U)
            pUser->SetOvershellSlotState(kState_OptionsDrumMessage);
    }
    if (!InOverrideFlow(kOverrideFlow_SongSettings))
        pUser->SetOvershellSlotState(kState_GameOptions);
    mOvershell->UpdateAll();
}

void OvershellSlot::DismissCymbalMessage() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x3BF);
    pUser->SetOvershellSlotState(kState_ChooseDiff);
    mOvershell->UpdateAll();
}

void OvershellSlot::SelectDifficulty(Difficulty diff) {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser, 0x3C7);
    MILO_ASSERT(pUser->IsLocal(), 0x3C8);
    bool old5e = mSongOptionsRequired;
    mSongOptionsRequired = 0;
    if (mOvershell->SongOptionsRequired()) {
        if (!old5e && mOvershell->InSong()) {
            if (!TheGameMode->Property("skip_choose_diff_prompt", true)->Int()) {
                Difficulty pUserDiff = pUser->GetDifficulty();
                if (diff == pUserDiff)
                    CancelSongSettings();
                else {
                    mStateMgr->GetSlotState(kState_ChooseDiffConfirm)
                        ->SetProperty("difficulty", diff);
                    pUser->SetOvershellSlotState(kState_ChooseDiffConfirm);
                }
            }
            goto lol;
        }
        pUser->SetDifficulty(diff);
        EndOverrideFlow(kOverrideFlow_SongSettings, true);
    } else {
        pUser->SetDifficulty(diff);
        pUser->SetOvershellSlotState(kState_ReadyToPlay);
    }
lol:
    MILO_ASSERT(pUser->GetTrackType() != kTrackNone, 0x3E5);
    if (old5e) {
        if (InGame()) {
            static Message chosenMsg("required_song_options_chosen", 0);
            chosenMsg[0] = pUser;
            mOvershell->Export(chosenMsg, true);
        }
    }
    mOvershell->UpdateAll();
}

void OvershellSlot::ConfirmChooseDiff() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x3F8);
    pUser->SetDifficulty((Difficulty)mState->Property("difficulty", true)->Int());
    EndOverrideFlow(kOverrideFlow_SongSettings, true);
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveDifficultyConfirmation() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x403);
    pUser->SetOvershellSlotState(kState_ChooseDiff);
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveChoosePart() {
    CancelSongSettings();
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveChoosePartWait() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x411);
    pUser->SetTrackType(kTrackNone);
    pUser->SetOvershellSlotState(kState_ChoosePart);
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveChooseDifficulty() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x41A);
    if (!TheGameMode->Property("skip_choose_part", true)->Int()
        && (!mInGame || mSongOptionsRequired)) {
        pUser->SetTrackType(kTrackNone);
        pUser->SetOvershellSlotState(kState_ChoosePart);
    } else
        CancelSongSettings();
    mOvershell->UpdateAll();
}

void OvershellSlot::CancelSongSettings() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x42E);
    if (mOvershell->mSongOptionsRequired) {
        if (mSongOptionsRequired) {
            AttemptRemoveUser();
        } else {
            SetOverrideFlowReturnState(kState_Options);
            EndOverrideFlow(kOverrideFlow_SongSettings, true);
        }
    } else {
        if (mBandUserMgr->GetNumParticipants() <= 1) {
            mOvershell->EndOverrideFlow(kOverrideFlow_SongSettings, true);
        } else
            ShowState(kState_SongOptionsCancel);
    }
}

void OvershellSlot::LeaveReadyToPlay() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x44C);
    BandUser *critUser = mSessionMgr->mCritUserListener->mCriticalUser;
    if (critUser && critUser != pUser) {
        CancelSongSettings();
    } else {
        pUser->SetOvershellSlotState(kState_ChooseDiff);
        mOvershell->UpdateAll();
    }
}

void OvershellSlot::LeaveSignInWait() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x45E);
    pUser->SetOvershellSlotState(kState_SignInToRegisterNoResolve);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowEnterWiiSpeakOptions() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x466);
    pUser->SetOvershellSlotState(kState_EnterWiiSpeakOptions);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowEnterWiiProfile() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x46E);
    if (mSessionMgr->IsLocal()) {
        pUser->SetOvershellSlotState(kState_EnterWiiProfile);
    } else
        pUser->SetOvershellSlotState(kState_WiiProfileDenial);
    mOvershell->UpdateAll();
}

void OvershellSlot::AttemptDisconnect() {
    if (mSessionMgr->IsLocal()) {
        mSessionMgr->Disconnect();
    } else {
        BandUser *pUser = GetUser();
        MILO_ASSERT(pUser->IsLocal(), 0x48C);
        pUser->SetOvershellSlotState(kState_DisconnectConfirm);
        mOvershell->UpdateAll();
    }
}

void OvershellSlot::AttemptRemoveUser() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x495);

    bool b1 = false;
    if (!mSessionMgr->IsLocal()) {
        LocalBandUser *host = mSessionMgr->GetLocalHost();
        if (host == pUser->GetLocalUser()) {
            b1 = true;
        } else {
            LocalUser *lUser = dynamic_cast<LocalUser *>(pUser);
            int i;
            for (i = 0; i < 4; i++) {
                if (i != lUser->GetPadNum()) {
                    int idx = TheWiiProfileMgr.GetIndexForPad(i);
                    if (idx >= 0 && TheWiiProfileMgr.IsIndexValid(idx)
                        && !TheWiiProfileMgr.IsPadAGuest(i)
                        && TheWiiProfileMgr.IsPadRegistered(i))
                        break;
                }
            }
            if (i == 4)
                b1 = true;
        }
    }

    if (b1) {
        pUser->SetOvershellSlotState((OvershellSlotStateID)0x1A);
        mOvershell->UpdateAll();
    } else if (mSessionMgr->mCritUserListener->mCriticalUser == pUser) {
        pUser->SetOvershellSlotState((OvershellSlotStateID)0x41);
        mOvershell->UpdateAll();
    } else if (mOvershell->InSong()) {
        pUser->SetOvershellSlotState((OvershellSlotStateID)0x4D);
        mOvershell->UpdateAll();
    } else if (TheProfileMgr.IsPrimaryProfileCritical(pUser->GetLocalUser())) {
        pUser->SetOvershellSlotState((OvershellSlotStateID)0xCB);
        mOvershell->UpdateAll();
    } else
        RemoveUser();
}

void OvershellSlot::ShowChordBook() {
    LeaveOptions();
    mOvershell->UpdateAll();
}

void OvershellSlot::PracticeNewSection() { mOvershell->UpdateAll(); }
void OvershellSlot::ToggleMetronome() { mOvershell->UpdateAll(); }

void OvershellSlot::KickUser(int i) {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x4FB);
    OvershellSlotState *ostate = mStateMgr->GetSlotState(kState_KickConfirmation);
    ostate->SetProperty("kick_user", mKickUsersProvider->GetUser(i));
    pUser->SetOvershellSlotState(kState_KickConfirmation);
    mOvershell->UpdateAll();
}

void OvershellSlot::ConfirmKick() {
    BandUser *pUserToKick = mState->Property("kick_user", true)->Obj<BandUser>();
    MILO_ASSERT(pUserToKick != NULL, 0x505);
    mKickUsersProvider->KickPlayer(pUserToKick);
    LeaveKickConfirmation();
}

void OvershellSlot::LeaveKickConfirmation() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x50D);
    pUser->SetOvershellSlotState(kState_KickUsers);
    mOvershell->UpdateAll();
}

void OvershellSlot::ToggleMuteUser(int i) {
    mMuteUsersProvider->ToggleMuteStatus(i);
    mOvershell->UpdateAll();
}

void OvershellSlot::ActOnUserProfile(int i) {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x52B);
    HandleWiiProfileActResult(
        mSwappableProfilesProvider->ActOnProfile(i, pUser->GetLocalBandUser(), false)
    );
}

void OvershellSlot::ActOnUserProfileConfirm() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x534);
    HandleWiiProfileActResult(
        mSwappableProfilesProvider->ActOnProfileConfirmed(pUser->GetLocalBandUser())
    );
}

void OvershellSlot::HandleWiiProfileActResult(WiiProfileActResult res) {
    switch (res) {
    case 1:
        ShowWiiProfileConfirm();
        break;
    case 2:
        ShowWiiProfilePreconfirm();
        break;
    case 3:
        ShowWiiProfileSwitchConfirm();
        break;
    case 4:
        ShowEnterWiiProfile();
        break;
    case 5: {
        BandUser *pUser = GetUser();
        MILO_ASSERT(pUser->IsLocal(), 0x54C);
        if (mSessionMgr->IsLocal()) {
            pUser->SetOvershellSlotState((OvershellSlotStateID)0xcc);
        } else
            pUser->SetOvershellSlotState((OvershellSlotStateID)0xce);
        mOvershell->UpdateAll();
        break;
    }
    case 6:
        ShowWiiProfileFail();
        break;
    case 7:
        ShowWiiProfileFailCreate();
        break;
    case 8:
        ShowWiiProfilePostAction();
        break;
    case 9:
        MILO_ASSERT(mSwappableProfilesProvider, 0x561);
        AttemptSwapUserProfile(mSwappableProfilesProvider->unk24);
        break;
    default:
        LeaveOptions();
        break;
    }
}

void OvershellSlot::SelectGuestProfile() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x594);
    LocalBandUser *pLocUser = pUser->GetLocalBandUser();
    MILO_ASSERT(pLocUser, 0x596);
    int padnum = pLocUser->GetPadNum();
    if (TheSaveLoadMgr)
        TheSaveLoadMgr->AutoSaveNow();
    BandProfile *profile = TheProfileMgr.GetProfileForUser(pLocUser);
    if (profile) {
        profile->DeleteAll();
    }
    TheWiiProfileMgr.SetPadToGuest(padnum);
    pLocUser->UpdateOnlineID();
}

void OvershellSlot::ShowWiiProfileConfirm() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x5AD);
    pUser->SetOvershellSlotState(kState_WiiProfileConfirm);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfilePreconfirm() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x5B5);
    pUser->SetOvershellSlotState(kState_WiiProfilePreconfirm);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileSwitchConfirm() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x5BD);
    pUser->SetOvershellSlotState(kState_WiiProfileSwitchConfirm);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileFail() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x5C5);
    pUser->SetOvershellSlotState(kState_WiiProfileFail);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileFailBusy() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x5CD);
    pUser->SetOvershellSlotState(kState_WiiProfileFailBusy);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileFailCreate() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x5D5);
    pUser->SetOvershellSlotState(kState_WiiProfileFailCreate);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileSwapFail() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x5DD);
    pUser->SetOvershellSlotState(kState_WiiProfileSwapFail);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfilePostAction() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x5E5);
    pUser->SetOvershellSlotState(kState_WiiProfilePostAction);
    mOvershell->UpdateAll();
}

void OvershellSlot::SetWiiProfileListMode(int i, bool b) {
    if (i != 0x10)
        mSwappableProfilesProvider->SetWiiProfileListMode(
            (OvershellProfileProvider::WiiProfileListMode)i, b
        );
}

OvershellProfileProvider::WiiProfileListMode OvershellSlot::GetWiiProfileListMode() {
    return mSwappableProfilesProvider->GetWiiProfileListMode();
}

int OvershellSlot::GetWiiProfileLastIndex() { return mSwappableProfilesProvider->unk24; }

bool OvershellSlot::IsWiiProfileFull() const {
    return !TheWiiProfileMgr.IsSlotAvailable();
}

bool OvershellSlot::IsWiiProfileDeleteQueueFull() const {
    return TheWiiProfileMgr.IsDeleteQueueFull();
}

const char *OvershellSlot::GetWiiProfileListSelectedName() const {
    return mSwappableProfilesProvider->GetWiiProfileSelectedName();
}

void OvershellSlot::ShowWiiProfileList(int i) {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x60E);
    SetWiiProfileListMode(i, false);
    if (i == 0 || i == 2) {
        pUser->SetOvershellSlotState(kState_EnterWiiProfile);
    } else {
        if (mSwappableProfilesProvider->GetWiiProfileCount(pUser->GetLocalBandUser())
            <= 0) {
            pUser->SetOvershellSlotState(kState_WiiProfileListEmpty);
        } else
            pUser->SetOvershellSlotState(kState_WiiProfileList);
    }
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileOptions() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x62A);
    LocalBandUser *pLocalUser = pUser->GetLocalBandUser();
    MILO_ASSERT(pLocalUser, 0x62D);
    unk28 = (OvershellSlotStateID)0x82;
    pUser->SetOvershellSlotState(kState_WiiProfileOptions);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWaitWii() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x638);
    pUser->SetOvershellSlotState(kState_WaitWii);
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveWaitWii() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x640);
    pUser->SetOvershellSlotState(kState_JoinedDefault);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileSelector(bool b) {
    OvershellSlotState *ostate = GetState();
    OvershellSlotStateID oid = kState_JoinedDefault;
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x64A);
    if (ostate)
        oid = ostate->GetStateID();
    unk28 = oid;
    SetWiiProfileListMode(1, b);
    if (mSwappableProfilesProvider->GetWiiProfileCount(pUser->GetLocalBandUser()) <= 0) {
        ShowState(kState_WiiProfileListEmpty);
    } else
        ShowState(kState_WiiProfileList);
}

void OvershellSlot::CancelWiiProfileSelector() {
    ShowState((OvershellSlotStateID)unk28);
    unk28 = kState_WiiProfileOptions;
}

WiiProfile *OvershellSlot::GetUserWiiProfile() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x669);
    return TheWiiProfileMgr.GetProfileForPad(pUser->GetLocalBandUser()->GetPadNum());
}

void OvershellSlot::ToggleWiiSpeak() {
    TheProfileMgr.SetWiiSpeakToggle(!TheProfileMgr.mWiiSpeakToggle);
}

void OvershellSlot::AttemptSwapUserProfile(int i) {
    int pad = TheWiiProfileMgr.GetPadForIndex(i);
    if (pad >= 0) {
        LocalBandUser *user = mBandUserMgr->GetUserFromPad(pad);
        OvershellSlotState *state = mStateMgr->GetSlotState(kState_ChooseProfileConfirm);
        state->SetProperty("swap_user", user);
        ShowState(kState_ChooseProfileConfirm);
    }
}

bool OvershellSlot::ConfirmSwapUserProfile() {
    OvershellSlotState *state = mStateMgr->GetSlotState(kState_ChooseProfileConfirm);
    return SwapUserProfile(state->Property("swap_user", true)->Obj<LocalBandUser>());
}

bool OvershellSlot::SwapUserProfile(LocalBandUser *) {
    ShowWiiProfileFail();
    return false;
}

void OvershellSlot::ShowOptionsDrum() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x70A);
    mCymbalConfiguration = TheProfileMgr.GetCymbalConfiguration();
    pUser->SetOvershellSlotState(kState_OptionsDrum);
    mOvershell->UpdateAll();
}

void OvershellSlot::AttemptToggleAutoVocals() {
    if (MetaPerformer::Current()) {
        BandUser *pUser = GetUser();
        MILO_ASSERT(pUser->IsLocal(), 0x715);
        if (TheModifierMgr->IsModifierActive(mod_auto_vocals)) {
            if (mOvershell->IsNonVocalistInVocalsSlot() || mInGame) {
                pUser->SetOvershellSlotState((OvershellSlotStateID)0x23);
            } else
                TheModifierMgr->DisableAutoVocals();
        } else {
            bool b1 = false;
            if (mBandUserMgr->GetNumLocalParticipants() == 1
                && pUser->GetControllerType() == 2)
                b1 = true;
            if (mOvershell->IsAutoVocalsAllowed() && !b1) {
                TheUIEventMgr->TriggerEvent(auto_vocals_confirm, nullptr);
            } else
                pUser->SetOvershellSlotState((OvershellSlotStateID)0x23);
        }
        mOvershell->UpdateAll();
    }
}

void OvershellSlot::FetchLinkingCode() {
    MILO_ASSERT(mState->GetStateID() == kState_LinkingCode, 0x744);
    mState->SetProperty(waiting, 1);
    mState->SetProperty(success, 0);
    mState->SetProperty(code, "");
    BandUser *pUser = GetUser();
    if (pUser->IsLocal()) {
        int padnum = pUser->GetLocalBandUser()->GetPadNum();
        if (TheServer->GetPlayerID(padnum) != 0) {
            TheRockCentral.GetLinkingCode(padnum, mLinkingCodeResultList, this);
            unk81 = true;
        } else
            unk80 = true;
        Update();
    }
}

void OvershellSlot::CancelLinkingCode() {
    MILO_ASSERT(mState->GetStateID() == kState_LinkingCode, 0x769);
    unk80 = false;
    unk81 = false;
    TheRockCentral.CancelOutstandingCalls(this);
}

DataNode OvershellSlot::OnMsg(const RockCentralOpCompleteMsg &msg) {
    MILO_ASSERT(mState->GetStateID() == kState_LinkingCode, 0x777);
    mState->SetProperty(waiting, 0);
    mState->SetProperty(success, msg.Arg0());
    if (msg.Arg0()) {
        DataNode node(0);
        mLinkingCodeResultList.Update(nullptr);
        mLinkingCodeResultList.GetDataResult(0)->GetDataResultValue("code", node);
        mState->SetProperty(code, node.Str());
    }
    mLinkingCodeResultList.Clear();
    Update();
    unk81 = false;
    return 1;
}

void OvershellSlot::AddValidController(ControllerType cty) { unk40.push_back(cty); }

void OvershellSlot::AddAutoVocalsValidController(ControllerType cty) {
    unk48.push_back(cty);
}

void OvershellSlot::ToggleVocalStyle() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x79E);
    MILO_ASSERT(pUser->GetControllerType() == kControllerVocals, 0x79F);
    GameplayOptions *options = pUser->GetGameplayOptions();
    if (options->GetVocalStyle() == kVocalStyleStatic) {
        options->SetVocalStyle(kVocalStyleScrolling);
    } else
        options->SetVocalStyle(kVocalStyleStatic);
    Update();
}

void OvershellSlot::ToggleLeftyFlip() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0x7AB);
    MILO_ASSERT(pUser->GetControllerType() != kControllerVocals, 0x7AC);
    GameplayOptions *options = pUser->GetGameplayOptions();
    options->SetLefty(options->GetLefty() == 0);
    Update();
}

void OvershellSlot::ResetSlotCamera() { mOvershellDir->HandleType(reset_cam_msg); }

void OvershellSlot::EnableAutohide(bool b) {
    if (mAutohideEnabled != b) {
        mAutohideEnabled = b;
        Update();
    }
}

void OvershellSlot::SetBlockAllInput(bool b) {
    if (mBlockAllInput != b) {
        mBlockAllInput = b;
        Update();
    }
}

void OvershellSlot::SetInGame(bool b) {
    if (mInGame != b) {
        mInGame = b;
        Update();
    }
}

void OvershellSlot::SetInTrackMode(bool b) {
    mOvershellDir->SetProperty("in_track_mode", b);
}

void OvershellSlot::SetView(Symbol s) {
    mCurrentView = s;
    mOvershellDir->SetProperty("slot_view", s);
}

void OvershellSlot::SetOverrideFlowReturnState(OvershellSlotStateID oid) {
    MILO_ASSERT(GetUser()->IsLocal(), 0x7E0);
    mOverrideFlowReturnState = oid;
}

void OvershellSlot::RevertToOverrideFlowReturnState() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser, 0x7e7);
    MILO_ASSERT(pUser->IsLocal(), 0x7E8);
    pUser->SetOvershellSlotState((OvershellSlotStateID)mOverrideFlowReturnState);
    mOverrideFlowReturnState = kState_JoinedDefault;
    mOvershell->UpdateAll();
}

bool OvershellSlot::IsValidUser(BandUser *user) const {
    if (!user)
        return false;
    BandUser *curUser = GetUser();
    if (user == curUser)
        return true;
    else if (curUser)
        return false;
    else {
        FOREACH (it, mPotentialUsers) {
            if (it->mUser == user)
                return true;
        }
        return false;
    }
}

bool OvershellSlot::IsQuitToken(Symbol s) const {
    return s == TheGameMode->Property("pause_menu_quit_token", true)->Sym();
}

bool OvershellSlot::InOverrideFlow(OvershellOverrideFlow flow) const {
    if (mSlotOverrideFlow == flow)
        return true;
    else
        return mOvershell->mPanelOverrideFlow == flow;
}

void OvershellSlot::BeginOverrideFlow(OvershellOverrideFlow type, bool b) {
    MILO_ASSERT(mSlotOverrideFlow == kOverrideFlow_None, 0x826);
    MILO_ASSERT(type != kOverrideFlow_None, 0x827);
    SetOverrideType(type, b);
}

void OvershellSlot::EndOverrideFlow(OvershellOverrideFlow type, bool b) {
    MILO_ASSERT(mSlotOverrideFlow == type, 0x82D);
    if (type == kOverrideFlow_SongSettings)
        mSongOptionsRequired = false;
    SetOverrideType(kOverrideFlow_None, b);
}

void OvershellSlot::SetOverrideType(OvershellOverrideFlow type, bool b) {
    mSlotOverrideFlow = type;
    if (b)
        mOvershell->UpdateAll();
}

// big chunguses...chungi?
void OvershellSlot::UpdateState() {
    BandUser *pUser = GetUser();
    OvershellSlotState *curState = GenerateCurrentState();
    if (!mState || (curState->GetStateID() != mState->GetStateID())) {
        bool b2 = false;
        if (mState) {
            mState->HandleMsg(exit_msg);
            if (!pUser || pUser->IsLocal()) {
                if (mState->RetractedPosition() && !curState->RetractedPosition()) {
                    TheSynth->Play("overshell_up.cue", 0, 0, 0);
                }
                if (!mState->RetractedPosition() && curState->RetractedPosition()) {
                    TheSynth->Play("overshell_down.cue", 0, 0, 0);
                }
            }
            if (mState->AllowsInputToShell() != curState->AllowsInputToShell())
                b2 = true;
        }
        mState = curState;
        if (b2) {
            static OvershellAllowingInputChangedMsg allowingInputMsg(GetUser());
            allowingInputMsg[0] = GetUser();
            mOvershell->Export(allowingInputMsg, true);
        }
        mState->HandleMsg(enter_msg);
    }

    if (pUser && pUser->IsLocal()) {
        LocalBandUser *localUser = pUser->GetLocalBandUser();
        if (mState->GetStateID() == 0x2F) {
            bool cannotSave = !localUser->CanSaveData();
            cannotSave |= !TheServer->IsConnected();
            if (cannotSave) {
                CancelLinkingCode();
                ShowState((OvershellSlotStateID)0x2D);
            }
        }
        if (mState->InCharEditFlow() && !localUser->CanSaveData()) {
            ShowState((OvershellSlotStateID)6);
        }
        if (mState->GetStateID() == 0x18 && !localUser->CanSaveData()) {
            ShowState((OvershellSlotStateID)6);
        }
        if (mState->GetStateID() == 0x33 && localUser->CanSaveData()) {
            ShowState((OvershellSlotStateID)6);
        }
        if (mState->GetStateID() == 0x10 && localUser->IsSignedInOnline()
            && !localUser->HasOnlinePrivilege()) {
            ShowState((OvershellSlotStateID)0x11);
        }
        if (mState->GetStateID() == 0x18) {
            if (mSessionMgr->IsLocal()) {
                if (!TheUIEventMgr->HasTransitionEvent("go_to_wiiprofilecreator"))
                    goto next17;
            }
            ShowState((OvershellSlotStateID)0x30);
        }
    next17:
        if (mState->GetStateID() == 0x17) {
            if (mSessionMgr->IsLocal()) {
                if (!TheUIEventMgr->HasTransitionEvent("go_to_wiiprofilecreator"))
                    goto next3b;
            }
            ShowState((OvershellSlotStateID)0x31);
        }
    next3b:
        if (mState->GetStateID() == 0x3B) {
            if (mSessionMgr->IsLocal()) {
                if (!TheUIEventMgr->HasTransitionEvent("go_to_wiiprofilecreator"))
                    goto nextc9;
            }
            ShowState((OvershellSlotStateID)0x3C);
        }
    nextc9:
        if (mState->GetStateID() == 0xC9) {
            if (mSessionMgr->IsLocal()) {
                if (!TheUIEventMgr->HasTransitionEvent("go_to_wiiprofilecreator"))
                    goto nextcc;
            }
            ShowState((OvershellSlotStateID)0xCD);
        }
    nextcc:
        if (mState->GetStateID() == 0xCC) {
            if (mSessionMgr->IsLocal()) {
                if (!TheUIEventMgr->HasTransitionEvent("go_to_wiiprofilecreator"))
                    goto next13;
            }
            ShowState((OvershellSlotStateID)0xCE);
        }
    next13:
        if (mState->GetStateID() == 0x13 && localUser->HasOnlinePrivilege()
            && !mBandUserMgr->AllLocalUsersInSessionAreGuests()) {
            ShowState((OvershellSlotStateID)0x14);
        }

        if (mState->GetStateID() == 0x36
            && mOvershell->DoesAnySlotHaveChar(mCharForEdit)) {
            ShowState((OvershellSlotStateID)0x42);
        }
        if (mState->GetStateID() == 0x1A && mSessionMgr->IsLocal()) {
            ShowState((OvershellSlotStateID)0x7);
        }
        BandUser *pCritUser = mSessionMgr->mCritUserListener->mCriticalUser;
        if (mState->GetStateID() == 0x41) {
            if (pCritUser != localUser) {
                LeaveOptions();
            }
        }
        if (mState->GetStateID() == 0xCB) {
            if (!TheProfileMgr.IsPrimaryProfileCritical(pUser->GetLocalUser())) {
                LeaveOptions();
            }
        }
        if (mState->GetStateID() == 0x37 && !localUser->CanSaveData()) {
            LeaveOptions();
        }
        if (mState->GetStateID() == 0x20) {
            LocalBandUser *swapUser = mState->Property("swap_user")->Obj<LocalBandUser>();
            if (!swapUser->IsSignedIn() || !swapUser->IsJoypadConnected()
                || swapUser->IsGuest()) {
                ShowState((OvershellSlotStateID)0x1F);
            }
        }
    }
}

UNPOOL_DATA
void OvershellSlot::UpdateView() {
    bool b1 = false;
    Symbol s2ac = mState ? mState->GetView() : gNullStr;
    Symbol s2b0 = s2ac;
    CheckViewOverride(block_all_input, BlockAllInput(), s2ac);
    CheckViewOverride(hidden, IsHidden(), s2ac);
    BandUser *user = GetUser();
    if (user && !user->IsLocal()) {
        if (AutoHideEnabled())
            s2ac = hidden;
        else if (mState->UsesRemoteStatusView()) {
            s2ac = remote_status;
        }
    }
    if (s2ac != gNullStr && s2ac != GetCurrentView()) {
        SetView(s2ac);
    }
    ControllerType c14 = kControllerNone;
    if (!unk40.empty()) {
        c14 = unk40[0];
    }
    if (c14 != kControllerNone) {
        if (user && user->IsParticipating()) {
            c14 = user->GetControllerType();
        } else if (!mPotentialUsers.empty()) {
            c14 = mPotentialUsers[0].mUser->ConnectedControllerType();
        }
        if (c14 != kControllerNone) {
            MetaPerformer *mp = MetaPerformer::Current();
            bool b17 = true;
            if (!InOverrideFlow(kOverrideFlow_SongSettings)
                && !mOvershell->SongOptionsRequired())
                b17 = false;
            const char *cc2;
            if (user && user->GetTrackType() != 10 && user->GetTrackType() != 11 && b17
                && TheContentMgr->RefreshDone()) {
                cc2 = GetUserFontChar(user, mp, 0);
            } else {
                cc2 = GetFontCharFromControllerType(c14, 0);
            }
            static Message msgUpdateControllerType("update_controller_type", c14, cc2);
            msgUpdateControllerType[0] = c14;
            msgUpdateControllerType[1] = cc2;
            mOvershellDir->HandleType(msgUpdateControllerType);
        }
    }
    bool b4e = true;
    int i18 = 0;
    bool b17 = false;
    if (!mState->ShowsExtendedMicArrows() && !mOvershell->GetUseExtendedMicArrows())
        b4e = false;
    GameMicManager *i4 = 0;
    bool b4f = c14 == 2;
    bool i2 = 0;
    bool i6 = 0;
    bool i16 = 0;
    if (user) {
        static Message updateNameMsg("update_user_name", 0);
        updateNameMsg[0] = user;
        mOvershellDir->HandleType(updateNameMsg);
        static Message updateLocalStatusMsg("update_local_status", 0);
        updateLocalStatusMsg[0] = user->IsLocal();
        mOvershellDir->HandleType(updateLocalStatusMsg);
        mSessionMgr->Disconnect();
        static Message updateRestartAllowedMsg("update_restart_allowed", 0);
        updateRestartAllowedMsg[0] = mSessionMgr->IsLocalToLeader(user);
        mOvershellDir->HandleType(updateRestartAllowedMsg);
        if (user->IsLocal()) {
            b17 = c14 == 2;
            LocalBandUser *l14 = user->GetLocalBandUser();
            int i7 = 0;
            if (l14->HasOnlinePrivilege()
                && !mBandUserMgr->AllLocalUsersInSessionAreGuests()) {
                i7 = 1;
            }
            static Message msgUpdateContinue("update_sign_in_continue", 0);
            msgUpdateContinue[0] = i7;
            mOvershellDir->HandleType(msgUpdateContinue);
            static Message updatePadNumMsg("update_pad_num", 0);
            updatePadNumMsg[0] = l14->GetPadNum() + 1;
            mOvershellDir->HandleType(updatePadNumMsg);
            UpdateProfilesList();
            i4 = TheGameMicManager;
            if (TheGameMicManager) {
                i2 = i4->HasMic(MicClientID(0, -1));
                i6 = i4->HasMic(MicClientID(1, -1));
                i16 = i4->HasMic(MicClientID(2, -1));
            }
            if (!l14->IsGuest() && l14->IsSignedIn()) {
                b1 = true;
            }
        } else {
            if (user->IsParticipating()) {
                i18 = 1;
                static Message updateRemoteFocus(
                    "update_remote_feedback", Symbol(user->GetOvershellFocus())
                );
                updateRemoteFocus[0] = Symbol(user->GetOvershellFocus());
                mState->HandleMsg(updateRemoteFocus);
                DataNode handled = Handle(get_remote_status_msg, false);
                DataArrayPtr ptr;
                if (handled.Type() != kDataUnhandled) {
                    ptr = handled.Array();
                } else {
                    if (TheSessionMgr && TheNetSync->IsEnabled()) {
                        if (mSessionMgr->GetLeaderUser() == user) {
                            ptr->Insert(0, remote_status_leader_controlling);
                        } else {
                            ptr->Insert(0, remote_status_waiting_on_leader);
                        }
                    } else {
                        ptr->Insert(0, mState->GetRemoteStatus());
                    }
                }
                static Message updateRemoteStatus("update_remote_status", ptr);
                updateRemoteStatus[0] = ptr;
                mOvershellDir->HandleType(updateRemoteStatus);
                i16 = 0;
                i6 = 0;
                i2 = 0;
            }
        }
        if (MetaPerformer::Current() && mOvershell->InSong() && !IsHidden()) {
            static Message updateShowVocalBg("update_show_vocal_bg", 0);
            updateShowVocalBg[0] = user->GetTrackType() == 3;
            mOvershellDir->HandleType(updateShowVocalBg);
        }
        if (GetState()->InSongSettingsFlow() && MetaPerformer::Current()) {
            static Message updateSongDifficultyRanking(6);
            updateSongDifficultyRanking.SetType("update_song_difficulty_ranking");
            int i9 = 0;
            bool b19 = false;
            int i15 = 0;
            int i8 = 0;
            Symbol s2b8(gNullStr);
            bool b20 = false;
            bool b21 = false;
            MetaPerformer *mp = MetaPerformer::Current();
            Symbol s2bc = user->GetControllerSym();
            bool b50 = mp->IsRandomSetList();
            TrackType tt = user->GetTrackType();
            if (tt - 10U < 3) {
                DataNode handled = mState->HandleMsg(get_focus_track_type_msg);
                if (handled.Type() != kDataUnhandled) {
                    tt = (TrackType)handled.Int();
                } else
                    tt = ControllerTypeToTrackType(user->GetControllerType(), false);
            } else {
                b20 = mp->IsNowUsingVocalHarmony();
                if (mp->IsUsingRealDrums())
                    b21 = true;
            }
            Symbol s2c0 = TrackTypeToSym(tt);
            if (tt - 10U > 2) {
                i9 = mp->PartPlaysInSet(s2c0);
                i15 = mp->GetHighestDifficultyForPart(s2c0);
                b19 = mp->GetSongs().size() > 1;
                if (s2bc == vocals) {
                    if (!b20) {
                        DataNode harmHandled =
                            mState->HandleMsg(get_focus_is_harmony_msg);
                        if (harmHandled.Type() != kDataUnhandled) {
                            b20 = harmHandled.Int();
                        }
                    }
                    if (b20) {
                        if (mp->GetSetlistMaxVocalParts() == 1) {
                            i9 = 0;
                        }
                        s2c0 = harmony;
                    } else
                        i8 = 1;
                } else if (s2bc == drum) {
                    DataNode drumsHandled = mState->HandleMsg(get_focus_is_prodrums_msg);
                    if (drumsHandled.Type() != kDataUnhandled) {
                        b21 = drumsHandled.Int();
                    }
                    if (b21) {
                        s2c0 = real_drum;
                    }
                }
            }
            updateSongDifficultyRanking[0] = b50;
            updateSongDifficultyRanking[1] = i9;
            updateSongDifficultyRanking[2] = b19;
            updateSongDifficultyRanking[3] = i15;
            updateSongDifficultyRanking[4] = i8;
            updateSongDifficultyRanking[5] = s2c0;
            mOvershellDir->HandleType(updateSongDifficultyRanking);
            static Message updateLeftyAndStaticToggle(
                "update_lefty_and_static_toggle", 0, 0
            );
            updateLeftyAndStaticToggle[0] = user->GetGameplayOptions();
            updateLeftyAndStaticToggle[1] = user->GetControllerType();
            mOvershellDir->HandleType(updateLeftyAndStaticToggle);
            if (mOvershell->GetMinimumDifficulty() != 0
                && (mOvershell->GetPartRestriction() == 10
                    || mOvershell->GetPartRestrictedUser() == user)) {
                static Message setDifficultyRestriction("set_difficulty_restriction", 0);
                setDifficultyRestriction[0] = mOvershell->GetMinimumDifficulty();
                mOvershellDir->HandleType(setDifficultyRestriction);
            } else {
                mOvershellDir->HandleType(clear_difficulty_restriction_msg);
            }
        }
    }
    if (b1) {
        HandleType(show_invitation_notification_msg);
    } else {
        HandleType(hide_invitation_notification_msg);
    }
    static Message msgUpdateMics("update_mics", i4, 0, 0, 0, 0, 0, 0);
    msgUpdateMics[0] = i4;
    msgUpdateMics[1] = b17;
    msgUpdateMics[2] = b4e;
    msgUpdateMics[3] = i2;
    msgUpdateMics[4] = i6;
    msgUpdateMics[5] = i16;
    msgUpdateMics[6] = b4f;
    mOvershellDir->HandleType(msgUpdateMics);

    static Message msgUpdateOnlineEnabled("update_online_enabled", 0);
    msgUpdateOnlineEnabled[0] = i18;
    mOvershellDir->HandleType(msgUpdateOnlineEnabled);

    if (mState && s2ac == s2b0) {
        mState->UpdateView();
    }
}
END_UNPOOL_DATA

void OvershellSlot::Update() {
    UpdateState();
    UpdateView();
}

void OvershellSlot::CheckViewOverride(Symbol s, bool b, Symbol &sref) {
    if (b)
        sref = s;
    else if (mCurrentView == s) {
        sref = mState->GetView();
    }
}

DataNode OvershellSlot::OnMsg(const AddLocalUserResultMsg &msg) {
    mSessionMgr->RemoveSink(this, AddLocalUserResultMsg::Type());
    if (!msg.Success())
        return 0;
    else {
        LocalBandUser *pUser = msg.GetBandUser()->GetLocalBandUser();
        MILO_ASSERT(pUser, 0xAB1);
        mBandUserMgr->SetSlot(pUser, mSlotNum);
        ClearPotentialUsers();
        mSongOptionsRequired = false;
        BandProfile *pf = TheProfileMgr.GetProfileForUser(pUser);
        if (pf)
            pf->DeleteAll();
        TheWiiProfileMgr.SetPadToGuest(pUser->GetPadNum());
        BandProfile *cpf = TheProfileMgr.GetProfileForUser(pUser);
        CharData *cdata = nullptr;
        if (cpf)
            cdata = cpf->GetLastCharUsed();
        if (cdata && mBandUserMgr->IsCharAvailable(cdata)) {
            pUser->SetChar(cdata);
        } else
            pUser->SetLoadedPrefabChar(mSlotNum);

        if (mOvershell->mSongOptionsRequired) {
            if (pUser->GetControllerType() == 2) {
                pUser->SetTrackType(kTrackPendingVocals);
            } else {
                pUser->SetTrackType(kTrackPending);
            }
            mSongOptionsRequired = true;
            BeginOverrideFlow(kOverrideFlow_SongSettings, true);
        } else {
            MILO_ASSERT(!InGame(), 0xAF4);
            pUser->SetOvershellSlotState(kState_ChooseProfile);
        }
        mOvershell->UpdateAll();
        static NewOvershellLocalUserMsg newUserMsg(pUser);
        newUserMsg[0] = pUser;
        mOvershell->Export(newUserMsg, true);
        return 0;
    }
}

DataNode OvershellSlot::OnMsg(const VirtualKeyboardResultMsg &msg) {
    return mState->HandleMsg(msg);
}

void OvershellSlot::ShowCharEdit(int i) {
    if (TheNetSync->GetUIState() == 0xF) {
        ShowState(kState_ChooseCharDenial);
    } else {
        mCharForEdit = dynamic_cast<TourCharLocal *>(mCharProvider->GetCharData(i));
        MILO_ASSERT(mCharForEdit != NULL, 0xB23);
        ShowState(kState_ChooseCharEdit);
    }
}

bool OvershellSlot::CanEditCharacter(int idx) const {
    if (mCharProvider->IsIndexCustomChar(idx)) {
        TourCharLocal *tcloc =
            dynamic_cast<TourCharLocal *>(mCharProvider->GetCharData(idx));
        BandUser *pUser = GetUser();
        MILO_ASSERT(pUser->IsLocal(), 0xB2E);
        BandProfile *profile = TheProfileMgr.GetProfileForUser(pUser->GetLocalBandUser());
        if (profile && profile->HasChar(tcloc)
            && !mOvershell->IsAnySlotEditingChar(tcloc))
            return true;
    }
    return false;
}

void OvershellSlot::DeleteCharacter() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0xB40);
    LocalBandUser *localUser = pUser->GetLocalBandUser();
    BandProfile *pProfile = TheProfileMgr.GetProfileForUser(localUser);
    if (TheNetSync->GetUIState() == 0xF) {
        ShowState(kState_ChooseCharDeleteDenial);
    } else if (!pProfile) {
        MILO_WARN("illegal attempt made to delete guest character\n");
    } else {
        MILO_ASSERT(pProfile, 0xB53);
        pProfile->DeleteChar(mCharForEdit);
        mCharForEdit = 0;
        mCharProvider->Reload(localUser);
    }
}

void OvershellSlot::AttemptShowCharDelete() {
    if (mOvershell->DoesAnySlotHaveChar(mCharForEdit)) {
        ShowState((OvershellSlotStateID)0x42);
    } else {
        ShowState((OvershellSlotStateID)0x36);
    }
}

void OvershellSlot::RenameCharacter(const char *cc) {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0xB6A);
    BandProfile *pProfile = TheProfileMgr.GetProfileForUser(pUser->GetLocalBandUser());
    if (TheNetSync->GetUIState() != 0xF) {
        if (!pProfile) {
            MILO_WARN("illegal attempt made to rename guest character to %s\n", cc);
        } else {
            MILO_ASSERT(pProfile, 0xB7C);
            pProfile->RenameCharacter(mCharForEdit, cc);
        }
    }
}

void OvershellSlot::SelectChar(int i1) {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0xB83);
    LocalBandUser *pLocalUser = pUser->GetLocalBandUser();
    MILO_ASSERT(pLocalUser, 0xB85);
    BandProfile *profile = TheProfileMgr.GetProfileForUser(pLocalUser);
    if (TheNetSync->GetUIState() == 0xF) {
        ShowState((OvershellSlotStateID)0x49);
    } else if (mCharProvider->IsIndexNewChar(i1)) {
        if (!mSessionMgr->IsLocal()) {
            ShowState((OvershellSlotStateID)0x49);
        } else if (!profile || !profile->HasValidSaveData()) {
            ShowState((OvershellSlotStateID)0x33);
        } else if (profile->NumChars() >= 10) {
            ShowEnterFlowPrompt((OvershellSlotStateID)0x34);
        } else
            ShowState((OvershellSlotStateID)0x18);
    } else if (mCharProvider->GetCharData(i1)) {
        pUser->SetChar(mCharProvider->GetCharData(i1));
        LeaveOptions();
    }
}

DataNode OvershellSlot::OnMsg(const ButtonDownMsg &msg) {
    BandUser *pUser = BandUserMgr::GetBandUser(msg.GetUser());
    MILO_ASSERT(pUser && pUser->IsLocal(), 0xBC1);
    LocalBandUser *lUser = pUser->GetLocalBandUser();
    const Message &btnMsg =
        GetState()->GetView() == join || GetState()->GetView() == finding
        ? button_pulse_unjoined_msg
        : button_pulse_joined_msg;

    if (!TheInputMgr->IsValidButtonForShell(msg.GetButton(), lUser)) {
        return 1;
    } else if (mBlockAllInput) {
        TheSynth->Play("button_error.cue", 0, 0, 0);
        return 0;
    } else {
        DataNode handled = mState->HandleMsg(msg);
        if (handled.Type() == kDataUnhandled) {
            if (msg.GetAction() == kAction_Cancel) {
                handled = mState->HandleMsg(on_cancel_msg);
                if (handled.Type() != kDataUnhandled) {
                    TheSynth->Play("overshell_back.cue", 0, 0, 0);
                }
            } else if (msg.GetAction() == kAction_Start) {
                static Message on_start("on_start", 0);
                on_start[0] = msg.GetUser();
                handled = mState->HandleMsg(on_start);
            } else if (msg.GetAction() == kAction_ViewModify) {
                handled = mState->HandleMsg(on_view_modify_msg);
            }
        }
        if (mOvershell->mAllowsButtonPulse) {
            mOvershellDir->HandleType(btnMsg);
        }
        if (mState->AllowsInputToShell() && handled.Type() == kDataUnhandled) {
            return DataNode(kDataUnhandled, 0);
        } else if (handled.Type() == kDataUnhandled) {
            mOvershellDir->Handle(msg, false);
        }
        return 0;
    }
}

DataNode OvershellSlot::OnMsg(const ButtonUpMsg &msg) {
    if (mBlockAllInput)
        return 0;
    else if (mState->AllowsInputToShell())
        return DataNode(kDataUnhandled, 0);
    else {
        mOvershellDir->Handle(msg, false);
        return 0;
    }
}

void OvershellSlot::AddUser(LocalBandUser *user) {
    JoinState state;
    if (LookupUserInJoinList(user, &state) && state == kMetaJoinOK) {
        mSessionMgr->AddSink(this, AddLocalUserResultMsg::Type());
        mSessionMgr->AddLocalUser(user);
        mOvershell->UpdateAll();
    } else {
        MILO_FAIL("Local user %s cannot join", user->UserName());
    }
}

DataNode OvershellSlot::OnMsg(const UIComponentScrollMsg &msg) {
    BandUser *pUser = GetUser();
    UIList *list = nullptr;
    if (pUser && pUser->IsLocal()) {
        list = dynamic_cast<UIList *>(msg.GetUIComponent());
        if (list) {
            pUser->GetLocalBandUser()->SetOvershellFocus(list->SelectedSym(false).mStr);
        }
    }
    mState->HandleMsg(msg);
    if (pUser && pUser->IsLocal()) {
        if (list) {
            DataArrayPtr ptr("play_instr_sfx_local", pUser, button_toggle);
            ptr->Execute();
        } else
            TheSynth->Play("slider.cue", 0, 0, 0);
    }
    if (list) {
        Handle(print_haq_focus_status_msg, true);
    }
    return 1;
}

DataNode OvershellSlot::OnMsg(const UIComponentSelectMsg &msg) {
    if (mState->HandleMsg(msg) != DataNode(kDataUnhandled, 0)) {
        TheSynth->Play("overshell_select.cue", 0, 0, 0);
    }
    return 1;
}

int OvershellSlot::GetDefaultCharIndex() const {
    MILO_ASSERT(mCharProvider, 0xC64);
    return mCharProvider->GetDefaultCharIndex();
}

void OvershellSlot::UpdateCharacterList() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0xC6C);
    LocalBandUser *pLocalUser = pUser->GetLocalBandUser();
    MILO_ASSERT(pLocalUser, 0xC6F);
    TheProfileMgr.GetProfileForUser(pLocalUser);
    mCharProvider->Reload(pLocalUser);
    static Message updateCharListMsg("update_char_provider", 0);
    updateCharListMsg[0] = mCharProvider;
    mOvershellDir->HandleType(updateCharListMsg);
}

void OvershellSlot::UpdateMuteUsersList() {
    BandUser *pUser = GetUser();
    mMuteUsersProvider->RefreshUserList(pUser, mBandUserMgr);
    static Message updateMuteUsersMsg("update_users_provider", 0);
    updateMuteUsersMsg[0] = mMuteUsersProvider;
    mOvershellDir->HandleType(updateMuteUsersMsg);
}

void OvershellSlot::UpdateKickUsersList() {
    BandUser *pUser = GetUser();
    mKickUsersProvider->RefreshUserList(pUser, mBandUserMgr);
    static Message updateKickUsersMsg("update_users_provider", 0);
    updateKickUsersMsg[0] = mKickUsersProvider;
    mOvershellDir->HandleType(updateKickUsersMsg);
}

void OvershellSlot::UpdateProfilesList() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser->IsLocal(), 0xC97);
    mSwappableProfilesProvider->Reload(pUser->GetLocalBandUser());
    static Message updateProfilesMsg("update_profiles_provider", 0);
    updateProfilesMsg[0] = mSwappableProfilesProvider;
    mOvershellDir->HandleType(updateProfilesMsg);
}

void OvershellSlot::UpdatePartSelectList() {
    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser, 0xCB0);
    ControllerType ty = pUser->GetControllerType();
    mPartSelectProvider->Reload(ty, pUser);
    static Message updatePartSelectMsg("update_part_select_provider", 0, 0);
    updatePartSelectMsg[0] = mPartSelectProvider;
    updatePartSelectMsg[1] = ty;
    mOvershellDir->HandleType(updatePartSelectMsg);
}

#pragma push
#pragma pool_data off
void OvershellSlot::RefreshHighlightedChar(int i1) {
    static Message updatePortraitMsg("update_character_portrait", 0);
    CharData *data = mCharProvider->GetCharData(i1);
    if (data)
        updatePortraitMsg[0] = data->GetPortraitTex();
    else
        updatePortraitMsg[0] = 0;
    mOvershellDir->HandleType(updatePortraitMsg);

    BandUser *pUser = GetUser();
    MILO_ASSERT(pUser, 0xCC8);
    MILO_ASSERT(pUser->IsLocal(), 0xCC9);
    static Message updateMoreOptionsMsg("update_char_more_options", 0, pUser);
    updateMoreOptionsMsg[0] = CanEditCharacter(i1);
    updateMoreOptionsMsg[1] = pUser;
    mOvershellDir->HandleType(updateMoreOptionsMsg);
}
#pragma pop

void OvershellSlot::ShowEnterFlowPrompt(OvershellSlotStateID id) {
    OvershellSlotStateID outputID = (OvershellSlotStateID)0x30;
    switch (id) {
    case 0x18:
        outputID = (OvershellSlotStateID)0x30;
        break;
    case 0x17:
        outputID = (OvershellSlotStateID)0x31;
        break;
    case 0x3B:
        outputID = (OvershellSlotStateID)0x3C;
        break;
    default:
        MILO_FAIL("slot state %i is not an Enter Flow Prompt\n", id);
        break;
    }
    if (mSessionMgr->IsLocal()) {
        outputID = id;
    }
    ShowState(outputID);
}

DataNode OvershellSlot::OnMsg(const UserLoginMsg &msg) {
    if (unk80 && !unk81) {
        User *pUser = GetUser();
        if (pUser && pUser->IsLocal()) {
            if (pUser->GetLocalUser()->GetPadNum() == msg.GetPadNum()) {
                TheRockCentral.GetLinkingCode(
                    msg.GetPadNum(), mLinkingCodeResultList, this
                );
                unk80 = false;
                unk81 = true;
            }
        }
    }
    return 1;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(OvershellSlot)
    HANDLE_EXPR(get_user, GetUser())
    HANDLE_EXPR(in_game, InGame())
    HANDLE_EXPR(in_song, mOvershell->InSong())
    HANDLE_MESSAGE(AddLocalUserResultMsg)
    HANDLE_MESSAGE(LocalUserLeftMsg)
    HANDLE_EXPR(get_current_view, GetCurrentView())
    HANDLE_EXPR(get_slot_num, GetSlotNum())
    HANDLE_EXPR(get_state, mState)
    HANDLE_EXPR(get_session_mgr, mSessionMgr)
    HANDLE_ACTION(update, Update())
    HANDLE_ACTION(leave_options, LeaveOptions())
    HANDLE_ACTION(show_state, ShowState((OvershellSlotStateID)_msg->Int(2)))
    HANDLE_ACTION(show_chars, ShowState(kState_ChooseChar))
    HANDLE_ACTION(show_profiles, ShowProfiles())
    HANDLE_ACTION(show_options, ShowState(kState_Options))
    HANDLE_ACTION(show_online_options, ShowOnlineOptions())
    HANDLE_ACTION(attempt_register_online, AttemptRegisterOnline())
    HANDLE_ACTION(show_game_options, ShowState(kState_GameOptions))
    HANDLE_ACTION(show_options_av_settings, ShowState(kState_OptionsAVSettings))
    HANDLE_ACTION(show_options_audio, ShowState(kState_OptionsAudio))
    HANDLE_ACTION(show_options_vocal, ShowState(kState_OptionsVocal))
    HANDLE_ACTION(show_options_wiispeak, ShowState(kState_OptionsWiiSpeak))
    HANDLE_ACTION(show_options_extras, ShowState(kState_OptionsExtras))
    HANDLE_ACTION(show_options_drum, ShowOptionsDrum())
    HANDLE_ACTION(show_saveloadmgr_not_idle, ShowState(kState_SaveloadManagerNotIdle))
    HANDLE_ACTION(show_saveloadmgr_not_meta, ShowState(kState_SaveloadManagerNotMeta))
    HANDLE_ACTION(
        show_saveloadmgr_autosave_confirm,
        ShowState(kState_SaveloadManagerAutosaveConfirm)
    )
    HANDLE_ACTION(show_options_end_game, ShowState(kState_OptionsEndGame))
    HANDLE_ACTION(show_linking_code, ShowState(kState_LinkingCode))
    HANDLE_ACTION(show_linking_code_error, ShowState(kState_LinkingCodeError))
    HANDLE_ACTION(fetch_linking_code, FetchLinkingCode())
    HANDLE_ACTION(cancel_linking_code, CancelLinkingCode())
    HANDLE_ACTION(show_char_edit, ShowCharEdit(_msg->Int(2)))
    HANDLE_ACTION(attempt_show_char_delete, AttemptShowCharDelete())
    HANDLE_ACTION(remove_user, RemoveUser())
    HANDLE_ACTION(show_song_options, ShowSongOptions())
    HANDLE_ACTION(select_part, SelectPart((TrackType)_msg->Int(2)))
    HANDLE_ACTION(select_vocal_part, SelectVocalPart(_msg->Int(2)))
    HANDLE_ACTION(select_drum_part, SelectDrumPart(_msg->Int(2)))
    HANDLE_ACTION(show_choose_part_wait, ShowChoosePartWait())
    HANDLE_ACTION(toggle_hihat_pedal, ToggleHiHatPedal())
    HANDLE_ACTION(toggle_cymbal, ToggleCymbal(_msg->Sym(2)))
    HANDLE_ACTION(finish_cymbal_selection, FinishCymbalSelect(_msg->Int(2)))
    HANDLE_ACTION(dismiss_cymbal_message, DismissCymbalMessage())
    HANDLE_ACTION(select_difficulty, SelectDifficulty((Difficulty)_msg->Int(2)))
    HANDLE_ACTION(leave_choose_part, LeaveChoosePart())
    HANDLE_ACTION(leave_choose_part_wait, LeaveChoosePartWait())
    HANDLE_ACTION(leave_choose_difficulty, LeaveChooseDifficulty())
    HANDLE_ACTION(leave_ready_to_play, LeaveReadyToPlay())
    HANDLE_ACTION(leave_char_delete, ShowState(kState_ChooseCharEdit))
    HANDLE_ACTION(show_sign_in_wait, ShowState(kState_SignInWait))
    HANDLE_ACTION(leave_sign_in_wait, LeaveSignInWait())
    HANDLE_ACTION(refresh_highlighted_char, RefreshHighlightedChar(_msg->Int(2)))
    HANDLE_ACTION(update_character_list, UpdateCharacterList())
    HANDLE_EXPR(get_default_char_index, GetDefaultCharIndex())
    HANDLE_ACTION(select_char, SelectChar(_msg->Int(2)))
    HANDLE_ACTION(
        begin_override_flow, BeginOverrideFlow((OvershellOverrideFlow)_msg->Int(2), true)
    )
    HANDLE_ACTION(
        end_override_flow, EndOverrideFlow((OvershellOverrideFlow)_msg->Int(2), true)
    )
    HANDLE_ACTION(show_enter_calibration, ShowEnterFlowPrompt(kState_EnterCalibration))
    HANDLE_ACTION(show_enter_credits, ShowEnterFlowPrompt(kState_EnterCredits))
    HANDLE_ACTION(show_enter_wiispeak_options, ShowEnterWiiSpeakOptions())
    HANDLE_ACTION(attempt_disconnect, AttemptDisconnect())
    HANDLE_ACTION(attempt_remove_user, AttemptRemoveUser())
    HANDLE_ACTION(show_kick_users, ShowState(kState_KickUsers))
    HANDLE_ACTION(kick_user, KickUser(_msg->Int(2)))
    HANDLE_ACTION(show_mute_users, ShowState(kState_MuteUsers))
    HANDLE_ACTION(toggle_mute_user, ToggleMuteUser(_msg->Int(2)))
    HANDLE_ACTION(show_gamercard_users, ShowState(kState_GamercardUsers))
    HANDLE_ACTION(toggle_vocal_style, ToggleVocalStyle())
    HANDLE_ACTION(toggle_lefty_flip, ToggleLeftyFlip())
    HANDLE_EXPR(get_char_provider, mCharProvider)
    HANDLE_EXPR(get_profiles_provider, mSwappableProfilesProvider)
    HANDLE_EXPR(confirm_swap_user_profile, ConfirmSwapUserProfile())
    HANDLE_ACTION(select_guest_profile, SelectGuestProfile())
    HANDLE_ACTION(show_modifiers, ShowState(kState_Modifiers))
    HANDLE_ACTION(show_modifiers_drum_warning, ShowState(kState_ModifiersDrumWarning))
    HANDLE_ACTION(show_modifier_unlock, ShowState(kState_ModifierUnlock))
    HANDLE_ACTION(show_modifier_delayed_effect, ShowState(kState_ModifierDelayedEffect))
    HANDLE_ACTION(show_toggle_no_fail_denial, ShowState(kState_ToggleNoFailDenial))
    HANDLE_EXPR(is_unlocking_modifiers, GetState()->GetStateID() == kState_ModifierUnlock)
    HANDLE_ACTION(attempt_toggle_auto_vocals, AttemptToggleAutoVocals())
    HANDLE_ACTION(update_part_select_list, UpdatePartSelectList())
    HANDLE_EXPR(is_cymbal_selected, IsCymbalSelected(_msg->Sym(2)))
    HANDLE_ACTION(confirm_choose_diff, ConfirmChooseDiff())
    HANDLE_ACTION(leave_difficulty_confirmation, LeaveDifficultyConfirmation())
    HANDLE_ACTION(confirm_kick, ConfirmKick())
    HANDLE_ACTION(leave_kick_confirmation, LeaveKickConfirmation())
    HANDLE_EXPR(is_in_track_mode, mOvershellDir->Property("in_track_mode", true)->Int())
    HANDLE_ACTION(reset_slot_cam, ResetSlotCamera())
    HANDLE_ACTION(show_chord_book, ShowChordBook())
    HANDLE_ACTION(practice_new_section, PracticeNewSection())
    HANDLE_ACTION(toggle_metronome, ToggleMetronome())
    HANDLE_EXPR(character_name, mCharForEdit ? mCharForEdit->GetCharacterName() : 0)
    HANDLE_ACTION(rename_character, RenameCharacter(_msg->Str(2)))
    HANDLE_ACTION(delete_character, DeleteCharacter())
    HANDLE_ACTION(refresh_cymbal_provider, mCymbalProvider->ReloadData())
    HANDLE_EXPR(can_edit_character, CanEditCharacter(_msg->Int(2)))
    HANDLE_EXPR(is_quit_token, IsQuitToken(_msg->Sym(2)))
    HANDLE_ACTION(update_mute_users_list, UpdateMuteUsersList())
    HANDLE_ACTION(update_kick_users_list, UpdateKickUsersList())
    HANDLE_ACTION(set_wiiprofile_list_mode, SetWiiProfileListMode(_msg->Int(2), false))
    HANDLE_EXPR(get_wiiprofile_list_mode, GetWiiProfileListMode())
    HANDLE_EXPR(get_wiiprofile_last_index, GetWiiProfileLastIndex())
    HANDLE_EXPR(is_wiiprofile_full, IsWiiProfileFull())
    HANDLE_EXPR(is_wiiprofile_delete_queue_full, IsWiiProfileDeleteQueueFull())
    HANDLE_EXPR(get_wiiprofile_list_selected_name, GetWiiProfileListSelectedName())
    HANDLE_ACTION(show_wiiprofile_list, ShowWiiProfileList(_msg->Int(2)))
    HANDLE_ACTION(act_on_user_profile, ActOnUserProfile(_msg->Int(2)))
    HANDLE_ACTION(act_on_user_profile_confirm, ActOnUserProfileConfirm())
    HANDLE_ACTION(show_enter_wiiprofile, ShowEnterWiiProfile())
    HANDLE_ACTION(show_register_wiiprofile, ShowEnterWiiProfile())
    HANDLE_ACTION(show_switch_wiiprofile, ShowEnterWiiProfile())
    HANDLE_ACTION(show_create_wiiprofile, ShowEnterWiiProfile())
    HANDLE_ACTION(show_delete_wiiprofile, ShowEnterWiiProfile())
    HANDLE_EXPR(get_user_wiiprofile, GetUserWiiProfile())
    HANDLE_ACTION(toggle_wii_speak, ToggleWiiSpeak())
    HANDLE_ACTION(show_wiiprofile_confirm, ShowWiiProfileConfirm())
    HANDLE_ACTION(show_wiiprofile_options, ShowWiiProfileOptions())
    HANDLE_ACTION(show_wiiprofile_fail, ShowWiiProfileFail())
    HANDLE_ACTION(show_wiiprofile_fail_busy, ShowWiiProfileFailBusy())
    HANDLE_ACTION(show_wiiprofile_swap_fail, ShowWiiProfileSwapFail())
    HANDLE_ACTION(show_wait_wii, ShowWaitWii())
    HANDLE_ACTION(leave_wait_wii, LeaveWaitWii())
    HANDLE_ACTION(show_choose_invitation, ShowState(kState_ChooseInvitation))
    HANDLE_ACTION(show_accept_invitation, ShowState(kState_AcceptInvitation))
    HANDLE_ACTION(show_no_invitations, ShowState(kState_NoInvitations))
    HANDLE_ACTION(show_wii_profile_selector, ShowWiiProfileSelector(false))
    HANDLE_ACTION(cancel_wii_profile_selector, CancelWiiProfileSelector())
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_MESSAGE(UIComponentScrollMsg)
    HANDLE_MESSAGE(UIComponentSelectMsg)
    HANDLE_MESSAGE(VirtualKeyboardResultMsg)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_MESSAGE(UserLoginMsg)
    HANDLE_MEMBER_PTR(mOvershellDir)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xE4D)
END_HANDLERS
#pragma pop
