#ifndef UTL_LOADER_H
#define UTL_LOADER_H
#include "utl/FilePath.h"
#include "os/System.h"
#include "os/File.h"
#include "utl/Str.h"
#include "os/Timer.h"
#include <list>

enum LoaderPos {
    kLoadFront = 0,
    kLoadBack = 1,
    kLoadFrontStayBack = 2,
    kLoadStayBack = 3,
};

class Loader {
public:
    class Callback {
    public:
        Callback(){}
        virtual ~Callback(){}
        virtual void FinishLoading(Loader*){}
        virtual void FailedLoading(Loader*){}
    };

    Loader(const FilePath&, LoaderPos);
    virtual ~Loader();
    virtual const char* DebugText();
    virtual bool IsLoaded() const = 0;
    virtual const char* StateName() const { return "Unknown"; }
    virtual void PollLoading() = 0;

    LoaderPos mPos;
    FilePath mFile;
    int mHeap;
};

class LoadMgr {
public:
    LoadMgr();
    Loader* AddLoader(const FilePath&, LoaderPos);
    Loader* GetLoader(const FilePath&) const;
    void PollUntilLoaded(Loader*, Loader*);
    void RegisterFactory(const char*, Loader* (*)(const FilePath&, LoaderPos));
    void StartAsyncUnload();
    void FinishAsyncUnload();
    void Print();
    void SetEditMode(bool);
    void Init();
    Loader* ForceGetLoader(const FilePath&);

    bool EditMode() const { return mEditMode; }

    std::list<Loader*> mLoaders;
    Platform mPlatform;
    bool mEditMode;
    bool mCacheMode;
    std::list<int> unk10; // should be a list of std::pair<String, Loader* (*)(const FilePath&, LoaderPos)>
    float unk18;
    float unk1c;
    std::list<int> unk20;
    Timer mTimer;
    int unk58;
    int unk5c;

    // // total size: 0x60
    // class list mLoaders; // offset 0x0, size 0x8
    // enum Platform mPlatform; // offset 0x8, size 0x4
    // unsigned char mCacheMode; // offset 0xC, size 0x1
    // unsigned char mEditMode; // offset 0xD, size 0x1
    // class list mFactories; // offset 0x10, size 0x8
    // float mPeriod; // offset 0x18, size 0x4
    // class list mLoading; // offset 0x1C, size 0x8
    // class Timer mTimer; // offset 0x28, size 0x38
};

extern LoadMgr TheLoadMgr;

class FileLoader : public Loader {
public:
    FileLoader(const FilePath&, const char*, LoaderPos, int, bool, bool, BinStream*);
    virtual ~FileLoader();
    virtual const char* DebugText();
    virtual bool IsLoaded() const;
    virtual void PollLoading();

    const char* GetBuffer(int*);
    int GetSize();

    File* mFile;
    BinStream* mStream;
    const char* mBuffer;
    int mBufLen;
    bool mAccessed;
    bool mTemp;
    bool mWarn;
    int mFlags;
    class String mFilename;
};

#endif
