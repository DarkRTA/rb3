#ifndef METABAND_ASSETMGR_H
#define METABAND_ASSETMGR_H

#include <vector>
#include <set>
#include "system/utl/Symbol.h"
#include "system/obj/Object.h"
#include "AssetTypes.h"
#include "Asset.h"

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
    void GetEyebrowsCount(Symbol) const;
    void StripFinish(Symbol);
    void ConfigureAssetTypeToIconPathMap();
    void AddAssets();
    void VerifyAssets(const char*);
    void VerifyAssets(const char*, const char*);
    // void EquipAsset(BandCharDesc*, Symbol);
    // void EquipAssets(LocalBandUser*, std::vector<Symbol>&);

private:
    std::set<int> m_1;      // 0x0
    std::set<Symbol> m_2;   // 0x00
};

static AssetMgr* TheAssetMgr;

#endif // METABAND_ASSETMGR_H