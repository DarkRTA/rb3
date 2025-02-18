#include "GemPlayer.h"
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
#include "os/Joypad.h"
#include "os/System.h"
#include "rndobj/Overlay.h"
#include "synth/Synth.h"
#include "synthwii/FXWii.h"
#include "utl/SongInfoCopy.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/TimeConversion.h"

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
      unk35c(0), mLastTimeWhammyVelWasHigh(-10000.0f), unk364(0), unk368(0), unk36c(0),
      unk378(0), mGuitarFx(0), mKeysFx(0), mFxPos(4), unk388(0), mPitchShift(0),
      unk390(0), unk394(0), unk398(0), unk39c(-1), unk3a0(-1), unk3a4(0), unk3a8(0),
      unk3ac(0), mAutoMissSoundTimeoutMs(kHugeFloat), unk3b4(0), unk3b8(0), unk3b9(0),
      unk3bc(0), unk3c0(0), mAutoMissSoundTimeoutGems(100000),
      mAutoMissSoundTimeoutGemsRemote(100000), unk3cc(*this), unk3d8(0), unk3dc(-1),
      unk3e0(0), unk3e1(0), unk3e4(0), unk3e8(0), unk3ec(0), unk3f0(0), unk3f4(1),
      unk404(-1), unk408(1) {
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
    if (unk368) {
        unk368->GetGemManager()->SetupGems(0);
        unk368->ResetFills(true);
        unk368->DropIn(tick);
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
    RELEASE(unk36c);
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
    if (mEnabledState == 0 && i1 == GetTrackNum() && unk368) {
        unk368->See(f2, i3);
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

void GemPlayer::SetFillLogic(FillLogic fl) {
    if (mBeatMatcher)
        mBeatMatcher->SetFillLogic(fl);
}

bool GemPlayer::IsAutoplay() const { return mBeatMatcher->IsAutoplay(); }

void GemPlayer::SetAutoplay(bool b) { mBeatMatcher->SetAutoplay(b); }

void GemPlayer::PrintMsg(const char *str) {
    const char *prnt = MakeString("", 3, str);
    *mOverlay << prnt;
    MILO_LOG(prnt);
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
