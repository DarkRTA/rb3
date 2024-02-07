/*
    Compile unit: C:\rockband2\system\src\utl\BinkIntegration.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80600098 -> 0x80600FA8
*/
struct RADARAMCALLBACKS {
    // total size: 0x8
    void * (* aram_malloc)(unsigned int); // offset 0x0, size 0x4
    void (* aram_free)(void *); // offset 0x4, size 0x4
};
// Range: 0x80600098 -> 0x80600100
void BinkInit() {
    // Local variables
    struct RADARAMCALLBACKS aram_callbacks; // r1+0x8
}

// Range: 0x80600100 -> 0x80600110
static void * BinkAlloc() {}

// Range: 0x80600110 -> 0x80600114
static void BinkFree() {}

// Range: 0x80600114 -> 0x80600140
static void intelendian() {
    // Local variables
    unsigned int s; // r5
    unsigned int * d; // r3
}

// Range: 0x80600140 -> 0x8060021C
static int BinkFileOpen(struct BINKIO * pBinkIO /* r29 */, const char * pFileName /* r30 */, unsigned int iOpenFlags /* r31 */) {}

struct BINKENCRYPTIONHEADER {
    // total size: 0x38
    unsigned int mSignature; // offset 0x0, size 0x4
    unsigned int mVersion; // offset 0x4, size 0x4
    unsigned int mKeyIndex; // offset 0x8, size 0x4
    unsigned int mMagicA; // offset 0xC, size 0x4
    unsigned int mMagicB; // offset 0x10, size 0x4
    unsigned long long mNonce[2]; // offset 0x18, size 0x10
    unsigned char mKeyMask[16]; // offset 0x28, size 0x10
};
class XTEABlockEncrypter {
    // total size: 0x20
    unsigned long long mNonce[2]; // offset 0x0, size 0x10
    unsigned int mKey[4]; // offset 0x10, size 0x10
};
struct BINKFILE {
    // total size: 0x70
    class File * pFile; // offset 0x0, size 0x4
    unsigned int iCloseFile; // offset 0x4, size 0x4
    unsigned char * pBuffer; // offset 0x8, size 0x4
    unsigned char * pBufEnd; // offset 0xC, size 0x4
    unsigned char * pBufPos; // offset 0x10, size 0x4
    unsigned char * pBufBack; // offset 0x14, size 0x4
    unsigned int iBufEmpty; // offset 0x18, size 0x4
    unsigned int iFileBufPos; // offset 0x1C, size 0x4
    unsigned int iSimulateBPS; // offset 0x20, size 0x4
    unsigned int iTimer; // offset 0x24, size 0x4
    unsigned int iHeaderSize; // offset 0x28, size 0x4
    struct BINKENCRYPTIONHEADER mEncryptionHeader; // offset 0x30, size 0x38
    class XTEABlockEncrypter * pXTEADecrypter; // offset 0x68, size 0x4
};
// Range: 0x8060021C -> 0x8060062C
static unsigned int BinkFileReadHeader(struct BINKIO * pBinkIO /* r26 */, void * pDest /* r27 */, unsigned int iReadSize /* r28 */) {
    // Local variables
    struct BINKFILE * pBinkFileInfo; // r0
    class File * pReadFile; // r31
    struct BINKENCRYPTIONHEADER * pEncryptionHeader; // r30
    int iEncryptionHeaderReadSize; // r29
    char script[256]; // r1+0x118
    unsigned char masterKey[256]; // r1+0x18
    class DataArray * randomGen; // r18
    unsigned long masher; // r0
    char functionName; // r5
    class DataArray * masterKeyGen; // r18
    unsigned char fileKey[16]; // r1+0x8
    int ix; // r6
    unsigned int kiBytesRead; // r18
    unsigned int kiBytesLeft; // r3

    // References
    // -> class Synth * TheSynth;
}

static class Timer * _t; // size: 0x4, address: 0x80A553A0
struct XTEABlock {
    // total size: 0x10
    unsigned long long mData[2]; // offset 0x0, size 0x10
};
// Range: 0x8060062C -> 0x80600A5C
static void ReadFunc(struct BINKIO * pBinkIO /* r29 */, unsigned char bStartNewRead /* r30 */) {
    // Local variables
    struct BINKFILE * pBinkFileInfo; // r0
    int iBytesRead; // r1+0x10
    class AutoTimer _at; // r1+0xC
    struct XTEABlock * pBlock; // r31
    struct XTEABlock decrypted; // r1+0x18
    unsigned int iReadSize; // r21

    // References
    // -> class Debug TheDebug;
    // -> static class Timer * _t;
}

// Range: 0x80600A5C -> 0x80600DF4
static unsigned int BinkFileReadFrame(struct BINKIO * pBinkIO /* r26 */, int iOffset /* r29 */, void * pDest /* r27 */, unsigned int iReadSize /* r28 */) {
    // Local variables
    struct BINKFILE * pBinkFileInfo; // r0
    unsigned int iTimerReadStart; // r0
    unsigned int iOffsetAlign; // r30
    unsigned int iOffsetDifference; // r4
    unsigned int iEncryptedOffset; // r0
    unsigned int iBlockNumber; // r0
    unsigned int iTAmt; // r30
    unsigned int iTimerReadSyncStart; // r0
    unsigned int iBytesRead; // r0
    unsigned int iTimerReadStop; // r0
    unsigned int iCopySize; // r29
    unsigned int iFrontSize; // r25
    unsigned int iFileBytesLeft; // r3
}

// Range: 0x80600DF4 -> 0x80600E10
static unsigned int BinkFileGetBufferSize() {}

// Range: 0x80600E10 -> 0x80600E84
static void BinkFileClose(struct BINKIO * pBinkIO /* r31 */) {
    // Local variables
    struct BINKFILE * pBinkFileInfo; // r0
}

// Range: 0x80600E84 -> 0x80600EEC
static unsigned int BinkFileIdle(struct BINKIO * pBinkIO /* r31 */) {}

// Range: 0x80600EEC -> 0x80600F1C
static void BinkFileSetInfo(unsigned int iBufferSize /* r5 */) {
    // Local variables
    struct BINKFILE * pBinkFileInfo; // r0
}

// Range: 0x80600F1C -> 0x80600FA8
static int BinkFileBGControl(struct BINKIO * pBinkIO /* r31 */) {}


