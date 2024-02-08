#ifndef UTL_LOCALE_H
#define UTL_LOCALE_H
#include "Symbol.h"
#include "Data.h"

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
