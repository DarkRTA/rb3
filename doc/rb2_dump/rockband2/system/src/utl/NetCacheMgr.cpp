/*
    Compile unit: C:\rockband2\system\src\utl\NetCacheMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8061C7E4 -> 0x8061DF00
*/
class NetCacheMgr * TheNetCacheMgr; // size: 0x4, address: 0x80A554A8
// Range: 0x8061C7E4 -> 0x8061C82C
void NetCacheMgrTerminate() {
    // References
    // -> class NetCacheMgr * TheNetCacheMgr;
}

// Range: 0x8061C82C -> 0x8061C9CC
void * NetCacheMgr::NetCacheMgr(class NetCacheMgr * const this /* r29 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__11NetCacheMgr;
}

class _List_node : public _List_node_base {
    // total size: 0x2C
public:
    struct ServerData _M_data; // offset 0x8, size 0x24
};
class _List_node : public _List_node_base {
    // total size: 0x1C
public:
    struct NetCacheLoaderRef _M_data; // offset 0x8, size 0x14
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class NetCacheFileLoader * _M_data; // offset 0x8, size 0x4
};
// Range: 0x8061C9CC -> 0x8061CBF8
void * NetCacheMgr::~NetCacheMgr(class NetCacheMgr * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__11NetCacheMgr;
}

static class Symbol servers; // size: 0x4, address: 0x80A554B0
static class Symbol server; // size: 0x4, address: 0x80A554B8
static class Symbol port; // size: 0x4, address: 0x80A554C0
static class Symbol root; // size: 0x4, address: 0x80A554C8
static class Symbol verify_ssl; // size: 0x4, address: 0x80A554D0
static class Symbol default_server; // size: 0x4, address: 0x80A554D8
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8061CBF8 -> 0x8061D060
void NetCacheMgr::OnInit(class NetCacheMgr * const this /* r27 */, class DataArray * pData /* r28 */) {
    // Local variables
    int index; // r25
    class DataArray * s; // r30
    int i; // r29
    struct ServerData sd; // r1+0x48
    struct _List_iterator s; // r1+0x44

    // References
    // -> static class Symbol default_server;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std39_List_node<Q211NetCacheMgr10ServerData>;
    // -> unsigned char gStlAllocNameLookup;
    // -> static class Symbol verify_ssl;
    // -> const char * gNullStr;
    // -> static class Symbol root;
    // -> static class Symbol port;
    // -> static class Symbol server;
    // -> static class Symbol servers;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std39_List_node<Q211NetCacheMgr10ServerData>; // size: 0x8, address: 0x8092E718
// Range: 0x8061D060 -> 0x8061D078
unsigned long long NetCacheMgr::GetMaxSize() {}

// Range: 0x8061D078 -> 0x8061D09C
char * NetCacheMgr::GetServer() {}

// Range: 0x8061D09C -> 0x8061D0C0
unsigned short NetCacheMgr::GetPort() {}

// Range: 0x8061D0C0 -> 0x8061D0E4
char * NetCacheMgr::GetServerRoot() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8061D0E4 -> 0x8061D150
void NetCacheMgr::Load(class NetCacheMgr * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std31_List_node<17NetCacheLoaderRef>; // size: 0x8, address: 0x8092E8E8
// Range: 0x8061D150 -> 0x8061D23C
void NetCacheMgr::ReleaseRef(class NetCacheMgr * const this /* r31 */, class NetCacheLoader * pLoader /* r30 */) {
    // Local variables
    class String strRemotePath; // r1+0x24
    struct _List_iterator it; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8061D23C -> 0x8061D240
void NetCacheMgr::DeleteNetCacheLoader() {}

// Range: 0x8061D240 -> 0x8061D258
unsigned char NetCacheMgr::IsUnloaded() {}

// Range: 0x8061D258 -> 0x8061D270
unsigned char NetCacheMgr::IsReady() {}

// Range: 0x8061D270 -> 0x8061D288
unsigned char NetCacheMgr::HasFailed() {}

// Range: 0x8061D288 -> 0x8061D290
enum NetCacheMgrFailType NetCacheMgr::GetFailType() {}

// Range: 0x8061D290 -> 0x8061D318
unsigned char NetCacheMgr::IsLocalFile(const class NetCacheMgr * const this /* r29 */, const class String & strRemotePath /* r30 */) {
    // Local variables
    const struct NetCacheEntry * it; // r31
}

// Range: 0x8061D318 -> 0x8061D3B0
unsigned long long NetCacheMgr::GetCacheSize(class NetCacheMgr * const this /* r31 */) {
    // Local variables
    unsigned long long size; // r3
    const struct NetCacheEntry * it; // r6
}

// Range: 0x8061D3B0 -> 0x8061D4A0
class NetCacheFileLoader * NetCacheMgr::AddFileCacheLoader(class NetCacheMgr * const this /* r29 */, const class String & strRemotePath /* r30 */) {
    // Local variables
    struct NetCacheEntry * pEntry; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std33_List_node<P18NetCacheFileLoader>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std33_List_node<P18NetCacheFileLoader>; // size: 0x8, address: 0x8092E948
// Range: 0x8061D4A0 -> 0x8061D564
void NetCacheMgr::DeleteFileCacheLoader(class NetCacheFileLoader * pLoader /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x1C
}

// Range: 0x8061D564 -> 0x8061D57C
unsigned char __eq() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8061D57C -> 0x8061D584
enum NetCacheMgrState NetCacheMgr::GetState() {}

// Range: 0x8061D584 -> 0x8061D688
void NetCacheMgr::AddEntry(class NetCacheMgr * const this /* r29 */, const struct NetCacheEntry & entry /* r30 */) {}

// Range: 0x8061D688 -> 0x8061D6FC
struct NetCacheEntry * NetCacheMgr::FindEntry(class NetCacheMgr * const this /* r29 */, const class String & strRemotePath /* r30 */) {
    // Local variables
    struct NetCacheEntry * it; // r31
}

// Range: 0x8061D6FC -> 0x8061D780
struct NetCacheEntry * NetCacheMgr::FindOldestEntry(class NetCacheMgr * const this /* r29 */) {
    // Local variables
    struct NetCacheEntry * pEntry; // r31
    struct NetCacheEntry * it; // r30
}

// Range: 0x8061D780 -> 0x8061D7E0
void NetCacheMgr::DeleteOldestFile(class NetCacheMgr * const this /* r30 */) {
    // Local variables
    struct NetCacheEntry * pEntry; // r0
}

// Range: 0x8061D7E0 -> 0x8061D864
void NetCacheMgr::EnterUnloadState(class NetCacheMgr * const this /* r31 */) {
    // Local variables
    unsigned char ret; // r0

    // References
    // -> class CacheMgr * TheCacheMgr;
}

// Range: 0x8061D864 -> 0x8061D910
struct ServerData & NetCacheMgr::Server(const class NetCacheMgr * const this /* r31 */) {
    // Local variables
    struct _List_iterator s; // r1+0x24

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A554E0
static class Symbol _s; // size: 0x4, address: 0x80A554E8
static class Symbol _s; // size: 0x4, address: 0x80A554F0
static class Symbol _s; // size: 0x4, address: 0x80A554F8
static class Symbol _s; // size: 0x4, address: 0x80A55500
// Range: 0x8061D910 -> 0x8061DF00
class DataNode NetCacheMgr::Handle(class NetCacheMgr * const this /* r29 */, class DataArray * _msg /* r26 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x6C
} __vt__11NetCacheMgr; // size: 0x6C, address: 0x8092EB74
struct {
    // total size: 0x8
} __RTTI__11NetCacheMgr; // size: 0x8, address: 0x8092EC00
struct {
    // total size: 0x8
} __RTTI__P13NetCacheEntry; // size: 0x8, address: 0x8092EC50

