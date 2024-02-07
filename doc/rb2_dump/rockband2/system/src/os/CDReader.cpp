/*
    Compile unit: C:\rockband2\system\src\os\CDReader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805A4F20 -> 0x805A5580
*/
static int gPendingFile; // size: 0x4, address: 0x80A477B0
class vector : protected _Vector_base {
    // total size: 0xC
};
static class vector gFileInfos; // size: 0xC, address: 0x80983F3C
static class vector gFileLengths; // size: 0xC, address: 0x80983F54
int gRetryAttempts; // size: 0x4, address: 0x80A477B4
// Range: 0x805A4F20 -> 0x805A515C
unsigned char CDReadDone() {
    // Local variables
    int status; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> int gRetryAttempts;
    // -> static int gPendingFile;
    // -> static class vector gFileInfos;
}

// Range: 0x805A515C -> 0x805A5164
int CDGetError() {}

// Range: 0x805A5164 -> 0x805A5508
int CDRead(int arkfileNum /* r26 */, int sector /* r27 */, int numSectors /* r28 */, void * buf /* r29 */) {
    // Local variables
    int i; // r30
    const char * filename; // r24
    class String qualName; // r1+0x38

    // References
    // -> static int gPendingFile;
    // -> class Debug TheDebug;
    // -> static class vector gFileLengths;
    // -> class Archive * TheArchive;
    // -> static class vector gFileInfos;
}

struct {
    // total size: 0x8
} __RTTI__P11DVDFileInfo; // size: 0x8, address: 0x80921F88
// Range: 0x805A5508 -> 0x805A5580
static void __sinit_\CDReader_cpp() {
    // References
    // -> static class vector gFileLengths;
    // -> static class vector gFileInfos;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct DVDFileInfo * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct DVDFileInfo * _M_start; // offset 0x0, size 0x4
    struct DVDFileInfo * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};

