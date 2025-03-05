#include "AssetTypes.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "system/os/Debug.h"

Symbol GetSymbolFromAssetType(AssetType asset_type) {
    Symbol symbol = gNullStr;
    switch (asset_type) {
    case kAssetType_None:
        break;
    case kAssetType_Bandana:
        symbol = bandana;
        break;
    case kAssetType_Bass:
        symbol = bass;
        break;
    case kAssetType_Drum:
        symbol = drum;
        break;
    case kAssetType_Earrings:
        symbol = earrings;
        break;
    case kAssetType_Eyebrows:
        symbol = eyebrows;
        break;
    case kAssetType_FaceHair:
        symbol = facehair;
        break;
    case kAssetType_Feet:
        symbol = feet;
        break;
    case kAssetType_GlassesAndMasks:
        symbol = glasses;
        break;
    case kAssetType_Gloves:
        symbol = hands;
        break;
    case kAssetType_Guitar:
        symbol = guitar;
        break;
    case kAssetType_Hair:
        symbol = hair;
        break;
    case kAssetType_Hat:
        symbol = hat;
        break;
    case kAssetType_Keyboard:
        symbol = keyboard;
        break;
    case kAssetType_Legs:
        symbol = legs;
        break;
    case kAssetType_Mic:
        symbol = mic;
        break;
    case kAssetType_Piercings:
        symbol = piercings;
        break;
    case kAssetType_Rings:
        symbol = rings;
        break;
    case kAssetType_Torso:
        symbol = torso;
        break;
    case kAssetType_Wrists:
        symbol = wrist;
        break;
    default:
        MILO_ASSERT(false, 0x61);
    }
    return symbol;
}

AssetType GetAssetTypeFromSymbol(Symbol symbol) {
    for (int i = 0; i < 20; i++) {
        Symbol assetType = GetSymbolFromAssetType((AssetType)i);
        if (assetType == symbol) {
            return (AssetType)i;
        }
    }
    MILO_WARN("AssetType: (%s) not found.", symbol);
    return (AssetType)0;
}

AssetGender GetAssetGenderFromSymbol(Symbol symbol) {
    if (symbol == gNullStr) {
        return kAssetGender_None;
    }

    if (symbol == male) {
        return kAssetGender_Male;
    } else if (symbol == female) {
        return kAssetGender_Female;
    }

    MILO_WARN("AssetGender: (%s) not found.", symbol);
    return kAssetGender_None;
}

Symbol GetSymbolFromAssetBoutique(AssetBoutique boutique) {
    Symbol symbol = gNullStr;
    switch (boutique) {
    case kAssetBoutique_None:
        break;
    case kAssetBoutique_Boss:
        symbol = boutique_boss;
        break;
    case kAssetBoutique_Romantic:
        symbol = boutique_romantic;
        break;
    case kAssetBoutique_Scrapper:
        symbol = boutique_scrapper;
        break;
    case kAssetBoutique_Sheathed:
        symbol = boutique_sheathed;
        break;
    case kAssetBoutique_Showman:
        symbol = boutique_showman;
        break;
    case kAssetBoutique_ThatStore:
        symbol = boutique_thatstore;
        break;
    case kAssetBoutique_Warrior:
        symbol = boutique_warrior;
        break;
    case kAssetBoutique_TShirts:
        symbol = boutique_tshirts;
        break;
    case kAssetBoutique_Premium:
        symbol = boutique_premium;
        break;
    default:
        MILO_ASSERT(false, 0xb6);
    }
    return symbol;
}

AssetBoutique GetAssetBoutiqueFromSymbol(Symbol symbol) {
    for (int i = 0; i < 10; i++) {
        Symbol assetType = GetSymbolFromAssetBoutique((AssetBoutique)i);
        if (assetType == symbol) {
            return (AssetBoutique)i;
        }
    }
    MILO_WARN("AssetBoutique: (%s) not found.", symbol);
    return kAssetBoutique_None;
}

