/*
    Compile unit: C:\rockband2\band2\src\game\GemPlayer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80065084 -> 0x8006FEE8
*/
class Symbol name; // size: 0x4, address: 0x80A4995C
class Symbol name; // size: 0x4, address: 0x80A49964
class DeltaTracker {
    // total size: 0xFA4
protected:
    float mDeltas[1000]; // offset 0x0, size 0xFA0
    int mCur; // offset 0xFA0, size 0x4
};
static class DeltaTracker * sTracker; // size: 0x4, address: 0x80A49968
// Range: 0x80065084 -> 0x80065114
static class DataNode OnEnableDeltas(class DataArray * msg /* r30 */) {
    // References
    // -> static class DeltaTracker * sTracker;
}

// Range: 0x80065114 -> 0x80065338
static class DataNode OnPrintDeltas() {
    // References
    // -> class Debug TheDebug;
    // -> static class DeltaTracker * sTracker;
}

static unsigned char once; // size: 0x1, address: 0x80A463A4
// Range: 0x80065338 -> 0x800653A0
void DeltaTrackerInit() {
    // References
    // -> static unsigned char once;
}

// Range: 0x800653A0 -> 0x800654B0
static unsigned char GetPhraseExtents(enum BeatmatchPhraseType type /* r28 */, int track /* r0 */, int tick /* r29 */, int & start /* r30 */, int & end /* r31 */) {
    // Local variables
    int startSection; // r1+0x14
    int endSection; // r1+0x10
    int practiceStart; // r1+0xC
    int practiceEnd; // r1+0x8

    // References
    // -> class GameConfig * TheGameConfig;
    // -> class GameMode * TheGameMode;
    // -> class SongDB * TheSongDB;
}

class GuitarFx : public Object {
    // total size: 0x68
    int mLastSetting; // offset 0x28, size 0x4
    unsigned char mLastGains; // offset 0x2C, size 0x1
    unsigned char mLastReverb; // offset 0x2D, size 0x1
    enum TrackType mTrackType; // offset 0x30, size 0x4
    int mFramesWhammyIdle; // offset 0x34, size 0x4
    class DataArray * mFxCfg; // offset 0x38, size 0x4
    class ObjDirPtr mFxDir; // offset 0x3C, size 0xC
    float mLastFbNote; // offset 0x48, size 0x4
    float mFbNote; // offset 0x4C, size 0x4
    float mFbEnd; // offset 0x50, size 0x4
    unsigned char mHeldNoteState; // offset 0x54, size 0x1
    int mFbTrigger; // offset 0x58, size 0x4
    int mPrevFbTrigger; // offset 0x5C, size 0x4
    unsigned char mLastWhammying; // offset 0x60, size 0x1
    float mLastWhammyPos; // offset 0x64, size 0x4
};
class FxSendPitchShift : public FxSend {
    // total size: 0x54
protected:
    float mRatio; // offset 0x50, size 0x4
};
// Range: 0x800654B0 -> 0x80065C44
void * GemPlayer::GemPlayer(class GemPlayer * const this /* r28 */, class BandUser * config /* r29 */, class BeatMaster * beatMaster /* r30 */, class Band * band /* r27 */, int player /* r26 */, int track /* r24 */, class BandPerformer * band_performer /* r23 */) {
    // Local variables
    int i; // r4
    class DataArray * star_power_cfg; // r23
    class DataArray * coda_cfg; // r23
    class DataArray * endgame_cfg; // r23
    int i; // r4
    class Symbol song; // r1+0xA8
    enum TrackType inst; // r23

    // References
    // -> class WiiFX TheWiiFX;
    // -> class GameMode * TheGameMode;
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class SongMgr & TheSongMgr;
    // -> class GameConfig * TheGameConfig;
    // -> class SongDB * TheSongDB;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__9GemPlayer;
    // -> struct [anonymous] __vt__13BeatMatchSink;
}

// Range: 0x80065C44 -> 0x80065E0C
void * GemPlayer::~GemPlayer(class GemPlayer * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__9GemPlayer;
}

enum BeatMatchControllerGemMapping {
    kDefaultGemMapping = 0,
    kDrumGemMapping = 1,
};
class BeatMatchController : public Object {
    // total size: 0x3C
protected:
    int mPlayerNum; // offset 0x28, size 0x4
    int mForceMercuryBut; // offset 0x2C, size 0x4
    unsigned char mLefty; // offset 0x30, size 0x1
    enum BeatMatchControllerGemMapping mGemMapping; // offset 0x34, size 0x4
private:
    const class DataArray * mSlots; // offset 0x38, size 0x4
};
static class Message dtmsg; // size: 0x8, address: 0x80977338
// Range: 0x80065E0C -> 0x800660D8
void GemPlayer::SeeGem(class GemPlayer * const this /* r30 */, int gem_id /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class Message dtmsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
}

static class Message msg; // size: 0x8, address: 0x80977350
// Range: 0x800660D8 -> 0x80066388
void GemPlayer::FinaleSwing(class GemPlayer * const this /* r28 */, int slot /* r29 */, float ms /* f31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x80977368
// Range: 0x80066388 -> 0x8006657C
void GemPlayer::LocalFinaleSwing(class GemPlayer * const this /* r30 */, int slot /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class WorldDir * TheWorld;
}

