#include "CacheMgr_Wii.h"

const char* unusedStrings[] = {
    "A", 
    "Can't delete system file.", 
    "Not enough NAND available for VF.", 
    "Can't create sytem file.", // Intentional typo
    "Can't mount nand drive.", 
    "Can't format nand drive", 
    "Can't unmount nand drive.", 
    "Unknown OpType encountered in CacheMgr::Poll()\n", 
    "SearchAsync BAD PARAM: ppCacheID = 0x%X", 
    ", *ppCacheID = 0x%X"
};

CacheMgrWii::CacheMgrWii() : mVar1(), mVar2(0), mVar3(0), mVar4(0), mVar5(0) {
    CreateVFCache();
}

void CacheMgrWii::CreateVFCache() {}
CacheMgrWii::~CacheMgrWii() {
    
}
void CacheMgrWii::Poll() {}
bool CacheMgrWii::SearchAsync(const char*, CacheID**) {}
bool CacheMgrWii::CreateCacheID(const char*, const char*, const char*, const char*, const char*, int, CacheID**) {}
void CacheMgrWii::MountAsync(CacheID*, Cache**, Hmx::Object*) {}
void CacheMgrWii::UnmountAsync(Cache**, Hmx::Object*) {}
void CacheMgrWii::DeleteAsync(CacheID*) {}
void CacheMgrWii::PollSearch() {}
void CacheMgrWii::EndSearch(CacheResult) {}
void CacheMgrWii::PollMount() {}
void CacheMgrWii::PollUnmount() {}

