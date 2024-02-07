/*
    Compile unit: C:\rockband2\system\src\beatmatch\TrackWatcher.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80303CA0 -> 0x8030437C
*/
static class Symbol guitar; // size: 0x4, address: 0x80A5079C
static class Symbol joypad; // size: 0x4, address: 0x80A507A4
static class Symbol joypad_guitar; // size: 0x4, address: 0x80A507AC
// Range: 0x80303CA0 -> 0x80303DC4
class Symbol ControllerTypeToTrackWatcherType(class Symbol & controller_type /* r28 */) {
    // Local variables
    class DataArray * ctrl_cfg; // r0
    class Symbol instrument; // r1+0x20

    // References
    // -> static class Symbol joypad_guitar;
    // -> static class Symbol joypad;
    // -> static class Symbol guitar;
}

static class Symbol guitar; // size: 0x4, address: 0x80A507B4
static class Symbol joypad; // size: 0x4, address: 0x80A507BC
// Range: 0x80303DC4 -> 0x80303F94
class TrackWatcherImpl * NewTrackWatcherImpl(int track /* r23 */, unsigned char independent_slots /* r24 */, int player_num /* r25 */, int player_slot /* r26 */, class Symbol & controller_type /* r21 */, class SongData * song_data /* r27 */, class TrackWatcherParent * parent /* r28 */, class DataArray * cfg /* r29 */, class DataArray * song_cfg /* r30 */) {
    // Local variables
    class Symbol type; // r1+0x1C
    class GameGemList * gems; // r22
    class GameGemInfoList * gem_infos; // r21

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol joypad;
    // -> static class Symbol guitar;
}

// Range: 0x80303F94 -> 0x80304010
void * TrackWatcher::TrackWatcher(class TrackWatcher * const this /* r31 */, class DataArray * cfg /* r12 */, class DataArray * song_cfg /* r11 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x80304010 -> 0x803040C0
void * TrackWatcher::~TrackWatcher(class TrackWatcher * const this /* r30 */) {}

// Range: 0x803040C0 -> 0x803040CC
void TrackWatcher::ReplaceImpl() {}

class TrackWatcherState {
    // total size: 0x58
public:
    int mLastGemHit; // offset 0x0, size 0x4
    int mAutoCaptureUntil; // offset 0x4, size 0x4
    unsigned char mAutoplayCoda; // offset 0x8, size 0x1
    unsigned char mIsCurrentTrack; // offset 0x9, size 0x1
    int mGemInProgress; // offset 0xC, size 0x4
    float mGemInProgressEndMs; // offset 0x10, size 0x4
    float mSyncOffset; // offset 0x14, size 0x4
    class PhraseCatcher * mCatcher; // offset 0x18, size 0x4
    int mTrack; // offset 0x1C, size 0x4
    unsigned char mEnabled; // offset 0x20, size 0x1
    int mLastGemPassed; // offset 0x24, size 0x4
    int mLastGemSeen; // offset 0x28, size 0x4
    float mLastMiss; // offset 0x2C, size 0x4
    unsigned char mCheating; // offset 0x30, size 0x1
    int mCheatError; // offset 0x34, size 0x4
    int mNextCheatError; // offset 0x38, size 0x4
    int mNextGemToAutoplay; // offset 0x3C, size 0x4
    unsigned char mPitchBendReady; // offset 0x40, size 0x1
    int mPitchBendRange; // offset 0x44, size 0x4
    int mPitchBendMsToFull; // offset 0x48, size 0x4
    float mPitchBendMsHit; // offset 0x4C, size 0x4
    float mBiggestWhammy; // offset 0x50, size 0x4
    unsigned char mCanSwitchTracks; // offset 0x54, size 0x1
    unsigned char mSucceeding; // offset 0x55, size 0x1
};
// Range: 0x803040CC -> 0x803041DC
void TrackWatcher::SetImpl(class TrackWatcher * const this /* r29 */) {
    // Local variables
    class TrackWatcherState state; // r1+0x18
    unsigned char saved_state; // r31
    int i; // r30
}

// Range: 0x803041DC -> 0x803041F0
void TrackWatcher::SetIsCurrentTrack() {}

// Range: 0x803041F0 -> 0x80304284
void TrackWatcher::AddSink(class TrackWatcher * const this /* r31 */, class BeatMatchSink * sink /* r1+0x8 */) {}

// Range: 0x80304284 -> 0x80304298
void TrackWatcher::SetCatcher() {}

// Range: 0x80304298 -> 0x803042AC
void TrackWatcher::Poll() {}

// Range: 0x803042AC -> 0x803042C0
void TrackWatcher::Jump() {}

// Range: 0x803042C0 -> 0x803042D4
unsigned char TrackWatcher::Swing() {}

// Range: 0x803042D4 -> 0x803042E8
void TrackWatcher::NonStrumSwing() {}

// Range: 0x803042E8 -> 0x803042FC
void TrackWatcher::FretButtonDown() {}

// Range: 0x803042FC -> 0x80304310
void TrackWatcher::FretButtonUp() {}

// Range: 0x80304310 -> 0x80304324
void TrackWatcher::AutoCapture() {}

// Range: 0x80304324 -> 0x80304338
void TrackWatcher::Enable() {}

// Range: 0x80304338 -> 0x8030434C
void TrackWatcher::SetCheating() {}

// Range: 0x8030434C -> 0x80304360
void TrackWatcher::SetAutoplayError() {}

// Range: 0x80304360 -> 0x80304368
void TrackWatcher::SetAutoplayCoda() {}

// Range: 0x80304368 -> 0x8030437C
void TrackWatcher::SetSyncOffset() {}

struct {
    // total size: 0x8
} __RTTI__PP13BeatMatchSink; // size: 0x8, address: 0x808CE2A8

