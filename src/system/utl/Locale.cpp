#include "utl/Locale.h"

Locale TheLocale;

Locale::~Locale(){
    if(mMagnuStrings){
        mMagnuStrings->Release();
        mMagnuStrings = 0;
    }
}

void Locale::SetMagnuStrings(DataArray* da){
    if(mMagnuStrings){
        mMagnuStrings->Release();
        mMagnuStrings = 0;
    }
    mMagnuStrings = da;
}
