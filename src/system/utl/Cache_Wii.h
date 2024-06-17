

#ifndef UTL_CACHEWII_H
#define UTL_CACHEWII_H

#include "Cache.h"
#include <vector>

class CacheIDWii {
public: 
    CacheIDWii();
    virtual ~CacheIDWii();
    virtual const char* GetCachePath(const char*);
    virtual const char* GetCacheSearchPath(const char*);
    String mStrCacheName;  // 0x04
    String m0x10;  // 0x10 
    String m0x1c;  // 0x1c
    int m0x28;     // 0x28
};

class CacheWii : public Cache {
    CacheWii(const CacheIDWii&);
    virtual ~CacheWii();
    virtual const char* GetCacheName();
    virtual void Poll();
    virtual bool IsConnectedSync();
    virtual int GetFreeSpaceSync(unsigned long long*);
    virtual bool DeleteSync(const char*);
    virtual bool GetDirectoryAsync(const char*, std::vector<CacheDirEntry>*, Hmx::Object*);  
    virtual bool GetFileSizeAsync(const char*, unsigned int*, Hmx::Object*);
    virtual bool ReadAsync(const char*, void*, uint, Hmx::Object*);
    virtual bool WriteAsync(const char*, void*, uint, Hmx::Object*);
    virtual bool DeleteAsync(const char*, Hmx::Object*);
    virtual int ThreadStart();
    virtual void ThreadDone(int);
    virtual int ThreadGetDir(String);
    virtual int ThreadGetFileSize();
    virtual int ThreadRead();
    virtual int ThreadWrite();
    virtual int ThreadDelete();

    int* m0x0c;
    CacheIDWii* m0x10;
    String m0x14;
    String m0x20;
    String m0x2c;
    int m0x38;
    String s_mThreadStr; // 0x3c
    String m0x48;
    void* m0x54;
    int m0x58;
    int m0x5c;
    int m0x60;
    char* m0x64;
    char* m0x68;
    char* m0x6c;
    int m0x70; // padding
    int m0x74;


    String mCacheName; // 0x1c

    std::vector<CacheDirEntry>* s_mCacheDirList; // 0x5c
    char* drive; // 0x68
    String m0x100;
};

#endif