#include "AssetMgr.h"

#include "decomp.h"
#include "meta_band/AssetTypes.h"
#include "meta_band/ClosetMgr.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/System.h"
#include "tour/TourCharLocal.h"
#include "utl/Std.h"
#include "utl/Symbol.h"
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

DECOMP_FORCEACTIVE(AssetMgr, "")

AssetMgr::~AssetMgr() {
    FOREACH (it, mAssets) {
        RELEASE(it->second);
    }
    mAssets.clear();
    mIconPaths.clear();
}

void AssetMgr::Init() { TheAssetMgr = new AssetMgr(); }

AssetMgr *AssetMgr::GetAssetMgr() { return TheAssetMgr; }

bool search(Asset *a) { return false; }

Asset *AssetMgr::GetAsset(Symbol name) const {
    std::map<Symbol, Asset *>::const_iterator asset = mAssets.find(name);
    if (asset != mAssets.end()) {
        return asset->second;
    }
    return NULL;
}

FORCE_LOCAL_INLINE
bool AssetMgr::HasAsset(Symbol asset) const { return GetAsset(asset) != NULL; }
END_FORCE_LOCAL_INLINE

AssetType AssetMgr::GetTypeFromName(Symbol name) const {
    AssetType type;
    if (name == none_bandana) {
        return kAssetType_Bandana;
    }
    if (name == none_earrings) {
        return kAssetType_Earrings;
    }
    if (name == none_eyebrows) {
        return kAssetType_Eyebrows;
    }
    if (name == none_facehair) {
        return kAssetType_FaceHair;
    }
    if (name == none_glasses) {
        return kAssetType_GlassesAndMasks;
    }
    if (name == none_hair) {
        return kAssetType_Hair;
    }
    if (name == none_hat) {
        return kAssetType_Hat;
    }
    if (name == none_piercings) {
        return kAssetType_Piercings;
    }
    if (name == none_rings) {
        return kAssetType_Rings;
    }
    if (name == none_wrists) {
        return kAssetType_Wrists;
    }

    Asset *pAsset = GetAsset(name);
    MILO_ASSERT(pAsset, 0x9f);
    return (AssetType)pAsset->mType;
}

void AssetMgr::GetEyebrows(std::vector<Symbol> &eyebrows, Symbol symbol) const {
    AssetGender gender = GetAssetGenderFromSymbol(symbol);
    FOREACH_POST (it, mAssets) {
        Asset *pAsset = it->second;
        MILO_ASSERT(pAsset, 0xaf);
        AssetType ty = pAsset->GetType();
        AssetGender g = pAsset->GetGender();
        if (ty == 5 && g == gender) {
            Symbol name = pAsset->GetName();
            eyebrows.push_back(name);
        }
    }
    std::sort(eyebrows.begin(), eyebrows.end());
}

int AssetMgr::GetEyebrowsCount(Symbol symbol) const {
    std::vector<Symbol> eyebrows;
    GetEyebrows(eyebrows, symbol);
    return eyebrows.size();
}

