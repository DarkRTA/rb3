/*
    Compile unit: C:\rockband2\system\src\beatmatch\MercurySwitchFilter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802EC140 -> 0x802EC694
*/
static class RndOverlay * gGuitarOverlay; // size: 0x4, address: 0x80A50628
// Range: 0x802EC140 -> 0x802EC474
class MercurySwitchFilter * NewMercurySwitchFilter(class DataArray * cfg /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__26AnySignMercurySwitchFilter;
    // -> struct [anonymous] __vt__26LowPassMercurySwitchFilter;
    // -> const char * gNullStr;
    // -> static class RndOverlay * gGuitarOverlay;
}

class AnySignMercurySwitchFilter : public MercurySwitchFilter {
    // total size: 0x18
    float mWindow; // offset 0x4, size 0x4
    float mLastOn; // offset 0x8, size 0x4
    int mNumFrames; // offset 0xC, size 0x4
    int mNumFramesThreshold; // offset 0x10, size 0x4
    float mThreshold; // offset 0x14, size 0x4
};
// Range: 0x802EC474 -> 0x802EC490
void AnySignMercurySwitchFilter::Reset() {}

// Range: 0x802EC490 -> 0x802EC54C
unsigned char AnySignMercurySwitchFilter::Poll(class AnySignMercurySwitchFilter * const this /* r5 */) {
    // Local variables
    unsigned char on; // r31

    // References
    // -> static class RndOverlay * gGuitarOverlay;
}

struct {
    // total size: 0x14
} __vt__26AnySignMercurySwitchFilter; // size: 0x14, address: 0x808CC57C
struct {
    // total size: 0x8
} __RTTI__26AnySignMercurySwitchFilter; // size: 0x8, address: 0x808CC5B8
class LowPassMercurySwitchFilter : public MercurySwitchFilter {
    // total size: 0x1C
    float mSensitivity; // offset 0x4, size 0x4
    float mOnThreshold; // offset 0x8, size 0x4
    float mOffThreshold; // offset 0xC, size 0x4
    unsigned char mState; // offset 0x10, size 0x1
    float mLastPoll; // offset 0x14, size 0x4
    float mAccum; // offset 0x18, size 0x4
};
// Range: 0x802EC54C -> 0x802EC558
void LowPassMercurySwitchFilter::Reset() {}

// Range: 0x802EC558 -> 0x802EC694
unsigned char LowPassMercurySwitchFilter::Poll(class LowPassMercurySwitchFilter * const this /* r31 */, float ms /* f31 */) {
    // Local variables
    float dt; // f4

    // References
    // -> static class RndOverlay * gGuitarOverlay;
}

struct {
    // total size: 0x14
} __vt__26LowPassMercurySwitchFilter; // size: 0x14, address: 0x808CC5C0
struct {
    // total size: 0x8
} __RTTI__26LowPassMercurySwitchFilter; // size: 0x8, address: 0x808CC600
struct {
    // total size: 0x14
} __vt__19MercurySwitchFilter; // size: 0x14, address: 0x808CC608
struct {
    // total size: 0x8
} __RTTI__19MercurySwitchFilter; // size: 0x8, address: 0x808CC630

