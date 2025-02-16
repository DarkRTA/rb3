#include "game/Game.h"
#include "Game.h"
#include "bandobj/BandDirector.h"
#include "bandobj/CrowdAudio.h"
#include "bandtrack/TrackPanel.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/PlayerTrackConfig.h"
#include "beatmatch/SongData.h"
#include "beatmatch/TrackType.h"
#include "decomp.h"
#include "game/Band.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/FadePanel.h"
#include "game/GameConfig.h"
#include "game/GameMode.h"
#include "game/GamePanel.h"
#include "game/GemPlayer.h"
#include "game/NetGameMsgs.h"
#include "game/Player.h"
#include "game/Scoring.h"
#include "game/Shuttle.h"
#include "game/SongDB.h"
#include "game/TrackerManager.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/BandUI.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ModifierMgr.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/OvershellPanel.h"
#include "midi/MidiParser.h"
#include "midi/MidiParserMgr.h"
#include "net/NetMessage.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "rndobj/Rnd.h"
#include "synth/Synth.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/MBT.h"
#include "utl/Messages.h"
#include "utl/SongInfoCopy.h"
#include "utl/SongPos.h"
#include "utl/Symbols.h"
#include "utl/TempoMap.h"
#include "utl/TimeConversion.h"

Game *TheGame;
bool gDebugFullQuota;
bool gKickAutoplay;

NetMessage *PlayerGameplayMsg::NewNetMessage() { return new PlayerGameplayMsg(); }
NetMessage *RestartGameMsg::NewNetMessage() { return new RestartGameMsg(); }
NetMessage *ResumeNoScoreGameMsg::NewNetMessage() { return new ResumeNoScoreGameMsg(); }
NetMessage *PlayerStatsMsg::NewNetMessage() { return new PlayerStatsMsg(); }
NetMessage *SetUserTrackTypeMsg::NewNetMessage() { return new SetUserTrackTypeMsg(); }
NetMessage *SetUserDifficultyMsg::NewNetMessage() { return new SetUserDifficultyMsg(); }
NetMessage *SetlistSubmissionMsg::NewNetMessage() { return new SetlistSubmissionMsg(); }
NetMessage *TourMostStarsMsg::NewNetMessage() { return new TourMostStarsMsg(); }
NetMessage *TourPlayedMsg::NewNetMessage() { return new TourPlayedMsg(); }
NetMessage *AccomplishmentMsg::NewNetMessage() { return new AccomplishmentMsg(); }
NetMessage *AccomplishmentEarnedMsg::NewNetMessage() {
    return new AccomplishmentEarnedMsg();
}
NetMessage *SetPartyShuffleModeMsg::NewNetMessage() {
    return new SetPartyShuffleModeMsg();
}
NetMessage *TourHideShowFiltersMsg::NewNetMessage() {
    return new TourHideShowFiltersMsg();
}
NetMessage *SongResultsScrollMsg::NewNetMessage() { return new SongResultsScrollMsg(); }
NetMessage *SetUpMicsMsg::NewNetMessage() { return new SetUpMicsMsg(); }

void GameInit() {
    FadePanel::Init();
    // GamePanel::Init();
    // SyncGameStartPanel::Init();
    // TrackPanel::Init();
    PlayerGameplayMsg::Register();
    RestartGameMsg::Register();
    ResumeNoScoreGameMsg::Register();
    PlayerStatsMsg::Register();
    SetUserTrackTypeMsg::Register();
    SetUserDifficultyMsg::Register();
    SetlistSubmissionMsg::Register();
    TourMostStarsMsg::Register();
    TourPlayedMsg::Register();
    AccomplishmentMsg::Register();
    AccomplishmentEarnedMsg::Register();
    SetPartyShuffleModeMsg::Register();
    // MusicLibraryTaskMsg::Register();
    SetUpMicsMsg::Register();
    TourHideShowFiltersMsg::Register();
    SongResultsScrollMsg::Register();
    // GemTrainerPanel::Init();
    // GemTrainerLoopPanel::Init();
    // RGTrainerPanel::Init();
    // RKTrainerPanel::Init();
    // PracticePanel::Init();
    // ChordbookPanel::Init();
    // TrainerChallenge::Init();
    // VocalTrainerPanel::Init();
    // FreestylePanel::Init();
    TheDebug.AddExitCallback(GameTerminate);
}

