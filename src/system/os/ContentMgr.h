#ifndef OS_CONTENTMGR_H
#define OS_CONTENTMGR_H
#include "obj/Object.h"

enum ContentLocT {
    kLocationRemovableMem,
    kLocationHDD,
    kLocationRoot
};

class ContentMgr : public Hmx::Object {
public:

    class Callback {
    public:
        Callback(){}
        virtual ~Callback(){}
        virtual void ContentStarted(){}
        virtual bool ContentDiscovered(Symbol){ return true; }
        virtual void ContentMountBegun(int){}
        virtual void ContentAllMounted(){}
        virtual void ContentMounted(const char*, const char*){}
        virtual void ContentUnmounted(const char*){}
        virtual void ContentFailed(const char*){}
        virtual void ContentLoaded(class Loader*, ContentLocT, Symbol){}
        virtual void ContentDone(){}
        virtual void ContentCancelled(){}
        virtual const char* ContentPattern(){ return ""; }
        virtual const char* ContentDir(){ return "."; }
        virtual const char* ContentAltDirs(){ return 0; }
        virtual bool HasContentAltDirs(){ return false; }
    };

    void RegisterCallback(Callback*, bool);
    void UnregisterCallback(Callback*, bool);

    enum /* @enum$36095BandOffline_cpp */ {
        kDone = 0,
        kDiscoveryEnumerating = 1,
        kDiscoveryMounting = 2,
        kDiscoveryLoading = 3,
        kDiscoveryCheckIfDone = 4,
        kMounting = 5,
    } mState; // offset 0x28, size 0x4
    // class list mCallbacks; // offset 0x2C, size 0x8
    // class list mContents; // offset 0x34, size 0x8
    // class list mExtraContents; // offset 0x3C, size 0x8
    // unsigned char mDirty; // offset 0x44, size 0x1
    // class Loader * mLoader; // offset 0x48, size 0x4
    // class Callback * mCallback; // offset 0x4C, size 0x4
    // enum ContentLocT mLocation; // offset 0x50, size 0x4
    // class String mName; // offset 0x54, size 0xC
    // int mRootLoaded; // offset 0x60, size 0x4
    // class list mCallbackFiles; // offset 0x64, size 0x8
};

extern ContentMgr* TheContentMgr;

#endif
