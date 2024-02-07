/*
    Compile unit: C:\rockband2\system\src\utl\BufStreamNAND.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80601EA4 -> 0x806026C8
*/
// Range: 0x80601EA4 -> 0x80601FB8
void * BufStreamNAND::BufStreamNAND(class BufStreamNAND * const this /* r27 */, void * buffer /* r28 */, int chunkSize /* r29 */, int totalSize /* r30 */, char * filePath /* r31 */) {
    // Local variables
    float remainder; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__13BufStreamNAND;
}

// Range: 0x80601FB8 -> 0x80602028
void * BufStreamNAND::~BufStreamNAND(class BufStreamNAND * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__13BufStreamNAND;
}

// Range: 0x80602028 -> 0x80602030
void BufStreamNAND::SetResult() {}

// Range: 0x80602030 -> 0x80602038
enum MCResult BufStreamNAND::GetResult() {}

// Range: 0x80602038 -> 0x80602098
void BufStreamNAND::DeleteChecksum(class BufStreamNAND * const this /* r30 */) {}

// Range: 0x80602098 -> 0x806021A4
void BufStreamNAND::ReadImpl(class BufStreamNAND * const this /* r29 */, void * data /* r30 */, int bytes /* r31 */) {}

// Range: 0x806021A4 -> 0x806022B8
void BufStreamNAND::WriteImpl(class BufStreamNAND * const this /* r30 */, void * data /* r29 */, int bytes /* r31 */) {
    // Local variables
    enum MCResult result; // r0
}

// Range: 0x806022B8 -> 0x80602324
void BufStreamNAND::SeekImpl() {
    // Local variables
    int i; // r4
}

// Range: 0x80602324 -> 0x80602454
enum MCResult BufStreamNAND::SaveBufferToNAND(class BufStreamNAND * const this /* r29 */) {
    // Local variables
    long result; // r4
    enum MCResult mcResult; // r30
}

// Range: 0x80602454 -> 0x806024E8
enum MCResult BufStreamNAND::FinishWrite(class BufStreamNAND * const this /* r31 */) {
    // Local variables
    enum MCResult mcResult; // r3
}

// Range: 0x806024E8 -> 0x806025A4
enum MCResult BufStreamNAND::LoadBufferFromNAND(class BufStreamNAND * const this /* r30 */) {
    // Local variables
    long result; // r4
    enum MCResult mcResult; // r31
}

// Range: 0x806025A4 -> 0x80602614
enum MCResult BufStreamNAND::FinishStream(class BufStreamNAND * const this /* r31 */) {
    // Local variables
    long result; // r0
    enum MCResult mcResult; // r4
}

// Range: 0x80602614 -> 0x806026C8
enum MCResult BufStreamNAND::HandleResultNAND() {
    // Local variables
    enum MCResult mcResult; // r31
}

struct {
    // total size: 0x2C
} __vt__13BufStreamNAND; // size: 0x2C, address: 0x8092B180
struct {
    // total size: 0x8
} __RTTI__13BufStreamNAND; // size: 0x8, address: 0x8092B1C8

