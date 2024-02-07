/*
    Compile unit: C:\rockband2\system\src\os\AsyncFile.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805A1A78 -> 0x805A2658
*/
static int gBufferSize; // size: 0x4, address: 0x80A477A0
class AsyncFile : public File {
    // total size: 0x3C
protected:
    int mHandle; // offset 0x4, size 0x4
    int mMode; // offset 0x8, size 0x4
    unsigned char mFail; // offset 0xC, size 0x1
    class String mFilename; // offset 0x10, size 0xC
    unsigned int mTell; // offset 0x1C, size 0x4
    int mOffset; // offset 0x20, size 0x4
private:
    unsigned int mSize; // offset 0x24, size 0x4
    int mUCSize; // offset 0x28, size 0x4
    char * mBuffer; // offset 0x2C, size 0x4
    char * mData; // offset 0x30, size 0x4
    int mBytesLeft; // offset 0x34, size 0x4
    int mBytesRead; // offset 0x38, size 0x4
};
// Range: 0x805A1A78 -> 0x805A1C74
class AsyncFile * AsyncFile::New(const char * filename /* r30 */, int mode /* r31 */) {
    // Local variables
    class AsyncFile * ret; // r29

    // References
    // -> unsigned char gHostLogging;
}

// Range: 0x805A1C74 -> 0x805A1CE4
void * AsyncFile::AsyncFile(class AsyncFile * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__9AsyncFile;
}

// Range: 0x805A1CE4 -> 0x805A1EAC
void AsyncFile::Init(class AsyncFile * const this /* r31 */) {
    // Local variables
    unsigned char cur; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static int gBufferSize;
}

// Range: 0x805A1EAC -> 0x805A1F0C
void AsyncFile::Terminate(class AsyncFile * const this /* r31 */) {}

// Range: 0x805A1F0C -> 0x805A1F80
int AsyncFile::Read(class AsyncFile * const this /* r31 */, int iBytes /* r1+0x8 */) {}

// Range: 0x805A1F80 -> 0x805A20C0
unsigned char AsyncFile::ReadAsync(class AsyncFile * const this /* r29 */, void * iData /* r30 */, int iBytes /* r1+0x8 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805A20C0 -> 0x805A2224
unsigned char AsyncFile::ReadDone(class AsyncFile * const this /* r30 */, int & oBytes /* r31 */) {
    // Local variables
    int len; // r29

    // References
    // -> static int gBufferSize;
}

// Range: 0x805A2224 -> 0x805A238C
int AsyncFile::Write(class AsyncFile * const this /* r29 */, void * iData /* r30 */, int iBytes /* r31 */) {
    // Local variables
    int bytesLeft; // r28
    const char * data; // [invalid]
    int len; // r27

    // References
    // -> static int gBufferSize;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805A238C -> 0x805A2514
int AsyncFile::Seek(class AsyncFile * const this /* r31 */, int iOffset /* r28 */, int iSeekType /* r29 */) {
    // Local variables
    long long tell; // r4

    // References
    // -> static int gBufferSize;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805A2514 -> 0x805A251C
int AsyncFile::Tell() {}

// Range: 0x805A251C -> 0x805A257C
void AsyncFile::Flush(class AsyncFile * const this /* r31 */) {}

// Range: 0x805A257C -> 0x805A2628
void AsyncFile::FillBuffer(class AsyncFile * const this /* r31 */) {
    // References
    // -> static int gBufferSize;
}

// Range: 0x805A2628 -> 0x805A2640
unsigned char AsyncFile::Eof() {}

// Range: 0x805A2640 -> 0x805A2648
unsigned char AsyncFile::Fail() {}

// Range: 0x805A2648 -> 0x805A2650
int AsyncFile::Size() {}

// Range: 0x805A2650 -> 0x805A2658
int AsyncFile::UncompressedSize() {}

struct {
    // total size: 0x50
} __vt__9AsyncFile; // size: 0x50, address: 0x80921AB0
struct {
    // total size: 0x8
} __RTTI__9AsyncFile; // size: 0x8, address: 0x80921B18

