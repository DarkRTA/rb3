#include "meta_band/MusicLibrary.h"
#include "MusicLibraryNetSetlists.h"
#include "SongSetlistProvider.h"
#include "SongSortMgr.h"
#include "ViewSetting.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "game/GameMode.h"
#include "meta/Profile.h"
#include "meta/SongPreview.h"
#include "meta_band/BandMachine.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/HeaderPerformanceProvider.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SavedSetlist.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/SongSort.h"
#include "meta_band/SongSortMgr.h"
#include "meta_band/SongSortNode.h"
#include "meta_band/UIEventMgr.h"
#include "meta_band/Utl.h"
#include "net/Server.h"
#include "net/Synchronize.h"
#include "net/WiiFriendMgr.h"
#include "net_band/RockCentral.h"
#include "obj/Dir.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/DataPointMgr.h"
#include "utl/Messages2.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

MusicLibrary *TheMusicLibrary;

void MusicLibrary::Init(SongPreview &prev) {
    MILO_ASSERT(!TheMusicLibrary, 0x53);
    TheMusicLibrary = new MusicLibrary(prev);
}

void MusicLibrary::Poll() {
    if (unk12c)
        PushSetlistToScreen();
    if (mNetSetlists)
        mNetSetlists->Poll();
    if (unke8 != 9) {
        NodeSort *sort = TheSongSortMgr->GetSort(unke8);
        sort->PollReady();
        if (sort->IsReady()) {
            SongSortType old = unke8;
            unke8 = kNumSongSortTypes;
            SetSort(old);
        }
    }
    CheckSongPreview();
}

DECOMP_FORCEACTIVE(MusicLibrary, "TheMusicLibrary")

MusicLibrary::MusicLibrary(SongPreview &prev)
    : Synchronizable("music_library"), unk40(0),
      mViewSettingsProvider(new ViewSettingsProvider()), mSongPreview(prev),
      mSongPreviewDelay(0), unkcc(gNullStr), unkd0(0), unkd4(gNullStr), unkd8(kNodeNone),
      unkdc(kSongSortBySong), unke0(0), unke4(8), unke8(kNumSongSortTypes), unkec(0),
      mHeaderMat(0), mSubheaderMat(0), mFunctionMat(0), mFunctionSetlistMat(0),
      mRockCentralMat(0), mDiscMatEven(0), mDiscMatOdd(0), mDlcMatEven(0), mDlcMatOdd(0),
      mStoreMatEven(0), mStoreMatOdd(0), mUgcMatEven(0), mUgcMatOdd(0),
      mSetlistMatEven(0), mSetlistMatOdd(0), unk12c(0), unk12d(0),
      mSetlistProvider(new SetlistProvider()), unk13c(0),
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
            unkdc = (SongSortType)i5;
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
    NodeSort *sort = TheSongSortMgr->GetSort(unkdc);
    if (!sort->IsReady()) {
        unke0 = 2;
        unkdc = kSongSortByDiff;
        MILO_ASSERT(TheSongSortMgr->GetSort(kSongSortByDiff)->IsReady(), 0x11E);
    }
    mViewSettingsProvider->BuildFilters(PartForFilter());
    TheSongSortMgr->BuildFilteredSongList(&mTask.filter, PartForFilter());
    TheSongSortMgr->BuildSetlistList();
    TheSongSortMgr->BuildSortTree(unkdc);
    TheSongSortMgr->BuildSortList(unkdc);
    TryToSetHighlight(unkd4, unkd8, true);
    unk15c = false;
    if (SongSortMgr::IsSetlistSort(unkdc)) {
        RefreshNetSetlists();
    }
    if (!TheUI.WentBack()) {
        if (mTask.setlistMode == 0 || mTask.setlistMode == 2) {
            SetMakingSetlist(false);
        } else
            SetMakingSetlist(true);
    }
    if (!GetMakingSetlist(false) || !TheUI.WentBack()) {
        ClearSetlist();
    }
    PushFilterToScreen();
    PushSortToScreen();
    UpdateHeaderData();
    TheProfileMgr.AddSink(this, PrimaryProfileChangedMsg::Type());
    TheProfileMgr.AddSink(this, ProfileChangedMsg::Type());
    ThePlatformMgr.AddSink(this, SigninChangedMsg::Type());
    ThePlatformMgr.AddSink(this, FriendsListChangedMsg::Type());
    TheServer->AddSink(this, UserLoginMsg::Type());
    TheSessionMgr->AddSink(this, LocalUserLeftMsg::Type());
    TheSessionMgr->AddSink(this, RemoteUserLeftMsg::Type());
    TheSessionMgr->AddSink(this, AddLocalUserResultMsg::Type());
    TheSessionMgr->AddSink(this, NewRemoteUserMsg::Type());
    TheRockCentral.AddSink(this, ServerStatusChangedMsg::Type());
    TheSessionMgr->GetMachineMgr()->AddSink(this, RemoteMachineUpdatedMsg::Type());
    TheSessionMgr->GetMachineMgr()->AddSink(this, RemoteMachineLeftMsg::Type());
    TheContentMgr->RegisterCallback(TheMusicLibrary, false);
}