void GameTerminate() { TheSongMgr->Terminate(); }

Game::Game()
    : mSongDB(new SongDB()), mSongInfo(0), mIsPaused(0), mGameWantsPause(0),
      mOvershellWantsPause(0), unk6b(0), unk6c(0), mPauseTime(0), mRealtime(0), unk6f(0),
      mTimeOffset(0), mLastPollMs(0), mMuckWithPitch(0), mMusicSpeed(1.0f),
      mNeverAllowInput(0), unkb9(1), mDemoMaxPctComplete(0), mDemoMaxMs(0), unkc4(0),
      mLoadState(kLoadingSong), mResult(kRestart), mBand(0), mShuttle(new Shuttle()),
      unkdc(-1), unk11c(-1), unk120(0), mSkippedSong(0), unk124(0), mResumeTime(0),
      mInvalidScore(0), unk130(0), unk134(0), unk138(0), mDrumFillsMod(1), unk13c(-1),
      unk140(-1), mTrackerManager(0), unk148(0), mDisablePauseMs(-1), unk150(1) {
    MILO_ASSERT(!TheSongDB, 0xCE);
    TheSongDB = mSongDB;
    TheGame = this;
    SetName("beatmatch", ObjectDir::sMainDir);
    mMaster =
        new BeatMaster(mSongDB->GetSongData(), TheBandUserMgr->GetNumParticipants());
    mMaster->RegisterSink(*this);
    TheNetSession->AddSink(this, GameEndedMsg::Type());
    TheSessionMgr->AddSink(this, LocalUserLeftMsg::Type());
    TheSessionMgr->AddSink(this, RemoteUserLeftMsg::Type());
    TheSessionMgr->AddSink(this, RemoteLeaderLeftMsg::Type());
    TheBandUI.AddSink(this, "required_song_options_chosen");
    TheBandUI.AddSink(this, NewOvershellLocalUserMsg::Type());
    TheBandUI.AddSink(this, UIScreenChangeMsg::Type());

    SetBackgroundVolume(TheProfileMgr.GetBackgroundVolumeDb());
    SetForegroundVolume(TheProfileMgr.GetForegroundVolumeDb());
    SetStereo(true);
    TheGameConfig->AssignTracks();
    for (int i = 0; i != (uint)TheSynth->GetNumMics(); i++) {
        TheSynth->GetMic(i)->Stop();
        TheSynth->GetMic(i)->Start();
    }
    mBand = new Band(false, 0, BandUserMgr::GetBandUser(nullptr), mMaster);
    PopulatePlayerLists();
    mTrackerManager = new TrackerManager(mBand);
    mDemoMaxPctComplete = SystemConfig(demo)->FindInt(max_pct_complete);
    mDemoMaxMs = SystemConfig(demo)->FindFloat(max_ms);
    LoadSong();
    ThePlatformMgr.GetDiscErrorMgrWii()->RegisterCallback(this);
}

Game::~Game() {}

void Game::LoadSong() {
    gSongLoadTimer.Restart();
    Symbol songSym = MetaPerformer::Current()->Song();
    PlayerTrackConfigList *cfgList = TheGameConfig->GetConfigList();
    SongDataValidate i2 =
        TheSongMgr->Data(TheSongMgr->GetSongIDFromShortName(songSym, true))->IsOnDisc()
        ? kSongData_Validate
        : kSongData_NoValidation;
    Fader *fader = TheSynth->Find<Fader>("per_song_sfx_level.fade", false);
    if (fader)
        fader->SetVal(0);
    mMaster->GetAudio()->SetPracticeMode(TheGameMode->InMode("practice"));
    RELEASE(mSongInfo);
    mSongInfo = new SongInfoCopy(TheSongMgr->SongAudioData(songSym));
    mMaster->Load(mSongInfo, 4, cfgList, false, i2, nullptr);
}

