#pragma once
#include "os/FileCache.h"
#include "utl/Loader.h"
#include "utl/NetLoader.h"
#include "utl/Str.h"

class NetCacheLoader {
public:
    enum State {
        kS_Nil = -1,
        kS_0x0 = 0,
        kS_0x1 = 1,
        kS_0x2 = 2,
        kS_Loaded = 3,
        kS_Failed = 4,
    };

    NetCacheLoader(FileCache *, const String &);
    ~NetCacheLoader();

    bool IsLoaded() const;
    int GetSize();
    void *GetBuffer();
    bool HasFailed() const;
    void SetState(State);
    const char *GetRemotePath() const;
    void Poll();
    bool IsSafeToDelete() const;
    u32 GetFailType() const;
    void WriteToCache();

    State mState;
    FileCache *mCache;
    String strPath;
    FileLoader *mFileLoader;
    const char *mFileLoaderBuffer;
    NetLoader *mNetLoader;
    char *mNetLoaderBuffer;
    u32 unk_0x24;
};