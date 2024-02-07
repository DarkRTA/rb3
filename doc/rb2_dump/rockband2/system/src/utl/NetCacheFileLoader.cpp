/*
    Compile unit: C:\rockband2\system\src\utl\NetCacheFileLoader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8061B9FC -> 0x8061BF28
*/
class NetCacheFileLoader {
    // total size: 0x28
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    enum State mState; // offset 0x4, size 0x4
    class Cache * mCache; // offset 0x8, size 0x4
    class String mStrPath; // offset 0xC, size 0xC
    unsigned int mSize; // offset 0x18, size 0x4
    char * mBuffer; // offset 0x1C, size 0x4
    unsigned char mOwnsBuffer; // offset 0x20, size 0x1
    enum NetCacheMgrFailType mFailType; // offset 0x24, size 0x4
};
// Range: 0x8061B9FC -> 0x8061BAA8
void * NetCacheFileLoader::NetCacheFileLoader(class NetCacheFileLoader * const this /* r30 */, const class String & strPath /* r31 */) {
    // References
    // -> class NetCacheMgr * TheNetCacheMgr;
    // -> struct [anonymous] __vt__18NetCacheFileLoader;
}

// Range: 0x8061BAA8 -> 0x8061BB1C
void * NetCacheFileLoader::~NetCacheFileLoader(class NetCacheFileLoader * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__18NetCacheFileLoader;
}

// Range: 0x8061BB1C -> 0x8061BB34
unsigned char NetCacheFileLoader::IsLoaded() {}

// Range: 0x8061BB34 -> 0x8061BB4C
unsigned char NetCacheFileLoader::HasFailed() {}

// Range: 0x8061BB4C -> 0x8061BB54
enum NetCacheMgrFailType NetCacheFileLoader::GetFailType() {}

// Range: 0x8061BB54 -> 0x8061BB5C
int NetCacheFileLoader::GetSize() {}

// Range: 0x8061BB5C -> 0x8061BB78
char * NetCacheFileLoader::GetBuffer() {}

enum State {
    kS_Waiting = 0,
    kS_GetSize = 1,
    kS_Loading = 2,
    kS_Done = 3,
    kS_Failure = 4,
    kS_Nil = -1,
};
// Range: 0x8061BB78 -> 0x8061BD0C
void NetCacheFileLoader::SetState(class NetCacheFileLoader * const this /* r30 */, enum State state /* r31 */) {
    // Local variables
    unsigned char ret; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8061BD0C -> 0x8061BE24
void NetCacheFileLoader::StartLoading(class NetCacheFileLoader * const this /* r30 */) {
    // Local variables
    unsigned char ret; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8061BE24 -> 0x8061BF28
void NetCacheFileLoader::PollLoading(class NetCacheFileLoader * const this /* r31 */) {
    // Local variables
    enum CacheResult result; // r0
    enum CacheResult result; // r0
}

struct {
    // total size: 0xC
} __vt__18NetCacheFileLoader; // size: 0xC, address: 0x8092E4CC
struct {
    // total size: 0x8
} __RTTI__18NetCacheFileLoader; // size: 0x8, address: 0x8092E4F0