bool Game::IsLoaded() {
    if (mLoadState == kReady)
        return true;
    else if (mMaster && mMaster->GetAudio()->GetSongStream()
             && mMaster->GetAudio()->Fail()) {
        return true;
    } else if (mMaster && !mMaster->IsLoaded()) {
        return false;
    } else {
        if (mLoadState == kLoadingSong) {
            if (!mMaster->IsLoaded())
                return false;
            TheSongDB->PostLoad(GetBeatMaster()->GetMidiParserMgr()->GetEventsList());
            PostLoad();
            mLoadState = kWaitingForAudio;
        }
        if (mLoadState == kWaitingForAudio) {
            if (mMaster->GetAudio()->Fail())
                return true;
            if (!mMaster->GetAudio()->IsReady()) {
                TheSynth->Poll();
                return false;
            }
            mLoadState = kReady;
            TheProfileMgr.PushAllOptions();
            mTrackerManager->ConfigureGoals();
        }
        return mLoadState == kReady;
    }
}

void Game::PostLoad() {
    int i24 = -1;
    std::vector<Player *> &players = GetActivePlayers();
    FOREACH (it, players) {
        (*it)->SetTrack(TheGameConfig->GetTrackNum((*it)->GetUserGuid()));
        (*it)->PostLoad(false);
        Extent ext(0, 0);
        if ((*it)->GetCodaFreestyleExtents(ext) != 0) {
            MaxEq(i24, ext.unk4);
        }
    }

    float ms;
    if (i24 != -1)
        ms = TickToMs(i24);
    else
        ms = mSongDB->GetSongDurationMs();

    FOREACH (it, players) {
        if ((*it)->NeedsToSetCodaEnd()) {
            (*it)->SetCodaEndMs(ms);
        }
    }
    if (DataVariable("print_base_points").Int()) {
        PrintBasePoints();
    }
    ResetVoiceChatState();
}

bool Game::IsReady() {
    if (!IsLoaded())
        return false;
    else {
        std::vector<Player *> &players = GetActivePlayers();
        FOREACH (it, players) {
            if (!(*it)->IsReady())
                return false;
        }
        return true;
    }
}

void Game::Start() {
    for (int i = 0; i < unk154.size(); i++) {
        AddPlayer(unk154[i]);
    }
    unk154.clear();
    mHasIntro = false;
    Go();
}

void Game::Go() {
    if (!mMaster->GetAudio()->Fail()) {
        if (unk150) {
            GetTrackPanelDir()->UpdateTrackSpeed();
            unk150 = false;
        }
        mMaster->GetAudio()->Play();
        std::vector<Player *> &players = GetActivePlayers();
        FOREACH (it, players) {
            (*it)->Start();
        }
        mIsPaused = false;
        unk148 = true;
        SetRealtime(false);
    }
}

void Game::StartIntro() {
    std::vector<Player *> &players = GetActivePlayers();
    FOREACH (it, players) {
        (*it)->StartIntro();
    }
    mTrackerManager->StartIntro();
}

void Game::Reset() {
    TheTaskMgr.SetAVOffset(GetSongToTaskMgrMs() / 1000.0f);
    TheTaskMgr.SetSeconds(0, true);
    mRealtime = false;
    mTimeOffset = 0;
    mPauseTime = 0;
    mSongPos = SongPos();
    mResult = kRestart;
    unk124 = 0;
    mTime.Restart();
    mHasIntro = false;
    unk11c = -1.0f;
    unkdc = -1.0f;
    unk120 = false;
    unk138 = false;
    unk6f = false;
    TheGamePanel->mDeJitter.Reset();
    if (DataVarExists("beatmatch_start_mbt")) {
        int m, b, t;
        ParseMBT(DataVariable("beatmatch_start_mbt").Str(), m, b, t);
        unk134 = TickToMs(
            TheSongDB->GetSongData()->GetMeasureMap()->MeasureBeatTickToTick(m, b, t)
        );
    }
}

bool Game::HasIntro() { return mHasIntro; }

float Game::GetSongToTaskMgrMs() {
    float f1 = 1;
    LagContext ctx = kGame;
    if (mProperties.mInPracticeMode || mProperties.mInTrainer)
        f1 = mMusicSpeed;
    if (0.85 < f1 && f1 <= 0.95) {
        ctx = kPractice90;
    } else if (0.75 < f1 && f1 <= 0.85) {
        ctx = kPractice80;
    } else if (0.65 < f1 && f1 <= 0.75) {
        ctx = kPractice70;
    } else if (0.55 < f1 && f1 <= 0.65) {
        ctx = kPractice60;
    }
    return TheProfileMgr.GetSongToTaskMgrMs(ctx);
}

float Game::GetSongMs() const { return mMaster->GetAudio()->GetTime(); }

