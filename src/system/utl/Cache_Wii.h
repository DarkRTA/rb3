

#ifndef UTL_CACHEWII_H
#define UTL_CACHEWII_H

#include "Cache.h"

class CacheIDWii {
public: 
    CacheIDWii();
    ~CacheIDWii();
    void GetCachePath(const char*);
    void GetCacheSearchPath(const char*);
};

class CacheWii : public Cache {
    CacheWii(const CacheIDWii&);
    ~CacheWii();
    const char* GetCacheName();
    void Poll();
    bool IsConnectedSync();
    int GetFreeSpaceSync(unsigned long long*);
    bool DeleteSync(const char*);
    bool GetDirectoryAsync(const char*, std::vector<CacheDirEntry>*, Hmx::Object*);  
    bool GetFileSizeAsync(const char*, unsigned int*, Hmx::Object*);
    bool ReadAsync(const char*, void*, uint, Hmx::Object*);
    bool WriteAsync(const char*, void*, uint, Hmx::Object*);
    bool DeleteAsync(const char*, Hmx::Object*);
    void ThreadStart();
    void ThreadDone(int);
    void ThreadGetDir(String);
    void ThreadGetFileSize();
    void ThreadRead();
    void ThreadWrite();
    void ThreadDelete();

    const char* mCacheName;     // 0x1c
};

#endif