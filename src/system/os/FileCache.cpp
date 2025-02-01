#include "os/FileCache.h"
#include "os/Debug.h"
#include "obj/DirLoader.h"
#include "rndobj/Utl.h"
#include "synth/Utl.h"

std::list<FileCache *> gCaches;

inline FileCacheEntry::~FileCacheEntry() {
    MILO_ASSERT(mRefCount == 0, 0x88);
    delete mLoader;
    _MemFree((void *)mBuf);
}

FileCacheFile::FileCacheFile(FileCacheEntry *entry)
    : mParent(entry), mBytesRead(0), mData(0), mPos(0) {
    entry->AddRef();
}

FileCacheFile::~FileCacheFile() { mParent->Release(); }

int FileCacheFile::Read(void *iData, int iBytes) {
    MILO_ASSERT(!mData, 0x103);
    mBytesRead = iBytes;
    if (mParent->Fail())
        return 0;
    else {
        int bytesRead = Min(iBytes, mParent->Size() - mPos);
        memcpy(iData, mParent->Buf() + mPos, bytesRead);
        mBytesRead = bytesRead;
        mPos += bytesRead;
        return bytesRead;
    }
}

bool FileCacheFile::ReadAsync(void *v, int i) {
    MILO_ASSERT(!mData, 0x117);
    if (mParent->ReadDone(false)) {
        if (mParent->Fail())
            return false;
        else {
            Read(v, i);
            return true;
        }
    } else {
        mBytesRead = i;
        mData = v;
        return true;
    }
}

bool FileCacheFile::ReadDone(int &iref) {
    if (!mParent->ReadDone(false)) {
        iref = 0;
        return false;
    } else {
        if (mParent->Fail())
            return false;
        else {
            void *buf = mData;
            if (buf) {
                mData = 0;
                Read(buf, mBytesRead);
            }
            iref = mBytesRead;
            return true;
        }
    }
}

