#pragma once
#include "obj/Object.h"

enum ContentLocT {
    kLocationRemovableMem,
    kLocationHDD,
    kLocationRoot
};

class Content {
public:
    enum State {
        kUnmounted = 0,
        kNeedsMounting = 1,
        kMounting = 2,
        kUnmounting = 3,
        kMounted = 4,
        kAlwaysMounted = 5,
        kNeedsBackup = 6,
        kBackingUp = 7,
        kContentDeleting = 8,
        kDeleted = 9,
        kFailed = 10
    };

    Content() {}
    virtual ~Content() {}
    // fix ret types as you implement them
    virtual const char *Root() = 0;
    virtual int OnMemcard() = 0;
    virtual ContentLocT Location() = 0;
    virtual int LicenseBits() { return 0; }
    virtual bool HasValidLicenseBits() { return true; }
    virtual State GetState() = 0;
    virtual void Poll() {}
    virtual void Mount() {}
    virtual void Unmount() {}
    virtual void Delete() {}
    virtual Symbol FileName() = 0;
    virtual int DisplayName() = 0;
    virtual int GetLRM() { return 0; }
};

class ContentMgr : public Hmx::Object {
public:
    class Callback {
    public:
        Callback() {}
        virtual ~Callback() {}
        virtual void ContentStarted() {}
        virtual bool ContentDiscovered(Symbol) { return true; }
        virtual void ContentMountBegun(int) {}
        virtual void ContentAllMounted() {}
        virtual void ContentMounted(const char *, const char *) {}
        virtual void ContentUnmounted(const char *) {}
        virtual void ContentFailed(const char *) {}
        virtual void ContentLoaded(class Loader *, ContentLocT, Symbol) {}
        virtual void ContentDone() {}
        virtual void ContentCancelled() {}
        virtual const char *ContentPattern() { return ""; }
        virtual const char *ContentDir() { return "."; }
        virtual std::vector<String> *ContentAltDirs() { return 0; }
        virtual bool HasContentAltDirs() { return false; }
    };

    class CallbackFile {
    public:
        CallbackFile(const char *cc1, Callback *cb, ContentLocT t, const char *cc2)
            : unk0(cc1), unkc(cb), unk10(t), unk14(cc2) {}
        ~CallbackFile() {}
        FilePath unk0;
        Callback *unkc;
        ContentLocT unk10;
        String unk14;
    };

    ContentMgr() {}
    virtual ~ContentMgr() {}
    virtual DataNode Handle(DataArray *, bool);
    virtual void PreInit() {}
    virtual void Init();
    virtual void Terminate() {}
    virtual void StartRefresh() {}
    virtual void PollRefresh();
    virtual bool CanRefreshOnDone() { return true; }
    virtual bool ShowCurRefreshProgress() { return RefreshInProgress(); }
    virtual const char *TitleContentPath() { return 0; } // possibly wrong ret type
    virtual const char *ContentPath(int) { return 0; } // ditto
    virtual bool MountContent(Symbol) { return true; }
    virtual bool IsMounted(Symbol) { return true; }
    virtual bool DeleteContent(Symbol) { return true; }
    virtual bool IsDeleteDone(Symbol) { return true; }
    virtual bool GetLicenseBits(Symbol, unsigned long &ul) {
        ul = 0;
        return true;
    }
    virtual int GetCreationDate(Symbol) { return 0; } // ditto
    virtual bool InDiscoveryState() {
        return mState == 2 || mState == 3 || mState == 4 || mState == 5;
    }
    virtual void NotifyMounted(Content *) {}
    virtual void NotifyUnmounted(Content *) {}
    virtual void NotifyDeleted(Content *) {}
    virtual void NotifyFailed(Content *) {}
    virtual bool IsDirty() { return mDirty; }

    void AddCallbackFile(const char *, const char *);
    void RegisterCallback(Callback *, bool);
    void UnregisterCallback(Callback *, bool);
    DataNode OnAddContent(DataArray *);
    DataNode OnRemoveContent(DataArray *);
    Hmx::Object *SetReadFailureHandler(Hmx::Object *);
    bool RefreshDone() const;
    bool NeverRefreshed() const { return mState == kDone; }
    bool RefreshInProgress();
    void UpdateShouldCreateCache() {
        if (InDiscoveryState())
            mCreateSongCache = true;
    }
    bool PollContents();
    Content *FindFirstContent(Content::State);

    static void ContentRecurseCallback(const char *, const char *);

    bool mCreateSongCache; // 0x1c
    enum {
        kDone = 0,
        kDiscoveryEnumerating = 1,
        kDiscoveryMounting = 2,
        kDiscoveryLoading = 3,
        kDiscoveryCheckIfDone = 4,
        kMounting = 5,
    } mState; // 0x20
    std::list<Callback *> mCallbacks; // 0x24
    std::list<Content *> mContents; // 0x2c
    std::list<String> unk34; // 0x34 - mExtraContents?
    bool mDirty; // 0x3c
    Loader *mLoader; // 0x40
    Callback *mCallback; // 0x44
    ContentLocT mLocation; // 0x48
    String mName; // 0x4c
    int mRootLoaded; // 0x58
    std::list<CallbackFile> mCallbackFiles; // 0x5c
    Hmx::Object *mReadFailureHandler; // 0x64
};

extern ContentMgr *TheContentMgr;
extern const char *gContentStateName[11];

#include "obj/Msg.h"

DECLARE_MESSAGE(ContentReadFailureMsg, "content_read_failure");
ContentReadFailureMsg(bool b, const char *cc) : Message(Type(), b, cc) {}
// TODO: rename these methods once you actually know what the bool and const char*
// represent
bool GetBool() const { return mData->Int(2); }
const char *GetStr() const { return mData->Str(3); }
END_MESSAGE
;
