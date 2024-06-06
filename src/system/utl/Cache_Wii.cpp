#include "Cache_Wii.h"

CacheIDWii::CacheIDWii() {

}

CacheIDWii::~CacheIDWii() {}

void CacheIDWii::GetCachePath(const char*) {}

void CacheIDWii::GetCacheSearchPath(const char*) {}

CacheWii::CacheWii(const CacheIDWii&) {}
CacheWii::~CacheWii() {}
const char* CacheWii::GetCacheName() {
    return mCacheName;
}

void CacheWii::Poll() {}

bool CacheWii::IsConnectedSync() {
    return true;
}

int CacheWii::GetFreeSpaceSync(unsigned long long*) {}

bool CacheWii::DeleteSync(const char*) {}
bool CacheWii::GetDirectoryAsync(const char*, std::vector<CacheDirEntry>*, Hmx::Object*) {}
bool CacheWii::GetFileSizeAsync(const char*, unsigned int*, Hmx::Object*) {}
bool CacheWii::ReadAsync(const char*, void*, uint, Hmx::Object*) {}
bool CacheWii::WriteAsync(const char*, void*, uint, Hmx::Object*) {}
bool CacheWii::DeleteAsync(const char*, Hmx::Object*) {}
void CacheWii::ThreadStart() {}
void CacheWii::ThreadDone(int) {}
void CacheWii::ThreadGetDir(String) {}
void CacheWii::ThreadGetFileSize() {}
void CacheWii::ThreadRead() {}
void CacheWii::ThreadWrite() {}
void CacheWii::ThreadDelete() {}