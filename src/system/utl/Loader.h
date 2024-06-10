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

typedef Loader* LoaderFactoryFunc(const FilePath&, LoaderPos);

class LoadMgr {
public:
    LoadMgr();
    Loader* AddLoader(const FilePath&, LoaderPos);
    Loader* GetLoader(const FilePath&) const;
    void PollUntilLoaded(Loader*, Loader*);
    void RegisterFactory(const char*, LoaderFactoryFunc*);
    void StartAsyncUnload();
    void FinishAsyncUnload();
    void Print();
    void SetEditMode(bool);
    void Init();
    Loader* ForceGetLoader(const FilePath&);
    inline bool EditMode() const { return mEditMode; }
    inline Platform GetPlatform() const { return (Platform)mPlatform; }
    int AsyncUnload() const { return unk58; }

    static const char* LoaderPosString(LoaderPos, bool);

    std::list<Loader*> mLoaders;
    unsigned int mPlatform;
    bool mEditMode;
    bool mCacheMode;
    std::list<std::pair<class String, LoaderFactoryFunc*> > mFactories;
    float unk18; // mPeriod?
    float unk1c;
    std::list<Loader*> unk20; // mLoading?
    Timer mTimer;
    int unk58;
    int unk5c;
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
