#include "beatmatch/MercurySwitchFilter.h"

MercurySwitchFilter* NewMercurySwitchFilter(DataArray* arr){
    gGuitarOverlay = RndOverlay::Find("guitar", true);
    if(arr->Sym(0) == "low_pass_filter"){
        return new LowPassMercurySwitchFilter(arr);
    }
    else if(arr->Sym(0) == "any_sign_filter"){
        return new AnySignMercurySwitchFilter(arr);
    }
    else {
        MILO_FAIL("no mercury switch filter called %s\n", arr->Sym(0));
        return 0;
    }
}
