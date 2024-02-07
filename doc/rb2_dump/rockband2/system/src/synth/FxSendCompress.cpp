/*
    Compile unit: C:\rockband2\system\src\synth\FxSendCompress.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8057907C -> 0x80579F20
*/
class DataArray * types; // size: 0x4, address: 0x80A54428
class Symbol name; // size: 0x4, address: 0x80A54430
class FxSendCompress : public FxSend {
    // total size: 0x70
protected:
    float mThresholdDB; // offset 0x50, size 0x4
    float mRatio; // offset 0x54, size 0x4
    float mOutputLevel; // offset 0x58, size 0x4
    float mAttack; // offset 0x5C, size 0x4
    float mRelease; // offset 0x60, size 0x4
    float mExpRatio; // offset 0x64, size 0x4
    float mExpAttack; // offset 0x68, size 0x4
    float mExpRelease; // offset 0x6C, size 0x4
};
// Range: 0x8057907C -> 0x805790F0
void * FxSendCompress::FxSendCompress(class FxSendCompress * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14FxSendCompress;
}

// Range: 0x805790F0 -> 0x8057914C
void * FxSendCompress::~FxSendCompress(class FxSendCompress * const this /* r30 */) {}

static int REV; // size: 0x4, address: 0x80A476B8
// Range: 0x8057914C -> 0x80579190
void FxSendCompress::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80579190 -> 0x805792E8
void FxSendCompress::Load(class FxSendCompress * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0xC
    float tmp; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x805792E8 -> 0x80579388
void FxSendCompress::Copy(class FxSendCompress * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class FxSendCompress * delay; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14FxSendCompress;
}

// Range: 0x80579388 -> 0x80579630
class DataNode FxSendCompress::Handle(class FxSendCompress * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A54438
static class Symbol _s; // size: 0x4, address: 0x80A54440
static class Symbol _s; // size: 0x4, address: 0x80A54448
static class Symbol _s; // size: 0x4, address: 0x80A54450
static class Symbol _s; // size: 0x4, address: 0x80A54458
static class Symbol _s; // size: 0x4, address: 0x80A54460
static class Symbol _s; // size: 0x4, address: 0x80A54468
static class Symbol _s; // size: 0x4, address: 0x80A54470
// Range: 0x80579630 -> 0x80579F20
unsigned char FxSendCompress::SyncProperty(class FxSendCompress * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
} __vt__14FxSendCompress; // size: 0x68, address: 0x8091CD30
struct {
    // total size: 0x8
} __RTTI__14FxSendCompress; // size: 0x8, address: 0x8091CDC8

