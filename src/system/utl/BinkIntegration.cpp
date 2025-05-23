#include "utl/BinkIntegration.h"
#include "obj/DataFile.h"
#include "os/File.h"
#include "os/Debug.h"
#include "KeyChain.h"
#include "synth/Synth.h"
#include "utl/EncryptXTEA.h"
#include <string.h>

void BinkInit() {
    // BinkSetMemory(BinkAlloc, BinkFree);
    // BinkSetIO(BinkFileOpen);
    // RADARAMCALLBACKS aram_callbacks = {BinkAlloc, BinkFree};
    // BinkSetSoundSystem(BinkOpenAX, aram_callbacks);
    // AXSetCompressor(0);
}

void *BinkAlloc(unsigned int size) { _MemAlloc(size, 128); }

void BinkFree(void *mem) { _MemFree(mem); }

void intelendian(void *, unsigned int) {}

bool BinkFileOpen(BINKIO *bink, const char *cc, unsigned int ui) {
    memset(bink, 0, sizeof(BINKIO));
    if (ui & 0x800000) {
        const char **binkCCData =
            reinterpret_cast<const char **>(const_cast<unsigned char *>(&bink->iodata[0])
            );
        *binkCCData = cc;
    } else {
        File *file = NewFile(cc, 2);
        ((BINKFILE *)bink->iodata)->pFile = file;
        ((BINKFILE *)bink->iodata)->iCloseFile = 1;
        if (!file)
            return false;
    }
    bink->ReadHeader = BinkFileReadHeader;
    bink->ReadFrame = BinkFileReadFrame;
    bink->GetBufferSize = BinkFileGetBufferSize;
    bink->SetInfo = BinkFileSetInfo;
    bink->Idle = BinkFileIdle;
    bink->Close = BinkFileClose;
    bink->BGControl = BinkFileBGControl;
    return true;
}

#define BSWAP(i)                                                                         \
    (((i) & 0xff) << 24 | ((i) & 0xff00) << 8 | ((i) & 0xff0000) >> 8                    \
     | ((i) >> 24) & 0xff)

unsigned int BinkFileReadHeader(BINKIO *bink, int, void *header, unsigned int length) {
    BINKENCRYPTIONHEADER *encHeader = &((BINKFILE *)bink->iodata)->mEncryptionHeader;
    File *file = (File *)&bink->iodata[0];
    // check if we've read a file header before
    if (encHeader->mSignature == 0) {
        // read the header
        int encread = file->Read(encHeader, sizeof(BINKENCRYPTIONHEADER));
        // byteswap mSignature through mMagicB from bad endian to big endian
        intelendian(encHeader, 0x14);
        // byteswap mNonce (THIS DOESNT MATCH!)
        unsigned int nonceSwap[4];
        nonceSwap[0] = (unsigned int)(encHeader->mNonce[0] >> 32);
        nonceSwap[2] = (unsigned int)(encHeader->mNonce[1] >> 32);
        nonceSwap[1] = (unsigned int)(encHeader->mNonce[0]);
        nonceSwap[3] = (unsigned int)(encHeader->mNonce[1]);
        encHeader->mNonce[0] = BSWAP(nonceSwap[1]) << 32 | BSWAP(nonceSwap[0]);
        encHeader->mNonce[1] = BSWAP(nonceSwap[3]) << 32 | BSWAP(nonceSwap[2]);
        // check if the header is BIKE
        int whatever = encHeader->mSignature - 0x45420000; // 'BI--'
        if (whatever == 0x494B) { // '--KE'
            XTEABlockEncrypter *decrypter = new XTEABlockEncrypter;
            ((BINKFILE *)bink->iodata)->pXTEADecrypter = decrypter;

            // perform the key derivation step
            DataArray *arr = DataReadString("{Na 42 'O32'}");
            unsigned int iEval = arr->Evaluate(0).Int();
            arr->Release();

            char i6 = (iEval % 13);
            i6 = i6 + 'A';
            char script[256];
            unsigned char masterKey[256];
            sprintf(script, "{%c %d %c}", i6, (int)masterKey ^ iEval, i6);
            DataArray *buf118Arr = DataReadString(script);
            buf118Arr->Evaluate(0);
            buf118Arr->Release();

            unsigned char key[0x10];
            KeyChain::getKey(encHeader->mKeyIndex, key, masterKey);
            TheSynth->mGrinder.GrindArray(
                encHeader->mMagicA, encHeader->mMagicB, key, 0x10, 0x1D
            );
            for (int i = 0; i < 16; i++) {
                key[i] ^= encHeader->mKeyMask[i];
            }

            // endian swap the key for use in XTEA and prepare the decrypter
            intelendian(key, 0x10);
            ((BINKFILE *)bink->iodata)->pXTEADecrypter->SetKey(key);
            ((BINKFILE *)bink->iodata)->pXTEADecrypter->SetNonce(encHeader->mNonce, 0);
            ((BINKFILE *)bink->iodata)->iFileBufPos += encread;
        } else {
            // it's not an encrypted BIK, seek back in the file and act like this never
            // happened
            memset(encHeader, 0, encread);
            file->Seek(-encread, SEEK_CUR);
            BINK *curBink = bink->bink;
            // only warn if this is a multitrack?
            if (curBink != NULL && curBink->NumTracks >= 2 && curBink->Width < 8) {
                MILO_WARN("Attempting read of unsecure Bink song file!\n");
            }
        }
    }
    // read the actual bink file header
    int r = file->Read(header, length);
    if (r != length) {
        bink->ReadError = 1;
    }
    ((BINKFILE *)bink->iodata)->iHeaderSize += r;
    ((BINKFILE *)bink->iodata)->iFileBufPos += r;
    int size = file->Size();
    int anothersize = size - ((BINKFILE *)bink->iodata)->iFileBufPos;
    if (bink->BufSize <= anothersize) {
        anothersize = bink->BufSize;
    }
    bink->CurBufSize = anothersize;
    intelendian(header, r);
    return r;
}

