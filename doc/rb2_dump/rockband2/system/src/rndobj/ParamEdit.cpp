/*
    Compile unit: C:\rockband2\system\src\rndobj\ParamEdit.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804D6234 -> 0x804D7018
*/
class set {
    // total size: 0x18
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class ParamEdit : public Object {
    // total size: 0x60
    class String mTitle; // offset 0x28, size 0xC
    class DataArray * mCurGroup; // offset 0x34, size 0x4
    class DataArray * mCurUpdateFunc; // offset 0x38, size 0x4
    int mScrollIdx; // offset 0x3C, size 0x4
    class RndOverlay * mOverlay; // offset 0x40, size 0x4
    float mStepSize; // offset 0x44, size 0x4
    class set mSavedParams; // offset 0x48, size 0x18
};
class Param {
    // total size: 0x8
public:
    class DataArray * mDesc; // offset 0x0, size 0x4
    int mIdx; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
// Range: 0x804D6234 -> 0x804D6274
void ParamEdit::SaveCurParam(class ParamEdit * const this /* r5 */) {}

enum ParamType {
    kBool = 0,
    kInteger = 1,
    kReal = 2,
    kInvalid = 3,
};
static class Symbol _s; // size: 0x4, address: 0x80A5336C
static class Symbol _s; // size: 0x4, address: 0x80A53374
static class Symbol _s; // size: 0x4, address: 0x80A5337C
static class Symbol _s; // size: 0x4, address: 0x80A53384
static class Symbol _s; // size: 0x4, address: 0x80A5338C
// Range: 0x804D6274 -> 0x804D6A9C
class DataNode ParamEdit::Handle(class ParamEdit * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x804D6A9C -> 0x804D6C4C
class DataNode ParamEdit::OnPrint(class ParamEdit * const this /* r27 */) {
    // Local variables
    class DataArray * desc; // r30
    class DataArray * array; // r29
    struct _Rb_tree_iterator it; // r1+0x1C
    int i; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x804D6C4C -> 0x804D6D10
class DataNode ParamEdit::OnInc(class ParamEdit * const this /* r31 */) {}

// Range: 0x804D6D10 -> 0x804D6E20
class DataNode ParamEdit::OnStep(class ParamEdit * const this /* r30 */, class DataArray * d /* r31 */) {}

// Range: 0x804D6E20 -> 0x804D6F00
class DataNode ParamEdit::OnScroll(class ParamEdit * const this /* r29 */, class DataArray * d /* r30 */) {
    // Local variables
    int idx; // r31
}

// Range: 0x804D6F00 -> 0x804D7018
class DataNode ParamEdit::OnEdit(class ParamEdit * const this /* r30 */, class DataArray * d /* r31 */) {}

struct {
    // total size: 0x54
} __vt__9ParamEdit; // size: 0x54, address: 0x808FC930
struct {
    // total size: 0x8
} __RTTI__9ParamEdit; // size: 0x8, address: 0x808FC9A8
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std33_Rb_tree_node<Q29ParamEdit5Param>; // size: 0x8, address: 0x808FCA10