void MusicLibrary::OnExit() {
    ClearSongPreview();
    if (!TheGameMode->Property(custom_music_library_tasks, true)->Int()) {
        mFilter = mTask.GetFilter();
    }
    TheProfileMgr.RemoveSink(this, PrimaryProfileChangedMsg::Type());
    TheProfileMgr.RemoveSink(this, ProfileChangedMsg::Type());
    ThePlatformMgr.RemoveSink(this, SigninChangedMsg::Type());
    ThePlatformMgr.RemoveSink(this, FriendsListChangedMsg::Type());
    TheServer->RemoveSink(this, UserLoginMsg::Type());
    TheSessionMgr->RemoveSink(this, LocalUserLeftMsg::Type());
    TheSessionMgr->RemoveSink(this, RemoteUserLeftMsg::Type());
    TheSessionMgr->RemoveSink(this, AddLocalUserResultMsg::Type());
    TheSessionMgr->RemoveSink(this, NewRemoteUserMsg::Type());
    TheRockCentral.RemoveSink(this, ServerStatusChangedMsg::Type());
    TheSessionMgr->GetMachineMgr()->RemoveSink(this, RemoteMachineUpdatedMsg::Type());
    TheSessionMgr->GetMachineMgr()->RemoveSink(this, RemoteMachineLeftMsg::Type());
    TheContentMgr->UnregisterCallback(TheMusicLibrary, true);
    mNetSetlists->CleanUp();
    if (unke8 != kNumSongSortTypes) {
        TheSongSortMgr->GetSort(unke8)->CancelMakeReady();
        unke8 = kNumSongSortTypes;
    }
    unk40 = false;
    ThePlatformMgr.SetHomeMenuEnabled(true);
}

bool MusicLibrary::IsExiting() { return false; }

void MusicLibrary::OnSynchronized(unsigned int) {
    if (unk40)
        PushSetlistToScreen();
}

void MusicLibrary::SyncSave(BinStream &bs, unsigned int) const { bs << mSetlist; }
void MusicLibrary::SyncLoad(BinStream &bs, unsigned int) {
    mSetlist.clear();
    bs >> mSetlist;
}

bool MusicLibrary::HasSyncPermission() const { return IsLeaderLocal(); }

