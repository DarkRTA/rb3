#include "meta_band/OvershellSlot.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/PassiveMessage.h"
#include "meta_band/SessionUsersProviders.h"
#include "meta_band/CharProvider.h"
#include "meta_band/OvershellPartSelectProvider.h"
#include "meta_band/CymbalSelectionProvider.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/ProfileMgr.h"
#include "game/GameMode.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

OvershellSlot::OvershellSlot(int i, OvershellPanel* panel, OvershellDir* dir, BandUserMgr* umgr, SessionMgr* smgr) : mStateMgr(new OvershellSlotStateMgr()), mState(0),
    mOverrideFlowReturnState(kState_JoinedDefault), unk28(0x82),
    mOvershell(panel), mBandUserMgr(umgr), mSessionMgr(smgr), mSlotNum(i), mOvershellDir(dir), mAutohideEnabled(0), mIsLeavingOptions(0), mCurrentView(gNullStr), mBlockAllInput(0), mInGame(0),
    mSongOptionsRequired(0), unk80(0), unk81(0), mCharForEdit(0), mCymbalConfiguration(0), mSlotOverrideFlow(kOverrideFlow_None) {
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
}

OvershellSlot::~OvershellSlot(){
    mSessionMgr->RemoveSink(this, LocalUserLeftMsg::Type());
    RELEASE(mSwappableProfilesProvider);
    RELEASE(mCharProvider);
    RELEASE(mMuteUsersProvider);
    RELEASE(mKickUsersProvider);
    RELEASE(mMessageQueue);
    RELEASE(mStateMgr);
    RELEASE(mPartSelectProvider);
    RELEASE(mCymbalProvider);
}

ObjectDir* OvershellSlot::DataDir(){ return mOvershellDir; }

void OvershellSlot::SetTypeDef(DataArray* da){
    if(TypeDef() != da){
        Hmx::Object::SetTypeDef(da);
        mStateMgr->Init(da->FindArray(state_handlers, true), this);
        float dur = 0;
        if(da->FindData(msg_duration, dur, false)){
            mMessageQueue->SetMessageDuration(dur);
        }
    }
}

void OvershellSlot::Enter(){
    Hmx::Object::Handle(enter_msg, false);
}

void OvershellSlot::Poll(){
    mMessageQueue->Poll();
    mIsLeavingOptions = false;
}

int OvershellSlot::GetSlotNum(){ return mSlotNum; }
PanelDir* OvershellSlot::GetPanelDir(){ return mOvershellDir; }

bool OvershellSlot::IsHidden() const {
    return mAutohideEnabled && mState->AllowsHiding();
}

bool OvershellSlot::IsLeavingOptions() const { return mIsLeavingOptions; }
Symbol OvershellSlot::GetCurrentView() const { return mCurrentView; }

void OvershellSlot::ClearPotentialUsers(){
    mPotentialUsers.clear();
}

void OvershellSlot::AddPotentialUser(PotentialUserEntry e){
    mPotentialUsers.push_back(e);
}

int OvershellSlot::NumPotentialUsers() const { return mPotentialUsers.size(); }

bool OvershellSlot::LookupUserInJoinList(const LocalBandUser* user, JoinState* state){
    if(user){
        for(std::vector<PotentialUserEntry>::iterator it = mPotentialUsers.begin(); it != mPotentialUsers.end(); ++it){
            if(it->mUser == user){
                *state = it->mJoinState;
                return true;
            }
        }
    }
    return false;
}

bool OvershellSlot::IsValidControllerType(ControllerType ty){
    std::vector<ControllerType>& vec = TheModifierMgr && TheModifierMgr->IsModifierActive(mod_auto_vocals) ? unk48 : unk40;
    for(int i = 0; i < vec.size(); i++){
        if(ty == vec[i]) return true;
    }
    return false;
}

inline BandUser* OvershellSlot::GetUser() const {
    return mBandUserMgr->GetUserFromSlot(mSlotNum);
}

OvershellSlotState* OvershellSlot::GetState(){
    MILO_ASSERT(mState, 0x1B2);
    return mState;
}