int FileCacheFile::Seek(int i1, int i2) {
    int ret;
    switch (i2) {
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

bool FileCacheFile::Eof() { return mParent->Size() <= mPos; }

int FileCacheFile::Tell() { return mPos; }

int FileCacheFile::Size() { return mParent->Size(); }

bool FileCacheFile::Fail() { return mParent->Fail(); }

void FileCache::Init() {}
void FileCache::Terminate() {}

void FileCache::PollAll() {
    for (std::list<FileCache *>::iterator it = gCaches.begin(); it != gCaches.end();
         ++it) {
        (*it)->Poll();
    }
}

File *FileCache::GetFileAll(const char *cc) {
    for (std::list<FileCache *>::iterator it = gCaches.begin(); it != gCaches.end();
         ++it) {
        File *file = (*it)->GetFile(cc);
        if (file)
            return file;
    }
    return nullptr;
}

bool FileCache::FileCached(const char *cc) {
    FilePath path(DirLoader::CachedPath(cc, 0));
    File *file = GetFile(path.c_str());
    if (file) {
        delete file;
        return true;
    } else
        return false;
}

FileCache::FileCache(int i1, LoaderPos pos, bool b3)
    : mMaxSize(i1), mTryClear(0), unk10(pos), unk14(b3) {
    gCaches.push_back(this);
    mEntries.reserve(0x200);
}

FileCache::~FileCache() {
    for (int i = 0; i < mEntries.size(); i++)
        delete mEntries[i];
    gCaches.erase(std::find(gCaches.begin(), gCaches.end(), this), gCaches.end());
}

void FileCache::StartSet(int iii) {
    mTryClear = false;
    for (int i = 0; i < mEntries.size(); i++) {
        FileCacheEntry *curEntry = mEntries[i];
        if ((!curEntry->CheckSize() || curEntry->Fail()) && !curEntry->mLoader
            && !curEntry->mRefCount) {
            delete curEntry;
            mEntries.erase(mEntries.begin() + i);
            i--;
        } else {
            mEntries[i]->mPriority = iii;
        }
    }
}

struct Priority {
    bool operator()(FileCacheEntry *e1, FileCacheEntry *e2) const {
        return e1->mPriority > e2->mPriority;
    }
};

void FileCache::EndSet() {
    mTryClear = false;
    std::sort(mEntries.begin(), mEntries.end(), Priority());
    Poll();
}

void FileCache::Add(const FilePath &fp1, int iii, const FilePath &fp2) {
    mTryClear = false;
    FilePath file;
    const char *ext = FileGetExt(fp1.c_str());
    if (streq(ext, "milo")) {
        file.SetRoot(DirLoader::CachedPath(fp1.c_str(), 0));
    } else if (streq(ext, "png") || streq(ext, "bmp")) {
        file.SetRoot(CacheResource(fp1.c_str(), 0));
    } else if (streq(ext, "wav")) {
        CacheResourceResult res;
        file.SetRoot(CacheWav(fp1.c_str(), res));
    } else
        file = fp1;

    for (int i = 0; i < mEntries.size(); i++) {
        if (file == mEntries[i]->mFileName) {
            MaxEq(mEntries[i]->mPriority, iii);
            return;
        }
    }
    MILO_ASSERT(GetFileAll(file.c_str()) == NULL, 0x203);
    FilePath fp30;
    if (fp2.empty())
        fp30 = file;
    else
        fp30.SetRoot(DirLoader::CachedPath(fp2.c_str(), 0));
    mEntries.push_back(new FileCacheEntry(file, fp30, iii));
}

void FileCache::Add(const FilePath &fp, char *c, int iii) {
    mTryClear = false;
    FilePath file(DirLoader::CachedPath(fp.c_str(), 0));
    for (int i = 0; i < mEntries.size(); i++) {
        if (file == mEntries[i]->mFileName) {
            return;
        }
    }
    MILO_ASSERT(GetFileAll(file.c_str()) == NULL, 0x226);
    mEntries.push_back(new FileCacheEntry(file, c, iii));
}

void FileCache::Clear() {
    mTryClear = true;
    for (int i = 0; i < mEntries.size();) {
        FileCacheEntry *curEntry = mEntries[i];
        if (!curEntry->mLoader && !curEntry->mRefCount) {
            delete curEntry;
            mEntries.erase(mEntries.begin() + i);
        } else
            i++;
    }
}

File *FileCache::GetFile(const char *cc) {
    FilePathTracker tracker(".");
    FilePath file(cc);
    for (int i = 0; i < mEntries.size(); i++) {
        FileCacheEntry *curEntry = mEntries[i];
        if (curEntry->mFileName == file) {
            return curEntry->MakeFile();
        }
    }
    return nullptr;
}

int FileCache::CurSize() const {
    int size = 0;
    for (int i = 0; i < mEntries.size(); i++) {
        if (mEntries[i]->CheckSize()) {
            size += mEntries[i]->mSize;
        }
    }
    return size;
}

// FilePath mFileName; // 0x0
// FilePath mReadFileName; // 0xc
// const char* mBuf; // 0x18
// FileLoader* mLoader; // 0x1c
// int mSize; // 0x20
// int mRefCount; // 0x24
// int mPriority; // 0x28
// int mReads; // 0x2c
// float mLastRead; // 0x30

void FileCache::DumpOverSize(int iii) {
    int i2 = CurSize();
    while (i2 > iii) {
        float f1 = 0;
        int u9 = -1;
        int i8 = 0;
        for (int i = 0; i < mEntries.size(); i++) {
            FileCacheEntry *curEntry = mEntries[i];
            if (curEntry->CheckSize() && !curEntry->mLoader && !curEntry->mRefCount
                && (u9 == -1 || curEntry->mPriority < i8
                    || (curEntry->mPriority == i8 && curEntry->mLastRead < f1))) {
                i8 = curEntry->mPriority;
                f1 = curEntry->mLastRead;
                u9 = i;
            }
        }
        if (u9 == -1)
            break;
        FileCacheEntry *delEntry = mEntries[u9];
        i2 -= delEntry->mSize;
        delete delEntry;
        mEntries.erase(mEntries.begin() + u9);
    }
}

inline void FileCacheEntry::StartRead(LoaderPos pos, bool b) {
    MILO_ASSERT(mLoader == NULL, 0xA0);
    MILO_ASSERT(!mBuf, 0xA1);
    MILO_ASSERT(mSize == -1, 0xA2);
    mLoader = new FileLoader(mReadFileName, mReadFileName.c_str(), pos, 0x20000, b, 0, 0);
}

void FileCache::Poll() {
    int i8 = 1;
    for (int i = 0; i < mEntries.size(); i++) {
        FileCacheEntry *curEntry = mEntries[i];
        curEntry->ReadDone(true);
        if (curEntry->mLoader)
            i8--;
    }
    DumpOverSize(mTryClear ? 0 : mMaxSize);
    for (int i = 0; i < mEntries.size() && i8 > 0; i++) {
        FileCacheEntry *curEntry = mEntries[i];
        if (!curEntry->CheckSize() && !curEntry->mLoader) {
            curEntry->StartRead(unk10, unk14);
            i8--;
        }
    }
}

bool FileCache::DoneCaching() {
    for (int i = 0; i < mEntries.size(); i++) {
        if (!mEntries[i]->ReadDone(true))
            return false;
    }
    return true;
}