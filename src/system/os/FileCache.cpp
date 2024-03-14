#include "os/FileCache.h"

FileCacheFile::FileCacheFile(FileCacheEntry* entry) : mParent(entry), mBytesRead(0), mData(0), mPos(0) {
    entry->mRefCount++;
    entry->mReads++;
}

FileCacheFile::~FileCacheFile(){
    mParent->mRefCount--;
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
