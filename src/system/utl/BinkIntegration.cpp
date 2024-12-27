#include "utl/BinkIntegration.h"
#include "os/File.h"
#include <string.h>

void BinkInit(){

}

bool BinkFileOpen(BINKIO* bink, const char* cc, unsigned int ui){
    memset(bink, 0, sizeof(BINKIO));
    if(ui & 0x800000){
        const char** binkCCData = (const char**)&bink->file;
        *binkCCData = cc;
    }
    else {
        File* file = NewFile(cc, 2);
        bink->file = file;
        bink->unk58 = 1;        
        if(!file) return false;
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