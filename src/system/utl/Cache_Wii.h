

#ifndef UTL_CACHEWII_H
#define UTL_CACHEWII_H

#include "Cache.h"

class CacheIDWii : public CacheID {
public: 
    CacheIDWii();
    ~CacheIDWii();
    const char* GetCachePath(const char*);
    const char* GetCacheSearchPath(const char*);
private:
    const char* unk1;  // 0x04
    const char* unk2;  // 0x10
    const char* unk3;  // 0x1c
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