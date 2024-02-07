/*
    Compile unit: C:\rockband2\system\src\os\AsyncFileCNT.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805A2FB0 -> 0x805A3124
*/
class AsyncFileCNT : public AsyncFile {
    // total size: 0x23C0
public:
    void * mTempBufferCNT; // offset 0x3C, size 0x4
    int mReadSizeCNT; // offset 0x40, size 0x4
    int mReadResultCNT; // offset 0x44, size 0x4
private:
    unsigned char mReadInProgress; // offset 0x48, size 0x1
    unsigned char mCNTReadThreadStack[8192]; // offset 0x60, size 0x2000
    struct OSThread mCNTReadThread; // offset 0x2060, size 0x318
    struct CNTFileInfo mCNTFileInfo; // offset 0x2378, size 0x44
};
// Range: 0x805A2FB0 -> 0x805A3014
void * AsyncFileCNT::AsyncFileCNT(class AsyncFileCNT * const this /* r30 */, const char * filename /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12AsyncFileCNT;
}

// Range: 0x805A3014 -> 0x805A301C
int AsyncFileCNT::_Write() {}

// Range: 0x805A301C -> 0x805A3074
void AsyncFileCNT::_SeekToTell(class AsyncFileCNT * const this /* r31 */) {
    // Local variables
    int rv; // r0
}

// Range: 0x805A3074 -> 0x805A30B4
void * ReadAsyncCNT(void * param /* r31 */) {
    // Local variables
    class AsyncFileCNT * file; // r0
}

// Range: 0x805A30B4 -> 0x805A3124
void AsyncFileCNT::_Close(class AsyncFileCNT * const this /* r31 */) {}

struct {
    // total size: 0x50
} __vt__12AsyncFileCNT; // size: 0x50, address: 0x80921D68
struct {
    // total size: 0x8
} __RTTI__12AsyncFileCNT; // size: 0x8, address: 0x80921DE0

