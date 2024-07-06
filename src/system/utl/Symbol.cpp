#include "utl/Symbol.h"
#include "os/System.h"
#include "utl/KeylessHash.h"
#include "os/Debug.h"
#include "utl/StringTable.h"
#include "utl/PoolAlloc.h"
#include "utl/DataPointMgr.h"
#include "obj/DataFunc.h"
#include "math/MathFuncs.h"
#include <algorithm>
#include <new>

static StringTable* gStringTable;
static KeylessHash<const char*, const char*>* gHashTable;
bool gLiteralSymbolStaticInitialization = true;

const char* SymbolCacheLookup(const char* cc){
    const char** found = gHashTable ? gHashTable->Find(cc) : 0;
    return found ? *found : 0;
}

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

#pragma push
#pragma pool_data off
void Symbol::UploadDebugStats(){
    static int gBigHashEntries;
    static int gBigHashStrings;
    static int gBigStringsUsed;
    static int gBigStringTableSize;
    if(UsingCD()){
        int curHashNumEntries = gHashTable->mNumEntries;
        int curHashSize = gHashTable->mSize;
        int curStrUsed = gStringTable->UsedSize();
        int curStrSize = gStringTable->Size();
        if(curHashNumEntries > gBigHashEntries ||
            curHashSize > gBigHashStrings ||
            curStrUsed > gBigStringsUsed ||
            curStrSize > gBigStringTableSize){

            gBigHashEntries = Max(gBigHashEntries, curHashNumEntries);
            gBigHashStrings = Max(gBigHashEntries, curHashSize);
            gBigStringsUsed = Max(gBigHashEntries, curStrUsed);
            gBigStringTableSize = Max(gBigHashEntries, curStrSize);

            SendDataPoint(MakeString("debug/%s/symbol", SystemConfig("rnd", "title")->Str(1)),"hashEntries",gBigHashEntries,
                "hashStrings", gBigHashStrings, "stringsUsed", gBigStringsUsed, "stringTableSize", gBigStringTableSize);
        }
    }
}
#pragma pop

// not sure where else to put this, it's only used here
struct Alpha {
    bool operator()(const char* ci, const char* cj) { return strcmp(ci, cj) < 0; }
} MyAlpha;

static DataNode PrintSymbolTable(DataArray* da){
    TheDebug << MakeString("Symbol table:\n");
    TheDebug << MakeString("%d / %d hashes\n", gHashTable->mNumEntries, gHashTable->mSize);
    TheDebug << MakeString("%d / %d strings\n", gStringTable->UsedSize(), gStringTable->Size());
    TheDebug << MakeString("adding 30%%, suggest Symbol::PreInit(%d, %d)\n", (int)(gStringTable->UsedSize() * 1.3f), (int)((gHashTable->mNumEntries << 1) * 1.3f));
    if(da->Size() > 1){
        std::vector<const char*> strvec;
        strvec.reserve(gHashTable->mNumEntries);
        for(const char** it = gHashTable->FirstFromStart(); it != 0; it = gHashTable->FirstFromNext(it)){
            // strvec.push_back(*it); // constness casted away?
        }
        std::sort(strvec.begin(), strvec.end(), MyAlpha);
        for(int i = 0; i < strvec.size(); i++){
            TheDebug << MakeString("%s\n", strvec[i]);
        }
    }
    return DataNode(0);
}

void Symbol::PreInit(int stringSize, int hashSize){
    if(!gStringTable){
        gStringTable = new StringTable(stringSize);
        gHashTable = new KeylessHash<const char*, const char*>(hashSize, 0, (const char*)-1, 0);
    }
}

void Symbol::Init(){
    if(!gStringTable) PreInit(560000, 80000);
    DataRegisterFunc("print_symbol_table", PrintSymbolTable);
}

void Symbol::Terminate(){}