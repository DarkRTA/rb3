/*
    Compile unit: C:\rockband2\band2\src\bandtrack\TrackPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80026758 -> 0x8002BE70
*/
class DataArray * types; // size: 0x4, address: 0x80A49070
class Symbol name; // size: 0x4, address: 0x80A49078
class DataArray * types; // size: 0x4, address: 0x80A4907C
class Symbol name; // size: 0x4, address: 0x80A49084
// Range: 0x80026758 -> 0x8002677C
class TrackPanelDirBase * GetTrackPanelDir() {}

enum TrackInstrument {
    kInstGuitar = 0,
    kInstDrum = 1,
    kInstBass = 2,
    kInstVocals = 3,
    kNumTrackInstruments = 4,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    enum TrackInstrument * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    enum TrackInstrument * _M_start; // offset 0x0, size 0x4
    enum TrackInstrument * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TrackPanelInterface : public UIPanel {
    // total size: 0x5C
};
class TrackPanel : public TrackPanelInterface {
    // total size: 0xDC
    unsigned char mInitialized; // offset 0x30, size 0x1
    unsigned char mCamTweak; // offset 0x31, size 0x1
    const class DataArray * mConfig; // offset 0x34, size 0x4
    class vector mTracks; // offset 0x38, size 0xC
    class vector mScoreDisplays; // offset 0x44, size 0xC
    class vector mLastScore; // offset 0x50, size 0xC
    class vector mLastNumStars; // offset 0x5C, size 0xC
    class vector mCodaDisplays; // offset 0x68, size 0xC
    unsigned char mBandsReversed; // offset 0x74, size 0x1
    class map mReloadChecks; // offset 0x78, size 0x18
    float mNextReloadTime; // offset 0x90, size 0x4
    class TrackPanelDirBase * mTrackPanelDir; // offset 0x94, size 0x4
    int mFrame; // offset 0x98, size 0x4
    float mTargetStartAccumScore; // offset 0x9C, size 0x4
    float mTargetEndAccumScore; // offset 0xA0, size 0x4
    float mBandNamesFadeOutMS; // offset 0xA4, size 0x4
    float mBandNamesFadeInMS; // offset 0xA8, size 0x4
    unsigned char mHidingBandNames; // offset 0xAC, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Track * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Track * * _M_start; // offset 0x0, size 0x4
    class Track * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class Scoreboard : public RndDir {
    // total size: 0x2F0
    int mCurrentStar; // offset 0x1F4, size 0x4
    float mTestScore; // offset 0x1F8, size 0x4
    float mTestStars; // offset 0x1FC, size 0x4
    float mTestOpponentScore; // offset 0x200, size 0x4
    float mScore; // offset 0x204, size 0x4
    float mNumStars; // offset 0x208, size 0x4
    float mOpponentScore; // offset 0x20C, size 0x4
    float mSweepPercent; // offset 0x210, size 0x4
    unsigned char mGold; // offset 0x214, size 0x1
    unsigned char mPlayStarSfx; // offset 0x215, size 0x1
    class ObjVector mStars; // offset 0x218, size 0x10
    unsigned char mSound; // offset 0x228, size 0x1
    class Symbol mConfig; // offset 0x22C, size 0x4
    class ObjPtr mStarsOffset; // offset 0x230, size 0xC
    class ObjPtr mGoldStars; // offset 0x23C, size 0xC
    class ObjPtr mScoreText; // offset 0x248, size 0xC
    class ObjPtr mOpponentScoreText; // offset 0x254, size 0xC
    class ObjPtr mStarBattle; // offset 0x260, size 0xC
    class ObjPtr mStarBattleOff; // offset 0x26C, size 0xC
    class ObjPtr mGoldStarsTrigger; // offset 0x278, size 0xC
    class ObjPtr mAchieveStar; // offset 0x284, size 0xC
    class ObjPtr mConfigNormal; // offset 0x290, size 0xC
    class ObjPtr mConfigBotb; // offset 0x29C, size 0xC
    class ObjPtr mStarsGroup; // offset 0x2A8, size 0xC
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Scoreboard * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Scoreboard * * _M_start; // offset 0x0, size 0x4
    class Scoreboard * * _M_finish; // offset 0x4, size 0x4
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
    class EndingBonus * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class EndingBonus * * _M_start; // offset 0x0, size 0x4
    class EndingBonus * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class DepChecker {
    // total size: 0x4
    unsigned long mCacheModTime; // offset 0x0, size 0x4
};
struct pair {
    // total size: 0x8
    class Symbol first; // offset 0x0, size 0x4
    class DepChecker * second; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
// Range: 0x8002677C -> 0x80026988
void * TrackPanel::~TrackPanel(class TrackPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__10TrackPanel;
}

// Range: 0x80026988 -> 0x800269BC
void TrackPanel::Load(class TrackPanel * const this /* r31 */) {}

// Range: 0x800269BC -> 0x80026A3C
unsigned char TrackPanel::IsLoaded(class TrackPanel * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> struct [anonymous] __RTTI__17TrackPanelDirBase;
}

// Range: 0x80026A3C -> 0x80026A40
void TrackPanel::Enter() {}

// Range: 0x80026A40 -> 0x80026A7C
void TrackPanel::FinishLoad(class TrackPanel * const this /* r31 */) {}

class list : public _List_base {
    // total size: 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class BandUser * _M_data; // offset 0x8, size 0x4
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
static class Message on_reset; // size: 0x8, address: 0x80976BC0
struct SongStatus {
    // total size: 0x18
    class Symbol mSongName; // offset 0x0, size 0x4
    class String mFullSongName; // offset 0x4, size 0xC
    int mStars; // offset 0x10, size 0x4
    int mScore; // offset 0x14, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct SongStatus * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct SongStatus * _M_start; // offset 0x0, size 0x4
    struct SongStatus * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct BandMember {
    // total size: 0x20
    class HxGuid mCharGuid; // offset 0x0, size 0x10
    class String mCharName; // offset 0x10, size 0xC
    unsigned char mCharNameUnchecked; // offset 0x1C, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BandMember * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BandMember * _M_start; // offset 0x0, size 0x4
    struct BandMember * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class BandData : public virtual Object {
    // total size: 0x34
public:
    void * __vptr$; // offset 0x4, size 0x4
};
class PersistentGameData {
    // total size: 0x4C
public:
    int mTotalScore; // offset 0x0, size 0x4
    float mTotalStars; // offset 0x4, size 0x4
    int mLongestStreak; // offset 0x8, size 0x4
    class PersistentPlayerData mPlayerData[4]; // offset 0xC, size 0x40
};
struct WorldState {
    // total size: 0x1C
    class Symbol mEvent; // offset 0x0, size 0x4
    class Symbol mVenue; // offset 0x4, size 0x4
    class Symbol mTown; // offset 0x8, size 0x4
    int mFame; // offset 0xC, size 0x4
    int mStars; // offset 0x10, size 0x4
    enum Difficulty mMaxDiff; // offset 0x14, size 0x4
    int mMaxPlayers; // offset 0x18, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct WorldState * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct WorldState * _M_start; // offset 0x0, size 0x4
    struct WorldState * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct SeenVenue {
    // total size: 0x8
    class Symbol mTown; // offset 0x0, size 0x4
    class Symbol mVenue; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct SeenVenue * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct SeenVenue * _M_start; // offset 0x0, size 0x4
    struct SeenVenue * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum TourBuzzState {
    kTourBuzzNone = 0,
    kTourBuzzCap = 1,
    kTourBuzzMaxCap = 2,
};
struct BuzzInfo {
    // total size: 0xC
    int mBuzz; // offset 0x0, size 0x4
    int mFansChange; // offset 0x4, size 0x4
    enum TourBuzzState mBuzzState; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct BandSongStatus {
    // total size: 0x14
    class Symbol mSongName; // offset 0x0, size 0x4
    int mStars; // offset 0x4, size 0x4
    int mScore; // offset 0x8, size 0x4
    int mFans; // offset 0xC, size 0x4
    unsigned char mDirty; // offset 0x10, size 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class BandSongStatusMgr : public Object {
    // total size: 0x3C
    const class SongMgr * mSongMgr; // offset 0x28, size 0x4
    class HxGuid * mBandGuid; // offset 0x2C, size 0x4
    class list mSongList; // offset 0x30, size 0x8
    struct BandSongStatus * mUpdatingScore; // offset 0x38, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct OpportunityLoc {
    // total size: 0xC
    class Symbol mTown; // offset 0x0, size 0x4
    class Symbol mVenue; // offset 0x4, size 0x4
    class Symbol mMomentName; // offset 0x8, size 0x4
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
class TourHint : public Object {
    // total size: 0x30
protected:
    class DataArray * mCfg; // offset 0x28, size 0x4
    class Symbol mHintName; // offset 0x2C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TourHint * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TourHint * * _M_start; // offset 0x0, size 0x4
    class TourHint * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct SongState {
    // total size: 0x8
    class Symbol mSong; // offset 0x0, size 0x4
    int mStars; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct SongState * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct SongState * _M_start; // offset 0x0, size 0x4
    struct SongState * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct ChallengeState {
    // total size: 0x18
    class Symbol mName; // offset 0x0, size 0x4
    class vector mSongs; // offset 0x4, size 0xC
    int mMaxPlayers; // offset 0x10, size 0x4
    enum Difficulty mMaxDiff; // offset 0x14, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
enum ChallengeFocus {
    kChallengeFocusEvent = 0,
    kChallengeFocusHighestTier = 1,
    kChallengeFocusHighestNewTier = 2,
};
enum TourEventType {
    kTourEventWorld = 0,
    kTourEventChallenge = 1,
};
struct TourRequirement {
    // total size: 0x28
    unsigned char mMet; // offset 0x0, size 0x1
    class String mIcon; // offset 0x4, size 0xC
    class String mInstrument; // offset 0x10, size 0xC
    class String mDesc; // offset 0x1C, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct TourRequirement * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct TourRequirement * _M_start; // offset 0x0, size 0x4
    struct TourRequirement * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum TourStatus {
    kTourLocked = 0,
    kTourUnlocked = 1,
    kTourPlayed = 2,
    kTourNew = 3,
};
class EventSong {
    // total size: 0x8
    class DataNode mData; // offset 0x0, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class EventSong * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class EventSong * _M_start; // offset 0x0, size 0x4
    class EventSong * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct EventOutfit {
    // total size: 0xC
    class Symbol mGender; // offset 0x0, size 0x4
    class Symbol mCategory; // offset 0x4, size 0x4
    class Symbol mOutfit; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct EventOutfit * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct EventOutfit * _M_start; // offset 0x0, size 0x4
    struct EventOutfit * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct EventInstrument {
    // total size: 0x8
    class Symbol mCategory; // offset 0x0, size 0x4
    class Symbol mOutfit; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct EventInstrument * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct EventInstrument * _M_start; // offset 0x0, size 0x4
    struct EventInstrument * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TourEvent : public Object {
    // total size: 0x90
protected:
    const class SongMgr & mSongMgr; // offset 0x28, size 0x4
    class Symbol mEventName; // offset 0x2C, size 0x4
    int mBattleId; // offset 0x30, size 0x4
    class String mDisplayName; // offset 0x34, size 0xC
    class vector mSongs; // offset 0x40, size 0xC
    int mMoneyPerStar; // offset 0x4C, size 0x4
    unsigned char mSellout; // offset 0x50, size 0x1
    enum Difficulty mMinDifficulty; // offset 0x54, size 0x4
    class Symbol mRequiredPart; // offset 0x58, size 0x4
    class Symbol mCharUnlockToken; // offset 0x5C, size 0x4
    class vector mUnlockOutfits; // offset 0x60, size 0xC
    class vector mUnlockInstruments; // offset 0x6C, size 0xC
    unsigned int mTimeRemaining; // offset 0x78, size 0x4
    int mTimeToLive; // offset 0x7C, size 0x4
    unsigned int mTimeSince; // offset 0x80, size 0x4
    const char * mLoadingScreen; // offset 0x84, size 0x4
    unsigned char mNoOverdrive; // offset 0x88, size 0x1
    unsigned char mNoCrowdMeter; // offset 0x89, size 0x1
    unsigned char mNoBackFromBrink; // offset 0x8A, size 0x1
    enum WinMetric mWinMetric; // offset 0x8C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TourWorldEvent * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TourWorldEvent * * _M_start; // offset 0x0, size 0x4
    class TourWorldEvent * * _M_finish; // offset 0x4, size 0x4
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
    const class TourTown * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    const class TourTown * * _M_start; // offset 0x0, size 0x4
    const class TourTown * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct EventState {
    // total size: 0x8
    class TourWorldEvent * mEvent; // offset 0x0, size 0x4
    enum TourStatus mStatus; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct EventState * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct EventState * _M_start; // offset 0x0, size 0x4
    struct EventState * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct VenueState {
    // total size: 0x14
    class TourVenue * mVenue; // offset 0x0, size 0x4
    enum TourStatus mStatus; // offset 0x4, size 0x4
    class vector mEvents; // offset 0x8, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct VenueState * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct VenueState * _M_start; // offset 0x0, size 0x4
    struct VenueState * _M_finish; // offset 0x4, size 0x4
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
    class TourChallengeEvent * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TourChallengeEvent * * _M_start; // offset 0x0, size 0x4
    class TourChallengeEvent * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TourBand : public BandData, public MetaPerformer {
    // total size: 0x208
public:
    class String mBotbRivalBandName; // offset 0x48, size 0xC
    float mBotbRivalBandScore; // offset 0x54, size 0x4
    int mBotbRivalBandStars; // offset 0x58, size 0x4
protected:
    struct DateTime mCreationDate; // offset 0x5C, size 0x6
    class HxGuid mGuidBand; // offset 0x64, size 0x10
    class String mBandName; // offset 0x74, size 0xC
    class String mMotto; // offset 0x80, size 0xC
    class String mBandLogo; // offset 0x8C, size 0xC
    int mBandLogoPos; // offset 0x98, size 0x4
    unsigned char mFinalized; // offset 0x9C, size 0x1
    class vector mRoster; // offset 0xA0, size 0xC
    class vector mWorldStates; // offset 0xAC, size 0xC
    class vector mSeenVenues; // offset 0xB8, size 0xC
    class list mWorldRecentUnlocks; // offset 0xC4, size 0x8
    int mNumUnlockedEvents; // offset 0xCC, size 0x4
    int mNumUnlockedVenues; // offset 0xD0, size 0x4
    int mNumUnlockedTowns; // offset 0xD4, size 0x4
    class Symbol mCharUnlock; // offset 0xD8, size 0x4
    unsigned char mJustPlayedAllVenues; // offset 0xDC, size 0x1
    unsigned char mIronBladder; // offset 0xDD, size 0x1
    unsigned char mIconsUpgraded; // offset 0xDE, size 0x1
    struct BuzzInfo mCurrentBuzz; // offset 0xE0, size 0xC
    struct BuzzInfo mPreMomentBuzz; // offset 0xEC, size 0xC
    enum Difficulty mWinDifficulty; // offset 0xF8, size 0x4
    class vector mItems; // offset 0xFC, size 0xC
    class vector mAchievementItems; // offset 0x108, size 0xC
    class BandSongStatusMgr mSongStatusMgr; // offset 0x114, size 0x3C
    const class TourWorld & mWorld; // offset 0x150, size 0x4
    class BandUserMgr & mUserMgr; // offset 0x154, size 0x4
    class Symbol mHometown; // offset 0x158, size 0x4
    class Symbol mTown; // offset 0x15C, size 0x4
    class Symbol mVenue; // offset 0x160, size 0x4
    class Symbol mWorldEvent; // offset 0x164, size 0x4
    class list mOpportunityLocs; // offset 0x168, size 0x8
    class Symbol mStaff; // offset 0x170, size 0x4
    class vector mWorldHints; // offset 0x174, size 0xC
    class TourMoment * mMoment; // offset 0x180, size 0x4
    class vector mBotbTargetScoreFracs; // offset 0x184, size 0xC
    const class TourChallenge & mChallenge; // offset 0x190, size 0x4
    class Symbol mChallengeEvent; // offset 0x194, size 0x4
    class list mChallengeStates; // offset 0x198, size 0x8
    class list mChallengeNewUnlocks; // offset 0x1A0, size 0x8
    class list mChallengeRecentUnlocks; // offset 0x1A8, size 0x8
    class vector mChallengeHints; // offset 0x1B0, size 0xC
    enum ChallengeFocus mChallengeFocus; // offset 0x1BC, size 0x4
    class TourCharRemote * mStandIns[4]; // offset 0x1C0, size 0x10
    class Symbol mBotbScoreString; // offset 0x1D0, size 0x4
    class list mLiveBattles; // offset 0x1D4, size 0x8
};
// Range: 0x80026A7C -> 0x80026EF8
void TrackPanel::Reset(class TrackPanel * const this /* r30 */) {
    // Local variables
    float ms; // f31
    int i; // r29
    int ii; // r29
    class TourBand * band; // r0
    class TourEvent * event; // r0
    class MetaPerformer * mp; // r29
    float endingScore; // f0
    const char * otherName; // r28
    const char * bandName; // r31
    class String thisBandIcon; // r1+0x4C
    class String rivalBandIcon; // r1+0x40

    // References
    // -> class Game * TheGame;
    // -> class Tour * TheTour;
    // -> class LoadMgr TheLoadMgr;
    // -> static class Message on_reset;
    // -> struct [anonymous] __vt__7Message;
    // -> class GameMode * TheGameMode;
    // -> class TaskMgr TheTaskMgr;
}

class PersistentPlayerData {
    // total size: 0x10
public:
    float mEnergy; // offset 0x0, size 0x4
    float mRawCrowdRating; // offset 0x4, size 0x4
    int mStreak; // offset 0x8, size 0x4
    unsigned char mFailed; // offset 0xC, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
enum FitType {
    kFitWrap = 0,
    kFitStretch = 1,
    kFitJust = 2,
    kFitEllipsis = 3,
};
class UILabel : public UIComponent {
    // total size: 0x1E0
public:
    class String printMsg; // offset 0x130, size 0xC
protected:
    class RndText * mText; // offset 0x13C, size 0x4
    class String mDisplayText; // offset 0x140, size 0xC
    class Symbol mTextToken; // offset 0x14C, size 0x4
    unsigned char mLocalize; // offset 0x150, size 0x1
    float mTextSize; // offset 0x154, size 0x4
    enum Alignment mAlignment; // offset 0x158, size 0x4
    enum CapsMode mCapsMode; // offset 0x15C, size 0x4
    unsigned char mMarkup; // offset 0x160, size 0x1
    float mLeading; // offset 0x164, size 0x4
    float mBaseKerning; // offset 0x168, size 0x4
    float mItalics; // offset 0x16C, size 0x4
    enum FitType mFitType; // offset 0x170, size 0x4
    float mWidth; // offset 0x174, size 0x4
    float mHeight; // offset 0x178, size 0x4
    int mFixedLength; // offset 0x17C, size 0x4
    int mReserveLines; // offset 0x180, size 0x4
    class String mPreserveTruncText; // offset 0x184, size 0xC
    float mAlpha; // offset 0x190, size 0x4
    unsigned char mUseAutoHyphenation; // offset 0x194, size 0x1
    int mHyphMinWordLength; // offset 0x198, size 0x4
    int mHyphMinPrefix; // offset 0x19C, size 0x4
    int mHyphMinSuffix; // offset 0x1A0, size 0x4
};
class BandTextComp {
    // total size: 0x20
public:
    void * __vptr$; // offset 0x0, size 0x4
protected:
    class RndText * mTextObjPtr; // offset 0x4, size 0x4
    int mStateColors[5]; // offset 0x8, size 0x14
private:
    class Symbol mColorPreset; // offset 0x1C, size 0x4
};
class BandLabel : public UILabel, public BandTextComp {
    // total size: 0x220
    class Keys mCountKeys; // offset 0x1C4, size 0xC
    class String mCountString; // offset 0x1D0, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BandLabel * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BandLabel * * _M_start; // offset 0x0, size 0x4
    class BandLabel * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class EndingBonus : public RndDir {
    // total size: 0x260
    unsigned char mInUnison; // offset 0x1F4, size 0x1
    int mScore; // offset 0x1F8, size 0x4
    unsigned char mAwarding; // offset 0x1FC, size 0x1
    class ObjPtr mCodaEndTask; // offset 0x200, size 0xC
    class vector mTrackOrder; // offset 0x20C, size 0xC
    unsigned char mDisabled[4]; // offset 0x218, size 0x4
    class vector mIcons; // offset 0x21C, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class CrowdMeterIcon : public RndDir {
    // total size: 0x260
    class EventTrigger * mResetTrig; // offset 0x1F4, size 0x4
    class EventTrigger * mArrowHideTrig; // offset 0x1F8, size 0x4
    class EventTrigger * mArrowShowTrig; // offset 0x1FC, size 0x4
    class EventTrigger * mDeployTrig; // offset 0x200, size 0x4
    class EventTrigger * mStopDeployTrig; // offset 0x204, size 0x4
    class EventTrigger * mStateFailedTrig; // offset 0x208, size 0x4
    class EventTrigger * mStateFailingTrig; // offset 0x20C, size 0x4
    class EventTrigger * mStateNormalTrig; // offset 0x210, size 0x4
    class EventTrigger * mGlowTrig; // offset 0x214, size 0x4
    class EventTrigger * mGlowStopTrig; // offset 0x218, size 0x4
    class BandLabel * mIconLbl; // offset 0x21C, size 0x4
    unsigned char mShowTrigger; // offset 0x220, size 0x1
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class CrowdMeterIcon * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ObjPtr * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ObjPtr * _M_start; // offset 0x0, size 0x4
    class ObjPtr * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
class BandCrowdMeter : public RndDir {
    // total size: 0x320
    class ObjVector mAnims; // offset 0x1F4, size 0x10
    class ObjVector mIcons; // offset 0x204, size 0x10
    class ObjPtr mTmp; // offset 0x214, size 0xC
    float mValues[4]; // offset 0x220, size 0x10
    unsigned char mDisabled[4]; // offset 0x230, size 0x4
    unsigned char mMaxed; // offset 0x234, size 0x1
    int mDeploying; // offset 0x238, size 0x4
    int mPeaks; // offset 0x23C, size 0x4
    float mPeakValue; // offset 0x240, size 0x4
    unsigned char mNoCrowdMeter; // offset 0x244, size 0x1
    class vector mLevelColors; // offset 0x248, size 0xC
    enum ExcitementLevel mExcitement; // offset 0x254, size 0x4
    class TrackPanelInterface * mTrackPanel; // offset 0x258, size 0x4
    class ObjPtrList mOrderedPeaks; // offset 0x25C, size 0x14
    class ObjPtr mBandEnergyDeployTrig; // offset 0x270, size 0xC
    class ObjPtr mBandEnergyStopTrig; // offset 0x27C, size 0xC
    class ObjPtr mDisabledStartTrig; // offset 0x288, size 0xC
    class ObjPtr mDisabledStopTrig; // offset 0x294, size 0xC
    class ObjPtr mShowPeakArrowTrig; // offset 0x2A0, size 0xC
    class ObjPtr mHidePeakArrowTrig; // offset 0x2AC, size 0xC
    class ObjPtr mCrowdMeterMat; // offset 0x2B8, size 0xC
    class ObjPtr mCrowdMeterAnim; // offset 0x2C4, size 0xC
    class vector mUnused; // offset 0x2D0, size 0xC
    float mValue; // offset 0x2DC, size 0x4
};
class TrackPanelDirBase : public PanelDir {
    // total size: 0x2F0
protected:
    float mViewTimeEasy; // offset 0x24C, size 0x4
    float mViewTimeExpert; // offset 0x250, size 0x4
    float mNetTrackAlpha; // offset 0x254, size 0x4
    class ObjPtr mConfiguration; // offset 0x258, size 0xC
    class ObjPtrList mConfigurableObjects; // offset 0x264, size 0x14
    class ObjVector mGemTracks; // offset 0x278, size 0x10
    unsigned char mSimplifiedLOD; // offset 0x288, size 0x1
    class TrackPanelInterface * mTrackPanel; // offset 0x28C, size 0x4
    class ObjPtr mApplauseMeter; // offset 0x290, size 0xC
    class ObjPtr mSetWinningGlow; // offset 0x29C, size 0xC
    class RndDir * mIcon0; // offset 0x2A8, size 0x4
    class RndDir * mIcon1; // offset 0x2AC, size 0x4
};
// Range: 0x80026EF8 -> 0x80027144
void TrackPanel::CleanUpTracks(class TrackPanel * const this /* r31 */) {
    // Local variables
    class list band_users; // r1+0x50
    struct _List_iterator it; // r1+0x38

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP5Track;
    // -> unsigned char gStlAllocNameLookup;
    // -> class BandUserMgr * TheBandUserMgr;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PP5Track; // size: 0x8, address: 0x8086FA80
// Range: 0x80027144 -> 0x80027B28
void TrackPanel::Reload(class TrackPanel * const this /* r28 */) {
    // Local variables
    int i; // r29
    class Symbol trackType; // r1+0x8C
    const char * trackName; // r25
    int b; // r29
    int slot; // r0
    class Scoreboard * scoreboard; // r1+0x88
    class EndingBonus * ending_bonus; // r1+0x84
    class Scoreboard * scoreboard; // r1+0x80

    // References
    // -> struct [anonymous] __RTTI__11EndingBonus;
    // -> struct [anonymous] __RTTI__10Scoreboard;
    // -> const char * kAssertStr;
    // -> class Game * TheGame;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class GameMode * TheGameMode;
}

// Range: 0x80027B28 -> 0x80027DB4
void TrackPanel::Unload(class TrackPanel * const this /* r31 */) {
    // Local variables
    int i; // r29
}

// Range: 0x80027DB4 -> 0x80027E2C
unsigned char TrackPanel::ShowApplauseMeter() {
    // Local variables
    class MetaPerformer * mp; // r30
}

static class Timer * _t; // size: 0x4, address: 0x80A4908C
static class Timer * _t; // size: 0x4, address: 0x80A49094
// Range: 0x80027E2C -> 0x80028874
void TrackPanel::Poll(class TrackPanel * const this /* r28 */) {
    // Local variables
    class AutoTimer _at; // r1+0x28
    class AutoTimer _at; // r1+0x24
    float ms; // f31
    int i; // r24
    int i; // r29
    float newScore; // f30
    float numStars; // f0
    int s0; // r0
    int s1; // r0
    class MetaPerformer * mp; // r24
    class DataArray * config; // r25
    float fadeOutDelay; // r1+0x20
    float fadeInAnticipation; // r1+0x1C
    class Performer * perf; // r25
    int current_score; // r0
    float current_target; // f1
    int current_streak; // r0
    float current_target; // f2
    float current_star_cents; // f0
    float current_target; // f1
    class Performer * mainPerformer; // r24
    int i; // r25
    class Performer * p; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameConfig * TheGameConfig;
    // -> class GameMode * TheGameMode;
    // -> class TaskMgr TheTaskMgr;
    // -> class Game * TheGame;
    // -> class SongDB * TheSongDB;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
}

class BandPerformer : public Performer {
    // total size: 0xA8
    class DataArray * mWeights; // offset 0x70, size 0x4
    float mLoseLevel; // offset 0x74, size 0x4
    float mGhostScore; // offset 0x78, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BeatMasterSink * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BeatMasterSink * * _M_start; // offset 0x0, size 0x4
    class BeatMasterSink * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum AudioStyle {
    kUnmute = 0,
    kSlipStream = 1,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class ChannelData * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class ChannelData * * _M_start; // offset 0x0, size 0x4
    class ChannelData * * _M_finish; // offset 0x4, size 0x4
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
    class TrackData * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TrackData * * _M_start; // offset 0x0, size 0x4
    class TrackData * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct ExtraTrackInfo {
    // total size: 0xC
    unsigned char mPlayable; // offset 0x0, size 0x1
    float mExtraAtten; // offset 0x4, size 0x4
    unsigned char mDuckable; // offset 0x8, size 0x1
    unsigned char mVocalCue; // offset 0x9, size 0x1
    unsigned char mVocal; // offset 0xA, size 0x1
};
enum DontPlayReason {
    kMiss = 0,
    kPass = 1,
};
class MasterAudio : public BeatMasterSink, public BeatMatchSink, public Object {
    // total size: 0xF8
    enum AudioStyle mDefaultStyle; // offset 0x30, size 0x4
    int mNumPlayers; // offset 0x34, size 0x4
    class Stream * mSongStream; // offset 0x38, size 0x4
    class SongData * mSongData; // offset 0x3C, size 0x4
    unsigned char mStreamEnabled; // offset 0x40, size 0x1
    class Fader * mMasterFader; // offset 0x44, size 0x4
    class Fader * mForegroundFader; // offset 0x48, size 0x4
    class Fader * mMultiplayerFader; // offset 0x4C, size 0x4
    class Fader * mBackgroundFader; // offset 0x50, size 0x4
    class Fader * mBackgroundAttenFader; // offset 0x54, size 0x4
    class Fader * mCommonFader; // offset 0x58, size 0x4
    class Fader * mRemoteFader; // offset 0x5C, size 0x4
    class Fader * mPracticeFader; // offset 0x60, size 0x4
    class Fader * mVocalDuckFader; // offset 0x64, size 0x4
    class Fader * mVocalCueFader; // offset 0x68, size 0x4
    class Fader * mVocalFailFader; // offset 0x6C, size 0x4
    class Fader * mCrowdFader; // offset 0x70, size 0x4
    class Fader * mBaseCrowdFader; // offset 0x74, size 0x4
    class SubmixCollection * mSubmixes; // offset 0x78, size 0x4
    class vector mChannelData; // offset 0x7C, size 0xC
    class vector mTrackData; // offset 0x88, size 0xC
    class vector mNumTracksToVolume; // offset 0x94, size 0xC
    unsigned char mFocusVolumesEnabled; // offset 0xA0, size 0x1
    int mActiveTrack; // offset 0xA4, size 0x4
    unsigned char mPlayingInCommon; // offset 0xA8, size 0x1
    float mMultiplayerStereoScale; // offset 0xAC, size 0x4
    float mMultiplayerVolume; // offset 0xB0, size 0x4
    float mMultiplayerCommonVolume; // offset 0xB4, size 0x4
    float mPlayerAtten; // offset 0xB8, size 0x4
    float mBackgroundVolume; // offset 0xBC, size 0x4
    float mMuteVolume; // offset 0xC0, size 0x4
    float mPassVolume; // offset 0xC4, size 0x4
    float mUnplayedVolume; // offset 0xC8, size 0x4
    float mCueVolume; // offset 0xCC, size 0x4
    float mPracticeVolume; // offset 0xD0, size 0x4
    float mRemoteVolume; // offset 0xD4, size 0x4
    unsigned char mHeadToHead; // offset 0xD8, size 0x1
    float mVolume; // offset 0xDC, size 0x4
    float mStereoScale; // offset 0xE0, size 0x4
    float mStereoCenter; // offset 0xE4, size 0x4
    unsigned char mMuckWithPitch; // offset 0xE8, size 0x1
    unsigned char mMuteMaster; // offset 0xE9, size 0x1
    float mMasterVolume; // offset 0xEC, size 0x4
    class PitchMucker * mPitchMucker; // offset 0xF0, size 0x4
    unsigned char mAddFaders; // offset 0xF4, size 0x1
};
class BeatMaster : public SongParserSink {
    // total size: 0x74
    unsigned char mRecording; // offset 0x4, size 0x1
    class SongData * mSongData; // offset 0x8, size 0x4
    class vector mSinks; // offset 0xC, size 0xC
    class MasterAudio * mAudio; // offset 0x18, size 0x4
    class MidiParserMgr * mMidiParserMgr; // offset 0x1C, size 0x4
    class DataArray * mSongCfg; // offset 0x20, size 0x4
    class PlayerTrackConfigList * mPtCfg; // offset 0x24, size 0x4
    class BeatMasterLoader * mLoader; // offset 0x28, size 0x4
    unsigned char mLoaded; // offset 0x2C, size 0x1
    class SongPos mSongPos; // offset 0x30, size 0x14
    class SongPos mLastSongPos; // offset 0x44, size 0x14
    class vector mSubmixIdxs; // offset 0x58, size 0xC
    int mActivePlayerTrack; // offset 0x64, size 0x4
    int mCurActivePlayers; // offset 0x68, size 0x4
    int mActivePlayerGemIdx; // offset 0x6C, size 0x4
    class DataArray * mHandlers; // offset 0x70, size 0x4
};
static int sVals[20]; // size: 0x50, address: 0x80976BC8
static int sGross; // size: 0x4, address: 0x80A4909C
// Range: 0x80028874 -> 0x80028904
static int GetTrend() {
    // Local variables
    int ii; // r6
    int idx; // r0

    // References
    // -> static int sGross;
    // -> static int sVals[20];
}

// Range: 0x80028904 -> 0x8002899C
static int ApplyDeltaCurve() {}

// Range: 0x8002899C -> 0x800289FC
void TrackPanel::ExportScoreDiffAndTrend(class TrackPanel * const this /* r31 */, int delta /* r30 */) {
    // Local variables
    int trend; // r1+0x8
}

// Range: 0x800289FC -> 0x80028A40
void TrackPanel::ExportScoreDiff(class TrackPanel * const this /* r5 */) {}

static class Timer * _t; // size: 0x4, address: 0x80A490A0
static class Timer * _t; // size: 0x4, address: 0x80A490A8
// Range: 0x80028A40 -> 0x80028BB4
void TrackPanel::Draw(class TrackPanel * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0x14
    class AutoTimer _at; // r1+0x10

    // References
    // -> static class Timer * _t;
    // -> static class Timer * _t;
}

class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class VocalTrackDir * mPtr; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    const class VocalNote * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    const class VocalNote * * _M_start; // offset 0x0, size 0x4
    const class VocalNote * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class Lyric : public Object {
    // total size: 0x70
public:
    class ObjPtr mTextObj; // offset 0x28, size 0xC
    class vector mVocalNotes; // offset 0x34, size 0xC
    class ObjPtr mNoteTube; // offset 0x40, size 0xC
    class Keys mColorKeys; // offset 0x4C, size 0xC
    class Keys mAlphaKeys; // offset 0x58, size 0xC
    class Keys mPositionKeys; // offset 0x64, size 0xC
};
struct _Deque_iterator_base {
    // total size: 0x10
    class Lyric * * _M_cur; // offset 0x0, size 0x4
    class Lyric * * _M_first; // offset 0x4, size 0x4
    class Lyric * * _M_last; // offset 0x8, size 0x4
    class Lyric * * * _M_node; // offset 0xC, size 0x4
};
struct _Deque_iterator : public _Deque_iterator_base {
    // total size: 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Lyric * * * _M_data; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned long _M_data; // offset 0x0, size 0x4
};
class _Deque_base {
    // total size: 0x28
protected:
    struct _Deque_iterator _M_start; // offset 0x0, size 0x10
    struct _Deque_iterator _M_finish; // offset 0x10, size 0x10
    class _STLP_alloc_proxy _M_map; // offset 0x20, size 0x4
    class _STLP_alloc_proxy _M_map_size; // offset 0x24, size 0x4
};
class deque : protected _Deque_base {
    // total size: 0x28
};
struct pair {
    // total size: 0x8
    class RndLine * first; // offset 0x0, size 0x4
    float second; // offset 0x4, size 0x4
};
struct _Deque_iterator_base {
    // total size: 0x10
    struct pair * _M_cur; // offset 0x0, size 0x4
    struct pair * _M_first; // offset 0x4, size 0x4
    struct pair * _M_last; // offset 0x8, size 0x4
    struct pair * * _M_node; // offset 0xC, size 0x4
};
struct _Deque_iterator : public _Deque_iterator_base {
    // total size: 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct pair * * _M_data; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned long _M_data; // offset 0x0, size 0x4
};
class _Deque_base {
    // total size: 0x28
protected:
    struct _Deque_iterator _M_start; // offset 0x0, size 0x10
    struct _Deque_iterator _M_finish; // offset 0x10, size 0x10
    class _STLP_alloc_proxy _M_map; // offset 0x20, size 0x4
    class _STLP_alloc_proxy _M_map_size; // offset 0x24, size 0x4
};
class deque : protected _Deque_base {
    // total size: 0x28
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
struct pair {
    // total size: 0x8
    class RndMesh * first; // offset 0x0, size 0x4
    float second; // offset 0x4, size 0x4
};
struct _Deque_iterator_base {
    // total size: 0x10
    struct pair * _M_cur; // offset 0x0, size 0x4
    struct pair * _M_first; // offset 0x4, size 0x4
    struct pair * _M_last; // offset 0x8, size 0x4
    struct pair * * _M_node; // offset 0xC, size 0x4
};
struct _Deque_iterator : public _Deque_iterator_base {
    // total size: 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct pair * * _M_data; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned long _M_data; // offset 0x0, size 0x4
};
class _Deque_base {
    // total size: 0x28
protected:
    struct _Deque_iterator _M_start; // offset 0x0, size 0x10
    struct _Deque_iterator _M_finish; // offset 0x10, size 0x10
    class _STLP_alloc_proxy _M_map; // offset 0x20, size 0x4
    class _STLP_alloc_proxy _M_map_size; // offset 0x24, size 0x4
};
class deque : protected _Deque_base {
    // total size: 0x28
};
struct _Deque_iterator_base {
    // total size: 0x10
    class TambourineGem * * _M_cur; // offset 0x0, size 0x4
    class TambourineGem * * _M_first; // offset 0x4, size 0x4
    class TambourineGem * * _M_last; // offset 0x8, size 0x4
    class TambourineGem * * * _M_node; // offset 0xC, size 0x4
};
struct _Deque_iterator : public _Deque_iterator_base {
    // total size: 0x10
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TambourineGem * * * _M_data; // offset 0x0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    unsigned long _M_data; // offset 0x0, size 0x4
};
class _Deque_base {
    // total size: 0x28
protected:
    struct _Deque_iterator _M_start; // offset 0x0, size 0x10
    struct _Deque_iterator _M_finish; // offset 0x10, size 0x10
    class _STLP_alloc_proxy _M_map; // offset 0x20, size 0x4
    class _STLP_alloc_proxy _M_map_size; // offset 0x24, size 0x4
};
class deque : protected _Deque_base {
    // total size: 0x28
};
struct LyricSetupInfo {
    // total size: 0x1C
    unsigned char mSpotlight; // offset 0x0, size 0x1
    float mXCentered; // offset 0x4, size 0x4
    float mXPreview; // offset 0x8, size 0x4
    float mPreviewAlpha; // offset 0xC, size 0x4
    float mPhraseTick; // offset 0x10, size 0x4
    float mNextPhraseTick; // offset 0x14, size 0x4
    float mNextPhraseEndTick; // offset 0x18, size 0x4
};
class VocalTrack : public Track {
    // total size: 0x208
protected:
    unsigned char mScoreDebug; // offset 0x64, size 0x1
    float mTimeWindow; // offset 0x68, size 0x4
    enum VocalStyle mVocalStyle; // offset 0x6C, size 0x4
    float mMsInWindow; // offset 0x70, size 0x4
    float mWindowSize; // offset 0x74, size 0x4
    class DirLoader * mLoader; // offset 0x78, size 0x4
    class ObjPtr mDir; // offset 0x7C, size 0xC
    class VocalPlayer * mPlayer; // offset 0x88, size 0x4
    class RndGroup * mNowBar; // offset 0x8C, size 0x4
    class deque mLyrics; // offset 0x90, size 0x28
    float mZBottom; // offset 0xB8, size 0x4
    float mZTop; // offset 0xBC, size 0x4
    float mMinPitchRange; // offset 0xC0, size 0x4
    float mPreviewZ; // offset 0xC4, size 0x4
    float mCurrentZ; // offset 0xC8, size 0x4
    float mPhonomeZ; // offset 0xCC, size 0x4
    float mArrowSmoothing; // offset 0xD0, size 0x4
    class vector mTubeWidths; // offset 0xD4, size 0xC
    float mPhraseStartMs; // offset 0xE0, size 0x4
    float mPhraseEndMs; // offset 0xE4, size 0x4
    float mNextPhraseEndMs; // offset 0xE8, size 0x4
    unsigned int mLastPhonemeLineIdx; // offset 0xEC, size 0x4
    unsigned char mShowPhonemeLine; // offset 0xF0, size 0x1
    int mLastUpdateLyric; // offset 0xF4, size 0x4
    int mLastUpdateGem; // offset 0xF8, size 0x4
    int mLastUpdatePhrase; // offset 0xFC, size 0x4
    int mLastBeat; // offset 0x100, size 0x4
    int mNextScrollNote; // offset 0x104, size 0x4
    int mPhraseChangeDurationTicks; // offset 0x108, size 0x4
    int mTimeBeforePhraseToSpaceTicks; // offset 0x10C, size 0x4
    float mNextPhraseSpacedAnimationRatio; // offset 0x110, size 0x4
    int mNextPhraseFadeInBefore; // offset 0x114, size 0x4
    int mHideCounter; // offset 0x118, size 0x4
    unsigned char mPressToTalk; // offset 0x11C, size 0x1
    unsigned char mSpotlight; // offset 0x11D, size 0x1
    class deque mNoteTubes; // offset 0x120, size 0x28
    class map mNoteTubePool; // offset 0x148, size 0x18
    class map mTextPool; // offset 0x160, size 0x18
    class vector mMeshPool; // offset 0x178, size 0xC
    class deque mMarkers; // offset 0x184, size 0x28
    class deque mMasks; // offset 0x1AC, size 0x28
    class TambourineGemPool * mTambourineGemPool; // offset 0x1D4, size 0x4
    class deque mTambourineGems; // offset 0x1D8, size 0x28
    enum VocalParam mCharOptParam; // offset 0x200, size 0x4
    unsigned char mRemoteBandVocals; // offset 0x204, size 0x1
};
// Range: 0x80028BB4 -> 0x80028C48
void TrackPanel::TogglePhonemeFeedback(class TrackPanel * const this /* r30 */) {
    // Local variables
    int i; // r31
    class VocalTrack * track; // r0

    // References
    // -> struct [anonymous] __RTTI__5Track;
    // -> struct [anonymous] __RTTI__10VocalTrack;
}

// Range: 0x80028C48 -> 0x80028CD0
void TrackPanel::ToggleScoreDebug(class TrackPanel * const this /* r30 */) {
    // Local variables
    int i; // r31
    class VocalTrack * track; // r0

    // References
    // -> struct [anonymous] __RTTI__5Track;
    // -> struct [anonymous] __RTTI__10VocalTrack;
}

// Range: 0x80028CD0 -> 0x80028D58
void TrackPanel::ToggleLyricMode(class TrackPanel * const this /* r30 */) {
    // Local variables
    int i; // r31
    class VocalTrack * track; // r0

    // References
    // -> struct [anonymous] __RTTI__5Track;
    // -> struct [anonymous] __RTTI__10VocalTrack;
}

// Range: 0x80028D58 -> 0x80028DE8
void TrackPanel::SetSmasherGlowing(class TrackPanel * const this /* r28 */, int slot /* r29 */, unsigned char glowing /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x80028DE8 -> 0x80028E68
void TrackPanel::PopSmasher(class TrackPanel * const this /* r29 */, int slot /* r30 */) {
    // Local variables
    int i; // r31
}

static class Message msg; // size: 0x8, address: 0x80976C28
// Range: 0x80028E68 -> 0x80029004
void TrackPanel::ToggleCamTweaking(class TrackPanel * const this /* r31 */) {
    // Local variables
    class Object * config; // r0

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Symbol temp_config; // size: 0x4, address: 0x80A490B0
static class Message sApplyMessage; // size: 0x8, address: 0x80976C40
static unsigned char sDumpData; // size: 0x1, address: 0x80A490B5
enum JoypadType {
    kJoypadNone = 0,
    kJoypadDigital = 1,
    kJoypadAnalog = 2,
    kJoypadDualShock = 3,
    kJoypadMidi = 4,
    kJoypadXboxHxGuitar = 5,
    kJoypadXboxHxGuitarRb2 = 6,
    kJoypadXboxRoGuitar = 7,
    kJoypadXboxDrums = 8,
    kJoypadXboxDrumsRb2 = 9,
    kJoypadXboxStageKit = 10,
    kJoypadPs3HxGuitar = 11,
    kJoypadPs3HxGuitarRb2 = 12,
    kJoypadPs3HxDrums = 13,
    kJoypadPs3HxDrumsRb2 = 14,
    kJoypadPs3RoGuitar = 15,
    kJoypadWiiCore = 16,
    kJoypadWiiFS = 17,
    kJoypadWiiClassic = 18,
    kJoypadWiiGamecube = 19,
    kJoypadWiiGuitar = 20,
    kJoypadWiiDrums = 21,
    kJoypadWiiHxGuitar = 22,
    kJoypadWiiHxGuitarRb2 = 23,
    kJoypadWiiHxDrums = 24,
    kJoypadWiiHxDrumsRb2 = 25,
};
class JoypadData {
    // total size: 0x68
public:
    unsigned int mButtons; // offset 0x0, size 0x4
    unsigned int mNewPressed; // offset 0x4, size 0x4
    unsigned int mNewReleased; // offset 0x8, size 0x4
    float mSticks[2][2]; // offset 0xC, size 0x10
    float mTriggers[2]; // offset 0x1C, size 0x8
    float mSensors[3]; // offset 0x24, size 0xC
    float mPressures[8]; // offset 0x30, size 0x20
    int mUserNum; // offset 0x50, size 0x4
    unsigned char mConnected; // offset 0x54, size 0x1
    unsigned char mForceFeedback; // offset 0x55, size 0x1
    unsigned char mCanForceFeedback; // offset 0x56, size 0x1
    unsigned char mWireless; // offset 0x57, size 0x1
    enum JoypadType mType; // offset 0x58, size 0x4
    class Symbol mControllerType; // offset 0x5C, size 0x4
    float mDistFromRest; // offset 0x60, size 0x4
    unsigned char mHasGreenCymbal; // offset 0x64, size 0x1
    unsigned char mHasYellowCymbal; // offset 0x65, size 0x1
};
// Range: 0x80029004 -> 0x80029BB8
void TrackPanel::PollCameraParameters(class TrackPanel * const this /* r24 */, float ms /* f31 */) {
    // Local variables
    class Object * config; // r29
    class Object * currConfig; // r0
    int i; // r28
    class JoypadData * data; // r0
    float val; // f1
    enum JoypadButton incFadeStart; // r25
    enum JoypadButton decFadeStart; // r24
    enum JoypadButton incFadeLen; // r27
    enum JoypadButton decFadeLen; // r26
    unsigned char backState; // r24

    // References
    // -> class Debug TheDebug;
    // -> static unsigned char sDumpData;
    // -> static class Message sApplyMessage;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol temp_config;
}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x80029BB8 -> 0x80029F8C
void TrackPanel::BuildReloadChecks(class TrackPanel * const this /* r30 */) {}

class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
// Range: 0x80029F8C -> 0x8002A490
void TrackPanel::CleanUpReloadChecks(class TrackPanel * const this /* r31 */) {
    // Local variables
    struct _Rb_tree_iterator it; // r1+0x10
    class map tmp; // r1+0x68
}

// Range: 0x8002A490 -> 0x8002A614
class DataNode TrackPanel::ForEachTrack(class TrackPanel * const this /* r28 */, const class DataArray * a /* r29 */) {
    // Local variables
    class DataNode * var; // r31
    class DataNode tmp; // r1+0x18
    int i; // r30
    int j; // r26
}

// Range: 0x8002A614 -> 0x8002A688
int TrackPanel::BandNumToSlot() {
    // Local variables
    class Player * player; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Game * TheGame;
}

// Range: 0x8002A688 -> 0x8002A690
void TrackPanel::GetTrackOrder() {
    // References
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x8002A690 -> 0x8002A698
int TrackPanel::GetNumPlayers() {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8002A698 -> 0x8002A6B4
unsigned char TrackPanel::IsGameOver() {
    // References
    // -> class GamePanel * TheGamePanel;
}

// Range: 0x8002A6B4 -> 0x8002A6C8
unsigned char TrackPanel::InGame() {
    // References
    // -> class Game * TheGame;
}

// Range: 0x8002A6C8 -> 0x8002A6D4
int TrackPanel::MaxDeltaPoints() {
    // References
    // -> class Game * TheGame;
}

// Range: 0x8002A6D4 -> 0x8002A6E0
int TrackPanel::GetTieWindow() {
    // References
    // -> class Game * TheGame;
}

// Range: 0x8002A6E0 -> 0x8002A758
void TrackPanel::UnisonPlayerSuccess(class Player * p /* r30 */) {
    // Local variables
    class EndingBonus * endingBonus; // r31
}

static class Message set_glowing; // size: 0x8, address: 0x80976C58
// Range: 0x8002A758 -> 0x8002AA44
void TrackPanel::SetWinningGlow(int val /* r29 */, class RndDir * icon0 /* r30 */, class RndDir * icon1 /* r31 */) {
    // Local variables
    enum EndGameResult result; // r0

    // References
    // -> static class Message set_glowing;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8002AA44 -> 0x8002AA74
unsigned char TrackPanel::GetNoCrowdMeter() {}

// Range: 0x8002AA74 -> 0x8002AA7C
enum ExcitementLevel TrackPanel::GetGameExcitement() {
    // References
    // -> class Game * TheGame;
}

static class Object * gameMode; // size: 0x4, address: 0x80A490B8
// Range: 0x8002AA7C -> 0x8002AB4C
void TrackPanel::PushCrowdReaction(unsigned char maxed /* r31 */) {
    // References
    // -> static class Object * gameMode;
    // -> class Game * TheGame;
}

// Range: 0x8002AB4C -> 0x8002AD24
void TrackPanel::SetBotbTarget(class TrackPanel * const this /* r28 */, int end /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x8002AD24 -> 0x8002AD5C
void TrackPanel::SetPlayStarSfx() {
    // Local variables
    int i; // r6
}

static class Symbol _s; // size: 0x4, address: 0x80A490C0
static class Symbol _s; // size: 0x4, address: 0x80A490C8
static class Symbol _s; // size: 0x4, address: 0x80A490D0
static class Symbol _s; // size: 0x4, address: 0x80A490D8
static class Symbol _s; // size: 0x4, address: 0x80A490E0
static class Symbol _s; // size: 0x4, address: 0x80A490E8
static class Symbol _s; // size: 0x4, address: 0x80A490F0
static class Symbol _s; // size: 0x4, address: 0x80A490F8
static class Symbol _s; // size: 0x4, address: 0x80A49100
static class Symbol _s; // size: 0x4, address: 0x80A49108
static class Symbol _s; // size: 0x4, address: 0x80A49110
static class Symbol _s; // size: 0x4, address: 0x80A49118
static class Symbol _s; // size: 0x4, address: 0x80A49120
static class Symbol _s; // size: 0x4, address: 0x80A49128
static class Symbol _s; // size: 0x4, address: 0x80A49130
// Range: 0x8002AD5C -> 0x8002BE70
class DataNode TrackPanel::Handle(class TrackPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x5C
    class MessageTimer _mt; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode _n; // r1+0x60

    // References
    // -> class Debug TheDebug;
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x8
} __RTTI__10VocalTrack; // size: 0x8, address: 0x8086FEE8
struct {
    // total size: 0x8
} __RTTI__17TrackPanelDirBase; // size: 0x8, address: 0x8086FF90
struct {
    // total size: 0x8
} __RTTI__10Scoreboard; // size: 0x8, address: 0x808700D8
struct {
    // total size: 0x8
} __RTTI__11EndingBonus; // size: 0x8, address: 0x80870140
struct {
    // total size: 0xD8
} __vt__10TrackPanel; // size: 0xD8, address: 0x80870248
struct {
    // total size: 0x8
} __RTTI__10TrackPanel; // size: 0x8, address: 0x80870350
struct {
    // total size: 0xD8
} __vt__19TrackPanelInterface; // size: 0xD8, address: 0x808703F0
struct {
    // total size: 0x8
} __RTTI__19TrackPanelInterface; // size: 0x8, address: 0x808704F8
struct {
    // total size: 0x8
} __RTTI__PP11EndingBonus; // size: 0x8, address: 0x80870590
struct {
    // total size: 0x8
} __RTTI__PP10Scoreboard; // size: 0x8, address: 0x808705A8
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std60_Rb_tree_node<Q211stlpmtx_std28pair<C6Symbol,P10DepChecker>>; // size: 0x8, address: 0x80870610
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
enum TourMode {
    kMetaTour_StartNew = 0,
    kMetaTour_UnknownRemote = 1,
    kMetaTour_KnownLocal = 2,
    kMetaTour_KnownRemote = 3,
    kMetaTour_BrowsingRemote = 4,
    kMetaTour_Max = 5,
    kMetaTour_Nil = -1,
};
class Tour : public Object {
    // total size: 0xE8
public:
    class list mTestChars; // offset 0x28, size 0x8
private:
    const class SongMgr & mSongMgr; // offset 0x30, size 0x4
    class TourWorld * mWorld; // offset 0x34, size 0x4
    class TourChallenge * mChallenge; // offset 0x38, size 0x4
    class TourBand * mBand; // offset 0x3C, size 0x4
    class HxGuid * mLastBandSet; // offset 0x40, size 0x4
    class TownProvider * mTownProvider; // offset 0x44, size 0x4
    class VenueProvider * mVenueProvider; // offset 0x48, size 0x4
    class EventProvider * mEventProvider; // offset 0x4C, size 0x4
    class EventSongProvider * mEventSongProvider; // offset 0x50, size 0x4
    class HometownProvider * mHometownProvider; // offset 0x54, size 0x4
    class RequirementProvider * mRequirementProvider; // offset 0x58, size 0x4
    class StaffProvider * mStaffProvider; // offset 0x5C, size 0x4
    class TourBandLocal * mNewBand; // offset 0x60, size 0x4
    unsigned char mWinSequence; // offset 0x64, size 0x1
    class list mSharedChallengeBattles[4]; // offset 0x68, size 0x20
    class list mSharedWorldBattles[4]; // offset 0x88, size 0x20
    unsigned char mDirtyBattles; // offset 0xA8, size 0x1
    class Timer mValidBattleTimer; // offset 0xB0, size 0x38
};

