#include "os/FileCache.h"
#include "os/Debug.h"

FileCacheFile::FileCacheFile(FileCacheEntry* entry) : mParent(entry), mBytesRead(0), mData(0), mPos(0) {
    entry->mRefCount++;
    entry->mReads++;
}

FileCacheFile::~FileCacheFile(){
    mParent->mRefCount--;
}

int FileCacheFile::Read(void* iData, int iBytes){
    MILO_ASSERT(!mData, 0x103);
    mBytesRead = iBytes;
    bool b = (mParent->mSize == 0 && !mParent->mBuf);
    if(b){
        int size = mParent->mSize - mBytesRead;
        if(size < iBytes) iBytes = size;
        memcpy(iData, mParent->mBuf + mBytesRead, iBytes);
        mBytesRead = iBytes;
        mPos += iBytes;
    }
    else iBytes = 0;
    return iBytes;
}

int FileCacheFile::Tell(){
    return mPos;
}

int FileCacheFile::Size(){
    return mParent->mSize;
}

bool FileCacheFile::Fail(){
    return (mParent->mSize == 0) && (mParent->mBuf == 0);
}
