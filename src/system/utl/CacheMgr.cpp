#include "CacheMgr.h"
#include "CacheMgr_Wii.h"

void CacheMgrInit() {
    MILO_ASSERT(TheCacheMgr == NULL, 0x12);
    TheCacheMgr = new CacheMgrWii();
    MILO_ASSERT(TheCacheMgr != NULL, 0x14);
}

void CacheMgrTerminate() {
    delete TheCacheMgr;
    TheCacheMgr = NULL;
}

CacheMgr::CacheMgr() : mOp((CacheMgr::OpType)0), mLastResult(kCache_NoError) {}

CacheMgr::~CacheMgr() {}

bool CacheMgr::SearchAsync(const char*, CacheID**) {
    FormatString str = FormatString("CacheMgr::SearchAsync() not supported by this platform.\n");
    TheDebug.Fail(str.Str());
    SetLastResult(kCache_ErrorUnknown);

    return 0;
}

bool CacheMgr::ShowUserSelectUIAsync(LocalUser*, unsigned long long, const char*, const char*, CacheID**) {
    FormatString str = FormatString("CacheMgr::ShowUserSelectUIAsync() not supported by this platform.\n");
    TheDebug.Fail(str.Str());
    SetLastResult(kCache_ErrorUnknown);

    return 0;
}

bool CacheMgr::CreateCacheIDFromDeviceID(unsigned int, const char*, const char*, CacheID**) {
    FormatString str = FormatString("CacheMgr::SetDeviceID() not supported by this platform.\n");
    TheDebug.Fail(str.Str());
    SetLastResult(kCache_ErrorUnknown);

    return 0;
}

bool CacheMgr::CreateCacheID(const char*, const char*, const char*, const char*, const char*, int, CacheID**) {
    FormatString str = FormatString("CacheMgr::CreateCacheID() not supported by this platform.\n");
    TheDebug.Fail(str.Str());
    SetLastResult(kCache_ErrorUnknown);

    return 0;
}

bool CacheMgr::IsDone() {
    return mOp == 0;
}

CacheResult CacheMgr::GetLastResult() {
    return mLastResult;
}

void CacheMgr::AddCacheID(CacheID* id, Symbol symbol) {
    std::vector<CacheMgr::CacheIDStoreEntry>::iterator it = mCacheIDStore.begin();
    while (it != mCacheIDStore.end()) {
        CacheMgr::CacheIDStoreEntry& entry = (*it);
        if (entry.symbol == symbol) {
            entry.id = id;
            return;
        }
        it++;
    }
    MILO_ASSERT(it == mCacheIDStore.end(), 0x8a);
    CacheIDStoreEntry e;
    e.symbol = symbol;
    e.id = id;
    mCacheIDStore.push_back(e);
}

void CacheMgr::RemoveCacheID(CacheID* id) {
    std::vector<CacheMgr::CacheIDStoreEntry>::iterator it = mCacheIDStore.begin();
    while (it != mCacheIDStore.end()) {
        CacheMgr::CacheIDStoreEntry entry = (*it);
        if (entry.id == id) {
            mCacheIDStore.erase(it);
        } else {
            it++;
        }
    }
}

CacheID* CacheMgr::GetCacheID(Symbol symbol) {
    std::vector<CacheMgr::CacheIDStoreEntry>::iterator it = mCacheIDStore.begin();
    while (it != mCacheIDStore.end()) {
        CacheMgr::CacheIDStoreEntry entry = (*it);
        if (entry.symbol == symbol) {
            return entry.id;
        }
        it++;
    }
    return NULL;
}

void CacheMgr::SetOp(CacheMgr::OpType opType) {
    mOp = opType;
}

enum CacheMgr::OpType CacheMgr::GetOp() {
    return mOp;
}

void CacheMgr::SetLastResult(CacheResult result) {
    mLastResult = result;
}
