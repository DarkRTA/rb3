/*
    Compile unit: C:\rockband2\system\src\utl\BinStream.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80600FA8 -> 0x80601B38
*/
class Rand2 {
    // total size: 0x4
    int mSeed; // offset 0x0, size 0x4
};
// Range: 0x80600FA8 -> 0x80600FB4
char * BinStream::Name() {}

// Range: 0x80600FB4 -> 0x80601054
class BinStream & BinStream::__ls(class BinStream * const this /* r29 */, const char * str /* r30 */) {
    // Local variables
    unsigned int len; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80601054 -> 0x806010F8
class BinStream & BinStream::__ls(class BinStream * const this /* r29 */) {
    // Local variables
    unsigned int len; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806010F8 -> 0x80601168
class BinStream & BinStream::__ls(class BinStream * const this /* r29 */, const class String & str /* r30 */) {}

// Range: 0x80601168 -> 0x80601200
void BinStream::ReadString(class BinStream * const this /* r29 */, char * str /* r30 */, int bufSize /* r31 */) {
    // Local variables
    unsigned int len; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

static char buf[512]; // size: 0x200, address: 0x809897C8
// Range: 0x80601200 -> 0x80601264
class BinStream & BinStream::__rs(class BinStream * const this /* r29 */, class Symbol & str /* r30 */) {
    // References
    // -> static char buf[512];
}

// Range: 0x80601264 -> 0x806012C4
class BinStream & BinStream::__rs(class BinStream * const this /* r30 */, class String & str /* r31 */) {
    // Local variables
    unsigned int len; // r1+0x8
}

// Range: 0x806012C4 -> 0x806012E0
void * BinStream::BinStream() {
    // References
    // -> struct [anonymous] __vt__9BinStream;
}

// Range: 0x806012E0 -> 0x80601344
void * BinStream::~BinStream(class BinStream * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__9BinStream;
}

// Range: 0x80601344 -> 0x806013D0
void BinStream::EnableReadEncryption(class BinStream * const this /* r31 */) {
    // Local variables
    int seed; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806013D0 -> 0x8060147C
void BinStream::EnableWriteEncryption(class BinStream * const this /* r30 */, int seedOverride /* r31 */) {
    // Local variables
    int seed; // [invalid]

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8060147C -> 0x806014EC
void BinStream::DisableEncryption(class BinStream * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class DebugWarner _dw; // size: 0x100, address: 0x809899C8
// Range: 0x806014EC -> 0x806015F8
void BinStream::Read(class BinStream * const this /* r29 */, void * data /* r31 */, int bytes /* r30 */) {
    // Local variables
    unsigned char * ptr; // [invalid]
    unsigned char * end; // r30
    unsigned char c; // r3

    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
}

class DebugWarnPrinter {
    // total size: 0x100
    char mStr[256]; // offset 0x0, size 0x100
};
static class DebugWarnPrinter _dw; // size: 0x100, address: 0x80989AC8
// Range: 0x806015F8 -> 0x8060176C
void BinStream::Write(class BinStream * const this /* r28 */, void * void_data /* r29 */, int bytes /* r1+0x8 */) {
    // Local variables
    const unsigned char * data; // [invalid]
    char crypt[512]; // r1+0x10
    int buf_size; // r30
    int i; // r31
    unsigned char c; // r3

    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarnPrinter _dw;
}

// Range: 0x8060176C -> 0x80601844
void BinStream::Seek(class BinStream * const this /* r28 */, int offset /* r29 */, enum SeekType type /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80601844 -> 0x806019B4
void BinStream::ReadEndian(class BinStream * const this /* r27 */, void * data /* r31 */, int bytes /* r26 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x806019B4 -> 0x80601B38
void BinStream::WriteEndian(class BinStream * const this /* r30 */, int bytes /* r31 */) {
    // Local variables
    char buf[16]; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x2C
} __vt__9BinStream; // size: 0x2C, address: 0x8092B058

