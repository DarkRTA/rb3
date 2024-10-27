#include "meta_band/NewAwardPanel.h"
#include "AssetMgr.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AssetTypes.h"
#include "meta_band/TexLoadPanel.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "rndobj/Mesh.h"
#include "ui/UILabel.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
#include "ui/UIPanel.h"
#include "utl/Messages2.h"
#include "utl/Messages4.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

inline void AwardAssetProvider::Update(Symbol s){
    unk20 = s;
    unk24.clear();
    Award* pAward = TheAccomplishmentMgr->GetAward(unk20);
    MILO_ASSERT(pAward, 0x31);
    pAward->InqAssets(unk24);
}

NewAwardPanel::NewAwardPanel() : mUser(0), mAwardName(gNullStr), mAwardReason(gNullStr), m_pAwardAssetProvider(0) {

}

void NewAwardPanel::Enter(){
    UIPanel::Enter();
    PopAndShowFirstAward();
}

void NewAwardPanel::LoadIcons(){
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0xAE);
    const std::map<int, String>& icons = pAssetMgr->GetIconPaths();
    for(std::map<int, String>::const_iterator it = icons.begin(); it != icons.end(); ++it){
        Symbol sym = GetSymbolFromAssetType((AssetType)it->first);
        String path(it->second);
        if(!path.empty()){
            AddTex(path.c_str(), sym.Str(), true, false);
        }
    }
}

void NewAwardPanel::Load(){
    TexLoadPanel::Load();
    MILO_ASSERT(!m_pAwardAssetProvider, 0xC3);
    LoadIcons();
}

void NewAwardPanel::Unload(){
    TexLoadPanel::Unload();
    RELEASE(m_pAwardAssetProvider);
}

void NewAwardPanel::FinishLoad(){
    TexLoadPanel::FinishLoad();
    MILO_ASSERT(!m_pAwardAssetProvider, 0xD5);
    m_pAwardAssetProvider = new AwardAssetProvider(mTexs);
}

void NewAwardPanel::PopAndShowFirstAward(){
    if(!TheAccomplishmentMgr->HasNewAwards()){
        Handle(handle_continue_msg, true);
    }
    else {
        mUser = TheAccomplishmentMgr->GetUserForFirstNewAward();
        mAwardName = TheAccomplishmentMgr->GetNameForFirstNewAward(mUser);
        mAwardReason = TheAccomplishmentMgr->GetReasonForFirstNewAward(mUser);
        MILO_ASSERT(m_pAwardAssetProvider, 0xEC);
        m_pAwardAssetProvider->Update(mAwardName);
        static Message cUpdateProviderMsg("update_provider", 0);
        cUpdateProviderMsg[0] = m_pAwardAssetProvider;
        Handle(cUpdateProviderMsg, true);
        Handle(update_all_msg, true);
        TheAccomplishmentMgr->ClearFirstNewAward(mUser);
    }
}

int NewAwardPanel::GetNumAssets() const {
    MILO_ASSERT(m_pAwardAssetProvider, 0x10F);
    return m_pAwardAssetProvider->NumData();
}

BEGIN_HANDLERS(NewAwardPanel)
    HANDLE_EXPR(get_award, mAwardName)
    HANDLE_EXPR(get_award_reason, mAwardReason)
    HANDLE_EXPR(get_user, mUser)
    HANDLE_ACTION(pop_and_show_first_award, PopAndShowFirstAward())
    HANDLE_EXPR(get_num_assets, GetNumAssets())
    HANDLE_SUPERCLASS(TexLoadPanel)
    HANDLE_CHECK(0x123)
END_HANDLERS

inline Symbol AwardAssetProvider::DataSymbol(int i_iIndex) const {
    MILO_ASSERT_RANGE( i_iIndex, 0, NumData(), 0x87);
    return unk24[i_iIndex];
}

inline RndMat* AwardAssetProvider::Mat(int, int i_iData, UIListMesh* slot) const {
    MILO_ASSERT(i_iData < NumData(), 0x55);
    Symbol dataSym = DataSymbol(i_iData);
    if(slot->Matches("icon")){
        AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x5B);
        String assetStr(GetSymbolFromAssetType(pAssetMgr->GetTypeFromName(dataSym)).Str());
        return GetMatForName(assetStr);     
    }
    else if(slot->Matches("gender")){
        AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x65);
        Asset* pAsset = pAssetMgr->GetAsset(dataSym);
        MILO_ASSERT(pAsset, 0x68);
        if(pAsset->mGender == 1){
            return mMaleMat;
        }
        else if(pAsset->mGender == 2){
            return mFemaleMat;
        }
        else return mUnisexMat;
    }
    else return slot->DefaultMat();
}

inline void AwardAssetProvider::Text(int, int i_iData, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(i_iData < NumData(), 0x38);
    Symbol dataSym = DataSymbol(i_iData);
    if(slot->Matches("name")){
        label->SetTextToken(dataSym);
    }
    else label->SetTextToken(gNullStr);
}

inline void AwardAssetProvider::InitData(RndDir* rdir){
    mMaleMat = rdir->Find<RndMat>("male.mat", false);
    mFemaleMat = rdir->Find<RndMat>("female.mat", false);
    mUnisexMat = rdir->Find<RndMat>("unisex.mat", false);
}