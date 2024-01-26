#ifndef RB3_SYSTEM_HPP
#define RB3_SYSTEM_HPP
#include "symbol.hpp"
#include "data.hpp"

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
