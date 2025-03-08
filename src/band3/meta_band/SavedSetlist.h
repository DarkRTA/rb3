#pragma once
#include "bandobj/PatchDir.h"
#include "os/DateTime.h"
#include "os/OnlineID.h"
#include "os/User.h"
#include "rndobj/Tex.h"
#include "meta/FixedSizeSaveable.h"
#include "obj/Object.h"
#include "tour/TourSavable.h"
#include "meta_band/BandProfile.h"
#include "utl/HxGuid.h"

class SavedSetlist {
public:
    enum SetlistType {
        kSetlistLocal = 0,
        kSetlistInternal = 1,
        kSetlistFriend = 2,
        kSetlistHarmonix = 3,
        kBattleHarmonix = 4,
        kBattleFriend = 5,
        kBattleHarmonixArchived = 6,
        kBattleFriendArchived = 7
    };
    SavedSetlist(const char *title, const char *desc)
        : mTitle(title), mDescription(desc) {}
    virtual ~SavedSetlist() {}
    virtual SetlistType GetType() const = 0;
    virtual Symbol GetIdentifyingToken() const = 0;
    virtual const char *GetOwner() const;
    virtual RndTex *GetArtTex() const;
    virtual bool IsBattle() const;
    virtual void AddSong(int);
    virtual void SetSongs(const std::vector<int> &);
    virtual void SetTitle(const char *);
    virtual void SetDateTime(const DateTime &dt) { mDateTime = dt; }
    virtual void SetDescription(const char *);

    int GetLengthMs() const;
    const char *GetTitle() const { return mTitle.c_str(); }
    const char *GetDescription() const { return mDescription.c_str(); }

    static Symbol SetlistTypeToSym(SetlistType);

    String mTitle; // 0x4
    std::vector<int> mSongs; // 0x10
    DateTime mDateTime; // 0x18
    String mDescription; // 0x20
};

class NetSavedSetlist : public SavedSetlist {
public:
    NetSavedSetlist(const char *title, const char *desc) : SavedSetlist(title, desc) {}
    virtual ~NetSavedSetlist() {}
    virtual SetlistType GetType() const;
    virtual Symbol GetIdentifyingToken() const;
    virtual const char *GetOwner() const;

    const OnlineID *GetOwnerOnlineID() const;
    const char *GetArtUrl() const;
    const char *GetSongTitle(int) const;
    void AddSongTitle(const char *);

    int mSetlistType; // 0x2c
    String mOwner; // 0x30
    OnlineID mOID; // 0x3c
    int unk44;
    String unk48;
    String mGuid; // 0x54
    std::vector<String> mSongTitles; // 0x60
};

class BattleSavedSetlist : public NetSavedSetlist {
public:
    BattleSavedSetlist(const char *title, const char *desc)
        : NetSavedSetlist(title, desc) {}
    virtual ~BattleSavedSetlist() {}
    virtual Symbol GetIdentifyingToken() const;
    virtual bool IsBattle() const { return true; }

    int unk68; // 0x68
};

class LocalSavedSetlist : public SavedSetlist,
                          public TourSavable,
                          public FixedSizeSaveable {
public:
    LocalSavedSetlist();
    LocalSavedSetlist(BandProfile *, const char *, const char *, bool);
    virtual ~LocalSavedSetlist() {}
    virtual SetlistType GetType() const { return kSetlistLocal; }
    virtual Symbol GetIdentifyingToken() const;
    virtual const char *GetOwner() const { return mOwnerProfile->GetName(); }
    virtual RndTex *GetArtTex() const;
    virtual void AddSong(int song) {
        SavedSetlist::AddSong(song);
        mNeedsUpload = true;
    }
    virtual void SetSongs(const std::vector<int> &songs) {
        SavedSetlist::SetSongs(songs);
        mNeedsUpload = true;
    }
    virtual void SetTitle(const char *title) {
        mTitle = title;
        mNeedsUpload = true;
    }
    virtual void SetDateTime(const DateTime &dt) {
        mDateTime = dt;
        mNeedsUpload = true;
    }
    virtual void SetDescription(const char *desc) {
        mDescription = desc;
        mNeedsUpload = true;
    }
    virtual DataNode Handle(DataArray *, bool);
    virtual int SecBetweenUploads() const { return 45; }
    virtual void UploadComplete();
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);

    void ProcessRetCode(int);
    DataNode OnMsg(const RockCentralOpCompleteMsg &);

    void SetOwnerProfile(BandProfile *p) { mOwnerProfile = p; }
    bool GetShared() const { return mIsShared; }
    void SetShared(bool b) {
        mIsShared = b;
        mNeedsUpload = true;
    }

    static int SaveSize(int);

    BandProfile *mOwnerProfile; // 0x48
    bool mIsShared; // 0x4c
    bool mNeedsUpload; // 0x4d
    HxGuid mGuid; // 0x50
    PatchDescriptor mArt; // 0x60
    int unk68; // 0x68
};