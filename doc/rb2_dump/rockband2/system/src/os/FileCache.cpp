/*
    Compile unit: C:\rockband2\system\src\os\FileCache.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805B2644 -> 0x805B39C8
*/
class list : public _List_base {
    // total size: 0x8
};
static class list gCaches; // size: 0x8, address: 0x809854B8
class FileCacheFile : public File {
    // total size: 0x14
protected:
    class FileCacheEntry * mParent; // offset 0x4, size 0x4
    int mBytesRead; // offset 0x8, size 0x4
    void * mData; // offset 0xC, size 0x4
    int mPos; // offset 0x10, size 0x4
};
// Range: 0x805B2644 -> 0x805B2680
void * FileCacheFile::FileCacheFile() {
    // References
    // -> struct [anonymous] __vt__13FileCacheFile;
}

// Range: 0x805B2680 -> 0x805B26E4
void * FileCacheFile::~FileCacheFile(class FileCacheFile * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__13FileCacheFile;
}

// Range: 0x805B26E4 -> 0x805B27F0
int FileCacheFile::Read(class FileCacheFile * const this /* r31 */, void * iData /* r29 */, int iBytes /* r1+0x8 */) {
    // Local variables
    int size; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B27F0 -> 0x805B2994
unsigned char FileCacheFile::ReadAsync(class FileCacheFile * const this /* r28 */, void * iData /* r29 */, int iBytes /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B2994 -> 0x805B2B0C
unsigned char FileCacheFile::ReadDone(class FileCacheFile * const this /* r29 */, int & oBytes /* r30 */) {}

// Range: 0x805B2B0C -> 0x805B2BC8
int FileCacheFile::Seek(class FileCacheFile * const this /* r30 */, int iOffset /* r31 */) {
    // Local variables
    int i; // [invalid]
}

// Range: 0x805B2BC8 -> 0x805B2BD0
int FileCacheFile::Tell() {}

// Range: 0x805B2BD0 -> 0x805B2BF0
unsigned char FileCacheFile::Eof() {}

// Range: 0x805B2BF0 -> 0x805B2BFC
int FileCacheFile::Size() {}

// Range: 0x805B2BFC -> 0x805B2C24
unsigned char FileCacheFile::Fail() {}

// Range: 0x805B2C24 -> 0x805B2C28
void FileCache::Init() {}

// Range: 0x805B2C28 -> 0x805B2C2C
void FileCache::Terminate() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x805B2C2C -> 0x805B2C8C
void FileCache::PollAll() {
    // Local variables
    struct _List_iterator it; // r1+0x10

    // References
    // -> static class list gCaches;
}

// Range: 0x805B2C8C -> 0x805B2D0C
class File * FileCache::GetFileAll(const char * file /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x10
    class File * f; // r0

    // References
    // -> static class list gCaches;
}

// Range: 0x805B2D0C -> 0x805B2DF4
unsigned char FileCache::FileCached(class FileCache * const this /* r29 */, const char * file /* r30 */) {
    // Local variables
    class FilePath p; // r1+0x14
    class File * f; // r0

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x805B2DF4 -> 0x805B2E98
void * FileCache::FileCache(class FileCache * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std23_List_node<P9FileCache>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class list gCaches;
}

class FileCacheEntry {
    // total size: 0x38
protected:
    class FilePath mFileName; // offset 0x0, size 0xC
    class FilePath mReadFileName; // offset 0xC, size 0xC
    char * mBuf; // offset 0x18, size 0x4
    class FileLoader * mLoader; // offset 0x1C, size 0x4
    int mSize; // offset 0x20, size 0x4
    int mRefCount; // offset 0x24, size 0x4
    int mPriority; // offset 0x28, size 0x4
    int mReads; // offset 0x2C, size 0x4
    float mLastRead; // offset 0x30, size 0x4
    class DataArray * mSongData; // offset 0x34, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std23_List_node<P9FileCache>; // size: 0x8, address: 0x80923898
// Range: 0x805B2E98 -> 0x805B3130
void * FileCache::~FileCache(class FileCache * const this /* r1+0x8 */) {
    // Local variables
    int i; // r28

    // References
    // -> static class list gCaches;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B3130 -> 0x805B32E8
void FileCache::StartSet(class FileCache * const this /* r29 */, int priority /* r30 */) {
    // Local variables
    int i; // r31
    class FileCacheEntry * e; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B32E8 -> 0x805B3338
void FileCache::EndSet(class FileCache * const this /* r31 */) {}

struct Priority {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x805B3338 -> 0x805B3348
void FileCache::Clear() {}

// Range: 0x805B3348 -> 0x805B3398
int FileCache::CurSize() {
    // Local variables
    int size; // r5
    int i; // r6
}

// Range: 0x805B3398 -> 0x805B3574
void FileCache::DumpOverSize(class FileCache * const this /* r28 */, int maxSize /* r29 */) {
    // Local variables
    int total; // r31
    int worstEntry; // r30
    int worstPriority; // r4
    float worstRead; // f1
    int i; // r5
    class FileCacheEntry * e; // r3
    class FileCacheEntry * e; // r27

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B3574 -> 0x805B37E4
void FileCache::Poll(class FileCache * const this /* r30 */) {
    // Local variables
    int fileCount; // r31
    int i; // r29
    class FileCacheEntry * e; // r28
    int i; // r28
    class FileCacheEntry * e; // r29

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805B37E4 -> 0x805B38EC
unsigned char FileCache::DoneCaching(class FileCache * const this /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x805B38EC -> 0x805B38F4
int FileCacheFile::UncompressedSize() {}

// Range: 0x805B38F4 -> 0x805B38F8
void FileCacheFile::Flush() {}

// Range: 0x805B38F8 -> 0x805B3940
int FileCacheFile::Write() {
    // References
    // -> class Debug TheDebug;
}

struct {
    // total size: 0x38
} __vt__13FileCacheFile; // size: 0x38, address: 0x809238D0
struct {
    // total size: 0x8
} __RTTI__13FileCacheFile; // size: 0x8, address: 0x80923928
// Range: 0x805B3940 -> 0x805B396C
void _Vector_base::_M_throw_length_error() {}

struct {
    // total size: 0x8
} __RTTI__PP14FileCacheEntry; // size: 0x8, address: 0x80923950
// Range: 0x805B396C -> 0x805B39C8
static void __sinit_\FileCache_cpp() {
    // References
    // -> static class list gCaches;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class FileCache * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};

