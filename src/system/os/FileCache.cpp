#include "os/FileCache.h"
#include "os/Debug.h"
#include "obj/DirLoader.h"

std::list<FileCache*> gCaches;

FileCacheFile::FileCacheFile(FileCacheEntry* entry) : mParent(entry), mBytesRead(0), mData(0), mPos(0) {
    entry->AddRef();
}

FileCacheFile::~FileCacheFile(){
    mParent->Release();
}

int FileCacheFile::Read(void* iData, int iBytes){
    MILO_ASSERT(!mData, 0x103);
    mBytesRead = iBytes;
    if(mParent->Fail()) return 0;
    else {
        int bytesRead = Min(iBytes, mParent->Size() - mPos);
        memcpy(iData, mParent->Buf() + mPos, bytesRead);
        mBytesRead = bytesRead;
        mPos += bytesRead;
        return bytesRead;
    }
}

bool FileCacheFile::ReadAsync(void* v, int i){
    if(mParent->ReadDone(false)){
        if(mParent->Fail()) return false;
        else {
            Read(v, i);
            return true;
        }
    }
    else {
        mBytesRead = i;
        mData = v;
        return true;
    }
}

bool FileCacheFile::ReadDone(int& iref){
    if(!mParent->ReadDone(false)){
        iref = 0;
        return false;
    }
    else {
        if(mParent->Fail()) return false;
        else {
            void* buf = mData;
            if(buf){
                mData = 0;
                Read(buf, mBytesRead);
            }
            iref = mBytesRead;
            return true;
        }
    }
}

int FileCacheFile::Seek(int i1, int i2){
    int ret;
    switch(i2){
        case 0:
            ret = i1;
            break;
        case 1:
            ret = Tell() + i1;
            break;
        case 2:
            ret = mParent->Size() + i1;
            break;
        default:
            return mPos;
    }
    ClampEq(ret, 0, mParent->Size());
    mPos = ret;
    return mPos;
}

bool FileCacheFile::Eof(){
    return mParent->Size() <= mPos;
}

int FileCacheFile::Tell(){
    return mPos;
}

int FileCacheFile::Size(){
    return mParent->Size();
}

bool FileCacheFile::Fail(){
    return mParent->Fail();
}

void FileCache::Init(){}
void FileCache::Terminate(){}

void FileCache::PollAll(){
    for(std::list<FileCache*>::iterator it = gCaches.begin(); it != gCaches.end(); ++it){
        (*it)->Poll();
    }
}

File* FileCache::GetFileAll(const char* cc){
    for(std::list<FileCache*>::iterator it = gCaches.begin(); it != gCaches.end(); ++it){
        File* file = (*it)->GetFile(cc);
        if(file) return file;
    }
    return nullptr;
}

bool FileCache::FileCached(const char* cc){
    FilePath path(DirLoader::CachedPath(cc, 0));
    File* file = GetFile(path.c_str());
    if(file){
        delete file;
        return true;
    }
    else return false;
}