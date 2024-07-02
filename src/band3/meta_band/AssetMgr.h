#ifndef METABAND_ASSETMGR_H
#define METABAND_ASSETMGR_H

#include <vector>
#include "system/utl/Symbol.h"

class AssetMgr {
    AssetMgr();
    virtual ~AssetMgr();
    void Init();
public:
    static AssetMgr* GetAssetMgr();
    void GetAsset(Symbol) const;
    bool HasAsset(Symbol) const;
    void GetTypeFromName(Symbol) const;
    void GetEyebrows(std::vector<Symbol>&, Symbol) const;
    void GetEyebrowsCount(Symbol) const;
    void StripFinish(Symbol) const;
    void ConfigureAssetTypeToIconPathMap();
    void AddAssets();
    void VerifyAssets(const char*);
    void VerifyAssets(const char*, const char*);
    // void EquipAsset(BandCharDesc*, Symbol);
    // void EquipAssets(LocalBandUser*, std::vector<Symbol>&);
};

static AssetMgr* TheAssetMgr;

#endif // METABAND_ASSETMGR_H