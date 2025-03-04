#pragma once
#include "system/obj/Data.h"

enum AssetType {
    kAssetType_None = 0,
    kAssetType_Bandana = 1,
    kAssetType_Bass = 2,
    kAssetType_Drum = 3,
    kAssetType_Earrings = 4,
    kAssetType_Eyebrows = 5,
    kAssetType_FaceHair = 6,
    kAssetType_Feet = 7,
    kAssetType_GlassesAndMasks = 8,
    kAssetType_Gloves = 9,
    kAssetType_Guitar = 10,
    kAssetType_Hair = 11,
    kAssetType_Hat = 12,
    kAssetType_Keyboard = 13,
    kAssetType_Legs = 14,
    kAssetType_Mic = 15,
    kAssetType_Piercings = 16,
    kAssetType_Rings = 17,
    kAssetType_Torso = 18,
    kAssetType_Wrists = 19
};

enum AssetGender {
    kAssetGender_None = 0,
    kAssetGender_Male = 1,
    kAssetGender_Female = 2
};

enum AssetBoutique {
    kAssetBoutique_None = 0,
    kAssetBoutique_Boss = 1,
    kAssetBoutique_Romantic = 2,
    kAssetBoutique_Scrapper = 3,
    kAssetBoutique_Sheathed = 4,
    kAssetBoutique_Showman = 5,
    kAssetBoutique_ThatStore = 6,
    kAssetBoutique_Warrior = 7,
    kAssetBoutique_TShirts = 8,
    kAssetBoutique_Premium = 9
};

Symbol GetSymbolFromAssetType(AssetType);
AssetType GetAssetTypeFromSymbol(Symbol);
AssetGender GetAssetGenderFromSymbol(Symbol);
Symbol GetSymbolFromAssetBoutique(AssetBoutique);
AssetBoutique GetAssetBoutiqueFromSymbol(Symbol);
const char *GetConfigNameFromAssetType(AssetType);
Symbol GetDefaultAssetFromAssetType(AssetType, AssetGender);
int GetPatchCategoryFromAssetType(AssetType);
bool IsInstrumentAssetType(Symbol);
