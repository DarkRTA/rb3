#ifndef UTL_LOCALE_H
#define UTL_LOCALE_H
#include "utl/Symbol.h"
#include "obj/Data.h"
#include "utl/StringTable.h"

enum LocaleGender {
    LocaleGenderMasculine = 0,
    LocaleGenderFeminine = 1,
};

enum LocaleNumber {
    LocaleSingular = 0,
    LocalePlural = 1,
};

class LocaleChunkSort {
public:
    struct OrderedLocaleChunk {
        OrderedLocaleChunk() : node1(0), node2(0), node3(0) {}
        DataNode node1;
        DataNode node2;
        DataNode node3;
    };
};

class Locale {
public:
    Locale() : mSize(0), mSymTable(0), mStrTable(0), mStringData(0), 
        mUploadedFlags(0), mFile(), mNumFilesLoaded(0), mMagnuStrings(0) {}
    ~Locale();

    static bool sVerboseNotify;
    static const char* sIgnoreMissingText;
    static void Init();
    static void Terminate();

    int mSize;
    Symbol* mSymTable;
    const char** mStrTable;
    StringTable* mStringData;
    Symbol mFile;
    bool* mUploadedFlags;
    int mNumFilesLoaded;
    DataArray* mMagnuStrings;

    void SetMagnuStrings(DataArray*);
    bool FindDataIndex(Symbol, int&, bool) const;
    const char* Localize(Symbol, bool) const;
};

extern Locale TheLocale;

void SetLocaleVerboseNotify(bool);

void SyncReloadLocale();
const char* Localize(Symbol, bool*);
const char* LocalizeSeparatedInt(int);
const char* LocalizeFloat(const char*, float);

#endif
