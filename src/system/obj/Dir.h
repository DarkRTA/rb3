#ifndef OBJ_DIR_H
#define OBJ_DIR_H
#include "obj/Object.h"
#include "utl/FilePath.h"
#include "utl/StringTable.h"
#include "utl/KeylessHash.h"

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

// Circular dependency moment
class DirLoader;

template <class T> class ObjDirPtr : public ObjRef {
public:

    ObjDirPtr(T* dir) : mDir(dir), mLoader(0) {}
    virtual ~ObjDirPtr(); // nightmare
    virtual Hmx::Object* RefOwner(){ return 0; }
    virtual void Replace(Hmx::Object*, Hmx::Object*); // nightmare
    virtual bool IsDirPtr(){ return true; }
    void operator=(T*);

    T* mDir;
    DirLoader* mLoader;
};

class ObjectDir : public virtual Hmx::Object {
public:
    struct Entry {
        Entry() : name(0), obj(0) {}
        Entry& operator=(const Entry& entry){
            name = entry.name;
            obj = entry.obj;
            return *this;
        }

        const char* name;
        Hmx::Object* obj;
    };

    struct InlinedDir {
        // Note: names are fabricated, no DWARF info
        ObjDirPtr<ObjectDir> dir;
        FilePath file;
        bool shared;
        InlineDirType inlineDirType;
    };

    static ObjectDir* sMainDir;

    static ObjectDir* Main() { return sMainDir; }
    static void PreInit(int, int);

    ObjectDir();
    virtual Symbol ClassName() const; // fn_800103C8
    virtual void SetType(Symbol); // fn_800102A0
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
    virtual int InlineSubDirType();
    virtual void AddedObject(Hmx::Object*);
    virtual void RemovingObject(Hmx::Object*);
    virtual void OldLoadProxies(BinStream&, int);

    void Reserve(int, int);
    bool IsProxy() const;
    bool HasSubDir(ObjectDir*);

    Hmx::Object* FindObject(const char*, bool);
    static Symbol StaticClassName();
    template <class T> T* Find(const char*, bool) {
        // return dynamic_cast<T*>(GetObj(a));
    }

    KeylessHash<const char*, Entry> mHashTable;
    StringTable mStringTable;
    FilePath mProxyFile;
    bool mProxyOverride;
    bool mInlineProxy;
    DirLoader* mLoader;
    std::vector<ObjDirPtr<ObjectDir> > mSubDirs;
    bool mIsSubDir;
    InlineDirType mInlineSubDirType;
    const char* mPathName;
    FilePath mStoredFile;
    std::vector<InlinedDir> mInlinedDirs;
    Hmx::Object* mCurCam;
    bool mAlwaysInlined;
    const char* mAlwaysInlineHash;
};

extern bool gLoadingProxyFromDisk;

#endif
