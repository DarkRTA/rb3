/*
    Compile unit: C:\rockband2\system\src\utl\NetLoader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8061A874 -> 0x8061B274
*/
// Range: 0x8061A874 -> 0x8061A8B4
class NetLoader * NetLoader::Create(const class String & strRemotePath /* r31 */) {}

// Range: 0x8061A8B4 -> 0x8061A948
void * NetLoader::NetLoader(class NetLoader * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetCacheMgr * TheNetCacheMgr;
    // -> struct [anonymous] __vt__9NetLoader;
}

// Range: 0x8061A948 -> 0x8061A9CC
void * NetLoader::~NetLoader(class NetLoader * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__9NetLoader;
}

// Range: 0x8061A9CC -> 0x8061A9D4
unsigned char NetLoader::IsLoaded() {}

// Range: 0x8061A9D4 -> 0x8061A9DC
class String & NetLoader::GetRemotePath() {}

// Range: 0x8061A9DC -> 0x8061A9E4
int NetLoader::GetSize() {}

// Range: 0x8061A9E4 -> 0x8061AA00
char * NetLoader::GetBuffer() {}

// Range: 0x8061AA00 -> 0x8061AA94
void NetLoader::AttachBuffer(class NetLoader * const this /* r30 */, char * pBuffer /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8061AA94 -> 0x8061AA9C
void NetLoader::SetSize() {}

// Range: 0x8061AA9C -> 0x8061ABFC
void NetLoader::PreDownload(class NetLoader * const this /* r31 */) {
    // Local variables
    struct NetCacheEntry * pEntry; // r30
    struct NetCacheEntry entry; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> class NetCacheMgr * TheNetCacheMgr;
}

// Range: 0x8061ABFC -> 0x8061AD30
void NetLoader::PostDownload(class NetLoader * const this /* r28 */) {
    // Local variables
    struct NetCacheEntry * pEntry; // r0

    // References
    // -> const char * kAssertStr;
    // -> class NetCacheMgr * TheNetCacheMgr;
    // -> class Debug TheDebug;
}

class NetLoaderStub : public NetLoader {
    // total size: 0x28
    class FileLoader * mFileLoader; // offset 0x20, size 0x4
    float mNetSimEndTime; // offset 0x24, size 0x4
};
// Range: 0x8061AD30 -> 0x8061ADC4
void * NetLoaderStub::~NetLoaderStub(class NetLoaderStub * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__13NetLoaderStub;
}

// Range: 0x8061ADC4 -> 0x8061AEB4
void NetLoaderStub::PollLoading(class NetLoaderStub * const this /* r31 */) {
    // Local variables
    int size; // r1+0x8

    // References
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8061AEB4 -> 0x8061AEBC
unsigned char NetLoaderStub::HasFailed() {}

// Range: 0x8061AEBC -> 0x8061AF00
void * DataNetLoader::DataNetLoader(class DataNetLoader * const this /* r31 */) {}

// Range: 0x8061AF00 -> 0x8061AFB0
void * DataNetLoader::~DataNetLoader(class DataNetLoader * const this /* r30 */) {}

// Range: 0x8061AFB0 -> 0x8061B1E0
void DataNetLoader::PollLoading(class DataNetLoader * const this /* r31 */) {
    // Local variables
    int size; // r27
    void * pBuf; // r26
    unsigned char isZ; // r25
    const class String & strFileName; // r0
    int strLen; // r0
    char * pBufSize; // r0
    int decompSize; // r1+0xC
    char * pCharInt; // r0
    void * pDecompBuf; // r25
    class BufStream buf; // r1+0x34
    class BufStream buf; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8061B1E0 -> 0x8061B23C
unsigned char DataNetLoader::IsLoaded(class DataNetLoader * const this /* r31 */) {
    // Local variables
    unsigned char isLoaded; // r0
}

// Range: 0x8061B23C -> 0x8061B244
class DataArray * DataNetLoader::GetData() {}

// Range: 0x8061B244 -> 0x8061B274
unsigned char DataNetLoader::HasFailed() {}

struct {
    // total size: 0x14
} __vt__13NetLoaderStub; // size: 0x14, address: 0x8092E2A8
struct {
    // total size: 0x8
} __RTTI__13NetLoaderStub; // size: 0x8, address: 0x8092E2D8
struct {
    // total size: 0x14
} __vt__9NetLoader; // size: 0x14, address: 0x8092E2E0
struct {
    // total size: 0x8
} __RTTI__9NetLoader; // size: 0x8, address: 0x8092E300

