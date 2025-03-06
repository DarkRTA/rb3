#pragma once
#include "MusicLibraryNetSetlists.h"
#include "SongSetlistProvider.h"
#include "ViewSetting.h"
#include "meta/SongPreview.h"
#include "meta_band/HeaderPerformanceProvider.h"
#include "meta_band/SongSortMgr.h"
#include "net/Synchronize.h"
#include "net_band/DataResults.h"
#include "obj/Object.h"
#include "os/ContentMgr.h"
#include "os/Timer.h"
#include "ui/UIListProvider.h"
#include <vector>

class MusicLibrary : public UIListProvider,
                     public Hmx::Object,
                     public ContentMgr::Callback,
                     public Synchronizable {
public:
    class MusicLibraryTask {
    public:
        enum SetlistMode {
            kSetlistOptional = 0,
            kSetlistForced = 1,
            kSetlistForbidden = 2
        };

        MusicLibraryTask();
        void Reset();
        void ResetWithBackScreen(Symbol);
        void GetSongFilterAsString(String &);
        void SetSongFilter(const SongSortMgr::SongFilter &);

        int setlistMode; // 0x0
        SongSortMgr::SongFilter filter; // 0x4
        bool filterLocked; // 0x18
        bool allowDuplicates; // 0x19
        bool requiresStandardParts; // 0x1a
        Symbol backScreen; // 0x1c
        Symbol nextScreen; // 0x20
        int maxSetlistSize; // 0x24
        Symbol partSym; // 0x28
        int unk2c; // 0x2c
        Symbol titleToken; // 0x30
        Symbol makingSetlistToken; // 0x34
    };

    MusicLibrary(SongPreview &);
    virtual ~MusicLibrary() {}
    virtual void Text(int, int, UIListLabel *, UILabel *) const;
    virtual RndMat *Mat(int, int, UIListMesh *) const;
    virtual void Custom(int, int, class UIListCustom *, Hmx::Object *) const;
    virtual int NumData() const;
    virtual bool IsActive(int) const;
    virtual void InitData(RndDir *);
    virtual UIComponent::State
    ComponentStateOverride(int, int, UIComponent::State s) const;
    virtual int SnappableAtOrBeforeData(int) const;
    virtual bool IsSnappableAtData(int) const;
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void ContentStarted();
    virtual void ContentMounted(const char *, const char *);
    virtual void ContentDone();
    virtual const char *ContentDir();
    virtual void SyncSave(BinStream &, unsigned int) const;
    virtual void SyncLoad(BinStream &, unsigned int);
    virtual bool HasSyncPermission() const;
    virtual void OnSynchronized(unsigned int);

    const std::vector<int> &GetSetlist();
    void AppendToSetlist(int);
    void RemoveLastSongFromSetlist();

    static void Init(SongPreview &);

    bool unk40; // 0x40
    MusicLibraryTask mTask; // 0x44
    SongSortMgr::SongFilter mFilter; // 0x7c
    ViewSettingsProvider *mViewSettingsProvider; // 0x90
    SongPreview &mSongPreview; // 0x94
    Timer mSongPreviewTimer; // 0x98
    float unkc8;
    Symbol unkcc;
    int unkd0;
    Symbol unkd4;
    int unkd8;
    int unkdc;
    int unke0;
    int unke4;
    int unke8;
    bool unkec;
    int unkf0;
    int unkf4;
    int unkf8;
    int unkfc;
    int unk100;
    int unk104;
    int unk108;
    int unk10c;
    int unk110;
    int unk114;
    int unk118;
    int unk11c;
    int unk120;
    int unk124;
    int unk128;
    bool unk12c;
    bool unk12d;
    std::vector<int> unk130;
    SetlistProvider *mSetlistProvider; // 0x138
    int unk13c; // 0x13c
    DataResultList unk140; // 0x140
    MusicLibraryNetSetlists *mNetSetlists; // 0x158
    bool unk15c;
    SetlistScoresProvider *mSetlistScoresProvider; // 0x160
    bool unk164;
    int unk168;
    short unk16c;
    int unk170;
    int unk174;
};

extern MusicLibrary *TheMusicLibrary;