void OvershellSlot::GenerateCurrentState(){
    OvershellSlotStateID id = kState_NoInstrument;
    BandUser* user = mBandUserMgr->GetUserFromSlot(mSlotNum);
    if(user) id = user->mOvershellState;
    else {
        if(mOvershell->IsFinding()) id = kState_Finding;
        else {
            if(mPotentialUsers.empty()) id = kState_NoInstrument;
            else {
                JoinState jstate = mPotentialUsers[0].mJoinState;
                switch(jstate){
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
    mStateMgr->GetSlotState(id);
}

void OvershellSlot::RemoveUser(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser, 0x1E5);
    LocalBandUser* pLocUser = pUser->GetLocalBandUser();
    MILO_ASSERT(pLocUser, 0x1E7);
}

void OvershellSlot::ShowState(OvershellSlotStateID id){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x21B);
    if(id == kState_CalibrationDenial){
        UILabel* lbl = mOvershellDir->Find<UILabel>("reconnect_controller.lbl", false);
        if(lbl){
            static Symbol overshell_reconnect_controller("overshell_reconnect_controller");
            static Symbol wii_error_remote_extension_x("wii_error_remote_extension_x");
        }
    }
    pUser->SetOvershellSlotState(id);
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveOptions(){
    ShowState(kState_JoinedDefault);
    mIsLeavingOptions = true;
}

void OvershellSlot::ShowSongOptions(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x2DA);
    BandUser* user = mSessionMgr->GetLocalHost(); // wrong
    if(mInGame && !mSongOptionsRequired){
        pUser->SetOvershellSlotState(kState_ChooseDiff);
    }
    else {
        if(user && user != pUser){
            pUser->SetTrackType(kTrackNone);
            pUser->SetOvershellSlotState(kState_ReadyToPlay);
        }
        else {
            if(TheGameMode->Property("skip_choose_part", true)->Int(0)){
                int part = TheGameMode->Property("forced_part", true)->Int(0);
                if(part == kTrackNone){
                    part = ControllerTypeToTrackType(pUser->GetControllerType(), false);
                }
                pUser->SetTrackType((TrackType)part);
                pUser->SetOvershellSlotState(kState_ChooseDiff);
            }
            else pUser->SetOvershellSlotState(kState_ChoosePart);
        } 
    }
    mOvershell->UpdateAll();
}

bool OvershellSlot::InGame() const { return mInGame; }

void OvershellSlot::SelectPart(TrackType trackType){
    MILO_ASSERT(trackType != kTrackVocals, 0x2FD);
    MILO_ASSERT(trackType != kTrackDrum, 0x2FE);
    SelectPartImpl(trackType, false, false);
}

void OvershellSlot::SelectVocalPart(bool b){
    SelectPartImpl(kTrackVocals, b, false);
}

void OvershellSlot::SelectDrumPart(bool b){
    SelectPartImpl(kTrackDrum, false, b);
}

void OvershellSlot::SelectPartImpl(TrackType track, bool harmony, bool proDrums){
    MILO_ASSERT(track == kTrackVocals || !harmony, 0x30E);
    MILO_ASSERT(track == kTrackDrum || !proDrums, 0x30F);
}

void OvershellSlot::ToggleCymbal(Symbol s){
    unsigned int cymBit = 0;
    if(s == overshell_yellow_cym) cymBit = 4;
    else if(s == overshell_blue_cym) cymBit = 8;
    else if(s == overshell_green_cym) cymBit = 0x10;
    MILO_ASSERT(cymBit != 0, 0x391);
    mCymbalConfiguration ^= cymBit;
}

bool OvershellSlot::IsCymbalSelected(Symbol s){
    if(s == overshell_yellow_cym && (mCymbalConfiguration & 4)) return true;
    else if(s == overshell_blue_cym && (mCymbalConfiguration & 8)) return true;
    else if(s == overshell_green_cym && (mCymbalConfiguration & 0x10)) return true;
    else return false;
}

void OvershellSlot::FinishCymbalSelect(bool b){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x3A8);
    if(b){
        if(InOverrideFlow(kOverrideFlow_SongSettings))
            pUser->SetOvershellSlotState(kState_ChoosePart);
    }
    else {
        TheProfileMgr.SetCymbalConfiguration(mCymbalConfiguration);
        if(InOverrideFlow(kOverrideFlow_SongSettings))
            pUser->SetOvershellSlotState(kState_OptionsDrumMessage);
    }
    if(!InOverrideFlow(kOverrideFlow_SongSettings))
        pUser->SetOvershellSlotState(kState_GameOptions);
    mOvershell->UpdateAll();
}

void OvershellSlot::DismissCymbalMessage(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x3BF);
    pUser->SetOvershellSlotState(kState_ChooseDiff);
    mOvershell->UpdateAll();
}

