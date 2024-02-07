/*
    Compile unit: C:\rockband2\system\src\os\AsyncFile_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805A26C4 -> 0x805A2F38
*/
int gFileRetryAttempts; // size: 0x4, address: 0x80A477A8
class AsyncFileWii : public AsyncFile {
    // total size: 0xDC
    int mCount; // offset 0x3C, size 0x4
    int mDLCIdx; // offset 0x40, size 0x4
    int mFileReadPosition; // offset 0x44, size 0x4
    unsigned char mReadInProgress; // offset 0x48, size 0x1
    void * mTempBuffer; // offset 0x4C, size 0x4
    unsigned char mUseFRead; // offset 0x50, size 0x1
    int mTotalCount; // offset 0x54, size 0x4
    struct DVDFileInfo mFileInfo; // offset 0x58, size 0x3C
    struct CNTFileInfo mCNTFileInfo; // offset 0x94, size 0x44
    struct _FILE * mFile; // offset 0xD8, size 0x4
};
// Range: 0x805A26C4 -> 0x805A27D4
void * AsyncFileWii::AsyncFileWii(class AsyncFileWii * const this /* r28 */, const char * filename /* r29 */, int mode /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12AsyncFileWii;
}

// Range: 0x805A27D4 -> 0x805A29F4
unsigned int AsyncFileWii::_Open(class AsyncFileWii * const this /* r29 */) {
    // Local variables
    unsigned int size; // r30
    char mode[4]; // r1+0x8
    int i; // r5
    long dvdFileNum; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805A29F4 -> 0x805A2A68
int AsyncFileWii::_Write(class AsyncFileWii * const this /* r29 */, void * buffer /* r30 */, int count /* r31 */) {}

// Range: 0x805A2A68 -> 0x805A2B0C
void AsyncFileWii::_SeekToTell(class AsyncFileWii * const this /* r31 */) {}

// Range: 0x805A2B0C -> 0x805A2BD0
void AsyncFileWii::_ReadAsync(class AsyncFileWii * const this /* r29 */, void * buffer /* r30 */, int count /* r31 */) {
    // Local variables
    long readStart; // r0
}

// Range: 0x805A2BD0 -> 0x805A2E7C
unsigned char AsyncFileWii::_ReadDone(class AsyncFileWii * const this /* r31 */) {
    // Local variables
    int read; // r0
    int status; // r0

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> int gFileRetryAttempts;
}

// Range: 0x805A2E7C -> 0x805A2F38
void AsyncFileWii::_Close(class AsyncFileWii * const this /* r31 */) {}

struct {
    // total size: 0x50
} __vt__12AsyncFileWii; // size: 0x50, address: 0x80921C10
struct {
    // total size: 0x8
} __RTTI__12AsyncFileWii; // size: 0x8, address: 0x80921C88

