/*
    Compile unit: C:\rockband2\system\src\os\ToolStream.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CF5C4 -> 0x805CFAF4
*/
class ToolStream : public BinStream {
    // total size: 0x28
    int mBufferSize; // offset 0xC, size 0x4
    int * mSize; // offset 0x10, size 0x4
    int * mNumWritten; // offset 0x14, size 0x4
    int * mNumRead; // offset 0x18, size 0x4
    int mOffset; // offset 0x1C, size 0x4
    char * mBuffer; // offset 0x20, size 0x4
    int mTell; // offset 0x24, size 0x4
};
// Range: 0x805CF5C4 -> 0x805CF634
void * ToolStream::ToolStream(class ToolStream * const this /* r30 */, int bufferSize /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10ToolStream;
}

// Range: 0x805CF634 -> 0x805CF690
void * ToolStream::~ToolStream(class ToolStream * const this /* r30 */) {}

// Range: 0x805CF690 -> 0x805CF698
unsigned char ToolStream::Fail() {}

// Range: 0x805CF698 -> 0x805CF770
unsigned char ToolStream::Eof(class ToolStream * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805CF770 -> 0x805CFAF0
void ToolStream::ReadImpl(class ToolStream * const this /* r31 */, void * data /* r27 */, int bytes /* r28 */) {
    // Local variables
    int i; // r29
    int bytes; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805CFAF0 -> 0x805CFAF4
void ToolStream::Flush() {}

struct {
    // total size: 0x2C
} __vt__10ToolStream; // size: 0x2C, address: 0x80927064
struct {
    // total size: 0x8
} __RTTI__10ToolStream; // size: 0x8, address: 0x809270A8