void OvershellSlot::SelectDifficulty(Difficulty diff){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser, 0x3C7);
    MILO_ASSERT(pUser->IsLocal(), 0x3C8);
    bool old5e = mSongOptionsRequired;
    mSongOptionsRequired = 0;
    if(mOvershell->unk88){
        if(!old5e && mOvershell->InSong()){
            if(!TheGameMode->Property("skip_choose_diff_prompt", true)->Int(0)){
                Difficulty pUserDiff = pUser->GetDifficulty();
                if(diff == pUserDiff) CancelSongSettings();
                else {
                    mStateMgr->GetSlotState(kState_ChooseDiffConfirm)->SetProperty("difficulty", diff);
                    pUser->SetOvershellSlotState(kState_ChooseDiffConfirm);
                }
            }
            goto lol;
        }
        pUser->SetDifficulty(diff);
        EndOverrideFlow(kOverrideFlow_SongSettings, true);
    }
    else {
        pUser->SetDifficulty(diff);
        pUser->SetOvershellSlotState(kState_ReadyToPlay);
    }
lol:
    MILO_ASSERT(pUser->GetTrackType() != kTrackNone, 0x3E5);
    if(old5e){
        if(mInGame){
            static Message chosenMsg("required_song_options_chosen", 0);
            chosenMsg[0] = pUser;
            mOvershell->Export(chosenMsg, true);
        }
    }
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveDifficultyConfirmation(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x403);
    pUser->SetOvershellSlotState(kState_ChooseDiff);
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveChoosePart(){
    CancelSongSettings();
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveChoosePartWait(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x411);
    pUser->SetTrackType(kTrackNone);
    pUser->SetOvershellSlotState(kState_ChoosePart);
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveChooseDifficulty(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x41A);
    if(!TheGameMode->Property("skip_choose_part", true)->Int(0) && (!mInGame || mSongOptionsRequired)){
        pUser->SetTrackType(kTrackNone);
        pUser->SetOvershellSlotState(kState_ChoosePart);
    }
    else CancelSongSettings();
    mOvershell->UpdateAll();
}

void OvershellSlot::CancelSongSettings(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x42E);
    if(!mOvershell->unk88){
        if(mBandUserMgr->GetNumParticipants() < 2){
            mOvershell->EndOverrideFlow(kOverrideFlow_SongSettings, true);
        }
        else ShowState(kState_SongOptionsCancel);
    }
    else if(!mSongOptionsRequired){
        SetOverrideFlowReturnState(kState_Options);
        EndOverrideFlow(kOverrideFlow_SongSettings, true);
    }
    else AttemptRemoveUser();
}

void OvershellSlot::LeaveReadyToPlay(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x44C);
}

void OvershellSlot::LeaveSignInWait(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x45E);
    pUser->SetOvershellSlotState((OvershellSlotStateID)0x46); // missing enum whoa
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowEnterWiiSpeakOptions(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x466);
    pUser->SetOvershellSlotState(kState_EnterWiiSpeakOptions);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowEnterWiiProfile(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x46E);
    if(mSessionMgr->IsLocal()){
        pUser->SetOvershellSlotState(kState_EnterWiiProfile);
    }
    else pUser->SetOvershellSlotState((OvershellSlotStateID)0xCD); // missing enum whoa
    mOvershell->UpdateAll();
}

void OvershellSlot::AttemptDisconnect(){
    if(mSessionMgr->IsLocal()){
        mSessionMgr->Disconnect();
    }
    else {
        BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
        MILO_ASSERT(pUser->IsLocal(), 0x48C);
        pUser->SetOvershellSlotState(kState_DisconnectConfirm);
        mOvershell->UpdateAll();
    }
}

