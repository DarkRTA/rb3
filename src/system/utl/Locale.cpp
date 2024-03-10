#include "utl/Locale.h"
#include "os/Debug.h"

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

const char* Localize(Symbol token, bool* notify){
    const char* textStr = TheLocale.Localize(token, false);
    bool localized = textStr != 0;
    if(!localized){
        Locale::sIgnoreMissingText = textStr;
        if(Locale::sVerboseNotify != 0){
            MILO_WARN("\"%s\" needs localization", token);
        }
    }
    if(notify) *notify = localized;
    return textStr;
}
