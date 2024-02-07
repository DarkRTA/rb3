/*
    Compile unit: C:\rockband2\band2\src\game\BandLeaderboards.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800ADCA8 -> 0x800AF028
*/
class BandLeaderboardData : public LeaderboardData {
    // total size: 0x64
protected:
    unsigned char mLocal; // offset 0x40, size 0x1
    class RemoteBandData * mBandData; // offset 0x44, size 0x4
    class BandResultList mResultList; // offset 0x48, size 0x1C
};
// Range: 0x800ADCA8 -> 0x800ADD04
void * BandLeaderboardData::BandLeaderboardData(class BandLeaderboardData * const this /* r30 */, unsigned char local /* r31 */) {
    // References
    // -> struct [anonymous] __vt__19BandLeaderboardData;
}

// Range: 0x800ADD04 -> 0x800ADDB8
void * BandLeaderboardData::~BandLeaderboardData(class BandLeaderboardData * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__19BandLeaderboardData;
}

static class Symbol on_select_band_error; // size: 0x4, address: 0x80A4A49C
// Range: 0x800ADDB8 -> 0x800ADFC0
class Symbol BandLeaderboardData::OnSelectRow(class BandLeaderboardData * const this /* r31 */, const class LeaderboardResultRow * row /* r30 */) {
    // Local variables
    class BandData * band; // r30
    class HxGuid guid; // r1+0x10

    // References
    // -> class RockCentralGateway RockCentral;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LeaderboardsMgr * TheLeaderboards;
    // -> const char * gNullStr;
    // -> static class Symbol on_select_band_error;
}

// Range: 0x800ADFC0 -> 0x800ADFC8
unsigned char BandLeaderboardData::CanRowsBeSelected() {}

// Range: 0x800ADFC8 -> 0x800ADFE8
void BandLeaderboardData::OnSelectRowComplete() {}

