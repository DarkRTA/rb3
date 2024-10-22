#ifndef METABAND_ASSETTYPES_H
#define METABAND_ASSETTYPES_H
#include "system/obj/Data.h"

enum AssetType {

};

enum AssetGender {};

enum AssetBoutique {};

Symbol GetSymbolFromAssetType(AssetType);
AssetType GetAssetTypeFromSymbol(Symbol);
AssetGender GetAssetGenderFromSymbol(Symbol);
Symbol GetSymbolFromAssetBoutique(AssetBoutique);
AssetBoutique GetAssetBoutiqueFromSymbol(Symbol);
const char* GetConfigNameFromAssetType(AssetType);
Symbol GetDefaultAssetFromAssetType(AssetType, AssetGender);
int GetPatchCategoryFromAssetType(AssetType);
bool IsInstrumentAssetType(Symbol);

#endif // METABAND_ASSETTYPES_H