/*
    Compile unit: C:\rockband2\band2\src\meta\StoreMainPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801801F0 -> 0x80181410
*/
class DataArray * types; // size: 0x4, address: 0x80A4CB00
enum NetCacheMgrFailType {
    kNCMFT_Unknown = 0,
    kNCMFT_StoreServer = 1,
    kNCMFT_NoSpace = 2,
    kNCMFT_StorageDeviceMissing = 3,
    kNCMFT_Max = 4,
};
// Range: 0x801801F0 -> 0x80180750
void StoreMainPanel::Poll(class StoreMainPanel * const this /* r28 */) {
    // Local variables
    struct ArtEntry * it; // r30
    int size; // r27
    void * pBuffer; // r26
    class BufStream stream; // r1+0xC
    enum NetCacheMgrFailType failType; // r26
    unsigned char isArtLoaded; // r29
    int nextEntry; // r26
    float timeToNextEvent; // f1
    float rawAlpha; // r1+0x8
    float unitAlpha; // f1
    float overlayAlpha; // f31

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class TaskMgr TheTaskMgr;
    // -> class NetCacheMgr * TheNetCacheMgr;
}

// Range: 0x80180750 -> 0x801807E4
void StoreMainPanel::Unload(class StoreMainPanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

static class Symbol display_rate; // size: 0x4, address: 0x80A4CB08
static class Symbol crossfade_duration; // size: 0x4, address: 0x80A4CB10
static class Symbol content; // size: 0x4, address: 0x80A4CB18
static class Symbol require; // size: 0x4, address: 0x80A4CB20
static class Symbol release_num; // size: 0x4, address: 0x80A4CB28
// Range: 0x801807E4 -> 0x80180CAC
void StoreMainPanel::SetConfigData(class StoreMainPanel * const this /* r27 */, class DataArray * pData /* r24 */) {
    // Local variables
    class DataArray * pDataContent; // r30
    int max_release_num; // r29
    int i; // r28
    class DataArray * r; // r26
    class StoreOffer * o; // r0
    int new_release_num; // r24
    class DataArray * r; // r26
    struct NewReleaseEntry entry; // r1+0x38
    struct NewReleaseEntry * n; // r28

    // References
    // -> static class Symbol release_num;
    // -> static class Symbol require;
    // -> static class Symbol content;
    // -> static class Symbol crossfade_duration;
    // -> static class Symbol display_rate;
    // -> class Debug TheDebug;
}

// Range: 0x80180CAC -> 0x80181028
void StoreMainPanel::ClearConfigData(class StoreMainPanel * const this /* r30 */) {
    // Local variables
    struct ArtEntry * it; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ214StoreMainPanel8ArtEntry;
    // -> unsigned char gStlAllocNameLookup;
    // -> class NetCacheMgr * TheNetCacheMgr;
    // -> class Debug TheDebug;
}

struct {
    // total size: 0x8
} __RTTI__PQ214StoreMainPanel8ArtEntry; // size: 0x8, address: 0x8089A748
enum State {
    kS_LoadFromCache = 0,
    kS_PreDownload = 1,
    kS_Download = 2,
    kS_PreWrite = 3,
    kS_WriteToCache = 4,
    kS_DataReady = 5,
    kS_Failure = 6,
    kS_Max = 7,
    kS_Nil = -1,
};
class NetCacheLoader {
    // total size: 0x20
    enum State mState; // offset 0x0, size 0x4
    class Cache * mCache; // offset 0x4, size 0x4
    class String mStrRemotePath; // offset 0x8, size 0xC
    class NetCacheFileLoader * mCacheLoader; // offset 0x14, size 0x4
    class NetLoader * mNetLoader; // offset 0x18, size 0x4
    enum NetCacheMgrFailType mFailType; // offset 0x1C, size 0x4
};
// Range: 0x80181028 -> 0x80181054
unsigned char StoreMainPanel::IsArtLoaded() {}

static class Symbol _s; // size: 0x4, address: 0x80A4CB30
// Range: 0x80181054 -> 0x80181410
class DataNode StoreMainPanel::Handle(class StoreMainPanel * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__14StoreMainPanel; // size: 0xAC, address: 0x8089AAB8
struct {
    // total size: 0x8
} __RTTI__14StoreMainPanel; // size: 0x8, address: 0x8089AB98
struct {
    // total size: 0x8
} __RTTI__12StoreUIPanel; // size: 0x8, address: 0x8089ABD0
struct {
    // total size: 0x8
} __RTTI__PQ214StoreMainPanel15NewReleaseEntry; // size: 0x8, address: 0x8089AC60
enum NetCacheMgrState {
    kNCMS_Load = 0,
    kNCMS_Ready = 1,
    kNCMS_UnloadWaitForWrite = 2,
    kNCMS_UnloadUnmount = 3,
    kNCMS_Failure = 4,
    kNCMS_Max = 5,
    kNCMS_Nil = -1,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct ServerData {
    // total size: 0x24
    class Symbol mType; // offset 0x0, size 0x4
    class String mServer; // offset 0x4, size 0xC
    unsigned short mPort; // offset 0x10, size 0x2
    class String mServerRoot; // offset 0x14, size 0xC
    unsigned char mVerifySSL; // offset 0x20, size 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct NetCacheLoaderRef {
    // total size: 0x14
    class String mName; // offset 0x0, size 0xC
    int mCount; // offset 0xC, size 0x4
    class NetCacheLoader * mLoader; // offset 0x10, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
struct NetCacheEntry {
    // total size: 0x20
    class String mStrRemotePath; // offset 0x0, size 0xC
    struct DateTime mTimeLastNetAccess; // offset 0xC, size 0x6
    unsigned char mIsCached; // offset 0x12, size 0x1
    struct DateTime mTimeLastLocalAccess; // offset 0x13, size 0x6
    int mFileSize; // offset 0x1C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct NetCacheEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct NetCacheEntry * _M_start; // offset 0x0, size 0x4
    struct NetCacheEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
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
class list : public _List_base {
    // total size: 0x8
};
enum LoadState {
    kLS_None = 0,
    kLS_Mount = 1,
    kLS_Delete = 2,
    kLS_ReMount = 3,
    kLS_Resync = 4,
};
class NetCacheMgr : public Object {
    // total size: 0x94
protected:
    class String mStrLocal; // offset 0x28, size 0xC
    enum NetCacheMgrFailType mFailType; // offset 0x34, size 0x4
private:
    enum NetCacheMgrState mState; // offset 0x38, size 0x4
    class Symbol mSymNameToken; // offset 0x3C, size 0x4
    int mMinSize; // offset 0x40, size 0x4
    int mMaxSize; // offset 0x44, size 0x4
    class String mStrFilter; // offset 0x48, size 0xC
    unsigned int mServiceId; // offset 0x54, size 0x4
    class list mServers; // offset 0x58, size 0x8
    class Symbol mServerType; // offset 0x60, size 0x4
protected:
    class CacheID * mCacheID; // offset 0x64, size 0x4
    class Cache * mCache; // offset 0x68, size 0x4
private:
    class list mLoaders; // offset 0x6C, size 0x8
    class vector mIndex; // offset 0x74, size 0xC
    class list mLoaderQueue; // offset 0x80, size 0x8
    enum LoadState mLoadState; // offset 0x88, size 0x4
    class vector * mDirList; // offset 0x8C, size 0x4
    unsigned char mIsUnmounting; // offset 0x90, size 0x1
};

