#include "NetLoader.h"
#include <obj/Task.h>

NetLoader::NetLoader(const String &pStrRemotePath) {
    this->mStrRemotePath = String(pStrRemotePath);
    this->mIsLoaded = false;
    this->mBuffer = nullptr;
    this->mSize = -1;
    this->unk_0x20 = 0;
    // MILO_ASSERT(TheNetCacheMgr == 0, 0x2d);
}

NetLoader::~NetLoader() {
    if (mBuffer != nullptr) {
        _MemFree(mBuffer);
        mBuffer = nullptr;
    }
}

bool NetLoader::IsLoaded() {
    return mIsLoaded;
}

const char *NetLoader::GetRemotePath() const {
    return mStrRemotePath.c_str();
}

int NetLoader::GetSize() {
    return mSize;
}

char *NetLoader::GetBuffer() {
    if (mIsLoaded != false) {
        return mBuffer;
    }
    return 0;
}

char *NetLoader::DetachBuffer() {
    if (mIsLoaded == false) {
        return 0;
    }
    char *buf = mBuffer;
    mBuffer = 0;
    return buf;
}

void NetLoader::AttachBuffer(char *pBuf) {
    if (mBuffer != 0) {
        MILO_ASSERT(mIsLoaded, 0x74);
        if (mBuffer != 0) {
            _MemFree(mBuffer);
            mBuffer = 0;
        }
    }
    mBuffer = pBuf;
}

void NetLoader::SetSize(int pSize) {
    mSize = pSize;
}

void NetLoader::PostDownload() {
    mIsLoaded = mBuffer != 0;
}

NetLoaderStub::~NetLoaderStub() {}

bool NetLoaderStub::HasFailed() {
    return !mBuffer;
}

bool NetLoaderStub::IsSafeToDelete() const {
    return 1;
}

void NetLoaderStub::PollLoading() {
    MILO_ASSERT(mFileLoader, 0xb2);
    if (mIsLoaded == false) {
        if (mFileLoader->IsLoaded() == 0) {
            TheLoadMgr.Poll();
        }
        if (mFileLoader->IsLoaded() != 0) {
            float uiSeconds = TheTaskMgr.UISeconds();
            if (mNetSimEndTime <= uiSeconds) {
                int size = -1;
                const char *buf = mFileLoader->GetBuffer(&size);
                AttachBuffer((char *)buf);
                SetSize(size);
                PostDownload();
            }
        }
        return;
    }
}

DataNetLoader::~DataNetLoader() {}

bool DataNetLoader::IsLoaded() {
    bool loaderIsLoaded = true;
    if (mLoader != 0) {
        loaderIsLoaded = mLoader->mIsLoaded;
    }
    bool retVal = false;
    if ((loaderIsLoaded != false) && (unk_0x4 != 0)) {
        retVal = true;
    }
    return retVal;
}

bool DataNetLoader::HasFailed() {
    NetLoaderStub *loader = mLoader;
    if (mLoader != 0) {
        return mLoader->HasFailed();
    }
    return unk_0x4 == 0;
}
