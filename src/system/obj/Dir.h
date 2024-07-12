#ifndef OBJ_DIR_H
#define OBJ_DIR_H
#include "obj/Object.h"
#include "utl/FilePath.h"
#include "utl/StringTable.h"
#include "utl/KeylessHash.h"
#include "utl/Loader.h"
#include "obj/DirLoader.h"

enum ViewportId {
    kPerspective = 0,
    kLeft = 1,
    kRight = 2,
    kTop = 3,
    kBottom = 4,
    kFront = 5,
    kBack = 6,
    kCustom = 7,
    kNumViewports = 8,
};

enum InlineDirType {
    kInlineNever = 0,
    kInlineCached = 1,
    kInlineAlways = 2,
    kInline3 = 3
};

template <class T> class ObjDirPtr : public ObjRef {
public:

    ObjDirPtr(T* dir) : mDir(dir), mLoader(0) { if(mDir) mDir->AddRef(this); }
    ObjDirPtr() : mDir(0), mLoader(0) {}
    ObjDirPtr(const ObjDirPtr& dPtr) : mDir(dPtr.mDir), mLoader(0) { if(mDir) mDir->AddRef(this); }
    virtual ~ObjDirPtr(){ *this = (T*)0; }
    virtual Hmx::Object* RefOwner(){ return 0; }
    virtual void Replace(Hmx::Object* from, Hmx::Object* to){
        if(mDir == from) *this = dynamic_cast<T*>(to);
    }
    virtual bool IsDirPtr(){ return true; }

    // GetFile__21ObjDirPtr<9ObjectDir>CFv
    FilePath& GetFile() const {
        if(mDir && mDir->mLoader){
            return mDir->mLoader->mFile;
        }
        if(mLoader) return mLoader->mFile;
        if(mDir) return mDir->mStoredFile;
        return FilePath::sNull;
    }

    // LoadFile__21ObjDirPtr<9ObjectDir>FRC8FilePathbb9LoaderPosb
    void LoadFile(const FilePath& p, bool async, bool share, LoaderPos pos, bool b3){
        *this = 0;
        DirLoader* d = 0;
        if(share){
            d = DirLoader::Find(p);
            if(d && !d->IsLoaded()){
                MILO_WARN("Can't share unloaded dir %s", p.c_str());
                d = 0;
            }
        }
        if(!d){
            if(TheLoadMgr.unk5c != 3 && TheLoadMgr.unk5c != 2){
            
            }
            else pos = kLoadFrontStayBack;
            if(!p.empty()) d = new DirLoader(p, pos, 0, 0, 0, b3);
        }
        mLoader = d;
        if(mLoader){
            if(!async || mLoader->IsLoaded()) PostLoad(0);
        }
        else if(!p.empty()) MILO_WARN("Couldn't load %s", p);
    }

    // LoadInlinedFile__21ObjDirPtr<9ObjectDir>FRC8FilePathP9BinStream

    T* operator->() const {
        MILO_ASSERT(mDir, 0x4D);
        return mDir;
    }

    // IsLoaded__21ObjDirPtr<9ObjectDir>CFv
    bool IsLoaded() const {
        bool ret = true;
        if(!mDir){
            bool b = false;
            if(mLoader && mLoader->IsLoaded()) b = true;
            if(!b) ret = false;
        }
        return ret;
    }

    // PostLoad__21ObjDirPtr<9ObjectDir>FP6Loader
    // https://decomp.me/scratch/qfnAI - seems to check out
    void PostLoad(Loader* loader){
        if(mLoader){
            TheLoadMgr.PollUntilLoaded(mLoader, loader);
            class ObjectDir* gotten = mLoader->GetDir();
            mLoader = 0;
            *this = dynamic_cast<T*>(gotten);
        }
    }

    // __as__18ObjDirPtr<6RndDir>FP6RndDir
    // https://decomp.me/scratch/yVHtf - also seems to check out
    ObjDirPtr& operator=(T* dir){
        if(mLoader && mLoader->IsLoaded()) PostLoad(0);
        if((dir != mDir) || !dir){
            delete mLoader;
            mLoader = 0;
            if(mDir){
                mDir->Release(this);
                if(!mDir->HasDirPtrs()){
                    delete mDir;
                }
            }
            mDir = dir;
            if(mDir) mDir->AddRef(this);
        }
        return *this;
    }
    
    // __as__21ObjDirPtr<9ObjectDir>FRC21ObjDirPtr<9ObjectDir>
    ObjDirPtr& operator=(const ObjDirPtr& oPtr){
        *this = oPtr.mDir;
    }

    operator T*() const { return mDir; }
    T* Ptr() const { return mDir; }

    T* mDir;
    class DirLoader* mLoader;
};

// TODO: fill out
template <class T1> BinStream& operator>>(BinStream& bs, ObjDirPtr<T1>& ptr){
    // ptr.Load(bs, true, 0);
    return bs;
}

class ObjectDir : public virtual Hmx::Object {
public:
    struct Entry {
        Entry() : name(0), obj(0) {}
        Entry& operator=(const Entry& entry){
            name = entry.name;
            obj = entry.obj;
            return *this;
        }
        bool operator==(const Entry& e) const { return name == e.name; }
        bool operator!=(const Entry& e) const { return name != e.name; }
        operator const char*() const { return name; }

        const char* name;
        Hmx::Object* obj;
    };

    struct InlinedDir {
        InlinedDir(ObjectDir* d, const FilePath& fp, bool b, InlineDirType ty);
        // Note: names are fabricated, no DWARF info
        ObjDirPtr<ObjectDir> dir; // 0x0
        FilePath file; // 0xc
        bool shared; // 0x18
        InlineDirType inlineDirType; // 0x1c
    };