Symbol Game::GetSectionAtMs(float ms) const { MILO_WARN("No practice sections!"); }

void Game::RemovePlayer(Player *p) {
    mAllActivePlayers.erase(
        std::find(mAllActivePlayers.begin(), mAllActivePlayers.end(), p),
        mAllActivePlayers.end()
    );
}

void Game::SetPaused(bool b1, bool b2, bool b3) {
    mGameWantsPause = b1;
    UpdatePausedState(b2, b3);
}

bool Game::CanUserPause() const {
    return !mProperties.mEndWithSong
        || mLastPollMs < TheSongDB->GetSongDurationMs() - mDisablePauseMs;
}

void Game::DiscErrorEnd() { unk6b = true; }

void Game::SetMusicSpeed(float speed) {
    gDebugFullQuota = speed != 1;
    mMusicSpeed = speed;
    FOREACH (it, mAllActivePlayers) {
        (*it)->SetMusicSpeed(speed);
    }
}

void Game::SetPitchMucker(bool b1) {
    mMuckWithPitch = true;
    mMaster->GetAudio()->SetMuckWithPitch(b1);
}

float Game::GetMusicSpeed() const { return mMusicSpeed; }

void Game::SetMusicVolume(float vol) {
    MILO_ASSERT(mMaster->GetAudio(), 0x446);
    mMaster->GetAudio()->SetMasterVolume(vol);
}

void Game::SetIntroRealTime(float f1) {
    TheTaskMgr.SetSeconds(f1, true);
    mHasIntro = f1 < 0;
    SetRealtime(true);
    unkd8 = f1 * 1000.0f;
}

Band *Game::GetBand() { return mBand; }

bool Game::IsActiveUser(BandUser *u) const {
    for (int i = 0; i < mAllActivePlayers.size(); i++) {
        if (mAllActivePlayers[i]->GetUser() == u)
            return true;
    }
    return false;
}

Player *Game::GetPlayerFromTrack(int i1, bool b2) const {
    for (int i = 0; i < mAllActivePlayers.size(); i++) {
        if (i1 == mAllActivePlayers[i]->GetTrackNum()) {
            return mAllActivePlayers[i];
        }
    }
    if (b2) {
        MILO_FAIL("There is no player with Track %i", i1);
    }
    return nullptr;
}

int Game::NumActivePlayers() const { return mAllActivePlayers.size(); }

int Game::GetScoringTracks() const {
    int tracks = 0;
    FOREACH (it, mAllActivePlayers) {
        if (!(*it)->GetQuarantined()) {
            tracks |= 1 << ((*it)->GetTrackNum());
        }
    }
    return tracks;
}

EndGameResult Game::GetResult(bool won) {
    if (won) {
        if (MetaPerformer::Current()->SongEndsWithEndgameSequence()) {
            return kWonFinale;
        } else
            return kWon;
    } else
        return kLost;
}

EndGameResult Game::GetResultForUser(BandUser *) {
    MILO_FAIL("Game::GetResultForUser shouldn't be called anymore");
    return kLost;
}

Player *Game::GetActivePlayer(int index) const {
    MILO_ASSERT_RANGE(index, 0, mAllActivePlayers.size(), 0x4B2);
    return mAllActivePlayers[index];
}

void Game::Jump(float f1, bool b2) {
    if (f1 < 0)
        f1 = 0;
    if (b2) {
        mMaster->Jump(f1);
        unk120 = true;
    }
    mBand->Restart(false);
    FOREACH (it, mAllActivePlayers) {
        (*it)->Jump(f1, b2);
    }
    unkd8 = f1;
    CheckRollbackEnd(unkdc);
}

void Game::Replay() { unk120 = true; }

DataNode Game::OnJump(const DataArray *a) {
    DataNode &node = a->Evaluate(2);
    DataType ty = node.Type();
    if (ty == kDataFloat || ty == kDataInt) {
        Jump(node.Float(), true);
    } else if (ty == kDataSymbol || ty == kDataString) {
        int m, b, t;
        ParseMBT(node.Str(), m, b, t);
        int tick =
            TheSongDB->GetSongData()->GetMeasureMap()->MeasureBeatTickToTick(m, b, t);
        Jump(TickToMs(tick), true);
    }
    return 1;
}

