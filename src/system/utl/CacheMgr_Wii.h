#ifndef UTL_CACHEMGRWII_H
#define UTL_CACHEMGRWII_H

#include "CacheMgr.h"

class CacheMgrWii : public CacheMgr {
public:
    CacheMgrWii();
    virtual ~CacheMgrWii();
    virtual void Poll();
    virtual bool SearchAsync(const char*, CacheID**);
    virtual bool ShowUserSelectUIAsync(LocalUser*, unsigned long long, const char*, const char*, CacheID**);
    virtual bool CreateCacheIDFromDeviceID(unsigned int, const char*, const char*, CacheID**);
    virtual bool CreateCacheID(const char*, const char*, const char*, const char*, const char*, int, CacheID**);
    virtual bool MountAsync(CacheID*, Cache**, Hmx::Object*);
    virtual bool UnmountAsync(Cache**, Hmx::Object*);
    virtual bool DeleteAsync(CacheID*);

    void CreateVFCache();
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