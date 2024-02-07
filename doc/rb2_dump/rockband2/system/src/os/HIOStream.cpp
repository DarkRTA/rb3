/*
    Compile unit: C:\rockband2\system\src\os\HIOStream.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CE234 -> 0x805CE8B8
*/
static unsigned int crc32_tab[256]; // size: 0x400, address: 0x8084E9E8
// Range: 0x805CE234 -> 0x805CE274
static unsigned int Checksum() {
    // Local variables
    unsigned int crc32val; // r5
    unsigned int i; // r7

    // References
    // -> static unsigned int crc32_tab[256];
}

class HIOStream : public BinStream {
    // total size: 0x18
    unsigned char mFail; // offset 0xC, size 0x1
    unsigned char * mReadBuffer; // offset 0x10, size 0x4
    int mReadBufferCount; // offset 0x14, size 0x4
};
// Range: 0x805CE274 -> 0x805CE2EC
void * HIOStream::HIOStream(class HIOStream * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__9HIOStream;
}

// Range: 0x805CE2EC -> 0x805CE370
void * HIOStream::~HIOStream(class HIOStream * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__9HIOStream;
}

// Range: 0x805CE370 -> 0x805CE3B8
unsigned char HIOStream::Eof() {}

// Range: 0x805CE3B8 -> 0x805CE3CC
char * HIOStream::Name() {}

// Range: 0x805CE3CC -> 0x805CE3D8
void HIOStream::Failure() {}

// Range: 0x805CE3D8 -> 0x805CE434
unsigned char HIOStream::CanRead(class HIOStream * const this /* r31 */) {
    // Local variables
    unsigned long status; // r1+0x8
}

// Range: 0x805CE434 -> 0x805CE494
unsigned char HIOStream::CanWrite(class HIOStream * const this /* r31 */) {
    // Local variables
    unsigned long status; // r1+0x8
}

// Range: 0x805CE494 -> 0x805CE6DC
void HIOStream::ReadImpl(class HIOStream * const this /* r29 */, int bytes /* r1+0x8 */) {
    // Local variables
    unsigned char * pData; // r30
    int bufferBytes; // r28
    int numRead; // r28
    unsigned long msg; // r1+0xC
    unsigned long mailBytes; // r27
    unsigned int checksum; // r0
    int bufferBytes; // r27

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805CE6DC -> 0x805CE874
void HIOStream::WriteImpl(class HIOStream * const this /* r27 */, int bytes /* r1+0x8 */) {
    // Local variables
    const unsigned char * pData; // r29
    int numWritten; // r0
    unsigned long mailBytes; // r28
    unsigned int checksum; // r0
    unsigned long ack; // r1+0xC

    // References
    // -> static int READ_BUFFER_SIZE;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805CE874 -> 0x805CE8B8
void HIOStream::SeekImpl() {
    // References
    // -> class Debug TheDebug;
}

struct {
    // total size: 0x2C
} __vt__9HIOStream; // size: 0x2C, address: 0x80926E9C
struct {
    // total size: 0x8
} __RTTI__9HIOStream; // size: 0x8, address: 0x80926EE0
static int READ_BUFFER_SIZE; // size: 0x4, address: 0x80A57E10

