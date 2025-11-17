#ifndef UTL_NETLOADER_H
#define UTL_NETLOADER_H

#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Str.h"
#include "utl/Loader.h"

enum NetLoaderPos {
};

class NetLoader {
public:
    NetLoader(const String &);
    virtual ~NetLoader();
    virtual void V_Unk0xC();
    virtual bool V_Unk0x10();
    virtual bool IsSafeToDelete();

    bool IsLoaded();
    const char *GetRemotePath() const;
    int GetSize();
    char *GetBuffer();
    char *DetachBuffer();
    void AttachBuffer(char *);
    void SetSize(int);
    void PostDownload();

    static NetLoader *Create(const String &);

    class String mStrRemotePath; // 0x00
    bool mIsLoaded; // 0x10

    char *mBuffer; // 0x14
    bool mBufferOwner; // 0x18

    int mSize; // 0x1C

    int unk_0x20; // 0x20
};

class NetLoaderStub : public NetLoader {
public:
    NetLoaderStub(const String &);
    virtual ~NetLoaderStub();
    virtual void PollLoading();
    virtual bool HasFailed();
    virtual bool IsSafeToDelete() const;

    FileLoader *mFileLoader; // 0x24
    float mNetSimEndTime; // 0x28
};

// called DataNetLoader but not a subclass of NetLoader/Stub, wtf lol
class DataNetLoader {
public:
    DataNetLoader(const String &);
    ~DataNetLoader();
    bool IsLoaded();
    void PollLoading();
    bool HasFailed();

    NetLoaderStub *mLoader; // 0x0
    DataArray *unk_0x4; // 0x4
};

#endif