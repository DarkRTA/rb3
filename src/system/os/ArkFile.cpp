#include "os/ArkFile.h"
#include "os/AsyncTask.h"
#include "os/Debug.h"
#include "os/File.h"
#include "os/Archive.h"
#include "os/BlockMgr.h"
#include "os/CDReader.h"
#include "os/System.h"
#include "utl/Loader.h"
#include "utl/TextStream.h"

#ifndef MILO_DEBUG
int File::sOpenCount[4] = {0,0,0,0};
#endif

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
#ifndef MILO_DEBUG
        mReadAhead = false;
        if (mTell + iBytes > mSize) {
            iBytes = mSize - mTell;
        }
#endif
#ifdef MILO_DEBUG
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
#endif
        u64 byte_start = mByteStart + mTell;
        int a = 0, b = 0, c = 0;
        TheBlockMgr.GetAssociatedBlocks(mByteStart, iBytes, a, b, c);
        u64 byte_end = mByteStart + iBytes;
        int max = (b + c) - 1;
        bool first_loop = true; 
        for (int i = c; i <= max; i++) {
            u32 x;
            if (i == a) {
                x = byte_start % c;
            } else x = 0;
            u32 y = c;
            if (i == max && iBytes != 0) {
                u32 gjksf = byte_end % c;
                if (gjksf != 0) y = gjksf;
            }
            AsyncTask at(this, iBuff, mArkfileNum, i, x, y, mFilename.c_str());
            mNumOutstandingTasks++;
            iBuff = (void*)((u32)iBuff + (y - x));
            if (!first_loop || !at.FillData()) {
                first_loop = false;
                TheBlockMgr.AddTask(at);
            }
        }
        TheBlockMgr.Poll();
        return true;
    }
}

int ArkFile::Write(const void*, int){
#ifdef MILO_DEBUG
    MILO_FAIL("ERROR: Cannot write to a file in an archive!");
#endif
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