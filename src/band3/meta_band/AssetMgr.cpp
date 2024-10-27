#include "AssetMgr.h"

#include "utl/STLHelpers.h"
#include <algorithm>
#include "system/utl/Symbols.h"
#include "system/utl/Symbols4.h"
#include "system/obj/Utl.h"

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
    for(std::map<Symbol, Asset*>::iterator it = mAssets.begin(); it != mAssets.end(); ++it){
        RELEASE(it->second);
    }
    mAssets.clear();
    mIconPaths.clear();
}

void AssetMgr::Init() {
    TheAssetMgr = new AssetMgr();
}

AssetMgr* AssetMgr::GetAssetMgr() {
    return TheAssetMgr;
}

bool search(Asset* a) {
    return false;
}

Asset* AssetMgr::GetAsset(Symbol name) const {
    std::map<Symbol, Asset*>::const_iterator asset = mAssets.find(name);
    if (asset != mAssets.end()) {
        return asset->second;
    }  
    return NULL;
    // m_1.find(name);

    // for (std::set<Asset*>::const_iterator it = m_2.begin(); it != m_2.end(); it++) {
    //     Asset* asset = *it;
    //     if (asset->mName == name) {
    //         return asset;
    //     }
    // }
    // return NULL;
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

void AssetMgr::GetEyebrows(std::vector<Symbol>& eyebrows, Symbol symbol) const {
    AssetGender gender = GetAssetGenderFromSymbol(symbol);

    std::map<Symbol, Asset*>::const_iterator it = mAssets.begin();
    while (it != mAssets.end()) {
        Asset* pAsset = it->second;
        MILO_ASSERT(pAsset, 0xaf);
        if (pAsset->mType == 5 && pAsset->mGender == gender) {
            eyebrows.push_back(pAsset->mName);
        }
        it++;
    }
    std::sort(eyebrows.begin(), eyebrows.end());
}

int AssetMgr::GetEyebrowsCount(Symbol symbol) const {
    std::vector<Symbol> eyebrows;
    GetEyebrows(eyebrows, symbol);
    return eyebrows.size();
}

Symbol AssetMgr::StripFinish(Symbol symbol) {
    Asset* pAsset = GetAsset(symbol);
    
    if (pAsset == NULL) {
        String string = symbol;
        std::vector<String> subStrings;
        string.split("_", subStrings);
        Symbol s = Symbol(subStrings[0].c_str());
        pAsset = GetAsset(s);
        MILO_ASSERT(pAsset, 0xd9);
        return s;
    }
    
    return symbol;
}

void AssetMgr::ConfigureAssetTypeToIconPathMap() {
    Symbol assetType = "asset_type_icons";
    DataArray* pAssetTypeIcons = SystemConfig();
    MILO_ASSERT(pAssetTypeIcons, 0x100);

    if (1 < pAssetTypeIcons->Size()) {
        for (int i = 0; i < pAssetTypeIcons->Size(); i++) {
            DataArray* pEntry = pAssetTypeIcons->Array(i);
            MILO_ASSERT(pEntry, 0x106);
            MILO_ASSERT(pEntry->Size() != 2, 0x107);

            Symbol symbol = pEntry->Sym(0);
            AssetType type = GetAssetTypeFromSymbol(symbol);
            String str = pEntry->Str(1);
        }
    }
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

void AssetMgr::VerifyAssets(const char* param1) {
    VerifyAssets(param1, gNullStr);
    VerifyAssets(param1, "male");
    VerifyAssets(param1, "female");
}

void AssetMgr::VerifyAssets(const char* param1, const char* param2) {
    String dir = MakeString("char/main/%s", param1);
    if (param2 != gNullStr) {
        dir += MakeString("/%s");
    }

    if (!UsingCD()) {
        dir += "/*.milo";
    } else {
        dir += "/gen/*.milo_wii";
    }

    // MakeFileList(); param1 is DataArray* -> Char*
    DataArray* pFiles = new DataArray(0); // temp

    MILO_ASSERT(pFiles, 0x152);

    if (1 < pFiles->Size()) {
        for (int i = 1; i < pFiles->Size(); i++) {
            Symbol s = pFiles->Sym(i);

            if (s != "female_torso_naked" 
                && s != "male_legs_naked" 
                && s != "female_legs_naked" 
                && s != "male_feet_naked" 
                && s != "female_feet_naked") {

                // if (mTest.find(s) == mTest.end()) {
                //     TheDebug.Notify(MakeString("(%s/%s.milo) needs an entry in ui/customize/assets", param1, param2));
                // }
            }
        }
    }
}


void AssetMgr::EquipAsset(BandCharDesc*, Symbol) {

}

void AssetMgr::EquipAssets(LocalBandUser* user, const std::vector<Symbol>& assets) {
    BandCharacter* pChar = user->GetCharLocal();
    MILO_ASSERT(pChar, 0x1cb);
    BandCharDesc* pBandCharDesc;
    MILO_ASSERT(pBandCharDesc, 0x1cf);

    for (std::vector<Symbol>::const_iterator it = assets.begin(); it != assets.end(); it++) {
        EquipAsset(pBandCharDesc, *it);
    }
}
