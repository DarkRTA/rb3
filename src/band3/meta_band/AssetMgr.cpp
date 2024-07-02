#include "AssetMgr.h"

AssetMgr::AssetMgr() {

}

AssetMgr::~AssetMgr() {

}

void AssetMgr::Init() {
    TheAssetMgr = new AssetMgr();
}

AssetMgr* AssetMgr::GetAssetMgr() {
    return TheAssetMgr;
}

void AssetMgr::GetAsset(Symbol) const {

}

bool AssetMgr::HasAsset(Symbol) const {

}

void AssetMgr::GetTypeFromName(Symbol) const {

}

void AssetMgr::GetEyebrows(std::vector<Symbol>&, Symbol) const {

}

void AssetMgr::GetEyebrowsCount(Symbol) const {

}

void AssetMgr::StripFinish(Symbol) const {

}

void AssetMgr::ConfigureAssetTypeToIconPathMap() {

}

void AssetMgr::AddAssets() {

}

void AssetMgr::VerifyAssets(const char*) {

}

void AssetMgr::VerifyAssets(const char*, const char*) {

}