Symbol AssetMgr::StripFinish(Symbol symbol) {
    Asset *pAsset = GetAsset(symbol);
    if (!pAsset) {
        String string = symbol.mStr;
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
    mIconPaths.clear();
    DataArray *pAssetTypeIcons = SystemConfig("asset_type_icons");
    MILO_ASSERT(pAssetTypeIcons, 0x100);
    for (int i = 1; i < pAssetTypeIcons->Size(); i++) {
        DataArray *pEntry = pAssetTypeIcons->Array(i);
        MILO_ASSERT(pEntry, 0x106);
        MILO_ASSERT(pEntry->Size() == 2, 0x107);
        AssetType ty = GetAssetTypeFromSymbol(pEntry->Sym(0));
        String str = pEntry->Str(1);
        mIconPaths[ty] = str;
    }
}

void AssetMgr::AddAssets() {
    DataArray *pAssets = SystemConfig("assets");
    MILO_ASSERT(pAssets, 0x114);
    int assetIdx = 0;
    for (int i = 1; i < pAssets->Size(); i++) {
        DataArray *pConfig = pAssets->Array(i);
        MILO_ASSERT(pConfig, 0x11a);
        Asset *pAsset = new Asset(pConfig, assetIdx);
        MILO_ASSERT(pAsset, 0x11D);
        Symbol name = pAsset->GetName();
        if (HasAsset(name)) {
            MILO_WARN("(%s) has a duplicate entry in ui/customize/assets.dta", name.mStr);
            delete pAsset;
        } else {
            mAssets[name] = pAsset;
            assetIdx++;
        }
    }
}

void AssetMgr::VerifyAssets(const char *param1) {
    VerifyAssets(param1, gNullStr);
    VerifyAssets(param1, "male");
    VerifyAssets(param1, "female");
}

void AssetMgr::VerifyAssets(const char *path, const char *gender) {
    String s38(MakeString("char/main/%s", path));
    if (gender != gNullStr) {
        s38 += MakeString("/%s", gender);
    }
    String s44(s38);
    if (UsingCD()) {
        s44 += "/gen/*.milo_wii";
    } else {
        s44 += "/*.milo";
    }
    DataNode node = MakeFileList(s44.c_str(), true, nullptr);
    DataArray *pFiles = node.Array();
    MILO_ASSERT(pFiles, 0x152);
    for (int i = 1; i < pFiles->Size(); i++) {
        Symbol asset = pFiles->Node(i).Sym();
        if (asset != "female_torso_naked" && asset != "male_legs_naked"
            && asset != "female_legs_naked" && asset != "male_feet_naked"
            && asset != "female_feet_naked") {
            if (mAssets.find(asset) == mAssets.end()) {
                MILO_WARN(
                    "(%s/%s.milo) needs an entry in ui/customize/assets.dta",
                    s38,
                    asset.mStr
                );
            }
        }
    }
}

bool AssetMgr::EquipAsset(BandCharDesc *pBandCharDesc, Symbol s) {
    MILO_ASSERT(pBandCharDesc, 0x16F);
    AssetGender gender = GetAssetGenderFromSymbol(pBandCharDesc->Gender());
    Asset *pAsset = GetAsset(s);
    MILO_ASSERT(pAsset, 0x177);
    if (gender != pAsset->GetGender())
        return false;
    else {
        BandCharDesc::InstrumentOutfit outfit = pBandCharDesc->mInstruments;
        switch (pAsset->GetType()) {
        case kAssetType_None:
            break;
        case kAssetType_Bandana:
            pBandCharDesc->mOutfit.mFaceHair.mName = s;
            break;
        case kAssetType_Bass:
            outfit.mBass.mName = s;
            break;
        case kAssetType_Drum:
            outfit.mDrum.mName = s;
            break;
        case kAssetType_Earrings:
            pBandCharDesc->mOutfit.mEarrings.mName = s;
            break;
        case kAssetType_Eyebrows:
            pBandCharDesc->mOutfit.mEyebrows.mName = s;
            break;
        case kAssetType_FaceHair:
            pBandCharDesc->mOutfit.mFaceHair.mName = s;
            break;
        case kAssetType_Feet:
            pBandCharDesc->mOutfit.mFeet.mName = s;
            break;
        case kAssetType_GlassesAndMasks:
            pBandCharDesc->mOutfit.mGlasses.mName = s;
            break;
        case kAssetType_Gloves:
            pBandCharDesc->mOutfit.mHands.mName = s;
            break;
        case kAssetType_Guitar:
            outfit.mGuitar.mName = s;
            break;
        case kAssetType_Hair:
            pBandCharDesc->mOutfit.mHair.mName = s;
            break;
        case kAssetType_Hat:
            pBandCharDesc->mOutfit.mHair.mName = s;
            break;
        case kAssetType_Keyboard:
            outfit.mKeyboard.mName = s;
            break;
        case kAssetType_Legs:
            pBandCharDesc->mOutfit.mLegs.mName = s;
            break;
        case kAssetType_Mic:
            outfit.mMic.mName = s;
            break;
        case kAssetType_Piercings:
            pBandCharDesc->mOutfit.mPiercings.mName = s;
            break;
        case kAssetType_Rings:
            pBandCharDesc->mOutfit.mRings.mName = s;
            break;
        case kAssetType_Torso:
            pBandCharDesc->mOutfit.mTorso.mName = s;
            break;
        case kAssetType_Wrists:
            pBandCharDesc->mOutfit.mWrist.mName = s;
            break;
        default:
            MILO_ASSERT(false, 0x1BF);
            break;
        }
        return true;
    }
}

void AssetMgr::EquipAssets(LocalBandUser *user, const std::vector<Symbol> &assets) {
    TourCharLocal *pChar = user->GetCharLocal();
    MILO_ASSERT(pChar, 0x1cb);
    BandCharDesc *pBandCharDesc = pChar->GetBandCharDesc();
    MILO_ASSERT(pBandCharDesc, 0x1cf);
    bool equipped = false;
    FOREACH (it, assets) {
        if (EquipAsset(pBandCharDesc, *it)) {
            equipped = true;
        }
    }
    if (equipped) {
        ClosetMgr *pClosetMgr = ClosetMgr::GetClosetMgr();
        MILO_ASSERT(pClosetMgr, 0x1E4);
        pClosetMgr->PreviewCharacter(false, false);
    }
}
