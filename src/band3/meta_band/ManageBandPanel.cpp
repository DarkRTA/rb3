#include "meta_band/ManageBandPanel.h"
#include "BandProfile.h"
#include "MetaMessages.h"
#include "bandobj/BandCharDesc.h"
#include "game/BandUser.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/CharData.h"
#include "meta_band/CharProvider.h"
#include "meta_band/CharSync.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/PrefabMgr.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/StandInProvider.h"
#include "meta_band/UIEventMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "utl/Messages2.h"
#include "utl/Messages4.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

inline void VignetteViewerProvider::Text(int, int iData, UIListLabel*, UILabel* label) const {
    MILO_ASSERT(iData < NumData(), 0x58);
    label->SetTextToken(mEntries[iData]);
}

inline bool VignetteViewerProvider::IsLocked(int idx){
    return mEntries[idx] == vignetteviewer_hidden_title;
}

inline Symbol VignetteViewerProvider::GetScreen(int idx){
    MILO_ASSERT(!IsLocked(idx), 0x6C);
    MILO_ASSERT_RANGE(idx, 0, mEntries.size(), 0x6D);
    Symbol target = mEntries[idx];
    int size = unk20->Size();
    for(int i = 0; i < size; i++){
        DataArray* arr = unk20->Array(i);
        if(target == arr->Sym(0)) return arr->Sym(1);
    }
    return gNullStr;
}

