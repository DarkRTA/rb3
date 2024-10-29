#include "meta_band/ManageBandPanel.h"
#include "BandProfile.h"
#include "MetaMessages.h"
#include "bandobj/BandCharDesc.h"
#include "game/BandUser.h"
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
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "utl/Symbols.h"

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
        BandCharDesc* pPreviewDesc = pClosetMgr->mBandCharDesc;
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
        BandCharDesc* pPreviewDesc = pClosetMgr->mBandCharDesc;
        MILO_ASSERT(pPreviewDesc, 0x177);
        pPreviewDesc->CopyCharDesc(pStandInDesc);
        pClosetMgr->PreviewCharacter(false, true);
        ShowCharacter();
    }
}