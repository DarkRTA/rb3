#ifndef RB3_LOCALE_HPP
#define RB3_LOCALE_HPP
#include "Symbol.h"
#include "Data.h"

enum LocaleGender { GenMale, GenFemale };
enum LocaleNumber { n1, n2, n3 };

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
