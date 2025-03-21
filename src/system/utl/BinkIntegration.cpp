#include "utl/BinkIntegration.h"
#include "os/File.h"
#include "utl/MemMgr.h"
#include <string.h>

void BinkInit() {}

void BinkFree(void *mem) { _MemFree(mem); }

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
