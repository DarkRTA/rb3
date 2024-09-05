#ifndef META_WIIPROFILEMGR_H
#define META_WIIPROFILEMGR_H

#include "meta/FixedSizeSaveable.h"
#include "obj/MsgSource.h"

class LocalUser; // forward dec

class WiiProfile : public Hmx::Object {
public:
    WiiProfile();
    ~WiiProfile();

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
    char *mProfileName; // 0x2c
};

class WiiProfileMgr : public FixedSizeSaveable, public MsgSource {
public:
    WiiProfileMgr();
    ~WiiProfileMgr();

    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void SetProfileDirty(int);
    int GetIndexForUser(const LocalUser*) const;
    int GetIdForIndex(int) const;
    bool IsIndexValid(int) const;
    int GetIndexForPad(int) const;

    static int sSaveVersion;
    static int sSaveVersionWii;
};

extern WiiProfileMgr TheWiiProfileMgr;

#endif
