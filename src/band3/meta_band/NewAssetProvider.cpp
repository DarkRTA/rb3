#include "NewAssetProvider.h"
#include "system/utl/Symbols4.h"
#include "AssetMgr.h"

NewAssetProvider::NewAssetProvider(BandProfile* profile, AssetGender gender) : mProfile(profile), mGender(gender) {
    MILO_ASSERT(mProfile, 0x16);
    mSymbols.push_back(none);
}

NewAssetProvider::~NewAssetProvider() {

}

void NewAssetProvider::Update() {

}

void NewAssetProvider::Text(int param_1, int param_2, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(slot, 0x2b);
    MILO_ASSERT(label, 0x2c);
    Symbol s = mSymbols[param_2];
    if (s != none) {
        AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
        MILO_ASSERT(pAssetMgr, 0x38);

        pAssetMgr->GetAsset(s);
    }
}

void NewAssetProvider::UpdateExtendedText(int, int i_iData, UILabel*) const {
    MILO_ASSERT(i_iData < NumData(), 0x4f);

}

Symbol NewAssetProvider::DataSymbol(int data) const {
    MILO_ASSERT(( 0) <= (data) && (data) < (NumData()), 0x75);
    return mSymbols[data];
}

int NewAssetProvider::NumData() const {
    return mSymbols.size();
}