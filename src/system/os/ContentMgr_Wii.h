#pragma once
#include "os/ContentMgr.h"
#include "os/ThreadCall.h"

bool CntSdRsoInit(struct RSOObjectHeader*);
void CntSdRsoTerminate();

// RootContent : Content

class WiiContent : public Content, public ThreadCallback {
public:
    WiiContent(Symbol, unsigned long long, unsigned int, bool, bool);
    virtual ~WiiContent();
    virtual const char* Root();
    virtual int OnMemcard();
    virtual ContentLocT Location();
    virtual State GetState();
    virtual void Poll();
    virtual void Mount();
    virtual void Unmount();
    virtual void Delete();
    virtual Symbol FileName();
    virtual int DisplayName();
    virtual int ThreadStart();
    virtual void ThreadDone(int);

    void Enumerate(const char*, void(*)(const char*, const char*), bool, const char*);

    int unk8; // 0x8 - mState?
    Symbol mName; // 0xc
    unsigned long long mTitleId; // 0x10
    unsigned int mContentId; // 0x18
    int unk1c; // 0x1c
    int unk20; // 0x20
    int unk24; // 0x24
    int unk28; // 0x28
    int unk2c; // 0x2c - location
    bool unk30; // 0x30
    bool unk31; // 0x31
    bool unk32; // 0x32
};

class WiiContentMgr : public ContentMgr {
public:
    WiiContentMgr();
    virtual ~WiiContentMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual void PreInit();
    virtual void Init();
    virtual void Terminate();
    virtual void StartRefresh();
    virtual void PollRefresh();
    virtual bool CanRefreshOnDone();
    virtual bool ShowCurRefreshProgress();  
    virtual bool MountContent(Symbol);
    virtual bool IsMounted(Symbol);
    virtual bool DeleteContent(Symbol);
    virtual bool IsDeleteDone(Symbol);
    virtual void NotifyMounted(Content*);
    virtual void NotifyUnmounted(Content*);
    virtual void NotifyDeleted(Content*);
    virtual void NotifyFailed(Content*);

    void UnmountContents(Symbol);
    WiiContent* ContentOf(Symbol);
};

extern WiiContentMgr TheWiiContentMgr;
extern const char* gCurContentName;
