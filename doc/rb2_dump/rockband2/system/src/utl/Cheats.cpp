/*
    Compile unit: C:\rockband2\system\src\utl\Cheats.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x806048D0 -> 0x80605760
*/
static unsigned char sKeyCheatsEnabled; // size: 0x1, address: 0x80A47A98
class CheatsManager : public Object {
    // total size: 0x98
    class vector mLongJoyCheats; // offset 0x28, size 0xC
    class vector mQuickJoyCheats[2]; // offset 0x34, size 0x18
    class vector mKeyCheats; // offset 0x4C, size 0xC
    class Timer mLastButtonTime; // offset 0x58, size 0x38
    unsigned char mKeyCheatsEnabled; // offset 0x90, size 0x1
};
// Range: 0x806048D0 -> 0x8060497C
void * CheatsManager::CheatsManager(class CheatsManager * const this /* r30 */) {
    // References
    // -> static unsigned char sKeyCheatsEnabled;
    // -> struct [anonymous] __vt__13CheatsManager;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct QuickJoyCheat * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct QuickJoyCheat * _M_start; // offset 0x0, size 0x4
    struct QuickJoyCheat * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct LongJoyCheat * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct LongJoyCheat * _M_start; // offset 0x0, size 0x4
    struct LongJoyCheat * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct KeyCheat * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct KeyCheat * _M_start; // offset 0x0, size 0x4
    struct KeyCheat * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
static class Symbol wii_remote; // size: 0x4, address: 0x80A553B4
enum ShiftMode {
    kLeftShift = 0,
    kRightShift = 1,
};
// Range: 0x80604990 -> 0x80604CA8
int CheatsManager::OnMsg(class CheatsManager * const this /* r28 */, const class ButtonDownMsg & iMsg /* r29 */) {
    // Local variables
    class JoypadData * data; // r0
    int but; // r30
    enum ShiftMode shiftMode; // r0
    const struct QuickJoyCheat * it; // r27
    struct LongJoyCheat * lit; // r3
    struct LongJoyCheat * lit; // r5

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol wii_remote;
}

// Range: 0x80604CA8 -> 0x80604D70
class DataNode CheatsManager::OnMsg(class CheatsManager * const this /* r29 */) {
    // Local variables
    int key; // r0
    const struct KeyCheat * it; // r30
}

static class CheatsManager * gCheatsManager; // size: 0x4, address: 0x80A553B8
static unsigned char gDisable; // size: 0x1, address: 0x80A553BC
struct QuickJoyCheat {
    // total size: 0x8
    int mButton; // offset 0x0, size 0x4
    class DataArray * mScript; // offset 0x4, size 0x4
};
// Range: 0x80604D70 -> 0x80604ECC
void InitQuickJoyCheats(const class DataArray * cheats /* r28 */, enum ShiftMode mode /* r29 */) {
    // Local variables
    int i; // r30
    struct QuickJoyCheat item; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> static class CheatsManager * gCheatsManager;
}

struct LongJoyCheat {
    // total size: 0x14
    class vector mSequence; // offset 0x0, size 0xC
    int ixProgress; // offset 0xC, size 0x4
    class DataArray * mScript; // offset 0x10, size 0x4
};
// Range: 0x80604ECC -> 0x8060518C
void InitLongJoyCheats(const class DataArray * cheats /* r29 */) {
    // Local variables
    int i; // r30
    struct LongJoyCheat item; // r1+0x2C
    unsigned char ok; // r25
    int buttonNo; // r26
    int button; // r1+0x28

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__Pi;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class CheatsManager * gCheatsManager;
    // -> class Debug TheDebug;
}

struct KeyCheat {
    // total size: 0x8
    int mKey; // offset 0x0, size 0x4
    class DataArray * mScript; // offset 0x4, size 0x4
};
// Range: 0x8060518C -> 0x80605334
void InitKeyCheats(const class DataArray * cheats /* r28 */) {
    // Local variables
    int i; // r29
    struct KeyCheat item; // r1+0x10

    // References
    // -> static class CheatsManager * gCheatsManager;
    // -> class Debug TheDebug;
}

// Range: 0x80605334 -> 0x8060534C
void EnableKeyCheats() {
    // References
    // -> static class CheatsManager * gCheatsManager;
    // -> static unsigned char sKeyCheatsEnabled;
}

// Range: 0x8060534C -> 0x806053B0
class DataNode SetKeyCheatsEnabled(class DataArray * msg /* r31 */) {}

// Range: 0x806053B0 -> 0x80605510
void CheatsInit() {
    // Local variables
    const class DataArray * quickcheats; // r31
    const class DataArray * leftCheats; // r0
    const class DataArray * rightCheats; // r0
    const class DataArray * keyCheats; // r0
    const class DataArray * longcheats; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class CheatsManager * gCheatsManager;
    // -> static unsigned char gDisable;
}

// Range: 0x80605510 -> 0x806055AC
void CheatsTerminate() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class CheatsManager * gCheatsManager;
    // -> static unsigned char gDisable;
}

struct {
    // total size: 0x54
} __vt__13CheatsManager; // size: 0x54, address: 0x8092B928
struct {
    // total size: 0x8
} __RTTI__13CheatsManager; // size: 0x8, address: 0x8092B9A0
struct {
    // total size: 0x8
} __RTTI__P8KeyCheat; // size: 0x8, address: 0x8092BA68
struct {
    // total size: 0x8
} __RTTI__P13QuickJoyCheat; // size: 0x8, address: 0x8092BA80
struct {
    // total size: 0x8
} __RTTI__P12LongJoyCheat; // size: 0x8, address: 0x8092BA98

