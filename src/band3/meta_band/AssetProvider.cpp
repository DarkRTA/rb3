#include "AssetProvider.h"

#include "utl/Symbols.h"
#include "AssetMgr.h"

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
}

void AssetProvider::Update(AssetType, AssetBoutique) {
    AssetMgr* pAssetMgr = AssetMgr::GetAssetMgr();
    MILO_ASSERT(pAssetMgr, 0x3d);
}

UIComponent::State AssetProvider::ComponentStateOverride(int, int, UIComponent::State) const {
    
}

void AssetProvider::Text(int, int, UIListLabel*, UILabel*) const {

}

RndMat* AssetProvider::Mat(int, int, UIListMesh*) const {

}

void AssetProvider::UpdateExtendedText(int, int, UILabel*) const {

}

Symbol AssetProvider::DataSymbol(int data) const {
    MILO_ASSERT(( 0) <= (data) && (data) < ( NumData()), 0x165);
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