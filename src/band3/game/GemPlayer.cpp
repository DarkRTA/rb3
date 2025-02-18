#include "GemPlayer.h"
#include "bandtrack/TrackPanel.h"
#include "beatmatch/BeatMatchUtl.h"
#include "beatmatch/BeatMatcher.h"
#include "beatmatch/FillInfo.h"
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/TrackType.h"
#include "game/BandPerformer.h"
#include "game/BandUserMgr.h"
#include "game/Game.h"
#include "game/GameConfig.h"
#include "game/GameMode.h"
#include "game/GuitarFx.h"
#include "game/KeysFx.h"
#include "game/Player.h"
#include "game/SongDB.h"
#include "math/Utl.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/ObjMacros.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "os/System.h"
#include "rndobj/Overlay.h"
#include "synth/Synth.h"
#include "synthwii/FXWii.h"
#include "utl/Messages4.h"
#include "utl/SongInfoCopy.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/TimeConversion.h"
#include "world/Dir.h"

class DeltaTracker;
DeltaTracker *sTracker = nullptr;

static DataNode OnEnableDeltas(DataArray *array) {
    bool enable = array->Int(1);
    RELEASE(sTracker);
    if (enable) {
        sTracker = new DeltaTracker();
    }
    return 0;
}

static DataNode OnPrintDeltas(DataArray *array) {
    if (sTracker) {
        sTracker->PrintDeltas();
    } else
        MILO_LOG("delta tracking not enabled\n");
    return 0;
}

void DeltaTrackerInit() {
    static bool once = true;
    if (once) {
        DataRegisterFunc("enable_deltas", OnEnableDeltas);
        DataRegisterFunc("print_deltas", OnPrintDeltas);
    }
    once = false;
}

bool GetPhraseExtents(BeatmatchPhraseType ty, int i2, int i3, int &i4, int &i5) {
    if (!TheSongDB->GetPhraseExtents(ty, i2, i3, i4, i5))
        return false;
    if (TheGame->mProperties.mHasSongSections) {
        int i20, i24;
        TheGameConfig->GetPracticeSections(i20, i24);
        int i28, i2c;
        TheGameConfig->GetSectionBoundsTick(i20, i28, i2c);
        if (i28 > i4)
            i4 = i28;
        int i30, i34;
        TheGameConfig->GetSectionBoundsTick(i24, i30, i34);
        if (i34 < i5)
            i5 = i34;
        if (ty == kSoloPhrase) {
            if (i3 >= i5)
                return false;
            if (i3 < i4)
                return false;
        }
    }
    if (ty == kSoloPhrase) {
        if (!TheGameMode->Property("can_solo", true)->Int())
            return false;
    }
    return true;
}

