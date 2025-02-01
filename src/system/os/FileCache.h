#pragma once
#include "utl/FilePath.h"
#include "utl/Loader.h"
#include "os/Debug.h"

class FileCacheEntry;

class FileCacheFile : public File {
public:
    FileCacheFile(FileCacheEntry *);
    virtual ~FileCacheFile();
    virtual int Read(void *, int);
    virtual bool ReadAsync(void *, int);
    virtual int Write(const void *, int) {
        MILO_FAIL("not implemented");
        return 0;
    }
    virtual int Seek(int, int);
    virtual int Tell();
    virtual void Flush() {}
    virtual bool Eof();
    virtual bool Fail();
    virtual int Size();
    virtual int UncompressedSize() { return 0; }
    virtual bool ReadDone(int &);
    virtual int GetFileHandle(DVDFileInfo *&) { return 0; }

    NEW_POOL_OVERLOAD(FileCacheFile);
    DELETE_POOL_OVERLOAD(FileCacheFile);

    FileCacheEntry *mParent; // 0x4
    int mBytesRead; // 0x8
    void *mData; // 0xc
    int mPos; // 0x10
};

class FileCacheEntry {
public:
    FileCacheEntry(const FilePath &filename, const FilePath &readfilename, int prio)
        : mFileName(filename), mReadFileName(readfilename), mBuf(0), mLoader(0),
          mSize(-1), mRefCount(0), mPriority(prio), mReads(0), mLastRead(-kHugeFloat) {}
    FileCacheEntry(const FilePath &filename, char *buf, int size)
        : mFileName(filename), mReadFileName(filename), mBuf(buf), mLoader(0),
          mSize(size), mRefCount(0), mPriority(-1), mReads(0), mLastRead(-kHugeFloat) {}
    ~FileCacheEntry();
    void AddRef() {
        mRefCount++;
        mReads++;
    }
    void Release() { mRefCount--; }
    int Size() const { return mSize; }
    bool Fail() const { return !mSize && !mBuf; }
    const char *Buf() const { return mBuf; }
    bool ReadDone(bool bbb) {
        if (!bbb)
            mLastRead = SystemMs();
        if (mSize > -1)
            return true;
        if (!mLoader || !mLoader->IsLoaded())
            return false;
        else {
            mSize = mLoader->GetSize();
            mBuf = mLoader->GetBuffer(0);
            RELEASE(mLoader);
            return true;
        }
    }
    File *MakeFile() {
        if (!ReadDone(false) || Fail())
            return nullptr;
        else
            return new FileCacheFile(this);
    }
    bool CheckSize() const { return mSize > -1; }
    void StartRead(LoaderPos pos, bool b);

    NEW_POOL_OVERLOAD(FileCacheEntry);
    DELETE_POOL_OVERLOAD(FileCacheEntry);

    FilePath mFileName; // 0x0
    FilePath mReadFileName; // 0xc
    const char *mBuf; // 0x18
    FileLoader *mLoader; // 0x1c
    int mSize; // 0x20
    int mRefCount; // 0x24
    int mPriority; // 0x28
    int mReads; // 0x2c
    float mLastRead; // 0x30
};

class FileCache {
public:
    FileCache(int, LoaderPos, bool);
    ~FileCache();
    bool DoneCaching();
    void Clear();
    void StartSet(int);
    void EndSet();
    void Add(const FilePath &, int, const FilePath &);
    void Add(const FilePath &, char *, int);
    bool FileCached(const char *);
    void Poll();
    File *GetFile(const char *);
    int CurSize() const;
    void DumpOverSize(int);

    static void Init();
    static void Terminate();
    static void PollAll();
    static File *GetFileAll(const char *);

    int mMaxSize; // 0x0
    bool mTryClear; // 0x4
    std::vector<FileCacheEntry *> mEntries; // 0x8
    LoaderPos unk10; // 0x10
    bool unk14; // 0x14
};
