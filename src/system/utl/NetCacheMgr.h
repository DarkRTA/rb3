#pragma once
#include "obj/Object.h"
#include "obj/Dir.h"
#include "utl/Symbols.h"
#include "utl/Cache.h"
#include "utl/NetLoader.h"
#include "utl/NetCacheLoader.h"
#include <vector>
#include <list>

enum NetCacheMgrFailType {
    kNCMFT_Unknown,
    kNCMFT_StoreServer,
    kNCMFT_NoSpace,
    kNCMFT_StorageDeviceMissing,
    kNCMFT_Max
};

enum NetCacheMgrState {
    kNCMS_Load,
    kNCMS_Ready,
    kNCMS_UnloadWaitForWrite,
    kNCMS_UnloadUnmount,
    kNCMS_Failure,
    kNCMS_Max,
    kNCMS_Nil = -1
};

enum LoadState {
    kLS_None,
    kLS_Mount,
    kLS_Delete,
    kLS_ReMount,
    kLS_Resync
};

class NetCacheMgr : public Hmx::Object {
public:
    enum CacheSize {
    };

    NetCacheMgr();
    virtual ~NetCacheMgr();
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll();
    virtual void LoadInit();
    virtual bool IsDoneLoading() const;
    virtual void ReadyInit();
    virtual void UnloadInit();
    virtual bool IsDoneUnloading() const;

    int GetServerRoot() const;
    int GetPort() const;
    NetCacheMgrFailType GetFailType() const;
    void SetState(NetCacheMgrState);
    void Unload();
    bool IsLocalFile(const char *) const;
    void OnInit();
    void CheatNextServer();
    void DebugClearCache();
    void DeleteNetCacheLoader(NetCacheLoader *);
    void Load(CacheSize);
    bool IsUnloaded() const;
    bool IsReady() const;
    NetCacheLoader *AddNetCacheLoader(const char *, NetLoaderPos);

    NetCacheMgrState mState; // 0x1c
    bool unk_0x20; // 0x20
    NetCacheMgrFailType mFailType; // 0x24
    String mStrXLSPFilter; // 0x28 unsure if this name is still correct, but there is
                           // indeed a String here
    std::list<int> mServers; // 0x34
    Symbol mServerType; // 0x40
    unsigned int mLoadCacheSize; // 0x44
    Cache *mCache; // 0x48
    std::vector<int> mNetLoaderRefs; // 0x4C
};

extern NetCacheMgr *TheNetCacheMgr;
void NetCacheMgrInit();
void NetCacheMgrTerminate();
