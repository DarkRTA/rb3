#pragma once
#include "MusicLibraryNetSetlists.h"
#include "SongSetlistProvider.h"
#include "ViewSetting.h"
#include "game/Defines.h"
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
    virtual ~MusicLibrary();
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
    void OnLoad();
    void OnEnter();
    void ClearSetlist();
    void SetupTaskForTrainer(ControllerType);
    bool GetFilterLocked();
    bool GetDuplicatesAllowed();
    bool GetForcedSetlist();
    int GetMaxSetlistSize();
    void SetTask(MusicLibraryTask &);
    SongSortMgr::SongFilter &GetFilter();
    int SongAtSetlistIndex(int);
    int SetlistSize();
    bool SetlistIsFull();
    bool CanHeadersBeSelected();
    ScoreType ActiveScoreType() const;
    bool GetMakingSetlist(bool) const;
    bool NetSetlistsFailed();
    bool NetSetlistsSucceeded();
    Symbol DifficultySortPart() const;

    static void Init(SongPreview &);

    bool unk40; // 0x40
    MusicLibraryTask mTask; // 0x44
    SongSortMgr::SongFilter mFilter; // 0x7c
    ViewSettingsProvider *mViewSettingsProvider; // 0x90
    SongPreview &mSongPreview; // 0x94
    Timer mSongPreviewTimer; // 0x98
    float mSongPreviewDelay; // 0xc8
    Symbol unkcc;
    int unkd0;
    Symbol unkd4;
    int unkd8;
    int unkdc; // should be enum SongSortType
    int unke0;
    int unke4;
    int unke8;
    bool unkec;
    RndMat *mHeaderMat; // 0xf0
    RndMat *mSubheaderMat; // 0xf4
    RndMat *mFunctionMat; // 0xf8
    RndMat *mFunctionSetlistMat; // 0xfc
    RndMat *mRockCentralMat; // 0x100
    RndMat *mDiscMatEven; // 0x104
    RndMat *mDiscMatOdd; // 0x108
    RndMat *mDlcMatEven; // 0x10c
    RndMat *mDlcMatOdd; // 0x110
    RndMat *mStoreMatEven; // 0x114
    RndMat *mStoreMatOdd; // 0x118
    RndMat *mUgcMatEven; // 0x11c
    RndMat *mUgcMatOdd; // 0x120
    RndMat *mSetlistMatEven; // 0x124
    RndMat *mSetlistMatOdd; // 0x128
    bool unk12c;
    bool unk12d;
    std::vector<int> mSetlist; // 0x130
    SetlistProvider *mSetlistProvider; // 0x138
    int unk13c; // 0x13c
    DataResultList mResults; // 0x140
    MusicLibraryNetSetlists *mNetSetlists; // 0x158
    bool unk15c;
    SetlistScoresProvider *mSetlistScoresProvider; // 0x160
    bool mHasHeaderData; // 0x164
    int mHeaderCareerScore; // 0x168
    short mHeaderCareerInstrumentMask; // 0x16c
    int mHeaderCareerStars; // 0x170
    int mHeaderPossibleStars; // 0x174
};

extern MusicLibrary *TheMusicLibrary;