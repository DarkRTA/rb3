#include "os/ArkFile.h"
#include "os/Debug.h"
#include "os/File.h"
#include "os/Archive.h"
#include "os/BlockMgr.h"
#include "os/CDReader.h"
#include "os/System.h"
#include "utl/Loader.h"

ArkFile::ArkFile(const char* iFilename, int iMode) : mNumOutstandingTasks(0), mBytesRead(0), mTell(0), mFail(0), mReadAhead(true), mFilename(iFilename) {
    bool fileinfores = TheArchive->GetFileInfo(FileMakePath(".", iFilename, 0), mArkfileNum, mByteStart, mSize, mUCSize);
    if(!fileinfores || (iMode & 4)){
        mFail = 1;
    }
}

ArkFile::~ArkFile(){
    if(mNumOutstandingTasks > 0)
        TheBlockMgr.KillBlockRequests(this);
}

int ArkFile::Read(void *c, int a) {
    if(ReadAsync(c, a) == 0) return 0;
    int ret = -1;
    while(ReadDone(ret) == 0);
    return ret;
}

bool ArkFile::ReadAsync(void* iBuff, int iBytes){
    MILO_ASSERT(iBytes >= 0, 0x5A);
    if(mTell == mSize || mNumOutstandingTasks != 0) return false;
    else {
        mBytesRead = 0;
        if(iBytes == 0) return true;
        if(mReadAhead){
            unsigned int last = mFilename.find_last_of('_');
            bool met = last != String::npos;
            if(met){
                Symbol plat = PlatformSymbol(TheLoadMgr.GetPlatform());
                const char* strIdx = mFilename.c_str() + last + 1;
                met = plat == strIdx;
            }
            String someStrIdk(met ? mFilename.substr(0, last) : mFilename);
            TheArchive->HasArchivePermission(mArkfileNum);
            if(Archive::DebugArkOrder() != 0){
                TheDebug << MakeString("ArkFile%d:   '%s'\n", mArkfileNum, someStrIdk.c_str());
            }
        }
        mReadAhead = false;
        if(mTell + iBytes > mSize){
            iBytes = mSize - mTell;
        }
        MILO_ASSERT(iBytes >= 0, 0x82);
        // more crap goes here
        return true;
    }
}

int ArkFile::Write(const void*, int){
    TheDebug.Fail(MakeString("ERROR: Cannot write to a file in an archive!"));
    return 0;
}

int ArkFile::Seek(int offset, int mode) {
    switch (mode) {
    case 0:
        mTell = offset;
        break;
    case 1:
        mTell += offset;
        break;
    case 2:
        mTell = mSize + offset;
        break;
    default:
        break;
    }
    return mTell;
}

int ArkFile::Tell(){
    return mTell;
}

bool ArkFile::Eof() {
    return (mSize - mTell) == 0;
}

bool ArkFile::Fail() {
    return (mFail != 0);
}

int ArkFile::Size(){
    return mSize;
}

int ArkFile::UncompressedSize(){
    return mUCSize;
}

void ArkFile::TaskDone(int a) {
    mNumOutstandingTasks--;
    mBytesRead += a;
    mTell += a;
}

bool ArkFile::ReadDone(int& i){
    TheBlockMgr.Poll();
    i = mBytesRead;
    return mNumOutstandingTasks == 0;
}

int ArkFile::GetFileHandle(DVDFileInfo*& info){
    return CDReadExternal(info, mArkfileNum, mByteStart + mTell);
}