#include "os/AsyncFile.h"
#include "os/Debug.h"
#include <string.h>
#include "os/File.h"
#include "utl/Loader.h"
#include "os/System.h"

static int gBufferSize = 0x20000;

void PrintDiscFile(const char* cc){
    const char* gen = "gen/";
    const char* path = FileGetPath(cc, 0);
    const char* base = FileGetBase(cc, 0);
    const char* ext = FileGetExt(cc);
    int miloCmp = strncmp(ext, "milo", 4);
    if(miloCmp == 0){
        DataArray* found = SystemConfig()->FindArray("force_milo_inline", false);
        if(found){
            for(int i = 1; i < found->Size(); i++){
                if(FileMatch(cc, found->Str(i))) return;
            }
        }
    }
    else {
        if(strncmp(ext, "wav", 3) == 0 || strncmp(ext, "bmp", 3) == 0 || strncmp(ext, "png", 3) == 0){
            if(strstr(cc, "_keep") == 0) return;
        }
        else {
            if(strncmp(ext, "dta", 3) == 0){
                gen = "";
            }
            else ext = "dtb";
        }
    }
    String fullPath(MakeString("%s/%s%s.%s", path, gen, base, ext));
    unsigned int last = fullPath.find_last_of('_');
    bool asdf = false;
    if(last != String::npos){
        if(PlatformSymbol(TheLoadMgr.mPlatform) == &fullPath[last + 1]){
            asdf = true;
        }
    }
    fullPath = (asdf) ? fullPath.substr(0, last) : fullPath;
    TheDebug << MakeString("AsyncFile:   '%s'\n", fullPath);
}

AsyncFile::AsyncFile(const char* c, int i) : mMode(i), mFail(false), unk9(0), mFilename(c), mTell(0), mOffset(0), mBuffer(0), mData(0), mBytesLeft(0) {

}

int AsyncFile::Read(void* iBuf, int iBytes){
    ReadAsync(iBuf, iBytes);
    if(mFail) return 0;
    else while(!ReadDone(iBytes));
    return iBytes;
}

int AsyncFile::Write(const void* iBuf, int iBytes){
    WriteAsync((void*)iBuf, iBytes);
    if(mFail) return 0;
    else while(!WriteDone(iBytes));
    return iBytes;
}

bool AsyncFile::ReadAsync(void* iBuff, int iBytes){
    MILO_ASSERT(iBytes >= 0, 299);
    MILO_ASSERT(mMode & FILE_OPEN_READ, 0x12D);
    if(mFail) return false;
    else {
        if(!mBuffer){
            _WriteAsync(iBuff, iBytes);
        }
        else {
            if(mTell + iBytes > mSize){
                iBytes = mSize - mTell;
            }
            MILO_ASSERT(iBytes >= 0, 0x13F);
            mData = (char*)iBuff;
            mBytesLeft = iBytes;
            mBytesRead = 0;
            ReadDone(iBytes);
        }
        return mFail == 0;
    }
}