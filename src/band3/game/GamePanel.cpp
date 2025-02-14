#include "game/GamePanel.h"
#include "GamePanel.h"
#include "bandobj/BandDirector.h"
#include "bandobj/BandWardrobe.h"
#include "bandobj/CrowdAudio.h"
#include "bandtrack/TrackPanel.h"
#include "beatmatch/TrackType.h"
#include "game/BandUserMgr.h"
#include "game/DirectInstrument.h"
#include "game/Game.h"
#include "game/GameMode.h"
#include "game/HitTracker.h"
#include "game/NetGameMsgs.h"
#include "game/Scoring.h"
#include "game/SongDB.h"
#include "meta/HAQManager.h"
#include "meta/PreloadPanel.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "obj/PropSync_p.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "os/Timer.h"
#include "rndobj/Overlay.h"
#include "rndobj/Rnd.h"
#include "synth/Synth.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "utl/Loader.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
#include "utl/Messages3.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

GamePanel *TheGamePanel;
LatencyCallback gGamePanelCallback;

GamePanel::GamePanel()
    : mGame(0), mTime(RndOverlay::Find("time", true)),
      mLatency(RndOverlay::Find("latency", true)),
      mDeltaTime(RndOverlay::Find("delta_time", true)), unk64(1), unk68(0), unk6c(0),
      unk70(0), mStartPaused(0), mGameState(kInLobby), mMultiEvent(0), mScoring(0),
      mLoadProf("game_panel_load", 1), mExcitement(kNumExcitements),
      mLastExcitement(kNumExcitements), mReplay(0), unk150(1), unk151(0), unk154(0),
      mLoadingState(kLoadingState_NotReady), mHitTracker(new HitTracker()),
      mDirectInstrument(new DirectInstrument()) {
    MILO_ASSERT(!TheGamePanel, 0x6B);
    TheGamePanel = this;
    mScoring = new Scoring();
    mConfig.SetName("gamecfg", ObjectDir::sMainDir);
}

GamePanel::~GamePanel() {
    TheGamePanel = nullptr;
    RELEASE(mHitTracker);
    RELEASE(mDirectInstrument);
    RELEASE(mScoring);
}

void GamePanel::Reset() {
    mGame->Reset();
    mGameState = kInLobby;
    mExcitement = kNumExcitements;
    mLastExcitement = kNumExcitements;
    Export(reset_msg, true);
    mGame->Restart(true);
    unk151 = false;
}

void GamePanel::Load() {
    mReplay = false;
    mLoadProf.Start();
    BandSongMetadata *data = (BandSongMetadata *)TheSongMgr->Data(
        TheSongMgr->GetSongIDFromShortName(MetaPerformer::Current()->Song(), true)
    );
    mVocalPercussionBank.LoadFile(
        FilePath(".", data->VocalPercussionBank().mStr), true, true, kLoadBack, false
    );

    const char *drumbankStr = data->DrumKitBank().mStr;
    if (!drumbankStr || *drumbankStr == '\0') {
        drumbankStr = SystemConfig("sound", "banks", "kit")->Str(1);
    }
    mDrumKitBank.LoadFile(FilePath(".", drumbankStr), true, true, kLoadBack, false);
    UIPanel::Load();
    Symbol playModeSym;
    std::vector<BandUser *> users;
    TheBandUserMgr->GetParticipatingBandUsers(users);
    int i6 = data->HasBass();
    int i7 = data->HasGuitar();
    int i8 = data->HasKeys();
    FOREACH (it, users) {
        switch ((*it)->GetTrackType()) {
        case kTrackKeys:
        case kTrackRealKeys:
            i8 = 2;
            break;
        case kTrackBass:
        case kTrackRealBass:
            i6 = 2;
            break;
        case kTrackGuitar:
        case kTrackRealGuitar:
            i7 = 2;
            break;
        default:
            break;
        }
    }
    if (!data->HasKeys())
        i8 = 0;
    if (!data->HasBass())
        i6 = 0;
    if (!data->HasGuitar())
        i7 = 0;
    int i50 = -1;
    if (MaxEq(i50, i7 + i6)) {
        playModeSym = coop_bg;
    }
    if (MaxEq(i50, i7 + i8)) {
        playModeSym = coop_gk;
    }
    if (MaxEq(i50, i6 + i8)) {
        playModeSym = coop_bk;
    }
    TheBandWardrobe->SetPlayMode(playModeSym, nullptr);
}

void GamePanel::CreateGame() {
    RELEASE(mGame);
    mGame = new Game();
    mGame->mDisablePauseMs = Property(disable_pause_ms, true)->Float();
}

