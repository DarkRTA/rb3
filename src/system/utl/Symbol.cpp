#include "utl/Symbol.h"
#include "os/System.h"
#include "utl/KeylessHash.h"
#include "os/Debug.h"
#include "utl/StringTable.h"
#include "utl/PoolAlloc.h"
#include "utl/DataPointMgr.h"
#include "obj/DataFunc.h"
#include "math/Utl.h"
#include <algorithm>
#include <new>

StringTable *gStringTable;
static KeylessHash<const char *, const char *> *gHashTable;
bool gLiteralSymbolStaticInitialization = true;

const char *SymbolCacheLookup(const char *cc) {
    const char **found = gHashTable ? gHashTable->Find(cc) : 0;
    return found ? *found : 0;
}

Symbol::Symbol(const char *str) {
    if (str == 0 || *str == '\0')
        mStr = gNullStr;
    else {
        if (gHashTable) {
            const char **found = gHashTable->Find(str);
            if (found)
                mStr = *found;
            else {
                if (gLiteralSymbolStaticInitialization)
                    mStr = str;
                else
                    mStr = gStringTable->Add(str);
#ifdef MILO_DEBUG
                if (100 < strlen(str) && MakeStringInitted()) {
                    MILO_WARN("Huge symbol %s", str);
                }
#endif
                gHashTable->Insert(mStr);
            }
        } else
            MILO_FAIL(
                "Can't instantiate symbols before Symbol::PreInit() has been called.\n"
            );
    }
}

#pragma push
#pragma pool_data off
void Symbol::UploadDebugStats() {
    static int gBigHashEntries;
    static int gBigHashStrings;
    static int gBigStringsUsed;
    static int gBigStringTableSize;
    if (UsingCD()) {
        int curHashNumEntries = gHashTable->mNumEntries;
        int curHashSize = gHashTable->mSize;
        int curStrUsed = gStringTable->UsedSize();
        int curStrSize = gStringTable->Size();
        if (curHashNumEntries > gBigHashEntries || curHashSize > gBigHashStrings
            || curStrUsed > gBigStringsUsed || curStrSize > gBigStringTableSize) {
            gBigHashEntries = Max(gBigHashEntries, curHashNumEntries);
            gBigHashStrings = Max(gBigHashEntries, curHashSize);
            gBigStringsUsed = Max(gBigHashEntries, curStrUsed);
            gBigStringTableSize = Max(gBigHashEntries, curStrSize);

            SendDataPoint(
                MakeString("debug/%s/symbol", SystemConfig("rnd", "title")->Str(1)),
                "hashEntries",
                gBigHashEntries,
                "hashStrings",
                gBigHashStrings,
                "stringsUsed",
                gBigStringsUsed,
                "stringTableSize",
                gBigStringTableSize
            );
        }
    }
}
#pragma pop

// not sure where else to put this, it's only used here
struct Alpha {
    bool operator()(const char *ci, const char *cj) { return strcmp(ci, cj) < 0; }
};

static DataNode PrintSymbolTable(DataArray *da) {
    MILO_LOG("Symbol table:\n");
    MILO_LOG("%d / %d hashes\n", gHashTable->UsedSize(), gHashTable->Size());
    MILO_LOG("%d / %d strings\n", gStringTable->UsedSize(), gStringTable->Size());
    MILO_LOG(
        "adding 30%%, suggest Symbol::PreInit(%d, %d)\n",
        (int)(gStringTable->UsedSize() * 1.3f),
        (int)((gHashTable->UsedSize() << 1) * 1.3f)
    );
    if (da->Size() > 1) {
        std::vector<const char *> strvec;
        strvec.reserve(gHashTable->UsedSize());
        for (const char **it = gHashTable->Begin(); it != 0; it = gHashTable->Next(it)) {
            strvec.push_back(*it);
        }
        std::sort(strvec.begin(), strvec.end(), Alpha());
        for (int i = 0; i < strvec.size(); i++) {
            MILO_LOG("%s\n", strvec[i]);
        }
    }
    return DataNode(0);
}

void Symbol::PreInit(int stringSize, int hashSize) {
    if (!gStringTable) {
        gStringTable = new StringTable(stringSize);
        gHashTable =
            new KeylessHash<const char *, const char *>(hashSize, 0, (const char *)-1, 0);
    }
}

void Symbol::Init() {
    if (!gStringTable)
        PreInit(560000, 80000);
    DataRegisterFunc("print_symbol_table", PrintSymbolTable);
}

void Symbol::Terminate() {}
