#pragma once
#include "os/Timer.h"
#include "sdk/RVL_SDK/revolution/tpl/TPL.h"
#include "system/utl/MemMgr.h"

class CustomSplash {
public:
    CustomSplash();
    ~CustomSplash();

    Timer mTimer1; // 0x0
    Timer mTimer2; // 0x30
    float unk_60; // 0x60
    unsigned int unk_64; // 0x64
    TPLPalette *mPalette; // 0x68
    GXTexObj *mGXTexObj; // 0x6C

    // no clue what this is
    char unknownBytes[0x41c];

    char unk_48c; // 0x48C
    char unk_48d; // 0x48D
    char unk_48e; // 0x48E
    char unk_48f; // 0x48F
    char unk_490; // 0x490
};