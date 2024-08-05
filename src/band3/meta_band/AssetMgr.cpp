#include "AssetMgr.h"

#include "system/utl/Symbols4.h"

AssetMgr::AssetMgr() {
    AddAssets();
    ConfigureAssetTypeToIconPathMap();
    VerifyAssets("earrings");
    VerifyAssets("eyebrows");
    VerifyAssets("facehair");
    VerifyAssets("glasses");
    VerifyAssets("hair");
    VerifyAssets("hands");
    VerifyAssets("piercings");
    VerifyAssets("rings");
    VerifyAssets("wrist");
    VerifyAssets("feet");
    VerifyAssets("legs");
    VerifyAssets("torso");
    VerifyAssets("keyboard");
    VerifyAssets("mic");
}

AssetMgr::~AssetMgr() {

}

void AssetMgr::Init() {
    TheAssetMgr = new AssetMgr();
}

AssetMgr* AssetMgr::GetAssetMgr() {
    return TheAssetMgr;
}

Asset* AssetMgr::GetAsset(Symbol name) const {
    for (std::set<Asset*>::const_iterator it = m_2.begin(); it != m_2.end(); it++) {
        Asset* asset = *it;

    }
    return NULL;
}

bool AssetMgr::HasAsset(Symbol asset) const {
    return GetAsset(asset) != NULL;
}

AssetType AssetMgr::GetTypeFromName(Symbol name) const {
    AssetType type;
    if (name == none_bandana) {
        return (AssetType)1;
    } 
    if (name == none_earrings) {
        return (AssetType)4;
    } 
    if (name == none_eyebrows) {
        return (AssetType)5;
    }
    if (name == none_facehair) {
        return (AssetType)6;
    }
    if (name == none_glasses) {
        return (AssetType)8;
    }
    if (name == none_hair) {
        return (AssetType)0xb;
    }
    if (name == none_hat) {
        return (AssetType)0xc;
    }
    if (name == none_piercings) {
        return (AssetType)0x10;
    }
    if (name == none_rings) {
        return (AssetType)0x11;
    }
    if (name == none_wrists) {
        return (AssetType)0x13;
    }

    Asset* pAsset = GetAsset(name);
    MILO_ASSERT(pAsset, 0x9f);
    return (AssetType)pAsset->mType;
}

void AssetMgr::GetEyebrows(std::vector<Symbol>&, Symbol) const {

}

void AssetMgr::GetEyebrowsCount(Symbol) const {

}

void AssetMgr::StripFinish(Symbol) {

}

void AssetMgr::ConfigureAssetTypeToIconPathMap() {

}

void AssetMgr::AddAssets() {
    Symbol("assets");
    DataArray* pAssets = SystemConfig();
    MILO_ASSERT(pAssets, 0x114);
    for (int i = 1; i < pAssets->Size(); i++) {
        DataArray* pConfig = pAssets->Array(i);
        MILO_ASSERT(pConfig, 0x11a);
    }
}

void AssetMgr::VerifyAssets(const char*) {

}

void AssetMgr::VerifyAssets(const char*, const char*) {

}


void AssetMgr::EquipAsset(BandCharDesc*, Symbol) {

}

void AssetMgr::EquipAssets(LocalBandUser*, const std::vector<Symbol>&) {

}
