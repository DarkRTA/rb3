#ifndef UTL_SYMBOLS_H
#define UTL_SYMBOLS_H
#include "utl/StringTable.h"
#include "utl/Symbol.h"

extern StringTable* gStringTable;
extern bool gLiteralSymbolStaticInitialization;

class BeginLiteralSymbols {
public:
    BeginLiteralSymbols(){
        if(gStringTable == 0){
            Symbol::PreInit(0x81700, 0x13c00);
        }
        gLiteralSymbolStaticInitialization = true;
    }
};

class EndLiteralSymbols {
public:
    EndLiteralSymbols(){
        gLiteralSymbolStaticInitialization = false;
    }

};



#endif
