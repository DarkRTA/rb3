#include "stringtablelocks.hpp"
#include "stringtable.hpp"
#include "Symbol.h"

extern StringTable* gStringTable;
extern bool StringTableLocked;

StringTableLockBegin::StringTableLockBegin(){
    if(gStringTable == 0){
        Symbol::PreInit(0x81700, 0x13c00);
    }
    StringTableLocked = true;
}

StringTableLockEnd::StringTableLockEnd(){
    StringTableLocked = false;
}