void Game::Rollback(float f1, float toMs) {
    MILO_ASSERT(toMs >= 0.0f, 0x4F1);
    GetTrackPanelDir()->UpdateTrackSpeed();
    EnableWorldPolling(false);
    mMaster->Jump(toMs);
    FOREACH (it, mAllActivePlayers) {
        (*it)->Rollback(f1, toMs);
    }
    unkdc = f1;
    unk11c = 0;
    mInterpolator.Reset(mLastPollMs / 1000.0f, toMs / 1000.0f, 0, 60.0f, 3.5f);
    unkd8 = toMs;
    unk120 = true;
    if (mProperties.mInPracticeMode) {
        ObjectDir::sMainDir->Find<MidiParser>("practice_metronome", true)
            ->Reset(MsToBeat(toMs));
    }
}

bool Game::HandleRollbackAnimation() {}

void Game::CheckRollbackEnd(float f1) {
    if (unkdc != -1.0f && f1 >= unkdc) {
        EnableWorldPolling(true);
        unkdc = -1.0f;
    }
}

void Game::EnableWorldPolling(bool b1) {
    if (TheBandDirector) {
        TheBandDirector->unke5 = b1;
    }
    UIPanel *panel = ObjectDir::sMainDir->Find<UIPanel>("world_panel", true);
}

void Game::ResetAudio() { mMaster->ResetAudio(); }

void Game::Restart(bool) {
    mDrumFillsMod = TheModifierMgr->IsModifierActive("mod_drum_fills");
}

FORCE_LOCAL_INLINE
std::vector<Player *> &Game::GetActivePlayers() { return mAllActivePlayers; }
END_FORCE_LOCAL_INLINE

void Game::SetBackgroundVolume(float vol) {
    mMaster->GetAudio()->SetBackgroundVolume(vol);
}

void Game::SetForegroundVolume(float vol) {
    mMaster->GetAudio()->SetForegroundVolume(vol);
}

void Game::SetVocalCueVolume(float vol) { mMaster->GetAudio()->SetVocalCueFader(vol); }
void Game::SetStereo(bool stereo) { mMaster->GetAudio()->SetStereo(stereo); }

void Game::AddMusicFader(Fader *fader) {
    MILO_ASSERT(mMaster->GetAudio() && mMaster->GetAudio()->GetSongStream(), 0x645);
    mMaster->GetAudio()->GetSongStream()->Faders()->Add(fader);
}

void Game::PopulatePlayerLists() {
    std::vector<BandUser *> &users = TheBandUserMgr->GetBandUsers();
    FOREACH (it, users) {
        BandUser *pUser = *it;
        MILO_ASSERT(pUser, 0x651);
        Player *p = pUser->GetPlayer();
        if (p)
            mAllActivePlayers.push_back(p);
    }
    NullLocalBandUser *nullUser = TheBandUserMgr->GetNullUser();
    if (nullUser) {
        Player *p = nullUser->GetPlayer();
        if (p)
            mAllActivePlayers.push_back(p);
    }
}

DECOMP_FORCEACTIVE(Game, "pPlayer", "player")

void Game::AddBonusPoints(BandUser *pUser, int i2, int) {
    MILO_ASSERT(pUser, 0x666);
    pUser->GetPlayer()->AddPoints(i2, 0, 0);
}

Performer *Game::GetMainPerformer() { return mBand->MainPerformer(); }

ExcitementLevel Game::GetCrowdExcitement() {
    return mBand->MainPerformer()->GetExcitement();
}

bool Game::AllowInput() const { return !mPauseTime && !mRealtime && !mNeverAllowInput; }
void Game::SetKickAutoplay(bool autokick) { gKickAutoplay = autokick; }

void Game::SetVocalPercussionBank(ObjectDir *dir) {
    FOREACH (it, mAllActivePlayers) {
        SetVocalPercussionBank(*it, dir);
    }
}

void Game::SetDrumKitBank(Player *p, ObjectDir *dir) {
    if (p->GetTrackType() == kTrackDrum) {
        GemPlayer *gp = dynamic_cast<GemPlayer *>(p);
        if (gp)
            gp->SetDrumKitBank(dir);
    }
}

void Game::SetDrumKitBank(ObjectDir *dir) {
    FOREACH (it, mAllActivePlayers) {
        SetDrumKitBank(*it, dir);
    }
}