void OvershellSlot::ShowChordBook(){
    LeaveOptions();
    mOvershell->UpdateAll();
}

void OvershellSlot::PracticeNewSection(){ mOvershell->UpdateAll(); }
void OvershellSlot::ToggleMetronome(){ mOvershell->UpdateAll(); }

void OvershellSlot::KickUser(int i){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x4FB);
    OvershellSlotState* ostate = mStateMgr->GetSlotState(kState_KickConfirmation);
    ostate->SetProperty("kick_user", mKickUsersProvider->GetUser(i));
    pUser->SetOvershellSlotState(kState_KickConfirmation);
    mOvershell->UpdateAll();
}

void OvershellSlot::ConfirmKick(){
    BandUser* pUserToKick = mState->Property("kick_user", true)->Obj<BandUser>(0);
    MILO_ASSERT(pUserToKick != NULL, 0x505);
    mKickUsersProvider->KickPlayer(pUserToKick);
    LeaveKickConfirmation();
}

void OvershellSlot::LeaveKickConfirmation(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x50D);
    pUser->SetOvershellSlotState(kState_KickUsers);
    mOvershell->UpdateAll();
}

void OvershellSlot::ToggleMuteUser(int i){
    mMuteUsersProvider->ToggleMuteStatus(i);
    mOvershell->UpdateAll();
}

void OvershellSlot::ActOnUserProfile(int i){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x52B);
    HandleWiiProfileActResult(mSwappableProfilesProvider->ActOnProfile(i, pUser->GetLocalBandUser(), false));
}

void OvershellSlot::ActOnUserProfileConfirm(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x534);
    HandleWiiProfileActResult(mSwappableProfilesProvider->ActOnProfileConfirmed(pUser->GetLocalBandUser()));
}

void OvershellSlot::HandleWiiProfileActResult(WiiProfileActResult res){
    switch(res){
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
        case 5:
            BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
            MILO_ASSERT(pUser->IsLocal(), 0x54C);
            if(mSessionMgr->IsLocal()){
                pUser->SetOvershellSlotState((OvershellSlotStateID)0xcc);
            }
            else pUser->SetOvershellSlotState((OvershellSlotStateID)0xce);
            mOvershell->UpdateAll();
            break;
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

void OvershellSlot::SelectGuestProfile(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x594);
    LocalBandUser* pLocUser = pUser->GetLocalBandUser();
    MILO_ASSERT(pLocUser, 0x596);
}

void OvershellSlot::ShowWiiProfileConfirm(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x5AD);
    pUser->SetOvershellSlotState(kState_WiiProfileConfirm);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfilePreconfirm(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x5B5);
    pUser->SetOvershellSlotState((OvershellSlotStateID)0x8F);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileSwitchConfirm(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x5BD);
    pUser->SetOvershellSlotState((OvershellSlotStateID)0x90);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileFail(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x5C5);
    pUser->SetOvershellSlotState(kState_WiiProfileFail);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileFailBusy(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x5CD);
    pUser->SetOvershellSlotState((OvershellSlotStateID)0x88);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileFailCreate(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x5D5);
    pUser->SetOvershellSlotState((OvershellSlotStateID)0x89);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileSwapFail(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x5DD);
    pUser->SetOvershellSlotState((OvershellSlotStateID)0x8A);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfilePostAction(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x5E5);
    pUser->SetOvershellSlotState((OvershellSlotStateID)0x91);
    mOvershell->UpdateAll();
}

void OvershellSlot::SetWiiProfileListMode(int i, bool b){
    if(i != 0x10) mSwappableProfilesProvider->SetWiiProfileListMode((OvershellProfileProvider::WiiProfileListMode)i, b);
}

OvershellProfileProvider::WiiProfileListMode OvershellSlot::GetWiiProfileListMode(){
    return mSwappableProfilesProvider->GetWiiProfileListMode();
}

int OvershellSlot::GetWiiProfileLastIndex(){
    return mSwappableProfilesProvider->unk24;
}

