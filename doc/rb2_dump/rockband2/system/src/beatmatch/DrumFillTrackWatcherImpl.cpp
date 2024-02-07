/*
    Compile unit: C:\rockband2\system\src\beatmatch\DrumFillTrackWatcherImpl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802D8830 -> 0x802D8C18
*/
class DrumFillTrackWatcherImpl : public DrumTrackWatcherImpl {
    // total size: 0xA0
    class DataArray * mFillCfg; // offset 0x94, size 0x4
    class DrumFillInfo * mFillInfo; // offset 0x98, size 0x4
    int mFillNotes; // offset 0x9C, size 0x4
};
// Range: 0x802D8830 -> 0x802D88C8
void * DrumFillTrackWatcherImpl::DrumFillTrackWatcherImpl(class DrumFillTrackWatcherImpl * const this /* r29 */, int track /* r30 */, class DataArray * cfg /* r0 */, class DataArray * song_cfg /* r31 */) {
    // References
    // -> struct [anonymous] __vt__24DrumFillTrackWatcherImpl;
}

// Range: 0x802D88C8 -> 0x802D8924
void * DrumFillTrackWatcherImpl::~DrumFillTrackWatcherImpl(class DrumFillTrackWatcherImpl * const this /* r30 */) {}

// Range: 0x802D8924 -> 0x802D893C
void DrumFillTrackWatcherImpl::CodaSwing() {}

// Range: 0x802D893C -> 0x802D8B24
void DrumFillTrackWatcherImpl::FillSwing(class DrumFillTrackWatcherImpl * const this /* r27 */, int tick /* r28 */, int slot /* r29 */, int gem_id /* r30 */, unsigned char at_end /* r31 */) {
    // Local variables
    int lanes; // r0
    int bucket; // r24
    class BeatMatchSink * * it; // r24
    class BeatMatchSink * * it; // r24
}

// Range: 0x802D8B24 -> 0x802D8B94
void DrumFillTrackWatcherImpl::ResetFill(class DrumFillTrackWatcherImpl * const this /* r30 */) {
    // Local variables
    class BeatMatchSink * * it; // r31
}

// Range: 0x802D8B94 -> 0x802D8C18
void DrumFillTrackWatcherImpl::RegisterFill(class DrumFillTrackWatcherImpl * const this /* r29 */, int tick /* r30 */) {
    // Local variables
    class BeatMatchSink * * it; // r31
}

class TrackWatcherImpl {
    // total size: 0x90
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    int mPlayerNum; // offset 0x4, size 0x4
    int mPlayerSlot; // offset 0x8, size 0x4
    class GameGemList * mGemList; // offset 0xC, size 0x4
    class GameGemInfoList * mGemInfoList; // offset 0x10, size 0x4
    class TrackWatcherParent * mParent; // offset 0x14, size 0x4
    float mSlop; // offset 0x18, size 0x4
    int mLastGemHit; // offset 0x1C, size 0x4
    int mAutoCaptureUntil; // offset 0x20, size 0x4
    unsigned char mIsCurrentTrack; // offset 0x24, size 0x1
    int mGemInProgress; // offset 0x28, size 0x4
    float mGemInProgressEndMs; // offset 0x2C, size 0x4
    float mSyncOffset; // offset 0x30, size 0x4
    unsigned char mSucceeding; // offset 0x34, size 0x1
    unsigned char mEnabled; // offset 0x35, size 0x1
    class vector mSinks; // offset 0x38, size 0xC
    class SongData * mSongData; // offset 0x44, size 0x4
private:
    class PhraseCatcher * mCatcher; // offset 0x48, size 0x4
    int mTrack; // offset 0x4C, size 0x4
    unsigned char mButtonMashingMode; // offset 0x50, size 0x1
    int mLastGemPassed; // offset 0x54, size 0x4
    int mLastGemSeen; // offset 0x58, size 0x4
    float mLastMiss; // offset 0x5C, size 0x4
    unsigned char mCheating; // offset 0x60, size 0x1
    unsigned char mAutoplayCoda; // offset 0x61, size 0x1
    int mCheatError; // offset 0x64, size 0x4
    int mNextCheatError; // offset 0x68, size 0x4
    float mLastCheatCodaSwing; // offset 0x6C, size 0x4
    int mNextGemToAutoplay; // offset 0x70, size 0x4
    float mAutoplayAccuracy; // offset 0x74, size 0x4
    unsigned char mPitchBendReady; // offset 0x78, size 0x1
    int mPitchBendRange; // offset 0x7C, size 0x4
    int mPitchBendMsToFull; // offset 0x80, size 0x4
    float mPitchBendMsHit; // offset 0x84, size 0x4
    float mBiggestWhammy; // offset 0x88, size 0x4
    unsigned char mCanSwitchTracks; // offset 0x8C, size 0x1
};
class DrumTrackWatcherImpl : public TrackWatcherImpl {
    // total size: 0x94
    int mNextKickGemToAutoplay; // offset 0x90, size 0x4
};
struct {
    // total size: 0x90
} __vt__24DrumFillTrackWatcherImpl; // size: 0x90, address: 0x808CAA68
struct {
    // total size: 0x8
} __RTTI__24DrumFillTrackWatcherImpl; // size: 0x8, address: 0x808CAB28
struct {
    // total size: 0x8
} __RTTI__20DrumTrackWatcherImpl; // size: 0x8, address: 0x808CAB58
struct {
    // total size: 0x8
} __RTTI__16TrackWatcherImpl; // size: 0x8, address: 0x808CAB78

