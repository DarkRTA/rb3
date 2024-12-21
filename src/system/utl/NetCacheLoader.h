#pragma once
#include "os/FileCache.h"
#include "utl/Str.h"

class NetCacheLoader {
public:
    NetCacheLoader(FileCache*, const String&);

    bool IsLoaded() const;
    int GetSize();
    void* GetBuffer();
    bool HasFailed() const;

    int mState;
    FileCache* unk4;
};