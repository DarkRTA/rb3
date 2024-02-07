/*
    Compile unit: C:\rockband2\band2\src\band\BudgetScreen.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80013688 -> 0x80015230
*/
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std13_List_node<i>; // size: 0x8, address: 0x8085DB78
class DataArray * types; // size: 0x4, address: 0x80A48ED8
int gMainFree; // size: 0x4, address: 0x80A48EE0
// Range: 0x80013688 -> 0x8001370C
void * Distribution::Distribution(class Distribution * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8001370C -> 0x80013810
void Distribution::Reset(class Distribution * const this /* r30 */) {}

// Range: 0x80013810 -> 0x800139A8
void Distribution::Report(class Distribution * const this /* r27 */, class TextStream & log /* r28 */) {
    // Local variables
    float r; // f31
    int acc; // r30
    int i; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800139A8 -> 0x80013AF8
void Distribution::__ls(class Distribution * const this /* r31 */, float t /* f31 */) {
    // Local variables
    int i; // r29
}

// Range: 0x80013AF8 -> 0x80013BE0
float Average(class vector & times /* r30 */, unsigned char discard_worst /* r31 */) {
    // Local variables
    int num; // r6
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80013BE0 -> 0x80013DD0
void * BudgetScreen::BudgetScreen(class BudgetScreen * const this /* r31 */) {
    // Local variables
    const char * logFile; // r29
    class list tmp; // r1+0x30
    int i; // r29

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class ContentMgr & TheContentMgr;
    // -> class SongMgr & TheSongMgr;
    // -> struct [anonymous] __vt__12BudgetScreen;
}

class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x80013E40 -> 0x80014250
void BudgetScreen::Enter(class BudgetScreen * const this /* r28 */, class UIScreen * from /* r29 */) {
    // Local variables
    class vector mNullCpuTimes; // r1+0x4C
    class vector mNullGsTimes; // r1+0x40
    int i; // r29
    class DataArray * initScript; // r4

    // References
    // -> class SongDB * TheSongDB;
    // -> class Rnd & TheRnd;
    // -> class GamePanel * TheGamePanel;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class TaskMgr TheTaskMgr;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    float * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    float * _M_start; // offset 0x0, size 0x4
    float * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
// Range: 0x80014250 -> 0x800146EC
void BudgetScreen::Poll(class BudgetScreen * const this /* r30 */) {
    // Local variables
    float tick; // f0
    class Timer pollT; // r1+0x10
    float cpu; // f31
    float gs; // f30
    float poll; // f0

    // References
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class ObjectDir * sMainDir;
    // -> int gMainFree;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class Rnd & TheRnd;
    // -> class TaskMgr TheTaskMgr;
    // -> class SongDB * TheSongDB;
    // -> class GamePanel * TheGamePanel;
}

// Range: 0x800146EC -> 0x80014884
void BudgetScreen::EndTest(class BudgetScreen * const this /* r30 */) {
    // Local variables
    int main; // r29

    // References
    // -> class UIManager TheUI;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class ObjectDir * sMainDir;
    // -> int gMainFree;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

enum NetState {
    kInLobby = 0,
    kJoining = 1,
    kLoading = 2,
    kInGame = 3,
};
class SessionData {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    unsigned int * _M_start; // offset 0x0, size 0x4
    unsigned int * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum JoinResponseError {
    kSuccess = 0,
    kNotHosting = 1,
    kBusy = 2,
    kNoRoom = 3,
    kWrongMode = 4,
    kTimeout = 5,
    kNoSelfJoin = 6,
    kAlreadyHosting = 7,
    kCannotConnect = 8,
    kCustom = 9,
};
enum PacketType {
    kUnreliable = 0,
    kReliable = 1,
};
class NetSession : public MsgSource {
    // total size: 0xD8
protected:
    enum NetState mState; // offset 0x1C, size 0x4
    class SessionData * mData; // offset 0x20, size 0x4
    class list mPlayerIDs; // offset 0x24, size 0x8
    class Timer mTime; // offset 0x30, size 0x38
    int mLocalHost; // offset 0x68, size 0x4
    class SessionData * mJoinData; // offset 0x6C, size 0x4
    unsigned char mWaitingForAddResponse; // offset 0x70, size 0x1
    class SessionSettings * mSettings; // offset 0x74, size 0x4
    class JobMgr mJobMgr; // offset 0x78, size 0x10
private:
    int mQuazalSessionJobID; // offset 0x88, size 0x4
    float mJoinTimeout; // offset 0x8C, size 0x4
    class Time * mGameStartTime; // offset 0x90, size 0x4
    class vector mStillLoading; // offset 0x94, size 0xC
    int mJoinWaitTime; // offset 0xA0, size 0x4
    int mGameStartDelay; // offset 0xA4, size 0x4
    unsigned char mBusy; // offset 0xA8, size 0x1
};
class Synchronizable {
    // total size: 0x20
public:
    void * __vptr$; // offset 0x0, size 0x4
private:
    unsigned int mDirtyMask; // offset 0x4, size 0x4
    class vector mDirtyPlayers; // offset 0x8, size 0xC
    class String mTag; // offset 0x14, size 0xC
};
class UserMgr : public Object {
    // total size: 0x28
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class BandUser * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BandUser * * _M_start; // offset 0x0, size 0x4
    class BandUser * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ListProvider {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
enum BandUserProviderState {
    kGameBUPS_LocalCharOwners = 0,
    kGameBUPS_LocalBandOwners = 1,
    kGameBUPS_Max = 2,
};
class BandUserProvider : public ListProvider, public Object {
    // total size: 0x3C
    enum BandUserProviderState mState; // offset 0x2C, size 0x4
    class vector mUsers; // offset 0x30, size 0xC
};
class BandUserMgr : public UserMgr {
    // total size: 0x9C
protected:
    class vector mUsers; // offset 0x28, size 0xC
    class vector mSlots; // offset 0x34, size 0xC
private:
    class BandUserProvider mUserProvider; // offset 0x40, size 0x3C
    enum ControllerType mControllerTypeOverride[8]; // offset 0x7C, size 0x20
};
class MetaPerformer : public virtual Object, public Synchronizable {
    // total size: 0x6C
protected:
    class vector mSongs; // offset 0x24, size 0xC
    class vector mStars; // offset 0x30, size 0xC
    const class SongMgr & mSongMgr; // offset 0x3C, size 0x4
};
class QuickplayPerformer : public MetaPerformer {
    // total size: 0x74
    int mSongSelectUserNum; // offset 0x40, size 0x4
    unsigned char mSongSelectSync; // offset 0x44, size 0x1
};
// Range: 0x80014884 -> 0x80014B9C
void BudgetScreen::NextTest(class BudgetScreen * const this /* r26 */) {
    // Local variables
    class NetSession * session; // r28
    const class DataArray * players; // r30
    int i; // r27
    int player_idx; // r26
    class BandUser * user; // r26
    enum ControllerType controller; // r0
    class QuickplayPerformer * qp; // r26

    // References
    // -> class GameConfig * TheGameConfig;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__13MetaPerformer;
    // -> struct [anonymous] __RTTI__18QuickplayPerformer;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Net TheNet;
}

// Range: 0x80014B9C -> 0x80014C24
int BudgetScreen::MainFree() {
    // Local variables
    int main; // r31
    int heap; // r30
    const char * heapName; // r0
    int num; // r1+0x10
    int bytes; // r1+0xC
    int largest; // r1+0x8
}

static class Symbol _s; // size: 0x4, address: 0x80A48EE8
static class Symbol _s; // size: 0x4, address: 0x80A48EF0
class MessageTimer {
    // total size: 0x40
protected:
    class Timer mTimer; // offset 0x0, size 0x38
    class Object * mObject; // offset 0x38, size 0x4
    class Symbol mMessage; // offset 0x3C, size 0x4
};
// Range: 0x80014C24 -> 0x80015088
class DataNode BudgetScreen::Handle(class BudgetScreen * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A48EF8
// Range: 0x80015088 -> 0x80015230
unsigned char BudgetScreen::SyncProperty(class BudgetScreen * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8
} __RTTI__18QuickplayPerformer; // size: 0x8, address: 0x8085DDB0
struct {
    // total size: 0x8
} __RTTI__13MetaPerformer; // size: 0x8, address: 0x8085DDE8
struct {
    // total size: 0x8
} __RTTI__14Synchronizable; // size: 0x8, address: 0x8085DE28
struct {
    // total size: 0x80
} __vt__12BudgetScreen; // size: 0x80, address: 0x8085DE30
struct {
    // total size: 0x8
} __RTTI__12BudgetScreen; // size: 0x8, address: 0x8085DEE0
class ButtonDownMsg : public Message {
    // total size: 0x8
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class UIPanel * _M_data; // offset 0x8, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__Pf; // size: 0x8, address: 0x8085DF48
struct {
    // total size: 0x8
} __RTTI__Pi; // size: 0x8, address: 0x8085DF58
struct _OKToMemCpy {
    // total size: 0x1
};
struct PracticeSection {
    // total size: 0x18
    class Symbol mName; // offset 0x0, size 0x4
    int mStartTick; // offset 0x4, size 0x4
    int mEndTick; // offset 0x8, size 0x4
    float mStartMs; // offset 0xC, size 0x4
    float mEndMs; // offset 0x10, size 0x4
    unsigned char mEmpty; // offset 0x14, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct PracticeSection * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct PracticeSection * _M_start; // offset 0x0, size 0x4
    struct PracticeSection * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class PracticeSectionProvider : public ListProvider, public Object {
    // total size: 0x54
    class vector mSections; // offset 0x2C, size 0xC
    struct PracticeSection mFullSong; // offset 0x38, size 0x18
    int mStartSection; // offset 0x50, size 0x4
};
class Providers {
    // total size: 0x58
public:
    class PracticeSectionProvider practiceSectionProvider; // offset 0x0, size 0x54
private:
    class LeaderboardsMgr * mLeaderboards; // offset 0x54, size 0x4
};
class XMPStateChangedMsg : public Message {
    // total size: 0x8
};
enum GameControllerState {
    kGameControllerAll = 0,
    kGameControllerParticipating = 1,
    kGameControllerNotParticipating = 2,
};
class GameConfig : public Object, public Synchronizable, public NetGameData {
    // total size: 0x80
    class PlayerTrackConfigList * mPlayerTrackConfigList; // offset 0x4C, size 0x4
    unsigned char mJoiningAllowed; // offset 0x50, size 0x1
    int mNetRandomSeed; // offset 0x54, size 0x4
    unsigned char mActiveRosterSet; // offset 0x58, size 0x1
    class Providers * mProviders; // offset 0x5C, size 0x4
    class Symbol mVenue; // offset 0x60, size 0x4
    float mSongLimitMs; // offset 0x64, size 0x4
    class Symbol mCoopIntroCategory; // offset 0x68, size 0x4
    int mDisableAvailablePlayer; // offset 0x6C, size 0x4
    int mPracticeSections[2]; // offset 0x70, size 0x8
    int mPracticeSpeed; // offset 0x78, size 0x4
    unsigned char mPracticeMode; // offset 0x7C, size 0x1
};
class ButtonUpMsg : public Message {
    // total size: 0x8
};
class JoypadReassignMsg : public Message {
    // total size: 0x8
};
enum BeatmatchPhraseType {
    kCommonPhrase = 0,
    kSoloPhrase = 1,
    kPlayerOneFocusPhrase = 2,
    kPlayerTwoFocusPhrase = 3,
    kNumPhraseTypes = 4,
    kNoPhrase = 4,
};
class TempoMap {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class GameGem {
    // total size: 0x10
    float mMs; // offset 0x0, size 0x4
    int mTick; // offset 0x4, size 0x4
    unsigned short mDurationMs; // offset 0x8, size 0x2
    unsigned short mDurationTicks; // offset 0xA, size 0x2
    unsigned char mSlots; // offset 0xC, size 0x1
    unsigned char mNoStrum : 1; // offset 0xD, size 0x1
    unsigned char mIgnoreDuration : 1; // offset 0xD, size 0x1
    unsigned char mPlayableBy; // offset 0xE, size 0x1
};
class SongParserSink {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
class InternalSongParserSink {
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
    class SongParserSink * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class SongParserSink * * _M_start; // offset 0x0, size 0x4
    class SongParserSink * * _M_finish; // offset 0x4, size 0x4
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
    class BeatMatcher * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class BeatMatcher * * _M_start; // offset 0x0, size 0x4
    class BeatMatcher * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct TrackInfo {
    // total size: 0x10
    class Symbol mName; // offset 0x0, size 0x4
    class TickedInfoCollection * mLyrics; // offset 0x4, size 0x4
    class Symbol mInstrument; // offset 0x8, size 0x4
    unsigned char mIndependentSlots; // offset 0xC, size 0x1
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct TrackInfo * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct TrackInfo * * _M_start; // offset 0x0, size 0x4
    struct TrackInfo * * _M_finish; // offset 0x4, size 0x4
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
    class DrumFillInfo * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class DrumFillInfo * * _M_start; // offset 0x0, size 0x4
    class DrumFillInfo * * _M_finish; // offset 0x4, size 0x4
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
    class DrumMap * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class DrumMap * * _M_start; // offset 0x0, size 0x4
    class DrumMap * * _M_finish; // offset 0x4, size 0x4
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
    class GameGemDB * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class GameGemDB * * _M_start; // offset 0x0, size 0x4
    class GameGemDB * * _M_finish; // offset 0x4, size 0x4
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
    class PhraseDB * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class PhraseDB * * _M_start; // offset 0x0, size 0x4
    class PhraseDB * * _M_finish; // offset 0x4, size 0x4
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
    class GameGemInfoDB * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class GameGemInfoDB * * _M_start; // offset 0x0, size 0x4
    class GameGemInfoDB * * _M_finish; // offset 0x4, size 0x4
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
    class DrumMixDB * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class DrumMixDB * * _M_start; // offset 0x0, size 0x4
    class DrumMixDB * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct BeatInfo {
    // total size: 0x8
    int mTick; // offset 0x0, size 0x4
    int mLevel; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct BeatInfo * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct BeatInfo * _M_start; // offset 0x0, size 0x4
    struct BeatInfo * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class BeatMap {
    // total size: 0xC
    class vector mInfos; // offset 0x0, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    const char * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    const char * * _M_start; // offset 0x0, size 0x4
    const char * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum SongDataValidate {
    kSongData_NoValidation = 0,
    kSongData_ValidateUsingNameOnly = 1,
    kSongData_Validate = 2,
};
class SongData : public InternalSongParserSink {
    // total size: 0xB8
    int mNumTracks; // offset 0x4, size 0x4
    int mNumDifficulties; // offset 0x8, size 0x4
    const class DataArray * mSongData; // offset 0xC, size 0x4
    unsigned char mSeparateParts; // offset 0x10, size 0x1
    int mSectionStartTick; // offset 0x14, size 0x4
    int mSectionEndTick; // offset 0x18, size 0x4
    unsigned char mFakeHitGemsInFill; // offset 0x1C, size 0x1
    class vector mSinks; // offset 0x20, size 0xC
    class vector mBeatMatchers; // offset 0x2C, size 0xC
    class vector mTrackInfos; // offset 0x38, size 0xC
    class vector mTrackDifficulties; // offset 0x44, size 0xC
    class vector mFills; // offset 0x50, size 0xC
    class vector mDrumMaps; // offset 0x5C, size 0xC
    class vector mGemDBs; // offset 0x68, size 0xC
    class vector mPhraseDBs; // offset 0x74, size 0xC
    class vector mGemInfoDBs; // offset 0x80, size 0xC
    class vector mDrumMixDBs; // offset 0x8C, size 0xC
    class VocalNoteList * mVocalNotes; // offset 0x98, size 0x4
    class TempoMap * mTempoMap; // offset 0x9C, size 0x4
    class MeasureMap * mMeasureMap; // offset 0xA0, size 0x4
    class BeatMap * mBeatMap; // offset 0xA4, size 0x4
    float mLastGemTime; // offset 0xA8, size 0x4
    class MemStream * mMemStream; // offset 0xAC, size 0x4
    class SongParser * mSongParser; // offset 0xB0, size 0x4
    class PlayerTrackConfigList * mPlayerTrackConfigList; // offset 0xB4, size 0x4
};
struct Extent {
    // total size: 0x8
    int startTick; // offset 0x0, size 0x4
    int endTick; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct Extent * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct Extent * _M_start; // offset 0x0, size 0x4
    struct Extent * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct TrackData {
    // total size: 0x4C
    class Symbol mInstrument; // offset 0x0, size 0x4
    class vector mSoloPhrases; // offset 0x4, size 0xC
    class vector mCommonPhrases; // offset 0x10, size 0xC
    class vector mGemSoloState; // offset 0x1C, size 0xC
    class vector mGemCommonState; // offset 0x28, size 0xC
    class vector mPhraseIDs; // offset 0x34, size 0xC
    class vector mPhraseIDToCommonPhraseNum; // offset 0x40, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct TrackData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct TrackData * _M_start; // offset 0x0, size 0x4
    struct TrackData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct MBT {
    // total size: 0xC
    int measure; // offset 0x0, size 0x4
    int beat; // offset 0x4, size 0x4
    int tick; // offset 0x8, size 0x4
};
class SongDB : public SongParserSink {
    // total size: 0x34
    class SongData * mSongData; // offset 0x4, size 0x4
    class vector mTrackData; // offset 0x8, size 0xC
    float mSongDurationMs; // offset 0x14, size 0x4
    int mCodaStartTick; // offset 0x18, size 0x4
    class PhraseAnalyzer * mPhraseAnalyzer; // offset 0x1C, size 0x4
    class MultiplayerAnalyzer * mMultiplayerAnalyzer; // offset 0x20, size 0x4
    float mMultiplayerNormalizationFactor; // offset 0x24, size 0x4
    class vector mPracticeSections; // offset 0x28, size 0xC
};
struct PressRec {
    // total size: 0x18
    int iUserNum; // offset 0x0, size 0x4
    class User * iUser; // offset 0x4, size 0x4
    enum JoypadButton iRawButton; // offset 0x8, size 0x4
    enum JoypadAction iAction; // offset 0xC, size 0x4
    float fPressTime; // offset 0x10, size 0x4
    int iPadNum; // offset 0x14, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct PressRec * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct PressRec * _M_start; // offset 0x0, size 0x4
    struct PressRec * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct StrActionRec {
    // total size: 0x14
    enum JoypadAction mAction; // offset 0x0, size 0x4
    float mHoldTime; // offset 0x4, size 0x4
    class vector mPresses; // offset 0x8, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct StrActionRec * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct StrActionRec * _M_start; // offset 0x0, size 0x4
    struct StrActionRec * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class HeldButtonPanel : public UIPanel {
    // total size: 0x68
    class vector mActionRecs; // offset 0x30, size 0xC
};
class BeatMasterSink {
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
    class Player * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Player * * _M_start; // offset 0x0, size 0x4
    class Player * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum LoadState {
    kLoadingSong = 0,
    kWaitingForAudio = 1,
    kReady = 2,
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Band * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Band * * _M_start; // offset 0x0, size 0x4
    class Band * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum WaitState {
    kWaitNone = 0,
    kWaitStart = 1,
    kWaitJump = 2,
    kWaitRestart = 3,
};
enum EndGameResult {
    kRestart = 0,
    kLost = 1,
    kWon = 2,
    kWonBand0 = 3,
    kWonBand1 = 4,
    kWonTie = 5,
    kWonFinale = 6,
    kQuit = 7,
};
enum ExcitementLevel {
    kExcitementBoot = 0,
    kExcitementBad = 1,
    kExcitementOkay = 2,
    kExcitementGreat = 3,
    kExcitementPeak = 4,
    kNumExcitements = 5,
};
class Game : public BeatMasterSink, public Object {
    // total size: 0xF0
    unsigned char mBotbReset; // offset 0x2C, size 0x1
    class SongPos mSongPos; // offset 0x30, size 0x14
    class SongDB * mSongDB; // offset 0x44, size 0x4
    class BeatMaster * mMaster; // offset 0x48, size 0x4
    class vector mAllPlayers; // offset 0x4C, size 0xC
    class vector mAllActivePlayers; // offset 0x58, size 0xC
    class vector mAllLocalPlayers; // offset 0x64, size 0xC
    unsigned char mPaused; // offset 0x70, size 0x1
    unsigned char mPauseTime; // offset 0x71, size 0x1
    unsigned char mRealtime; // offset 0x72, size 0x1
    unsigned char mRestartedYet; // offset 0x73, size 0x1
    float mTimeOffset; // offset 0x74, size 0x4
    class Timer mTime; // offset 0x78, size 0x38
    float mStartTime; // offset 0xB0, size 0x4
    float mMusicSpeed; // offset 0xB4, size 0x4
    int mMaxDeltaPoints; // offset 0xB8, size 0x4
    int mTieWindow; // offset 0xBC, size 0x4
    unsigned char mNeverAllowInput; // offset 0xC0, size 0x1
    unsigned char mGameDataIsPersistent; // offset 0xC1, size 0x1
    enum LoadState mLoadState; // offset 0xC4, size 0x4
    class vector mBands; // offset 0xC8, size 0xC
    class BonusAwards * mBonusAwards; // offset 0xD4, size 0x4
    class Shuttle * mShuttle; // offset 0xD8, size 0x4
    unsigned char mUseOldWait; // offset 0xDC, size 0x1
    float mJumpWaitMs; // offset 0xE0, size 0x4
    enum WaitState mWaitState; // offset 0xE4, size 0x4
    unsigned char mHasVocalPlayer; // offset 0xE8, size 0x1
};
enum GameState {
    kGameNeedIntro = 0,
    kGameNeedStart = 1,
    kGamePlaying = 2,
    kGameOver = 3,
};
struct PointsInfo {
    // total size: 0x8
    int mHeadPoints; // offset 0x0, size 0x4
    int mTailPoints; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct PointsInfo * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct PointsInfo * _M_start; // offset 0x0, size 0x4
    struct PointsInfo * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct StreakItem {
    // total size: 0x8
    int notes; // offset 0x0, size 0x4
    float data; // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct StreakItem * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct StreakItem * _M_start; // offset 0x0, size 0x4
    struct StreakItem * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct StreakList {
    // total size: 0x10
    class Symbol mType; // offset 0x0, size 0x4
    class vector mItems; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct StreakList * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct StreakList * _M_start; // offset 0x0, size 0x4
    struct StreakList * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
struct StarPowerConfig {
    // total size: 0x20
    float rechargeRate; // offset 0x0, size 0x4
    float starPhrase; // offset 0x4, size 0x4
    float commonPhrase; // offset 0x8, size 0x4
    float fillBoost; // offset 0xC, size 0x4
    float whammyRate; // offset 0x10, size 0x4
    float readyLevel; // offset 0x14, size 0x4
    int multiplier; // offset 0x18, size 0x4
    float crowdBoost; // offset 0x1C, size 0x4
};
enum HitType {
    kPoor = 0,
    kGood = 1,
    kPerfect = 2,
    kNumHitTypes = 3,
};
class Scoring {
    // total size: 0x60
    class vector mPointsInfos; // offset 0x0, size 0xC
    int mError[3]; // offset 0xC, size 0xC
    class vector mStreakMultLists; // offset 0x18, size 0xC
    class vector mStreakEnergyLists; // offset 0x24, size 0xC
    class DataArray * mPointsArray; // offset 0x30, size 0x4
    class DataArray * mConfig; // offset 0x34, size 0x4
    struct StarPowerConfig mStarPowerConfig; // offset 0x38, size 0x20
    float mCommonPhraseReward; // offset 0x58, size 0x4
    float mCommonPhrasePenalty; // offset 0x5C, size 0x4
};
class Profiler {
    // total size: 0x58
    const char * mName; // offset 0x0, size 0x4
    class Timer mTimer; // offset 0x8, size 0x38
    float mMin; // offset 0x40, size 0x4
    float mMax; // offset 0x44, size 0x4
    float mSum; // offset 0x48, size 0x4
    unsigned int mCount; // offset 0x4C, size 0x4
    unsigned int mCountMax; // offset 0x50, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
struct Target {
    // total size: 0x110
    class ObjOwnerPtr mTarget; // offset 0x0, size 0xC
    class Transform mTo; // offset 0x10, size 0x40
    class Transform mFrom; // offset 0x50, size 0x40
    class String mAnim; // offset 0x90, size 0xC
    unsigned char mReturn; // offset 0x9C, size 0x1
    class Character * mTargetChar; // offset 0xA0, size 0x4
    unsigned char mTeleport; // offset 0xA4, size 0x1
    unsigned char mTeleportHold; // offset 0xA5, size 0x1
    unsigned char mSelfShadow; // offset 0xA6, size 0x1
    unsigned char mSpotCutout; // offset 0xA7, size 0x1
    unsigned char mFloorShadow; // offset 0xA8, size 0x1
    unsigned char mFreeze; // offset 0xA9, size 0x1
    float mFreezeDelay; // offset 0xAC, size 0x4
    unsigned char mFrozen; // offset 0xB0, size 0x1
    float mFastForward; // offset 0xB4, size 0x4
    class Symbol mForwardEvent; // offset 0xB8, size 0x4
    class String mTargetIK; // offset 0xBC, size 0xC
    class ObjPtr mWorldIK; // offset 0xC8, size 0xC
    class ObjPtr mWorldProp; // offset 0xD4, size 0xC
    class String mTargetProp; // offset 0xE0, size 0xC
    class ObjPtr mEnvOverride; // offset 0xEC, size 0xC
    class ObjPtr mEnvCache; // offset 0xF8, size 0xC
    unsigned char mLODOverride; // offset 0x104, size 0x1
    int mOutfitHides; // offset 0x108, size 0x4
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
class ObjList : public list {
    // total size: 0xC
    class Object * mOwner; // offset 0x8, size 0x4
};
class TimedTrigger {
    // total size: 0x10
protected:
    float mFrame; // offset 0x0, size 0x4
    class ObjPtr mTrigger; // offset 0x4, size 0xC
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class TimedTrigger * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class TimedTrigger * _M_start; // offset 0x0, size 0x4
    class TimedTrigger * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class ObjVector : public vector {
    // total size: 0x10
    class Object * mOwner; // offset 0xC, size 0x4
};
class BandCamShot : public CamShot {
    // total size: 0x210
public:
    class ObjList mTargets; // offset 0x184, size 0xC
    class ObjVector mTriggers; // offset 0x190, size 0x10
    int mCurTrigger; // offset 0x1A0, size 0x4
    float mLastFrame; // offset 0x1A4, size 0x4
    class ObjPtr mNextShot; // offset 0x1A8, size 0xC
    int mMinTime; // offset 0x1B4, size 0x4
    int mMaxTime; // offset 0x1B8, size 0x4
    class ObjPtr mEventAtStart; // offset 0x1BC, size 0xC
    class ObjPtr mEventAtEnd; // offset 0x1C8, size 0xC
    float mZeroTime; // offset 0x1D4, size 0x4
    unsigned char mFPSOverride; // offset 0x1D8, size 0x1
};
class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class BandCamShot * mPtr; // offset 0x8, size 0x4
};
class GamePanel : public HeldButtonPanel, public MsgSource {
    // total size: 0x230
    class Game * mGame; // offset 0x58, size 0x4
    class RndOverlay * mNowBar; // offset 0x5C, size 0x4
    class RndOverlay * mLatency; // offset 0x60, size 0x4
    class ObjDirPtr mBank; // offset 0x64, size 0xC
    unsigned char mStartPaused; // offset 0x70, size 0x1
    enum GameState mState; // offset 0x74, size 0x4
    unsigned char mMultiEvent; // offset 0x78, size 0x1
    enum EndGameResult mResult; // offset 0x7C, size 0x4
    class GameConfig mConfig; // offset 0x80, size 0x80
    class Scoring mScoring; // offset 0x100, size 0x60
    class Profiler mLoadProf; // offset 0x160, size 0x58
    enum ExcitementLevel mExcitement; // offset 0x1B8, size 0x4
    enum ExcitementLevel mLastExcitement; // offset 0x1BC, size 0x4
    class CrowdAudio * mCrowdAudio; // offset 0x1C0, size 0x4
    class ObjPtr mIntroShot; // offset 0x1C4, size 0xC
    unsigned char mAnyController; // offset 0x1D0, size 0x1
    unsigned char mReplay; // offset 0x1D1, size 0x1
    float mStartButtonDownTime[4]; // offset 0x1D4, size 0x10
    class vector mJitter; // offset 0x1E4, size 0xC
    int mJitterIndex; // offset 0x1F0, size 0x4
    int mJitterWindow; // offset 0x1F4, size 0x4
    float mLastAverage; // offset 0x1F8, size 0x4
    float mLastMs; // offset 0x1FC, size 0x4
    unsigned char mDriveTime; // offset 0x200, size 0x1
};

