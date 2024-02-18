#ifndef UTL_LOCALE_H
#define UTL_LOCALE_H
#include "obj/Data.h"
#include "utl/Symbol.h"

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
    Locale();
    ~Locale();

    static bool sVerboseNotify;

    int unk0;
    int unk4;
    int unk8;
    int unkc;
    Symbol unk10;
    int unk14;
};

DataNode DataSetLocaleVerboseNotify(DataArray*);
void SetLocaleVerboseNotify(bool);
char* LocalizeSeparatedInt(int);

#endif

// class Locale {
//     // total size: 0x18
// protected:
//     int mSize; // offset 0x0, size 0x4
//     class Symbol * mSymTable; // offset 0x4, size 0x4
//     const char * * mStrTable; // offset 0x8, size 0x4
//     class StringTable * mStringData; // offset 0xC, size 0x4
//     class Symbol mFile; // offset 0x10, size 0x4
//     int mNumFilesLoaded; // offset 0x14, size 0x4
// };
