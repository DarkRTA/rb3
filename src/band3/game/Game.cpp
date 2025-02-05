#include "game/Game.h"
#include "beatmatch/BeatMaster.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/GameMode.h"
#include "game/Shuttle.h"
#include "game/SongDB.h"
#include "meta_band/BandUI.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/OvershellPanel.h"
#include "net/NetSession.h"
#include "os/Debug.h"
#include "ui/UIScreen.h"

Game *TheGame;

Game::Game()
    : mSongDB(new SongDB()), unk58(0), mIsPaused(0), unk69(0), unk6a(0), unk6b(0),
      unk6c(0), unk6d(0), unk6e(0), unk6f(0), unk70(0), unkac(0), unkb0(0), unkb4(1.0f),
      unkb8(0), unkb9(1), unkbc(0), unkc0(0), unkc4(0), unkc8(0), unkcc(0), unkd0(0),
      mShuttle(new Shuttle()), unkdc(-1), unk11c(-1), unk120(0), unk121(0), unk124(0),
      unk128(0), unk12c(0), unk130(0), unk134(0), unk138(0), unk139(1), unk13c(-1),
      unk140(-1), unk144(0), unk148(0), unk14c(-1), unk150(1) {
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
}

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