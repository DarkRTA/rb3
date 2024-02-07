/*
    Compile unit: C:\rockband2\band2\src\meta\Tour.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801978D4 -> 0x8019B95C
*/
class Tour * TheTour; // size: 0x4, address: 0x80A4D088
class WorldStateBase {
    // total size: 0x1
};
struct TownData {
    // total size: 0x1C
    class Symbol mName; // offset 0x0, size 0x4
    class String mIcon; // offset 0x4, size 0xC
    enum TourStatus mStatus; // offset 0x10, size 0x4
    int mNumPlayers; // offset 0x14, size 0x4
    enum Difficulty mDifficulty; // offset 0x18, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct TownData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct TownData * _M_start; // offset 0x0, size 0x4
    struct TownData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class TownProvider : public ListProvider, public WorldStateBase, public Object {
    // total size: 0x40
    class vector mTowns; // offset 0x2C, size 0xC
    class TourBand * mBand; // offset 0x38, size 0x4
    const class TourWorld & mWorld; // offset 0x3C, size 0x4
};
struct VenueData {
    // total size: 0x20
    class Symbol mName; // offset 0x0, size 0x4
    class Symbol mToken; // offset 0x4, size 0x4
    class String mIcon; // offset 0x8, size 0xC
    enum TourStatus mStatus; // offset 0x14, size 0x4
    int mNumPlayers; // offset 0x18, size 0x4
    enum Difficulty mDifficulty; // offset 0x1C, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct VenueData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct VenueData * _M_start; // offset 0x0, size 0x4
    struct VenueData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class VenueProvider : public ListProvider, public WorldStateBase, public Object {
    // total size: 0x40
    class vector mVenues; // offset 0x2C, size 0xC
    class TourBand * mBand; // offset 0x38, size 0x4
    const class TourWorld & mWorld; // offset 0x3C, size 0x4
};
struct EventData {
    // total size: 0x1C
    class TourWorldEvent * mEvent; // offset 0x0, size 0x4
    enum TourStatus mStatus; // offset 0x4, size 0x4
    class String mIcon; // offset 0x8, size 0xC
    int mNumPlayers; // offset 0x14, size 0x4
    enum Difficulty mDifficulty; // offset 0x18, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct EventData * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct EventData * _M_start; // offset 0x0, size 0x4
    struct EventData * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class EventProvider : public ListProvider, public WorldStateBase, public Object {
    // total size: 0x40
    class vector mEvents; // offset 0x2C, size 0xC
    const class TourWorld & mWorld; // offset 0x38, size 0x4
    class TourBand * mBand; // offset 0x3C, size 0x4
};
class EventSongProvider : public ListProvider, public Object {
    // total size: 0x34
    const class SongMgr & mSongMgr; // offset 0x2C, size 0x4
    class TourBand * mBand; // offset 0x30, size 0x4
};
class HometownProvider : public ListProvider, public Object {
    // total size: 0x38
    class vector mHometowns; // offset 0x2C, size 0xC
};
class RequirementProvider : public ListProvider, public Object {
    // total size: 0x38
    class vector mReqs; // offset 0x2C, size 0xC
};
class StaffProvider : public ListProvider, public Object {
    // total size: 0x30
    const class vector & mStaff; // offset 0x2C, size 0x4
};
// Range: 0x801978D4 -> 0x80197BC0
void * Tour::Tour(class Tour * const this /* r31 */, class DataArray * cfg /* r30 */, const class SongMgr & song_mgr /* r29 */, unsigned char load_logo /* r27 */) {
    // References
    // -> struct [anonymous] __vt__19RequirementProvider;
    // -> struct [anonymous] __vt__12ListProvider;
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
    // -> struct [anonymous] __vt__4Tour;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class TourCharLocal * _M_data; // offset 0x8, size 0x4
};
// Range: 0x80197BE8 -> 0x80197E80
void * Tour::~Tour(class Tour * const this /* r30 */) {
    // References
    // -> class Tour * TheTour;
    // -> struct [anonymous] __vt__4Tour;
}

// Range: 0x8019843C -> 0x80198444
class TourChallenge & Tour::GetChallenge() {}

// Range: 0x80198444 -> 0x8019844C
class TourWorld & Tour::GetWorld() {}

// Range: 0x8019844C -> 0x80198454
class TourBand * Tour::GetBand() {}

static double kValidBattleDurationMs; // size: 0x8, address: 0x808484F8
// Range: 0x80198454 -> 0x801984FC
unsigned char Tour::DirtyBattles(const class Tour * const this /* r8 */) {
    // References
    // -> static double kValidBattleDurationMs;
    // -> double sDoubleCycles2Ms;
}

// Range: 0x801984FC -> 0x801987E4
unsigned char Tour::HasBotbChallenges(const class Tour * const this /* r30 */) {
    // Local variables
    int leader_num; // r0
    class list shared_c; // r1+0x90
    class vector users; // r1+0x98
    class BandUser * * u; // r31
    const class list & rc; // r28
    struct _List_iterator c; // r1+0x7C

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class SessionMgr * TheSessionMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801987E4 -> 0x80198858
class TourHint * Tour::GetBandHint() {
    // Local variables
    class TourHint * t; // r31

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80198858 -> 0x801989B0
char * Tour::TourScreen(const class Tour * const this /* r29 */, unsigned char from_game /* r30 */) {
    // Local variables
    class TourHint * h; // r0
    class TourEvent * e; // r0
    class TourHint * h; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801989B0 -> 0x80198A30
char * Tour::LoadingScreen(const class Tour * const this /* r30 */) {
    // Local variables
    const char * loading_screen; // r31
    class TourEvent * e; // r0

    // References
    // -> const char * gNullStr;
}

class TourBandRemote : public TourBand {
    // total size: 0x240
    const class RemoteBandData * mCachedData; // offset 0x1DC, size 0x4
    class TourMoment * mNextMoment; // offset 0x1E0, size 0x4
    int mStarRating; // offset 0x1E4, size 0x4
    enum Difficulty mDifficultyRating; // offset 0x1E8, size 0x4
    class String mCensoredName; // offset 0x1EC, size 0xC
    class String mCensoredMotto; // offset 0x1F8, size 0xC
    class OnlineID * mOwnerID; // offset 0x204, size 0x4
    class String mOwnerName; // offset 0x208, size 0xC
};
// Range: 0x80198A30 -> 0x80198B14
enum TourMode Tour::GetMode(class Tour * const this /* r29 */) {
    // Local variables
    class TourBandRemote * rtBand; // r0
    class TourBandLocal * ltBand; // r0

    // References
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class NetSession * TheNetSession;
    // -> struct [anonymous] __RTTI__8TourBand;
    // -> struct [anonymous] __RTTI__14TourBandRemote;
}

static class Symbol remote_player_left; // size: 0x4, address: 0x80A4D090
static class Symbol new_remote_player; // size: 0x4, address: 0x80A4D098
// Range: 0x80198B14 -> 0x80198DC0
void Tour::SetBand(class Tour * const this /* r31 */, class TourBand * b /* r29 */) {
    // Local variables
    class TourBandLocal * ltb; // r0

    // References
    // -> static class Symbol new_remote_player;
    // -> static class Symbol remote_player_left;
    // -> class Net TheNet;
    // -> class RockCentralGateway RockCentral;
    // -> const char * gNullStr;
    // -> class Symbol t;
    // -> struct [anonymous] __RTTI__16BandProfilePanel;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__17BotbNewsFeedPanel;
    // -> class ObjectDir * sMainDir;
    // -> class BotbPanel * TheBotbPanel;
    // -> struct [anonymous] __RTTI__8TourBand;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol remote_player_left; // size: 0x4, address: 0x80A4D0A0
static class Symbol new_remote_player; // size: 0x4, address: 0x80A4D0A8
// Range: 0x80198DC0 -> 0x80198FE8
void Tour::ClearBand(class Tour * const this /* r31 */) {
    // Local variables
    class TourBandLocal * ltb; // r29

    // References
    // -> class BotbPanel * TheBotbPanel;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__13TourBandLocal;
    // -> struct [anonymous] __RTTI__8TourBand;
    // -> struct [anonymous] __RTTI__14TourBandRemote;
    // -> static class Symbol new_remote_player;
    // -> static class Symbol remote_player_left;
    // -> class Net TheNet;
    // -> class RockCentralGateway RockCentral;
    // -> const char * gNullStr;
}

// Range: 0x80198FE8 -> 0x80199010
class HxGuid * Tour::GetLastBandSet() {}

// Range: 0x80199010 -> 0x80199088
void Tour::OverrideLastBandSet(class Tour * const this /* r30 */, const class HxGuid & guid /* r31 */) {}

// Range: 0x80199088 -> 0x801990E0
void Tour::SetDirtyBattles(class Tour * const this /* r31 */) {}

// Range: 0x801990E0 -> 0x8019944C
void Tour::CreateBattles(class Tour * const this /* r31 */, class BotbChallengeLoader & bl /* r29 */) {
    // Local variables
    class list challenge_names; // r1+0x50
    class vector we; // r1+0x70
    class list world_names; // r1+0x48
    int i; // r29
    class vector local_nums; // r1+0x64
    int i; // r30
    class LocalBattlesMsg msg; // r1+0x80

    // References
    // -> class Net TheNet;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__Pi;
    // -> unsigned char gStlAllocNameLookup;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SessionMgr * TheSessionMgr;
}

static class Message update; // size: 0x8, address: 0x80979EF0
// Range: 0x8019944C -> 0x801996C0
void Tour::SetSharedBattles(class Tour * const this /* r26 */, int user_num /* r27 */, const class list & challenge_battles /* r28 */, const class list & world_battles /* r29 */) {
    // Local variables
    class MultiFocusScreen * mfs; // r31

    // References
    // -> static class Message update;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> struct [anonymous] __RTTI__16MultiFocusScreen;
    // -> class UIManager TheUI;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801996C0 -> 0x80199B1C
void Tour::SendSharedBattles(class Tour * const this /* r30 */) {
    // Local variables
    int leader_num; // r0
    class list shared_c; // r1+0xF0
    class list shared_w; // r1+0xE8
    class vector users; // r1+0xF8
    class BandUser * * u; // r31
    const class list & rc; // r27
    struct _List_iterator c; // r1+0xC0
    const class list & rw; // r27
    struct _List_iterator w; // r1+0xBC
    class SharedBattlesMsg msg; // r1+0x104

    // References
    // -> class Net TheNet;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class SessionMgr * TheSessionMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80199B1C -> 0x80199BAC
void Tour::SyncSharedBattles(class Tour * const this /* r29 */, const class list & shared_challenge /* r30 */, const class list & shared_world /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80199BAC -> 0x80199C14
void Tour::ClearSharedBattles(class Tour * const this /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x80199C14 -> 0x80199C8C
class DataNode Tour::OnMsg(class Tour * const this /* r30 */) {}

// Range: 0x80199C8C -> 0x80199CFC
class DataNode Tour::OnMsg(class Tour * const this /* r30 */) {}

// Range: 0x80199CFC -> 0x80199D6C
class DataNode Tour::OnMsg(class Tour * const this /* r30 */) {}

// Range: 0x80199D6C -> 0x80199DE8
void Tour::ClearUserSharedBattles(class Tour * const this /* r29 */, int user_num /* r30 */) {
    // References
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x80199DE8 -> 0x8019A008
void Tour::SetUserSharedBattles(class Tour * const this /* r28 */, int user_num /* r29 */) {
    // Local variables
    class User * user; // r0
    class vector users; // r1+0x40
    class BandUser * * it; // r7
    class User * pu; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8019A008 -> 0x8019A27C
void Tour::CreateTestEvent(class Tour * const this /* r29 */) {
    // Local variables
    int i; // r30
    class BandUser * user; // r25
    class Symbol instrument; // r1+0x34

    // References
    // -> class SongMgr & TheSongMgr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<P13TourCharLocal>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> class BandUserMgr * TheBandUserMgr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<P13TourCharLocal>; // size: 0x8, address: 0x8089DC70
// Range: 0x8019A27C -> 0x8019A290
unsigned char Tour::ToggleAllExpired() {
    // References
    // -> unsigned char sAllExpired;
}

// Range: 0x8019A290 -> 0x8019A2A4
unsigned char Tour::ToggleAllLive() {
    // References
    // -> unsigned char sAllLive;
}

// Range: 0x8019A2A4 -> 0x8019A318
void Tour::SetRemoteBand(class Tour * const this /* r30 */, const class RemoteBandData * band /* r31 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
}

static class Symbol ui; // size: 0x4, address: 0x80A4D0B0
static class Symbol update_band; // size: 0x4, address: 0x80A4D0B8
// Range: 0x8019A318 -> 0x8019A57C
class DataNode Tour::OnUpdateChar(class DataArray * a /* r29 */) {
    // Local variables
    class CharData * p; // r0
    class TourCharRemote * rtc; // r30
    class DataArrayPtr ui_msg; // r1+0x28

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol update_band;
    // -> static class Symbol ui;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8CharData;
    // -> struct [anonymous] __RTTI__14TourCharRemote;
    // -> class BandUserMgr * TheBandUserMgr;
}

// Range: 0x8019A57C -> 0x8019A644
class DataNode Tour::OnUpdateCharAppearance(class DataArray * a /* r30 */) {
    // Local variables
    class BandUser * user; // r31

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8019A644 -> 0x8019A764
class DataNode Tour::OnVenueToken(class Tour * const this /* r29 */, class DataArray * a /* r30 */) {
    // Local variables
    class Symbol town; // r1+0x30
    class Symbol venue; // r1+0x2C

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8019A764 -> 0x8019A7E4
class DataNode Tour::OnEvent(class Tour * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4D0C0
static class Symbol _s; // size: 0x4, address: 0x80A4D0C8
static class Symbol _s; // size: 0x4, address: 0x80A4D0D0
static class Symbol _s; // size: 0x4, address: 0x80A4D0D8
static class Symbol _s; // size: 0x4, address: 0x80A4D0E0
static class Symbol _s; // size: 0x4, address: 0x80A4D0E8
static class Symbol _s; // size: 0x4, address: 0x80A4D0F0
static class Symbol _s; // size: 0x4, address: 0x80A4D0F8
static class Symbol _s; // size: 0x4, address: 0x80A4D100
static class Symbol _s; // size: 0x4, address: 0x80A4D108
static class Symbol _s; // size: 0x4, address: 0x80A4D110
static class Symbol _s; // size: 0x4, address: 0x80A4D118
static class Symbol _s; // size: 0x4, address: 0x80A4D120
static class Symbol _s; // size: 0x4, address: 0x80A4D128
static class Symbol _s; // size: 0x4, address: 0x80A4D130
static class Symbol _s; // size: 0x4, address: 0x80A4D138
static class Symbol _s; // size: 0x4, address: 0x80A4D140
static class Symbol _s; // size: 0x4, address: 0x80A4D148
static class Symbol _s; // size: 0x4, address: 0x80A4D150
static class Symbol _s; // size: 0x4, address: 0x80A4D158
static class Symbol _s; // size: 0x4, address: 0x80A4D160
static class Symbol _s; // size: 0x4, address: 0x80A4D168
static class Symbol _s; // size: 0x4, address: 0x80A4D170
static class Symbol _s; // size: 0x4, address: 0x80A4D178
static class Symbol _s; // size: 0x4, address: 0x80A4D180
static class Symbol _s; // size: 0x4, address: 0x80A4D188
static class Symbol _s; // size: 0x4, address: 0x80A4D190
static class Symbol _s; // size: 0x4, address: 0x80A4D198
static class Symbol _s; // size: 0x4, address: 0x80A4D1A0
static class Symbol _s; // size: 0x4, address: 0x80A4D1A8
static class Symbol _s; // size: 0x4, address: 0x80A4D1B0
static class Symbol _s; // size: 0x4, address: 0x80A4D1B8
// Range: 0x8019A7E4 -> 0x8019B7E4
class DataNode Tour::Handle(class Tour * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode _n; // r1+0x50

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
}

static class Symbol _s; // size: 0x4, address: 0x80A4D1C0
// Range: 0x8019B7E4 -> 0x8019B95C
unsigned char Tour::SyncProperty(class Tour * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8
} __RTTI__14TourBandRemote; // size: 0x8, address: 0x8089E280
struct {
    // total size: 0x8
} __RTTI__17BotbNewsFeedPanel; // size: 0x8, address: 0x8089E438
struct {
    // total size: 0x54
} __vt__4Tour; // size: 0x54, address: 0x8089E570
struct {
    // total size: 0x8
} __RTTI__4Tour; // size: 0x8, address: 0x8089E5E0

