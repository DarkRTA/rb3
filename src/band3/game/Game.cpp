#include "game/Game.h"
#include "bandtrack/TrackPanel.h"
#include "beatmatch/BeatMaster.h"
#include "beatmatch/PlayerTrackConfig.h"
#include "beatmatch/SongData.h"
#include "game/Band.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/FadePanel.h"
#include "game/GameConfig.h"
#include "game/GameMode.h"
#include "game/NetGameMsgs.h"
#include "game/Player.h"
#include "game/Shuttle.h"
#include "game/SongDB.h"
#include "game/TrackerManager.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/BandUI.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/OvershellPanel.h"
#include "midi/MidiParserMgr.h"
#include "net/NetMessage.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "synth/Synth.h"
#include "ui/UIScreen.h"
#include "utl/SongInfoCopy.h"
#include "utl/Symbols4.h"
#include "utl/TimeConversion.h"

Game *TheGame;

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
    : mSongDB(new SongDB()), mSongInfo(0), mIsPaused(0), unk69(0), unk6a(0), unk6b(0),
      unk6c(0), unk6d(0), mRealtime(0), unk6f(0), unk70(0), unkac(0), unkb0(0),
      mMusicSpeed(1.0f), mNeverAllowInput(0), unkb9(1), unkbc(0), unkc0(0), unkc4(0),
      unkc8(0), unkcc(0), mBand(0), mShuttle(new Shuttle()), unkdc(-1), unk11c(-1),
      unk120(0), mSkippedSong(0), unk124(0), unk128(0), mInvalidScore(0), unk130(0),
      unk134(0), unk138(0), unk139(1), unk13c(-1), unk140(-1), mTrackerManager(0),
      unk148(0), unk14c(-1), unk150(1) {
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
    unkbc = SystemConfig(demo)->FindInt(max_pct_complete);
    unkc0 = SystemConfig(demo)->FindFloat(max_ms);
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
    mMaster->GetMasterAudio()->SetPracticeMode(TheGameMode->InMode("practice"));
    RELEASE(mSongInfo);
    mSongInfo = new SongInfoCopy(TheSongMgr->SongAudioData(songSym));
    mMaster->Load(mSongInfo, 4, cfgList, false, i2, nullptr);
}

bool Game::IsLoaded() {
    if (unkc8 == 2)
        return true;
    else if (mMaster && mMaster->GetMasterAudio()->GetSongStream()
             && mMaster->GetMasterAudio()->Fail()) {
        return true;
    } else if (mMaster && !mMaster->IsLoaded()) {
        return false;
    } else {
        if (unkc8 == 0) {
            if (!mMaster->IsLoaded())
                return false;
            TheSongDB->PostLoad(GetBeatMaster()->GetMidiParserMgr()->GetEventsList());
            PostLoad();
            unkc8 = 1;
        }
        if (unkc8 == 1) {
            if (mMaster->GetMasterAudio()->Fail())
                return true;
            if (!mMaster->GetMasterAudio()->IsReady()) {
                TheSynth->Poll();
                return false;
            }
            unkc8 = 2;
            TheProfileMgr.PushAllOptions();
            mTrackerManager->ConfigureGoals();
        }
        return unkc8 == 2;
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
    if (!mMaster->GetMasterAudio()->Fail()) {
        if (unk150) {
            GetTrackPanelDir()->UpdateTrackSpeed();
            unk150 = false;
        }
        mMaster->GetMasterAudio()->Play();
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

void Game::Reset() {}

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

float Game::GetSongMs() const { return mMaster->GetMasterAudio()->GetTime(); }

void Game::RemovePlayer(Player *p) {
    mAllActivePlayers.erase(
        std::find(mAllActivePlayers.begin(), mAllActivePlayers.end(), p),
        mAllActivePlayers.end()
    );
}

void Game::SetPaused(bool b1, bool b2, bool b3) {
    unk69 = b1;
    UpdatePausedState(b2, b3);
}

bool Game::CanUserPause() const {
    return !mProperties.mEndWithSong || unkac < TheSongDB->GetSongDurationMs() - unk14c;
}

void Game::DiscErrorEnd() { unk6b = true; }

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