static class Symbol leaderboards_band_profile_screen; // size: 0x4, address: 0x80A4A4A4
// Range: 0x800ADFE8 -> 0x800AE160
void BandLeaderboardData::ShowBandProfile(class BandData * bandData /* r28 */) {
    // Local variables
    const class DataNode * profileScreen; // r0

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol leaderboards_band_profile_screen;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16BandProfilePanel;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x800AE160 -> 0x800AE30C
class BandData * BandLeaderboardData::FindLocalBandData(const class LeaderboardResultRow * row /* r27 */) {
    // Local variables
    class vector profiles; // r1+0x20
    class Profile * * it; // r30
    class Profile * pProfile; // r29
    int iBand; // r28
    class TourBandLocal * band; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
}

// Range: 0x800AE30C -> 0x800AE314
class LeaderboardResultList * BandLeaderboardData::GetResultList() {}

static class Symbol points; // size: 0x4, address: 0x80A4A4AC
class BandScoreLeaderboardData : public BandLeaderboardData {
    // total size: 0x68
    class Symbol mSong; // offset 0x64, size 0x4
};
// Range: 0x800AE314 -> 0x800AE394
void * BandScoreLeaderboardData::BandScoreLeaderboardData(class BandScoreLeaderboardData * const this /* r30 */, class Symbol & song /* r31 */) {
    // References
    // -> static class Symbol points;
    // -> struct [anonymous] __vt__24BandScoreLeaderboardData;
}

// Range: 0x800AE394 -> 0x800AE3F0
void * BandScoreLeaderboardData::~BandScoreLeaderboardData(class BandScoreLeaderboardData * const this /* r30 */) {}

// Range: 0x800AE3F0 -> 0x800AE4DC
void BandScoreLeaderboardData::EnumerateFromID(class BandScoreLeaderboardData * const this /* r28 */, class EntityID & id /* r29 */, int pageSize /* r30 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800AE4DC -> 0x800AE568
void BandScoreLeaderboardData::EnumerateFromRank(class BandScoreLeaderboardData * const this /* r28 */, int rank /* r29 */, int pageSize /* r30 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x800AE568 -> 0x800AE6C0
void BandScoreLeaderboardData::EnumerateFriendStats(class BandScoreLeaderboardData * const this /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP6Friend;
    // -> unsigned char gStlAllocNameLookup;
    // -> class LeaderboardsMgr * TheLeaderboards;
}

static class Symbol career; // size: 0x4, address: 0x80A4A4B4
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x800AE6C0 -> 0x800AE9F0
void BandScoreLeaderboardData::EnumerateLocal(class BandScoreLeaderboardData * const this /* r29 */) {
    // Local variables
    class vector profiles; // r1+0x3C
    class vector results; // r1+0x30
    int i; // r30
    class Profile * profile; // r25
    int count; // r0
    int j; // r24
    class TourBandLocal * band; // r26
    class String name; // r1+0x24
    int score; // r23
    const class HxGuid & guid; // r22
    class BandResultRow * new_row; // r1+0x14
    int rank; // r22
    class BandResultRow * * it; // r23

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol career;
    // -> class ProfileMgr TheProfileMgr;
}

class BandResultRow : public LeaderboardResultRow {
    // total size: 0x50
    class String mBandName; // offset 0x1C, size 0xC
    int mRanking; // offset 0x28, size 0x4
    unsigned long long mScore; // offset 0x30, size 0x8
    class EntityID mID; // offset 0x38, size 0x18
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BandResultRow * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BandResultRow * * _M_start; // offset 0x0, size 0x4
    class BandResultRow * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
static class Symbol fans; // size: 0x4, address: 0x80A4A4BC
class BandFansLeaderboardData : public BandLeaderboardData {
    // total size: 0x64
};
// Range: 0x800AE9F0 -> 0x800AEA58
void * BandFansLeaderboardData::BandFansLeaderboardData(class BandFansLeaderboardData * const this /* r31 */) {
    // References
    // -> static class Symbol fans;
    // -> struct [anonymous] __vt__23BandFansLeaderboardData;
}

// Range: 0x800AEA58 -> 0x800AEAB4
void * BandFansLeaderboardData::~BandFansLeaderboardData(class BandFansLeaderboardData * const this /* r30 */) {}

// Range: 0x800AEAB4 -> 0x800AEB88
void BandFansLeaderboardData::EnumerateFromID(class BandFansLeaderboardData * const this /* r29 */, class EntityID & id /* r30 */, int pageSize /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800AEB88 -> 0x800AEC08
void BandFansLeaderboardData::EnumerateFromRank(class BandFansLeaderboardData * const this /* r28 */, int rank /* r29 */, int pageSize /* r30 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x800AEC08 -> 0x800AED54
void BandFansLeaderboardData::EnumerateFriendStats(class BandFansLeaderboardData * const this /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP6Friend;
    // -> unsigned char gStlAllocNameLookup;
    // -> class LeaderboardsMgr * TheLeaderboards;
}

// Range: 0x800AED54 -> 0x800AF028
void BandFansLeaderboardData::EnumerateLocal(class BandFansLeaderboardData * const this /* r30 */) {
    // Local variables
    class vector results; // r1+0x3C
    class vector profiles; // r1+0x30
    int i; // r31
    class Profile * profile; // r26
    int count; // r0
    int j; // r25
    class TourBandLocal * band; // r27
    class String name; // r1+0x24
    int score; // r24
    const class HxGuid & guid; // r23
    class BandResultRow * new_row; // r1+0x14
    int rank; // r23
    class BandResultRow * * it; // r24

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ProfileMgr TheProfileMgr;
}

class DynamicTex {
    // total size: 0x1C
public:
    void * __vptr$; // offset 0x0, size 0x4
    class RndTex * mTex; // offset 0x4, size 0x4
    class String mMatName; // offset 0x8, size 0xC
    class RndMat * mMat; // offset 0x14, size 0x4
    class FileLoader * mLoader; // offset 0x18, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class DynamicTex * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class DynamicTex * * _M_start; // offset 0x0, size 0x4
    class DynamicTex * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum State {
    kStarting = 0,
    kMounting = 1,
    kLoading = 2,
    kLoaded = 3,
};
class DLCTex : public DynamicTex {
    // total size: 0x28
public:
    class Symbol mSong; // offset 0x1C, size 0x4
    enum State mState; // offset 0x20, size 0x4
    class RndTex * mFailTex; // offset 0x24, size 0x4
};
class TexLoadPanel : public UIPanel, public Callback {
    // total size: 0x6C
protected:
    class vector mTexs; // offset 0x34, size 0xC
};
struct TabData {
    // total size: 0x10
    class BandButton * mButton; // offset 0x0, size 0x4
    class RndGroup * mGroup; // offset 0x4, size 0x4
    class RndGroup * mSelectGroup; // offset 0x8, size 0x4
    class DataArray * mTypeDef; // offset 0xC, size 0x4
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
class TabInterfacePanel : public TexLoadPanel {
    // total size: 0x7C
    class vector mTabs; // offset 0x40, size 0xC
    int mCurrentTab; // offset 0x4C, size 0x4
};
enum /* @enum$30725BandLeaderboards_cpp */ {
    kAbsent = 0,
    kGuitarist = 1,
    kDrummer = 2,
    kVocalist = 3,
};
struct LineupMember {
    // total size: 0x34
    class String mUserName; // offset 0x0, size 0xC
    class String mCharName; // offset 0xC, size 0xC
    class HxGuid mCharGuid; // offset 0x18, size 0x10
    unsigned char mCharNameUnchecked; // offset 0x28, size 0x1
    unsigned char mIsBandMember; // offset 0x29, size 0x1
    enum /* @enum$30725BandLeaderboards_cpp */ {
        kAbsent = 0,
        kGuitarist = 1,
        kDrummer = 2,
        kVocalist = 3,
    } mIconState; // offset 0x2C, size 0x4
    const class OnlineID * mOnlineID; // offset 0x30, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct LineupMember * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct LineupMember * _M_start; // offset 0x0, size 0x4
    struct LineupMember * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class LineupProvider : public ListProvider, public Object {
    // total size: 0x3C
    class vector mLineup; // offset 0x2C, size 0xC
    class RndMat * mBlackBarMat; // offset 0x38, size 0x4
};
struct StandIn {
    // total size: 0x24
    enum TrackType mTrackType; // offset 0x0, size 0x4
    class String mCharName; // offset 0x4, size 0xC
    class HxGuid mCharGuid; // offset 0x10, size 0x10
    unsigned char mIsActive; // offset 0x20, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct StandIn * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct StandIn * _M_start; // offset 0x0, size 0x4
    struct StandIn * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class RemoteBandData : public BandData {
    // total size: 0xC8
    class String mName; // offset 0x8, size 0xC
    class HxGuid mGuid; // offset 0x14, size 0x10
    class vector mRoster; // offset 0x24, size 0xC
    int mFans; // offset 0x30, size 0x4
    int mCareerScore; // offset 0x34, size 0x4
    int mTotalScore; // offset 0x38, size 0x4
    int mWorldFame; // offset 0x3C, size 0x4
    int mStarRating; // offset 0x40, size 0x4
    enum Difficulty mDifficultyRating; // offset 0x44, size 0x4
    class String mBandLogo; // offset 0x48, size 0xC
    int mBandLogoPos; // offset 0x54, size 0x4
    class String mMotto; // offset 0x58, size 0xC
    struct DateTime mCreationDate; // offset 0x64, size 0x6
    class Symbol mHometown; // offset 0x6C, size 0x4
    class vector mTopSongs; // offset 0x70, size 0xC
    class OnlineID mOwnerID; // offset 0x7C, size 0x10
    class String mOwnerName; // offset 0x8C, size 0xC
    unsigned char mDirty; // offset 0x98, size 0x1
};
class StandInProvider : public ListProvider, public Object {
    // total size: 0x38
    class vector mStandIns; // offset 0x2C, size 0xC
};
struct Entry {
    // total size: 0x20
    unsigned char mHeader; // offset 0x0, size 0x1
    class HxGuid mGuid; // offset 0x4, size 0x10
    class String mName; // offset 0x14, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Entry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Entry * _M_start; // offset 0x0, size 0x4
    struct Entry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class StandInCharProvider : public ListProvider, public Object {
    // total size: 0x38
    class vector mEntries; // offset 0x2C, size 0xC
};
class TopSongsProvider : public ListProvider, public Object {
    // total size: 0x38
    class vector mSongStatusArray; // offset 0x2C, size 0xC
};
class BattleHistoryProvider : public ListProvider, public Object {
    // total size: 0x50
    class BotbBattlesParticipatedInList mBattles; // offset 0x2C, size 0x18
    const class vector & mCovers; // offset 0x44, size 0x4
    class RndMat * mDefaultMat; // offset 0x48, size 0x4
    class RndMat * mTrimMat; // offset 0x4C, size 0x4
};
class BandProfilePanel : public TabInterfacePanel {
    // total size: 0x16C
    class BandData * mBandData; // offset 0x50, size 0x4
    class LineupProvider mLineupProvider; // offset 0x54, size 0x3C
    class StandInProvider * mStandInProvider; // offset 0x90, size 0x4
    class StandInCharProvider * mStandInCharProvider; // offset 0x94, size 0x4
    class TopSongsProvider mTopSongsProvider; // offset 0x98, size 0x38
    class BattleHistoryProvider mBattleHistoryProvider; // offset 0xD0, size 0x50
    unsigned char mRequesting; // offset 0x120, size 0x1
    unsigned char mTexWaiting; // offset 0x121, size 0x1
    class Symbol mDisplayTab; // offset 0x124, size 0x4
    int mFirstShowingBattleOffset; // offset 0x128, size 0x4
    int mLastBattleId; // offset 0x12C, size 0x4
    class HxGuid mToggleCandidate; // offset 0x130, size 0x10
};
struct {
    // total size: 0x7C
} __vt__23BandFansLeaderboardData; // size: 0x7C, address: 0x8087D4C0
struct {
    // total size: 0x8
} __RTTI__23BandFansLeaderboardData; // size: 0x8, address: 0x8087D580
struct {
    // total size: 0x7C
} __vt__24BandScoreLeaderboardData; // size: 0x7C, address: 0x8087D588
struct {
    // total size: 0x8
} __RTTI__24BandScoreLeaderboardData; // size: 0x8, address: 0x8087D648
struct {
    // total size: 0x7C
} __vt__19BandLeaderboardData; // size: 0x7C, address: 0x8087D650
struct {
    // total size: 0x8
} __RTTI__19BandLeaderboardData; // size: 0x8, address: 0x8087D700
struct {
    // total size: 0x8
} __RTTI__16BandProfilePanel; // size: 0x8, address: 0x8087D780
struct {
    // total size: 0x8
} __RTTI__17TabInterfacePanel; // size: 0x8, address: 0x8087D7C8
struct {
    // total size: 0x8
} __RTTI__12TexLoadPanel; // size: 0x8, address: 0x8087D808
struct {
    // total size: 0x8
} __RTTI__PP13BandResultRow; // size: 0x8, address: 0x8087D8C8

