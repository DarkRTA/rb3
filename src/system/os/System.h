#ifndef OS_SYSTEM_H
#define OS_SYSTEM_H
#include "obj/Data.h"
#include "utl/Symbol.h"

const char* gNullStr = "";

DataNode OnSystemLanguage(DataArray*);
DataNode OnSystemExec(DataArray*);
DataNode OnUsingCD(DataArray*);
DataNode OnSupportedLanguages(DataArray*);

enum Platform {
    kPlatformNone = 0,
    kPlatformPS2 = 1,
    kPlatformXBox = 2,
    kPlatformPC = 3,
    kPlatformPS3 = 4,
    kPlatformWii = 5,
};

Symbol PlatformSymbol(Platform);

void SetUsingCD(bool);
DataArray* SystemConfig();
DataArray* SystemConfig(Symbol);
DataArray* SystemConfig(Symbol, Symbol);
DataArray* SystemConfig(Symbol, Symbol, Symbol);
DataArray* SystemConfig(Symbol, Symbol, Symbol, Symbol);
DataArray* SystemConfig(Symbol, Symbol, Symbol, Symbol, Symbol);
Symbol SystemLanguage();
DataArray* SupportedLanguages(bool);
bool IsSupportedLanguage(Symbol, bool);
int SystemExec();

#endif
