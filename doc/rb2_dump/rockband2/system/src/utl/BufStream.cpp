/*
    Compile unit: C:\rockband2\system\src\utl\BufStream.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80601B98 -> 0x80601E78
*/
// Range: 0x80601B98 -> 0x80601C14
void * BufStream::BufStream(class BufStream * const this /* r29 */, void * buffer /* r30 */, int size /* r31 */) {
    // References
    // -> struct [anonymous] __vt__9BufStream;
}

// Range: 0x80601C14 -> 0x80601C84
void * BufStream::~BufStream(class BufStream * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__9BufStream;
}

// Range: 0x80601C84 -> 0x80601CE4
void BufStream::DeleteChecksum(class BufStream * const this /* r30 */) {}

// Range: 0x80601CE4 -> 0x80601D98
void BufStream::ReadImpl(class BufStream * const this /* r29 */, void * data /* r30 */, int bytes /* r31 */) {}

// Range: 0x80601D98 -> 0x80601E0C
void BufStream::WriteImpl(class BufStream * const this /* r30 */, int bytes /* r31 */) {}

// Range: 0x80601E0C -> 0x80601E78
void BufStream::SeekImpl() {
    // Local variables
    int i; // r4
}

struct {
    // total size: 0x2C
} __vt__9BufStream; // size: 0x2C, address: 0x8092B0A8
struct {
    // total size: 0x8
} __RTTI__9BufStream; // size: 0x8, address: 0x8092B0F0

