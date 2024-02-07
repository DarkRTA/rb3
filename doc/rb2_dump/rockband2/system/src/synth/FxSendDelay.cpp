/*
    Compile unit: C:\rockband2\system\src\synth\FxSendDelay.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80577A28 -> 0x805786BC
*/
class DataArray * types; // size: 0x4, address: 0x80A543C8
class Symbol name; // size: 0x4, address: 0x80A543D0
static class Symbol eighth; // size: 0x4, address: 0x80A543D8
class FxSendDelay : public FxSend {
    // total size: 0x68
protected:
    float mDelayTime; // offset 0x50, size 0x4
    float mGain; // offset 0x54, size 0x4
    float mPingPongPct; // offset 0x58, size 0x4
    unsigned char mTempoSync; // offset 0x5C, size 0x1
    class Symbol mSyncType; // offset 0x60, size 0x4
    float mTempo; // offset 0x64, size 0x4
};
// Range: 0x80577A28 -> 0x80577AC0
void * FxSendDelay::FxSendDelay(class FxSendDelay * const this /* r31 */) {
    // References
    // -> static class Symbol eighth;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__11FxSendDelay;
}

// Range: 0x80577AC0 -> 0x80577B1C
void * FxSendDelay::~FxSendDelay(class FxSendDelay * const this /* r30 */) {}

static int REV; // size: 0x4, address: 0x80A476A8
// Range: 0x80577B1C -> 0x80577B60
void FxSendDelay::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80577B60 -> 0x80577C84
void FxSendDelay::Load(class FxSendDelay * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x80577C84 -> 0x80577D14
void FxSendDelay::Copy(class FxSendDelay * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class FxSendDelay * delay; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11FxSendDelay;
}

// Range: 0x80577D14 -> 0x80577FBC
class DataNode FxSendDelay::Handle(class FxSendDelay * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A543E0
static class Symbol _s; // size: 0x4, address: 0x80A543E8
static class Symbol _s; // size: 0x4, address: 0x80A543F0
static class Symbol _s; // size: 0x4, address: 0x80A543F8
static class Symbol _s; // size: 0x4, address: 0x80A54400
static class Symbol _s; // size: 0x4, address: 0x80A54408
// Range: 0x80577FBC -> 0x805786BC
unsigned char FxSendDelay::SyncProperty(class FxSendDelay * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
} __vt__11FxSendDelay; // size: 0x68, address: 0x8091C978
struct {
    // total size: 0x8
} __RTTI__11FxSendDelay; // size: 0x8, address: 0x8091CA08