    class Viewport {
    public:
        Transform mXfm;
    };

    static ObjectDir* sMainDir;

    static ObjectDir* Main() { return sMainDir; }
    static void PreInit(int, int);

    ObjectDir();
    OBJ_CLASSNAME(ObjectDir);
    OBJ_SET_TYPE(ObjectDir);
    virtual DataNode Handle(DataArray*, bool); // fn_80336C94
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp); // fn_80337B7C
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~ObjectDir();
    virtual ObjectDir* DataDir(){ return this; }
    virtual void SetProxyFile(const FilePath&, bool);
    virtual FilePath& ProxyFile(){ return mProxyFile; }
    virtual void PostSave(BinStream&);
    virtual void SetSubDir(bool);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void ResetEditorState();
    virtual bool AllowsInlineProxy(){ return mInlineProxy; }
    virtual InlineDirType InlineSubDirType();
    virtual void AddedObject(Hmx::Object*){}
    virtual void RemovingObject(Hmx::Object*);
    virtual void OldLoadProxies(BinStream&, int);

    void Reserve(int, int);
    bool IsProxy() const { return this != mDir; }
    bool HasSubDir(ObjectDir*);
    bool HasDirPtrs() const;
    Entry* FindEntry(const char*, bool);
    bool SaveSubdirs();
    void SetPathName(const char*);
    void TransferLoaderState(ObjectDir*);
    void DeleteObjects();
    void DeleteSubDirs();
    bool InlineProxy(BinStream&);
    void AddedSubDir(ObjDirPtr<ObjectDir>&);
    void RemovingSubDir(ObjDirPtr<ObjectDir>&);
    void PreLoadInlined(const FilePath&, bool, InlineDirType);
    ObjDirPtr<ObjectDir> PostLoadInlined();
    ObjectDir* NextSubDir(int&);
    void Iterate(DataArray*, bool);
    void AppendSubDir(const ObjDirPtr<ObjectDir>&);
    void RemoveSubDir(const ObjDirPtr<ObjectDir>&);
    FilePath GetSubDirPath(const FilePath&, const BinStream&);
    void LoadSubDir(int, const FilePath&, BinStream&, bool);
    DirLoader* Loader() const { return mLoader; }
    Hmx::Object* CurCam(){ return mCurCam; }
    bool IsSubDir() const { return mIsSubDir; }

    DataNode OnFind(DataArray*);

    Hmx::Object* FindObject(const char*, bool);
    template <class T> T* Find(const char* name, bool parentDirs) {
        T* castedObj = dynamic_cast<T*>(FindObject(name, false));
        if(!castedObj && parentDirs){
            MILO_FAIL(kNotObjectMsg, name, PathName(this) ? PathName(this) : "**no file**");
        }
        return castedObj;
    }

    static void Init();
    static void Terminate();

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(ObjectDir)
    static void Register(){
        REGISTER_OBJ_FACTORY(ObjectDir)
    }

    KeylessHash<const char*, Entry> mHashTable; // 0x8
    StringTable mStringTable; // 0x28
    FilePath mProxyFile; // 0x38
    bool mProxyOverride; // 0x44
    bool mInlineProxy; // 0x45
    DirLoader* mLoader; // 0x48
    std::vector<ObjDirPtr<ObjectDir> > mSubDirs; // 0x4c
    bool mIsSubDir; // 0x54
    InlineDirType mInlineSubDirType; // 0x58
    const char* mPathName; // 0x5c
    FilePath mStoredFile; // 0x60
    std::vector<InlinedDir> mInlinedDirs; // 0x6c
    Hmx::Object* mCurCam; // 0x74
    int mAlwaysInlined; // appears to be a word? - 0x78
    const char* mAlwaysInlineHash;
};

BinStream& operator>>(BinStream& bs, ObjectDir::Viewport& vp);
void PreloadSharedSubdirs(class Symbol);

extern bool gLoadingProxyFromDisk;
extern const char* kNotObjectMsg;

template <class T> class ObjDirItr {
public:
    // https://decomp.me/scratch/Qfa92
    ObjDirItr(ObjectDir* dir, bool b) : mDir(b ? dir : 0), mSubDir(dir), mWhich(0) {
        if(dir){
            // https://decomp.me/scratch/GNNj2 - KeylessHash::FirstFromStart?
            mEntry = dir->mHashTable.FirstFromStart();
            Advance();
        }
        else {
            mObj = 0;
            mEntry = 0;
        }
    }

    // https://decomp.me/scratch/47NK0
    ObjDirItr& operator++(){
        if(mEntry){
            // https://decomp.me/scratch/oVgXk - KeylessHash::FirstFromNext?
            mEntry = mSubDir->mHashTable.FirstFromNext(mEntry);
            Advance();
        }
        return *this;
    }

    operator T*(){ return mObj; }
    T* operator->() { return mObj; }

    // https://decomp.me/scratch/1uXoZ
    void Advance(){
        while(mEntry){
            mObj = dynamic_cast<T*>(mEntry->obj);
            if(mObj) return;
            mEntry = mSubDir->mHashTable.FirstFromNext(mEntry);
        }
        if(mDir){
            int nextwhich = ++mWhich;
            mSubDir = mDir->NextSubDir(nextwhich);
            if(mSubDir){
                mEntry = mSubDir->mHashTable.FirstFromStart();
                Advance();
                return;
            }
        }
        mObj = 0;
    }

    ObjectDir* mDir;
    ObjectDir* mSubDir;
    ObjectDir::Entry* mEntry;
    T* mObj;
    int mWhich;
};

#endif
