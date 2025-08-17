#pragma once 

#include "meta/StoreArtLoaderPanel.h"
#include "obj/Data.h"
#include "utl/Str.h"

class StoreMainPanel : StoreArtLoaderPanel {
    class NewReleaseEntry {
        public:
        String mStrName; // 0x0
        String mText1; // 0xC
        String mText2; // 0x18
        Symbol mRequiredOffer; // 0x24
    };

    public:
    StoreMainPanel(); 
    ~StoreMainPanel();
    //NewReleaseEntry

    DataArray *mPendingConfigData; // 0x6C
    float mTimeNextEvent; // 
};