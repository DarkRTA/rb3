#ifndef METABAND_NEWASSETPROVIDER_H
#define METABAND_NEWASSETPROVIDER_H

#include "AssetTypes.h"
#include "BandProfile.h"
#include "system/ui/UILabel.h"
#include "system/ui/UIListLabel.h"

class NewAssetProvider : public UIListProvider, public Hmx::Object {
    NewAssetProvider(BandProfile*, AssetGender);
    virtual ~NewAssetProvider();
    void Update();
    void Text(int, int, UIListLabel*, UILabel*) const;
    void UpdateExtendedText(int, int, UILabel*) const;
    Symbol DataSymbol(int) const;
    int NumData() const;

    BandProfile* mProfile;    // 0x20
    AssetGender mGender;          // 0x24
    std::vector<Symbol> mSymbols; // 0x28
};

#endif // METABAND_NEWASSETPROVIDER_H