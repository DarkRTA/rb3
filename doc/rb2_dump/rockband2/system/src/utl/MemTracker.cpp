/*
    Compile unit: C:\rockband2\system\src\utl\MemTracker.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80614CEC -> 0x80615244
*/
// Range: 0x80614CEC -> 0x80614CF0
void * MemTracker::__nw() {}

// Range: 0x80614CF0 -> 0x80614DE8
void MemTracker::UpdateStats(class MemTracker * const this /* r31 */) {
    // Local variables
    class AllocInfo * * pinfo; // r30
    class AllocInfo * info; // r7
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x80614DE8 -> 0x80614E28
class AllocInfo * MemTracker::GetInfo(void * mem /* r1+0x8 */) {
    // Local variables
    class AllocInfo * * pinfo; // r0
}

class vector : protected _Vector_base {
    // total size: 0xC
};
struct MemDiffEntry {
    // total size: 0x48
    char name[59]; // offset 0x0, size 0x3B
    int alloc_diff; // offset 0x3C, size 0x4
    int bytes_diff; // offset 0x40, size 0x4
    int heap; // offset 0x44, size 0x4
};
// Range: 0x80614E28 -> 0x80615124
static void DiffTblReport(const char * caption /* r23 */, class BlockStatTable & tbl0 /* r24 */, class BlockStatTable & tbl1 /* r25 */, class TextStream & stream /* r26 */) {
    // Local variables
    int sz0; // r0
    int sz1; // r0
    int idx0; // r28
    int idx1; // r27
    class vector entries; // r1+0x24
    class BlockStat & st0; // r0
    class BlockStat & st1; // r0
    int name_cmp; // r0
    const char * name; // r19
    int heap; // r20
    int alloc0; // r0
    int alloc1; // r3
    int bytes0; // r4
    int bytes1; // r5
    int alloc_diff; // r21
    int bytes_diff; // r22
    struct MemDiffEntry e; // r1+0x30
    int total_bytes; // r19
    int total_alloc; // r20
    int lastHeap; // r21
    struct MemDiffEntry * e; // r22
}

struct _OKToMemCpy {
    // total size: 0x1
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
struct _OKToSwap {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct MemDiffEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct MemDiffEntry * _M_start; // offset 0x0, size 0x4
    struct MemDiffEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class KeylessHash {
    // total size: 0x18
    class AllocInfo * * mEntries; // offset 0x0, size 0x4
    int mSize; // offset 0x4, size 0x4
    unsigned char mOwnEntries; // offset 0x8, size 0x1
    int mNumEntries; // offset 0xC, size 0x4
    class AllocInfo * mEmpty; // offset 0x10, size 0x4
    class AllocInfo * mRemoved; // offset 0x14, size 0x4
};
// Range: 0x80615124 -> 0x80615244
class AllocInfo * * KeylessHash::Find(class KeylessHash * const this /* r30 */, void * key /* r31 */) {
    // Local variables
    int i; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

class DebugWarner _dw; // size: 0x100, address: 0x8098A2C8
struct {
    // total size: 0x8
} __RTTI__P12MemDiffEntry; // size: 0x8, address: 0x8092DED8