void OvershellSlot::ShowWiiProfileList(int i){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x60E);
    SetWiiProfileListMode(i, false);
    if(i == 0 || i == 2){
        pUser->SetOvershellSlotState((OvershellSlotStateID)0xC9);
    }
    else {
        if(mSwappableProfilesProvider->GetWiiProfileCount(pUser->GetLocalBandUser()) <= 0){
            pUser->SetOvershellSlotState((OvershellSlotStateID)0x86);
        }
        else pUser->SetOvershellSlotState((OvershellSlotStateID)0x83);
    }
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileOptions(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x62A);
    LocalBandUser* pLocalUser = pUser->GetLocalBandUser();
    MILO_ASSERT(pLocalUser, 0x62D);
    unk28 = 0x82;
    pUser->SetOvershellSlotState((OvershellSlotStateID)0x82);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWaitWii(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x638);
    pUser->SetOvershellSlotState((OvershellSlotStateID)0x81);
    mOvershell->UpdateAll();
}

void OvershellSlot::LeaveWaitWii(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x640);
    pUser->SetOvershellSlotState((OvershellSlotStateID)0x5);
    mOvershell->UpdateAll();
}

void OvershellSlot::ShowWiiProfileSelector(bool b){
    OvershellSlotState* ostate = GetState();
    OvershellSlotStateID oid = kState_JoinedDefault;
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x64A);
    if(ostate) oid = ostate->GetStateID();
    unk28 = oid;
    SetWiiProfileListMode(1, b);
    if(mSwappableProfilesProvider->GetWiiProfileCount(pUser->GetLocalBandUser()) <= 0){
        ShowState((OvershellSlotStateID)0x86);
    }
    else ShowState((OvershellSlotStateID)0x83);
}

void OvershellSlot::CancelWiiProfileSelector(){
    ShowState((OvershellSlotStateID)unk28);
    unk28 = 0x82;
}

void OvershellSlot::AttemptSwapUserProfile(int i){
    mStateMgr->GetSlotState(kState_ChooseProfileConfirm)->SetProperty("swap_user", 0);
}

void OvershellSlot::FetchLinkingCode(){
    MILO_ASSERT(mState->GetStateID() == kState_LinkingCode, 0x744);
    mState->SetProperty(waiting, 1);
    mState->SetProperty(success, 0);
    mState->SetProperty(code, "");
}

DECOMP_FORCEACTIVE(OvershellSlot, "code")

void OvershellSlot::ToggleVocalStyle(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x79E);
    MILO_ASSERT(pUser->GetControllerType() == kControllerVocals, 0x79F);
    GameplayOptions* options = pUser->GetGameplayOptions();
    if(options->GetVocalStyle() == kVocStyle0){
        options->SetVocalStyle(kVocStyle1);
    }
    else options->SetVocalStyle(kVocStyle0);
    Update();
}

void OvershellSlot::ToggleLeftyFlip(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0x7AB);
    MILO_ASSERT(pUser->GetControllerType() != kControllerVocals, 0x7AC);
    GameplayOptions* options = pUser->GetGameplayOptions();
    options->SetLefty(options->GetLefty() == 0);
    Update();
}

void OvershellSlot::ResetSlotCamera(){
    mOvershellDir->HandleType(reset_cam_msg);
}

void OvershellSlot::EnableAutohide(bool b){
    if(mAutohideEnabled != b){
        mAutohideEnabled = b;
        Update();
    }
}

void OvershellSlot::SetBlockAllInput(bool b){
    if(mBlockAllInput != b){
        mBlockAllInput = b;
        Update();
    }
}

void OvershellSlot::SetInGame(bool b){
    if(mInGame != b){
        mInGame = b;
        Update();
    }
}

void OvershellSlot::SetInTrackMode(bool b){
    mOvershellDir->SetProperty("in_track_mode", b);
}

void OvershellSlot::SetView(Symbol s){
    mCurrentView = s;
    mOvershellDir->SetProperty("slot_view", s);
}

void OvershellSlot::SetOverrideFlowReturnState(OvershellSlotStateID oid){
    MILO_ASSERT(GetUser()->IsLocal(), 0x7E0);
    mOverrideFlowReturnState = oid;
}

