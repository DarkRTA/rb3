#include "meta_band/MusicLibrary.h"
#include "BandProfile.h"
#include "MusicLibrary.h"
#include "MusicLibraryNetSetlists.h"
#include "SavedSetlist.h"
#include "SongSetlistProvider.h"
#include "SongSortMgr.h"
#include "SongSortNode.h"
#include "ViewSetting.h"
#include "bandobj/ReviewDisplay.h"
#include "bandobj/StarDisplay.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/GameMode.h"
#include "game/NetGameMsgs.h"
#include "meta/Profile.h"
#include "meta/SongPreview.h"
#include "meta_band/AppLabel.h"
#include "meta_band/BandMachine.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/HeaderPerformanceProvider.h"
#include "meta_band/MetaNetMsgs.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SaveLoadManager.h"
#include "meta_band/SavedSetlist.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/SetlistSortByLocation.h"
#include "meta_band/SongRecord.h"
#include "meta_band/SongSort.h"
#include "meta_band/SongSortMgr.h"
#include "meta_band/SongSortNode.h"
#include "meta_band/SongStatusMgr.h"
#include "meta_band/UIEventMgr.h"
#include "meta_band/Utl.h"
#include "net/NetSession.h"
#include "net/Server.h"
#include "net/Synchronize.h"
#include "net/WiiFriendMgr.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/DataPointMgr.h"
#include "utl/Messages2.h"
#include "utl/Messages3.h"
#include "utl/Messages4.h"
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
      mSongPreviewDelay(0), mLastSongPreview(gNullStr), mCurrentHighlightIndex(0),
      unkd4(gNullStr), unkd8(kNodeNone), unkdc(kSongSortBySong), unke0(kSongSortBySong),
      unke4(kSetlistSortByLocation), unke8(kNumSongSortTypes), unkec(0), mHeaderMat(0),
      mSubheaderMat(0), mFunctionMat(0), mFunctionSetlistMat(0), mRockCentralMat(0),
      mDiscMatEven(0), mDiscMatOdd(0), mDlcMatEven(0), mDlcMatOdd(0), mStoreMatEven(0),
      mStoreMatOdd(0), mUgcMatEven(0), mUgcMatOdd(0), mSetlistMatEven(0),
      mSetlistMatOdd(0), unk12c(0), unk12d(0), mSetlistProvider(new SetlistProvider()),
      unk13c(0), mNetSetlists(new MusicLibraryNetSetlists()), unk15c(0),
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
            mCurrentHighlightIndex = 0;
        }
        unkec = false;
    }
    if (TheGameMode->InMode(practice)) {
        mTask.setlistMode = kSetlistForbidden;
    }
    if (TheGameMode->InMode(qp_coop) && !TheSessionMgr->IsLocal()) {
        mTask.setlistMode = kSetlistForced;
    }
    NodeSort *sort = TheSongSortMgr->GetSort(unkdc);
    if (!sort->IsReady()) {
        unke0 = kSongSortByDiff;
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
    setlistMode = kSetlistOptional;
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

FORCE_LOCAL_INLINE
int MusicLibrary::GetMaxSetlistSize() { return mTask.maxSetlistSize; }
END_FORCE_LOCAL_INLINE

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
    mTask.setlistMode = kSetlistForbidden;
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
    mLastSongPreview = gNullStr;
    mSongPreviewTimer.Reset();
    mSongPreview.Start(gNullStr);
}

