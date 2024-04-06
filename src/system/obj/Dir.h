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

    static ObjectDir* sMainDir;

    static ObjectDir* Main() { return sMainDir; }

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
    bool mInline;
    int mLoader; // should be a DirLoader*
    std::vector<ObjectDir*> mSubDirs;
    bool mIsSubDir;
    int unk58;
    const char* mPathName;
    FilePath fpath2;
    std::vector<int> mViewPorts; // fix the vector's data type
    int unk74;
    int unk78;
    const char* unk7c;

};

template <class T> class ObjDirPtr : public ObjRef {
public:

    ObjDirPtr(T* dir) : mDir(dir), mLoader(0) {}
    virtual ~ObjDirPtr(); // nightmare
    virtual Hmx::Object* RefOwner(){ return 0; }
    virtual void Replace(Hmx::Object*, Hmx::Object*); // nightmare
    virtual bool IsDirPtr(){ return true; }
    void operator=(T*);

    T* mDir;
    int* mLoader; // DirLoader*
};

#endif

// class ObjectDir : public virtual Object {
//     // total size: 0xAC
// public:
//     void * __vptr$; // offset 0x4, size 0x4
// private:
//     class KeylessHash mHashTable; // offset 0x8, size 0x20
//     class StringTable mStringTable; // offset 0x28, size 0x14
//     class FilePath mProxyFile; // offset 0x3C, size 0xC
//     unsigned char mProxyOverride; // offset 0x48, size 0x1
//     unsigned char mInline; // offset 0x49, size 0x1
//     class DirLoader * mLoader; // offset 0x4C, size 0x4
//     class vector mSubDirs; // offset 0x50, size 0xC
//     unsigned char mIsSubDir; // offset 0x5C, size 0x1
//     char * mPathName; // offset 0x60, size 0x4
//     class vector mViewports; // offset 0x64, size 0xC
//     enum ViewportId mCurViewport; // offset 0x70, size 0x4
//     class Object * mCurAnim; // offset 0x74, size 0x4
//     class Object * mCurCam; // offset 0x78, size 0x4
//     const char * mDestFileName; // offset 0x7C, size 0x4
// };
