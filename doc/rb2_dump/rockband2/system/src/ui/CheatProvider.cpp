/*
    Compile unit: C:\rockband2\system\src\ui\CheatProvider.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803C951C -> 0x803C9AD4
*/
class DataArray * types; // size: 0x4, address: 0x80A51878
class Symbol name; // size: 0x4, address: 0x80A51880
class CheatProvider : public ListProvider, public Object {
    // total size: 0x38
    class vector mCheats; // offset 0x2C, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
struct Cheat {
    // total size: 0x1C
    class String mKey; // offset 0x0, size 0xC
    class String mDesc; // offset 0xC, size 0xC
    class DataArray * mScript; // offset 0x18, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Cheat * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Cheat * _M_start; // offset 0x0, size 0x4
    struct Cheat * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
static class Symbol key; // size: 0x4, address: 0x80A51888
static class Symbol description; // size: 0x4, address: 0x80A51890
// Range: 0x803C951C -> 0x803C9618
char * CheatProvider::Text(const class CheatProvider * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol description;
    // -> static class Symbol key;
}

// Range: 0x803C9618 -> 0x803C9664
class RndMat * CheatProvider::Mat() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803C9664 -> 0x803C9690
int CheatProvider::NumData() {}

// Range: 0x803C9690 -> 0x803C9718
unsigned char CheatProvider::Invoke() {
    // Local variables
    class DataArray * script; // r4
}

static class Symbol _s; // size: 0x4, address: 0x80A51898
// Range: 0x803C9718 -> 0x803C9AD4
class DataNode CheatProvider::Handle(class CheatProvider * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

struct {
    // total size: 0xA4
} __vt__13CheatProvider; // size: 0xA4, address: 0x808E1B80
struct {
    // total size: 0x8
} __RTTI__13CheatProvider; // size: 0x8, address: 0x808E1C50
struct {
    // total size: 0x8
} __RTTI__PQ213CheatProvider5Cheat; // size: 0x8, address: 0x808E1CB8

