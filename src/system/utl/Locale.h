#pragma once
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

    static void Sort(OrderedLocaleChunk *, int);
};

class Locale {
public:
    Locale()
        : mSize(0), mSymTable(0), mStrTable(0), mStringData(0), mUploadedFlags(0),
          mFile(), mNumFilesLoaded(0), mMagnuStrings(0) {}
    ~Locale();

    void Init();
    void Terminate();

    static bool sVerboseNotify;
    static const char *sIgnoreMissingText;

    int mSize; // 0x0
    Symbol *mSymTable; // 0x4
    const char **mStrTable; // 0x8
    StringTable *mStringData; // 0xc
    Symbol mFile; // 0x10
    int mNumFilesLoaded; // 0x14
    bool *mUploadedFlags; // 0x18
    DataArray *mMagnuStrings; // 0x1c

    void SetMagnuStrings(DataArray *);
    bool FindDataIndex(Symbol, int &, bool) const;
    const char *Localize(Symbol, bool) const;
};

extern Locale TheLocale;

inline void SetLocaleVerboseNotify(bool set) { Locale::sVerboseNotify = set; }

void SyncReloadLocale();
const char *Localize(Symbol, bool *);
const char *LocalizeSeparatedInt(int);
const char *LocalizeFloat(const char *, float);
