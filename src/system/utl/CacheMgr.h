#ifndef UTL_CACHEMGR_H
#define UTL_CACHEMGR_H

#include "Cache.h"

class LocalUser;

void CacheMgrInit();
void CacheMgrTerminate();

class CacheMgr {
private:
    enum OpType {};

    struct CacheIDStoreEntry {
        Symbol symbol;
        CacheID* id;
    };

public:
    CacheMgr();
    virtual ~CacheMgr();
    virtual bool SearchAsync(const char*, CacheID**);
    bool ShowUserSelectUIAsync(LocalUser*, unsigned long long, const char*, const char*, CacheID**);
    bool CreateCacheIDFromDeviceID(unsigned int, const char*, const char*, CacheID**);
    virtual bool CreateCacheID(const char*, const char*, const char*, const char*, const char*, int, CacheID**);
    bool IsDone();
    CacheResult GetLastResult();
    void AddCacheID(CacheID*, Symbol);
    void RemoveCacheID(CacheID*);
    CacheID* GetCacheID(Symbol);
    void SetOp(CacheMgr::OpType);
    CacheMgr::OpType GetOp();
    void SetLastResult(CacheResult);
private:
    std::vector<CacheMgr::CacheIDStoreEntry> mCacheIDStore;
    CacheMgr::OpType mOp; // 0x0c
    CacheResult mLastResult;      // 0x10
    int mUnk; // 0x1c
};

static CacheMgr* TheCacheMgr;

#endif // UTL_CACHEMGR_H