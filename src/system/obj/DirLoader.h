#ifndef OBJ_DIRLOADER_H
#define OBJ_DIRLOADER_H
#include "utl/Loader.h"
#include "obj/Object.h"

class DirLoader : public Loader, public ObjRef {
public:
    DirLoader(const FilePath&, LoaderPos, Loader::Callback*, BinStream*, ObjectDir*, bool);
    virtual ~DirLoader();
    virtual bool IsLoaded() const;
    virtual const char* StateName() const;
    virtual void PollLoading();
    virtual Hmx::Object* RefOwner();
    virtual void Replace(Hmx::Object*, Hmx::Object*);

    int filler;
};

#endif

// class DirLoader : public Loader, public ObjRef {
//     // total size: 0xA8
//     void (DirLoader::* mState)(void *, void *); // offset 0x18, size 0x4
//     class String mRoot; // offset 0x24, size 0xC
//     unsigned char mOwnStream; // offset 0x30, size 0x1
//     class BinStream * mStream; // offset 0x34, size 0x4
//     int mRev; // offset 0x38, size 0x4
//     int mCounter; // offset 0x3C, size 0x4
//     class ObjPtrList mObjects; // offset 0x40, size 0x14
//     class Callback * mCallback; // offset 0x54, size 0x4
//     class ObjectDir * mDir; // offset 0x58, size 0x4
//     unsigned char mPostLoad; // offset 0x5C, size 0x1
//     unsigned char mLoadDir; // offset 0x5D, size 0x1
//     unsigned char mDeleteSelf; // offset 0x5E, size 0x1
//     const char * mProxyName; // offset 0x60, size 0x4
//     class ObjectDir * mProxyDir; // offset 0x64, size 0x4
//     class Timer mTimer; // offset 0x68, size 0x38
//     unsigned char mAccessed; // offset 0xA0, size 0x1
//     const char * mFileName; // offset 0xA4, size 0x4
// };
