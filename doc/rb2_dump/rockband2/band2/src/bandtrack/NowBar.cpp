/*
    Compile unit: C:\rockband2\band2\src\bandtrack\NowBar.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800226C8 -> 0x80022C3C
*/
// Range: 0x800226C8 -> 0x800227E0
void * NowBar::~NowBar(class NowBar * const this /* r28 */) {}

// Range: 0x800227E0 -> 0x800227E4
void NowBar::Poll() {}

static class Symbol miss; // size: 0x4, address: 0x80A48FE4
// Range: 0x800227E4 -> 0x8002292C
void NowBar::Miss(class NowBar * const this /* r31 */, int slot /* r28 */) {
    // Local variables
    class GemSmasher * smasher; // r29
    int i; // r28

    // References
    // -> static class Symbol miss;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8002292C -> 0x80022A20
void NowBar::PopSmasher(class NowBar * const this /* r29 */, int slot /* r30 */) {
    // Local variables
    class GemSmasher * * it; // r30
    class GemSmasher * smasher; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80022A20 -> 0x80022B10
void NowBar::SetSmasherGlowing(class NowBar * const this /* r29 */, int slot /* r31 */, unsigned char glowing /* r30 */) {
    // Local variables
    class GemSmasher * * it; // r31
    class GemSmasher * smasher; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80022B10 -> 0x80022BAC
void NowBar::StopBurning(class NowBar * const this /* r29 */) {
    // Local variables
    int slot; // r31
    class GemSmasher * smasher; // r30
}

// Range: 0x80022BAC -> 0x80022BB0
void NowBar::SetBonus() {}

// Range: 0x80022BB0 -> 0x80022C3C
class GemSmasher * NowBar::FindSmasher(const class NowBar * const this /* r30 */, int slot /* r1+0x8 */) {}

struct {
    // total size: 0x8
} __RTTI__PP10GemSmasher; // size: 0x8, address: 0x8086F0C8