void MusicLibrary::StartSongPreview() {
    if (TheMusicLibrary->GetHighlightedNode()->GetToken() != mLastSongPreview) {
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
        mLastSongPreview = node->GetToken();
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

void MusicLibrary::SelectNode(SortNode *node, LocalBandUser *user, bool b3) {
    switch (node->GetType()) {
    case kNodeFunction:
        if (node->GetToken() == shuffle_setlist) {
            ShuffleSetlist();
            unk12c = true;
        } else if (node->GetToken() == make_a_setlist) {
            ClearSetlist();
            SetMakingSetlist(true);
            SetSort(unke0);
        } else if (node->GetToken() == view_setlists) {
            SetSort(unke4);
        } else if (node->GetToken() == view_songs) {
            SetSort(unke0);
        } else if (node->GetToken() == party_setlist) {
            if (IsLeaderLocal()) {
                BuildPartySetlist();
                if (!mSetlist.empty()) {
                    TheGameMode->SetMode(qp_party_shuffle);
                    if (TheNetSession) {
                        SetPartyShuffleModeMsg msg;
                        TheNetSession->SendMsgToAll(msg, kReliable);
                    }
                }
                PlaySetlist(true);
            } else if (!b3) {
                TheUI.PushScreen(ObjectDir::Main()->Find<UIScreen>(
                    "leader_party_shuffle_warning_screen", true
                ));
            }
        } else if (node->GetToken() == play_setlist) {
            if (GetMaxSetlistSize() == 0 || GetMaxSetlistSize() == SetlistSize()) {
                PlaySetlist(true);
            }
        } else if (node->GetToken() == random_song) {
            std::vector<Symbol> symvec;
            FOREACH (it, mSetlist) {
                symvec.push_back(TheSongMgr.GetShortNameFromSongID(*it, true));
            }
            std::vector<Symbol> s30;
            if (TheSongSortMgr->GetRandomSongs(
                    1, &s30, nullptr, &symvec, nullptr, true, true
                )) {
                SelectNode(GetCurrentSort()->GetNode(s30.front()), user, false);
                SetSyncDirty(-1, true);
            } else if (!b3) {
                TheUI.PushScreen(
                    ObjectDir::Main()->Find<UIScreen>("no_valid_songs_screen", true)
                );
            }
        }
        break;
    case kNodeHeader:
    case kNodeSubheader:
        if (SetlistIsFull()) {
            if (!b3) {
                TryToSetHighlight(play_setlist, kNodeFunction, false);
                TheUI.PushScreen(
                    ObjectDir::Main()->Find<UIScreen>("full_setlist_screen", true)
                );
            }
        } else if (CanHeadersBeSelected() && node->LocalizeToken()) {
            bool makeSetlist = GetMakingSetlist(false);
            if (makeSetlist) {
                SetMakingSetlist(true);
            }
            FOREACH (it, node->mChildren) {
                SelectNode(*it, user, true);
            }
            if (makeSetlist) {
                if (mSetlist.size() != 0) {
                    PushSetlistToScreen();
                    PlaySetlist(false);
                } else {
                    SetMakingSetlist(false);
                }
            } else if (SetlistIsFull()) {
                TryToSetHighlight(play_setlist, kNodeFunction, false);
            }
        }
        break;
    case kNodeSong:
        OwnedSongSortNode *songNode = dynamic_cast<OwnedSongSortNode *>(node);
        MILO_ASSERT(songNode, 0x456);
        int songID = songNode->GetSongRecord()->Data()->ID();
        if (SetlistIsFull()) {
            if (!b3) {
                TryToSetHighlight(play_setlist, kNodeFunction, false);
                TheUI.PushScreen(
                    ObjectDir::Main()->Find<UIScreen>("full_setlist_screen", true)
                );
            }
        } else if (songNode->GetSongRecord()->GetRestricted() && !b3) {
            // "parental_control_panel"
        }
        break;
    case kNodeSetlist:
        break;
    default:
        break;
    }
}

DECOMP_FORCEACTIVE(
    MusicLibrary,
    "parental_control_panel",
    "parental_control_screen",
    "setlistNode",
    "leader_setlist_warning_screen",
    "data",
    "invalid_version_screen",
    "demos_allowed",
    "demo_mode_screen",
    "demo_online_screen",
    "demo_setlist_screen",
    "content_restricted_screen",
    "invalid_selection_screen"
)

bool MusicLibrary::IsIxActive(int ix) {
    MILO_ASSERT(ix >= 0 && ix < GetCurrentSort()->GetDataCount(), 0x551);
    return GetCurrentSort()->GetNode(ix)->IsActive();
}

FORCE_LOCAL_INLINE
bool MusicLibrary::CanHeadersBeSelected() {
    return mTask.setlistMode == 0 && !SongSortMgr::IsSetlistSort(unkdc);
}
END_FORCE_LOCAL_INLINE

void MusicLibrary::SetSavedSetlistHighlight(SavedSetlist *setlist) {
    unkd4 = setlist->GetIdentifyingToken();
    unkd8 = kNodeSetlist;
}

FORCE_LOCAL_INLINE
SortNode *MusicLibrary::GetHighlightedNode() const {
    return GetCurrentSort()->GetNode(mCurrentHighlightIndex);
}
END_FORCE_LOCAL_INLINE

FORCE_LOCAL_INLINE
NodeSort *MusicLibrary::GetCurrentSort() const { return TheSongSortMgr->GetSort(unkdc); }
END_FORCE_LOCAL_INLINE

void MusicLibrary::SetSort(SongSortType ty) {
    if (ty != unkdc) {
        if (unke8 != kNumSongSortTypes) {
            TheSongSortMgr->GetSort(unke8)->CancelMakeReady();
            unke8 = kNumSongSortTypes;
        }
        if (!TheSongSortMgr->GetSort(ty)->IsReady()) {
            unke8 = ty;
            TheSongSortMgr->GetSort(ty)->MakeReady();
        } else {
            if (SongSortMgr::IsSetlistSort(ty)) {
                unke4 = ty;
            } else
                unke0 = ty;
            TheSongSortMgr->BuildSortTree(ty);
            TheSongSortMgr->BuildSortList(ty);
            unkdc = ty;
            TryToSetHighlight(unkd4, unkd8, true);
            PushHighlightToScreen(true);
        }
        PushSortToScreen();
    }
    if (SongSortMgr::IsSetlistSort(unkdc) && !unk15c) {
        RefreshNetSetlists();
    }
}

void MusicLibrary::ReSort(SongSortType ty) {
    if (ty == unkdc) {
        TheSongSortMgr->BuildSortTree(ty);
        TheSongSortMgr->BuildSortList(ty);
        TryToSetHighlight(unkd4, unkd8, true);
        PushHighlightToScreen(true);
    }
}

void MusicLibrary::ReSort(Symbol s) {
    SongSortType theType = kNumSongSortTypes;
    for (int i = 0; i < 9; i++) {
        if (s == TheSongSortMgr->GetSort((SongSortType)i)->GetName()) {
            theType = (SongSortType)i;
        } else
            break;
    }
    if (theType == kNumSongSortTypes) {
        MILO_WARN(
            "Failed to find a sort for the symbol %s, refreshing current sort instead\n",
            s
        );
        theType = unkdc;
    }
    ReSort(theType);
}

void MusicLibrary::RebuildAndSortSetlists() {
    TheSongSortMgr->BuildSetlistList();
    for (int i = 0; i < 9; i++) {
        if (SongSortMgr::IsSetlistSort((SongSortType)i)) {
            TheSongSortMgr->BuildSortTree((SongSortType)i);
            TheSongSortMgr->BuildSortList((SongSortType)i);
        }
    }
    if (SongSortMgr::IsSetlistSort(unkdc)) {
        TryToSetHighlight(unkd4, unkd8, true);
        PushSonglistToScreen();
        PushHighlightToScreen(true);
    }
}

SongSortType MusicLibrary::GetCurrentSortType(bool b1) {
    if (b1 && unke8 != kNumSongSortTypes)
        return unke8;
    else
        return unkdc;
}

Symbol MusicLibrary::GetCurrentSortName(bool b1) {
    return TheSongSortMgr->GetSort(GetCurrentSortType(b1))->GetName();
}

void MusicLibrary::SwitchOffRankedSort() {
    if (unkdc == kSongSortByRank) {
        SetSort(kSongSortBySong);
        TheSongSortMgr->GetSort(kSongSortByRank)->CancelMakeReady();
    } else if (unke8 == kSongSortByRank) {
        TheSongSortMgr->GetSort(kSongSortByRank)->CancelMakeReady();
        unke8 = kNumSongSortTypes;
    } else if (TheSongSortMgr->GetSort(kSongSortByRank)->IsReady()) {
        TheSongSortMgr->GetSort(kSongSortByRank)->CancelMakeReady();
    }
}

DataNode MusicLibrary::OnGetSortList(DataArray *a) {
    DataArrayPtr ptr;
    int idx = 0;
    ptr->Resize(9);
    for (int i = 0; i < 9; i++) {
        if (TheSongSortMgr->IsValidNextSortTransition((SongSortType)i, unkdc)) {
            ptr->Node(idx) = TheSongSortMgr->GetSort((SongSortType)i)->GetName();
            idx++;
        }
    }
    ptr->Resize(idx);
    return ptr;
}

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

void MusicLibrary::Text(int, int idx, UIListLabel *slot, UILabel *label) const {
    AppLabel *p9_label = dynamic_cast<AppLabel *>(label);
    MILO_ASSERT(p9_label, 0x638);
    SortNode *sortNode = GetCurrentSort()->GetNode(idx);
    switch (sortNode->GetType()) {
    case kNodeHeader:
        HeaderSortNode *hsn = dynamic_cast<HeaderSortNode *>(sortNode);
        if (hsn->mCover) {
            if (slot->Matches("famousby")) {
                label->SetTextToken(store_famous_by);
            } else if (slot->Matches("famousby_group")) {
                p9_label->SetFromSongSelectNode(sortNode);
            }
        } else if (slot->Matches("group") && unkdc != 3 && unkdc != 7) {
            p9_label->SetFromSongSelectNode(sortNode);
        } else if (slot->Matches("song_count") && !SongSortMgr::IsSetlistSort(unkdc)) {
            p9_label->SetSongCount(hsn->GetSongCount());
        }
        break;
    case kNodeSubheader:
        SubheaderSortNode *subheaderNode = dynamic_cast<SubheaderSortNode *>(sortNode);
        if (slot->Matches("song_count") && !SongSortMgr::IsSetlistSort(unkdc)) {
            p9_label->SetSongCount(subheaderNode->GetSongCount());
        } else if (slot->Matches("subgroup")) {
            MILO_ASSERT(!subheaderNode->mCover, 0x671);
            p9_label->SetFromSongSelectNode(sortNode);
        }
        break;
    case kNodeSong:
        OwnedSongSortNode *osn = dynamic_cast<OwnedSongSortNode *>(sortNode);
        if (slot->Matches("song")) {
            if (unkdc != 1) {
                p9_label->SetSongAndArtistName(osn);
            } else
                p9_label->SetSongName(osn);
        } else if (slot->Matches("difficulty")) {
            SongRecord *record = osn->GetSongRecord();
            if (record->IsNotBand() && record->GetScore() > 0) {
                label->SetTextToken(record->GetShortDifficultySym());
            }
        } else if (slot->Matches("percentage")) {
            SongRecord *record = osn->GetSongRecord();
            if (record->IsNotBand() && record->GetScore() > 0) {
                label->SetTokenFmt(endgame_player_noteshit_fmt, record->GetNotesPct());
            }
        }
        break;
    case kNodeFunction:
        if (slot->Matches("function")) {
            p9_label->SetFromSongSelectNode(sortNode);
        }
        break;
    case kNodeSetlist:
        SetlistSortNode *ssn = dynamic_cast<SetlistSortNode *>(sortNode);
        SavedSetlist *setlist = ssn->GetSetlistRecord()->GetSetlist();
        if (slot->Matches("setlist_name")) {
            p9_label->SetSetlistName(setlist);
        } else if (slot->Matches("battle_instrument_rank") && setlist->IsBattle()) {
            p9_label->SetBattleInstrument(ssn->GetSetlistRecord());
        }
        break;
    default:
        label->SetTextToken(gNullStr);
        break;
    }
}

RndMat *MusicLibrary::Mat(int, int idx, UIListMesh *slot) const {
    SortNode *node = GetCurrentSort()->GetNode(idx);
    switch (node->GetType()) {
    case kNodeFunction:
        if (slot->Matches("bg")) {
            if (node->GetToken() == view_setlists) {
                return mFunctionSetlistMat;
            }
            if (node->GetToken() == net_setlists_connect
                || node->GetToken() == net_setlists_error
                || node->GetToken() == net_setlists_getting) {
                return mRockCentralMat;
            } else
                return mFunctionMat;
        }
        break;
    case kNodeHeader:
        if (slot->Matches("bg"))
            return mHeaderMat;
        break;
    case kNodeSubheader:
        if (slot->Matches("bg"))
            return mSubheaderMat;
        break;
    case kNodeSong:
        OwnedSongSortNode *ossn = dynamic_cast<OwnedSongSortNode *>(node);
        MILO_ASSERT(ossn, 0x6FA);
        SongRecord *record = ossn->GetSongRecord();
        if (slot->Matches("bg")) {
            if (record->Data()->IsUGC()) {
                if (idx & 1U) {
                    return mUgcMatOdd;
                } else
                    return mUgcMatEven;
            } else if (record->Data()->IsDownload()) {
                if (idx & 1U) {
                    return mDlcMatOdd;
                } else
                    return mDlcMatEven;
            } else {
                if (idx & 1U) {
                    return mDiscMatOdd;
                } else
                    return mDiscMatEven;
            }
        }

        if (slot->Matches("difficulty_bg")) {
            if (record->IsNotBand() && record->GetScore() > 0) {
                return slot->DefaultMat();
            }
        }
        break;
    case kNodeSetlist:
        if (slot->Matches("bg")) {
            if (idx & 1U) {
                return mSetlistMatOdd;
            } else
                return mSetlistMatEven;
        }
        break;
    default:
        break;
    }
    return nullptr;
}

void MusicLibrary::Custom(int, int idx, UIListCustom *slot, Hmx::Object *obj) const {
    StarDisplay *sdisp = dynamic_cast<StarDisplay *>(obj);
    ReviewDisplay *rdisp = dynamic_cast<ReviewDisplay *>(obj);
    SortNode *sort = GetCurrentSort()->GetNode(idx);
    if (slot->Matches("stars") && sort->GetType() == kNodeSong) {
        OwnedSongSortNode *ossn = dynamic_cast<OwnedSongSortNode *>(sort);
        int numStars = sort->GetTotalStars(true);
        if (numStars > 0 && ossn) {
            if (!ossn->GetSongRecord()->IsDemo()) {
                sdisp->SetValues(numStars, 5);
                sdisp->SetProperty(force_mixed_mode, 0);
                sdisp->SetShowing(true);
                return;
            }
        }
    } else if (slot->Matches("stars_head")) {
        switch (sort->GetType()) {
        case kNodeHeader:
        case kNodeSubheader:
            if (unkdc != 8
                || sort->GetToken()
                    != LocationCmp::SetlistHeaderTypeToSym((LocationCmp::SetlistHeaderType
                    )0)) {
                sdisp->SetValues(sort->GetTotalStars(false), sort->GetPotentialStars());
                sdisp->SetProperty(force_mixed_mode, 1);
                sdisp->SetShowing(true);
                return;
            }
            break;
        case kNodeSetlist:
            SetlistSortNode *ssn = dynamic_cast<SetlistSortNode *>(sort);
            MILO_ASSERT(ssn, 0x74A);
            if (!ssn->GetSetlistRecord()->GetSetlist()->IsBattle()) {
                sdisp->SetValues(sort->GetTotalStars(false), sort->GetPotentialStars());
                sdisp->SetProperty(force_mixed_mode, 1);
                sdisp->SetShowing(true);
                return;
            }
            break;
        default:
            break;
        }
    } else if (slot->Matches("stars_title") && sort->GetType() == 2 && unkdc == 3) {
        HeaderSortNode *hsn = dynamic_cast<HeaderSortNode *>(sort);
        sdisp->SetToToken(hsn->GetToken());
        sdisp->SetShowing(true);
        return;
    } else if (slot->Matches("review_title") && sort->GetType() == 2 && unkdc == 7) {
        HeaderSortNode *hsn = dynamic_cast<HeaderSortNode *>(sort);
        rdisp->SetToToken(hsn->GetToken());
        rdisp->SetShowing(true);
        return;
    }

    if (sdisp)
        sdisp->SetShowing(false);
    if (rdisp)
        rdisp->SetShowing(false);
}

int MusicLibrary::NumData() const { return GetCurrentSort()->GetDataCount(); }

bool MusicLibrary::IsActive(int idx) const {
    return GetCurrentSort()->GetNode(idx)->IsActive();
}

UIComponent::State
MusicLibrary::ComponentStateOverride(int, int idx, UIComponent::State state) const {
    if (GetCurrentSort()->GetNode(idx)->IsEnabled()) {
        return state;
    } else
        return UIComponent::kDisabled;
}

int MusicLibrary::SnappableAtOrBeforeData(int idx) const {
    for (; idx >= 0; idx--) {
        if (IsSnappableAtData(idx))
            break;
    }
    return idx;
}

bool MusicLibrary::IsSnappableAtData(int idx) const {
    return GetCurrentSort()->GetNode(idx)->GetType() == 2;
}

Symbol MusicLibrary::DifficultySortPart() const {
    switch (ActiveScoreType()) {
    case kScoreBand:
        return band;
    case kScoreGuitar:
        return guitar;
    case kScoreBass:
        return bass;
    case kScoreDrum:
    case kScoreRealDrum:
        return drum;
    case kScoreVocals:
    case kScoreHarmony:
        return vocals;
    case kScoreKeys:
        return keys;
    case kScoreRealGuitar:
        return real_guitar;
    case kScoreRealBass:
        return real_bass;
    case kScoreRealKeys:
        return real_keys;
    default:
        MILO_FAIL("Bad ScoreType in MusicLibrary::DifficultySortPart!");
        return gNullStr;
    }
}

ScoreType MusicLibrary::ActiveScoreType() const {
    std::vector<BandUser *> users;
    TheBandUserMgr->GetBandUsersInSession(users);
    BandUser *singleUser = nullptr;
    ScoreType sty;
    if (users.size() != 1)
        sty = kScoreBand;
    else {
        singleUser = users.front();
        MILO_ASSERT(singleUser, 0x7D9);
        if (singleUser->GetTrackType() != 10) {
            sty = TrackTypeToScoreType(singleUser->GetTrackType(), false, false);
        } else {
            sty = TrackTypeToScoreType(
                ControllerTypeToTrackType(singleUser->GetControllerType(), false),
                false,
                false
            );
        }
    }

    if (sty == kScoreDrum) {
        MILO_ASSERT(singleUser, 0x7EB);
        if (singleUser->GetPreferredScoreType() == kScoreRealDrum)
            sty = kScoreRealDrum;
    } else if (sty == kScoreVocals) {
        MILO_ASSERT(singleUser, 0x7F2);
        if (singleUser->GetPreferredScoreType() == kScoreHarmony)
            sty = kScoreHarmony;
    }

    switch (sty) {
    case kScoreGuitar:
        if (mTask.scoreType == kScoreBass)
            sty = kScoreBass;
        break;
    case kScoreBass:
        if (mTask.scoreType == kScoreGuitar)
            sty = kScoreGuitar;
        break;
    case kScoreDrum:
        if (mTask.scoreType == kScoreRealDrum)
            sty = kScoreRealDrum;
        break;
    case kScoreRealDrum:
        if (mTask.scoreType == kScoreDrum)
            sty = kScoreDrum;
        break;
    case kScoreVocals:
        if (mTask.scoreType == kScoreHarmony)
            sty = kScoreHarmony;
        break;
    case kScoreHarmony:
        if (mTask.scoreType == kScoreVocals)
            sty = kScoreVocals;
        break;
    case kScoreKeys:
        if (mTask.scoreType == kScoreRealKeys)
            sty = kScoreRealKeys;
        break;
    case kScoreRealKeys:
        if (mTask.scoreType == kScoreKeys)
            sty = kScoreKeys;
        break;
    case kScoreRealGuitar:
        if (mTask.scoreType == kScoreRealBass)
            sty = kScoreRealBass;
        break;
    case kScoreRealBass:
        if (mTask.scoreType == kScoreRealGuitar)
            sty = kScoreRealGuitar;
        break;
    default:
        break;
    }
    return sty;
}

Symbol MusicLibrary::PartForFilter() const {
    if (mTask.partSym == gNullStr)
        return DifficultySortPart();
    else
        return mTask.partSym;
}

void MusicLibrary::SetlistArtFinished() {
    if (GetHighlightedNode()->GetType() == 6) {
        PushHighlightToScreen(false);
    }
}

void MusicLibrary::SendMessageToSongSelectPanel(Message &msg) {
    UIPanel *panel = ObjectDir::Main()->Find<UIPanel>("song_select_panel", true);
    if (panel->GetState() == UIPanel::kUp) {
        panel->HandleType(msg);
    }
}

void MusicLibrary::PushHighlightToScreen(bool b1) {
    if (b1) {
        static Message msg(highlight_node_at_ix, 0);
        msg[0] = mCurrentHighlightIndex;
        SendMessageToSongSelectPanel(msg);
    }
    SetlistSortNode *sort = dynamic_cast<SetlistSortNode *>(GetHighlightedNode());
    if (sort) {
        mSetlistScoresProvider->SetSetlist(sort->GetSetlistRecord()->GetSetlist());
    }
    if (!TheContentMgr->RefreshInProgress()) {
        SendMessageToSongSelectPanel(refresh_selected_song_msg);
    }
}

void MusicLibrary::PushMakingSetlistToScreen() {
    SendMessageToSongSelectPanel(on_change_setlist_mode_msg);
    PushSonglistToScreen();
    PushHighlightToScreen(true);
}

void MusicLibrary::PushFilterToScreen() {
    SendMessageToSongSelectPanel(refresh_filter_msg);
}

void MusicLibrary::PushSortToScreen() {
    static Message msg(refresh_sort, 0);
    msg[0] = unke8 != 9U;
    SendMessageToSongSelectPanel(msg);
}

void MusicLibrary::PushSetlistToScreen() {
    unk12c = false;
    TheSessionMgr->GetMachineMgr()->GetLocalMachine()->SetNetUIStateParam(-mSetlist.size()
    );
    if (!TheContentMgr->RefreshInProgress()) {
        SendMessageToSongSelectPanel(refresh_setlist_msg);
    }
}

void MusicLibrary::PushSonglistToScreen() {
    if (!TheContentMgr->RefreshInProgress()) {
        SendMessageToSongSelectPanel(refresh_songlist_msg);
    }
}

void MusicLibrary::PushSetlistSaveDialog() {
    SendMessageToSongSelectPanel(show_setlist_save_dialog_msg);
}

void MusicLibrary::PushHeaderDataToScreen() {
    SendMessageToSongSelectPanel(refresh_summary_msg);
}

void MusicLibrary::PushMissingSetlistSongsToScreen(int idx) {
    static Message msg(show_missing_setlist_songs_dialog, 0);
    msg[0] = idx;
    SendMessageToSongSelectPanel(msg);
}

void MusicLibrary::SetMakingSetlist(bool val) {
    MILO_ASSERT(!(val && mTask.setlistMode == kSetlistForbidden), 0x8B1);
    MILO_ASSERT(!(!val && mTask.setlistMode == kSetlistForced), 0x8B3);
    if (val != unk12d) {
        unk12d = val;
        TheSongSortMgr->BuildSortList(unkdc);
        TryToSetHighlight(unkd4, unkd8, true);
        PushMakingSetlistToScreen();
    }
}

FORCE_LOCAL_INLINE
bool MusicLibrary::GetMakingSetlist(bool b1) const {
    return unk12d && (b1 || !SongSortMgr::IsSetlistSort(unkdc));
}
END_FORCE_LOCAL_INLINE

void MusicLibrary::ClearSetlist() {
    mSetlist.clear();
    unk13c = 0;
    unk12c = true;
    SetSyncDirty(-1, false);
}

void MusicLibrary::AppendToSetlist(int i) {
    if (!SetlistIsFull()) {
        if (ContentDir()) {
            mSetlist.push_back(i);
            unk12c = true;
            SetSyncDirty(-1, false);
        } else {
            AppendSongToSetlistMsg msg(i);
            TheSessionMgr->SendMsg(TheSessionMgr->GetLeaderUser(), msg, kReliable);
        }
    }
}

void MusicLibrary::RemoveLastSongFromSetlist() {
    if (mSetlist.size()) {
        if (ContentDir()) {
            mSetlist.pop_back();
            unk12c = true;
            SetSyncDirty(-1, false);
        } else {
            RemoveLastSongFromSetlistMsg msg;
            TheSessionMgr->SendMsg(TheSessionMgr->GetLeaderUser(), msg, kReliable);
        }
    }
}

void MusicLibrary::ShuffleSetlist() {
    std::random_shuffle(mSetlist.begin(), mSetlist.end());
    SetSyncDirty(-1, false);
}

void MusicLibrary::BuildPartySetlist() {
    if (TheGameMode->InMode(party_shuffle)) {
        TheSongSortMgr->BuildFilteredSongList(nullptr, "band");
    }
    mSetlist.clear();
    TheSongSortMgr->GetRandomSongs(0, nullptr, &mSetlist, nullptr, nullptr, true, true);
    SetSyncDirty(-1, true);
}

void MusicLibrary::SendSetlistToMetaPerformer() {
    MetaPerformer::Current()->SetSongs(mSetlist);
}

std::vector<int> &MusicLibrary::GetSetlist() { return mSetlist; }

bool MusicLibrary::SetlistHasSong(int song) {
    return std::find(mSetlist.begin(), mSetlist.end(), song) != mSetlist.end();
}

int MusicLibrary::SongAtSetlistIndex(int idx) {
    if (idx >= mSetlist.size())
        return 0;
    else
        return mSetlist[idx];
}

FORCE_LOCAL_INLINE
int MusicLibrary::SetlistSize() { return mSetlist.size(); }
END_FORCE_LOCAL_INLINE

bool MusicLibrary::SetlistIsFull() {
    if (mTask.setlistMode == kSetlistForced && mTask.maxSetlistSize != 0) {
        return mTask.maxSetlistSize <= SetlistSize();
    } else
        return SetlistSize() >= 100;
}

bool MusicLibrary::AllSetlistSongsHaveScoreType(ScoreType s) {
    switch (s) {
    case kScoreDrum:
    case kScoreBass:
    case kScoreGuitar:
    case kScoreVocals:
    case kScoreKeys:
    case kScoreRealDrum:
    case kScoreRealGuitar:
    case kScoreRealBass:
    case kScoreRealKeys:
        TrackType t = ScoreTypeToTrackType(s);
        FOREACH (it, mSetlist) {
            BandSongMetadata *data = (BandSongMetadata *)TheSongMgr.Data(*it);
            if (!data || !data->HasPart(TrackTypeToSym(t), false))
                return false;
        }
        break;
    case kScoreHarmony:
        FOREACH (it, mSetlist) {
            BandSongMetadata *data = (BandSongMetadata *)TheSongMgr.Data(*it);
            if (!data || !data->HasVocalHarmony())
                return false;
        }
        break;
    case kScoreBand:
        break;
    default:
        MILO_FAIL("Bad ScoreType %i in AllSetlistSongsHaveScoreType!", (int)s);
    }
    return true;
}

bool MusicLibrary::NetSetlistsFailed() {}
bool MusicLibrary::NetSetlistsSucceeded() {}

void MusicLibrary::RefreshNetSetlists() {
    if (unk15c) {
        mNetSetlists->CleanUp();
    }
    unk15c = true;
    mNetSetlists->RefreshSetlists();
    RebuildAndSortSetlists();
}

bool MusicLibrary::FilterSetlist(WiiFriendList *friends, NetSavedSetlist *setlist) const {
    switch (setlist->GetType()) {
    case SavedSetlist::kSetlistLocal:
    case SavedSetlist::kSetlistInternal:
        MILO_ASSERT(0 && "Net setlist contains unusual setlist type", 0x97D);
        return true;
    // case SavedSetlist::kSetlistHarmonix:
    case SavedSetlist::kBattleHarmonix:
    case SavedSetlist::kBattleFriend:
    case SavedSetlist::kBattleFriendArchived:
        if (ThePlatformMgr.IsOnlineRestricted())
            return false;
        const char *owner = setlist->GetOwner();
        const char *name = Localize(wii_friends_default_setlist_name, nullptr);
        const char *desc = Localize(wii_friends_default_setlist_description, nullptr);
        break;
    default:
        return true;
    }
}

DECOMP_FORCEACTIVE(
    MusicLibrary,
    "pSetlist->GetArtTex() == NULL && \"NetSaveSestlist has texture?  Tell Ian S.\""
)

void MusicLibrary::GetNetSetlists(std::vector<NetSavedSetlist *> &setlists) const {
    WiiFriendList friends;
    TheWiiFriendMgr.GetCachedFriends(&friends);
    setlists.clear();
}

void MusicLibrary::DeleteHighlightedSetlist() {
    SetlistSortNode *setlistNode = dynamic_cast<SetlistSortNode *>(GetHighlightedNode());
    MILO_ASSERT(setlistNode, 0xA11);
    MILO_ASSERT(setlistNode->GetSetlistRecord()->IsLocal(), 0xA12);
    LocalSavedSetlist *lss =
        dynamic_cast<LocalSavedSetlist *>(setlistNode->GetSetlistRecord()->GetSetlist());
    MILO_ASSERT(lss, 0xA17);
    lss->mOwnerProfile->DeleteSavedSetlist(lss);
    std::vector<BandProfile *> profiles = TheProfileMgr.GetSignedInProfiles();
    TheRockCentral.SyncSetlists(profiles, mResults, this);
    TheSaveLoadMgr->AutoSave();
    RebuildAndSortSetlists();
}

void MusicLibrary::UpdateHeaderData() {
    mHasHeaderData = false;
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    if (profile) {
        SongStatusMgr *mgr = profile->GetSongStatusMgr();
        ScoreType s = ActiveScoreType();
        mHasHeaderData = true;
        mHeaderCareerScore = mgr->CalculateTotalScore(s, gNullStr);
        mHeaderCareerInstrumentMask = 1 << s;
        mHeaderCareerStars = mgr->GetCachedTotalStars(s);
        mHeaderPossibleStars = mgr->GetPossibleStars(s, gNullStr);
    }
    PushHeaderDataToScreen();
}