#include "AssetProvider.h"

#include "utl/Symbols.h"
#include "AssetMgr.h"
#include <algorithm>
#include "system/rndwii/Rnd.h"
#include "AccomplishmentManager.h"

AssetProvider::AssetProvider(BandProfile* profile, AssetGender gender) : mProfile(profile), mGender(gender) {
    MILO_ASSERT(mProfile, 0x1d);
    mAssets.push_back(none);
}

AssetProvider::~AssetProvider() {

}

bool AssetProvider::SortAssetsByIndex(Symbol symbol1, Symbol symbol2) {
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x24);

    Asset* pAsset1 = pAssetMgr->GetAsset(symbol1);
    MILO_ASSERT(pAsset1, 0x30);

    Asset* pAsset2 = pAssetMgr->GetAsset(symbol2);
    MILO_ASSERT(pAsset2, 0x32);

    if (pAsset1->mIndex < pAsset2->mIndex) {
        return true;
    }
    return false;
}

void AssetProvider::Update(AssetType, AssetBoutique) {
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x3d);

    std::vector<Symbol> symbols;

    for (std::set<Asset*>::const_iterator it = pAssetMgr->m_2.begin(); it != pAssetMgr->m_2.end(); it++) {
        Asset* pAsset = *it;
        MILO_ASSERT(pAsset, 0x46);
    }
    
    std::sort(symbols.begin(), symbols.end());
}

UIComponent::State AssetProvider::ComponentStateOverride(int, int, UIComponent::State) const {
    
}

void AssetProvider::Text(int, int, UIListLabel*, UILabel*) const {

}

RndMat* AssetProvider::Mat(int, int, UIListMesh*) const {

}

void AssetProvider::UpdateExtendedText(int, int i_iData, UILabel* label) const {
    MILO_ASSERT(i_iData < NumData(), 0x12c);

    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x132);

    Symbol asset = label->Name();

    if (strcmp(asset.Str(), "asset_desc.lbl") == 0) {
        bool hasAsset = pAssetMgr->HasAsset(asset);
        if (!hasAsset) {
            label->SetTextToken(gNullStr);
        } else {
            Asset* pAsset = pAssetMgr->GetAsset(asset);
            MILO_ASSERT(pAsset, 0x139);
            if (TheWiiRnd.mShowAssetName == '\0') {
                // hasAsset = pAssetMgr->HasAsset();
                if (!hasAsset) {
                    MILO_ASSERT(TheAccomplishmentMgr, 0x14b);
                }
                // TheAccomplishmentMgr->UpdateAssetHintLabel(pAsset->GetDescription(), label);
            }
        }
    } else {
        if (strcmp(asset.Str(), "asset_progress.lbl") == 0) {
            // Bulid data array
        } else {
            label->SetTextToken(gNullStr);
        }
    }
}

Symbol AssetProvider::DataSymbol(int data) const {
    MILO_ASSERT(( 0) <= (data) && (data) < ( NumData()), 0x165);
    return mAssets[data];
}

int AssetProvider::NumData() const {
    return mAssets.size();
}

bool AssetProvider::HasAsset(Symbol s) {
    for (size_t i = 0; i < mAssets.size(); i++) {
        if (mAssets[i] == s) {
            return true;
        }
    }
    return false;
}