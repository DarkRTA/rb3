#include "meta_band/OvershellSlot.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/PassiveMessage.h"
#include "meta_band/SessionUsersProviders.h"
#include "meta_band/CharProvider.h"
#include "meta_band/OvershellProfileProvider.h"
#include "meta_band/OvershellPartSelectProvider.h"
#include "meta_band/CymbalSelectionProvider.h"
#include "game/GameMessages.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/ProfileMgr.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

OvershellSlot::OvershellSlot(int i, OvershellPanel* panel, OvershellDir* dir, BandUserMgr* umgr, SessionMgr* smgr) : mStateMgr(new OvershellSlotStateMgr()), mState(0), unk24(5), unk28(0x82),
    mOvershell(panel), mBandUserMgr(umgr), mSessionMgr(smgr), mSlotNum(i), mOvershellDir(dir), unk54(0), unk55(0), unk58(gNullStr), unk5c(0), mInGame(0), unk5e(0), unk80(0), unk81(0), unk84(0), unk88(0), unk90(kOverrideFlow_None) {
    mMessageQueue = new PassiveMessageQueue(this);
    unk98 = new SessionUsersProvider(false, true, false);
    unk9c = new SessionUsersProvider(true, true, false);
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
    unk2c = mOvershellDir->Find<BandLabel>("user_name.lbl", true);
}

OvershellSlot::~OvershellSlot(){

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
    unk55 = false;
}

int OvershellSlot::GetSlotNum(){ return mSlotNum; }
PanelDir* OvershellSlot::GetPanelDir(){ return mOvershellDir; }

bool OvershellSlot::IsHidden() const {
    return unk54 && mState->AllowsHiding();
}

bool OvershellSlot::IsLeavingOptions() const { return unk55; }
Symbol OvershellSlot::GetCurrentView() const { return unk58; }

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

BandUser* OvershellSlot::GetUser() const {
    return mBandUserMgr->GetUserFromSlot(mSlotNum);
}

OvershellSlotState* OvershellSlot::GetState(){
    MILO_ASSERT(mState, 0x1B2);
    return mState;
}

void OvershellSlot::LeaveOptions(){
    ShowState(kState_JoinedDefault);
    unk55 = true;
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
    unk88 ^= cymBit;
}

bool OvershellSlot::IsCymbalSelected(Symbol s){
    if(s == overshell_yellow_cym && (unk88 & 4)) return true;
    else if(s == overshell_blue_cym && (unk88 & 8)) return true;
    else if(s == overshell_green_cym && (unk88 & 0x10)) return true;
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
        TheProfileMgr.SetCymbalConfiguration(unk88);
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

// void __thiscall OvershellSlot::LeaveChoosePartWait(OvershellSlot *this)

// {
//   BandUser *this_00;
//   int iVar1;
//   char *pcVar2;
  
//   this_00 = (BandUser *)
//             BandUserMgr::GetUserFromSlot(*(BandUserMgr **)(this + 0x34),*(int *)(this + 0x3c));
//   iVar1 = (**(code **)(**(int **)this_00 + 100))();
//   if (iVar1 == 0) {
//     pcVar2 = ::MakeString(kAssertStr,s_OvershellSlot.cpp_80b9ca4e,0x411,s_pUser->IsLocal()_80b9caa 2)
//     ;
//     Debug::Fail((Debug *)TheDebug,pcVar2);
//   }
//   BandUser::SetTrackType(this_00,10);
//   BandUser::SetOvershellSlotState(this_00,10);
//   OvershellPanel::UpdateAll(*(OvershellPanel **)(this + 0x30));
//   return;
// }