void GamePanel::PollForLoading() {
    mLoadingState = kLoadingState_NotReady;
    UIPanel::PollForLoading();
    if (UIPanel::IsLoaded()) {
        mLoadingState = kLoadingState_UILoaded;
        if (TheUI->TransitionScreen()) {
            if (TheUI->TransitionScreen()->HasPanel(
                    ObjectDir::sMainDir->Find<UIPanel>("world_panel", true)
                )) {
                if (!TheBandDirector || !TheBandDirector->ReadyForMidiParsers())
                    return;
            }
        }
        mLoadingState = kLoadingState_WorldLoaded;
        if (TheGameMode->Property("load_chars", true)->Int()
            && !(TheBandWardrobe && TheBandWardrobe->AllCharsLoaded()))
            return;
        else {
            mLoadingState = kLoadingState_CharsLoaded;
            if (!mGame)
                CreateGame();
            if (mGame->IsReady()) {
                mLoadingState = kLoadingState_Ready;
            }
        }
    }
}

bool GamePanel::IsLoaded() const {
    if (!UIPanel::IsLoaded())
        return false;
    if (!mVocalPercussionBank.IsLoaded())
        return false;
    if (!mDrumKitBank.IsLoaded())
        return false;
    if (!mDirectInstrument->IsLoaded())
        return false;
    return mLoadingState == kLoadingState_Ready;
}

void GamePanel::Unload() {
    UIPanel::Unload();
    RELEASE(mVocalPercussionBank);
    RELEASE(mDrumKitBank);
    RELEASE(mGame);
    mLoadingState = kLoadingState_NotReady;
}

void GamePanel::Enter() {
    TheTaskMgr.ClearTasks();
    UIPanel::Enter();
    mLoadProf.Stop();
    Reset();
    mGame->SetPaused(false, true, true);
    ThePlatformMgr.SetNotifyUILocation((NotifyLocation)0);
    if (TheRnd->GetAspect() != Rnd::kWidescreen && !TheGame->mProperties.mLetterbox) {
        TheRnd->SetAspect(Rnd::kRegular);
        TrackPanelDirBase *trackPanelDir = GetTrackPanelDir();
        MILO_ASSERT(trackPanelDir, 0x155);
        RndCam *cam = trackPanelDir->GetCam();
        MILO_ASSERT(cam, 0x158);
        cam->UpdateLocal();
    }
}

void GamePanel::Exit() {
    if (!mMultiEvent) {
        TheTaskMgr.ClearTimelineTasks(kTaskSeconds);
        TheTaskMgr.ClearTimelineTasks(kTaskBeats);
        TheTaskMgr.ClearTimelineTasks(kTaskTutorialSeconds);
    }
    UIPanel::Exit();
    mReplay = true;
    ThePlatformMgr.SetNotifyUILocation((NotifyLocation)1);
    if (TheRnd->GetAspect() != Rnd::kWidescreen && !TheGame->mProperties.mLetterbox) {
        TheRnd->SetAspect(Rnd::kLetterbox);
    }
}

void GamePanel::StartGame() {
    AutoTimer::SetCollectStats(true, TheRnd->unkec);
    Export(on_extend_msg, true);
    if (mGame->HasIntro())
        mGame->Start();
    mGameState = kGamePlaying;
    if (DataVariable("vocal_test").Int()) {
        RunVocalTest();
    }
}

void GamePanel::RunVocalTest() {
    float durms = TheSongDB->GetSongDurationMs();
    unk150 = false;
    float f1 = 0;
    while (f1 < durms) {
        TheTaskMgr.SetSeconds(f1 / 1000.0f, false);
        f1 += 16.0f;
        mGame->Poll();
    }
    TheDebug.Exit(0, true);
}

void GamePanel::Poll() { START_AUTO_TIMER("game_poll"); }

void GamePanel::SetPaused(bool b1) {
    MILO_WARN(
        "Should not set game panel paused! Use SetGamePaused(bool) or {game set_game_paused <bool> instead!"
    );
    mPaused = b1;
}

void GamePanel::SetPlayingTrackIntroUntil(float f1) {
    if (!unk151) {
        unk151 = true;
        unk154 = f1;
    } else if (unk154 < f1) {
        unk154 = f1;
    }
}

void GamePanel::StartIntro() {
    mGameState = kStartingGame;
    HandleType(pick_intro_msg);
    if (mStartPaused) {
        mGame->SetPaused(true, true, true);
    }
    SetExcitementLevel(mGame->GetCrowdExcitement());
    mGame->StartIntro();
}

void GamePanel::UpdateNowBar() { MILO_ASSERT(mGame, 0x212); }

void GamePanel::SetDejitteredTime(float f1) {
    unk6c = unk70;
    unk70 = f1 - unk68;
    unk68 = f1;
}