BEGIN_HANDLERS(VignetteViewerProvider)
    HANDLE_EXPR(is_locked, IsLocked(_msg->Int(2)))
    HANDLE_EXPR(get_screen, GetScreen(_msg->Int(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x8C)
END_HANDLERS

ManageBandPanel::ManageBandPanel() : mManageBandState(kManageBandNone), mSelectedStandIn(0), mStandInProvider(0), mCharProvider(0), mProfile(0) {
    mHistoryProvider = new VignetteViewerProvider();
}

ManageBandPanel::~ManageBandPanel(){
    delete mCharProvider;
    delete mStandInProvider;
    RELEASE(mHistoryProvider);
}

void ManageBandPanel::RefreshToMainState(){
    SetManageBandState(kManageBandMain);
    RefreshAll();
}

void ManageBandPanel::RefreshToStandinsState(){
    SetManageBandState(kManageBandStandins);
    RefreshAll();
}

void ManageBandPanel::RefreshAll(){
    if(mProfile){
        LocalBandUser* pLocalUser = mProfile->GetAssociatedLocalBandUser();
        MILO_ASSERT(pLocalUser, 0xB3);
        mCharProvider->Reload(pLocalUser);
        mStandInProvider->Reload(mProfile);
    }
}

void ManageBandPanel::Enter(){
    TheProfileMgr.AddSink(this, ProfileChangedMsg::Type());
    ThePlatformMgr.AddSink(this, SigninChangedMsg::Type());
    MILO_ASSERT(mProfile, 0xD2);
    mStandInProvider = new StandInProvider(mProfile);
    LocalBandUser* pLocalUser = mProfile->GetAssociatedLocalBandUser();
    MILO_ASSERT(pLocalUser, 0xD6);
    mCharProvider = new CharProvider(pLocalUser, false, true);
    UIPanel::Enter();
    RefreshToMainState();
}

void ManageBandPanel::CheckForKickoutCondition(){
    if(mProfile){
        mProfile->GetPadNum();
    }
    static Message init("init", 0);
    init[0] = 0;
    TheUIEventMgr->TriggerEvent(sign_out, init);
}

DataNode ManageBandPanel::OnMsg(const SigninChangedMsg&){
    CheckForKickoutCondition();
    return DataNode(kDataUnhandled, 0);
}

DataNode ManageBandPanel::OnMsg(const ProfileChangedMsg&){
    CheckForKickoutCondition();
    return DataNode(kDataUnhandled, 0);
}

void ManageBandPanel::Exit(){
    UIPanel::Exit();
    RELEASE(mCharProvider);
    RELEASE(mStandInProvider);
    SetManageBandState(kManageBandNone);
    TheProfileMgr.RemoveSink(this, ProfileChangedMsg::Type());
    ThePlatformMgr.RemoveSink(this, SigninChangedMsg::Type());
}

void ManageBandPanel::Unload(){
    UIPanel::Unload();
    TheCharSync->UpdateCharCache();
}

void ManageBandPanel::SetProfile(BandProfile* p){ mProfile = p; }
void ManageBandPanel::ClearProfile(){ mProfile = nullptr; }

RndTex* ManageBandPanel::GetBandLogoTex(){
    MILO_ASSERT(mProfile, 0x11E);
    return mProfile->GetBandLogoTex();
}

StandInProvider* ManageBandPanel::GetStandInProvider(){
    MILO_ASSERT(mStandInProvider != NULL, 0x124);
    return mStandInProvider;
}

CharProvider* ManageBandPanel::GetCharProvider(){
    MILO_ASSERT(mCharProvider != NULL, 0x12A);
    return mCharProvider;
}

VignetteViewerProvider* ManageBandPanel::GetHistoryProvider(){
    MILO_ASSERT(mHistoryProvider != NULL, 0x130);
    return mHistoryProvider;
}

void ManageBandPanel::SetManageBandState(ManageBandState state){
    static Message msgUpdateState("update_state", 0, 0);
    msgUpdateState[0] = state;
    msgUpdateState[1] = mManageBandState;
    mManageBandState = state;
    HandleType(msgUpdateState);
}

void ManageBandPanel::UpdateCharacterFromStandInList(int i){
    StandIn* standin = mProfile->GetStandIn(i);
    if(standin->IsNone()){
        HideCharacter();
    }
    else {
        CharData* pCharacter = nullptr;
        if(standin->IsPrefabCharacter()){
            PrefabMgr* pPrefabMgr = PrefabMgr::GetPrefabMgr();
            MILO_ASSERT(pPrefabMgr, 0x14C);
            pCharacter = pPrefabMgr->GetPrefab(standin->mName);
        }
        else if(standin->IsCustomCharacter()){
            pCharacter = mProfile->GetCharFromGuid(standin->mGuid);
        }
        MILO_ASSERT(pCharacter, 0x157);
        BandCharDesc* pStandInDesc = pCharacter->GetBandCharDesc();
        MILO_ASSERT(pStandInDesc, 0x159);
        ClosetMgr* pClosetMgr = ClosetMgr::GetClosetMgr();
        MILO_ASSERT(pClosetMgr, 0x15C);
        BandCharDesc* pPreviewDesc = pClosetMgr->unk3c;
        MILO_ASSERT(pPreviewDesc, 0x15E);
        pPreviewDesc->CopyCharDesc(pStandInDesc);
        pClosetMgr->PreviewCharacter(false, true);
        ShowCharacter();
    }
}

void ManageBandPanel::UpdateCharacterFromCharList(int i){
    if(mCharProvider->IsIndexNone(i)){
        HideCharacter();
    }
    else {
        CharData* pCharacter = mCharProvider->GetCharData(i);
        MILO_ASSERT(pCharacter, 0x170);
        BandCharDesc* pStandInDesc = pCharacter->GetBandCharDesc();
        MILO_ASSERT(pStandInDesc, 0x172);
        ClosetMgr* pClosetMgr = ClosetMgr::GetClosetMgr();
        MILO_ASSERT(pClosetMgr, 0x175);
        BandCharDesc* pPreviewDesc = pClosetMgr->unk3c;
        MILO_ASSERT(pPreviewDesc, 0x177);
        pPreviewDesc->CopyCharDesc(pStandInDesc);
        pClosetMgr->PreviewCharacter(false, true);
        ShowCharacter();
    }
}

void ManageBandPanel::ShowCharacter(){
    Handle(show_character_msg, true);
}

void ManageBandPanel::HideCharacter(){
    Handle(hide_character_msg, true);
}

void ManageBandPanel::RefreshStandinList(){
    MILO_ASSERT(mProfile, 0x18E);
    LocalBandUser* pLocalUser = mProfile->GetAssociatedLocalBandUser();
    MILO_ASSERT(pLocalUser, 400);
    mCharProvider->unk30 = mSelectedStandIn;
    mCharProvider->Reload(pLocalUser);
}

void ManageBandPanel::SetSelectedStandIn(int i){ mSelectedStandIn = i; }

void ManageBandPanel::SetStandIn(int i){
    StandIn* standin = mProfile->AccessStandIn(mSelectedStandIn);
    if(mCharProvider->IsIndexNone(i)){
        standin->SetNone();
    }
    else if(mCharProvider->IsIndexPrefab(i)){
        standin->SetName(mCharProvider->DataSymbol(i));
    }
    else if(mCharProvider->IsIndexCustomChar(i)){
        CharData* pCharacter = mCharProvider->GetCharData(i);
        MILO_ASSERT(pCharacter, 0x1AB);
        standin->SetGuid(pCharacter->mGuid);
    }

    if(mProfile->GetNumStandins() == 4){
        TheAccomplishmentMgr->EarnAccomplishment(mProfile, acc_standins);
    }
}

void ManageBandPanel::QueueRewardVignette(Symbol s){
    AccomplishmentProgress* prog = mProfile->AccessAccomplishmentProgress();
    prog->AddNewRewardVignette(s);
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(ManageBandPanel)
    HANDLE_ACTION(set_profile, SetProfile(_msg->Obj<BandProfile>(2)))
    HANDLE_ACTION(clear_profile, ClearProfile())
    HANDLE_EXPR(get_profile, GetProfile())
    HANDLE_EXPR(get_band_logo_tex, GetBandLogoTex())
    HANDLE_ACTION(refresh_to_main_state, RefreshToMainState())
    HANDLE_ACTION(refresh_to_standins_state, RefreshToStandinsState())
    HANDLE_EXPR(get_standin_provider, GetStandInProvider())
    HANDLE_EXPR(get_char_provider, GetCharProvider())
    HANDLE_EXPR(get_history_provider, GetHistoryProvider())
    HANDLE_ACTION(queue_reward_vignette, QueueRewardVignette(_msg->Sym(2)))
    HANDLE_ACTION(update_character_from_standin_list, UpdateCharacterFromStandInList(_msg->Int(2)))
    HANDLE_ACTION(update_character_from_char_list, UpdateCharacterFromCharList(_msg->Int(2)))
    HANDLE_ACTION(refresh_standin_list, RefreshStandinList())
    HANDLE_ACTION(set_selected_standin, SetSelectedStandIn(_msg->Int(2)))
    HANDLE_EXPR(get_selected_standin, GetSelectedStandIn())
    HANDLE_ACTION(set_standin, SetStandIn(_msg->Int(2)))
    HANDLE_EXPR(get_state, GetManageBandState())
    HANDLE_ACTION(set_state, SetManageBandState((ManageBandState)_msg->Int(2)))
    HANDLE_ACTION(check_for_kickout_condition, CheckForKickoutCondition())
    HANDLE_MESSAGE(ProfileChangedMsg)
    HANDLE_MESSAGE(SigninChangedMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x1F4)
END_HANDLERS
#pragma pop