void MusicLibrary::OnUnload() {
    mSetlistScoresProvider->Clear();
    TheSongSortMgr->ClearAllSorts();
    TheSongSortMgr->ClearInternalSetlists();
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
    scoreType = kNumScoreTypes;
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

void MusicLibrary::ResetFilters() {
    if (!mTask.filterLocked) {
        mTask.filter.Reset();
        TheSongSortMgr->BuildFilteredSongList(&mTask.filter, PartForFilter());
        TheSongSortMgr->BuildSortTree(unkdc);
        TheSongSortMgr->BuildSortList(unkdc);
        TryToSetHighlight(unkd4, unkd8, true);
        PushHighlightToScreen(true);
        PushFilterToScreen();
    }
}

void MusicLibrary::ResetFilter(FilterType ty) {
    if (!mTask.filterLocked && mTask.filter.HasFilterType(ty)) {
        mTask.filter.ClearFilter(ty);
        TheSongSortMgr->BuildFilteredSongList(&mTask.filter, PartForFilter());
        TheSongSortMgr->BuildSortTree(unkdc);
        TheSongSortMgr->BuildSortList(unkdc);
        TryToSetHighlight(unkd4, unkd8, true);
        PushHighlightToScreen(true);
        PushFilterToScreen();
    }
}

void MusicLibrary::ToggleFilter(FilterType ty, Symbol s) {
    if (!mTask.filterLocked) {
        if (mTask.GetFilter().HasFilter(ty, s)) {
            mTask.filter.RemoveFilter(ty, s);
        } else {
            mTask.filter.AddFilter(ty, s);
        }
        TheSongSortMgr->BuildFilteredSongList(&mTask.filter, PartForFilter());
        TheSongSortMgr->BuildSortTree(unkdc);
        TheSongSortMgr->BuildSortList(unkdc);
        TryToSetHighlight(unkd4, unkd8, true);
        PushHighlightToScreen(true);
        PushFilterToScreen();
    }
}

const char *MusicLibrary::GetStatusText() {
    int i4 = TheSongSortMgr->mSongs.size();
    std::vector<int> songs;
    TheSongMgr.GetRankedSongs(songs, true, true);
    int numSongs = songs.size();
    const char *txt = Localize(GetCurrentSortName(true), nullptr);
    if (i4 < numSongs) {
        return MakeString(
            Localize(music_library_filtered_fmt, nullptr), i4, numSongs, txt
        );
    } else {
        return MakeString(Localize(music_library_unfiltered_fmt, nullptr), i4, txt);
    }
}

void MusicLibrary::SetTaskScoreType(ScoreType ty) {
    mTask.scoreType = ty;
    RebuildUserConfigData();
}

void MusicLibrary::SetupTaskForTrainer(ControllerType ty) {
    mTask.Reset();
    mTask.filterLocked = true;
    mTask.setlistMode = 2;
    switch (ty) {
    case kControllerRealGuitar:
        mTask.filter.AddFilter(kFilterSource, has_part_yes);
        break;
    case kControllerKeys:
        mTask.filter.AddFilter(kFilterLength, has_part_yes);
        break;
    default:
        MILO_FAIL("Bad ControllerType %i in MusicLibrary::SetupTaskForTrainer!", ty);
        break;
    }
}

void MusicLibrary::ReportSortAndFilters() {
    String str;
    mTask.GetSongFilterAsString(str);
    SendDataPoint(
        "music_library/sort_and_filters",
        mode,
        TheGameMode->mMode,
        sort,
        GetCurrentSortName(true),
        filters,
        str.c_str()
    );
}

void MusicLibrary::ClearSongPreview() {
    unkcc = gNullStr;
    mSongPreviewTimer.Reset();
    mSongPreview.Start(gNullStr);
}

void MusicLibrary::StartSongPreview() {
    if (TheMusicLibrary->GetHighlightedNode()->GetToken() != unkcc) {
        ClearSongPreview();
        mSongPreviewTimer.Start();
    }
}

void MusicLibrary::CheckSongPreview() {
    if (mSongPreviewTimer.Running()
        && mSongPreviewTimer.SplitMs() > mSongPreviewDelay * 1000.0f) {
        SortNode *node = TheMusicLibrary->GetHighlightedNode();
        if (node->GetType() == kNodeSubheader) {
            SubheaderSortNode *ssn = dynamic_cast<SubheaderSortNode *>(node);
            MILO_ASSERT(ssn, 0x2BE);
            node = ssn->GetFirstChildSong();
            MILO_ASSERT(node, 0x2C0);
        }
        mSongPreviewTimer.Stop();
        unkcc = node->GetToken();
        if (node->GetType() == kNodeSong) {
            SongSortNode *sort = dynamic_cast<SongSortNode *>(node);
            if (sort) {
                LocalBandMachine *machine =
                    TheSessionMgr->GetMachineMgr()->GetLocalMachine();
                const char *song = sort->GetTitle();
                machine->SetCurrentSongPreview(song);
            }
            Symbol token = node->GetToken();
            if (TheSongMgr.HasSong(token, true)
                && !TheSongMgr.IsRestricted(TheSongMgr.GetSongIDFromShortName(token, true)
                )) {
                mSongPreview.Start(token);
            }
        }
    }
}

void MusicLibrary::ContentStarted() { ClearSongPreview(); }
void MusicLibrary::ContentMounted(const char *, const char *) {}

void MusicLibrary::ContentDone() {
    mViewSettingsProvider->BuildFilters(PartForFilter());
    TheSongSortMgr->BuildFilteredSongList(&mTask.filter, PartForFilter());
    TheSongSortMgr->BuildSortTree(unkdc);
    TheSongSortMgr->BuildSortList(unkdc);
    TryToSetHighlight(unkd4, kNodeNone, true);
    PushSetlistToScreen();
    PushSonglistToScreen();
    PushHighlightToScreen(true);
    PushFilterToScreen();
}

void MusicLibrary::SelectHighlightedNode(LocalBandUser *user) {
    SelectNode(GetHighlightedNode(), user, false);
}

void MusicLibrary::PlaySetlist(bool b1) {
    if (ContentDir()) {
        MakeSureSetlistIsValid();
        if (!mSetlist.empty()) {
            SetSyncDirty(-1, true);
            if (b1 && GetMakingSetlist(false) && TheSessionMgr->IsLocal()
                && TheGameMode->Property(setlists_can_be_saved, true)->Int()
                && TheProfileMgr.GetPrimaryProfile()) {
                PushSetlistSaveDialog();
            } else if (TheSessionMgr->GetMachineMgr()->AllMachinesHaveSameNetUIState()) {
                SendSetlistToMetaPerformer();
                UIPanel *panel =
                    ObjectDir::Main()->Find<UIPanel>("song_select_panel", true);
                panel->HandleType(move_on_quickplay_msg);
            } else {
                TheUIEventMgr->TriggerEvent("remote_not_ready", nullptr);
            }
        }
    }
}

void MusicLibrary::PlaySetlist(SavedSetlist *setlist) {
    int numSongs = 0;
    FOREACH (it, setlist->mSongs) {
        if (TheSongMgr.HasSong(*it) && TheSongMgr.IsRestricted(*it)) {
            numSongs++;
        }
    }
    if (numSongs != 0) {
        TheUI.PushScreen(
            ObjectDir::Main()->Find<UIScreen>("setlist_content_restricted_screen", true)
        );
    } else {
        numSongs = 0;
        FOREACH (it, setlist->mSongs) {
            if (!TheSongMgr.HasSong(*it) || TheSongMgr.IsDemo(*it)
                || !TheSessionMgr->GetMachineMgr()->IsSongShared(*it)) {
                numSongs++;
            }
        }
        if (numSongs != 0)
            PushMissingSetlistSongsToScreen(numSongs);
        else if (TheSessionMgr->GetMachineMgr()->AllMachinesHaveSameNetUIState()) {
            if (setlist->IsBattle()) {
                BattleSavedSetlist *bss = dynamic_cast<BattleSavedSetlist *>(setlist);
                MILO_ASSERT(bss, 0x38F);
                MetaPerformer::Current()->SetBattle(bss);
            } else {
                MetaPerformer::Current()->SetSetlist(setlist);
            }
            UIPanel *panel = ObjectDir::Main()->Find<UIPanel>("song_select_panel", true);
            static Message msg("move_on_quickplay");
            panel->HandleType(msg);
        } else {
            TheUIEventMgr->TriggerEvent("remote_not_ready", nullptr);
        }
    }
}

void MusicLibrary::SkipToShortcut(int idx) {
    SetHighlightIx(GetCurrentSort()->FirstActiveIxForShortcut(idx), true);
}

void MusicLibrary::ClientSetPartyShuffleMode() {
    if (!IsLeaderLocal()) {
        TheGameMode->SetMode(qp_party_shuffle);
    }
}

FORCE_LOCAL_INLINE
SortNode *MusicLibrary::GetHighlightedNode() const {
    return GetCurrentSort()->GetNode(unkd0);
}
END_FORCE_LOCAL_INLINE

FORCE_LOCAL_INLINE
NodeSort *MusicLibrary::GetCurrentSort() const { return TheSongSortMgr->GetSort(unkdc); }
END_FORCE_LOCAL_INLINE

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

FORCE_LOCAL_INLINE
bool MusicLibrary::GetMakingSetlist(bool b1) const {
    return unk12d && (b1 || !SongSortMgr::IsSetlistSort(unkdc));
}
END_FORCE_LOCAL_INLINE