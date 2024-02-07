/*
    Compile unit: C:\rockband2\system\src\synth\FxSendReverb.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805769A4 -> 0x80577864
*/
class DataArray * types; // size: 0x4, address: 0x80A54370
class Symbol name; // size: 0x4, address: 0x80A54378
static class Symbol generic; // size: 0x4, address: 0x80A54380
class FxSendReverb : public FxSend {
    // total size: 0x70
protected:
    class Symbol mEnvironmentPreset; // offset 0x50, size 0x4
    float mPreDelayMs; // offset 0x54, size 0x4
    float mHighCut; // offset 0x58, size 0x4
    float mLowCut; // offset 0x5C, size 0x4
    float mRoomSize; // offset 0x60, size 0x4
    float mDamping; // offset 0x64, size 0x4
    float mDiffusion; // offset 0x68, size 0x4
    float mEarlyLate; // offset 0x6C, size 0x4
};
// Range: 0x805769A4 -> 0x80576A50
void * FxSendReverb::FxSendReverb(class FxSendReverb * const this /* r31 */) {
    // References
    // -> static class Symbol generic;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__12FxSendReverb;
}

// Range: 0x80576A50 -> 0x80576AAC
void * FxSendReverb::~FxSendReverb(class FxSendReverb * const this /* r30 */) {}

static int REV; // size: 0x4, address: 0x80A476A0
// Range: 0x80576AAC -> 0x80576AF0
void FxSendReverb::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80576AF0 -> 0x80576C14
void FxSendReverb::Load(class FxSendReverb * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x80576C14 -> 0x80576CB4
void FxSendReverb::Copy(class FxSendReverb * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class FxSendReverb * reverb; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12FxSendReverb;
}

// Range: 0x80576CB4 -> 0x80576F5C
class DataNode FxSendReverb::Handle(class FxSendReverb * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A54388
static class Symbol _s; // size: 0x4, address: 0x80A54390
static class Symbol _s; // size: 0x4, address: 0x80A54398
static class Symbol _s; // size: 0x4, address: 0x80A543A0
static class Symbol _s; // size: 0x4, address: 0x80A543A8
static class Symbol _s; // size: 0x4, address: 0x80A543B0
static class Symbol _s; // size: 0x4, address: 0x80A543B8
static class Symbol _s; // size: 0x4, address: 0x80A543C0
// Range: 0x80576F5C -> 0x80577864
unsigned char FxSendReverb::SyncProperty(class FxSendReverb * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
} __vt__12FxSendReverb; // size: 0x68, address: 0x8091C730
struct {
    // total size: 0x8
} __RTTI__12FxSendReverb; // size: 0x8, address: 0x8091C7C8

