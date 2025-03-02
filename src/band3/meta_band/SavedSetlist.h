#pragma once
#include "bandobj/PatchDir.h"
#include "os/DateTime.h"
#include "os/User.h"
#include "rndobj/Tex.h"
#include "meta/FixedSizeSaveable.h"
#include "obj/Object.h"
#include "tour/TourSavable.h"
#include "meta_band/BandProfile.h"

class SavedSetlist {
public:
    SavedSetlist(const char *title, const char *desc)
        : mTitle(title), mDescription(desc) {}
    virtual ~SavedSetlist() {}
    virtual int GetType() const = 0;
    virtual Symbol GetIdentifyingToken() const = 0;
    virtual const char *GetOwner() const;
    virtual RndTex *GetArtTex() const;
    virtual bool IsBattle() const;
    virtual void AddSong(int);
    virtual void SetSongs(const std::vector<int> &);
    virtual void SetTitle(const char *);
    virtual void SetDateTime(const DateTime &);
    virtual void SetDescription(const char *);

    String mTitle; // 0x4
    std::vector<int> mSongs; // 0x10
    DateTime mDateTime; // 0x18
    String mDescription; // 0x20
};

class LocalSavedSetlist : public SavedSetlist,
                          public TourSavable,
                          public FixedSizeSaveable {
public:
    LocalSavedSetlist();
    LocalSavedSetlist(BandProfile *, const char *, const char *, bool);
    virtual ~LocalSavedSetlist() {}
    virtual int GetType() const;
    virtual Symbol GetIdentifyingToken() const;
    virtual const char *GetOwner() const;
    virtual RndTex *GetArtTex() const;
    virtual void AddSong(int);
    virtual void SetSongs(const std::vector<int> &songs) {
        SavedSetlist::SetSongs(songs);
        unk4d = true;
    }
    virtual void SetTitle(const char *);
    virtual void SetDateTime(const DateTime &);
    virtual void SetDescription(const char *);
    virtual DataNode Handle(DataArray *, bool);
    virtual int SecBetweenUploads() const;
    virtual void UploadComplete();
    virtual void SaveFixed(FixedSizeSaveableStream &) const;
    virtual void LoadFixed(FixedSizeSaveableStream &, int);

    void SetOwnerProfile(BandProfile *p) { mOwnerProfile = p; }

    static int SaveSize(int);

    BandProfile *mOwnerProfile; // 0x48
    bool unk4c;
    bool unk4d;
    HxGuid mGuid; // 0x50
    PatchDescriptor mArt; // 0x60
    int unk64; // 0x64
};