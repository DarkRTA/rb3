#ifndef OBJ_DIR_H
#define OBJ_DIR_H
#include "obj/Object.h"
#include "utl/FilePath.h"
#include "utl/StringTable.h"

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
    ObjectDir();
    virtual Symbol ClassName() const; // fn_800103C8
    virtual void SetType(Symbol); // fn_800102A0
    virtual DataNode Handle(DataArray*, bool); // fn_80336C94
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp); // fn_80337B7C
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~ObjectDir();

    static ObjectDir* sMainDir;

    Hmx::Object* FindObject(const char*, bool);
    static Symbol StaticClassName();
    template <class T> T* Find(const char*, bool) {
        // return dynamic_cast<T*>(GetObj(a));
    }

    char mHashTable[0x20]; // should be a KeylessHash<const char*, ObjectDir::Entry*>
    StringTable mStringTable;
    FilePath mProxyFile;
    bool mProxyOverride;
    bool mInline;
    int mLoader; // should be a DirLoader*
    char mSubDirs[0x8]; // should be a vector
    bool mIsSubDir;
    int unk58;
    const char* mPathName;
    FilePath fpath2;
    char mViewports[0x8]; // should also be a vector
    int unk74;
    int unk78;
    const char* unk7c;

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

// ObjDirPtr header goes here
