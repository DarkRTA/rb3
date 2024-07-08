#ifndef OS_CONTENTMGR_H
#define OS_CONTENTMGR_H
#include "obj/Object.h"

enum ContentLocT {
    kLocationRemovableMem,
    kLocationHDD,
    kLocationRoot
};

class Content {
public:
    Content(){}
    virtual ~Content(){}
    // fix ret types as you implement them
    virtual void Root() = 0;
    virtual int OnMemcard() = 0;
    virtual int Location() = 0;
    virtual int LicenseBits(){ return 0; }
    virtual bool HasValidLicenseBits(){ return true; }
    virtual int GetState() = 0;
    virtual void Poll(){}
    virtual void Mount(){}
    virtual void Unmount(){}
    virtual void Delete(){}
    virtual Symbol FileName() = 0;
    virtual int DisplayName() = 0;
    virtual int GetLRM(){ return 0; }
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

    class CallbackFile {
    public:
    };

    ContentMgr(){}
    virtual ~ContentMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual void PreInit(){}
    virtual void Init();
    virtual void Terminate(){}
    virtual void StartRefresh(){}
    virtual void PollRefresh();
    virtual bool CanRefreshOnDone(){ return true; }
    virtual bool ShowCurRefreshProgress(){ return RefreshInProgress(); }
    virtual const char* TitleContentPath(){ return 0; } // possibly wrong ret type
    virtual const char* ContentPath(int){ return 0; } // ditto
    virtual bool MountContent(Symbol){ return true; }
    virtual bool IsMounted(Symbol){ return true; }
    virtual bool DeleteContent(Symbol){ return true; }
    virtual bool IsDeleteDone(Symbol){ return true; }
    virtual bool GetLicensedBits(Symbol, unsigned long& ul){ ul = 0; return true; }
    virtual int GetCreationDate(Symbol){ return 0; } // ditto
    virtual bool InDiscoveryState(){ return mState == kDiscoveryLoading; }
    virtual void NotifyMounted(Content*){}
    virtual void NotifyUnmounted(Content*){}
    virtual void NotifyDeleted(Content*){}
    virtual void NotifyFailed(Content*){}
    virtual bool IsDirty(){ return mDirty; }

    void AddCallbackFile(const char*, const char*);
    void RegisterCallback(Callback*, bool);
    void UnregisterCallback(Callback*, bool);
    DataNode OnAddContent(DataArray*);
    DataNode OnRemoveContent(DataArray*);
    Hmx::Object* SetReadFailureHandler(Hmx::Object*);
    bool RefreshDone() const;
    bool RefreshInProgress(){

    }

    static void ContentRecurseCallback(const char*, const char*);

    bool mCreateSongCache; // 0x1c
    enum {
        kDone = 0,
        kDiscoveryEnumerating = 1,
        kDiscoveryMounting = 2,
        kDiscoveryLoading = 3,
        kDiscoveryCheckIfDone = 4,
        kMounting = 5,
    } mState; // 0x20
    std::list<int> unk24; // 0x24
    std::list<int> unk2c; // 0x2c
    std::list<String> unk34; // 0x34
    bool mDirty; // 0x3c
    int unk40; // 0x40
    int unk44; // 0x44
    int unk48; // 0x48
    String unk4c; // 0x4c
    int mRootLoaded; // 0x58
    std::list<CallbackFile> unk5c; // 0x5c
    Hmx::Object* mReadFailureHandler; // 0x64

    // enum /* @enum$36095BandOffline_cpp */ {
    //     kDone = 0,
    //     kDiscoveryEnumerating = 1,
    //     kDiscoveryMounting = 2,
    //     kDiscoveryLoading = 3,
    //     kDiscoveryCheckIfDone = 4,
    //     kMounting = 5,
    // } mState; // offset 0x28, size 0x4
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
