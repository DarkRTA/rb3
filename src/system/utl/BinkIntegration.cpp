#include "utl/BinkIntegration.h"
#include "os/File.h"
#include "utl/MemMgr.h"
#include <cstdlib>
#include <string.h>

void BinkInit() {}

void BinkFree(void *mem) { _MemFree(mem); }

void *BinkAlloc(unsigned int size) { _MemAlloc(size, 128); }

unsigned int BinkFileIdle(BINKIO *bink) {
    if (bink->ReadError) {
        return 0;
    }
    if (bink->Suspended) {
        return 0;
    }
    if (bink->DoingARead) {
        return NULL; // wtf is ReadFunc?
    }
}

unsigned int BinkFileGetBufferSize(BINKIO *bink, unsigned int size) {
    unsigned int result = (size + 0x7fff) & 0xffff8000;
    if (result < 0x10000) {
        result = 0x10000;
    }
    return result;
}

void BinkFileSetInfo(
    BINKIO *bink, void *unk1, unsigned int unk2, unsigned int unk3, unsigned int unk4
) {
    bink->BufSize = 0;
    bink->CurBufUsed = 0;
}

bool BinkFileOpen(BINKIO *bink, const char *cc, unsigned int ui) {
    memset(bink, 0, sizeof(BINKIO));
    if (ui & 0x800000) {
        const char **binkCCData =
            reinterpret_cast<const char **>(const_cast<unsigned char *>(&bink->iodata[0])
            );
        *binkCCData = cc;
    } else {
        File *file = NewFile(cc, 2);
        *reinterpret_cast<File **>(const_cast<unsigned char *>(&bink->iodata[0])) = file;
        *reinterpret_cast<int *>(const_cast<unsigned char *>(&bink->iodata[4])) = 1;
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
