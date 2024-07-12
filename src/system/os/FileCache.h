#ifndef OS_FILECACHE_H
#define OS_FILECACHE_H
#include "utl/FilePath.h"
#include "utl/Loader.h"

class FileCacheEntry {
public:
    FilePath mFileName;
    FilePath mReadFileName;
    const char* mBuf;
    FileLoader* mLoader;
    int mSize;
    int mRefCount;
    int mPriority;
    int mReads;
    float mLastRead;
    // DataArray * mSongData; // found in RB2
};

class FileCacheFile : public File {
public:
    FileCacheFile(FileCacheEntry*);
    virtual ~FileCacheFile();
    virtual int Read(void *, int);
    virtual bool ReadAsync(void *, int);
    virtual int Write(const void *, int);
    virtual int Seek(int, int);
    virtual int Tell();
    virtual void Flush();
    virtual bool Eof();
    virtual bool Fail();
    virtual int Size();
    virtual int UncompressedSize();
    virtual bool ReadDone(int &);
    virtual int GetFileHandle(DVDFileInfo*&);
    
    void operator delete(void* v){
        _PoolFree(sizeof(FileCacheFile), FastPool, v);
    }

    FileCacheEntry* mParent;
    int mBytesRead;
    void* mData;
    int mPos;
};

class FileCache {
public:
    FileCache(int, LoaderPos, bool);

    int mMaxSize;
    bool mTryClear;
    // vector mEntries
};

#endif
