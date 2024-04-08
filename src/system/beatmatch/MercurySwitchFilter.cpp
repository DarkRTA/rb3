#include "beatmatch/MercurySwitchFilter.h"
#include "rndobj/Overlay.h"
#include "os/Debug.h"

namespace {
    RndOverlay* gGuitarOverlay = 0;
}

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

void AnySignMercurySwitchFilter::Reset(){
    mNumFrames = 0;
    mLastOn = mWindow * -2.0f;
}
