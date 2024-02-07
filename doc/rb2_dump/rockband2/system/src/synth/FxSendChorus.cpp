/*
    Compile unit: C:\rockband2\system\src\synth\FxSendChorus.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805734F4 -> 0x805743B8
*/
class DataArray * types; // size: 0x4, address: 0x80A54260
class Symbol name; // size: 0x4, address: 0x80A54268
static class Symbol quarter; // size: 0x4, address: 0x80A54270
class FxSendChorus : public FxSend {
    // total size: 0x70
protected:
    float mDelayMs; // offset 0x50, size 0x4
    float mRate; // offset 0x54, size 0x4
    float mDepth; // offset 0x58, size 0x4
    int mFeedbackPct; // offset 0x5C, size 0x4
    int mOffsetPct; // offset 0x60, size 0x4
    unsigned char mTempoSync; // offset 0x64, size 0x1
    class Symbol mSyncType; // offset 0x68, size 0x4
    float mTempo; // offset 0x6C, size 0x4
};
// Range: 0x805734F4 -> 0x805735A8
void * FxSendChorus::FxSendChorus(class FxSendChorus * const this /* r31 */) {
    // References
    // -> static class Symbol quarter;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__12FxSendChorus;
}

static int REV; // size: 0x4, address: 0x80A47688
// Range: 0x805735A8 -> 0x805735EC
void FxSendChorus::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805735EC -> 0x80573750
void FxSendChorus::Load(class FxSendChorus * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x80573750 -> 0x805737F0
void FxSendChorus::Copy(class FxSendChorus * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class FxSendChorus * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12FxSendChorus;
}

// Range: 0x805737F0 -> 0x80573A98
class DataNode FxSendChorus::Handle(class FxSendChorus * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A54278
static class Symbol _s; // size: 0x4, address: 0x80A54280
static class Symbol _s; // size: 0x4, address: 0x80A54288
static class Symbol _s; // size: 0x4, address: 0x80A54290
static class Symbol _s; // size: 0x4, address: 0x80A54298
static class Symbol _s; // size: 0x4, address: 0x80A542A0
static class Symbol _s; // size: 0x4, address: 0x80A542A8
static class Symbol _s; // size: 0x4, address: 0x80A542B0
// Range: 0x80573A98 -> 0x805743B8
unsigned char FxSendChorus::SyncProperty(class FxSendChorus * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
} __vt__12FxSendChorus; // size: 0x68, address: 0x8091BF58
struct {
    // total size: 0x8
} __RTTI__12FxSendChorus; // size: 0x8, address: 0x8091BFF0