void ReadFunc(BINKIO *bink, bool r4) {
    BINKFILE *bf = (BINKFILE *)bink->iodata;
    if (bink->DoingARead) {
        int lengthRead;
        if (!bf->pFile->ReadDone(lengthRead))
            return;
        bink->DoingARead = 0;
        if (bf->mEncryptionHeader.mVersion == 2) {
            static Timer *_t = AutoTimer::GetTimer(Symbol("XTEA"));
            _t->Start();
            // XTEA encryption
            _t->Stop();
        } else {
            intelendian(bf->pBufBack, lengthRead);
        }
    }
    if (r4) {
        int fileSize = bf->pFile->Size();
        int filePos = bf->pFile->Tell();
        int diff = fileSize - filePos;
        if (bf->iBufEmpty < 0x8000 || bf->pFile->Eof()) {
            bink->CurBufSize = bink->CurBufUsed;
        } else {
            bink->DoingARead = 1;
            if (diff > 0x8000)
                diff = 0x8000;
            bf->pFile->ReadAsync(bf->pBufBack, diff);
        }
    }
}

unsigned int BinkFileReadFrame(BINKIO *, unsigned int, int, void *, unsigned int) {}

unsigned int BinkFileGetBufferSize(BINKIO *bink, unsigned int size) {
    unsigned int result = (size + 0x7fff) & 0xffff8000;
    if (result < 0x10000) {
        result = 0x10000;
    }
    return result;
}

void BinkFileClose(BINKIO *bink) {
    BINKFILE *bf = (BINKFILE *)bink->iodata;
    if (bf->iCloseFile != 0) {
        delete bf->pFile;
        bf->pFile = NULL;
    }
    if (bf->mEncryptionHeader.mVersion == 2) {
        delete bf->pXTEADecrypter;
    }
}

unsigned int BinkFileIdle(BINKIO *bink) {
    if (bink->ReadError) {
        return 0;
    }
    if (bink->Suspended) {
        return 0;
    }
    if (bink->DoingARead) {
        ReadFunc(bink, false);
    }
    return bink->DoingARead;
}

void BinkFileSetInfo(
    BINKIO *bink,
    void *pBuffer,
    unsigned int iBufferSize,
    unsigned int unk3,
    unsigned int unk4
) {
    int bufSize = iBufferSize & 0xFFFF8000;
    bink->BufSize = bufSize;
    BINKFILE *bf = (BINKFILE *)bink->iodata;
    bf->pBuffer = (unsigned char *)pBuffer;
    bf->pBufPos = (unsigned char *)pBuffer;
    bf->pBufBack = (unsigned char *)pBuffer;
    bf->pBufEnd = (unsigned char *)pBuffer + bufSize;
    bf->iBufEmpty = bufSize;
    bink->CurBufUsed = 0;
    bf->iSimulateBPS = unk4;
}

int BinkFileBGControl(BINKIO *bink, unsigned int flags) {
    if ((flags & 1) != 0) {
        if (bink->Suspended == 0) {
            bink->Suspended = 1;
        }
        if (flags & 0x80000000)
            while (bink->DoingARead)
                ;
    } else {
        if (flags & 2) {
            if (bink->Suspended == 1) {
                bink->Suspended = 0;
            }
            if (flags & 0x80000000) {
                BinkFileIdle(bink);
            }
        }
    }
    return bink->Suspended;
}
