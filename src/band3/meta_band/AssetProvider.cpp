#include "AssetProvider.h"

AssetProvider::AssetProvider(BandProfile* profile, AssetGender gender) : mProfile(profile), mGender(gender) {
    MILO_ASSERT(mProfile, 0x1d);
}

AssetProvider::~AssetProvider() {}

void AssetProvider::SortAssetsByIndex(Symbol, Symbol) {}

void AssetProvider::Update(AssetType, AssetBoutique) {}

UIComponent::State AssetProvider::ComponentStateOverride(int, int, UIComponent::State) const {}

void AssetProvider::Text(int, int, UIListLabel*, UILabel*) const {}

RndMat* AssetProvider::Mat(int, int, UIListMesh*) const {}

void AssetProvider::UpdateExtendedText(int, int, UILabel*) const {}

Symbol AssetProvider::DataSymbol(int) const {}

int AssetProvider::NumData() const {}

void AssetProvider::HasAsset(Symbol) {
    
}