void GamePanel::UpdateDeltaTimeOverlay() {
    *mDeltaTime << MakeString("dt: %5.1f, ddt: %5.1f\n", unk70, unk70 - unk6c);
}

void GamePanel::FinishLoad() {
    UIPanel::FinishLoad();
    mVocalPercussionBank.PostLoad(nullptr);
    mGame->SetVocalPercussionBank(mVocalPercussionBank);
    mDrumKitBank.PostLoad(nullptr);
    mGame->SetDrumKitBank(mDrumKitBank);
    mDirectInstrument->PostLoad();
    PreloadPanel::sCache->Clear();
    HAQManager::PrintSongInfo(
        MetaPerformer::Current()->Song(), TheSongDB->GetSongDurationMs()
    );
    if (unk64)
        unk64 = false;
}

void GamePanel::PlayBandDiedCue() {
    String cue;
    TheSongDB->GetBandFailCue(cue);
    if (cue == "") {
        TheSynth->Play("band_fail_rock.cue", 0, 0, 0);
    } else {
        TheSynth->Play(cue.c_str(), 0, 0, 0);
    }
}

void GamePanel::SendRestartGameNetMsg(bool b1) {
    RestartGameMsg msg(b1);
    TheNetSession->SendMsgToAll(msg, kReliable);
}

void GamePanel::SendResumeNoScoreGameNetMsg(float f1) {
    ResumeNoScoreGameMsg msg(f1);
    TheNetSession->SendMsgToAll(msg, kReliable);
}

void GamePanel::SetExcitementLevel(ExcitementLevel e) {
    if (mExcitement != e) {
        mLastExcitement = mExcitement;
        mExcitement = e;
        static Message msg("excitement", 0);
        msg[0] = e;
        Export(msg, true);
    }
}

void GamePanel::ToggleInstrumentSynth() {
    if (mDirectInstrument->Enabled()) {
        mDirectInstrument->Disable();
    } else
        mDirectInstrument->Enable();
}

DataNode GamePanel::OnStartLoadSong(DataArray *a) {
    Symbol s = a->ForceSym(2);
    std::vector<Symbol> syms;
    syms.push_back(s);
    MetaPerformer::Current()->SetSongs(syms);
    CreateGame();
    return 0;
}

BEGIN_HANDLERS(GamePanel)
    HANDLE_ACTION(set_start_paused, mStartPaused = _msg->Int(2))
    HANDLE_EXPR(lost, mGameState == kGameOver && mGame->unkcc == 1)
    HANDLE_EXPR(in_intro, mGameState == kStartingGame)
    HANDLE_EXPR(is_game_over, mGameState == kGameOver)
    HANDLE_EXPR(is_playing, mGameState == kGamePlaying)
    HANDLE_ACTION(start_game, StartGame())
    HANDLE(start_load_song, OnStartLoadSong)
    HANDLE_ACTION(send_restart_game_net_msg, SendRestartGameNetMsg(_msg->Int(2)))
    HANDLE_ACTION(
        send_resume_no_score_game_net_msg, SendResumeNoScoreGameNetMsg(_msg->Float(2))
    )
    HANDLE_ACTION(clear_draw_glitch, ClearDrawGlitch())
    HANDLE_ACTION(play_band_died_cue, PlayBandDiedCue())
    HANDLE_ACTION(print_hit_stats, mHitTracker->PrintStats())
    HANDLE_ACTION(clear_hit_stats, mHitTracker->Reset())
    HANDLE_ACTION(toggle_instrument_synth, ToggleInstrumentSynth())
    HANDLE_EXPR(is_instrument_synth_on, mDirectInstrument->Enabled())
    HANDLE_ACTION(set_instrument_synth_volume, mDirectInstrument->SetVolume(_msg->Int(2)))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_MEMBER_PTR((&mConfig))
    HANDLE_MEMBER_PTR(mGame)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x352)
END_HANDLERS

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(GamePanel)
    SYNC_PROP(multi_event, mMultiEvent)

    {
        static Symbol _s("excitement");
        if (sym == _s && _op & kPropGet)
            return PropSync((int &)mExcitement, _val, _prop, _i + 1, _op);
    }
    {
        static Symbol _s("last_excitement");
        if (sym == _s && _op & kPropGet)
            return PropSync((int &)mLastExcitement, _val, _prop, _i + 1, _op);
    }
    {
        static Symbol _s("replay");
        if (sym == _s && _op & kPropGet)
            return PropSync(mReplay, _val, _prop, _i + 1, _op);
    }

    if (&mConfig && mConfig.SyncProperty(_val, _prop, _i, _op)) {
        return true;
    } else
        return false;
END_PROPSYNCS
#pragma pop

float LatencyCallback::UpdateOverlay(RndOverlay *, float) {}