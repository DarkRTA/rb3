#ifndef UTL_CACHE_H
#define UTL_CACHE_H

#include <vector>
#include "obj/Object.h"

enum OpType {
    kOpNone = 0,
    kOpDirectory = 1,
    kOpFileSize = 2,
    kOpRead = 3,
    kOpWrite = 4,
    kOpDelete = 5,
};
enum CacheResult {
    kCache_NoError = 0,
    kCache_ErrorBusy = 1,
    kCache_ErrorBadParam = 2,
    kCache_ErrorUnsupported = 3,
    kCache_ErrorUserCancel = 4,
    kCache_ErrorNoStorageDevice = 5,
    kCache_ErrorCacheNotFound = 6,
    kCache_ErrorCorrupt = 7,
    kCache_ErrorStorageDeviceMissing = 8,
    kCache_ErrorNotEnoughSpace = 9,
    kCache_Error360GuideAlreadyOut = 10,
    kCache_ErrorUnknown = -1,
};

struct CacheDirEntry;

class CacheID {
public:
    CacheID(){}
    virtual ~CacheID() = 0;
    virtual const char* GetCachePath(const char*) = 0;
    virtual const char* GetCacheSearchPath(const char*) = 0;
    virtual int GetDeviceID() const;
};

class Cache {
public:
    Cache();
    virtual ~Cache();
    virtual const char* GetCacheName() = 0;
    virtual void Poll() = 0;
    virtual bool IsConnectedSync() = 0;
    virtual int GetFreeSpaceSync(unsigned long long*) = 0;
    virtual bool DeleteSync(const char*) = 0;
    virtual bool GetDirectoryAsync(const char*, std::vector<CacheDirEntry>*, Hmx::Object*) = 0;
    virtual bool GetFileSizeAsync(const char*, uint*, Hmx::Object*) = 0;
    virtual bool ReadAsync(const char*, void*, uint, Hmx::Object*) = 0;
    virtual bool WriteAsync(const char*, void*, uint, Hmx::Object*) = 0;
    virtual bool DeleteAsync(const char*, Hmx::Object*) = 0;
    // more pure virtuals go here
    virtual CacheResult WaitForResult();

    bool IsDone();
    CacheResult GetLastResult();

    OpType mOpCur;
    CacheResult mLastResult;
};

#endif
