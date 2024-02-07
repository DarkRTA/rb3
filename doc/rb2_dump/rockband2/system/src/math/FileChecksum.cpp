/*
    Compile unit: C:\rockband2\system\src\math\FileChecksum.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8062FFAC -> 0x806301DC
*/
class vector : protected _Vector_base {
    // total size: 0xC
};
static class vector gChecksumData; // size: 0xC, address: 0x8098A924
// Range: 0x8062FFAC -> 0x80630040
void SetFileChecksumData() {
    // References
    // -> static class vector gChecksumData;
}

// Range: 0x80630040 -> 0x806300E0
void ClearFileChecksumData() {
    // References
    // -> static class vector gChecksumData;
}

// Range: 0x806300E0 -> 0x80630104
unsigned char HasFileChecksumData() {
    // References
    // -> static class vector gChecksumData;
}

// Range: 0x80630104 -> 0x806301B0
unsigned char * GetFileChecksum(const char * filename /* r29 */) {
    // Local variables
    struct ChecksumData * cd; // r31
    struct FileChecksum * it; // r30

    // References
    // -> static class vector gChecksumData;
}

struct {
    // total size: 0x8
} __RTTI__P12ChecksumData; // size: 0x8, address: 0x8092FC98
// Range: 0x806301B0 -> 0x806301DC
static void __sinit_\FileChecksum_cpp() {
    // References
    // -> static class vector gChecksumData;
}

class StlNodeAlloc {
    // total size: 0x1
};
struct ChecksumData {
    // total size: 0x8
    struct FileChecksum * start; // offset 0x0, size 0x4
    struct FileChecksum * end; // offset 0x4, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct ChecksumData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct ChecksumData * _M_start; // offset 0x0, size 0x4
    struct ChecksumData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};

