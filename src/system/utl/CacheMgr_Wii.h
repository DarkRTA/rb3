#ifndef UTL_CACHEMGRWII_H
#define UTL_CACHEMGRWII_H

#include "CacheMgr.h"

class CacheMgrWii : public CacheMgr {
public:
    CacheMgrWii();
private:
    void CreateVFCache();
    virtual ~CacheMgrWii();
    void Poll();
    bool SearchAsync(const char*, CacheID**);
    bool CreateCacheID(const char*, const char*, const char*, const char*, const char*, int, CacheID**);
    void MountAsync(CacheID*, Cache**, Hmx::Object*);
    void UnmountAsync(Cache**, Hmx::Object*);
    void DeleteAsync(CacheID*);
    void PollSearch();
    void EndSearch(CacheResult);
    void PollMount();
    void PollUnmount();

    String mVar1; // 0x18
    int mVar2;    // 0x1c
    int mVar3;
    int mVar4;
    int mVar5;
};

#endif // UTL_CACHEMGRWII_H