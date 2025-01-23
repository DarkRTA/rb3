#ifndef UTL_LOADER_H
#define UTL_LOADER_H
#include "utl/FilePath.h"
#include "os/System.h"
#include "os/File.h"
#include "utl/Loader.h"
#include "utl/PoolAlloc.h"
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
    virtual const char* DebugText(){ return mFile.c_str(); }
    virtual bool IsLoaded() const = 0;
    virtual const char* StateName() const { return "Unknown"; }
    virtual void PollLoading() = 0;

    LoaderPos GetPos() const { return mPos; }
    FilePath& LoaderFile(){ return mFile; }

    LoaderPos mPos; // 0x4
    FilePath mFile; // 0x8
    int mHeap; // 0x14
};

typedef Loader* LoaderFactoryFunc(const FilePath&, LoaderPos);

class LoadMgr {
public:
    LoadMgr();
    Loader* AddLoader(const FilePath&, LoaderPos);
    Loader* GetLoader(const FilePath&) const;
    void PollUntilLoaded(Loader*, Loader*);
    void PollUntilEmpty();
    void Poll();
    void RegisterFactory(const char*, LoaderFactoryFunc*);
    void StartAsyncUnload();
    void FinishAsyncUnload();
    void Print();
    void SetEditMode(bool);
    void Init();
    Loader* ForceGetLoader(const FilePath&);
    void PollFrontLoader();
    int AsyncUnload() const;

    bool EditMode(){ return mEditMode; }
    Platform GetPlatform() const { return (Platform)mPlatform; }
    LoaderPos GetLoaderPos() const { return mLoaderPos; }
    float SetLoaderPeriod(float period){
        float ret = mPeriod;
        unk1c = period;
        mPeriod = period;
        return ret;
    }

    bool CheckSplit(){
        return mTimer.SplitMs() > unk1c ? true : false;
    }

    Loader* GetFirstLoading(){
        if(mLoading.empty()){
            return nullptr;
        }
        else {
            return mLoading.front();
        }
    }

    static const char* LoaderPosString(LoaderPos, bool);

    std::list<Loader*> mLoaders; // 0x0
    unsigned int mPlatform; // 0x8
    bool mEditMode; // 0xC
    bool mCacheMode; // 0xD
    std::list<std::pair<class String, LoaderFactoryFunc*> > mFactories; // 0x10
    float mPeriod; // 0x18
    float unk1c;
    std::list<Loader*> mLoading; // 0x20
    Timer mTimer; // 0x28
    int mAsyncUnload; // 0x58
    LoaderPos mLoaderPos; // 0x5c

    static void (*sFileOpenCallback)(const char*);
};

extern LoadMgr TheLoadMgr;

#ifdef MILO_DEBUG
    #define LOADMGR_EDITMODE TheLoadMgr.EditMode()
#else
    #define LOADMGR_EDITMODE false
#endif

class FileLoader;
typedef void(FileLoader::*FileLoaderStateFunc)(void);

class FileLoader : public Loader {
public:
    FileLoader(const FilePath&, const char*, LoaderPos, int, bool, bool, BinStream*);
    virtual ~FileLoader();
    virtual const char* DebugText();
    virtual bool IsLoaded() const;
    virtual void PollLoading();

    const char* GetBuffer(int*);
    int GetSize();

    void AllocBuffer();
    void OpenFile();
    void LoadFile();
    void DoneLoading();
    void LoadStream();

    File* mFile; // 0x18
    BinStream* mStream; // 0x1c
    const char* mBuffer; // 0x20
    int mBufLen; // 0x24
    bool mAccessed; // 0x28
    bool mTemp; // 0x29
    bool mWarn; // 0x2a
    int mFlags; // 0x2c
    class String mFilename; // 0x30

    int unk3c; // 0x3c
    int unk40; // 0x40
    FileLoaderStateFunc mState; // 0x44
};

#include "utl/MakeString.h"

class NullLoader : public Loader {
public:
    NullLoader(const FilePath& fp, LoaderPos pos, Loader::Callback* cb) :
        Loader(fp, pos), mCallback(cb) {}
    virtual ~NullLoader(){ if(mCallback) mCallback->FailedLoading(this); }
    virtual const char* DebugText(){
        return MakeString("NullLoader: %s", mFile.c_str());
    }
    virtual bool IsLoaded() const { return false; }
    virtual const char* StateName() const { return "NullLoader"; }
    virtual void PollLoading(){
        mCallback->FinishLoading(this);
        mCallback = nullptr;
        delete this;
    }

    NEW_POOL_OVERLOAD(NullLoader);
    DELETE_POOL_OVERLOAD(NullLoader);

    Loader::Callback* mCallback; // 0x18
};

#endif
