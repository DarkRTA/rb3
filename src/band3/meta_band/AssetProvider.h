#ifndef METABAND_ASSETPROVIDER_H
#define METABAND_ASSETPROVIDER_H

#include "AssetTypes.h"
#include "BandProfile.h"
#include "system/ui/UILabel.h"
#include "system/ui/UIListLabel.h"
#include "system/ui/UIListMesh.h"

class AssetProvider : public UIListProvider {
    AssetProvider(BandProfile*, AssetGender);
    virtual ~AssetProvider();
    void SortAssetsByIndex(Symbol, Symbol);
    void Update(AssetType, AssetBoutique);
    UIComponent::State ComponentStateOverride(int, int, UIComponent::State) const;
    void Text(int, int, UIListLabel*, UILabel*) const;
    RndMat* Mat(int, int, UIListMesh*) const;
    void UpdateExtendedText(int, int, UILabel*) const;
    Symbol DataSymbol(int) const;
    int NumData() const;
    void HasAsset(Symbol);
};

#endif // METABAND_ASSETPROVIDER_H