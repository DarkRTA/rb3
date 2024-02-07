/*
    Compile unit: C:\rockband2\system\src\obj\MessageTimer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805ED86C -> 0x805EE058
*/
unsigned char sActive; // size: 0x1, address: 0x80A55078
class vector : protected _Vector_base {
    // total size: 0xC
};
static class vector gEntries; // size: 0xC, address: 0x809895F4
// Range: 0x805ED86C -> 0x805ED8A4
static class DataNode MessageTimerStart() {}

// Range: 0x805ED8A4 -> 0x805ED8DC
static class DataNode MessageTimerStop() {}

// Range: 0x805ED8DC -> 0x805ED914
static class DataNode MessageTimerDump() {}

// Range: 0x805ED914 -> 0x805ED928
static class DataNode MessageTimerOn() {
    // References
    // -> unsigned char sActive;
}

// Range: 0x805ED928 -> 0x805ED9B4
void MessageTimer::Init() {}

// Range: 0x805ED9B4 -> 0x805EDAEC
void MessageTimer::Start() {
    // References
    // -> static class vector gEntries;
    // -> unsigned char sActive;
}

class vector : protected _Vector_base {
    // total size: 0xC
};
struct ObjEntry {
    // total size: 0x10
    class Symbol name; // offset 0x0, size 0x4
    float maxMs; // offset 0x4, size 0x4
    float totalMs; // offset 0x8, size 0x4
    int num; // offset 0xC, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct ObjEntry * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct ObjEntry * * _M_start; // offset 0x0, size 0x4
    struct ObjEntry * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
// Range: 0x805EDAEC -> 0x805EDAF8
void MessageTimer::Stop() {
    // References
    // -> unsigned char sActive;
}

// Range: 0x805EDAF8 -> 0x805EDCB0
void MessageTimer::Dump() {
    // Local variables
    int i; // r31

    // References
    // -> static class vector gEntries;
    // -> class Debug TheDebug;
}

struct ObjSort {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
struct MaxSort {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x805EDCB0 -> 0x805EE02C
void MessageTimer::AddTime(class Object * o /* r30 */, class Symbol & msg /* r29 */, float ms /* f31 */) {
    // Local variables
    int i; // r7

    // References
    // -> static class vector gEntries;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x8
} __RTTI__PP10EventEntry; // size: 0x8, address: 0x80929930
struct {
    // total size: 0x8
} __RTTI__PP8ObjEntry; // size: 0x8, address: 0x80929948
// Range: 0x805EE02C -> 0x805EE058
static void __sinit_\MessageTimer_cpp() {
    // References
    // -> static class vector gEntries;
}

class StlNodeAlloc {
    // total size: 0x1
};
struct EventEntry {
    // total size: 0x10
    class Symbol msg; // offset 0x0, size 0x4
    class vector objs; // offset 0x4, size 0xC
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct EventEntry * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct EventEntry * * _M_start; // offset 0x0, size 0x4
    struct EventEntry * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};

