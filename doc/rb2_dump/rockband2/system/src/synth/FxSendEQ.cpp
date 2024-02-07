/*
    Compile unit: C:\rockband2\system\src\synth\FxSendEQ.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8057A0E4 -> 0x8057AE20
*/
class DataArray * types; // size: 0x4, address: 0x80A54478
// Range: 0x8057A0E4 -> 0x8057A150
void * FxSendEQ::FxSendEQ(class FxSendEQ * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8FxSendEQ;
}

// Range: 0x8057A150 -> 0x8057A1AC
void * FxSendEQ::~FxSendEQ(class FxSendEQ * const this /* r30 */) {}

static int REV; // size: 0x4, address: 0x80A476C0
// Range: 0x8057A1AC -> 0x8057A1F0
void FxSendEQ::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8057A1F0 -> 0x8057A2FC
void FxSendEQ::Load(class FxSendEQ * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x8057A2FC -> 0x8057A394
void FxSendEQ::Copy(class FxSendEQ * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class FxSendEQ * delay; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8FxSendEQ;
}

// Range: 0x8057A394 -> 0x8057A63C
class DataNode FxSendEQ::Handle(class FxSendEQ * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A54480
static class Symbol _s; // size: 0x4, address: 0x80A54488
static class Symbol _s; // size: 0x4, address: 0x80A54490
static class Symbol _s; // size: 0x4, address: 0x80A54498
static class Symbol _s; // size: 0x4, address: 0x80A544A0
static class Symbol _s; // size: 0x4, address: 0x80A544A8
static class Symbol _s; // size: 0x4, address: 0x80A544B0
// Range: 0x8057A63C -> 0x8057AE20
unsigned char FxSendEQ::SyncProperty(class FxSendEQ * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
} __vt__8FxSendEQ; // size: 0x68, address: 0x8091CF50

