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
    kInlineCached = 1 << 0,
    kInlineAlways = 1 << 1,
};

// // Circular dependency moment
// class DirLoader;

template <class T> class ObjDirPtr : public ObjRef {
public:

    ObjDirPtr(T* dir = 0) : mDir(dir), mLoader(0) { if(dir) mDir->AddRef(this); }
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
    // https://decomp.me/scratch/yVHtf - also seems to check out...maybe there's an inline depth setting somewhere?
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
        // if(mLoader && mLoader->IsLoaded()) PostLoad(0);
        // if(oPtr.mDir != mDir || !oPtr.mDir){
        //     delete mLoader;
        //     mLoader = 0;

        // }
    }

    operator bool() const { return mDir != 0; }
    operator T*() const { return mDir; }

    T* mDir;
    class DirLoader* mLoader;
};

// template <class T>
// ObjDirPtr<T>& ObjDirPtr<T>::operator=(T* dir){
//     if(mLoader && mLoader->IsLoaded()) PostLoad(0);
//     if((dir != mDir) || !dir){
//         delete mLoader;
//         mLoader = 0;
//         if(mDir){
//             mDir->Release(this);
//             if(!mDir->HasDirPtrs()){
//                 delete mDir;
//             }
//         }
//         mDir = dir;
//         if(mDir) mDir->AddRef(this);
//     }
//     return *this;
// }

class ObjectDir : public virtual Hmx::Object {
public:
    struct Entry {
        Entry() : name(0), obj(0) {}
        Entry& operator=(const Entry& entry){
            name = entry.name;
            obj = entry.obj;
            return *this;
        }
        bool operator!=(const Entry& e) const { return name != e.name; }

        operator const char*() const { return name; } // may not need this

        const char* name;
        Hmx::Object* obj;
    };

    struct InlinedDir {
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
    virtual FilePath* ProxyFile();
    virtual void PostSave(BinStream&);
    virtual void SetSubDir(bool);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void ResetEditorState();
    virtual bool AllowsInlineProxy();
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
    ObjDirPtr<ObjectDir> PostLoadInlined();
    ObjectDir* NextSubDir(int&);
    void Iterate(DataArray*, bool);

    DataNode OnFind(DataArray*);

    Hmx::Object* FindObject(const char*, bool);
    template <class T> T* Find(const char* name, bool parentDirs) {
        T* castedObj = dynamic_cast<T*>(FindObject(name, false));
        if(!castedObj && parentDirs){
            MILO_FAIL(kNotObjectMsg, name, PathName(this) ? PathName(this) : "**no file**");
        }
        return castedObj;
    }

    DECLARE_REVS;

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

#endif
