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
    for (std::vector<Symbol>::const_iterator iter = mSymbols.begin(); iter != mSymbols.end(); iter++) {

    }

    
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

void NewAssetProvider::UpdateExtendedText(int, int i_iData, UILabel* label) const {
    MILO_ASSERT(i_iData < NumData(), 0x4f);

    Symbol symbol = DataSymbol(i_iData);
    if (symbol != none) {
        AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x5b);
        Asset* pAsset = pAssetMgr->GetAsset(symbol);
        MILO_ASSERT(pAsset, 0x5e);

        const char* name = label->Name();
        if (strcmp(name, "asset_desc_new.lbl") == 0) {
            Symbol description = pAsset->GetDescription();
            label->SetTextToken(description);
        } else if (strcmp(name, "asset_progress_new.lbl") == 0) {
            DataNode node0 = customize_asset_progress;
            DataNode node1 = i_iData + 1;
            DataNode node2 = i_iData; 

            DataArray* array = new DataArray(3);
            array->Node(0) = node0;
            array->Node(1) = node1;
            array->Node(2) = node2;
            
            label->SetTokenFmt(array);
            delete array;
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