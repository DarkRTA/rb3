#include "os/CDReader.h"
#include <vector>

namespace {
    std::vector<DVDFileInfo> gArkFiles;
    std::vector<int> gFileLengths;
    int gPendingFile = -1;
}

int gRetryAttempts = 0x14;

int CDGetError(){ return 0; }

int CDReadExternal(DVDFileInfo*& info, int, unsigned long long){
    info = 0;
    return 0;
}