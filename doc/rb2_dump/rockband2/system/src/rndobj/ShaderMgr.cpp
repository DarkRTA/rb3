/*
    Compile unit: C:\rockband2\system\src\rndobj\ShaderMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804FDB8C -> 0x804FDB8C
*/
class FileEntry {
    // total size: 0x18
public:
    unsigned long long mOffset; // offset 0x0, size 0x8
    int mHashedName; // offset 0x8, size 0x4
    int mHashedPath; // offset 0xC, size 0x4
    int mSize; // offset 0x10, size 0x4
    int mUCSize; // offset 0x14, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class FileEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class FileEntry * _M_start; // offset 0x0, size 0x4
    class FileEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ArkHash {
    // total size: 0x14
    char * mHeap; // offset 0x0, size 0x4
    char * mHeapEnd; // offset 0x4, size 0x4
    char * mFree; // offset 0x8, size 0x4
    char * * mTable; // offset 0xC, size 0x4
    int mTableSize; // offset 0x10, size 0x4
};
enum Mode {
    kRead = 0,
    kWrite = 1,
};
class Archive {
    // total size: 0x50
    int mNumArkfiles; // offset 0x0, size 0x4
    class vector mArkfileSizes; // offset 0x4, size 0xC
    class vector mArkfileNames; // offset 0x10, size 0xC
    class vector mFileEntries; // offset 0x1C, size 0xC
    class ArkHash mHashTable; // offset 0x28, size 0x14
    class String mBasename; // offset 0x3C, size 0xC
    enum Mode mMode; // offset 0x48, size 0x4
    unsigned int mMaxArkfileSize; // offset 0x4C, size 0x4
};