void OvershellSlot::RevertToOverrideFlowReturnState(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser, 0x7e7);
    MILO_ASSERT(pUser->IsLocal(), 0x7E8);
    pUser->SetOvershellSlotState((OvershellSlotStateID)mOverrideFlowReturnState);
    mOverrideFlowReturnState = kState_JoinedDefault;
    mOvershell->UpdateAll();
}

bool OvershellSlot::IsQuitToken(Symbol s) const {
    return s == TheGameMode->Property("pause_menu_quit_token", true)->Sym(0);
}

void OvershellSlot::BeginOverrideFlow(OvershellOverrideFlow type, bool b){
    MILO_ASSERT(mSlotOverrideFlow == kOverrideFlow_None, 0x826);
    MILO_ASSERT(type != kOverrideFlow_None, 0x827);
    SetOverrideType(type, b);
}

void OvershellSlot::EndOverrideFlow(OvershellOverrideFlow type, bool b){
    MILO_ASSERT(mSlotOverrideFlow == type, 0x82D);
    if(type == kOverrideFlow_SongSettings) mSongOptionsRequired = false;
    SetOverrideType(kOverrideFlow_None, b);
}

void OvershellSlot::SetOverrideType(OvershellOverrideFlow type, bool b){
    mSlotOverrideFlow = type;
    if(b) mOvershell->UpdateAll();
}

void OvershellSlot::Update(){
    UpdateState();
    UpdateView();
}

void OvershellSlot::CheckViewOverride(Symbol s, bool b, Symbol& sref){
    if(b) sref = s;
    else if(mCurrentView == s){
        sref = mState->GetView();
    }
}

void OvershellSlot::UpdateMuteUsersList(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    mMuteUsersProvider->RefreshUserList(pUser, mBandUserMgr);
    static Message updateMuteUsersMsg("update_users_provider", 0);
    updateMuteUsersMsg[0] = mMuteUsersProvider;
    mOvershellDir->HandleType(updateMuteUsersMsg);
}

void OvershellSlot::UpdateKickUsersList(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    mKickUsersProvider->RefreshUserList(pUser, mBandUserMgr);
    static Message updateKickUsersMsg("update_users_provider", 0);
    updateKickUsersMsg[0] = mKickUsersProvider;
    mOvershellDir->HandleType(updateKickUsersMsg);
}

void OvershellSlot::UpdateProfilesList(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser->IsLocal(), 0xC97);
    mSwappableProfilesProvider->Reload(pUser->GetLocalBandUser());
    static Message updateProfilesMsg("update_profiles_provider", 0);
    updateProfilesMsg[0] = mSwappableProfilesProvider;
    mOvershellDir->HandleType(updateProfilesMsg);
}

