#pragma once
#include "AssetTypes.h"
#include "BandProfile.h"
#include "system/ui/UILabel.h"
#include "system/ui/UIListLabel.h"

class NewAssetProvider : public UIListProvider, public Hmx::Object {
public:
    NewAssetProvider(BandProfile *, AssetGender);
    virtual ~NewAssetProvider();
    void Update();
    void Text(int, int, UIListLabel *, UILabel *) const;
    void UpdateExtendedText(int, int, UILabel *) const;
    Symbol DataSymbol(int) const;
    int NumData() const;

    BandProfile *mProfile; // 0x20
    AssetGender mGender; // 0x24
    std::vector<Symbol> mSymbols; // 0x28
};
