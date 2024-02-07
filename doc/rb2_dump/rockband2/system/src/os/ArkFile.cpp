/*
    Compile unit: C:\rockband2\system\src\os\ArkFile.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805A1530 -> 0x805A1A74
*/
// Range: 0x805A1530 -> 0x805A15F0
void * ArkFile::ArkFile(class ArkFile * const this /* r29 */, const char * iFilename /* r30 */, int iMode /* r31 */) {
    // Local variables
    unsigned char retval; // r0

    // References
    // -> class Archive * TheArchive;
    // -> struct [anonymous] __vt__7ArkFile;
}

// Range: 0x805A15F0 -> 0x805A1678
void * ArkFile::~ArkFile(class ArkFile * const this /* r30 */) {
    // References
    // -> class BlockMgr TheBlockMgr;
    // -> struct [anonymous] __vt__7ArkFile;
}

// Range: 0x805A1678 -> 0x805A16EC
int ArkFile::Read(class ArkFile * const this /* r31 */) {
    // Local variables
    int retVal; // r1+0x8
}

// Range: 0x805A16EC -> 0x805A191C
unsigned char ArkFile::ReadAsync(class ArkFile * const this /* r29 */, void * iBuff /* r30 */, int iBytes /* r31 */) {
    // Local variables
    unsigned long long startByte; // r28
    int startBlock; // r1+0x10
    int numBlocks; // r1+0xC
    int blockSize; // r1+0x8
    int currBlock; // r26
    int lastBlock; // r25
    int startOffset; // r24
    int endOffset; // r23
    char * buff; // [invalid]
    unsigned char tryFill; // r22
    int endByte; // r4
    class AsyncTask task; // r1+0x18

    // References
    // -> class BlockMgr TheBlockMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805A191C -> 0x805A1964
int ArkFile::Write() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x805A1964 -> 0x805A19B4
int ArkFile::Seek() {}

// Range: 0x805A19B4 -> 0x805A19BC
int ArkFile::Tell() {}

// Range: 0x805A19BC -> 0x805A19D4
unsigned char ArkFile::Eof() {}

// Range: 0x805A19D4 -> 0x805A19E8
unsigned char ArkFile::Fail() {}

// Range: 0x805A19E8 -> 0x805A19F0
int ArkFile::Size() {}

// Range: 0x805A19F0 -> 0x805A19F8
int ArkFile::UncompressedSize() {}

// Range: 0x805A19F8 -> 0x805A1A20
void ArkFile::TaskDone() {}

// Range: 0x805A1A20 -> 0x805A1A74
unsigned char ArkFile::ReadDone(class ArkFile * const this /* r30 */, int & oBytes /* r31 */) {
    // References
    // -> class BlockMgr TheBlockMgr;
}

struct {
    // total size: 0x38
} __vt__7ArkFile; // size: 0x38, address: 0x80921990
struct {
    // total size: 0x8
} __RTTI__7ArkFile; // size: 0x8, address: 0x809219E0

