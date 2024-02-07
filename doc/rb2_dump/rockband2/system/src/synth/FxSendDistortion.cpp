/*
    Compile unit: C:\rockband2\system\src\synth\FxSendDistortion.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80578880 -> 0x80578EB8
*/
class DataArray * types; // size: 0x4, address: 0x80A54410
class Symbol name; // size: 0x4, address: 0x80A54418
class FxSendDistortion : public FxSend {
    // total size: 0x54
protected:
    float mDrive; // offset 0x50, size 0x4
};
// Range: 0x80578880 -> 0x805788C4
void * FxSendDistortion::FxSendDistortion(class FxSendDistortion * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__16FxSendDistortion;
}

// Range: 0x805788C4 -> 0x80578920
void * FxSendDistortion::~FxSendDistortion(class FxSendDistortion * const this /* r30 */) {}

static int REV; // size: 0x4, address: 0x80A476B0
// Range: 0x80578920 -> 0x80578964
void FxSendDistortion::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80578964 -> 0x80578A10
void FxSendDistortion::Load(class FxSendDistortion * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x80578A10 -> 0x80578A78
void FxSendDistortion::Copy(class FxSendDistortion * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class FxSendDistortion * distortion; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16FxSendDistortion;
}

// Range: 0x80578A78 -> 0x80578D20
class DataNode FxSendDistortion::Handle(class FxSendDistortion * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A54420
// Range: 0x80578D20 -> 0x80578EB8
unsigned char FxSendDistortion::SyncProperty(class FxSendDistortion * const this /* r31 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r30 */, enum PropOp _op /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x68
} __vt__16FxSendDistortion; // size: 0x68, address: 0x8091CBA0
struct {
    // total size: 0x8
} __RTTI__16FxSendDistortion; // size: 0x8, address: 0x8091CC38