GemPlayer::GemPlayer(
    BandUser *user, BeatMaster *bm, Band *band, int i, BandPerformer *perf
)
    : Player(user, band, i, bm), mBandPerformer(perf), mGemStatus(new GemStatus()),
      mDrumSlotWeights(0), mDrumCymbalPointBonus(0), mGameCymbalLanes(0), unk2ec(0),
      unk2ed(0), unk2f0(-1), unk2f4(-1), unk2f8(-1), mNumCrashFillReadyHits(1),
      mUseFills(SystemConfig("scoring", "overdrive")->FindInt("fills")), unk301(0),
      mTrillSlots(-1, -1), unk30c(0), unk310(-1), unk314(0), unk315(0), unk316(0),
      unk318(0), mCodaPointRate(200.0f), mCodaMashPeriod(500.0f), unk33c(1), unk33d(0),
      unk33e(1), mOverlay(RndOverlay::Find("score", true)),
      mGuitarOverlay(RndOverlay::Find("guitar", true)), unk348(0), unk354(0), unk358(0),
      unk35c(0), mLastTimeWhammyVelWasHigh(-10000.0f), unk364(0), mTrack(0),
      mController(0), mSyncOffset(0), mGuitarFx(0), mKeysFx(0), mFxPos(4), unk388(0),
      mPitchShift(0), unk390(0), unk394(0), unk398(0), unk39c(-1), unk3a0(-1), unk3a4(0),
      unk3a8(0), unk3ac(0), mAutoMissSoundTimeoutMs(kHugeFloat), unk3b4(0), unk3b8(0),
      unk3b9(0), unk3bc(0), unk3c0(0), mAutoMissSoundTimeoutGems(100000),
      mAutoMissSoundTimeoutGemsRemote(100000), mStatCollector(*this), unk3d8(0),
      unk3dc(-1), unk3e0(0), unk3e1(0), unk3e4(0), unk3e8(0), unk3ec(0), unk3f0(0),
      unk3f4(1), unk404(-1), unk408(1) {
    for (int i = 0; i < 6; i++) {
        mLastCodaSwing[i] = 0;
    }
    DataArray *odCfg = SystemConfig("scoring", "overdrive");
    mWhammySpeedThreshold = odCfg->FindFloat("whammy_speed") / 100.0f;
    mWhammySpeedTimeout = odCfg->FindFloat("whammy_timeout") * 1000.0f;
    mNumCrashFillReadyHits = odCfg->FindInt("crash_fill_ready_hits");

    DataArray *codaCfg = SystemConfig("scoring", "coda");
    mCodaPointRate = codaCfg->FindFloat("point_rate");
    mCodaMashPeriod = codaCfg->FindFloat("max_mash_ms");

    if (user->GetTrackType() == kTrackDrum) {
        mDrumSlotWeights = SystemConfig("scoring", "crowd", "drum_slot_weights");
        mDrumSlotWeightMapping = mDrumSlotWeights->FindSym("default_weights");
        DataArray *drumCfg = SystemConfig("scoring", "drums");
        mDrumCymbalPointBonus = drumCfg->FindArray("pro_drum_bonus", true);
    }

    SongInfoCopy songInfo(TheSongMgr->SongAudioData(MetaPerformer::Current()->Song()));
    mBeatMatcher = new BeatMatcher(
        GetUserGuid(),
        GetSlot(),
        TheBandUserMgr->GetNumParticipants(),
        TheGameConfig->GetController(GetUser()),
        TheSongDB->GetSongData(),
        songInfo,
        SystemConfig("beatmatcher"),
        bm
    );
    if (DataVariable("no_drum_fills").Int())
        ToggleNoFills();

    int i3 = -1;
    if (GetUser()->IsLocal()) {
        i3 = GetUser()->GetLocalBandUser()->GetPadNum();
    }
    SetSyncOffset(TheProfileMgr.GetSyncOffset(i3));
    mBeatMatcher->RegisterSink(*this);
    mBeatMatcher->DrivePitchBendExternally(IsNet());
    mBeatMatcher->EnableWhammy(TheGame->mProperties.mEnableWhammy);
    mBeatMatcher->EnableCapStrip(TheGame->mProperties.mEnableCapstrip);
    SetFillLogic(TheGame->GetFillLogic());
    SetTypeDef(SystemConfig("player", "handlers"));
    TrackType ty = mUser->GetTrackType();
    if (ty - 1U <= 1 && !TheGame->mProperties.mDisableGuitarFx) {
        mGuitarFx = new GuitarFx(ty);
        mGuitarFx->Load();
        SetGuitarFx();
        if (ty == 1) {
            unk39c = 1;
            TheWiiFX.SetFX(1, mFxPos);
        }
    }
    if (ty - 4U <= 1 && !TheGame->mProperties.mDisableKeysFx) {
        mKeysFx = new KeysFx(ty);
        mKeysFx->Load();
    }
    DeltaTrackerInit();
    if (!TheGame->InDrumTrainer()) {
        DataArray *audioCfg = SystemConfig("beatmatcher", "audio");
        float secs = 0;
        if (audioCfg->FindData("auto_miss_sound_timeout_seconds", secs, false)) {
            mAutoMissSoundTimeoutMs = secs * 1000.0f;
        }
        audioCfg->FindData(
            "auto_miss_sound_timeout_gems", mAutoMissSoundTimeoutGems, false
        );
        audioCfg->FindData(
            "auto_miss_sound_timeout_gems_remote", mAutoMissSoundTimeoutGemsRemote, false
        );
    }

    DataArray *ttypeArr =
        SystemConfig("in_game_tutorials")->FindArray(TrackTypeToSym(GetTrackType()), true);
    mSustainsReleasedBeforePopup =
        ttypeArr->FindArray("released_before_popup", true)->Int(1);
    mHeldNotes.resize(5);
    mUpcomingFretReleases.reserve(10);
};

void GemPlayer::DynamicAddBeatmatch() {
    float ms = TheTaskMgr.Seconds(TaskMgr::kRealTime) * 1000.0f;
    UpdateGameCymbalLanes();
    mBeatMatcher->PostDynamicAdd(mTrackNum, ms);
    Player::DynamicAddBeatmatch();
    mGemStatus->mGems.resize(TheSongDB->GetTotalGems(mTrackNum));
}

void GemPlayer::PostDynamicAdd() {
    float ms = TheTaskMgr.Seconds(TaskMgr::kRealTime) * 1000.0f;
    Player::PostDynamicAdd();
    int tick = MsToTick(ms);
    IgnoreGemsUntil(tick);
    if (mTrack) {
        mTrack->GetGemManager()->SetupGems(0);
        mTrack->ResetFills(true);
        mTrack->DropIn(tick);
    }
    if (GetUser()->IsLocal()) {
        JoypadKeepAlive(GetUser()->GetLocalUser()->GetPadNum(), true);
    }
}

