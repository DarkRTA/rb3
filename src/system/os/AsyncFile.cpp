#include "os/AsyncFile.h"
#include "os/Debug.h"
#include <string.h>
#include "os/File.h"
#include "utl/Loader.h"
#include "os/System.h"
#include "os/Archive.h"
#include "os/File_Wii.h"

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
    bool lastFound = last != String::npos;
    if(lastFound){
        Symbol plat = PlatformSymbol(TheLoadMgr.mPlatform);
        lastFound = plat == fullPath.c_str() + last + 1;
    }
    fullPath = (lastFound) ? fullPath.substr(0, last) : fullPath;
    TheDebug << MakeString("AsyncFile:   '%s'\n", fullPath);
}

extern bool UsingHolmes(int);

AsyncFile* AsyncFile::New(const char* cc, int i){
    if(Archive::DebugArkOrder() != 0) PrintDiscFile(cc);
    if(!UsingHolmes(4) || !(i & 4U) || FileIsLocal(cc)){

    }
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
            _ReadAsync(iBuff, iBytes);
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

bool AsyncFile::ReadDone(int& i){
    if(mFail){
        i = 0;
        return true;
    }
    else {
        if(mBuffer && mBytesLeft == 0){
            i = mBytesRead;
            return true;
        }
        else {
            if(!_ReadDone()){
                i = mBytesRead;
                return false;
            }
            else {
                if(!mBuffer) return true;
                else {
                    if(mOffset + mBytesLeft > gBufferSize){
                        int size = gBufferSize - mOffset;
                        memcpy(mData, mBuffer + mOffset, size);
                        mBytesRead += size;
                        mOffset = gBufferSize;
                        mTell += size;
                        mBytesLeft -= size;
                        mData += size;
                        FillBuffer();
                        i = mBytesRead;
                        return false;
                    }
                    else {
                        memcpy(mData, mBuffer + mOffset, mBytesLeft);
                        mOffset += mBytesLeft;
                        int ret = mBytesRead + mBytesLeft;
                        mTell += mBytesLeft;
                        mBytesLeft = 0;
                        mBytesRead = ret;
                        i = ret;
                        return true;
                    }
                }
            }
        }
    }
}

bool AsyncFile::WriteDone(int& i){
    if(mBuffer) return true;
    else return _WriteDone();
}