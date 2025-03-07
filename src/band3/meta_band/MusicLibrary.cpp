#include "meta_band/MusicLibrary.h"
#include "MusicLibraryNetSetlists.h"
#include "SongSetlistProvider.h"
#include "ViewSetting.h"
#include "decomp.h"
#include "game/Defines.h"
#include "game/GameMode.h"
#include "meta/SongPreview.h"
#include "meta_band/HeaderPerformanceProvider.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/SongSortMgr.h"
#include "net/Synchronize.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

MusicLibrary *TheMusicLibrary;

void MusicLibrary::Init(SongPreview &prev) {
    MILO_ASSERT(!TheMusicLibrary, 0x53);
    TheMusicLibrary = new MusicLibrary(prev);
}

DECOMP_FORCEACTIVE(MusicLibrary, "TheMusicLibrary")

MusicLibrary::MusicLibrary(SongPreview &prev)
    : Synchronizable("music_library"), unk40(0),
      mViewSettingsProvider(new ViewSettingsProvider()), mSongPreview(prev),
      mSongPreviewDelay(0), unkcc(gNullStr), unkd0(0), unkd4(gNullStr), unkd8(0),
      unkdc(0), unke0(0), unke4(8), unke8(9), unkec(0), mHeaderMat(0), mSubheaderMat(0),
      mFunctionMat(0), mFunctionSetlistMat(0), mRockCentralMat(0), mDiscMatEven(0),
      mDiscMatOdd(0), mDlcMatEven(0), mDlcMatOdd(0), mStoreMatEven(0), mStoreMatOdd(0),
      mUgcMatEven(0), mUgcMatOdd(0), mSetlistMatEven(0), mSetlistMatOdd(0), unk12c(0),
      unk12d(0), mSetlistProvider(new SetlistProvider()), unk13c(0),
      mNetSetlists(new MusicLibraryNetSetlists()), unk15c(0),
      mSetlistScoresProvider(new SetlistScoresProvider()), mHasHeaderData(0),
      mHeaderCareerScore(0), mHeaderCareerInstrumentMask(0), mHeaderCareerStars(0),
      mHeaderPossibleStars(0) {
    SetName("music_library", ObjectDir::Main());
}

MusicLibrary::~MusicLibrary() {
    delete mSetlistProvider;
    delete mSetlistScoresProvider;
    delete mViewSettingsProvider;
    delete mNetSetlists;
}

void MusicLibrary::OnLoad() {}

void MusicLibrary::OnEnter() {
    ThePlatformMgr.SetHomeMenuEnabled(false);
    unk40 = true;
    UIPanel *panel = ObjectDir::Main()->Find<UIPanel>("song_select_panel", true);
    mSongPreviewDelay = panel->TypeDef()->FindFloat("song_preview_delay");
    if (TheGameMode->InMode(qp_party_shuffle)) {
        ClearSetlist();
        TheGameMode->SetMode(qp_coop);
    }
    if (TheGameMode->InMode(qp_practice)) {
        TheSessionMgr->mCritUserListener->ClearCriticalUser();
        TheGameMode->SetMode(qp_coop);
    }
    if (TheGameMode->InMode(trainer)) {
        ControllerType ty =
            (ControllerType)panel->Property("trainer_from_main_menu", true)->Int();
        if (ty - 3 <= 1U) {
            SetupTaskForTrainer(ty);
        } else {
            TheSessionMgr->mCritUserListener->ClearCriticalUser();
            TheGameMode->SetMode(qp_coop);
        }
    }
    if (!TheUI.WentBack()) {
        if (!TheGameMode->Property(custom_music_library_tasks, true)->Int()) {
            mTask.Reset();
            mTask.SetSongFilter(mFilter);
        }
        int i5 = unkec ? unke4 : unke0;
        if (unkdc != i5) {
            unkdc = i5;
            unkd0 = 0;
        }
        unkec = false;
    }
    if (TheGameMode->InMode(practice)) {
        mTask.setlistMode = 2;
    }
    if (TheGameMode->InMode(qp_coop) && !TheSessionMgr->IsLocal()) {
        mTask.setlistMode = 1;
    }
}

MusicLibrary::MusicLibraryTask::MusicLibraryTask() { Reset(); }

void MusicLibrary::MusicLibraryTask::Reset() {
    setlistMode = 0;
    filter.Reset();
    filterLocked = false;
    allowDuplicates = true;
    requiresStandardParts = true;
    backScreen = main_hub_screen;
    nextScreen = part_difficulty_screen;
    maxSetlistSize = 0;
    partSym = gNullStr;
    unk2c = 11;
    titleToken = music_library;
    makingSetlistToken = making_setlist;
}

void MusicLibrary::MusicLibraryTask::ResetWithBackScreen(Symbol s) {
    Reset();
    backScreen = s;
}

void MusicLibrary::MusicLibraryTask::GetSongFilterAsString(String &str) {
    for (int i = 0; i < kNumFilterTypes; i++) {
        const std::set<Symbol> &filterSet = filter.GetFilterSet((FilterType)i);
        if (!filterSet.empty()) {
            str += MakeString("%i:", i);
            FOREACH (it, filterSet) {
                Symbol cur = *it;
                if (it != filterSet.begin())
                    str += ",";
                str += cur.mStr;
            }
            str += ";";
        }
    }
}

void MusicLibrary::MusicLibraryTask::SetSongFilter(const SongSortMgr::SongFilter &filt) {
    filter = filt;
}

bool MusicLibrary::GetFilterLocked() { return mTask.filterLocked; }
bool MusicLibrary::GetDuplicatesAllowed() { return mTask.allowDuplicates; }
bool MusicLibrary::GetForcedSetlist() { return mTask.setlistMode == 1; }
int MusicLibrary::GetMaxSetlistSize() { return mTask.maxSetlistSize; }
void MusicLibrary::SetTask(MusicLibraryTask &task) { mTask = task; }
SongSortMgr::SongFilter &MusicLibrary::GetFilter() { return mTask.filter; }

void MusicLibrary::InitData(RndDir *dir) {
    mHeaderMat = dir->Find<RndMat>("header.mat", false);
    mSubheaderMat = dir->Find<RndMat>("subheader.mat", false);
    mFunctionMat = dir->Find<RndMat>("function.mat", false);
    mFunctionSetlistMat = dir->Find<RndMat>("function_setlist.mat", false);
    mRockCentralMat = dir->Find<RndMat>("rockcentral.mat", false);
    mDiscMatEven = dir->Find<RndMat>("song_disc_dark.mat", false);
    mDiscMatOdd = dir->Find<RndMat>("song_disc_light.mat", false);
    mDlcMatEven = dir->Find<RndMat>("song_dlc_dark.mat", false);
    mDlcMatOdd = dir->Find<RndMat>("song_dlc_light.mat", false);
    mStoreMatEven = dir->Find<RndMat>("song_store_dark.mat", false);
    mStoreMatOdd = dir->Find<RndMat>("song_store_light.mat", false);
    mUgcMatEven = dir->Find<RndMat>("song_ugc_dark.mat", false);
    mUgcMatOdd = dir->Find<RndMat>("song_ugc_light.mat", false);
    mSetlistMatEven = dir->Find<RndMat>("setlist_dark.mat", false);
    mSetlistMatOdd = dir->Find<RndMat>("setlist_light.mat", false);
}