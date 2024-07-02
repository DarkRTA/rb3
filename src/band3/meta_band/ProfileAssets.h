#ifndef METABAND_PROFILEASSETS_H
#define METABAND_PROFILEASSETS_H

#include "BandProfile.h"
#include "system/utl/Symbol.h"
#include "AssetTypes.h"
#include "system/meta/FixedSizeSaveableStream.h"
#include "system/meta/FixedSizeSaveable.h"
#include <set>

class ProfileAssets : public FixedSizeSaveable {
    ProfileAssets(BandProfile*);
    virtual ~ProfileAssets();
    void Clear();
    void AddAsset(Symbol);
    bool HasAsset(Symbol) const;
    bool IsNew(Symbol) const;
    void SetOld(Symbol);
    void GetNewAssets(std::vector<Symbol>&, AssetGender) const;
    void GetNumNewAssets(AssetGender) const;
    void SaveSize(int);
    void SaveFixed(FixedSizeSaveableStream&) const;
    void LoadFixed(FixedSizeSaveableStream&, int);
    void FakeFill();

    BandProfile* mParentProfile;  // 0x04
    std::set<Symbol> mAssets;     // 0x08
    std::set<Symbol> mAssets2; 
};

#endif // METABAND_PROFILEASSETS_H