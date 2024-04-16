#include "utl/Symbol.h"
#include "os/System.h"
#include "utl/KeylessHash.h"
#include "os/Debug.h"
#include "utl/StringTable.h"
#include "utl/PoolAlloc.h"
#include <new>

extern bool gLiteralSymbolStaticInitialization;
KeylessHash<const char*, const char*>* gHashTable;
StringTable* gStringTable;

Symbol::Symbol(const char* str){
    if(str == 0 || *str == '\0') mStr = gNullStr;
    else {
        if(gHashTable){
            const char* found = *gHashTable->Find(str);
            if(found) mStr = found;
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
        #pragma dont_inline on
        tmp = new KeylessHash<const char*, const char*>(hashSize, 0, 0, 0);
    }
    gHashTable = tmp;

}
