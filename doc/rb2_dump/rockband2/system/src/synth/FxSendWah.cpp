/*
    Compile unit: C:\rockband2\system\src\synth\FxSendWah.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8057B784 -> 0x8057CA08
*/
class DataArray * types; // size: 0x4, address: 0x80A544C8
class Symbol name; // size: 0x4, address: 0x80A544D0
class FxSendWah : public FxSend {
    // total size: 0x80
protected:
    float mResonance; // offset 0x50, size 0x4
    float mUpperFreq; // offset 0x54, size 0x4
    float mLowerFreq; // offset 0x58, size 0x4
    float mLfoFreq; // offset 0x5C, size 0x4
    float mMagic; // offset 0x60, size 0x4
    float mDistAmount; // offset 0x64, size 0x4
    unsigned char mAutoWah; // offset 0x68, size 0x1
    float mFrequency; // offset 0x6C, size 0x4
    unsigned char mTempoSync; // offset 0x70, size 0x1
    class Symbol mSyncType; // offset 0x74, size 0x4
    float mTempo; // offset 0x78, size 0x4
    float mBeatFrac; // offset 0x7C, size 0x4
};
static int REV; // size: 0x4, address: 0x80A476C8
// Range: 0x8057B784 -> 0x8057B7C8
void FxSendWah::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8057B7C8 -> 0x8057B950
void FxSendWah::Load(class FxSendWah * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x8057B950 -> 0x8057BA08
void FxSendWah::Copy(class FxSendWah * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class FxSendWah * w; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9FxSendWah;
}

// Range: 0x8057BA08 -> 0x8057BCB0
class DataNode FxSendWah::Handle(class FxSendWah * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A544D8
static class Symbol _s; // size: 0x4, address: 0x80A544E0
static class Symbol _s; // size: 0x4, address: 0x80A544E8
static class Symbol _s; // size: 0x4, address: 0x80A544F0
static class Symbol _s; // size: 0x4, address: 0x80A544F8
static class Symbol _s; // size: 0x4, address: 0x80A54500
static class Symbol _s; // size: 0x4, address: 0x80A54508
static class Symbol _s; // size: 0x4, address: 0x80A54510
static class Symbol _s; // size: 0x4, address: 0x80A54518
static class Symbol _s; // size: 0x4, address: 0x80A54520
static class Symbol _s; // size: 0x4, address: 0x80A54528
static class Symbol _s; // size: 0x4, address: 0x80A54530
// Range: 0x8057BCB0 -> 0x8057CA08
unsigned char FxSendWah::SyncProperty(class FxSendWah * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x68
} __vt__9FxSendWah; // size: 0x68, address: 0x8091D288
struct {
    // total size: 0x8
} __RTTI__9FxSendWah; // size: 0x8, address: 0x8091D318

