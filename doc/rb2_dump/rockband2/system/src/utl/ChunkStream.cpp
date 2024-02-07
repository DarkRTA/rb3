/*
    Compile unit: C:\rockband2\system\src\utl\ChunkStream.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x806074A0 -> 0x8060800C
*/
// Range: 0x806074A0 -> 0x806074F8
class BinStream & MarkChunk(class BinStream & s /* r31 */) {
    // Local variables
    class ChunkStream * c; // r0

    // References
    // -> struct [anonymous] __RTTI__9BinStream;
    // -> struct [anonymous] __RTTI__11ChunkStream;
}

// Range: 0x806074F8 -> 0x80607638
void * ChunkStream::ChunkStream(class ChunkStream * const this /* r27 */, const char * file /* r28 */, enum FileType t /* r29 */, int chunkSize /* r30 */, unsigned char compress /* r31 */) {
    // References
    // -> struct [anonymous] __vt__11ChunkStream;
}

// Range: 0x80607638 -> 0x806077B0
void * ChunkStream::~ChunkStream(class ChunkStream * const this /* r29 */) {
    // Local variables
    int i; // r31

    // References
    // -> struct [anonymous] __vt__11ChunkStream;
}

// Range: 0x806077B0 -> 0x806078C0
void ChunkStream::ReadImpl(class ChunkStream * const this /* r28 */, void * data /* r29 */, int bytes /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806078C0 -> 0x80607994
void ChunkStream::WriteImpl(class ChunkStream * const this /* r28 */, void * data /* r29 */, int bytes /* r30 */) {
    // Local variables
    char * tmp; // r31
}

// Range: 0x80607994 -> 0x80607998
void ChunkStream::Flush() {}

// Range: 0x80607998 -> 0x806079DC
void ChunkStream::SeekImpl() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x806079DC -> 0x80607A24
int ChunkStream::Tell() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80607A24 -> 0x80607A9C
void ChunkStream::ReadChunk(class ChunkStream * const this /* r6 */) {
    // Local variables
    int size; // r5
}

// Range: 0x80607A9C -> 0x80607D8C
unsigned char ChunkStream::Eof(class ChunkStream * const this /* r30 */) {
    // Local variables
    int bytes; // r1+0xC
    int i; // r29
    int bytes; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80607D8C -> 0x80607D94
unsigned char ChunkStream::Fail() {}

// Range: 0x80607D94 -> 0x80607E74
void ChunkStream::MaybeWriteChunk(class ChunkStream * const this /* r31 */) {
    // Local variables
    int size; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80607E74 -> 0x80607F08
int ChunkStream::WriteChunk(class ChunkStream * const this /* r30 */) {
    // Local variables
    int size; // r31
    int dstLen; // r1+0x8
}

// Range: 0x80607F08 -> 0x80607FD4
void ChunkStream::DecompressChunk(class ChunkStream * const this /* r31 */) {
    // Local variables
    int size; // r4
    int dstLen; // r1+0x8
}

// Range: 0x80607FD4 -> 0x8060800C
void * ChunkInfo::ChunkInfo() {}

struct {
    // total size: 0x2C
} __vt__11ChunkStream; // size: 0x2C, address: 0x8092BDC0
struct {
    // total size: 0x8
} __RTTI__11ChunkStream; // size: 0x8, address: 0x8092BE08