const char *GetConfigNameFromAssetType(AssetType assetType) {
    const char *name = gNullStr;
    switch (assetType) {
    case kAssetType_None:
        break;
    case kAssetType_Bandana:
        name = "facehair.cfg";
        break;
    case kAssetType_Bass:
        name = "bass.cfg";
        break;
    case kAssetType_Drum:
        name = "drum.cfg";
        break;
    case kAssetType_Earrings:
        name = "earrings.cfg";
        break;
    case kAssetType_Eyebrows:
        name = "eyebrows.cfg";
        break;
    case kAssetType_FaceHair:
        name = "facehair.cfg";
        break;
    case kAssetType_Feet:
        name = "feet.cfg";
        break;
    case kAssetType_GlassesAndMasks:
        name = "glasses.cfg";
        break;
    case kAssetType_Gloves:
        name = "hands.cfg";
        break;
    case kAssetType_Guitar:
        name = "guitar.cfg";
        break;
    case kAssetType_Hair:
        name = "hair.cfg";
        break;
    case kAssetType_Hat:
        name = "hair.cfg";
        break;
    case kAssetType_Keyboard:
        name = "keyboard.cfg";
        break;
    case kAssetType_Legs:
        name = "legs.cfg";
        break;
    case kAssetType_Mic:
        name = "mic.cfg";
        break;
    case kAssetType_Piercings:
        name = "piercings.cfg";
        break;
    case kAssetType_Rings:
        name = "rings.cfg";
        break;
    case kAssetType_Torso:
        name = "torso.cfg";
        break;
    case kAssetType_Wrists:
        name = "wrist.cfg";
        break;
    default:
        MILO_ASSERT(false, 0x10f);
    }
    return name;
}

Symbol GetDefaultAssetFromAssetType(AssetType assetType, AssetGender assetGender) {
    Symbol asset = gNullStr;
    switch (assetType) {
    case kAssetType_None:
    case kAssetType_Bass:
    case kAssetType_Drum:
    case kAssetType_Guitar:
    case kAssetType_Keyboard:
    case kAssetType_Legs:
    case kAssetType_Mic:
        break;
    case kAssetType_Bandana:
        asset = none_bandana;
        break;
    case kAssetType_Earrings:
        asset = none_earrings;
        break;
    case kAssetType_Eyebrows:
        asset = none_eyebrows;
        break;
    case kAssetType_FaceHair:
        asset = none_facehair;
        break;
    case kAssetType_Feet:
        if (assetGender == kAssetGender_Male) {
            asset = male_feet_naked;
        } else if (assetGender == kAssetGender_Female) {
            asset = female_feet_naked;
        }
        break;
    case kAssetType_GlassesAndMasks:
        asset = none_glasses;
        break;
    case kAssetType_Gloves:
        if (assetGender == kAssetGender_Male) {
            asset = male_hands_naked;
        } else if (assetGender == kAssetGender_Female) {
            asset = female_hands_naked;
        }
        break;
    case kAssetType_Hair:
        asset = none_hair;
        break;
    case kAssetType_Hat:
        asset = none_hat;
        break;
    case kAssetType_Piercings:
        asset = none_piercings;
        break;
    case kAssetType_Rings:
        asset = none_rings;
        break;
    case kAssetType_Torso:
        if (assetGender == kAssetGender_Male) {
            asset = male_torso_naked;
        } else if (assetGender == kAssetGender_Female) {
            asset = femalebra_cotton;
        }
        break;
    case kAssetType_Wrists:
        asset = none_wrists;
        break;
    default:
        MILO_ASSERT(false, 0x17e);
    }
    return asset;
}

BandCharDesc::Patch::Category GetPatchCategoryFromAssetType(AssetType assetType) {
    BandCharDesc::Patch::Category result = BandCharDesc::Patch::kPatchNone;
    switch (assetType) {
    case kAssetType_Bass:
        result = BandCharDesc::Patch::kPatchBass;
        break;
    case kAssetType_Drum:
        result = BandCharDesc::Patch::kPatchDrum;
        break;
    case kAssetType_Feet:
        result = BandCharDesc::Patch::kPatchFeet;
        break;
    case kAssetType_Guitar:
        result = BandCharDesc::Patch::kPatchGuitar;
        break;
    case kAssetType_Hair:
        result = BandCharDesc::Patch::kPatchHair;
        break;
    case kAssetType_Keyboard:
        result = BandCharDesc::Patch::kPatchKeyboard;
        break;
    case kAssetType_Legs:
        result = BandCharDesc::Patch::kPatchTorso; // should be legs, i think this was a
                                                   // bug
        break;
    case kAssetType_Mic:
        result = BandCharDesc::Patch::kPatchMic;
        break;
    case kAssetType_Torso:
        result = BandCharDesc::Patch::kPatchTorso;
    }
    return result;
}

bool IsInstrumentAssetType(Symbol symbol) {
    if (symbol == guitar || symbol == bass || symbol == drum || symbol == mic
        || symbol == keyboard) {
        return true;
    }
    return false;
}