void Game::PrintBasePoints() {
    int pts = TheSongDB->TotalBasePoints();
    MILO_LOG("%s: (base_points %d)\n", MetaPerformer::Current()->Song(), pts);
}

void Game::SetGameOver(bool over) {
    if (TheGamePanel->GetGameState() != kGameOver) {
        if (!over) {
            unk124 = mLastPollMs;
        }
        AutoTimer::SetCollectStats(false, TheRnd->mVerboseTimers);
        TheNetSession->EndGame(GetResult(over), false, unk124);
    }
}

DataNode Game::OnMsg(const GameEndedMsg &msg) {
    ClearState();
    TheSynth->RequirePushToTalk(false, -1);
    if (msg.GetResult() == 0) {
        static DataArrayPtr restart("game_restart");
        restart->Execute();
        return 1;
    } else {
        TheGamePanel->mGameState = kGameOver;
        mResult = msg.GetResult();
        unk124 = msg->Float(3);
        switch (mResult) {
        case kLost:
            TheGamePanel->Export(Message("game_lost"), true);
            break;
        case kWon:
            TheGamePanel->Export(Message("game_won"), true);
            break;
        case kWonFinale:
            TheGamePanel->Export(Message("game_won_finale"), true);
            break;
        case kSkip:
            SetInvalidScore(true);
            SetSkippedSong(true);
            unk148 = true;
            unk120 = false;
            mBand->SetGameOver();
            break;
        case kQuit:
            break;
        default:
            MILO_WARN("bad game over state");
            break;
        }
        TheGamePanel->Export(Message("game_over"), true);
        if (mResult == kSkip) {
            TheGamePanel->Export(Message("game_skip"), true);
        }
        return 1;
    }
}

DataNode Game::OnLocalUserReadyToPlay(const DataArray *a) {
    AddPlayer(a->Obj<BandUser>(2));
    return 1;
}

DataNode Game::OnMsg(const LocalUserLeftMsg &msg) {
    DropUser(dynamic_cast<BandUser *>(msg.GetUser()));
    return 1;
}

DataNode Game::OnMsg(const RemoteUserLeftMsg &msg) {
    DropUser(dynamic_cast<BandUser *>(msg.GetUser()));
    return 1;
}

DataNode Game::OnMsg(const RemoteLeaderLeftMsg &msg) {
    if (unkc4) {
        if (!TheUI->InTransition()) {
            TheGamePanel->Handle(game_outro_msg, true);
        }
    }
    return 1;
}

DataNode Game::OnMsg(const UIScreenChangeMsg &) {
    unkc4 = false;
    return 1;
}

void Game::DropUser(BandUser *user) {
    MILO_ASSERT(user, 0x7D3);
    MILO_ASSERT(mBand, 0x7D5);
    mBand->RemoveUser(user);
    TheGameConfig->RemoveUser(user);
}

DataNode Game::OnMsg(const NewOvershellLocalUserMsg &msg) {
    if (TheGamePanel->GetGameState() == kGameOver)
        return 0;
    else {
        BandUser *band_user = msg.GetBandUser();
        MILO_ASSERT(band_user, 0x7E7);
        AddUser(band_user);
        return 1;
    }
}

void Game::AddUser(BandUser *user) {
    PlayerTrackConfigList *plist = TheGameConfig->GetConfigList();
    plist->AddPlaceholderConfig(user->GetUserGuid(), user->GetSlot(), !user->IsLocal());
    MILO_ASSERT(mBand, 0x7F6);
    mBand->AddUserDynamically(user);
}

const char *Game::DebugCycleAutoplay() { MILO_WARN("statePrev != stateCur"); }
const char *Game::DebugCycleAutoplayAccuracy() {
    MILO_WARN("%0.1f%%");
    MILO_WARN("NA");
}

void Game::SetInvalidScore(bool score) { mInvalidScore = score; }

void Game::SetSkippedSong(bool skipped) {
    mSkippedSong = skipped;
    unk124 = mLastPollMs;
}

void Game::SetResumeFraction(float f1) {
    mResumeTime = f1 * mSongDB->GetSongDurationMs();
}

bool Game::IsInvalidScore() const { return mInvalidScore; }
bool Game::SkippedSong() const { return mSkippedSong; }
bool Game::ResumedNoScore() const { return mResumeTime != 0; }

