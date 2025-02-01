#pragma once
#include "meta/FixedSizeSaveable.h"
#include "meta/Profile.h"
#include "obj/Msg.h"

class LocalUser; // forward dec

class WiiProfile : public Hmx::Object { // size should be 0x5c
public:
    WiiProfile();
    virtual ~WiiProfile();
    virtual DataNode Handle(DataArray *, bool);

    void Clear(int);
    void SaveToStream(BinStream &) const;
    void LoadFromStream(BinStream &);
    void SetId(uint);
    const char *GetName() const;
    void SetName(const char *);
    bool IsFlag(uint) const;
    void SetFlag(uint, bool);
    static int SaveSize();

    char mSlot; // 0x1C
    uint mId; // 0x20
    uint mFlags; // 0x24
    int mHasSeenFirstTimeInstrumentFlags; // 0x28
    char mProfileName[48]; // 0x2c
};

#define kNumWiiPads 4

class WiiProfileMgr : public FixedSizeSaveable, public MsgSource {
public:
    WiiProfileMgr();
    virtual ~WiiProfileMgr();
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);

    void SetProfileDirty(int);
    int GetIndexForUser(const LocalUser *) const;
    int GetIdForIndex(int) const;
    bool IsIndexValid(int) const;
    int GetIndexForPad(int) const;
    int GetPadForIndex(int) const;
    void SetPadToGuest(int);
    void Init(int, int);
    void Clear(int, int);
    WiiProfile *GetProfileForPad(int);
    bool IsPadAGuest(int) const;
    bool IsPadRegistered(int) const;
    const char *GetNameForPad(int) const;
    int Count(unsigned int) const;
    bool NeedsSave() const;
    bool NeedsLoading() const;
    void PostSave();
    void PreLoad();
    void CreateProfile(int);
    void SetIndexValid(int, bool);
    void SetIndexSaved(int, bool);
    bool DeleteProfile(int);
    bool IsIndexRegistered(int) const;
    bool AddIdToDeleteQueue(unsigned int);
    void RegisterProfile(int, unsigned int);
    void SetIndexRegistered(int, bool);
    int GetNextEmptyIndex() const;
    void SetPadToIndex(int, int);
    void RemovePad(int);
    WiiProfile *GetProfileForIndex(int);
    const char *GetNameForIndex(int) const;
    void SetIndexName(int, const char *);
    int GetIndexForName(const char *, int) const;
    bool IsSlotAvailable() const;
    bool IsIndexSaved(int) const;
    bool IsIndexLoaded(int) const;
    void SetIndexLoaded(int, bool);
    bool IsIndexSwapping(int) const;
    bool IsIndexLocked(int) const;
    void SetIndexLocked(int, bool);
    void SetLocked(Profile *, bool);
    void DoSignin(LocalUser *, int, int, int);
    bool IsDeleteQueueFull() const;
    int GetHasSeenFirstTimeInstrumentFlagsForUser(const LocalUser *) const;
    void SetHasSeenFirstTimeInstrumentFlagsForUser(const LocalUser *, int, bool);

    static int sSaveVersion;
    static int sSaveVersionWii;
    static int SaveSize(int);

    int mDeleteQueue[10]; // 0x24
    int unk4c;
    WiiProfile mWiiProfiles[4]; // 0x50
    int mPadProfileIndex[4]; // 0x1c0
    bool mHasLoaded; // 0x1d0
    bool mDirty; // 0x1d1
};

extern WiiProfileMgr TheWiiProfileMgr;
