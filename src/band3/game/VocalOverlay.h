#pragma once
#include "utl/Str.h"

class VocalOverlay {
public:
    VocalOverlay();
    ~VocalOverlay();

    String mDisplayedString; // 0x0
    std::vector<String> mSingerStrings; // 0xc
    String mFooterString; // 0x18
    int unk24;
    int unk28;
};