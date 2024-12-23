#pragma once
#include "meta/FixedSizeSaveable.h"
#include "obj/Msg.h"

class LocalUser; // forward dec

class WiiProfile : public Hmx::Object { // size should be 0x5c
public:
    WiiProfile();
    virtual ~WiiProfile();
    virtual DataNode Handle(DataArray *, bool);

    void Clear(int);
    int SaveSize();
    void SaveToStream(BinStream &) const;
    void LoadFromStream(BinStream &);
    void SetId(uint);
    const char *GetName() const;
    void SetName(const char *);
    bool IsFlag(uint) const;
    void SetFlag(uint, bool);

    char mSlot; // 0x1C
    uint mId; // 0x20
    uint mFlags; // 0x24
    int unk_0x28; // 0x28
    char mProfileName[48]; // 0x2c
};

class WiiProfileMgr : public FixedSizeSaveable, public MsgSource {
public:
    WiiProfileMgr();
    virtual ~WiiProfileMgr();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void SetProfileDirty(int);
    int GetIndexForUser(const LocalUser*) const;
    int GetIdForIndex(int) const;
    bool IsIndexValid(int) const;
    int GetIndexForPad(int) const;
    int GetPadForIndex(int) const;
    void SetPadToGuest(int);
    void Init(int, int);
    void Clear(int, int);

    static int sSaveVersion;
    static int sSaveVersionWii;
    static int SaveSize(int);

    int unk24;
    int unk28;
    int unk2c;
    int unk30;
    int unk34;
    int unk38;
    int unk3c;
    int unk40;
    int unk44;
    int unk48;
    int unk4c;
    WiiProfile mWiiProfiles[4]; // 0x50
    int unk1c0[4]; // 0x1c0
    bool unk1d0;
    bool mDirty; // 0x1d1
};

extern WiiProfileMgr TheWiiProfileMgr;
