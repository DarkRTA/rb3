#include "utl/Symbol.h"
#include "os/System.h"
#include "utl/KeylessHash.h"
#include "os/Debug.h"
#include "utl/StringTable.h"
#include "utl/PoolAlloc.h"
#include <new>

static StringTable* gStringTable;
static KeylessHash<const char*, const char*>* gHashTable;
bool gLiteralSymbolStaticInitialization = false;

const char* SymbolCacheLookup(const char* cc){
    const char** found = gHashTable ? gHashTable->Find(cc) : 0;
    return found ? *found : 0;
}

// undefined4 SymbolCacheLookup(char *param_1)

// {
//   undefined4 *puVar1;
//   undefined4 uVar2;
//   char *local_8 [2];
  
//   if (gHashTable == (KeylessHash<> *)0x0) {
//     puVar1 = (undefined4 *)0x0;
//   }
//   else {
//     local_8[0] = param_1;
//     puVar1 = (undefined4 *)KeylessHash<>::Find(gHashTable,local_8);
//   }
//   if (puVar1 == (undefined4 *)0x0) {
//     uVar2 = 0;
//   }
//   else {
//     uVar2 = *puVar1;
//   }
//   return uVar2;
// }

Symbol::Symbol(const char* str){
    if(str == 0 || *str == '\0') mStr = gNullStr;
    else {
        if(gHashTable){
            const char** found = gHashTable->Find(str);
            if(found) mStr = *found;
            else {
                if(gLiteralSymbolStaticInitialization) mStr = str;
                else mStr = gStringTable->Add(str);

                if(100 < strlen(str) && MakeStringInitted()){
                    MILO_WARN("Huge symbol %s", str);
                }
                gHashTable->Insert(mStr);
            }
        }
        else MILO_FAIL("Can't instantiate symbols before Symbol::PreInit() has been called.\n");
    }
}

void Symbol::PreInit(int stringSize, int hashSize){
    KeylessHash<const char*, const char*>* tmp;
    if(!gStringTable){
        gStringTable = new StringTable(stringSize);
        tmp = new KeylessHash<const char*, const char*>(hashSize, 0, 0, 0);
    }
    gHashTable = tmp;

}
