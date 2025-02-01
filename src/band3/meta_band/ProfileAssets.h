#pragma once
#include "system/utl/Symbol.h"
#include "AssetTypes.h"
#include "system/meta/FixedSizeSaveableStream.h"
#include "system/meta/FixedSizeSaveable.h"
#include <set>

class BandProfile;

class ProfileAssets : public FixedSizeSaveable {
public:
    ProfileAssets(BandProfile *);
    virtual ~ProfileAssets();
    void Clear();
    void AddAsset(Symbol);
    bool HasAsset(Symbol) const;
    bool IsNew(Symbol) const;
    void SetOld(Symbol);
    void GetNewAssets(std::vector<Symbol> &, AssetGender) const;
    int GetNumNewAssets(AssetGender) const;
    static int SaveSize(int);
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);
    void FakeFill();

    BandProfile *mParentProfile; // 0x04
    std::set<Symbol> mAssets; // 0x08
    std::set<Symbol> mNewAssets; // 0x24
};