void OvershellSlot::UpdatePartSelectList(){
    BandUser* pUser = mBandUserMgr->GetUserFromSlot(mSlotNum);
    MILO_ASSERT(pUser, 0xCB0);
    ControllerType ty = pUser->GetControllerType();
    mPartSelectProvider->Reload(ty, pUser);
    static Message updatePartSelectMsg("update_part_select_provider", 0, 0);
    updatePartSelectMsg[0] = mPartSelectProvider;
    updatePartSelectMsg[1] = ty;
    mOvershellDir->HandleType(updatePartSelectMsg);
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
    HANDLE_ACTION(show_options_wiispeak, ShowState((OvershellSlotStateID)0x92))
    HANDLE_ACTION(show_options_extras, ShowState(kState_OptionsExtras))
    HANDLE_ACTION(show_options_drum, ShowOptionsDrum())
    HANDLE_ACTION(show_saveloadmgr_not_idle, ShowState((OvershellSlotStateID)0x3E))
    HANDLE_ACTION(show_saveloadmgr_not_meta, ShowState((OvershellSlotStateID)0x45))
    HANDLE_ACTION(show_saveloadmgr_autosave_confirm, ShowState((OvershellSlotStateID)0x47))
    HANDLE_ACTION(show_options_end_game, ShowState(kState_OptionsEndGame))
    HANDLE_ACTION(show_linking_code, ShowState(kState_LinkingCode))
    HANDLE_ACTION(show_linking_code_error, ShowState((OvershellSlotStateID)0x3a))
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
    HANDLE_ACTION(leave_char_delete, ShowState((OvershellSlotStateID)0x35))
    HANDLE_ACTION(show_sign_in_wait, ShowState((OvershellSlotStateID)0x14))
    HANDLE_ACTION(leave_sign_in_wait, LeaveSignInWait())
    HANDLE_ACTION(refresh_highlighted_char, RefreshHighlightedChar(_msg->Int(2)))
    HANDLE_ACTION(update_character_list, UpdateCharacterList())
    HANDLE_EXPR(get_default_char_index, GetDefaultCharIndex())
    HANDLE_ACTION(select_char, SelectChar(_msg->Int(2)))
    HANDLE_ACTION(begin_override_flow, BeginOverrideFlow((OvershellOverrideFlow)_msg->Int(2), true))
    HANDLE_ACTION(end_override_flow, EndOverrideFlow((OvershellOverrideFlow)_msg->Int(2), true))
    HANDLE_ACTION(show_enter_calibration, ShowEnterFlowPrompt((OvershellSlotStateID)0x17))
    HANDLE_ACTION(show_enter_credits, ShowEnterFlowPrompt((OvershellSlotStateID)0x3B))
    HANDLE_ACTION(show_enter_wiispeak_options, ShowEnterWiiSpeakOptions())
    HANDLE_ACTION(attempt_disconnect, AttemptDisconnect())
    HANDLE_ACTION(attempt_remove_user, AttemptRemoveUser())
    HANDLE_ACTION(show_kick_users, ShowState((OvershellSlotStateID)0x1B))
    HANDLE_ACTION(kick_user, KickUser(_msg->Int(2)))
    HANDLE_ACTION(show_mute_users, ShowState((OvershellSlotStateID)0x1C))
    HANDLE_ACTION(toggle_mute_user, ToggleMuteUser(_msg->Int(2)))
    HANDLE_ACTION(show_gamercard_users, ShowState((OvershellSlotStateID)0x1D))
    HANDLE_ACTION(toggle_vocal_style, ToggleVocalStyle())
    HANDLE_ACTION(toggle_lefty_flip, ToggleLeftyFlip())
    HANDLE_EXPR(get_char_provider, mCharProvider)
    HANDLE_EXPR(get_profiles_provider, mSwappableProfilesProvider)
    HANDLE_EXPR(confirm_swap_user_profile, ConfirmSwapUserProfile())
    HANDLE_ACTION(select_guest_profile, SelectGuestProfile())
    HANDLE_ACTION(show_modifiers, ShowState((OvershellSlotStateID)0x22))
    HANDLE_ACTION(show_modifiers_drum_warning, ShowState((OvershellSlotStateID)0x3F))
    HANDLE_ACTION(show_modifier_unlock, ShowState((OvershellSlotStateID)0x2e))
    HANDLE_ACTION(show_modifier_delayed_effect, ShowState((OvershellSlotStateID)0x4a))
    HANDLE_ACTION(show_toggle_no_fail_denial, ShowState((OvershellSlotStateID)0x43))
    HANDLE_EXPR(is_unlocking_modifiers, GetState()->GetStateID() == 0x2e)
    HANDLE_ACTION(attempt_toggle_auto_vocals, AttemptToggleAutoVocals())
    HANDLE_ACTION(update_part_select_list, UpdatePartSelectList())
    HANDLE_EXPR(is_cymbal_selected, IsCymbalSelected(_msg->Sym(2)))
    HANDLE_ACTION(confirm_choose_diff, ConfirmChooseDiff())
    HANDLE_ACTION(leave_difficulty_confirmation, LeaveDifficultyConfirmation())
    HANDLE_ACTION(confirm_kick, ConfirmKick())
    HANDLE_ACTION(leave_kick_confirmation, LeaveKickConfirmation())
    HANDLE_EXPR(is_in_track_mode, mOvershellDir->Property("in_track_mode", true)->Int(0))
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
    HANDLE_ACTION(show_choose_invitation, ShowState((OvershellSlotStateID)0x8C))
    HANDLE_ACTION(show_accept_invitation, ShowState((OvershellSlotStateID)0x8D))
    HANDLE_ACTION(show_no_invitations, ShowState((OvershellSlotStateID)0x8E))
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