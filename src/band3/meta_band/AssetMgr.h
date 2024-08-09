#ifndef METABAND_ASSETMGR_H
#define METABAND_ASSETMGR_H

#include <vector>
#include <set>
#include <map>
#include "system/utl/Symbol.h"
#include "system/obj/Object.h"
#include "AssetTypes.h"
#include "Asset.h"
#include "band3/game/BandUser.h"

class BandCharDesc;

class AssetMgr : public Hmx::Object {
    AssetMgr();
    virtual ~AssetMgr();
    void Init();
public:
    static AssetMgr* GetAssetMgr();
    Asset* GetAsset(Symbol) const;
    bool HasAsset(Symbol) const;
    AssetType GetTypeFromName(Symbol) const;
    void GetEyebrows(std::vector<Symbol>&, Symbol) const;
    int GetEyebrowsCount(Symbol) const;
    Symbol StripFinish(Symbol);
    void ConfigureAssetTypeToIconPathMap();
    void AddAssets();
    void VerifyAssets(const char*);
    void VerifyAssets(const char*, const char*);
    void EquipAsset(BandCharDesc*, Symbol);
    void EquipAssets(LocalBandUser*, const std::vector<Symbol>&);

public:  
    std::map<Symbol, Asset*> mAssets;  
    std::map<String, String> mPadding;
};

static AssetMgr* TheAssetMgr;

#endif // METABAND_ASSETMGR_H