#include "stringtablelocks.hpp"
#include "utl/StringTable.h"
#include "utl/Symbol.h"

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
