#ifndef OS_SYSTEM_H
#define OS_SYSTEM_H
#include "Symbol.h"
#include "Data.h"

DataNode OnSystemLanguage(DataArray*);
DataNode OnSystemExec(DataArray*);
DataNode OnUsingCD(DataArray*);
DataNode OnSupportedLanguages(DataArray*);

enum Platform {
    PLATFORM_NULL, PLATFORM_PS2, PLATFORM_XBOX, PLATFORM_PC, PLATFORM_PS3, PLATFORM_WII
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
