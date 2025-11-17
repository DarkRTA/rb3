#include "NetCacheLoader.h"
#include "macros.h"
#include "os/Debug.h"
#include "utl/FilePath.h"
#include "utl/Loader.h"
#include "utl/NetCacheMgr.h"
#include "utl/NetLoader.h"
#include <cstddef>

NetCacheLoader::NetCacheLoader(FileCache *cache, const String &name)
    : mState(kS_Nil), mCache(cache), strPath(name), mFileLoader(nullptr),
      mFileLoaderBuffer(0), mNetLoader(nullptr), mNetLoaderBuffer(0), unk_0x24(0) {
    if (TheNetCacheMgr->IsLocalFile(strPath.c_str())) {
        SetState(kS_0x0);
    } else {
        SetState(kS_0x1);
    }
    MILO_ASSERT(mState != kS_Nil, 40);
    MILO_ASSERT(mCache, 43);
}

NetCacheLoader::~NetCacheLoader() { SetState(kS_Nil); }

bool NetCacheLoader::IsLoaded() const { return mState == kS_Loaded; }

bool NetCacheLoader::HasFailed() const { return mState == kS_Failed; }

u32 NetCacheLoader::GetFailType() const { return unk_0x24; }

void NetCacheLoader::Poll() {
    switch (mState) {
    case kS_0x1: {
        SetState(kS_0x2);
        return;
    }
    case kS_0x0: {
        MILO_ASSERT(mFileLoader, 78);
        if (mFileLoader->IsLoaded()) {
            MILO_ASSERT(!mFileLoaderBuffer, 82);
            mFileLoaderBuffer = mFileLoader->GetBuffer(NULL);
            SetState(kS_Loaded);
        }
        return;
    }
    case kS_0x2: {
        mNetLoader->V_Unk0xC();
        if (mNetLoader->IsLoaded()) {
            WriteToCache();
            SetState(kS_Loaded);
            return;
        }
        if (mNetLoader->V_Unk0x10()) {
            if (mNetLoader->unk_0x20 == 1) {
                MILO_LOG(
                    "Failed to find file on server: %s\n", mNetLoader->GetRemotePath()
                );
                unk_0x24 = 2;
            } else {
                MILO_WARN(
                    "NetCacheLoader failed for file: %s\n", mNetLoader->GetRemotePath()
                );
                unk_0x24 = 1;
            }
            SetState(kS_Failed);
        }
    }
    default:
        return;
    }
}

const char *NetCacheLoader::GetRemotePath() const { return strPath; }

bool NetCacheLoader::IsSafeToDelete() const {
    if (mNetLoader)
        return mNetLoader->IsSafeToDelete();
    return 1;
}

int NetCacheLoader::GetSize() {
    if (mNetLoader)
        return mNetLoader->GetSize();
    if (mFileLoader)
        return mFileLoader->GetSize();
    return 0;
}

void *NetCacheLoader::GetBuffer() {
    if (mNetLoader)
        return mNetLoaderBuffer;
    if (mFileLoader)
        return (void *)mFileLoaderBuffer;
    return NULL;
}

void NetCacheLoader::SetState(NetCacheLoader::State state) {
    if (state == mState)
        return;
    switch (mState) {
    case kS_0x0: {
        if (state != kS_Loaded) {
            RELEASE(mFileLoader);
            RELEASE(mFileLoaderBuffer);
        }
        break;
    }
    case kS_0x2: {
        if (state != kS_Loaded) {
            MILO_ASSERT(!mNetLoader || mNetLoader->IsSafeToDelete(), 193);
            RELEASE(mNetLoader);
        }
        break;
    }
    case kS_Loaded: {
        MILO_ASSERT(!mNetLoader || mNetLoader->IsSafeToDelete(), 199);
        break;
    }
    }
    MILO_ASSERT(!mFileLoader, 227);
    MILO_ASSERT(TheNetCacheMgr->IsLocalFile(strPath), 230);
    MILO_ASSERT(!mNetLoader, 239);
    mNetLoader = NetLoader::Create(strPath);
}

void NetCacheLoader::WriteToCache() {
    if (!TheNetCacheMgr->IsReady()) {
        unk_0x24 = 0;
        SetState(kS_Failed);
        return;
    }
    MILO_ASSERT(!mNetLoaderBuffer, 259);
    mNetLoaderBuffer = mNetLoader->DetachBuffer();
    FilePath fp(strPath.c_str());
    mCache->Add(fp, mNetLoaderBuffer, mNetLoader->GetSize());
}