void GemPlayer::Leave() {
    Player::Leave();
    if (mTrackNum != -1) {
        mBeatMatcher->Leave();
    }
    if (GetUser()->IsLocal()) {
        JoypadKeepAlive(GetUser()->GetLocalUser()->GetPadNum(), false);
    }
}

GemPlayer::~GemPlayer() {
    delete mGemStatus;
    if (mTrackNum != -1) {
        std::list<int> chans;
        mBeatMaster->GetAudio()->FillChannelList(chans, mTrackNum);
        Stream *stream = mBeatMaster->GetAudio()->GetSongStream();
        FOREACH (it, chans) {
            stream->SetFXSend(*it, nullptr);
        }
    }
    RELEASE(mBeatMatcher);
    RELEASE(mController);
    RELEASE(mGuitarFx);
    RELEASE(mKeysFx);
    TheSynth->DestroyPitchShift(mPitchShift);
    if (GetUser()->IsLocal()) {
        JoypadKeepAlive(GetUser()->GetLocalUser()->GetPadNum(), false);
    }
}

void GemPlayer::SeeGem(int i1, float f2, int i3) {
    if (unk3b4 == 0) {
        InputReceived();
        unk3b4 = f2;
    }
    if (mEnabledState == 0 && i1 == GetTrackNum() && mTrack) {
        mTrack->See(f2, i3);
    }
    if (unk3b8 && mEnabledState == 0) {
        static Message pass_msg("annoying_pass", 0, 0, 0);
        pass_msg[0] = GetUser();
        pass_msg[1] = TheSongDB->GetGem(mTrackNum, i3).GetSlot();
        pass_msg[2] = i3;
        Handle(pass_msg, false);
    }
    TheSongDB->GetGem(mTrackNum, i3);
    SeeGemHook(i1, f2, i3);
}

void GemPlayer::FinaleSwing(int i1) {
    if (IsLocal()) {
        LocalFinaleSwing(i1);
        if (GetBandTrack()) {
            GetBandTrack()->ClearFinaleHelp();
        }
        static Message msg("send_finale_hit", 0);
        msg[0] = i1;
        HandleType(msg);
    }
}

void GemPlayer::LocalFinaleSwing(int i1) {
    if (TheWorld) {
        static Message msg("");
        msg.SetType(
            MakeString("endgame_swing_%s_%d", TrackTypeToSym(GetTrackType()).mStr, i1)
        );
        TheWorld->Handle(msg, false);
    }
}

void GemPlayer::Swing(int i1, int i2, float f3, bool b4, bool b5) {
    InputReceived();
    if (unk1e1) {
        FinaleSwing(GetTrackSlot(i2));
    } else {
        Export(swing_msg, true);
        if (mTrack && GetUser()->GetTrackType() == 0 && i2 == 0) {
            mTrack->GetTrackDir()->KickSwing();
        }
    }
    SwingHook(i1, i2, f3, b4, b5);
}

bool GemPlayer::HandleSpecialMissScenarios(int i1, float f2) {
    if (CanFlail(f2)) {
        if (mUser->GetTrackType() == 0) {
            int slot = mController->GetVirtualSlot(i1);
            int bucket = mController->GetVelocityBucket(i1);
            PlayDrum(slot, i1, VelocityBucketToDb(bucket), bucket);
        } else {
            static Message miss_msg("miss", 0, 0, 0);
            miss_msg[0] = GetUser();
            miss_msg[1] = i1;
            miss_msg[2] = -1;
            Export(miss_msg, true);
        }
        return true;
    } else
        return false;
}

void GemPlayer::SpuriousMiss(int i1, int i2, float f3, int i4) {
    if (!CanFlail(f3) && mTrack) {
        mTrack->Miss(f3, i4, i2);
    }
}

void GemPlayer::FretButtonDown(int i1, float f2) {
    if (mUser->GetTrackType()) {
        int slot = GetTrackSlot(i1);
        if (mTrack)
            mTrack->SetFretButtonPressed(slot, true);
        static Message msg("fret_down", 0);
        msg[0] = slot;
        Export(msg, false);
    }
}

void GemPlayer::FretButtonUp(int i1, float f2) {
    if (mUser->GetTrackType()) {
        int slot = GetTrackSlot(i1);
        if (mTrack)
            mTrack->SetFretButtonPressed(slot, false);
        static Message msg("fret_up", 0);
        msg[0] = slot;
        Export(msg, false);
    }
}

