#include "Locale.h"

Locale TheLocale;

DataNode DataSetLocaleVerboseNotify(DataArray* da){
    SetLocaleVerboseNotify(da->GetIntAtIndex(1) != 0);
    return DataNode(0);
}

void SetLocaleVerboseNotify(bool b){
    Locale::sVerboseNotify = b;
}

Locale::Locale() : unk0(0), unk4(0), unk8(0), unkc(0), unk10(), unk14(0) {

}

Locale::~Locale(){

}
