/*
    Compile unit: C:\rockband2\band2\src\meta\MetaPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80115848 -> 0x80118218
*/
class DataArray * types; // size: 0x4, address: 0x80A4B7F0
class Symbol name; // size: 0x4, address: 0x80A4B7F8
class Symbol name; // size: 0x4, address: 0x80A4B800
class Symbol name; // size: 0x4, address: 0x80A4B808
class Symbol name; // size: 0x4, address: 0x80A4B810
class Symbol name; // size: 0x4, address: 0x80A4B818
class Symbol name; // size: 0x4, address: 0x80A4B820
class Symbol name; // size: 0x4, address: 0x80A4B828
class Symbol name; // size: 0x4, address: 0x80A4B830
class Symbol name; // size: 0x4, address: 0x80A4B838
class Symbol name; // size: 0x4, address: 0x80A4B840
class Symbol name; // size: 0x4, address: 0x80A4B848
class Symbol name; // size: 0x4, address: 0x80A4B850
class Symbol name; // size: 0x4, address: 0x80A4B858
class Symbol name; // size: 0x4, address: 0x80A4B860
class Symbol name; // size: 0x4, address: 0x80A4B868
class Symbol name; // size: 0x4, address: 0x80A4B870
class Symbol name; // size: 0x4, address: 0x80A4B878
class Symbol name; // size: 0x4, address: 0x80A4B880
class Symbol name; // size: 0x4, address: 0x80A4B888
class Symbol name; // size: 0x4, address: 0x80A4B890
class Symbol name; // size: 0x4, address: 0x80A4B898
class Symbol name; // size: 0x4, address: 0x80A4B8A0
class Symbol name; // size: 0x4, address: 0x80A4B8A8
class Symbol name; // size: 0x4, address: 0x80A4B8B0
class Symbol name; // size: 0x4, address: 0x80A4B8B8
class Symbol name; // size: 0x4, address: 0x80A4B8C0
class Symbol name; // size: 0x4, address: 0x80A4B8C8
class Symbol name; // size: 0x4, address: 0x80A4B8D0
class Symbol name; // size: 0x4, address: 0x80A4B8D8
class Symbol name; // size: 0x4, address: 0x80A4B8E0
class Symbol name; // size: 0x4, address: 0x80A4B8E8
class Symbol name; // size: 0x4, address: 0x80A4B8F0
class Symbol name; // size: 0x4, address: 0x80A4B8F8
class Symbol name; // size: 0x4, address: 0x80A4B900
class Symbol name; // size: 0x4, address: 0x80A4B908
class Symbol name; // size: 0x4, address: 0x80A4B910
class Symbol name; // size: 0x4, address: 0x80A4B918
unsigned char sUnlockAll; // size: 0x1, address: 0x80A4B91C
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct ChallengePrereq {
    // total size: 0xC
    unsigned char mAll; // offset 0x0, size 0x1
    class list mChallenges; // offset 0x4, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
enum ChallengeEventType {
    kChallengeAuthored = 0,
    kChallengeAlbum = 1,
    kChallengeArtist = 2,
    kChallengePack = 3,
};
class TourChallengeEvent : public TourEvent {
    // total size: 0xD8
    int mDiffTier; // offset 0x90, size 0x4
    class list mPrereqs; // offset 0x94, size 0x8
    int mMinPlayers; // offset 0x9C, size 0x4
    class vector mVenues; // offset 0xA0, size 0xC
    class String mCoverArt; // offset 0xAC, size 0xC
    class String mBackArt; // offset 0xB8, size 0xC
    unsigned char mShowListName; // offset 0xC4, size 0x1
    enum ChallengeEventType mType; // offset 0xC8, size 0x4
    class Symbol mAutoGenre; // offset 0xCC, size 0x4
    int mAutoDecade; // offset 0xD0, size 0x4
    class Symbol mAchievement; // offset 0xD4, size 0x4
};
class TourChallenge {
    // total size: 0x20
    const class SongMgr & mSongMgr; // offset 0x0, size 0x4
    class vector mChallenges; // offset 0x4, size 0xC
    class vector mDisabledBattles; // offset 0x10, size 0xC
    int mAutoMinSongs; // offset 0x1C, size 0x4
};
class DOFOverrideParams {
    // total size: 0x1C
protected:
    float mDepthScale; // offset 0x0, size 0x4
    float mDepthOffset; // offset 0x4, size 0x4
    float mMinBlurScale; // offset 0x8, size 0x4
    float mMinBlurOffset; // offset 0xC, size 0x4
    float mMaxBlurScale; // offset 0x10, size 0x4
    float mMaxBlurOffset; // offset 0x14, size 0x4
    float mBlurWidthScale; // offset 0x18, size 0x4
};
class RndPostProc : public Object, public PostProcessor {
    // total size: 0x1B0
protected:
    class Color mBloomColor; // offset 0x30, size 0x10
    float mBloomThreshold; // offset 0x40, size 0x4
    float mBloomSize; // offset 0x44, size 0x4
    float mBloomIntensity; // offset 0x48, size 0x4
    class ObjPtr mLuminanceMap; // offset 0x4C, size 0xC
    class RndColorXfm mColorXfm; // offset 0x60, size 0xA0
    float mPosterLevels; // offset 0x100, size 0x4
    float mPosterMin; // offset 0x104, size 0x4
    float mMirror; // offset 0x108, size 0x4
    class Vector2 mModBounds; // offset 0x10C, size 0x8
    class Vector2 mTimeBounds; // offset 0x114, size 0x8
    class Vector2 mSeconds; // offset 0x11C, size 0x8
    class Vector2 mModulate; // offset 0x124, size 0x8
    float mColorModulation; // offset 0x12C, size 0x4
    class Vector2 mNoiseBaseScale; // offset 0x130, size 0x8
    float mNoiseTopScale; // offset 0x138, size 0x4
    float mNoiseIntensity; // offset 0x13C, size 0x4
    unsigned char mNoiseStationary; // offset 0x140, size 0x1
    class ObjPtr mNoiseMap; // offset 0x144, size 0xC
    float mTrailThreshold; // offset 0x150, size 0x4
    float mTrailDuration; // offset 0x154, size 0x4
    class Vector3 mBlendVec; // offset 0x160, size 0x10
    float mEmulateFPS; // offset 0x170, size 0x4
    float mLastRender; // offset 0x174, size 0x4
    float mDeltaSecs; // offset 0x178, size 0x4
    unsigned char mHallOfTimeSolidRings; // offset 0x17C, size 0x1
    float mHallOfTimeRate; // offset 0x180, size 0x4
    class Color mHallOfTimeColor; // offset 0x190, size 0x10
    float mHallOfTimeMix; // offset 0x1A0, size 0x4
    float mDistortionScale; // offset 0x1A4, size 0x4
    int mDistortionWidth; // offset 0x1A8, size 0x4
    int mDistortionHeight; // offset 0x1AC, size 0x4
};
// Range: 0x80115848 -> 0x80115868
class DataNode MetaPanel::ToggleUnlockAll() {
    // References
    // -> unsigned char sUnlockAll;
}

// Range: 0x80115868 -> 0x801167D4
void MetaPanel::Init() {
    // References
    // -> class NetMessageFactory TheNetMessageFactory;
    // -> class BotbChallengeLoader TheBotbChallengeLoader;
    // -> class ProfileMgr TheProfileMgr;
    // -> class MemcardMgr TheMemcardMgr;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
}

enum BotbNetProgress {
    BotbNetUninitialized = 0,
    BotbNetClientDetailsState = 1,
    BotbNetClientWaitingForHost = 2,
    BotbNetDetailsState = 3,
    BotbNetNewsState = 4,
    BotbNetResultsState = 5,
    BotbNetBandResultsState = 6,
    BotbNetFriendsState = 7,
    BotbNetOverallState = 8,
    BotbNetTryToPlay = 9,
    BotbNetRequestProfile = 10,
    BotbNetOverallNextPage = 11,
    BotbNetDone = 12,
};
struct BotbSetListItem {
    // total size: 0x10
    const char * mSongName; // offset 0x0, size 0x4
    class Symbol mSongShortName; // offset 0x4, size 0x4
    const char * mArtist; // offset 0x8, size 0x4
    unsigned char mAvailable; // offset 0xC, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BotbSetListItem * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BotbSetListItem * _M_start; // offset 0x0, size 0x4
    struct BotbSetListItem * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class BotbEntryCondition {
    // total size: 0x8
    char mType; // offset 0x0, size 0x1
    unsigned char mSecondGuitar; // offset 0x1, size 0x1
    int mParam; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BotbEntryCondition * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BotbEntryCondition * _M_start; // offset 0x0, size 0x4
    class BotbEntryCondition * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class BotbPerformanceModifier {
    // total size: 0x8
    char mType; // offset 0x0, size 0x1
    int mParam; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BotbPerformanceModifier * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BotbPerformanceModifier * _M_start; // offset 0x0, size 0x4
    class BotbPerformanceModifier * _M_finish; // offset 0x4, size 0x4
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
    class BotbBattleResultsRow * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BotbBattleResultsRow * * _M_start; // offset 0x0, size 0x4
    class BotbBattleResultsRow * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
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
class BotbScoresProvider : public ListProvider, public Object {
    // total size: 0x68
    class vector mList; // offset 0x2C, size 0xC
    class map mListMap; // offset 0x38, size 0x18
    class list mListLru; // offset 0x50, size 0x8
    enum WinMetric mWinMetric; // offset 0x58, size 0x4
    int mSize; // offset 0x5C, size 0x4
    int mRank; // offset 0x60, size 0x4
    void (* mQueryCallback)(int); // offset 0x64, size 0x4
};
class BotbSetListProvider : public ListProvider, public Object {
    // total size: 0x30
    class vector * mItems; // offset 0x2C, size 0x4
};
class BotbRulesListProvider : public ListProvider, public Object {
    // total size: 0x38
    class vector & mEntryConditions; // offset 0x2C, size 0x4
    class vector & mPerformanceModifiers; // offset 0x30, size 0x4
    class BandData * mBandData; // offset 0x34, size 0x4
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
class UIScreenChangeMsg : public Message {
    // total size: 0x8
};
class BotbPanel : public TabInterfacePanel, public Synchronizable {
    // total size: 0x218
    unsigned char mGotDetails; // offset 0x70, size 0x1
    unsigned char mRockCentralFailed; // offset 0x71, size 0x1
    unsigned int mQueryTimeSeconds; // offset 0x74, size 0x4
    unsigned int mTimeLeftSeconds; // offset 0x78, size 0x4
    class UILabel * mTimeLeftLabel; // offset 0x7C, size 0x4
    class BandData * mBandData; // offset 0x80, size 0x4
    enum BotbNetProgress mNetProgress; // offset 0x84, size 0x4
    enum BotbNetProgress mPendingNetRequest; // offset 0x88, size 0x4
    class HxGuid mNetBandGuid; // offset 0x8C, size 0x10
    unsigned int mBattleId; // offset 0x9C, size 0x4
    class HxGuid mBandId; // offset 0xA0, size 0x10
    class Timer mValidCacheTimer; // offset 0xB0, size 0x38
    int mFocusTabIdx; // offset 0xE8, size 0x4
    class String mFocusName; // offset 0xEC, size 0xC
    unsigned char mRequestedFocus; // offset 0xF8, size 0x1
    int mFocusFirstShowing; // offset 0xFC, size 0x4
    int mFocusSelected; // offset 0x100, size 0x4
    unsigned char mBackingOut; // offset 0x104, size 0x1
    class vector mSetList; // offset 0x108, size 0xC
    unsigned char mHasAllSongs; // offset 0x114, size 0x1
    unsigned char mBattleClosed; // offset 0x115, size 0x1
    class vector mEntryConditions; // offset 0x118, size 0xC
    class vector mPerformanceModifiers; // offset 0x124, size 0xC
    class FileLoader * mAlbumArtLoader; // offset 0x130, size 0x4
    class BotbBattleDetails mNetDetails; // offset 0x134, size 0xC
    class BotbBattleResultsList mNetResults; // offset 0x140, size 0x18
    class BotbBattleResultsList mNetFriendsResults; // offset 0x158, size 0x18
    class BotbBattleResultsList mNetOverallResults; // offset 0x170, size 0x18
    class BotbBattleResultsByBandInfo mNetBandResults; // offset 0x188, size 0x4
    class BotbPlayBattleResponse mNetBattleResponse; // offset 0x18C, size 0x14
    int mDirtySyncFlags; // offset 0x1A0, size 0x4
    unsigned char mClientReceivedHostData; // offset 0x1A4, size 0x1
    unsigned char mClientReceivedRockCentralData; // offset 0x1A5, size 0x1
    class BotbScoresProvider * mFriendsResultsProvider; // offset 0x1A8, size 0x4
    class BotbScoresProvider * mOverallResultsProvider; // offset 0x1AC, size 0x4
    unsigned char mDirtyOverallResults; // offset 0x1B0, size 0x1
    class BotbSetListProvider * mSetListProvider; // offset 0x1B4, size 0x4
    class BotbRulesListProvider * mRulesListProvider; // offset 0x1B8, size 0x4
    unsigned char mCreatedNetBandProfile; // offset 0x1BC, size 0x1
    class RemoteBandData * mNetBandProfile; // offset 0x1C0, size 0x4
    class UILabel * mDebugNetworkLabel; // offset 0x1C4, size 0x4
    class UILabel * mNetworkFailedLabel; // offset 0x1C8, size 0x4
    class RndGroup * mLoadingGroup; // offset 0x1CC, size 0x4
    class map mResultsCache; // offset 0x1D0, size 0x18
};
enum BotbNewsNetProgress {
    BotbNewsNetGetNews = 0,
    BotbNewsNetDone = 1,
};
class BotbNewsProvider : public ListProvider, public Object {
    // total size: 0x3C
    class vector & mItems; // offset 0x2C, size 0x4
    const class vector & mCovers; // offset 0x30, size 0x4
    class RndMat * mDefaultMat; // offset 0x34, size 0x4
    class RndMat * mTrimMat; // offset 0x38, size 0x4
};
class BotbNewsFeedPanel : public TexLoadPanel {
    // total size: 0xC8
protected:
    class vector mItems; // offset 0x40, size 0xC
    unsigned char mHasNews; // offset 0x4C, size 0x1
    class HxGuid mBandId; // offset 0x50, size 0x10
    enum BotbNewsNetProgress mNetState; // offset 0x60, size 0x4
    class BotbNewsList mNewsList; // offset 0x64, size 0x34
    class BotbNewsProvider * mNewsProvider; // offset 0x98, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class BotbNewsItem {
    // total size: 0x118
    char mType; // offset 0x0, size 0x1
    int mNum1; // offset 0x4, size 0x4
    int mNum2; // offset 0x8, size 0x4
    int mSeconds; // offset 0xC, size 0x4
    int mBattleName; // offset 0x10, size 0x4
    char mParseBuf[255]; // offset 0x14, size 0xFF
    const char * mIcon; // offset 0x114, size 0x4
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BotbNewsItem * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BotbNewsItem * _M_start; // offset 0x0, size 0x4
    class BotbNewsItem * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class list {
    // total size: 0x0
};
class Movie {
    // total size: 0x4
    struct Impl * mImpl; // offset 0x0, size 0x4
};
class MoviePanel : public UIPanel {
    // total size: 0x84
protected:
    unsigned char mPreload; // offset 0x30, size 0x1
    unsigned char mAudio; // offset 0x31, size 0x1
    unsigned char mLoop; // offset 0x32, size 0x1
    unsigned char mUpdatePresence; // offset 0x33, size 0x1
    unsigned char mFillWidth; // offset 0x34, size 0x1
    const char * mCurrentMovie; // offset 0x38, size 0x4
    class vector mMovies; // offset 0x3C, size 0xC
    class list mRecent; // offset 0x48, size 0x8
    class Movie mMovie; // offset 0x50, size 0x4
    unsigned char mAnamorphic; // offset 0x54, size 0x1
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    const char * _M_data; // offset 0x8, size 0x4
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
class MultiFocusScreen : public BandScreen {
    // total size: 0x4C
    class DataArray * mOptions; // offset 0x3C, size 0x4
    class vector mPanels; // offset 0x40, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class PanelDir * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PanelDir * * _M_start; // offset 0x0, size 0x4
    class PanelDir * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class MultiSelectListPanel : public UIPanel {
    // total size: 0x90
    class RndMesh * mSelectionMesh; // offset 0x30, size 0x4
    class UIList * mScrollList; // offset 0x34, size 0x4
    int mStartSection; // offset 0x38, size 0x4
    int mDrawStart; // offset 0x3C, size 0x4
    int mDrawEnd; // offset 0x40, size 0x4
    float mSpacing; // offset 0x44, size 0x4
    float mHeightMultiplier; // offset 0x48, size 0x4
    class Vector3 mSelectionStart; // offset 0x50, size 0x10
};
class NextSongPanel : public UIPanel {
    // total size: 0x60
    float mEnterTime; // offset 0x30, size 0x4
};
class OutfitConfigPanel : public UIPanel {
    // total size: 0x80
    int mColorIdx; // offset 0x30, size 0x4
    class vector mSelectedColors; // offset 0x34, size 0xC
    class vector mInitialColors; // offset 0x40, size 0xC
    class OutfitPanel * mOutfitPanel; // offset 0x4C, size 0x4
    unsigned char mConfirm; // offset 0x50, size 0x1
};
class OutfitGroupPanel : public UIPanel, public ListProvider {
    // total size: 0x74
    class OutfitPanel * mOutfitPanel; // offset 0x34, size 0x4
    class vector mOutfits; // offset 0x38, size 0xC
    class Symbol mSelectedOutfit; // offset 0x44, size 0x4
};
class OutfitPanel : public UIPanel {
    // total size: 0x68
    class Symbol mSelectedOutfit; // offset 0x30, size 0x4
    class OutfitLoader * mOutfitLoader; // offset 0x34, size 0x4
    unsigned char mUsedUnlockAll; // offset 0x38, size 0x1
};
class PassiveMessagesPanel : public UIPanel {
    // total size: 0xA8
    class list mMsgQueue; // offset 0x30, size 0x8
    class Timer mTimer; // offset 0x38, size 0x38
    int mMsgDuration; // offset 0x70, size 0x4
    class PassiveMessenger * mMessenger; // offset 0x74, size 0x4
    class RndAnimatable * mMsgAnim; // offset 0x78, size 0x4
};
class PracticeBackgroundPanel : public UIPanel {
    // total size: 0x5C
};
class PracticePanel : public UIPanel {
    // total size: 0x68
    unsigned char mInVocalMode; // offset 0x30, size 0x1
    class Fader * mFader; // offset 0x34, size 0x4
    float mSpeedRatio; // offset 0x38, size 0x4
};
class PreloadPanel : public UIPanel, public Callback {
    // total size: 0x46C
    unsigned char mPreloadOK; // offset 0x34, size 0x1
    unsigned char mMounted; // offset 0x35, size 0x1
    class Symbol mSongContent; // offset 0x38, size 0x4
    char mLipSyncPath[256]; // offset 0x3C, size 0x100
    char mWeightsPath[256]; // offset 0x13C, size 0x100
    char mPanPath[256]; // offset 0x23C, size 0x100
    char mMidiPath[256]; // offset 0x33C, size 0x100
    unsigned char mLipSyncBackup; // offset 0x43C, size 0x1
};
enum PresenceInfo {
    kSearching = 0,
    kFailed = 1,
    kJoining = 2,
    kSuccess = 3,
    kNoInstrument = 4,
    kNoMultiplayerPrivilege = 5,
};
class SessionFindingPanel : public UIPanel {
    // total size: 0x74
    class BandUser * mJoiningUser; // offset 0x30, size 0x4
    class vector mJoiningPads; // offset 0x34, size 0xC
    class CharData * mJoiningChar; // offset 0x40, size 0x4
    enum TrackType mJoiningTrackType; // offset 0x44, size 0x4
};
class SessionPanel : public UIPanel {
    // total size: 0x60
    unsigned char mWaitingForSessionReady; // offset 0x30, size 0x1
};
class SigninScreen : public BandScreen {
    // total size: 0x40
    unsigned char mMustNotBeAGuest; // offset 0x3A, size 0x1
    unsigned char mMustBeOnline; // offset 0x3B, size 0x1
    unsigned char mMustBeMultiplayerCapable; // offset 0x3C, size 0x1
    unsigned char mHandleSignOuts; // offset 0x3D, size 0x1
    unsigned char mLimitUserSignin; // offset 0x3E, size 0x1
    unsigned char mSigninMsgDuringGuide; // offset 0x3F, size 0x1
};
class SongSyncPanel : public UIPanel {
    // total size: 0x68
    unsigned char mDiskError; // offset 0x30, size 0x1
    unsigned char mSentSongData; // offset 0x31, size 0x1
    unsigned char mLeaderIsReady; // offset 0x32, size 0x1
    unsigned char mSyncComplete; // offset 0x33, size 0x1
    class list mRemoteUsers; // offset 0x34, size 0x8
};
struct ArtEntry {
    // total size: 0x14
    class String mStrName; // offset 0x0, size 0xC
    class NetCacheLoader * mLoader; // offset 0xC, size 0x4
    class RndBitmap * mBmp; // offset 0x10, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct ArtEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct ArtEntry * _M_start; // offset 0x0, size 0x4
    struct ArtEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct NewReleaseEntry {
    // total size: 0x28
    class String mStrName; // offset 0x0, size 0xC
    class String mText1; // offset 0xC, size 0xC
    class String mText2; // offset 0x18, size 0xC
    int mReleaseNum; // offset 0x24, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct NewReleaseEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct NewReleaseEntry * _M_start; // offset 0x0, size 0x4
    struct NewReleaseEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StoreMainPanel : public StoreUIPanel {
    // total size: 0xD0
    class DataArray * mDataConfig; // offset 0x30, size 0x4
    float mTimeNextEvent; // offset 0x34, size 0x4
    int mCurrentEntry; // offset 0x38, size 0x4
    unsigned char mIsCrossfading; // offset 0x3C, size 0x1
    float mDtDisplay; // offset 0x40, size 0x4
    float mDtCrossfade; // offset 0x44, size 0x4
    unsigned char mIsFirst; // offset 0x48, size 0x1
    class RndTex * mTexArtA; // offset 0x4C, size 0x4
    class RndTex * mTexArtB; // offset 0x50, size 0x4
    class RndMat * mMatArtA; // offset 0x54, size 0x4
    class RndMat * mMatArtB; // offset 0x58, size 0x4
    class RndMesh * mMeshArtA; // offset 0x5C, size 0x4
    class RndMesh * mMeshArtB; // offset 0x60, size 0x4
    class RndMat * mMatArtNone; // offset 0x64, size 0x4
    class RndMesh * mMeshArtNone; // offset 0x68, size 0x4
    class RndMat * mMatTextFade; // offset 0x6C, size 0x4
    class RndMesh * mMeshTextFade; // offset 0x70, size 0x4
    class BandLabel * mLabelText1; // offset 0x74, size 0x4
    class BandLabel * mLabelText2; // offset 0x78, size 0x4
    class vector mArtList; // offset 0x7C, size 0xC
    class vector mNewReleaseList; // offset 0x88, size 0xC
    const char * mStrText1Prev; // offset 0x94, size 0x4
    const char * mStrText1Next; // offset 0x98, size 0x4
    const char * mStrText2Prev; // offset 0x9C, size 0x4
    const char * mStrText2Next; // offset 0xA0, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class StoreFilter * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class StoreFilter * _M_start; // offset 0x0, size 0x4
    class StoreFilter * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class SelectedFilter : public Object {
    // total size: 0x34
public:
    class vector mSelected; // offset 0x28, size 0xC
};
class StoreOffer : public Offer {
    // total size: 0x50
    unsigned char mPurchased; // offset 0x2C, size 0x1
    unsigned char mAvailable; // offset 0x2D, size 0x1
    class String mContentIndex; // offset 0x30, size 0xC
    class String mGameCode; // offset 0x3C, size 0xC
    unsigned short mPointsPrice; // offset 0x48, size 0x2
    unsigned short mContentId; // offset 0x4A, size 0x2
    unsigned char mDownloaded; // offset 0x4C, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class StoreOffer * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class StoreOffer * _M_start; // offset 0x0, size 0x4
    class StoreOffer * _M_finish; // offset 0x4, size 0x4
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
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class list : public _List_base {
    // total size: 0x8
};
enum StoreError {
    kStoreErrorSuccess = 0,
    kStoreErrorNoContent = 1,
    kStoreErrorCacheNoSpace = 2,
    kStoreErrorCacheRemoved = 3,
    kStoreErrorLiveServer = 4,
    kStoreErrorStoreServer = 5,
    kStoreErrorSignedOut = 6,
    kStoreErrorEcommerce = 7,
};
class StorePanel : public UIPanel {
    // total size: 0xD0
    class FilterProvider * mFilterProvider; // offset 0x30, size 0x4
    class StoreOfferProvider * mStoreOfferProvider; // offset 0x34, size 0x4
    class InfoProvider * mInfoProvider; // offset 0x38, size 0x4
    class GroupProvider * mGroupProvider; // offset 0x3C, size 0x4
    class InfoSongProvider * mInfoSongProvider; // offset 0x40, size 0x4
    class vector mFilters; // offset 0x44, size 0xC
    int mCurFilterDepth; // offset 0x50, size 0x4
    class SelectedFilter * mSelectedFilter; // offset 0x54, size 0x4
    class UILabel * mFilterCrumb; // offset 0x58, size 0x4
    class vector mOffers; // offset 0x5C, size 0xC
    class DataArray * mDecadeOptions; // offset 0x68, size 0x4
    class DataArray * mGenreOptions; // offset 0x6C, size 0x4
    unsigned char mLoadOK; // offset 0x70, size 0x1
    unsigned char mShowTestOffers; // offset 0x71, size 0x1
    class DataNetLoader * mMetadataLoader; // offset 0x74, size 0x4
    class DataArray * mMetadata; // offset 0x78, size 0x4
    class list mLoaders; // offset 0x7C, size 0x8
    class NetCacheLoader * mPendingArtLoader; // offset 0x84, size 0x4
    class RndTex * mPendingArtTex; // offset 0x88, size 0x4
    class Object * mPendingArtCallback; // offset 0x8C, size 0x4
    class StorePreviewMgrWii * mStorePreviewMgr; // offset 0x90, size 0x4
    class StoreEnumeration * mEnum; // offset 0x94, size 0x4
    unsigned char mSessionCreated; // offset 0x98, size 0x1
    unsigned char mNeedToEnumerate; // offset 0x99, size 0x1
    unsigned char mInCheckout; // offset 0x9A, size 0x1
    class StoreOffer * mCurrentOffer; // offset 0x9C, size 0x4
    unsigned char mCommerceStarted; // offset 0xA0, size 0x1
};
class StoreHeldButtonPanel : public HeldButtonPanel {
    // total size: 0x68
};
class StoreUIPanel : public UIPanel {
    // total size: 0x5C
};
class StoreUnloadPanel : public StoreUIPanel {
    // total size: 0x5C
};
struct /* @class$46408MetaPanel_cpp */ {
    // total size: 0x1C
    int mBattleID; // offset 0x0, size 0x4
    int mAccumScore; // offset 0x4, size 0x4
    int mTotalStars; // offset 0x8, size 0x4
    class HxGuid mBandGuid; // offset 0xC, size 0x10
};
class TourChallengeCompletePanel : public UIPanel {
    // total size: 0x80
    class BotbRecordBattleResponse mBotbResponse; // offset 0x30, size 0x4
    unsigned char mNeedsUnpack; // offset 0x34, size 0x1
    unsigned char mNetDone; // offset 0x35, size 0x1
    struct /* @class$46408MetaPanel_cpp */ {
        // total size: 0x1C
        int mBattleID; // offset 0x0, size 0x4
        int mAccumScore; // offset 0x4, size 0x4
        int mTotalStars; // offset 0x8, size 0x4
        class HxGuid mBandGuid; // offset 0xC, size 0x10
    } mSubmittedData; // offset 0x38, size 0x1C
};
class TourChallengeDetailsPanel : public TexLoadPanel {
    // total size: 0x74
    class ChallengeSongProvider * mSongProvider; // offset 0x40, size 0x4
    unsigned char mHasBackArt; // offset 0x44, size 0x1
};
class TourChallengePanel : public TexLoadPanel {
    // total size: 0x70
    class ChallengeProvider * mChallengeProvider; // offset 0x40, size 0x4
};
class TourChallengeTierPanel : public UIPanel {
    // total size: 0x60
    class ChallengeTierProvider * mTierProvider; // offset 0x30, size 0x4
};
class TutorialDrawPanel : public UIPanel {
    // total size: 0x60
protected:
    class TutorialPanel * mActivePanel; // offset 0x30, size 0x4
};
class TutorialBackgroundPanel : public TutorialDrawPanel {
    // total size: 0x60
};
class TutorialTVOverlayPanel : public TutorialDrawPanel {
    // total size: 0x60
};
class TutorialTVScreenPanel : public TutorialDrawPanel {
    // total size: 0x60
};
class VocalsTutorialPanel : public TutorialPanel {
    // total size: 0xF8
    class list mCallbackList; // offset 0xC0, size 0x8
};
// Range: 0x801167D4 -> 0x80116AC4
void * MetaPanel::MetaPanel(class MetaPanel * const this /* r30 */) {
    // Local variables
    int i; // r28
    class DataArray * backSfxArray; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> class SongMgr & TheSongMgr;
    // -> struct [anonymous] __vt__9MetaPanel;
}

// Range: 0x80116AC4 -> 0x80116DF8
void * MetaPanel::~MetaPanel(class MetaPanel * const this /* r30 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> struct [anonymous] __vt__9MetaPanel;
}

// Range: 0x80116E68 -> 0x80116E70
class MetaMusic * MetaPanel::GetMetaMusic() {}

// Range: 0x80116E70 -> 0x801173C4
void MetaPanel::Load(class MetaPanel * const this /* r31 */) {
    // Local variables
    class DataArray * loopArray; // r29
    int idx; // r0
    const char * filename; // r29

    // References
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class SongPreview TheSongPreview;
}

// Range: 0x801173C4 -> 0x80117470
unsigned char MetaPanel::IsLoaded(class MetaPanel * const this /* r29 */) {}

// Range: 0x80117470 -> 0x80117664
void MetaPanel::FinishLoad(class MetaPanel * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Synth * TheSynth;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80117664 -> 0x801178B4
void MetaPanel::Unload(class MetaPanel * const this /* r28 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class SongPreview TheSongPreview;
}

// Range: 0x801178B4 -> 0x801178B8
void MetaPanel::Draw() {}

// Range: 0x801178B8 -> 0x801179F8
void MetaPanel::Poll(class MetaPanel * const this /* r29 */) {
    // Local variables
    unsigned char playing; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
    // -> class Synth * TheSynth;
    // -> class TaskMgr TheTaskMgr;
    // -> class SessionMgr * TheSessionMgr;
    // -> class SongPreview TheSongPreview;
}

// Range: 0x801179F8 -> 0x80117A38
void MetaPanel::Enter() {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80117A38 -> 0x80117A78
void MetaPanel::Exit(class MetaPanel * const this /* r31 */) {
    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x80117A78 -> 0x80117AE4
unsigned char MetaPanel::Exiting(class MetaPanel * const this /* r30 */) {}

// Range: 0x80117AE4 -> 0x80117B40
void MetaPanel::CalcSfxPlayTime(class MetaPanel * const this /* r31 */) {
    // Local variables
    float delaySec; // f0

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80117B40 -> 0x80117C08
int MetaPanel::PickLoopIndex(class MetaPanel * const this /* r31 */, int size /* r29 */) {
    // Local variables
    int memSize; // r30
    int idx; // r3
    int i; // r5
}

static class Symbol postprocess; // size: 0x4, address: 0x80A4B920
// Range: 0x80117C08 -> 0x80117D60
void MetaPanel::UpdatePostProc() {
    // Local variables
    class RndPostProc * pp; // r29
    class UIScreen * s; // r0
    const class list & panels; // r0
    struct _List_iterator itr; // r1+0x1C
    const class DataNode * prop; // r28

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPostProc;
    // -> static class Symbol postprocess;
    // -> class UIManager TheUI;
}

// Range: 0x80117D60 -> 0x80117D98
void MetaPanel::OnSendBackSoundMsgToAll() {
    // Local variables
    class TriggerBackSoundMsg msg; // r1+0x8

    // References
    // -> class NetSession * TheNetSession;
    // -> struct [anonymous] __vt__19TriggerBackSoundMsg;
}

static class Symbol _s; // size: 0x4, address: 0x80A4B928
static class Symbol _s; // size: 0x4, address: 0x80A4B930
// Range: 0x80117D98 -> 0x80118218
class DataNode MetaPanel::Handle(class MetaPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x8
} __RTTI__11RndPostProc; // size: 0x8, address: 0x8088C968
struct {
    // total size: 0x8
} __RTTI__13PostProcessor; // size: 0x8, address: 0x8088C980
struct {
    // total size: 0xAC
} __vt__9MetaPanel; // size: 0xAC, address: 0x8088CA98
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class OutfitProvider * _M_data; // offset 0x8, size 0x4
};
class _DDL_TextMessage : public UserMessage {
    // total size: 0x38
public:
    class String m_strTextBody; // offset 0x30, size 0x4
};
class TextMessage : public _DDL_TextMessage {
    // total size: 0x38
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TextMessage * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TextMessage * * _M_start; // offset 0x0, size 0x4
    class TextMessage * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class _DDL_FriendData : public RootObject {
    // total size: 0x18
public:
    void * __vptr$; // offset 0x0, size 0x4
    unsigned int m_pid; // offset 0x4, size 0x4
    class String m_strName; // offset 0x8, size 0x4
    unsigned char m_byRelationship; // offset 0xC, size 0x1
    unsigned int m_uiDetails; // offset 0x10, size 0x4
    class String m_strStatus; // offset 0x14, size 0x4
};
class FriendData : public _DDL_FriendData {
    // total size: 0x18
};
class _List_node : public _List_node_base {
    // total size: 0x20
public:
    class FriendData _M_data; // offset 0x8, size 0x18
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
enum State {
    kIdle = 0,
    kMountingSong = 1,
    kPreparingSong = 2,
    kPlayingSong = 3,
    kFadingOutSong = 4,
};
class SongPreview : public Callback {
    // total size: 0x54
    class Stream * mStream; // offset 0x4, size 0x4
    class Fader * mFader; // offset 0x8, size 0x4
    class Fader * mForegroundFader; // offset 0xC, size 0x4
    class Fader * mBackgroundFader; // offset 0x10, size 0x4
    class Fader * mCrowdFader; // offset 0x14, size 0x4
    class Fader * mCrowdSingFader; // offset 0x18, size 0x4
    class Fader * mVocalsFader; // offset 0x1C, size 0x4
    class Symbol mForegroundInstr; // offset 0x20, size 0x4
    int mNumChannels; // offset 0x24, size 0x4
    float mAtten; // offset 0x28, size 0x4
    float mFadeMs; // offset 0x2C, size 0x4
    unsigned char mRestart; // offset 0x30, size 0x1
    unsigned char mLoopForever; // offset 0x31, size 0x1
    enum State mState; // offset 0x34, size 0x4
    class Symbol mSong; // offset 0x38, size 0x4
    class Symbol mSongContent; // offset 0x3C, size 0x4
    float mStartMs; // offset 0x40, size 0x4
    float mEndMs; // offset 0x44, size 0x4
    float mStartPreviewMs; // offset 0x48, size 0x4
    float mEndPreviewMs; // offset 0x4C, size 0x4
    unsigned char mRegisteredWithCM; // offset 0x50, size 0x1
};
enum BotbChallengeNetState {
    BotbChalNetStart = 0,
    BotbChalNetQueryBattles = 1,
    BotbChalNetBattleListDone = 2,
};
struct OpenBattleRecord {
    // total size: 0xC
    int mBattleId; // offset 0x0, size 0x4
    class TourEvent * mChallengeEvent; // offset 0x4, size 0x4
    class TourEvent * mWorldEvent; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct OpenBattleRecord * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct OpenBattleRecord * _M_start; // offset 0x0, size 0x4
    struct OpenBattleRecord * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class BotbChallengeLoader : public Object {
    // total size: 0xC8
protected:
    class vector mChallengeEvents; // offset 0x28, size 0xC
    class vector mWorldEvents; // offset 0x34, size 0xC
    unsigned char mLoaded; // offset 0x40, size 0x1
    unsigned char mCancelRockCentralRequest; // offset 0x41, size 0x1
    unsigned char mFailed; // offset 0x42, size 0x1
    class Timer mFailedTimer; // offset 0x48, size 0x38
    class HxGuid mBandId; // offset 0x80, size 0x10
    enum BotbChallengeNetState mNetState; // offset 0x90, size 0x4
    int mNetBattleQueryIndex; // offset 0x94, size 0x4
    class BotbBattleDetails mBattleDetails; // offset 0x98, size 0xC
    class BotbOpenBattlesList mOpenBattlesList; // offset 0xA4, size 0x18
    class vector mOpenBattleRecords; // offset 0xBC, size 0xC
};

