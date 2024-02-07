/*
    Compile unit: C:\rockband2\band2\src\bandtrack\GemManager.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80017950 -> 0x80019A0C
*/
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class GemSmasher * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class GemSmasher * * _M_start; // offset 0x0, size 0x4
    class GemSmasher * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class NowBar {
    // total size: 0x18
    class vector mSmashers; // offset 0x0, size 0xC
    int mCurrentGem; // offset 0xC, size 0x4
    unsigned char mBurning; // offset 0x10, size 0x1
    const class TrackConfig & mTrackCfg; // offset 0x14, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct HitGem _M_data; // offset 0x8, size 0x8
};
// Range: 0x80017950 -> 0x80017B20
void * GemManager::~GemManager(class GemManager * const this /* r30 */) {}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class GameGem * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class GameGem * _M_start; // offset 0x0, size 0x4
    class GameGem * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TickedInfo {
    // total size: 0x8
    int mTick; // offset 0x0, size 0x4
    int mInfo; // offset 0x4, size 0x4
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
struct FillExtent {
    // total size: 0x8
    int start; // offset 0x0, size 0x4
    int end; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct FillExtent * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct FillExtent * _M_start; // offset 0x0, size 0x4
    struct FillExtent * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class FillInfo {
    // total size: 0x1C
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class TickedInfoCollection mLanes; // offset 0x4, size 0xC
    class vector mFills; // offset 0x10, size 0xC
};
struct _OKToMemCpy {
    // total size: 0x1
};
// Range: 0x80017B20 -> 0x80017C0C
void GemManager::SetSlotRoll(class GemManager * const this /* r7 */, float roll /* f31 */) {}

// Range: 0x80017C0C -> 0x80017D58
float GemManager::SlotRoll(class GemManager * const this /* r8 */) {}

// Range: 0x80017D58 -> 0x80017D60
void GemManager::SetGemsEnabled() {}

static class Message msg; // size: 0x8, address: 0x80976B60
static class Symbol crash; // size: 0x4, address: 0x80A48F1C
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80017D60 -> 0x800182E8
void GemManager::UpdateLeftyFlip(class GemManager * const this /* r29 */) {
    // Local variables
    class RndDir * nowBarDir; // r30
    class Symbol gems; // r1+0x50
    class Symbol widName; // r1+0x4C
    float crashY; // f31
    struct _List_iterator it; // r1+0x48
    class Transform xfm; // r1+0x80

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
    // -> static class Symbol crash;
    // -> const char * gNullStr;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndMat * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
// Range: 0x800182E8 -> 0x80018444
void GemManager::UpdateSlotPositions(class GemManager * const this /* r29 */) {
    // Local variables
    class Transform t; // r1+0x30
    int i; // r30
    class RndDir * smasherDir; // r0
    struct SlotPosition sp; // r1+0x18
    class Vector3 rotation; // r1+0x20
}

class GemSmasher {
    // total size: 0xC
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    int mSlot; // offset 0x4, size 0x4
    class RndDir * mDir; // offset 0x8, size 0x4
};
// Range: 0x80018444 -> 0x80018538
class RndDir * GemManager::NowBarDir(class GemManager * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndDir;
}

// Range: 0x80018538 -> 0x800186F0
void GemManager::Poll(class GemManager * const this /* r30 */, float ms /* f30 */, const struct PlayerState & state /* r31 */) {
    // Local variables
    float topSeconds; // f31
}

// Range: 0x800186F0 -> 0x8001877C
void GemManager::PollVisibleGems(class GemManager * const this /* r30 */, float ms /* f30 */, float whammy /* f31 */) {
    // Local variables
    int i; // r31
}

// Range: 0x8001877C -> 0x800187C4
void GemManager::AdvanceBegin(class GemManager * const this /* r31 */) {}

// Range: 0x800187C4 -> 0x800188DC
void GemManager::AdvanceEnd(class GemManager * const this /* r27 */) {
    // Local variables
    class Symbol type; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x800188DC -> 0x800189F4
void GemManager::PollHitGems(class GemManager * const this /* r30 */, float ms /* f30 */) {
    // Local variables
    float clip; // f31
    struct _List_iterator it; // r1+0x10
    float elapsedMs; // f0
}

// Range: 0x800189F4 -> 0x80018AA4
void GemManager::ReleaseHitGems(class GemManager * const this /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x10
}

// Range: 0x80018AA4 -> 0x80018B38
void GemManager::PruneHitGems(class GemManager * const this /* r31 */, float ms /* f31 */) {}

static unsigned char sUnison; // size: 0x1, address: 0x80A48F20
// Range: 0x80018B38 -> 0x80018C58
void GemManager::Hit(class GemManager * const this /* r29 */, float ms /* f31 */, int gem_id /* r30 */, int hit_flags /* r31 */) {
    // References
    // -> static unsigned char sUnison;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std33_List_node<Q210GemManager6HitGem>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std33_List_node<Q210GemManager6HitGem>; // size: 0x8, address: 0x8086DB00
// Range: 0x80018C58 -> 0x80018C68
void GemManager::Pass() {}

// Range: 0x80018C68 -> 0x80018C8C
void GemManager::Ignore() {}

// Range: 0x80018C8C -> 0x80018D3C
void GemManager::Released(class GemManager * const this /* r30 */, float ms /* f31 */) {}

// Range: 0x80018D3C -> 0x80018D44
void GemManager::SetSmasherGlowing() {}

// Range: 0x80018D44 -> 0x80018D4C
void GemManager::PopSmasher() {}

// Range: 0x80018D4C -> 0x80018D9C
class Object * GemManager::GetSmasherObj() {
    // Local variables
    class GemSmasher * smasher; // r0
}

enum PhraseState {
    kPhraseNone = 0,
    kPhraseMissed = 1,
    kPhraseHitting = 2,
    kPhraseComplete = 3,
};
struct PlayerState {
    // total size: 0x18
    unsigned char warning; // offset 0x0, size 0x1
    unsigned char starPowerReady; // offset 0x1, size 0x1
    float whammy; // offset 0x4, size 0x4
    unsigned char whammyActive; // offset 0x8, size 0x1
    enum PhraseState phraseState; // offset 0xC, size 0x4
    float fillState; // offset 0x10, size 0x4
    int streak; // offset 0x14, size 0x4
};
// Range: 0x80018D9C -> 0x80018F44
void GemManager::Jump(class GemManager * const this /* r31 */, float ms /* f30 */) {
    // Local variables
    float bottom; // f31
    int newBegin; // r30
    int i; // r29
    struct PlayerState nullState; // r1+0x18
}

// Range: 0x80018F44 -> 0x80018FAC
void GemManager::SetBonusGems(class GemManager * const this /* r30 */, unsigned char bonus /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80018FAC -> 0x80018FB4
void GemManager::SetInCoda() {}

// Range: 0x80018FB4 -> 0x8001908C
void GemManager::OnMissPhrase(class GemManager * const this /* r29 */, int phrase_id /* r30 */) {
    // Local variables
    int track; // r0
    struct Extent e; // r1+0x18

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x8001908C -> 0x80019128
unsigned char GemManager::GetGemWidget(class Symbol & outName /* r30 */, class Symbol & state /* r31 */) {
    // Local variables
    class DataArray * dataArray; // r31
}

// Range: 0x80019128 -> 0x80019164
unsigned int GemManager::GetSlotsForGem() {}

// Range: 0x80019164 -> 0x80019210
void GemManager::EnableSlot(class GemManager * const this /* r30 */, int slot /* r31 */) {}

// Range: 0x80019210 -> 0x800192A0
void GemManager::DisableSlot(class GemManager * const this /* r30 */, int slot /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x800192A0 -> 0x80019314
unsigned char GemManager::SlotEnabled(const class GemManager * const this /* r31 */, int slot /* r1+0x8 */) {
    // Local variables
    struct _List_iterator f; // r1+0x28
}

static class Symbol normal; // size: 0x4, address: 0x80A48F24
static class Symbol star; // size: 0x4, address: 0x80A48F2C
static class Symbol unison; // size: 0x4, address: 0x80A48F34
static class Symbol invisible; // size: 0x4, address: 0x80A48F3C
static class Symbol bonus; // size: 0x4, address: 0x80A48F44
static class Symbol tom; // size: 0x4, address: 0x80A48F4C
// Range: 0x80019314 -> 0x800195D8
class Symbol GemManager::GetTypeForGem(class GemManager * const this /* r29 */, int gemID /* r30 */) {
    // Local variables
    int track; // r31
    const class vector & gems; // r0
    class GemPlayer * gemPlayer; // r0
    unsigned char is_unison; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> class GameMode * TheGameMode;
    // -> struct [anonymous] __RTTI__6Player;
    // -> struct [anonymous] __RTTI__9GemPlayer;
    // -> class GameConfig * TheGameConfig;
    // -> class SongDB * TheSongDB;
    // -> static class Symbol tom;
    // -> static class Symbol bonus;
    // -> static class Symbol invisible;
    // -> static class Symbol unison;
    // -> static class Symbol star;
    // -> static class Symbol normal;
}

// Range: 0x800195D8 -> 0x80019694
void GemManager::UpdateGemStates(class GemManager * const this /* r29 */) {
    // Local variables
    int i; // r30
    class Symbol type; // r1+0x10
}

// Range: 0x80019694 -> 0x80019728
void GemManager::ClearGems(class GemManager * const this /* r30 */) {
    // Local variables
    int i; // r31
}

static class Symbol invisible; // size: 0x4, address: 0x80A48F54
// Range: 0x80019728 -> 0x800197C0
void GemManager::HideGems(class GemManager * const this /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> static class Symbol invisible;
}

// Range: 0x800197C0 -> 0x800198BC
unsigned char GemManager::IsSpotlightGem(class GemManager * const this /* r28 */, int gem_id /* r30 */, unsigned char & unison /* r29 */) {
    // Local variables
    int phrase_id; // r30
    class Player * player; // r0
    int tracks; // r4

    // References
    // -> class GameConfig * TheGameConfig;
    // -> class SongDB * TheSongDB;
}

// Range: 0x800198BC -> 0x80019990
unsigned char GemManager::IsInFill(class GemManager * const this /* r29 */, int tick /* r30 */) {
    // Local variables
    class Player * player; // r31
    class FillInfo * fillinfo; // r0

    // References
    // -> class SongDB * TheSongDB;
    // -> class GameConfig * TheGameConfig;
}

class Stats {
    // total size: 0x2C
    int mTotal; // offset 0x0, size 0x4
    int mStreak; // offset 0x4, size 0x4
    int mLongestStreak; // offset 0x8, size 0x4
    float mNotesHitFraction; // offset 0xC, size 0x4
    unsigned char mFailedDeploy; // offset 0x10, size 0x1
    int mSavedCount; // offset 0x14, size 0x4
    int mDeployCount; // offset 0x18, size 0x4
    int mFillHitCount; // offset 0x1C, size 0x4
    unsigned char mStrummedUp; // offset 0x20, size 0x1
    unsigned char mStrummedDown; // offset 0x21, size 0x1
    unsigned char mFinalized; // offset 0x22, size 0x1
    int mSoloPercentage; // offset 0x24, size 0x4
    unsigned char mPerfectSoloWithSoloButtons; // offset 0x28, size 0x1
};
enum /* @enum$13641GemManager_cpp */ {
    kInProgress = 0,
    kSucceeded = 1,
    kFailed = 2,
};
enum PhraseStatus {
    kUnresolved = 0,
    kCaught = 1,
    kFailed = 2,
};
struct PhraseState {
    // total size: 0xC
    enum PhraseStatus resolved; // offset 0x0, size 0x4
    int tracks; // offset 0x4, size 0x4
    int failed_tracks; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct PhraseState * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct PhraseState * _M_start; // offset 0x0, size 0x4
    struct PhraseState * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class BeatMatchSink {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class GemStatus {
    // total size: 0xC
    class vector mGems; // offset 0x0, size 0xC
};
class HeldNote {
    // total size: 0x14
    const class GameGem * mGem; // offset 0x0, size 0x4
    int mGemID; // offset 0x4, size 0x4
    enum TrackType mTrackType; // offset 0x8, size 0x4
    float mPoints; // offset 0xC, size 0x4
    int mMaxPoints; // offset 0x10, size 0x4
};
enum FXCore {
    kFXCoreNone = -1,
    kFXCore0 = 0,
    kFXCore1 = 1,
};
enum EnabledState {
    kPlayerEnabled = 0,
    kPlayerDisabled = 1,
    kPlayerBeingSaved = 2,
    kPlayerDisconnected = 3,
};
class GemPlayer : public Player, public BeatMatchSink {
    // total size: 0x244
protected:
    class Performer * mBandPerformer; // offset 0x110, size 0x4
    class GemStatus * mGemStatus; // offset 0x114, size 0x4
    class DataArray * mDrumSlotWeights; // offset 0x118, size 0x4
    class Symbol mDrumSlotWeightMapping; // offset 0x11C, size 0x4
    int mLastBlownGem; // offset 0x120, size 0x4
    unsigned char mFill; // offset 0x124, size 0x1
    unsigned char mForceFill; // offset 0x125, size 0x1
    int mLastFillHitTick; // offset 0x128, size 0x4
    int mActiveSoloStart; // offset 0x12C, size 0x4
    unsigned char mWasFailedDuringSolo; // offset 0x130, size 0x1
    unsigned char mInSolo; // offset 0x131, size 0x1
    unsigned char mEncounteredAllSoloGems; // offset 0x132, size 0x1
    unsigned char mUsedSoloButtonForAllSoloGems; // offset 0x133, size 0x1
    int mNumFillSwings; // offset 0x134, size 0x4
    int mCodaPoints; // offset 0x138, size 0x4
    float mLastCodaSwing[5]; // offset 0x13C, size 0x14
    float mCodaPointRate; // offset 0x150, size 0x4
    float mCodaMashPeriod; // offset 0x154, size 0x4
    unsigned char mMercurySwitchEnabled; // offset 0x158, size 0x1
    unsigned char mMercurySwitchState; // offset 0x159, size 0x1
    unsigned char mWhammyStarPowerEnabled; // offset 0x15A, size 0x1
    class RndOverlay * mOverlay; // offset 0x15C, size 0x4
    class RndOverlay * mGuitarOverlay; // offset 0x160, size 0x4
    class HeldNote mHeldNote; // offset 0x164, size 0x14
    unsigned char mWhammying; // offset 0x178, size 0x1
    float mWhammySpeedThreshold; // offset 0x17C, size 0x4
    float mWhammySpeedTimeout; // offset 0x180, size 0x4
    float mLastNoteStart; // offset 0x184, size 0x4
    float mLastWhammySample; // offset 0x188, size 0x4
    float mLastWhammySampleTime; // offset 0x18C, size 0x4
    float mLastTimeWhammyVelWasHigh; // offset 0x190, size 0x4
    float mLastWhammyValueSent; // offset 0x194, size 0x4
    int mNumCrashFillReadyHits; // offset 0x198, size 0x4
    float mGhostScorePerGem; // offset 0x19C, size 0x4
    class GemTrack * mTrack; // offset 0x1A0, size 0x4
    class BeatMatchController * mController; // offset 0x1A4, size 0x4
    class Symbol mControllerType; // offset 0x1A8, size 0x4
    class BeatMatcher * mMatcher; // offset 0x1AC, size 0x4
    class BeatMaster * mBeatMaster; // offset 0x1B0, size 0x4
    float mSyncOffset; // offset 0x1B4, size 0x4
    class GuitarFx * mGuitarFx; // offset 0x1B8, size 0x4
    int mFxPos; // offset 0x1BC, size 0x4
    unsigned char mIgnoreMercurySwitch; // offset 0x1C0, size 0x1
    class FxSendPitchShift * mPitchShift; // offset 0x1C4, size 0x4
    class FxSendEQ * mAMRadio; // offset 0x1C8, size 0x4
    enum FXCore mFxCore; // offset 0x1CC, size 0x4
    int mLastFx; // offset 0x1D0, size 0x4
    unsigned char mFxActive; // offset 0x1D4, size 0x1
    signed short mFxWait; // offset 0x1D6, size 0x2
    unsigned char mReverbActive; // offset 0x1D8, size 0x1
    float mTimingErrorAvgMidTerm; // offset 0x1DC, size 0x4
    float mTimingErrorSum; // offset 0x1E0, size 0x4
    int mTimingErrorCount; // offset 0x1E4, size 0x4
    unsigned char mEndgameStarted; // offset 0x1E8, size 0x1
    float mLastEndgameSwing[5]; // offset 0x1EC, size 0x14
    float mLastEndgameNetworkSwing[5]; // offset 0x200, size 0x14
    float mEndgameSwingDelay; // offset 0x214, size 0x4
};
class CommonPhraseCapturer {
    // total size: 0x1C
    class vector mPhraseStates; // offset 0x0, size 0xC
    int mDisabledTracks; // offset 0xC, size 0x4
    int mFinishedTracks; // offset 0x10, size 0x4
    unsigned char mInUnisonPhrase; // offset 0x14, size 0x1
    int mLastStartedPhraseID; // offset 0x18, size 0x4
};
class Band : public Object {
    // total size: 0x8C
    class BandPerformer * mBandPerformer; // offset 0x28, size 0x4
    class vector mPlayers; // offset 0x2C, size 0xC
    class vector mActivePlayers; // offset 0x38, size 0xC
    class vector mCrowdRatings; // offset 0x44, size 0xC
    float mBandRating; // offset 0x50, size 0x4
    int mAccumulatedScore; // offset 0x54, size 0x4
    float mTotalStars; // offset 0x58, size 0x4
    int mLongestStreak; // offset 0x5C, size 0x4
    int mPlayersFinishedCoda; // offset 0x60, size 0x4
    int mPlayersBlewCoda; // offset 0x64, size 0x4
    unsigned char mCodaResolved; // offset 0x68, size 0x1
    enum /* @enum$13641GemManager_cpp */ {
        kInProgress = 0,
        kSucceeded = 1,
        kFailed = 2,
    } mCodaState; // offset 0x6C, size 0x4
    int mBonusLevel; // offset 0x70, size 0x4
    int mMultiplier; // offset 0x74, size 0x4
    int mMaxMultiplier; // offset 0x78, size 0x4
    float mMsWithMultiplier; // offset 0x7C, size 0x4
    float mMsWhenMultiplierStarted; // offset 0x80, size 0x4
    class DataArray * mBonusCfg; // offset 0x84, size 0x4
    class CommonPhraseCapturer * mCommonPhraseCapturer; // offset 0x88, size 0x4
};
class Performer : public virtual Object {
    // total size: 0x9C
public:
    void * __vptr$; // offset 0x4, size 0x4
protected:
    class CrowdRating * mCrowd; // offset 0x8, size 0x4
    class Stats mStats; // offset 0xC, size 0x2C
    class Band * mBand; // offset 0x38, size 0x4
    unsigned char mLostGame; // offset 0x3C, size 0x1
    unsigned char mPastFinishLine; // offset 0x3D, size 0x1
    unsigned char mFinished; // offset 0x3E, size 0x1
    float mScore; // offset 0x40, size 0x4
    class SongPos mSongPos; // offset 0x44, size 0x14
    unsigned char mBroadcastScore; // offset 0x58, size 0x1
    unsigned char mBroadcastStreak; // offset 0x59, size 0x1
    unsigned char mBroadcastCrowd; // offset 0x5A, size 0x1
private:
    float mPollMs; // offset 0x5C, size 0x4
    float mProgressMs; // offset 0x60, size 0x4
    unsigned char mGameOver; // offset 0x64, size 0x1
    float mLastSongMs; // offset 0x68, size 0x4
    float mLastUISeconds; // offset 0x6C, size 0x4
};
class Player : public Performer, public MsgSource {
    // total size: 0x138
protected:
    struct PlayerParams * mParams; // offset 0x8C, size 0x4
    class PlayerBehavior * mBehavior; // offset 0x90, size 0x4
    class BandUser * mUser; // offset 0x94, size 0x4
    class CommonPhraseCapturer * mCommonPhraseCapturer; // offset 0x98, size 0x4
    unsigned char mRemote; // offset 0x9C, size 0x1
    class String mPlayerName; // offset 0xA0, size 0xC
    int mTrackNum; // offset 0xAC, size 0x4
    enum TrackType mTrackType; // offset 0xB0, size 0x4
    enum EnabledState mEnabledState; // offset 0xB4, size 0x4
    int mTimesFailed; // offset 0xB8, size 0x4
    float mEnableMs; // offset 0xBC, size 0x4
    float mDisableMs; // offset 0xC0, size 0x4
    class vector mFailedWindows; // offset 0xC4, size 0xC
    unsigned char mInCoda; // offset 0xD0, size 0x1
    float mEnergy; // offset 0xD4, size 0x4
    unsigned char mIncreasingMultiplier; // offset 0xD8, size 0x1
    int mLastMultiplier; // offset 0xDC, size 0x4
    unsigned char mPhraseBonusesEnabled; // offset 0xE0, size 0x1
    float mGhostScore; // offset 0xE4, size 0x4
    int mBonusID; // offset 0xE8, size 0x4
    int mNumPlayersSaved; // offset 0xEC, size 0x4
    int mSaveInProgress; // offset 0xF0, size 0x4
    float mLastScoreSentMs; // offset 0xF4, size 0x4
    int mLastScoreSent; // offset 0xF8, size 0x4
    float mLastEnergySentMs; // offset 0xFC, size 0x4
    unsigned char mDisconnectedAtStart; // offset 0x100, size 0x1
    unsigned char mFailedAtStart; // offset 0x101, size 0x1
    int mPollCounter; // offset 0x104, size 0x4
    unsigned char mPermanentOverdrive; // offset 0x108, size 0x1
};
// Range: 0x80019990 -> 0x80019A0C
unsigned char GemManager::InMissedPhrase() {
    // Local variables
    int tick; // r0
    int i; // r7
}

struct {
    // total size: 0x8
} __RTTI__8RndGroup; // size: 0x8, address: 0x8086DBE8
struct {
    // total size: 0x8
} __RTTI__9GemPlayer; // size: 0x8, address: 0x8086DCE8
struct {
    // total size: 0x8
} __RTTI__13BeatMatchSink; // size: 0x8, address: 0x8086DD00
struct {
    // total size: 0x8
} __RTTI__6Player; // size: 0x8, address: 0x8086DD38
struct {
    // total size: 0x8
} __RTTI__9Performer; // size: 0x8, address: 0x8086DD60
struct {
    // total size: 0x8
} __RTTI__P3Gem; // size: 0x8, address: 0x8086DEB0
struct {
    // total size: 0x8
} __RTTI__P6Extent; // size: 0x8, address: 0x8086DEC8
class GameMode : public MsgSource {
    // total size: 0xA0
protected:
    class Symbol mMode; // offset 0x1C, size 0x4
    int mPlayer; // offset 0x20, size 0x4
    int mStarPowerEnabled; // offset 0x24, size 0x4
    int mSeparateParts; // offset 0x28, size 0x4
    int mBandArrangement; // offset 0x2C, size 0x4
    int mH2HArrangement; // offset 0x30, size 0x4
    int mIsPractice; // offset 0x34, size 0x4
    int mCanLose; // offset 0x38, size 0x4
    int mMaxDelta; // offset 0x3C, size 0x4
    int mCrowdReacts; // offset 0x40, size 0x4
    int mIsSolo; // offset 0x44, size 0x4
    int mPracticeModeFX; // offset 0x48, size 0x4
    int mDisableGuitarFX; // offset 0x4C, size 0x4
    int mIsDrumTrainer; // offset 0x50, size 0x4
    int mHasTrack; // offset 0x54, size 0x4
    int mEnableStreak; // offset 0x58, size 0x4
    int mIsJukebox; // offset 0x5C, size 0x4
    int mDontShowGemsInFills; // offset 0x60, size 0x4
    int mIsTutorial; // offset 0x64, size 0x4
    int mLoadChars; // offset 0x68, size 0x4
    int mShowStars; // offset 0x6C, size 0x4
    int mRenderPracticeLoop; // offset 0x70, size 0x4
};
class DrumFillInfo : public FillInfo {
    // total size: 0x1C
};
class GameGemList {
    // total size: 0x14
    int mTrack; // offset 0x0, size 0x4
    int mHopoThreshold; // offset 0x4, size 0x4
    class vector mGems; // offset 0x8, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class GameGemList * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class GameGemList * * _M_start; // offset 0x0, size 0x4
    class GameGemList * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class GameGemDB {
    // total size: 0x28
    class vector mGameGemLists; // offset 0x0, size 0xC
    class vector mCopy; // offset 0xC, size 0x14
    int mHopoThreshold; // offset 0x20, size 0x4
    class SongData * mParent; // offset 0x24, size 0x4
};

