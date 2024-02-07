/*
    Compile unit: C:\rockband2\system\src\utl\Rso_Utl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80621250 -> 0x806216DC
*/
struct RSOObjectHeader * staticRso; // size: 0x4, address: 0x80A55520
// Range: 0x80621250 -> 0x8062125C
void * RsoMemAlloc() {}

// Range: 0x8062125C -> 0x8062154C
void * LoadRsoFile(const char * fileName /* r29 */, unsigned int & size /* r30 */, void * (* memoryAlloc)(int) /* r31 */) {
    // Local variables
    struct DVDFileInfo fileInfo; // r1+0xC
    long dvdFileNum; // r0
    char newFileName[256]; // r1+0x48
    void * buffer; // r31
    class AsyncFileWii * file; // r29
    int fileHandle; // r1+0x8
    unsigned char failed; // r0
    struct _FILE * file; // r29
    void * buffer; // r31
    int read; // r0
    void * buffer; // r29
    long status; // r3
    int retryCount; // r30
}

// Range: 0x8062154C -> 0x806215F4
struct RSOObjectHeader * RsoLoad(const char * moduleName /* r30 */) {
    // Local variables
    unsigned int length; // r1+0x8
    struct RSOObjectHeader * module; // r31
    unsigned char * bss; // r4
}

// Range: 0x806215F4 -> 0x80621644
struct RSOObjectHeader * StaticRsoLoad() {
    // Local variables
    unsigned int length; // r1+0x8
    struct RSOObjectHeader * module; // r31
}

// Range: 0x80621644 -> 0x806216B8
unsigned char RsoInit(const char * staticRsoName /* r31 */) {
    // Local variables
    unsigned char success; // r0

    // References
    // -> struct RSOObjectHeader * staticRso;
}

// Range: 0x806216B8 -> 0x806216DC
void RsoTerminate() {}