void GemPlayer::PlayMissSound(int i1) {
    if (unk408) {
        const char *seq;
        switch (GetTrackType()) {
        case 1:
        case 6:
        case 7:
            seq = "miss_gtr.cue";
            break;
        case 2:
        case 8:
        case 9:
            seq = "miss_bass.cue";
            break;
        case 0:
            seq = i1 == 0 ? "miss_kick.cue" : "miss_drum.cue";
            break;
        case 4:
        case 5:
            seq = "miss_keys.cue";
            break;
        default:
            seq = gNullStr;
            break;
        }
        if (seq != gNullStr) {
            GetTrackPanel()->PlaySequence(seq, 0, 0, 0);
        }
    }
}

void GemPlayer::SwingAtHopo(int, float, int) {
    HandleType(swingAtHopo_msg);
    mStats.mHopoGemCount++;
}

void GemPlayer::FillSwing(int i1, int i2, int i3, int i4, bool b5) {
    if (IsLocal()) {
        if (b5 && !unk268) {
            EnterCoda();
        }
        if (i2 >= 0) {
            FillInProgress(i2, i3);
        }
        if (unk268) {
            PopupHelp("rock_ending", false);
        } else {
            PopupHelp("fill", false);
        }
        int tick = TheSongDB->GetCodaStartTick();
        if (!unk268 && (tick >= 0 && (tick - i4 < 0x1E0))) {
            unk2f8 = 100;
        }
        unk2f0 = i4;
        if (mTrack && i3 != -1) {
            ShowFillHit(i3);
        }
    }
}

void GemPlayer::ShowFillHit(int i1) {
    if (IsLocal()) {
        unk2f8++;
        LocalShowFillHit(i1, mController->GetVelocityBucket(i1), unk268);
        static Message msg("send_fill_hit", 0, 0, 0);
        msg[0] = i1;
        msg[1] = unk2f8;
        msg[2] = unk268;
        HandleType(msg);
    }
}

void GemPlayer::OnRemoteFillHit(int i1, int i2, bool b3) {
    if (b3 && !unk268) {
        EnterCoda();
    }
    unk2f8 = i2;
    SetAutoplay(true);
    LocalShowFillHit(i1, 0, b3);
}

void GemPlayer::LocalShowFillHit(int i1, int i2, bool b3) {
    if (mTrack) {
        GemTrackDir *dir = mTrack->GetTrackDir();
        mTrack->FillHit(i1, i2);
        if (unk268 || b3) {
            dir->Mash(i1);
        } else {
            MILO_ASSERT(mTrackType == kTrackDrum, 0x5B6);
            if (mTrackType == kTrackDrum) {
                if (unk2f8 <= mNumCrashFillReadyHits) {
                    dir->FillHit(unk2f8);
                }
                dir->FillMash(i1);
            }
        }
    }
}

void GemPlayer::FillReset() {
    FillInProgress(-1, 0);
    for (int i = 0; i < 6; i++)
        mLastCodaSwing[i] = 0;
    if (mTrack)
        mTrack->GetTrackDir()->FillReset();
}

void GemPlayer::SetFillLogic(FillLogic fl) {
    if (mBeatMatcher)
        mBeatMatcher->SetFillLogic(fl);
}

bool GemPlayer::IsAutoplay() const { return mBeatMatcher->IsAutoplay(); }

void GemPlayer::SetAutoplay(bool b) {
    GetUser()->SetAutoplay(b);
    mBeatMatcher->SetAutoplay(b);
}

void GemPlayer::PrintMsg(const char *str) {
    const char *prnt = MakeString("", GetScore(), str);
    *mOverlay << prnt;
    TheDebug << prnt;
}

void GemPlayer::PrintAddHead(int mils, int idx, int pts, int ms_avg, int recent) {
    if (unk2c4) {
        char id[5] = { 0 };
        if (idx > 1) {
            sprintf(id, " X %d", idx);
        }
        PrintMsg(MakeString(
            "%s (%dms) %d pts -- %dms avg  -- %d recent", id, mils, pts, ms_avg, recent
        ));
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(GemPlayer)
    HANDLE_ACTION(
        disable_fills_deploy_band_energy, mBehavior->SetFillsDeployBandEnergy(false)
    )
    HANDLE_ACTION(
        enable_fills_deploy_band_energy, mBehavior->SetFillsDeployBandEnergy(true)
    )

    HANDLE_ACTION(
        win,
        mBandPerformer ? mBandPerformer->WinGame(_msg->Int(2)) : WinGame(_msg->Int(2))
    )
    HANDLE_ACTION(lose, mBandPerformer ? mBandPerformer->LoseGame() : LoseGame())

    HANDLE_SUPERCLASS(Player)
    HANDLE_CHECK(4668)
END_HANDLERS
#pragma pop
