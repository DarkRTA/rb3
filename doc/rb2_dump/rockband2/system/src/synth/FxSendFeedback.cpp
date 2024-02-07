/*
    Compile unit: C:\rockband2\system\src\synth\FxSendFeedback.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805756F4 -> 0x805767E0
*/
class DataArray * types; // size: 0x4, address: 0x80A54310
class Symbol name; // size: 0x4, address: 0x80A54318
struct FbState {
    // total size: 0x34
    float mBendRange; // offset 0x0, size 0x4
    float mBendAmount; // offset 0x4, size 0x4
    float mNote; // offset 0x8, size 0x4
    float mFeedbackDB; // offset 0xC, size 0x4
    float mTone; // offset 0x10, size 0x4
    float mDrive; // offset 0x14, size 0x4
    float mSpaceDepth; // offset 0x18, size 0x4
    float mSpaceRate; // offset 0x1C, size 0x4
    float mSpaceAverage; // offset 0x20, size 0x4
    float mOtherNote; // offset 0x24, size 0x4
    float mFinePitch; // offset 0x28, size 0x4
    float mExcitation; // offset 0x2C, size 0x4
    float mAutoBend; // offset 0x30, size 0x4
};
class FxSendFeedback : public FxSend {
    // total size: 0xB8
protected:
    struct FbState mState; // offset 0x50, size 0x34
    struct FbState mStatePrev; // offset 0x84, size 0x34
};
// Range: 0x805756F4 -> 0x805757A4
void * FxSendFeedback::FxSendFeedback(class FxSendFeedback * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14FxSendFeedback;
}

// Range: 0x805757A4 -> 0x80575800
void * FxSendFeedback::~FxSendFeedback(class FxSendFeedback * const this /* r30 */) {}

static int REV; // size: 0x4, address: 0x80A47698
// Range: 0x80575800 -> 0x80575844
void FxSendFeedback::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80575844 -> 0x80575980
void FxSendFeedback::Load(class FxSendFeedback * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x80575980 -> 0x80575A30
void FxSendFeedback::Copy(class FxSendFeedback * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class FxSendFeedback * Feedback; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14FxSendFeedback;
}

// Range: 0x80575A30 -> 0x80575CD8
class DataNode FxSendFeedback::Handle(class FxSendFeedback * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A54320
static class Symbol _s; // size: 0x4, address: 0x80A54328
static class Symbol _s; // size: 0x4, address: 0x80A54330
static class Symbol _s; // size: 0x4, address: 0x80A54338
static class Symbol _s; // size: 0x4, address: 0x80A54340
static class Symbol _s; // size: 0x4, address: 0x80A54348
static class Symbol _s; // size: 0x4, address: 0x80A54350
static class Symbol _s; // size: 0x4, address: 0x80A54358
static class Symbol _s; // size: 0x4, address: 0x80A54360
static class Symbol _s; // size: 0x4, address: 0x80A54368
// Range: 0x80575CD8 -> 0x805767E0
unsigned char FxSendFeedback::SyncProperty(class FxSendFeedback * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x68
} __vt__14FxSendFeedback; // size: 0x68, address: 0x8091C508
struct {
    // total size: 0x8
} __RTTI__14FxSendFeedback; // size: 0x8, address: 0x8091C5A0

