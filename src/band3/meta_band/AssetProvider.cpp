#include "AssetProvider.h"

#include "utl/Symbols.h"
#include "AssetMgr.h"
#include <algorithm>
#include "system/rndwii/Rnd.h"
#include "AccomplishmentManager.h"
#include "system/ui/UIComponent.h"

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

    for (std::map<Symbol, Asset*>::const_iterator it = pAssetMgr->mAssets.begin(); it != pAssetMgr->mAssets.end(); it++) {
        Asset* pAsset = it->second;
        MILO_ASSERT(pAsset, 0x46);
    }

    std::sort(symbols.begin(), symbols.end());
}

UIComponent::State AssetProvider::ComponentStateOverride(int param_1, int param_2, UIComponent::State param_3) const {
    Symbol s; // TODO: Get symbol from profile, don't know which method is being used
    // bool hasAsset = mProfile.mProfileAssets->HasAsset(s);

    // if (!hasAsset) {
    //     param_3 = UIComponent::kDisabled;
    // }

    return param_3;
}

void AssetProvider::Text(int, int, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(slot, 200);
    MILO_ASSERT(label, 0xc9);

    // ProfileAssets* profileAssets = mProfile.mProfileAssets;

    // AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    // MILO_ASSERT(pAssetMgr, 0xd0);


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
    MILO_ASSERT_RANGE(data, 0, NumData(), 0x165);
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
