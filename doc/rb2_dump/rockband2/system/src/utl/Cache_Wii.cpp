/*
    Compile unit: C:\rockband2\system\src\utl\Cache_Wii.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80602768 -> 0x806030D8
*/
class CacheIDWii : public CacheID {
    // total size: 0x30
public:
    class String mStrCacheName; // offset 0x4, size 0xC
    class String mStrIconFilename; // offset 0x10, size 0xC
    class String mStrCacheDescription; // offset 0x1C, size 0xC
    unsigned char mHasCreatedNewGameData; // offset 0x28, size 0x1
    int mSizeKB; // offset 0x2C, size 0x4
};
// Range: 0x80602768 -> 0x806027B8
void * CacheIDWii::CacheIDWii(class CacheIDWii * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__10CacheIDWii;
}

// Range: 0x806027B8 -> 0x80602838
void * CacheIDWii::~CacheIDWii(class CacheIDWii * const this /* r29 */) {}

// Range: 0x80602838 -> 0x8060292C
char * CacheIDWii::GetCachePath(class CacheIDWii * const this /* r30 */, const char * strPath /* r31 */) {
    // Local variables
    class String str; // r1+0x8

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8060292C -> 0x806029CC
char * CacheIDWii::GetCacheSearchPath(class CacheIDWii * const this /* r30 */, const char * strFilter /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

class CacheWii : public Cache {
    // total size: 0x60
    class CacheIDWii mCacheID; // offset 0xC, size 0x30
    class String mThreadStr; // offset 0x3C, size 0xC
    class String mThreadStrFilter; // offset 0x48, size 0xC
    void * mData; // offset 0x54, size 0x4
    unsigned int mSize; // offset 0x58, size 0x4
    class vector * mCacheDirList; // offset 0x5C, size 0x4
};
// Range: 0x806029CC -> 0x80602A9C
void * CacheWii::CacheWii(class CacheWii * const this /* r30 */, const class CacheIDWii & cacheID /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__10CacheIDWii;
    // -> struct [anonymous] __vt__8CacheWii;
}

// Range: 0x80602A9C -> 0x80602B60
void * CacheWii::~CacheWii(class CacheWii * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__8CacheWii;
}

// Range: 0x80602B60 -> 0x80602B68
char * CacheWii::GetCacheName() {}

// Range: 0x80602B68 -> 0x80602B6C
void CacheWii::Poll() {}

// Range: 0x80602B6C -> 0x80602B74
unsigned char CacheWii::IsConnectedSync() {}

// Range: 0x80602B74 -> 0x80602BDC
unsigned char CacheWii::GetFreeSpaceSync(class CacheWii * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80602BDC -> 0x80602C50
unsigned char CacheWii::DeleteSync(class CacheWii * const this /* r30 */, const char * filename /* r31 */) {}

// Range: 0x80602C50 -> 0x80602D78
unsigned char CacheWii::GetDirectoryAsync(class CacheWii * const this /* r28 */, const char * filter /* r29 */, class vector * pDirList /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80602D78 -> 0x80602E68
unsigned char CacheWii::GetFileSizeAsync(class CacheWii * const this /* r29 */, const char * filename /* r30 */, unsigned int * pSize /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80602E68 -> 0x80602F34
unsigned char CacheWii::ReadAsync(class CacheWii * const this /* r28 */, const char * filename /* r29 */, void * pData /* r30 */, unsigned int size /* r31 */) {}

// Range: 0x80602F34 -> 0x80603000
unsigned char CacheWii::WriteAsync(class CacheWii * const this /* r28 */, const char * filename /* r29 */, void * pData /* r30 */, unsigned int size /* r31 */) {}

// Range: 0x80603000 -> 0x806030D8
unsigned char CacheWii::DeleteAsync(class CacheWii * const this /* r30 */, const char * filename /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x34
} __vt__8CacheWii; // size: 0x34, address: 0x8092B358
struct {
    // total size: 0x8
} __RTTI__8CacheWii; // size: 0x8, address: 0x8092B3A8
struct {
    // total size: 0x14
} __vt__10CacheIDWii; // size: 0x14, address: 0x8092B3B0
struct {
    // total size: 0x8
} __RTTI__10CacheIDWii; // size: 0x8, address: 0x8092B3E0
struct {
    // total size: 0x14
} __vt__7CacheID; // size: 0x14, address: 0x8092B3F8
struct {
    // total size: 0x8
} __RTTI__7CacheID; // size: 0x8, address: 0x8092B418