void Game::ForceTrackerStars(int i) { mTrackerManager->ForceStars(i); }
void Game::OnPlayerAddEnergy(Player *p, float f) {
    mTrackerManager->OnPlayerAddEnergy(p, f);
}
void Game::OnPlayerSaved(Player *p) { mTrackerManager->OnPlayerSaved(p); }
void Game::OnPlayerRemoved(Player *p) { mTrackerManager->HandleRemovePlayer(p); }
void Game::OnPlayerQuarantined(Player *p) { mTrackerManager->OnPlayerQuarantined(p); }
void Game::OnRemoteTrackerFocus(Player *p, int x, int y, int z) {
    mTrackerManager->OnRemoteTrackerFocus(p, x, y, z);
}
void Game::OnRemoteTrackerPlayerProgress(Player *p, float f) {
    mTrackerManager->OnRemoteTrackerPlayerProgress(p, f);
}
void Game::OnRemoteTrackerSectionComplete(Player *p, int x, int y, int z) {
    mTrackerManager->OnRemoteTrackerSectionComplete(p, x, y, z);
}
void Game::OnRemoteTrackerPlayerDisplay(Player *p, int x, int y, int z) {
    mTrackerManager->OnRemoteTrackerPlayerDisplay(p, x, y, z);
}
void Game::OnRemoteTrackerDeploy(Player *p) { mTrackerManager->OnRemoteTrackerDeploy(p); }
void Game::OnRemoteTrackerEndDeployStreak(Player *p, int i) {
    mTrackerManager->OnRemoteTrackerEndDeployStreak(p, i);
}
void Game::OnRemoteTrackerEndStreak(Player *p, int i, int j) {
    mTrackerManager->OnRemoteTrackerEndStreak(p, i, j);
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(Game)
    HANDLE_ACTION(start, Start())
    HANDLE_ACTION(
        set_paused,
        SetPaused(
            _msg->Int(2),
            _msg->Size() > 3 ? _msg->Int(3) : true,
            _msg->Size() > 4 ? _msg->Int(4) : true
        )
    )
    HANDLE_ACTION(set_overshell_pause, OvershellSetPaused(_msg->Int(2)))
    HANDLE_EXPR(get_paused, mIsPaused)
    HANDLE_EXPR(can_user_pause, CanUserPause())
    HANDLE_ACTION(set_music_speed, SetMusicSpeed(_msg->Float(2)))
    HANDLE_ACTION(set_pitch_mucker, SetPitchMucker(_msg->Int(2)))
    HANDLE_EXPR(music_speed, mMusicSpeed)
    HANDLE_EXPR(get_song_ms, GetSongMs())
    HANDLE_EXPR(get_section_at_ms, GetSectionAtMs(_msg->Float(2)))
    HANDLE_ACTION(set_music_volume, SetMusicVolume(_msg->Float(2)))
    HANDLE_ACTION(never_allow_input, NeverAllowInput(_msg->Int(2)))
    HANDLE(set_shuttle, OnSetShuttle)
    HANDLE_EXPR(shuttle_active, mShuttle->IsActive())
    HANDLE(jump, OnJump)
    HANDLE_ACTION(set_intro_real_time, SetIntroRealTime(_msg->Float(2)))
    HANDLE_ACTION(set_realtime, SetRealtime(_msg->Int(2)))
    HANDLE_EXPR(num_active_players, NumActivePlayers())
    HANDLE_EXPR(is_active_user, IsActiveUser(_msg->Obj<BandUser>(2)))
    HANDLE_EXPR(active_player, GetActivePlayer(_msg->Int(2)))
    HANDLE(foreach_active_player, ForEachActivePlayer)
    HANDLE_EXPR(ms_per_beat, TheTempoMap->GetTempo(TheTaskMgr.GetSongPos().GetTick()))
    HANDLE_EXPR(get_result, GetResult(false))
    HANDLE_EXPR(get_result_for_user, GetResultForUser(_msg->Obj<BandUser>(2)))
    HANDLE_ACTION(set_fake_hit_gems_in_fill, mSongDB->SetFakeHitGemsInFill(_msg->Int(2)))
    HANDLE_EXPR(main_performer, GetMainPerformer())
    HANDLE_ACTION(set_kick_autoplay, SetKickAutoplay(_msg->Int(2)))
    HANDLE_EXPR(is_waiting, IsWaiting())
    HANDLE_ACTION(print_base_points, PrintBasePoints())
    HANDLE_ACTION(reset_audio, ResetAudio())
    HANDLE(adjust_for_vocal_phrases, OnAdjustForVocalPhrases)
    HANDLE_EXPR(get_fraction_completed, GetFractionCompleted())
    HANDLE_ACTION(set_resume_fraction, SetResumeFraction(_msg->Float(2)))
    HANDLE_EXPR(resumed_no_score, ResumedNoScore())
    HANDLE_EXPR(skipped_song, SkippedSong())
    HANDLE_EXPR(is_invalid_score, IsInvalidScore())
    HANDLE_ACTION(stats_synced, OnStatsSynced())
    HANDLE_ACTION(replay, Replay())
    HANDLE_ACTION(print_star_thresholds, TheScoring->ComputeStarThresholds(true))
    HANDLE_EXPR(num_active_players, (int)mAllActivePlayers.size())
    HANDLE_ACTION(set_invalid_score, SetInvalidScore(_msg->Int(2)))
    HANDLE_ACTION(set_ready_for_exit, unkc4 = _msg->Int(2))
    HANDLE(required_song_options_chosen, OnLocalUserReadyToPlay)
    HANDLE_ACTION(e3_cheat_autoplay, E3CheatAutoplayAccuracy())
    HANDLE_MESSAGE(GameEndedMsg)
    HANDLE_MESSAGE(NewOvershellLocalUserMsg)
    HANDLE_MESSAGE(UIScreenChangeMsg)
    HANDLE_MESSAGE(LocalUserLeftMsg)
    HANDLE_MESSAGE(RemoteUserLeftMsg)
    HANDLE_MESSAGE(RemoteLeaderLeftMsg)
    HANDLE_EXPR(debug_cycle_autoplay, DebugCycleAutoplay())
    HANDLE_EXPR(debug_cycle_autoplay_accuracy, DebugCycleAutoplayAccuracy())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xA10)
