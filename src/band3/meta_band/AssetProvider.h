#pragma once
#include "AssetTypes.h"
#include "BandProfile.h"
#include "system/ui/UILabel.h"
#include "system/ui/UIListLabel.h"
#include "system/ui/UIListMesh.h"

class AssetProvider : public UIListProvider, public Hmx::Object {
public:
    AssetProvider(BandProfile *, AssetGender);
    virtual ~AssetProvider();
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual void UpdateExtendedText(int, int, UILabel *) const;
    virtual Symbol DataSymbol(int) const;
    virtual int NumData() const;
    virtual UIComponent::State ComponentStateOverride(int, int, UIComponent::State) const;

    bool HasAsset(Symbol);
    void Update(AssetType, AssetBoutique);
    static bool SortAssetsByIndex(Symbol, Symbol);

    BandProfile *mProfile; // 0x20
    std::vector<Symbol> mAssets; // 0x24
    AssetGender mGender; // 0x2c
};
