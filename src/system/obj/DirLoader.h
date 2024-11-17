#pragma once
#include "os/Timer.h"
#include "utl/Loader.h"
#include "obj/Object.h"
#include "utl/MemPoint.h"
#include "utl/PoolAlloc.h"
#include "obj/ObjPtr_p.h"

class DirLoader;
class ObjectDir;
typedef void(DirLoader::*DirLoaderStateFunc)(void);

class DirLoader : public Loader, public ObjRef {
public:
    DirLoader(const FilePath&, LoaderPos, Loader::Callback*, BinStream*, class ObjectDir*, bool);
    virtual ~DirLoader();
    virtual bool IsLoaded() const;
    virtual const char* StateName() const;
    virtual void PollLoading();
    virtual Hmx::Object* RefOwner();
    virtual void Replace(Hmx::Object*, Hmx::Object*);

    void Cleanup(const char*);
    class ObjectDir* GetDir();
    static bool SaveObjects(const char*, class ObjectDir*);
    Symbol FixClassName(Symbol);
    bool SetupDir(Symbol);

    void OpenFile();
    void LoadHeader();
    void LoadDir();
    void LoadResources();
    void CreateObjects();
    void LoadObjs();
    void DoneLoading();
    void ResolveEndianness();

    NEW_POOL_OVERLOAD(DirLoader);
    DELETE_POOL_OVERLOAD(DirLoader);

    static bool sCacheMode;
    static bool sPrintTimes;
    static class ObjectDir* sTopSaveDir;
    static int mbTrackObjMem;

    static DirLoader* Find(const FilePath&);
    static DirLoader* FindLast(const FilePath&);
    static void PrintLoaded(const char*);
    static class ObjectDir* LoadObjects(const FilePath&, Loader::Callback*, BinStream*);
    static void SetCacheMode(bool);
    static Symbol GetDirClass(const char*);
    static const char* CachedPath(const char*, bool);
    static Loader* New(const FilePath& f, LoaderPos l) {return new DirLoader(f, l, NULL, NULL, NULL, false);}

    DirLoaderStateFunc mState; // 0x1c
    class String mRoot; // 0x28
    bool mOwnStream; // 0x34
    BinStream* mStream; // 0x38
    int mRev; // 0x3c
    int mCounter; // 0x40
    ObjPtrList<Hmx::Object> mObjects; // 0x44
    Callback* mCallback; // 0x54
    class ObjectDir* mDir; // 0x58
    bool mPostLoad; // 0x5c
    bool mLoadDir; // 0x5d
    bool mDeleteSelf; // 0x5e
    const char* mProxyName; // 0x60
    class ObjectDir* mProxyDir; // 0x64
    Timer mTimer; // 0x68
    bool mAccessed; // 0x98
    bool unk99; // 0x99
};

class TrackObjMem {
public:
    TrackObjMem();
    char* unk0; // 0x0
    char* unk4; // 0x4
    char* unk8;
    MemPointDelta* unkc;
};