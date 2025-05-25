#pragma once
#include "os/File.h"
#include "utl/BINK.h"
#include "utl/EncryptXTEA.h"

typedef struct _BINKENCRYPTIONHEADER {
    unsigned int mSignature; // 0x0
    unsigned int mVersion; // 0x4
    unsigned int mKeyIndex; // 0x8
    unsigned int mMagicA; // 0xc
    unsigned int mMagicB; // 0x10
    unsigned long long mNonce[2]; // 0x18
    unsigned char mKeyMask[0x10]; // 0x28
} BINKENCRYPTIONHEADER;

typedef struct _BINKFILE {
    File *pFile; // 0x0
    unsigned int iCloseFile; // 0x4
    unsigned char *pBuffer; // 0x8
    unsigned char *pBufEnd; // 0xC
    unsigned char *pBufPos; // 0x10
    unsigned char *pBufBack; // 0x14
    unsigned int iBufEmpty; // 0x18
    unsigned int iFileBufPos; // 0x1c
    unsigned int iSimulateBPS; // 0x20
    unsigned int iShowSpeed; // 0x24
    unsigned int iHeaderSize; // 0x28
    BINKENCRYPTIONHEADER mEncryptionHeader; // 0x30
    XTEABlockEncrypter *pXTEADecrypter; // 0x68
} BINKFILE;

void BinkInit();
void *BinkAlloc(unsigned int);
void BinkFree(void *);
void intelendian(void *, unsigned int);
bool BinkFileOpen(BINKIO *, const char *, unsigned int);
unsigned int BinkFileReadHeader(BINKIO *, int, void *, unsigned int);
void ReadFunc(BINKIO *, bool);
unsigned int BinkFileReadFrame(BINKIO *, unsigned int, int, void *, unsigned int);
unsigned int BinkFileGetBufferSize(BINKIO *, unsigned int);
void BinkFileSetInfo(BINKIO *, void *, unsigned int, unsigned int, unsigned int);
unsigned int BinkFileIdle(BINKIO *);
void BinkFileClose(BINKIO *);
int BinkFileBGControl(BINKIO *, unsigned int);