#ifndef RB3_SYSTEM_HPP
#define RB3_SYSTEM_HPP
#include "symbol.hpp"
#include "data.hpp"

void SetUsingCD(bool);
DataArray* SystemConfig();
DataArray* SystemConfig(Symbol);
DataArray* SystemConfig(Symbol, Symbol);
DataArray* SystemConfig(Symbol, Symbol, Symbol);
DataArray* SystemConfig(Symbol, Symbol, Symbol, Symbol);
DataArray* SystemConfig(Symbol, Symbol, Symbol, Symbol, Symbol);
Symbol SystemLanguage();

#endif
