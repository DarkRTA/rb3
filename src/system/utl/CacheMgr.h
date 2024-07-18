#ifndef UTL_CACHEMGR_H
#define UTL_CACHEMGR_H

#include "Cache.h"

class LocalUser;

void CacheMgrInit();
void CacheMgrTerminate();

class CacheMgr {
public:
    enum OpType {};

    struct CacheIDStoreEntry {
        CacheIDStoreEntry(Symbol s, CacheID* cid) : symbol(s), id(cid) {}
        Symbol symbol;
        CacheID* id;
    };

    CacheMgr();
    virtual ~CacheMgr();
    virtual void Poll() = 0;
    virtual bool SearchAsync(const char*, CacheID**);
    virtual bool ShowUserSelectUIAsync(LocalUser*, unsigned long long, const char*, const char*, CacheID**);
    virtual bool CreateCacheIDFromDeviceID(unsigned int, const char*, const char*, CacheID**);
    virtual bool CreateCacheID(const char*, const char*, const char*, const char*, const char*, int, CacheID**);
    virtual bool MountAsync(CacheID*, Cache**, Hmx::Object*) = 0;
    virtual bool UnmountAsync(Cache**, Hmx::Object*) = 0;
    virtual bool DeleteAsync(CacheID*) = 0;

    bool IsDone();
    CacheResult GetLastResult();
    void AddCacheID(CacheID*, Symbol);
    void RemoveCacheID(CacheID*);
    CacheID* GetCacheID(Symbol);
    void SetOp(CacheMgr::OpType);
    CacheMgr::OpType GetOp();
    void SetLastResult(CacheResult);

    std::vector<CacheMgr::CacheIDStoreEntry> mCacheIDStore;
    CacheMgr::OpType mOp;       // 0x0c
    CacheResult mLastResult;    // 0x10
    int mUnk;                   // 0x1c
};

extern CacheMgr* TheCacheMgr;

#endif // UTL_CACHEMGR_H