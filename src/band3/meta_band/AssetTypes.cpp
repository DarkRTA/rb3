#include "AssetTypes.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "system/os/Debug.h"

Symbol GetSymbolFromAssetType(AssetType asset_type) {
    Symbol symbol = gNullStr;
    switch (asset_type) {
        case 0:
            break;
        case 1:
            symbol = bandana;
            break;
        case 2:
            symbol = bass;
            break;
        case 3:
            symbol = drum;
            break;
        case 4:
            symbol = earrings;
            break;
        case 5:
            symbol = eyebrows;
            break;
        case 6:
            symbol = facehair;
            break;
        case 7:
            symbol = feet;
            break;
        case 8:
            symbol = glasses;
            break;
        case 9:
            symbol = hands;
            break;
        case 10:
            symbol = guitar;
            break;
        case 11:
            symbol = hair;
            break;
        case 12:
            symbol = hat;
            break;
        case 13:
            symbol = keyboard;
            break;
        case 14:
            symbol = legs;
            break;
        case 15:
            symbol = mic;
            break;
        case 16:
            symbol = piercings;
            break;
        case 17:
            symbol = rings;
            break;
        case 18:
            symbol = torso;
            break;
        case 19:
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
        return (AssetGender)0;
    }

    if (symbol == male) {
        return (AssetGender)1;
    } else if (symbol == female) {
        return (AssetGender)2;
    }

    MILO_WARN("AssetGender: (%s) not found.", symbol);
    return (AssetGender)0;
}

Symbol GetSymbolFromAssetBoutique(AssetBoutique boutique) {
    Symbol symbol = gNullStr;
    switch (boutique) {
        case 0:
            break;
        case 1:
            symbol = boutique_boss;
            break;
        case 2:
            symbol = boutique_romantic;
            break;
        case 3:
            symbol = boutique_scrapper;
            break;
        case 4:
            symbol = boutique_sheathed;
            break;
        case 5:
            symbol = boutique_showman;
            break;
        case 6:
            symbol = boutique_thatstore;
            break;
        case 7:
            symbol = boutique_warrior;
            break;
        case 8:
            symbol = boutique_tshirts;
            break;
        case 9:
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
    return (AssetBoutique)0;
}

const char *GetConfigNameFromAssetType(AssetType assetType) {
    const char *name = gNullStr;
    switch (assetType) {
        case 0:
            break;
        case 1:
            name = "facehair.cfg";
            break;
        case 2:
            name = "bass.cfg";
            break;
        case 3:
            name = "drum.cfg";
            break;
        case 4:
            name = "earrings.cfg";
            break;
        case 5:
            name = "eyebrows.cfg";
            break;
        case 6:
            name = "facehair.cfg";
            break;
        case 7:
            name = "feet.cfg";
            break;
        case 8:
            name = "glasses.cfg";
            break;
        case 9:
            name = "hands.cfg";
            break;
        case 10:
            name = "guitar.cfg";
            break;
        case 11:
            name = "hair.cfg";
            break;
        case 12:
            name = "hair.cfg";
            break;
        case 13:
            name = "keyboard.cfg";
            break;
        case 14:
            name = "legs.cfg";
            break;
        case 15:
            name = "mic.cfg";
            break;
        case 16:
            name = "piercings.cfg";
            break;
        case 17:
            name = "rings.cfg";
            break;
        case 18:
            name = "torso.cfg";
            break;
        case 19:
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
        case 0:
        case 2:
        case 3:
        case 10:
        case 13:
        case 14:
        case 15:
            break;
        case 1:
            asset = none_bandana;
            break;
        case 4:
            asset = none_earrings;
            break;
        case 5:
            asset = none_eyebrows;
            break;
        case 6:
            asset = none_facehair;
            break;
        case 7:
            if (assetGender == 1) {
                asset = male_feet_naked;
            } else if (assetGender == 2) {
                asset = female_feet_naked;
            }
            break;
        case 8:
            asset = none_glasses;
            break;
        case 9:
            if (assetGender == 1) {
                asset = male_hands_naked;
            } else if (assetGender == 2) {
                asset = female_hands_naked;
            }
            break;
        case 11:
            asset = none_hair;
            break;
        case 12:
            asset = none_hat;
            break;
        case 16:
            asset = none_piercings;
            break;
        case 17:
            asset = none_rings;
            break;
        case 18:
            if (assetGender == 1) {
                asset = male_torso_naked;
            } else if (assetGender == 2) {
                asset = femalebra_cotton;
            }
            break;
        case 19:
            asset = none_wrists;
            break;
        default:
            MILO_ASSERT(false, 0x17e);
    }
    return asset;
}

int GetPatchCategoryFromAssetType(AssetType assetType) {
    int result = 0;
    switch (assetType) {
        case 2:
            result = 0x400;
            break;
        case 3:
            result = 0x800;
            break;
        case 7:
            result = 4;
            break;
        case 10:
            result = 0x200;
            break;
        case 0xb:
            result = 8;
            break;
        case 0xd:
            result = 0x2000;
            break;
        case 0xe:
            result = 1;
            break;
        case 0xf:
            result = 0x1000;
            break;
        case 0x12:
            result = 1;
    }
    return result;
}

bool IsInstrumentAssetType(Symbol symbol) {
    if (symbol == guitar || symbol == bass || symbol == drum || symbol == mic || symbol == keyboard) {
        return true;
    }
    return false;
}
