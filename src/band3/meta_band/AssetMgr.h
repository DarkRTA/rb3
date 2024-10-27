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
public:
    AssetMgr();
    virtual ~AssetMgr();
    void Init();
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

    const std::map<Symbol, Asset*>& GetAssets() const { return mAssets; }
    const std::map<int, String>& GetIconPaths() const { return mIconPaths; }

    std::map<Symbol, Asset*> mAssets; // 0x1c
    std::map<int, String> mIconPaths; // 0x34
};

static AssetMgr* TheAssetMgr;

#endif // METABAND_ASSETMGR_H