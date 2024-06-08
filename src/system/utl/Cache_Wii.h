

#ifndef UTL_CACHEWII_H
#define UTL_CACHEWII_H

#include "Cache.h"
#include <vector>

class CacheIDWii {
public: 
    CacheIDWii();
    virtual ~CacheIDWii();
    const char* GetCachePath(const char*);
    const char* GetCacheSearchPath(const char*);
    String unk1;  // 0x04
    String unk2;  // 0x10 
    String unk3;  // 0x1c
    int unk4;     // 0x28??
};

class CacheWii : public Cache {
    CacheWii(const CacheIDWii&);
    virtual ~CacheWii();
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
    int ThreadStart();
    void ThreadDone(int);
    int ThreadGetDir(String);
    int ThreadGetFileSize();
    int ThreadRead();
    int ThreadWrite();
    int ThreadDelete();

    String m0x14; // 0x14
    String mCacheName; // 0x1c
    String m0x2c;
    int m0x38;
    String s_mThreadStr;
    String m0x48;
    const char* m0x54;
    int m0x58;
    std::vector<CacheDirEntry>* s_mCacheDirList; // 0x5c
    char* m0x68;
    String m0x100;
};

#endif