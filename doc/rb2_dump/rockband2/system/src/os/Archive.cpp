/*
    Compile unit: C:\rockband2\system\src\os\Archive.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8059E2B8 -> 0x8059F23C
*/
class Archive * TheArchive; // size: 0x4, address: 0x80A54880
// Range: 0x8059E2B8 -> 0x8059E62C
void ArchiveInit() {
    // Local variables
    class Symbol plat; // r1+0x48
    const char * patch; // r30
    unsigned char patch_on_hd; // r29
    class String path; // r1+0x4C
    class File * f; // r0
    class Archive m; // r1+0x58

    // References
    // -> class BlockMgr TheBlockMgr;
    // -> class Archive * TheArchive;
    // -> class ContentMgr & TheContentMgr;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x8059E62C -> 0x8059E648
void * FileEntry::FileEntry() {}

// Range: 0x8059E648 -> 0x8059E68C
unsigned char FileEntry::__lt() {}

// Range: 0x8059E68C -> 0x8059E6A8
void * ArkHash::ArkHash() {}

// Range: 0x8059E6A8 -> 0x8059E708
void * ArkHash::~ArkHash(class ArkHash * const this /* r30 */) {}

// Range: 0x8059E708 -> 0x8059E8A4
int ArkHash::AddString(class ArkHash * const this /* r30 */, const char * str /* r26 */) {
    // Local variables
    int hashIdx; // r31
    int hashStart; // r27
    int len; // r27

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8059E8A4 -> 0x8059E974
int ArkHash::GetHashValue(const class ArkHash * const this /* r29 */, const char * str /* r30 */) {
    // Local variables
    int hashIdx; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8059E974 -> 0x8059E9EC
char * ArkHash::__vc(const class ArkHash * const this /* r30 */, int idx /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8059E9EC -> 0x8059EB28
void ArkHash::Read(class ArkHash * const this /* r30 */, class BinStream & s /* r31 */, int heap_headroom /* r28 */) {
    // Local variables
    int old_heap_size; // r1+0xC
    int heap_size; // r28
    char * * it; // r28
    char * * end; // r29
    int idx; // r1+0x8
}

// Range: 0x8059EB28 -> 0x8059EBC0
void * Archive::Archive(class Archive * const this /* r28 */, const char * basename /* r29 */, int heap_headroom /* r30 */) {}

// Range: 0x8059EBC0 -> 0x8059EE34
unsigned char Archive::GetFileInfo(class Archive * const this /* r24 */, const char * file /* r23 */, int & arkfileNum /* r25 */, unsigned long long & byteOffset /* r26 */, int & fileSize /* r27 */, int & fileUCSize /* r28 */) {
    // Local variables
    class String name; // r1+0x18
    class String path; // r1+0xC
    int hashpath; // r0
    int hashname; // r0
    class FileEntry target; // r1+0x28
    class FileEntry * itr; // r0
    unsigned long long arkOffset; // r30
    unsigned long long nTotalSize; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct __less_2 {
    // total size: 0x1
};
// Range: 0x8059EE34 -> 0x8059EEB4
class BinStream & __rs(class BinStream & in /* r30 */, class FileEntry & fe /* r31 */) {}

// Range: 0x8059EEB4 -> 0x8059F120
void Archive::Read(class Archive * const this /* r30 */, int heap_headroom /* r31 */) {
    // Local variables
    class FileStream arkhdr; // r1+0x48
    int version; // r1+0x10
    int i; // r27

    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__P9FileEntry; // size: 0x8, address: 0x80921800
// Range: 0x8059F120 -> 0x8059F170
unsigned char Archive::IsValidBlock() {
    // Local variables
    int maxBlock; // r0

    // References
    // -> int kArkBlockSize;
}

// Range: 0x8059F170 -> 0x8059F23C
void Archive::SetLocationHardDrive(class Archive * const this /* r29 */) {
    // Local variables
    int i; // r30
    class String path; // r1+0x8

    // References
    // -> class ContentMgr & TheContentMgr;
}

struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class ArkFile : public File {
    // total size: 0x40
    int mArkfileNum; // offset 0x4, size 0x4
    unsigned long long mByteStart; // offset 0x8, size 0x8
    int mSize; // offset 0x10, size 0x4
    int mUCSize; // offset 0x14, size 0x4
    int mNumOutstandingTasks; // offset 0x18, size 0x4
    int mBytesRead; // offset 0x1C, size 0x4
    int mTell; // offset 0x20, size 0x4
    int mFail; // offset 0x24, size 0x4
    float mReadStartTime; // offset 0x28, size 0x4
    int mReadAhead; // offset 0x2C, size 0x4
    class String mFilename; // offset 0x30, size 0xC
};
class AsyncTask {
    // total size: 0x18
    int mArkfileNum; // offset 0x0, size 0x4
    int mBlockNum; // offset 0x4, size 0x4
    int mOffsetStart; // offset 0x8, size 0x4
    int mOffsetEnd; // offset 0xC, size 0x4
    void * mBuffer; // offset 0x10, size 0x4
    class ArkFile * mOwner; // offset 0x14, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class BlockRequest {
    // total size: 0x10
public:
    int mArkfileNum; // offset 0x0, size 0x4
    int mBlockNum; // offset 0x4, size 0x4
    class list mTasks; // offset 0x8, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class Block {
    // total size: 0x10
public:
    char * mBuffer; // offset 0x0, size 0x4
    int mArkfileNum; // offset 0x4, size 0x4
    int mBlockNum; // offset 0x8, size 0x4
    int mTimestamp; // offset 0xC, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Block * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Block * * _M_start; // offset 0x0, size 0x4
    class Block * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class BlockMgr {
    // total size: 0x60
    class list mRequests; // offset 0x0, size 0x8
    class list mReadAheadRequests; // offset 0x8, size 0x8
    class vector mBlockCache; // offset 0x10, size 0xC
    class Block * mPendingBlock; // offset 0x1C, size 0x4
    int mSectorsPerBlock; // offset 0x20, size 0x4
    class Timer mSpinDownTimer; // offset 0x28, size 0x38
};

