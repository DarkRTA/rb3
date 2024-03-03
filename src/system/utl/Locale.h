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

class Locale {
public:
    Locale() : mSize(0), mSymTable(0), mStrTable(0), mStringData(0), 
        mUploadedFlags(0), mFile(), mNumFilesLoaded(0), mMagnuStrings(0) {}
    ~Locale();

    static bool sVerboseNotify;
    static char* sIgnoreMissingText;
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

void SetLocaleVerboseNotify(bool);

const char* Localize(Symbol, bool*);
const char* LocalizeSeparatedInt(int);
const char* LocalizeFloat(const char*, float);

#endif