static class Message msg; // size: 0x8, address: 0x80977380
// Range: 0x8006657C -> 0x8006672C
void GemPlayer::Swing(class GemPlayer * const this /* r28 */, int slot /* r29 */, unsigned char downstrum /* r30 */, unsigned char auto_swing /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x80977398
static class Message dtmsg; // size: 0x8, address: 0x809773B0
// Range: 0x8006672C -> 0x80066FE0
void GemPlayer::Hit(class GemPlayer * const this /* r26 */, float ms /* f31 */, int gem_id /* r27 */, unsigned char solo_button /* r28 */) {
    // Local variables
    const class GameGem & gem; // r29
    float delta_ms; // f0
    int hitFlags; // r24

    // References
    // -> static class Message dtmsg;
    // -> class GameMode * TheGameMode;
    // -> class Scoring * TheScoring;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> static class DeltaTracker * sTracker;
    // -> class SongDB * TheSongDB;
}

// Range: 0x80066FE0 -> 0x80067084
unsigned char GemPlayer::CanFreestyle(class GemPlayer * const this /* r5 */, float ms /* f31 */) {
    // Local variables
    const class GameGem & first_gem; // r0

    // References
    // -> class SongDB * TheSongDB;
    // -> class DrumTrainerPanel * TheDrumTrainerPanel;
    // -> class GameMode * TheGameMode;
}

static class Symbol drum_freestyle; // size: 0x4, address: 0x80A49974
static class Message miss_msg; // size: 0x8, address: 0x809773C8
// Range: 0x80067084 -> 0x8006753C
unsigned char GemPlayer::HandleSpecialMissScenarios(class GemPlayer * const this /* r27 */, int slot /* r28 */, float ms /* f30 */) {
    // Local variables
    int virtual_slot; // r30
    int bucket; // r29
    float vol; // f31
    enum TrackType track_type; // r0

    // References
    // -> static class Message miss_msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol drum_freestyle;
}

static class Message missMsg; // size: 0x8, address: 0x809773E0
static class Message dtmsg; // size: 0x8, address: 0x809773F8
// Range: 0x8006753C -> 0x80067AC8
void GemPlayer::Miss(class GemPlayer * const this /* r28 */, int slot /* r29 */, float ms /* f31 */, int gem_id /* r30 */) {
    // References
    // -> static class Message dtmsg;
    // -> class SongDB * TheSongDB;
    // -> class GameMode * TheGameMode;
    // -> static class Message missMsg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message passMsg; // size: 0x8, address: 0x80977410
static class Message dtmsg; // size: 0x8, address: 0x80977428
// Range: 0x80067AC8 -> 0x80068178
void GemPlayer::Pass(class GemPlayer * const this /* r27 */, float ms /* f31 */, int gem_id /* r28 */) {
    // Local variables
    const class vector & phraseIDs; // r0

    // References
    // -> class Debug TheDebug;
    // -> static class Message dtmsg;
    // -> class GameMode * TheGameMode;
    // -> static class Message passMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
    // -> class Synth * TheSynth;
    // -> class SongDB * TheSongDB;
}

static class Message fill_pass; // size: 0x8, address: 0x80977440
// Range: 0x80068178 -> 0x800682F8
void GemPlayer::Ignore(class GemPlayer * const this /* r31 */, int gem_id /* r30 */) {
    // References
    // -> static class Message fill_pass;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameMode * TheGameMode;
}

static class Message msg; // size: 0x8, address: 0x80977458
// Range: 0x800682F8 -> 0x800684FC
void GemPlayer::FretButtonDown(class GemPlayer * const this /* r30 */, int slot /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x80977470
// Range: 0x800684FC -> 0x80068700
void GemPlayer::FretButtonUp(class GemPlayer * const this /* r30 */, int slot /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x80068700 -> 0x80068748
void GemPlayer::MercurySwitch() {}

static class Message msg; // size: 0x8, address: 0x80977488
static class Message msg; // size: 0x8, address: 0x809774A0
// Range: 0x80068748 -> 0x80068C3C
void GemPlayer::FilteredWhammyBar(class GemPlayer * const this /* r29 */, float val /* f31 */) {
    // Local variables
    int phrase; // r4
    float whammy_vel; // f0
    unsigned char whammy_vel_high_now; // r27
    unsigned char active; // r0
    float ms; // f0

    // References
    // -> static class Message msg;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class SongDB * TheSongDB;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
}

static class Message msg; // size: 0x8, address: 0x809774B8
// Range: 0x80068C3C -> 0x80068D80
void GemPlayer::SwingAtHopo(class GemPlayer * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x809774D0
// Range: 0x80068D80 -> 0x80068EA0
void GemPlayer::Hopo(class GemPlayer * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x80068EA0 -> 0x80068F94
void GemPlayer::ReleaseGem(class GemPlayer * const this /* r30 */, float ms /* f31 */, int gem_id /* r31 */) {}

static class Message fillHitMsg; // size: 0x8, address: 0x809774E8
static class Message fillMissMsg; // size: 0x8, address: 0x80977500
static class Symbol drum_freestyle; // size: 0x4, address: 0x80A49988
static class Message missMsg; // size: 0x8, address: 0x80977518
// Range: 0x80068F94 -> 0x800696E4
void GemPlayer::FillSwing(class GemPlayer * const this /* r26 */, int total /* r24 */, int slot /* r27 */, int tick /* r25 */, unsigned char hit /* r28 */, unsigned char at_end /* r29 */) {
    // Local variables
    struct FillExtent fillExtent; // r1+0x78
    int codaStart; // r0
    int bucket; // r28
    float vol; // f31

    // References
    // -> static class Message missMsg;
    // -> class TaskMgr TheTaskMgr;
    // -> static class Symbol drum_freestyle;
    // -> static class Message fillMissMsg;
    // -> static class Message fillHitMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameMode * TheGameMode;
    // -> class SongDB * TheSongDB;
}

// Range: 0x800696E4 -> 0x80069780
void GemPlayer::ShowFillHit(class GemPlayer * const this /* r30 */, int slot /* r31 */) {}

// Range: 0x80069780 -> 0x800697EC
void GemPlayer::OnRemoteFillHit(class GemPlayer * const this /* r29 */, int slot /* r30 */, unsigned char in_coda /* r31 */) {}

// Range: 0x800697EC -> 0x8006989C
void GemPlayer::LocalShowFillHit(class GemPlayer * const this /* r29 */, int slot /* r30 */, unsigned char in_coda /* r31 */) {}

// Range: 0x8006989C -> 0x8006990C
void GemPlayer::FillReset(class GemPlayer * const this /* r31 */) {
    // Local variables
    int i; // r4
}

static class Message trainer_crash_fill; // size: 0x8, address: 0x80977530
// Range: 0x8006990C -> 0x80069AA8
void GemPlayer::FillComplete(class GemPlayer * const this /* r30 */, int fill_end_tick /* r31 */) {
    // References
    // -> static class Message trainer_crash_fill;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameMode * TheGameMode;
}

// Range: 0x80069AA8 -> 0x80069BFC
void GemPlayer::IgnoreGemsUntil(class GemPlayer * const this /* r30 */, int end_tick /* r28 */) {
    // Local variables
    const class GameGemList & gems; // r29
    int gem_id; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongDB * TheSongDB;
}

// Range: 0x80069BFC -> 0x80069C34
class Symbol GemPlayer::GetStarRating() {
    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x80069C34 -> 0x80069C88
int GemPlayer::GetNumStars(const class GemPlayer * const this /* r30 */) {}

// Range: 0x80069C88 -> 0x80069CB4
int GemPlayer::GetBaseMaxPoints() {
    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x80069CB4 -> 0x80069CE0
int GemPlayer::GetBaseMaxStreakPoints() {
    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x80069CE0 -> 0x80069D0C
int GemPlayer::GetBaseBonusPoints() {
    // References
    // -> class SongDB * TheSongDB;
}

static class DataNode & force_guitar_fx; // size: 0x4, address: 0x80A49990
static class Message msg; // size: 0x8, address: 0x80977548
// Range: 0x80069D0C -> 0x8006A2DC
void GemPlayer::Poll(class GemPlayer * const this /* r29 */, float ms /* f31 */, const class SongPos & pos /* r28 */) {
    // Local variables
    float delta_ticks; // f1
    int tick; // r28
    float tempo; // f0
    int oldFx; // r30
    float beat; // f0
    float frac; // f0
    unsigned char deploy; // r31
    unsigned char solo; // r30

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class WorldDir * TheWorld;
    // -> class WiiFX TheWiiFX;
    // -> class SongDB * TheSongDB;
    // -> class TempoMap * TheTempoMap;
    // -> class Game * TheGame;
    // -> class Scoring * TheScoring;
    // -> class GameMode * TheGameMode;
    // -> class ProfileMgr TheProfileMgr;
    // -> static class DataNode & force_guitar_fx;
}

// Range: 0x8006A2DC -> 0x8006A580
void GemPlayer::Restart(class GemPlayer * const this /* r31 */) {
    // Local variables
    class BandTrack * track; // r0
    int i; // r4
    enum TrackType track_type; // r0
    int i; // r4

    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x8006A580 -> 0x8006A5F8
void GemPlayer::SetTrack(class GemPlayer * const this /* r30 */, int track_num /* r31 */) {}

// Range: 0x8006A5F8 -> 0x8006A984
void GemPlayer::PostLoad(class GemPlayer * const this /* r30 */) {
    // Local variables
    class list chans; // r1+0x78
    struct _List_iterator itr; // r1+0x4C
    class list chans; // r1+0x70
    unsigned int i; // r1+0x48

    // References
    // -> class GameMode * TheGameMode;
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006A984 -> 0x8006A98C
unsigned char GemPlayer::IsReady() {}

// Range: 0x8006A98C -> 0x8006AA6C
class FxSendPitchShift * GemPlayer::GetPitchShift(class GemPlayer * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16FxSendPitchShift;
    // -> class Symbol name;
}

// Range: 0x8006AA6C -> 0x8006AB14
void GemPlayer::Start(class GemPlayer * const this /* r31 */) {
    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x8006AB14 -> 0x8006AB20
float GemPlayer::GetSongMs() {}

// Range: 0x8006AB20 -> 0x8006AB8C
void GemPlayer::PollTrack(class GemPlayer * const this /* r31 */) {
    // Local variables
    struct PlayerState playerState; // r1+0x8
}

// Range: 0x8006AB8C -> 0x8006AB90
void GemPlayer::PollAudio() {}

// Range: 0x8006AB90 -> 0x8006ABF8
void GemPlayer::SetPaused(class GemPlayer * const this /* r31 */) {}

// Range: 0x8006ABF8 -> 0x8006AC54
void GemPlayer::UpdateLeftyFlip(class GemPlayer * const this /* r31 */) {}

// Range: 0x8006AC54 -> 0x8006AC58
void GemPlayer::SetRealtime() {}

// Range: 0x8006AC58 -> 0x8006AC74
void GemPlayer::SetMusicSpeed() {}

// Range: 0x8006AC74 -> 0x8006AD78
void GemPlayer::Jump(class GemPlayer * const this /* r30 */, float ms /* f31 */, unsigned char sync_audio /* r31 */) {
    // Local variables
    int i; // r4
}

// Range: 0x8006AD78 -> 0x8006AD88
void GemPlayer::SetAutoplay() {}

// Range: 0x8006AD88 -> 0x8006AD90
unsigned char GemPlayer::IsAutoplay() {}

// Range: 0x8006AD90 -> 0x8006AE48
void GemPlayer::HookupTrack(class GemPlayer * const this /* r30 */) {
    // Local variables
    class TrackPanel * trackPanel; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__5Track;
    // -> struct [anonymous] __RTTI__8GemTrack;
}

// Range: 0x8006AE48 -> 0x8006AE54
void GemPlayer::UnHookTrack() {}

// Range: 0x8006AE54 -> 0x8006AEC8
void GemPlayer::EnableFills(class GemPlayer * const this /* r31 */, float delay /* f31 */) {}

// Range: 0x8006AEC8 -> 0x8006AEE0
void GemPlayer::DisableFills() {}

// Range: 0x8006AEE0 -> 0x8006AF68
void GemPlayer::EnableDrumFills(class GemPlayer * const this /* r31 */) {
    // Local variables
    float delayMS; // f1
}

// Range: 0x8006AF68 -> 0x8006B000
unsigned char GemPlayer::FillsEnabled(class GemPlayer * const this /* r28 */, int tick /* r29 */) {
    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006B000 -> 0x8006B090
void GemPlayer::EnterCoda(class GemPlayer * const this /* r31 */) {
    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x8006B090 -> 0x8006B09C
void GemPlayer::ResetCodaPoints() {}

// Range: 0x8006B09C -> 0x8006B114
void GemPlayer::AddCodaPoints(class GemPlayer * const this /* r30 */) {}

// Range: 0x8006B114 -> 0x8006B1F4
void GemPlayer::LocalSetEnabledState(class GemPlayer * const this /* r29 */, enum EnabledState state /* r30 */, int tick /* r31 */) {
    // References
    // -> class GamePanel * TheGamePanel;
}

// Range: 0x8006B1F4 -> 0x8006B200
void GemPlayer::SetSyncOffset() {}

// Range: 0x8006B200 -> 0x8006B278
void GemPlayer::EnableSwings(class GemPlayer * const this /* r30 */, unsigned char enable /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8006B278 -> 0x8006B30C
void GemPlayer::PlayDrum(class GemPlayer * const this /* r29 */, int slot /* r30 */, float vol /* f31 */, class Symbol & sample_set /* r31 */) {}

// Range: 0x8006B30C -> 0x8006B380
void GemPlayer::OverrideDrumSamples(class GemPlayer * const this /* r30 */, class DataArray * seq_list /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8006B380 -> 0x8006B388
void GemPlayer::ResetDrumSamples() {}

// Range: 0x8006B388 -> 0x8006B3E4
void GemPlayer::ResetGemStates(class GemPlayer * const this /* r31 */) {}

enum State {
    kInit = 0,
    kBuffering = 1,
    kReady = 2,
    kPlaying = 3,
    kSuspended = 4,
    kStopped = 5,
    kFinished = 6,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class StreamReceiver * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class StreamReceiver * * _M_start; // offset 0x0, size 0x4
    class StreamReceiver * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class VarTimer {
    // total size: 0x40
    class Timer mRawTimer; // offset 0x0, size 0x38
    float mAccumMs; // offset 0x38, size 0x4
    float mSpeed; // offset 0x3C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct ChannelParams * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct ChannelParams * * _M_start; // offset 0x0, size 0x4
    struct ChannelParams * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    void * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    void * _M_start; // offset 0x0, size 0x4
    void * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    float * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    float * * _M_start; // offset 0x0, size 0x4
    float * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StandardStream : public Stream, public SynthPollable {
    // total size: 0x118
    enum State mState; // offset 0x14, size 0x4
    class File * mFile; // offset 0x18, size 0x4
    class StreamReader * mRdr; // offset 0x1C, size 0x4
    class vector mChannels; // offset 0x20, size 0xC
    int mSampleRate; // offset 0x2C, size 0x4
    float mBufSecs; // offset 0x30, size 0x4
    float mFileStartMs; // offset 0x34, size 0x4
    float mStartMs; // offset 0x38, size 0x4
    float mLastStreamTime; // offset 0x3C, size 0x4
    class VarTimer mTimer; // offset 0x40, size 0x40
    class vector mChanParams; // offset 0x80, size 0xC
    float mJumpFromMs; // offset 0x8C, size 0x4
    float mJumpToMs; // offset 0x90, size 0x4
    class String mJumpFile; // offset 0x94, size 0xC
    int mCurrentSamp; // offset 0xA0, size 0x4
    float mSpeed; // offset 0xA4, size 0x4
    class Timer mFrameTimer; // offset 0xA8, size 0x38
    float mThrottle; // offset 0xE0, size 0x4
    class Symbol mExt; // offset 0xE4, size 0x4
    unsigned char mFloatSamples; // offset 0xE8, size 0x1
    int mVirtualChans; // offset 0xEC, size 0x4
    class vector mVirtBufs; // offset 0xF0, size 0xC
    class vector mChanMaps; // offset 0xFC, size 0xC
    class vector mFloatBufferVector; // offset 0x108, size 0xC
};
// Range: 0x8006B3E4 -> 0x8006B630
void GemPlayer::SetPitchShiftRatio(class GemPlayer * const this /* r29 */, float ratio /* f31 */) {
    // Local variables
    class Stream * str; // r31
    class StandardStream * sstr; // r30
    class list chans; // r1+0x58
    struct _List_iterator itr; // r1+0x28
    unsigned int i; // r30
    class list chans; // r1+0x50
    unsigned long i; // r1+0x24

    // References
    // -> struct [anonymous] __RTTI__6Stream;
    // -> struct [anonymous] __RTTI__14StandardStream;
    // -> class Debug TheDebug;
}

// Range: 0x8006B630 -> 0x8006B660
unsigned char GemPlayer::HasDealtWithGem() {}

// Range: 0x8006B660 -> 0x8006B704
float GemPlayer::GetNotesHitFraction() {}

// Range: 0x8006B704 -> 0x8006B710
void GemPlayer::OnResetCodaPoints() {}

// Range: 0x8006B710 -> 0x8006B7B0
int GemPlayer::OnGetPercentHit(const class GemPlayer * const this /* r30 */) {
    // Local variables
    int total; // r0
    float fraction; // f1

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006B7B0 -> 0x8006B8C4
int GemPlayer::OnGetPercentHitSlots(const class GemPlayer * const this /* r31 */) {
    // Local variables
    unsigned char slotFlags; // r0
    const class vector & gemVec; // r0
    int totalCount; // r5
    int hitCount; // r6
    int i; // r7
    float fraction; // f1

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006B8C4 -> 0x8006BA60
float GemPlayer::OnGetPercentHitGemsPractice(const class GemPlayer * const this /* r26 */, int slotNum /* r27 */, float startMs /* f30 */, float endMs /* f31 */) {
    // Local variables
    const class vector & gemVec; // r0
    int totalCount; // r30
    int hitCount; // r29
    int i; // r28
    float gemStart; // f0
    float gemEnd; // f0
    float fraction; // f1

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006BA60 -> 0x8006BA90
unsigned char GemPlayer::OnGetGemResult() {}

// Range: 0x8006BA90 -> 0x8006BC34
unsigned char GemPlayer::OnGetGemIsSustained(class GemPlayer * const this /* r5 */, int ixGem /* r31 */) {
    // Local variables
    class vector gemVec; // r1+0x24

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P7GameGem;
    // -> unsigned char gStlAllocNameLookup;
    // -> class SongDB * TheSongDB;
}

struct {
    // total size: 0x8
} __RTTI__P7GameGem; // size: 0x8, address: 0x808764C0
// Range: 0x8006BC34 -> 0x8006BC3C
void GemPlayer::OnSetWhammyStarPowerEnabled() {}

// Range: 0x8006BC3C -> 0x8006BC44
void GemPlayer::OnSetMercurySwitchEnabled() {}

// Range: 0x8006BC44 -> 0x8006BC94
void GemPlayer::OnGameOver(class GemPlayer * const this /* r31 */) {}

// Range: 0x8006BC94 -> 0x8006BCB8
void GemPlayer::OnDisableController() {}

// Range: 0x8006BCB8 -> 0x8006BD54
void GemPlayer::OnRemoteHit(class GemPlayer * const this /* r29 */, int streak /* r30 */, int score /* r31 */, float crowd /* f31 */) {}

// Range: 0x8006BD54 -> 0x8006BDE4
void GemPlayer::OnRemotePenalize(class GemPlayer * const this /* r29 */, int streak /* r30 */, int score /* r31 */, float crowd /* f31 */) {}

// Range: 0x8006BDE4 -> 0x8006BDE8
void GemPlayer::OnRemoteFill() {}

// Range: 0x8006BDE8 -> 0x8006BE60
void GemPlayer::OnRemoteCodaHit(class GemPlayer * const this /* r30 */, int slot /* r31 */) {}

// Range: 0x8006BE60 -> 0x8006BE68
void GemPlayer::OnRemoteWhammy() {}

// Range: 0x8006BE68 -> 0x8006BEA4
void GemPlayer::OnRemoteHitLastCodaGem(class GemPlayer * const this /* r31 */) {}

// Range: 0x8006BEA4 -> 0x8006BEDC
void GemPlayer::OnRemoteBlowCoda(class GemPlayer * const this /* r31 */) {}

// Range: 0x8006BEDC -> 0x8006BEE4
void GemPlayer::OnStartStarpower() {}

// Range: 0x8006BEE4 -> 0x8006BEEC
void GemPlayer::OnStopStarpower() {}

// Range: 0x8006BEEC -> 0x8006BEF8
class SongPos & GemPlayer::GetSongPos() {}

// Range: 0x8006BEF8 -> 0x8006BF88
unsigned char GemPlayer::InFillNow(class GemPlayer * const this /* r29 */) {
    // Local variables
    int tick; // r30
}

// Range: 0x8006BF88 -> 0x8006BF8C
void GemPlayer::SetReverb() {}

// Range: 0x8006BF8C -> 0x8006C04C
void GemPlayer::GetPlayerState(const class GemPlayer * const this /* r29 */, struct PlayerState & state /* r30 */) {}

class TickedInfo {
    // total size: 0x10
    int mTick; // offset 0x0, size 0x4
    class String mInfo; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TickedInfo * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TickedInfo * _M_start; // offset 0x0, size 0x4
    class TickedInfo * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TickedInfoCollection {
    // total size: 0xC
    class vector mInfos; // offset 0x0, size 0xC
};
static class Message msg; // size: 0x8, address: 0x80977560
// Range: 0x8006C04C -> 0x8006C428
void GemPlayer::FillInProgress(class GemPlayer * const this /* r29 */, int slot /* r31 */) {
    // Local variables
    float now; // f0
    float rate; // f2
    int hit_slot; // r30
    float delta; // f0
    int pts; // r3

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8006C428 -> 0x8006C4B8
void GemPlayer::SendPenalize(class GemPlayer * const this /* r31 */) {}

// Range: 0x8006C4B8 -> 0x8006C600
void GemPlayer::Penalize(class GemPlayer * const this /* r29 */, float ms /* f31 */, int gem_id /* r30 */) {
    // Local variables
    int spotlight_gem_id; // r31
    float gem_ms; // f0

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006C600 -> 0x8006C698
void GemPlayer::CheckHeldNote(class GemPlayer * const this /* r31 */) {
    // Local variables
    float newPoints; // f1
}

// Range: 0x8006C698 -> 0x8006C86C
void GemPlayer::FinishHeldNote(class GemPlayer * const this /* r31 */) {
    // Local variables
    float fraction; // f31
    class Message msg; // r1+0x20

    // References
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x80977578
// Range: 0x8006C86C -> 0x8006CA9C
void GemPlayer::CheckSolo(class GemPlayer * const this /* r31 */) {
    // Local variables
    int start_tick; // r1+0x14
    int end_tick; // r1+0x10
    unsigned char tick_in_solo; // r0

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8006CA9C -> 0x8006CBAC
unsigned char GemPlayer::IsCodaMiss(class GemPlayer * const this /* r27 */) {
    // Local variables
    int coda_start_tick; // r31
    int now_tick; // r29
    class DrumFillInfo * fill_info; // r28
    struct FillExtent next_fill; // r1+0x18
    struct FillExtent first_coda_fill; // r1+0x10
    unsigned char any_fills; // r0
    unsigned char any_upcoming_fills; // r0
    struct FillExtent fillExtent; // r1+0x8

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006CBAC -> 0x8006CD70
void GemPlayer::AddHeadPoints(class GemPlayer * const this /* r27 */, float ms /* f31 */, int gem_id /* r6 */, enum HitType type /* r28 */) {
    // Local variables
    const class GameGem & gem; // r31
    int numSlots; // r30
    int points; // r29

    // References
    // -> class Scoring * TheScoring;
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006CD70 -> 0x8006D1A8
void GemPlayer::SetFilling(class GemPlayer * const this /* r28 */, unsigned char fill /* r29 */, int tick /* r30 */) {
    // Local variables
    class Message msg; // r1+0x58
    class Message msg; // r1+0x50
    class Message msg; // r1+0x48

    // References
    // -> class GameMode * TheGameMode;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8006D1A8 -> 0x8006D1B4
void GemPlayer::ForceFill() {}

// Range: 0x8006D1B4 -> 0x8006D1CC
unsigned char GemPlayer::ToggleNoFills() {}

static class Message msg; // size: 0x8, address: 0x80977590
static class Message send_solo_hit; // size: 0x8, address: 0x809775A8
// Range: 0x8006D1CC -> 0x8006D5C0
void GemPlayer::HandleSoloGem(class GemPlayer * const this /* r28 */, int gem_id /* r27 */, unsigned char hit /* r29 */, unsigned char solo_button /* r30 */) {
    // Local variables
    float percentage; // r1+0x1C
    int num_hittable; // r1+0x18
    const class vector & gems; // r0

    // References
    // -> static class Message send_solo_hit;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class SongDB * TheSongDB;
}

class GameGemInfo {
    // total size: 0x1
    unsigned char mPlayed; // offset 0x0, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class GameGemInfo * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class GameGemInfo * _M_start; // offset 0x0, size 0x4
    class GameGemInfo * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x8006D5C0 -> 0x8006D804
unsigned char GemPlayer::GetSoloData(class GemPlayer * const this /* r22 */, int tick /* r7 */, float & percentage /* r23 */, int & num_hittable /* r24 */) {
    // Local variables
    int phrase_start; // r1+0xC
    int phrase_end; // r1+0x8
    int first_gem; // [invalid]
    unsigned char separate_parts; // r0
    int num_hit; // r27
    int player_slot; // r26
    const class vector & gems; // r0
    const class vector & gem_infos; // r0
    int i; // r25

    // References
    // -> class GameMode * TheGameMode;
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006D804 -> 0x8006D874
void GemPlayer::LocalSoloStart(class GemPlayer * const this /* r31 */) {
    // Local variables
    class BandTrack * track; // r0
}

// Range: 0x8006D874 -> 0x8006D8B0
void GemPlayer::LocalSoloHit(int percentage /* r31 */) {
    // Local variables
    class BandTrack * track; // r0
}

static class Message send_solo_end; // size: 0x8, address: 0x809775C0
// Range: 0x8006D8B0 -> 0x8006DBBC
void GemPlayer::SoloEnd(class GemPlayer * const this /* r31 */) {
    // Local variables
    float percentage; // r1+0x14
    int num_hittable; // r1+0x10

    // References
    // -> static class Message send_solo_end;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8006DBBC -> 0x8006DCCC
void GemPlayer::LocalSoloEnd(class GemPlayer * const this /* r28 */, int percentage /* r29 */, int num_gems /* r30 */) {
    // Local variables
    int points_per_gem; // r1+0x14
    class Symbol result; // r1+0x10
    int points; // r30

    // References
    // -> class Scoring * TheScoring;
    // -> const char * gNullStr;
    // -> class GameMode * TheGameMode;
}

static class Message msg; // size: 0x8, address: 0x809775D8
// Range: 0x8006DCCC -> 0x8006DF3C
void GemPlayer::SetGuitarFx(class GemPlayer * const this /* r30 */) {
    // Local variables
    int pos; // r31

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameConfig * TheGameConfig;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x8006DF3C -> 0x8006DFB8
void GemPlayer::LocalSetGuitarFx(class GemPlayer * const this /* r31 */) {
    // Local variables
    int oldPos; // r5
}

// Range: 0x8006DFB8 -> 0x8006DFE0
void GemPlayer::HandleCommonPhraseNote(class GemPlayer * const this /* r8 */, int hit /* r7 */) {}

static class Message msg; // size: 0x8, address: 0x809775F0
// Range: 0x8006DFE0 -> 0x8006E244
void GemPlayer::SendWhammyBar(class GemPlayer * const this /* r31 */, float val /* f31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8006E244 -> 0x8006E3A0
unsigned char GemPlayer::AllCodaGemsHit(const class GemPlayer * const this /* r30 */) {
    // Local variables
    int coda_start_tick; // r0
    const class GameGemList & gems; // r0
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006E3A0 -> 0x8006E448
unsigned char GemPlayer::GetCodaFreestyleExtents(const class GemPlayer * const this /* r29 */, struct Extent & extent /* r30 */) {
    // Local variables
    int coda_start_tick; // r0
    class DrumFillInfo * fill_info; // r0

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006E448 -> 0x8006E4CC
void GemPlayer::CodaHit(class GemPlayer * const this /* r29 */, int gem_id /* r30 */) {}

// Range: 0x8006E4CC -> 0x8006E544
void GemPlayer::PrintMsg(class GemPlayer * const this /* r30 */, const char * msg /* r31 */) {
    // Local variables
    const char * fullMsg; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8006E544 -> 0x8006E5FC
void GemPlayer::PrintFinishHeldNote(class GemPlayer * const this /* r31 */) {
    // Local variables
    char multstr[5]; // r1+0x8
    int numSlots; // r5
    float tailFrac; // f1
}

// Range: 0x8006E5FC -> 0x8006E6B4
void GemPlayer::PrintAddHead(class GemPlayer * const this /* r26 */, int error /* r27 */, int points /* r28 */, int avgError /* r29 */, int midTermError /* r30 */, enum HitType type /* r31 */) {
    // Local variables
    char multstr[5]; // r1+0x8
    const char * hitstr; // r0

    // References
    // -> class Scoring * TheScoring;
}

// Range: 0x8006E6B4 -> 0x8006E824
void GemPlayer::ConfigureBehavior(class GemPlayer * const this /* r28 */) {
    // Local variables
    unsigned char starPowerEnabled; // r0
    unsigned char singleplayer; // r0
    enum TrackType track_type; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameMode * TheGameMode;
}

// Range: 0x8006E824 -> 0x8006E84C
unsigned char GemPlayer::SoloActive() {}

// Range: 0x8006E84C -> 0x8006E8CC
void GemPlayer::SetTargetGhostScore(class GemPlayer * const this /* r31 */, float target_score /* f31 */) {
    // Local variables
    int num_gems; // r0

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8006E8CC -> 0x8006E8F0
void GemPlayer::EnableController() {}

// Range: 0x8006E8F0 -> 0x8006E8F4
void GemPlayer::DisableController() {}

static class Symbol _s; // size: 0x4, address: 0x80A499A0
static class Symbol _s; // size: 0x4, address: 0x80A499A8
static class Symbol _s; // size: 0x4, address: 0x80A499B0
static class Symbol _s; // size: 0x4, address: 0x80A499B8
static class Symbol _s; // size: 0x4, address: 0x80A499C0
static class Symbol _s; // size: 0x4, address: 0x80A499C8
static class Symbol _s; // size: 0x4, address: 0x80A499D0
static class Symbol _s; // size: 0x4, address: 0x80A499D8
static class Symbol _s; // size: 0x4, address: 0x80A499E0
static class Symbol _s; // size: 0x4, address: 0x80A499E8
static class Symbol _s; // size: 0x4, address: 0x80A499F0
static class Symbol _s; // size: 0x4, address: 0x80A499F8
static class Symbol _s; // size: 0x4, address: 0x80A49A00
static class Symbol _s; // size: 0x4, address: 0x80A49A08
static class Symbol _s; // size: 0x4, address: 0x80A49A10
static class Symbol _s; // size: 0x4, address: 0x80A49A18
static class Symbol _s; // size: 0x4, address: 0x80A49A20
static class Symbol _s; // size: 0x4, address: 0x80A49A28
static class Symbol _s; // size: 0x4, address: 0x80A49A30
static class Symbol _s; // size: 0x4, address: 0x80A49A38
static class Symbol _s; // size: 0x4, address: 0x80A49A40
static class Symbol _s; // size: 0x4, address: 0x80A49A48
static class Symbol _s; // size: 0x4, address: 0x80A49A50
static class Symbol _s; // size: 0x4, address: 0x80A49A58
static class Symbol _s; // size: 0x4, address: 0x80A49A60
static class Symbol _s; // size: 0x4, address: 0x80A49A68
static class Symbol _s; // size: 0x4, address: 0x80A49A70
static class Symbol _s; // size: 0x4, address: 0x80A49A78
static class Symbol _s; // size: 0x4, address: 0x80A49A80
static class Symbol _s; // size: 0x4, address: 0x80A49A88
static class Symbol _s; // size: 0x4, address: 0x80A49A90
static class Symbol _s; // size: 0x4, address: 0x80A49A98
static class Symbol _s; // size: 0x4, address: 0x80A49AA0
static class Symbol _s; // size: 0x4, address: 0x80A49AA8
static class Symbol _s; // size: 0x4, address: 0x80A49AB0
static class Symbol _s; // size: 0x4, address: 0x80A49AB8
static class Symbol _s; // size: 0x4, address: 0x80A49AC0
static class Symbol _s; // size: 0x4, address: 0x80A49AC8
static class Symbol _s; // size: 0x4, address: 0x80A49AD0
static class Symbol _s; // size: 0x4, address: 0x80A49AD8
static class Symbol _s; // size: 0x4, address: 0x80A49AE0
static class Symbol _s; // size: 0x4, address: 0x80A49AE8
static class Symbol _s; // size: 0x4, address: 0x80A49AF0
static class Symbol _s; // size: 0x4, address: 0x80A49AF8
static class Symbol _s; // size: 0x4, address: 0x80A49B00
static class Symbol _s; // size: 0x4, address: 0x80A49B08
static class Symbol _s; // size: 0x4, address: 0x80A49B10
static class Symbol _s; // size: 0x4, address: 0x80A49B18
// Range: 0x8006E8F4 -> 0x8006FEE8
class DataNode GemPlayer::Handle(class GemPlayer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x1C
    class MessageTimer _mt; // r1+0x28
    class DataNode _n; // r1+0x20

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class SongDB * TheSongDB;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

class TrackWatcherParent {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class BeatMatchControllerSink {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TrackWatcher * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TrackWatcher * * _M_start; // offset 0x0, size 0x4
    class TrackWatcher * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PhraseCatcher * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PhraseCatcher * * _M_start; // offset 0x0, size 0x4
    class PhraseCatcher * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BarFinder * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BarFinder * * _M_start; // offset 0x0, size 0x4
    class BarFinder * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PhraseFinder * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PhraseFinder * * _M_start; // offset 0x0, size 0x4
    class PhraseFinder * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PhraseCapturer * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PhraseCapturer * * _M_start; // offset 0x0, size 0x4
    class PhraseCapturer * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum BeatmatchTrackType {
    kDrums = 0,
    kGuitar = 1,
    kVocals = 2,
    kMisc = 3,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    enum BeatmatchTrackType * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    enum BeatmatchTrackType * _M_start; // offset 0x0, size 0x4
    enum BeatmatchTrackType * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class BeatMatcher : public TrackWatcherParent, public BeatMatchControllerSink {
    // total size: 0xD8
    unsigned char mWaitingForAudio; // offset 0x8, size 0x1
    int mPlayerNum; // offset 0xC, size 0x4
    int mPlayerSlot; // offset 0x10, size 0x4
    int mNumPlayers; // offset 0x14, size 0x4
    class Symbol mControllerType; // offset 0x18, size 0x4
    class SongData * mSongData; // offset 0x1C, size 0x4
    class DataArray * mCfg; // offset 0x20, size 0x4
    class DataArray * mSongCfg; // offset 0x24, size 0x4
    class BeatMatchSink * mSink; // offset 0x28, size 0x4
    class MasterAudio * mAudio; // offset 0x2C, size 0x4
    class BeatMatchController * mController; // offset 0x30, size 0x4
    class MercurySwitchFilter * mMercurySwitchFilter; // offset 0x34, size 0x4
    class vector mWatchers; // offset 0x38, size 0xC
    class vector mCatchers; // offset 0x44, size 0xC
    class vector mBarFinders; // offset 0x50, size 0xC
    class vector mPhraseFinders; // offset 0x5C, size 0xC
    class vector mPhraseCapturers; // offset 0x68, size 0xC
    class vector mTrackTypes; // offset 0x74, size 0xC
    class DrumPlayer * mDrumPlayer; // offset 0x80, size 0x4
    int mCurTrack; // offset 0x84, size 0x4
    unsigned char mEnabled; // offset 0x88, size 0x1
    class SongPos mSongPos; // offset 0x8C, size 0x14
    float mNow; // offset 0xA0, size 0x4
    int mTick; // offset 0xA4, size 0x4
    float mLastSwing; // offset 0xA8, size 0x4
    float mLastReleaseSwing; // offset 0xAC, size 0x4
    unsigned char mLastDirection; // offset 0xB0, size 0x1
    int mLastVelocityBucket; // offset 0xB4, size 0x4
    float mRawMercurySwitchState; // offset 0xB8, size 0x4
    unsigned char mMercurySwitchState; // offset 0xBC, size 0x1
    unsigned char mForceMercurySwitch; // offset 0xBD, size 0x1
    float mSyncOffset; // offset 0xC0, size 0x4
    unsigned char mDrivingPitchBendExternally; // offset 0xC4, size 0x1
    int mFillStartTick; // offset 0xC8, size 0x4
    int mCodaStartTick; // offset 0xCC, size 0x4
    unsigned char mInCoda; // offset 0xD0, size 0x1
    unsigned char mCheating; // offset 0xD1, size 0x1
    unsigned char mForceFill; // offset 0xD2, size 0x1
    unsigned char mNoFills; // offset 0xD3, size 0x1
    unsigned char mFillAudio; // offset 0xD4, size 0x1
    unsigned char mEnableWhammy; // offset 0xD5, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__14StandardStream; // size: 0x8, address: 0x80876A08
class FxSendEQ : public FxSend {
    // total size: 0x6C
protected:
    float mHighFreqCutoff; // offset 0x50, size 0x4
    float mHighFreqGain; // offset 0x54, size 0x4
    float mMidFreqCutoff; // offset 0x58, size 0x4
    float mMidFreqBandwidth; // offset 0x5C, size 0x4
    float mMidFreqGain; // offset 0x60, size 0x4
    float mLowFreqCutoff; // offset 0x64, size 0x4
    float mLowFreqGain; // offset 0x68, size 0x4
};
struct {
    // total size: 0x2A8
} __vt__9GemPlayer; // size: 0x2A8, address: 0x80876A10
struct {
    // total size: 0x8
} __RTTI__8FxSendEQ; // size: 0x8, address: 0x80876D88
struct {
    // total size: 0x8
} __RTTI__16FxSendPitchShift; // size: 0x8, address: 0x80876DC0
struct {
    // total size: 0x8
} __RTTI__6Stream; // size: 0x8, address: 0x80876DD0
struct {
    // total size: 0x68
} __vt__13BeatMatchSink; // size: 0x68, address: 0x80876DD8
struct {
    // total size: 0x8
} __RTTI__6FxSend; // size: 0x8, address: 0x80876F10
struct {
    // total size: 0x8
} __RTTI__PUc; // size: 0x8, address: 0x80876FE8
struct _OKToMemCpy {
    // total size: 0x1
};
struct BeatData {
    // total size: 0x24
    class Symbol mName; // offset 0x0, size 0x4
    int mStartTick; // offset 0x4, size 0x4
    int mEndTick; // offset 0x8, size 0x4
    float mTrackSpeed; // offset 0xC, size 0x4
    int mFillStartTick; // offset 0x10, size 0x4
    int mFillEndTick; // offset 0x14, size 0x4
    int mNumNotes; // offset 0x18, size 0x4
    int mNumFillNotes; // offset 0x1C, size 0x4
    unsigned char mDisco; // offset 0x20, size 0x1
    unsigned char mTom; // offset 0x21, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BeatData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BeatData * _M_start; // offset 0x0, size 0x4
    struct BeatData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct TabData {
    // total size: 0xC
    unsigned char mKick; // offset 0x0, size 0x1
    float mFrame; // offset 0x4, size 0x4
    int mSlot; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct TabData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct TabData * _M_start; // offset 0x0, size 0x4
    struct TabData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class DrumTrainerPanel : public UIPanel {
    // total size: 0xDC
    int mWritePos; // offset 0x30, size 0x4
    int mBeatIndex; // offset 0x34, size 0x4
    int mBeat; // offset 0x38, size 0x4
    int mBPM; // offset 0x3C, size 0x4
    unsigned char mMetronomeState; // offset 0x40, size 0x1
    unsigned char mRenderBeatMask; // offset 0x41, size 0x1
    int mEndBeatMaskTick; // offset 0x44, size 0x4
    int mDelayedMaskAdd; // offset 0x48, size 0x4
    int mHasBeats; // offset 0x4C, size 0x4
    int mUpdateScoreTick; // offset 0x50, size 0x4
    int mUpdateScoreGem; // offset 0x54, size 0x4
    int mFirstGemTick; // offset 0x58, size 0x4
    class vector mBeatData; // offset 0x5C, size 0xC
    class RndGroup * mTabKickGroup; // offset 0x68, size 0x4
    class RndGroup * mTabNoteGroup; // offset 0x6C, size 0x4
    class RndAnimatable * mTabColorAnim; // offset 0x70, size 0x4
    class RndAnimatable * mTabInfoAnim; // offset 0x74, size 0x4
    class RndAnimatable * mTabLaneAnim; // offset 0x78, size 0x4
    class RndAnimatable * mTabKickTimeAnim; // offset 0x7C, size 0x4
    class RndAnimatable * mTabNoteTimeAnim; // offset 0x80, size 0x4
    class RndAnimatable * mFlipAnim; // offset 0x84, size 0x4
    class vector mTabData; // offset 0x88, size 0xC
    float mTrackSpeedModifier0; // offset 0x94, size 0x4
    float mTrackSpeedModifier1; // offset 0x98, size 0x4
    class MultiTempoTempoMap * mTempoMap; // offset 0x9C, size 0x4
    class GemTrack * mTrack; // offset 0xA0, size 0x4
    class GemManager * mGemManager; // offset 0xA4, size 0x4
    class GemPlayer * mGemPlayer; // offset 0xA8, size 0x4
    class DrumFillInfo * mFillInfo; // offset 0xAC, size 0x4
};
struct AXFX_BUS {
    // total size: 0xC
    long * left; // offset 0x0, size 0x4
    long * right; // offset 0x4, size 0x4
    long * surround; // offset 0x8, size 0x4
};
struct AXFX_REVERBHI_EXP {
    // total size: 0x148
    float * earlyLine[3]; // offset 0x0, size 0xC
    unsigned long earlyPos[3]; // offset 0xC, size 0xC
    unsigned long earlyLength; // offset 0x18, size 0x4
    unsigned long earlyMaxLength; // offset 0x1C, size 0x4
    float earlyCoef[3]; // offset 0x20, size 0xC
    float * preDelayLine[3]; // offset 0x2C, size 0xC
    unsigned long preDelayPos; // offset 0x38, size 0x4
    unsigned long preDelayLength; // offset 0x3C, size 0x4
    unsigned long preDelayMaxLength; // offset 0x40, size 0x4
    float * combLine[3][3]; // offset 0x44, size 0x24
    unsigned long combPos[3]; // offset 0x68, size 0xC
    unsigned long combLength[3]; // offset 0x74, size 0xC
    unsigned long combMaxLength[3]; // offset 0x80, size 0xC
    float combCoef[3]; // offset 0x8C, size 0xC
    float * allpassLine[3][2]; // offset 0x98, size 0x18
    unsigned long allpassPos[2]; // offset 0xB0, size 0x8
    unsigned long allpassLength[2]; // offset 0xB8, size 0x8
    unsigned long allpassMaxLength[2]; // offset 0xC0, size 0x8
    float * lastAllpassLine[3]; // offset 0xC8, size 0xC
    unsigned long lastAllpassPos[3]; // offset 0xD4, size 0xC
    unsigned long lastAllpassLength[3]; // offset 0xE0, size 0xC
    unsigned long lastAllpassMaxLength[3]; // offset 0xEC, size 0xC
    float allpassCoef; // offset 0xF8, size 0x4
    float lastLpfOut[3]; // offset 0xFC, size 0xC
    float lpfCoef; // offset 0x108, size 0x4
    unsigned long active; // offset 0x10C, size 0x4
    unsigned long earlyMode; // offset 0x110, size 0x4
    float preDelayTimeMax; // offset 0x114, size 0x4
    float preDelayTime; // offset 0x118, size 0x4
    unsigned long fusedMode; // offset 0x11C, size 0x4
    float fusedTime; // offset 0x120, size 0x4
    float coloration; // offset 0x124, size 0x4
    float damping; // offset 0x128, size 0x4
    float crosstalk; // offset 0x12C, size 0x4
    float earlyGain; // offset 0x130, size 0x4
    float fusedGain; // offset 0x134, size 0x4
    struct AXFX_BUS * busIn; // offset 0x138, size 0x4
    struct AXFX_BUS * busOut; // offset 0x13C, size 0x4
    float outGain; // offset 0x140, size 0x4
    float sendGain; // offset 0x144, size 0x4
};
struct AXFX_REVERBHI {
    // total size: 0x160
    struct AXFX_REVERBHI_EXP reverbInner; // offset 0x0, size 0x148
    float coloration; // offset 0x148, size 0x4
    float mix; // offset 0x14C, size 0x4
    float time; // offset 0x150, size 0x4
    float damping; // offset 0x154, size 0x4
    float preDelay; // offset 0x158, size 0x4
    float crosstalk; // offset 0x15C, size 0x4
};
struct AXFX_DELAY {
    // total size: 0x64
    long * line[3]; // offset 0x0, size 0xC
    unsigned long curPos[3]; // offset 0xC, size 0xC
    unsigned long length[3]; // offset 0x18, size 0xC
    long feedbackGain[3]; // offset 0x24, size 0xC
    long outGain[3]; // offset 0x30, size 0xC
    unsigned long active; // offset 0x3C, size 0x4
    unsigned long delay[3]; // offset 0x40, size 0xC
    unsigned long feedback[3]; // offset 0x4C, size 0xC
    unsigned long output[3]; // offset 0x58, size 0xC
};
struct AXFX_CHORUS_EXP_DELAY {
    // total size: 0x20
    float * line[3]; // offset 0x0, size 0xC
    unsigned long inPos; // offset 0xC, size 0x4
    unsigned long outPos; // offset 0x10, size 0x4
    unsigned long lastPos; // offset 0x14, size 0x4
    unsigned long sizeFP; // offset 0x18, size 0x4
    unsigned long size; // offset 0x1C, size 0x4
};
struct AXFX_CHORUS_EXP_LFO {
    // total size: 0x28
    long * table; // offset 0x0, size 0x4
    long phaseAdd; // offset 0x4, size 0x4
    long stepSamp; // offset 0x8, size 0x4
    long depthSamp; // offset 0xC, size 0x4
    unsigned long phase; // offset 0x10, size 0x4
    unsigned long sign; // offset 0x14, size 0x4
    unsigned long lastNum; // offset 0x18, size 0x4
    long lastValue; // offset 0x1C, size 0x4
    long grad; // offset 0x20, size 0x4
    long gradFactor; // offset 0x24, size 0x4
};
struct AXFX_CHORUS_EXP {
    // total size: 0xA0
    struct AXFX_CHORUS_EXP_DELAY delay; // offset 0x0, size 0x20
    struct AXFX_CHORUS_EXP_LFO lfo; // offset 0x20, size 0x28
    float history[3][4]; // offset 0x48, size 0x30
    unsigned long histIndex; // offset 0x78, size 0x4
    unsigned long active; // offset 0x7C, size 0x4
    float delayTime; // offset 0x80, size 0x4
    float depth; // offset 0x84, size 0x4
    float rate; // offset 0x88, size 0x4
    float feedback; // offset 0x8C, size 0x4
    struct AXFX_BUS * busIn; // offset 0x90, size 0x4
    struct AXFX_BUS * busOut; // offset 0x94, size 0x4
    float outGain; // offset 0x98, size 0x4
    float sendGain; // offset 0x9C, size 0x4
};
struct AXFX_CHORUS {
    // total size: 0xAC
    struct AXFX_CHORUS_EXP chorusInner; // offset 0x0, size 0xA0
    unsigned long baseDelay; // offset 0xA0, size 0x4
    unsigned long variation; // offset 0xA4, size 0x4
    unsigned long period; // offset 0xA8, size 0x4
};
class WiiFX {
    // total size: 0x3B4
    class DataArray * FXconfig; // offset 0x0, size 0x4
    struct AXFX_REVERBHI reverbSetting; // offset 0x4, size 0x160
    struct AXFX_DELAY delaySetting; // offset 0x164, size 0x64
    struct AXFX_CHORUS chorusSetting; // offset 0x1C8, size 0xAC
    struct AXFX_CHORUS_EXP flangerSetting; // offset 0x274, size 0xA0
    struct AXFX_CHORUS_EXP wahSetting; // offset 0x314, size 0xA0
};

