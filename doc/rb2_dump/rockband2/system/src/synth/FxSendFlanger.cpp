/*
    Compile unit: C:\rockband2\system\src\synth\FxSendFlanger.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805745D8 -> 0x805754D4
*/
class DataArray * types; // size: 0x4, address: 0x80A542B8
class Symbol name; // size: 0x4, address: 0x80A542C0
static class Symbol quarter; // size: 0x4, address: 0x80A542C8
class FxSendFlanger : public FxSend {
    // total size: 0x70
protected:
    float mDelayMs; // offset 0x50, size 0x4
    float mRate; // offset 0x54, size 0x4
    int mDepthPct; // offset 0x58, size 0x4
    int mFeedbackPct; // offset 0x5C, size 0x4
    int mOffsetPct; // offset 0x60, size 0x4
    unsigned char mTempoSync; // offset 0x64, size 0x1
    class Symbol mSyncType; // offset 0x68, size 0x4
    float mTempo; // offset 0x6C, size 0x4
};
// Range: 0x805745D8 -> 0x80574688
void * FxSendFlanger::FxSendFlanger(class FxSendFlanger * const this /* r31 */) {
    // References
    // -> static class Symbol quarter;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__13FxSendFlanger;
}

static int REV; // size: 0x4, address: 0x80A47690
// Range: 0x80574688 -> 0x805746CC
void FxSendFlanger::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805746CC -> 0x80574868
void FxSendFlanger::Load(class FxSendFlanger * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x10
    float tmp; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x80574868 -> 0x80574908
void FxSendFlanger::Copy(class FxSendFlanger * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class FxSendFlanger * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13FxSendFlanger;
}

// Range: 0x80574908 -> 0x80574BB0
class DataNode FxSendFlanger::Handle(class FxSendFlanger * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A542D0
static class Symbol _s; // size: 0x4, address: 0x80A542D8
static class Symbol _s; // size: 0x4, address: 0x80A542E0
static class Symbol _s; // size: 0x4, address: 0x80A542E8
static class Symbol _s; // size: 0x4, address: 0x80A542F0
static class Symbol _s; // size: 0x4, address: 0x80A542F8
static class Symbol _s; // size: 0x4, address: 0x80A54300
static class Symbol _s; // size: 0x4, address: 0x80A54308
// Range: 0x80574BB0 -> 0x805754D4
unsigned char FxSendFlanger::SyncProperty(class FxSendFlanger * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
} __vt__13FxSendFlanger; // size: 0x68, address: 0x8091C228
struct {
    // total size: 0x8
} __RTTI__13FxSendFlanger; // size: 0x8, address: 0x8091C2C0

