/*
    Compile unit: C:\rockband2\system\src\synth\FxSend.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80571C6C -> 0x80572B30
*/
class DataArray * types; // size: 0x4, address: 0x80A54210
class Symbol name; // size: 0x4, address: 0x80A54218
// Range: 0x80571C6C -> 0x80571CF4
void * FxSend::FxSend(class FxSend * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__31ObjOwnerPtr<6FxSend,9ObjectDir>;
    // -> struct [anonymous] __vt__6FxSend;
}

// Range: 0x80571CF4 -> 0x80571D7C
void * FxSend::~FxSend(class FxSend * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__31ObjOwnerPtr<6FxSend,9ObjectDir>;
}

// Range: 0x80571D7C -> 0x80571E08
void FxSend::SetNextSend(class FxSend * const this /* r30 */, class FxSend * send /* r31 */) {}

// Range: 0x80571E08 -> 0x80571E68
void FxSend::SetStage(class FxSend * const this /* r30 */, int n /* r31 */) {}

// Range: 0x80571E68 -> 0x80571E80
void FxSend::SetChannels() {}

// Range: 0x80571E80 -> 0x80571F88
void FxSend::RebuildChain(class FxSend * const this /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
    class ObjRef * ref; // r31
    class FxSend * refSend; // r0
    class Sfx * sfx; // r0

    // References
    // -> struct [anonymous] __RTTI__3Sfx;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6FxSend;
}

// Range: 0x80571F88 -> 0x8057205C
void FxSend::Copy(class FxSend * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class FxSend * send; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6FxSend;
}

// Range: 0x8057205C -> 0x80572070
void FxSend::SetInputGain() {}

static class Symbol _s; // size: 0x4, address: 0x80A54220
// Range: 0x80572070 -> 0x805723F8
class DataNode FxSend::Handle(class FxSend * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A54228
static class Symbol _s; // size: 0x4, address: 0x80A54230
static class Symbol _s; // size: 0x4, address: 0x80A54238
static class Symbol _s; // size: 0x4, address: 0x80A54240
static class Symbol _s; // size: 0x4, address: 0x80A54248
static class Symbol _s; // size: 0x4, address: 0x80A54250
static class Symbol _s; // size: 0x4, address: 0x80A54258
// Range: 0x805723F8 -> 0x80572B30
unsigned char FxSend::SyncProperty(class FxSend * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6FxSend;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x68
} __vt__6FxSend; // size: 0x68, address: 0x8091BC60
struct {
    // total size: 0x18
} __vt__31ObjOwnerPtr<6FxSend,9ObjectDir>; // size: 0x18, address: 0x8091BCF0
struct {
    // total size: 0x8
} __RTTI__31ObjOwnerPtr<6FxSend,9ObjectDir>; // size: 0x8, address: 0x8091BD38