END_HANDLERS
#pragma pop

Game::Properties::Properties()
    : mInTrainer(TheGameMode->InMode("trainer")),
      mInDrumTrainer(TheGameMode->InMode("drum_trainer")),
      mInPracticeMode(TheGameMode->InMode("practice")),
      mAllowOverdrivePhrases(TheGameMode->Property("allow_overdrive_phrases", true)->Int()
      ),
      mEndWithSong(TheGameMode->Property("end_with_song", true)->Int()),
      mForceUseCymbals(TheGameMode->Property("force_use_cymbals", true)->Int()),
      mForceDontUseCymbals(TheGameMode->Property("force_dont_use_cymbals", true)->Int()),
      mAllowAutoVocals(TheGameMode->Property("allow_auto_vocals", true)->Int()),
      mHasSongSections(TheGameMode->Property("has_song_sections", true)->Int()),
      mLoadChars(TheGameMode->Property("load_chars", true)->Int()),
      mLetterbox(TheGameMode->Property("letterbox", true)->Int()),
      mCrowdReacts(TheGameMode->Property("crowd_reacts", true)->Int()),
      mIsPractice(TheGameMode->Property("is_practice", true)->Int()),
      mEnableWhammy(TheGameMode->Property("enable_whammy", true)->Int()),
      mEnableCapstrip(TheGameMode->Property("enable_capstrip", true)->Int()),
      mDisableGuitarFx(TheGameMode->Property("disable_guitar_fx", true)->Int()),
      mDisableKeysFx(TheGameMode->Property("disable_keys_fx", true)->Int()),
      mEnableOverdrive(TheGameMode->Property("enable_overdrive", true)->Int()),
      mEnableCoda(TheGameMode->Property("enable_coda", true)->Int()),
      mCanSolo(TheGameMode->Property("can_solo", true)->Int()),
      mHasBeatMask(TheGameMode->Property("has_beat_mask", true)->Int()),
      mCanLose(TheGameMode->Property("can_lose", true)->Int()),
      mEnableStreak(TheGameMode->Property("enable_streak", true)->Int()),
      mShowStars(TheGameMode->Property("show_stars", true)->Int()),
      mPlayStarSfx(TheGameMode->Property("play_star_sfx", true)->Int()) {}