#include "NewAssetProvider.h"
#include "system/utl/Symbols.h"
#include "system/utl/Symbols4.h"
#include "AssetMgr.h"

NewAssetProvider::NewAssetProvider(BandProfile* profile, AssetGender gender) : mProfile(profile), mGender(gender) {
    MILO_ASSERT(mProfile, 0x16);
    mSymbols.push_back(none);
}

NewAssetProvider::~NewAssetProvider() {

}

void NewAssetProvider::Update() {
    mSymbols.clear();
    mProfile->mProfileAssets.GetNewAssets(mSymbols, mGender);
}

void NewAssetProvider::Text(int param_1, int index, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(slot, 0x2b);
    MILO_ASSERT(label, 0x2c);
    Symbol symbol = DataSymbol(index);
    if (symbol != none) {
        AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x38);

        Asset* pAsset = pAssetMgr->GetAsset(symbol);

        MILO_ASSERT(pAsset, 0x3b);

        if (slot->Matches("name")) {
            label->SetTextToken(pAsset->mName);
        } else if (slot->Matches("new")) {
            label->SetTextToken(customize_new);
        } else {
            label->SetTextToken(gNullStr);
        } 
    }
}

void NewAssetProvider::UpdateExtendedText(int i, int i_iData, UILabel* label) const {
    MILO_ASSERT(i_iData < NumData(), 0x4f);

    Symbol symbol = DataSymbol(i_iData);
    if (symbol != none) {
        AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x5b);
        Asset* pAsset = pAssetMgr->GetAsset(symbol);
        MILO_ASSERT(pAsset, 0x5e);
        if (strcmp(label->Name(), "asset_desc_new.lbl") == 0) {
            Symbol description = pAsset->GetDescription();
            label->SetTextToken(description);
        } else if (strcmp(label->Name(), "asset_progress_new.lbl") == 0) {
            label->SetTokenFmt(customize_asset_progress, i_iData + 1, NumData());
        } else {
            label->SetTextToken(gNullStr);
        }
    }
}

Symbol NewAssetProvider::DataSymbol(int data) const {
    MILO_ASSERT(( 0) <= (data) && (data) < (NumData()), 0x75);
    return mSymbols[data];
}

int NewAssetProvider::NumData() const {
    return mSymbols.size();
}