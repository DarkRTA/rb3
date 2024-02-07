/*
    Compile unit: C:\rockband2\band2\src\meta\BotbPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802072F4 -> 0x8020D670
*/
class Symbol t; // size: 0x4, address: 0x80A4E714
class DataArray * types; // size: 0x4, address: 0x80A4E718
class BotbPanel * TheBotbPanel; // size: 0x4, address: 0x80A4E720
// Range: 0x802072F4 -> 0x80207300
void BotbRequestOverallPage() {
    // References
    // -> class BotbPanel * TheBotbPanel;
}

// Range: 0x80207300 -> 0x80207398
char * NetStateName() {}

class _List_node : public _List_node_base {
    // total size: 0x3C
public:
    class BotbBattleResultsRow _M_data; // offset 0x8, size 0x34
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80207398 -> 0x80207578
void * BotbPanel::BotbPanel(class BotbPanel * const this /* r30 */) {
    // References
    // -> class BotbPanel * TheBotbPanel;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__9BotbPanel;
}

struct BotbResultsCache {
    // total size: 0x58
    class HxGuid mBandId; // offset 0x0, size 0x10
    class Timer mValidCacheTimer; // offset 0x10, size 0x38
    unsigned char mPartialData; // offset 0x48, size 0x1
    class MemStream * mCache; // offset 0x4C, size 0x4
    unsigned int mQueryTimeSeconds; // offset 0x50, size 0x4
};
struct pair {
    // total size: 0x8
    int first; // offset 0x0, size 0x4
    struct BotbResultsCache * second; // offset 0x4, size 0x4
};
static class Symbol summary; // size: 0x4, address: 0x80A4E728
static class Symbol summary; // size: 0x4, address: 0x80A4E730
struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x80207578 -> 0x80207DCC
void BotbPanel::Enter(class BotbPanel * const this /* r26 */) {
    // Local variables
    class ObjectDir * dir; // r29
    unsigned char invalidBattleCache; // r28
    unsigned char partiallyValidBattlecache; // r27
    struct _Rb_tree_iterator it; // r1+0x2C
    unsigned int oldDirtyMask; // r23
    class MemStream * mem; // r22
    struct DateTime curTime; // r1+0x30
    int rank; // r0

    // References
    // -> static class Symbol summary;
    // -> static class Symbol summary;
    // -> class RockCentralGateway RockCentral;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol summary; // size: 0x4, address: 0x80A4E738
static class Symbol setlist; // size: 0x4, address: 0x80A4E740
static class Symbol friends; // size: 0x4, address: 0x80A4E748
static class Symbol overall; // size: 0x4, address: 0x80A4E750
// Range: 0x80207DCC -> 0x80207F4C
void BotbPanel::ShowTab(class BotbPanel * const this /* r29 */, class Symbol & name /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class Symbol overall;
    // -> static class Symbol friends;
    // -> static class Symbol setlist;
    // -> static class Symbol summary;
}

// Range: 0x80207F4C -> 0x80208050
void BotbPanel::InvalidateBattleCache(class BotbPanel * const this /* r29 */) {
    // Local variables
    struct _Rb_tree_iterator it; // r1+0x14

    // References
    // -> const char * gNullStr;
}

// Range: 0x80208050 -> 0x802083C8
void BotbPanel::Exit(class BotbPanel * const this /* r30 */) {
    // Local variables
    unsigned int oldDirtyMask; // r29

    // References
    // -> class RockCentralGateway RockCentral;
    // -> const char * gNullStr;
}

// Range: 0x802083C8 -> 0x802086C4
void BotbPanel::Unload(class BotbPanel * const this /* r31 */) {}

// Range: 0x80208724 -> 0x80208874
void BotbPanel::Poll(class BotbPanel * const this /* r28 */) {
    // Local variables
    class ObjectDir * dir; // r29

    // References
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
}

// Range: 0x80208874 -> 0x80208A18
void BotbPanel::SyncSave(const class BotbPanel * const this /* r30 */, class BinStream & dest /* r31 */, unsigned int dirtyMask /* r29 */) {
    // Local variables
    struct DateTime curTime; // r1+0x20
    unsigned int curTimeCode; // r0
    unsigned char exists; // r29
}

// Range: 0x80208A18 -> 0x80208BFC
void BotbPanel::SyncLoad(class BotbPanel * const this /* r30 */, class BinStream & src /* r31 */, unsigned int dirtyMask /* r29 */) {
    // Local variables
    int deltaTime; // r1+0xC
    struct DateTime curTime; // r1+0x10
    unsigned int curTimeCode; // r0
}

// Range: 0x80208BFC -> 0x80208CAC
void BotbPanel::UpdateRivalData(class BotbPanel * const this /* r28 */) {
    // Local variables
    class TourBand * band; // r29

    // References
    // -> class Tour * TheTour;
}

static class Message gotoProfileScreenMsg; // size: 0x8, address: 0x8097C918
// Range: 0x80208CAC -> 0x80209050
void BotbPanel::OnSynchronized(class BotbPanel * const this /* r30 */, unsigned int dirtyMask /* r31 */) {
    // Local variables
    class TourBand * band; // r29
    class TourEvent * e; // r29
    int i; // r28
    int i; // r28

    // References
    // -> static class Message gotoProfileScreenMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
}

// Range: 0x80209050 -> 0x802090BC
void BotbPanel::ClientSynchronizeDetails(class BotbPanel * const this /* r31 */) {}

// Range: 0x802090BC -> 0x80209118
unsigned char BotbPanel::HasSyncPermission() {
    // References
    // -> class NetSync * TheNetSync;
    // -> class NetSession * TheNetSession;
}

// Range: 0x80209118 -> 0x80209190
unsigned char BotbPanel::HasRockCentralPermission(const class BotbPanel * const this /* r30 */) {
    // References
    // -> class NetSync * TheNetSync;
    // -> class NetSession * TheNetSession;
}

static class Symbol botb_expired; // size: 0x4, address: 0x80A4E758
static class Message msg; // size: 0x8, address: 0x8097C930
static class Symbol botb_timeout; // size: 0x4, address: 0x80A4E760
// Range: 0x80209190 -> 0x80209454
void BotbPanel::UpdateTimeLeft(class BotbPanel * const this /* r31 */) {
    // Local variables
    class ObjectDir * dir; // r0
    struct DateTime curTime; // r1+0x28
    unsigned int curTimeCode; // r0
    int deltaTime; // r29
    int secondsLeft; // r29
    const char * timeVal; // r29
    const char * str; // r0

    // References
    // -> static class Symbol botb_timeout;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol botb_expired;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
}

static class Symbol botb_mini_setlist_0; // size: 0x4, address: 0x80A4E768
static class Symbol botb_mini_setlist_1; // size: 0x4, address: 0x80A4E770
static class Symbol botb_mini_setlist_2; // size: 0x4, address: 0x80A4E778
static class Symbol botb_mini_setlist_3; // size: 0x4, address: 0x80A4E780
static class Symbol botb_mini_setlist_long; // size: 0x4, address: 0x80A4E788
static class Symbol botb_best_score_mult; // size: 0x4, address: 0x80A4E790
static class Symbol botb_best_score_score; // size: 0x4, address: 0x80A4E798
static class Symbol botb_best_score_streak; // size: 0x4, address: 0x80A4E7A0
static class Symbol botb_best_stars; // size: 0x4, address: 0x80A4E7A8
static class Symbol botb_mini_world_overall; // size: 0x4, address: 0x80A4E7B0
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class BotbMiniRankings {
    // total size: 0x110
    char mType; // offset 0x0, size 0x1
    int mNum1; // offset 0x4, size 0x4
    int mNum2; // offset 0x8, size 0x4
    int mFriend; // offset 0xC, size 0x4
    char mText[255]; // offset 0x10, size 0xFF
};
// Range: 0x80209454 -> 0x8020A38C
void BotbPanel::UpdateDetails(class BotbPanel * const this /* r25 */) {
    // Local variables
    class ObjectDir * dir; // r29
    enum WinMetric winMetric; // r28
    const char * string; // r4
    unsigned char hasFriends; // r27
    const class list * rlist; // r26
    const class list * rlist; // r0
    const class list * rlist; // r30
    const class BotbBattleResultsRow * bestRow; // r27
    int myScore; // r26
    struct _List_iterator it; // r1+0x58
    const char * string; // r0
    const char * string; // r24
    const char * string; // r0
    class BotbMiniRankings item; // r1+0x68
    const char * string; // r0
    const char * albumArtFileName; // r24
    const char * path; // r24

    // References
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__10FileLoader;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol botb_mini_world_overall;
    // -> static class Symbol botb_best_stars;
    // -> static class Symbol botb_best_score_streak;
    // -> static class Symbol botb_best_score_score;
    // -> static class Symbol botb_best_score_mult;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> struct [anonymous] __vt__19BotbSetListProvider;
    // -> struct [anonymous] __vt__12ListProvider;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> static class Symbol botb_mini_setlist_long;
    // -> static class Symbol botb_mini_setlist_3;
    // -> static class Symbol botb_mini_setlist_2;
    // -> static class Symbol botb_mini_setlist_1;
    // -> static class Symbol botb_mini_setlist_0;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8020A38C -> 0x8020A394
void BotbPanel::OnRequestOverallPage() {}

// Range: 0x8020A394 -> 0x8020A45C
void BotbPanel::OnRequestOverallPages(class BotbPanel * const this /* r29 */, int request_idx /* r30 */, int count /* r31 */) {
    // Local variables
    int start; // r5
    int end; // r6

    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x8020A45C -> 0x8020A5EC
void BotbPanel::UpdateFocus(class BotbPanel * const this /* r29 */) {
    // Local variables
    class ObjectDir * dir; // r30
    class UIComponent * c; // r4
    class UIList * list; // r3

    // References
    // -> struct [anonymous] __RTTI__6UIList;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

// Range: 0x8020A5EC -> 0x8020A6F0
void BotbPanel::UpdateOverall(class BotbPanel * const this /* r28 */) {
    // Local variables
    const class list * rlist; // r0
    class ObjectDir * dir; // r0
    int pos; // r30
    int first_showing; // r29

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
}

// Range: 0x8020A6F0 -> 0x8020AC10
void BotbPanel::UpdateRules(class BotbPanel * const this /* r28 */) {
    // Local variables
    const char * ecStr; // r31
    const char * pmStr; // r29
    char token[256]; // r1+0x60
    int shared_entry_condition_state; // r1+0x40
    char * pcpy; // r3
    class BotbEntryCondition ec; // r1+0x58
    enum WinMetric m; // r4
    class BotbPerformanceModifier pm; // r1+0x50
    char * pcpy; // r3
    class BotbPerformanceModifier pm; // r1+0x48
    class ObjectDir * dir; // r27

    // References
    // -> struct [anonymous] __vt__21BotbRulesListProvider;
    // -> struct [anonymous] __vt__12ListProvider;
    // -> struct [anonymous] __RTTI__6UIList;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Debug TheDebug;
}

static class Symbol mtv_made_famous; // size: 0x4, address: 0x80A4E7B8
// Range: 0x8020AC10 -> 0x8020B110
void BotbPanel::ProcessSetList(class BotbPanel * const this /* r30 */) {
    // Local variables
    class list templist; // r1+0xA0
    struct _List_iterator it; // r1+0x88
    class Symbol songId; // r1+0x84
    struct BotbSetListItem item; // r1+0xA8

    // References
    // -> class Debug TheDebug;
    // -> class SongMgr & TheSongMgr;
    // -> const char * gNullStr;
    // -> static class Symbol mtv_made_famous;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std32_List_node<18BotbBattleSongInfo>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8020B110 -> 0x8020B14C
class DataNode BotbPanel::OnMsg() {}

// Range: 0x8020B14C -> 0x8020B188
class DataNode BotbPanel::OnMsg() {}

// Range: 0x8020B188 -> 0x8020B2B8
class DataNode BotbPanel::OnMsg(class BotbPanel * const this /* r26 */, const class UIComponentScrollMsg & msg /* r27 */) {
    // Local variables
    class UIList * list; // r28
    int pos; // r29
    int first_showing; // r27

    // References
    // -> struct [anonymous] __RTTI__6UIList;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

// Range: 0x8020B2B8 -> 0x8020B3F8
class DataNode BotbPanel::OnMsg(class BotbPanel * const this /* r29 */, const class ButtonDownMsg & msg /* r30 */) {}

static class Message msg; // size: 0x8, address: 0x8097C948
static class Message msg; // size: 0x8, address: 0x8097C960
static class Message msg; // size: 0x8, address: 0x8097C978
static class Message gotoProfileScreenMsg; // size: 0x8, address: 0x8097C990
// Range: 0x8020B3F8 -> 0x8020BFFC
class DataNode BotbPanel::OnMsg(class BotbPanel * const this /* r29 */) {
    // Local variables
    int rank; // r0
    int start_range; // r27
    int end_range; // r30
    class TourBand * band; // r0
    class TourEvent * e; // r27
    int i; // r26
    int i; // r26
    enum BotbNetProgress request; // r0

    // References
    // -> static class Message gotoProfileScreenMsg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
    // -> class RockCentralGateway RockCentral;
}

static class Message msgc; // size: 0x8, address: 0x8097C9A8
// Range: 0x8020BFFC -> 0x8020C168
class DataNode BotbPanel::OnMsg(class BotbPanel * const this /* r30 */) {
    // References
    // -> static class Message msgc;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8020C168 -> 0x8020C1D8
class DataNode BotbPanel::OnMsg(class BotbPanel * const this /* r30 */) {}

// Range: 0x8020C1D8 -> 0x8020C26C
unsigned char BotbPanel::CanPlay(const class BotbPanel * const this /* r31 */) {
    // References
    // -> class NetSync * TheNetSync;
}

// Range: 0x8020C26C -> 0x8020C320
unsigned char BotbPanel::ConditionsMet(const class BotbPanel * const this /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8020C320 -> 0x8020C3F0
void BotbPanel::TryToPlay(class BotbPanel * const this /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol botb_missing_dlc; // size: 0x4, address: 0x80A4E7C4
static class Symbol botb_missing_dlc_multi; // size: 0x4, address: 0x80A4E7CC
static class Symbol botb_missing_dlc_multi_two; // size: 0x4, address: 0x80A4E7D4
static class Symbol botb_buy_dlc; // size: 0x4, address: 0x80A4E7DC
static class Symbol botb_buy_dlc_multi; // size: 0x4, address: 0x80A4E7E4
static class Symbol botb_need_rb1_license; // size: 0x4, address: 0x80A4E7EC
static class Symbol botb_need_rb1_license_multi; // size: 0x4, address: 0x80A4E7F4
static class Symbol botb_license_and_store; // size: 0x4, address: 0x80A4E7FC
static class Symbol botb_ec_unknown; // size: 0x4, address: 0x80A4E804
// Range: 0x8020C3F0 -> 0x8020C868
char * BotbPanel::FailedConditionsMessage(const class BotbPanel * const this /* r28 */) {
    // Local variables
    int i; // r30
    unsigned char missingRB1Songs; // r27
    unsigned char missingStoreSongs; // r26
    int numMissing; // r30
    const char * song; // r29
    int i; // r25
    class Symbol buyMethod; // r1+0x24
    const char * dlc_msg; // r25

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol botb_ec_unknown;
    // -> static class Symbol botb_license_and_store;
    // -> static class Symbol botb_need_rb1_license_multi;
    // -> static class Symbol botb_need_rb1_license;
    // -> static class Symbol botb_buy_dlc_multi;
    // -> static class Symbol botb_buy_dlc;
    // -> static class Symbol botb_missing_dlc_multi_two;
    // -> static class Symbol botb_missing_dlc_multi;
    // -> static class Symbol botb_missing_dlc;
}

// Range: 0x8020C868 -> 0x8020C934
void BotbPanel::SelectFriendResult(class BotbPanel * const this /* r29 */) {
    // Local variables
    const class HxGuid & guid; // r30
    class ObjectDir * dir; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
}

// Range: 0x8020C934 -> 0x8020CA00
void BotbPanel::SelectOverallResult(class BotbPanel * const this /* r29 */) {
    // Local variables
    const class HxGuid & guid; // r30
    class ObjectDir * dir; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6UIList;
}

// Range: 0x8020CA00 -> 0x8020CB20
void BotbPanel::RequestBandProfile(class BotbPanel * const this /* r30 */, const class HxGuid & bandGuid /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x8020CB20 -> 0x8020CB74
unsigned char BotbPanel::IsFriendsListEmpty() {}

// Range: 0x8020CB74 -> 0x8020CBC8
unsigned char BotbPanel::IsOverallListEmpty() {}

// Range: 0x8020CBC8 -> 0x8020CC30
int BotbPanel::SetlistSize() {}

static class Symbol _s; // size: 0x4, address: 0x80A4E80C
static class Symbol _s; // size: 0x4, address: 0x80A4E814
static class Symbol _s; // size: 0x4, address: 0x80A4E81C
static class Symbol _s; // size: 0x4, address: 0x80A4E824
static class Symbol _s; // size: 0x4, address: 0x80A4E82C
static class Symbol _s; // size: 0x4, address: 0x80A4E834
static class Symbol _s; // size: 0x4, address: 0x80A4E83C
static class Symbol _s; // size: 0x4, address: 0x80A4E844
static class Symbol _s; // size: 0x4, address: 0x80A4E84C
static class Symbol _s; // size: 0x4, address: 0x80A4E854
static class Symbol _s; // size: 0x4, address: 0x80A4E85C
static class Symbol _s; // size: 0x4, address: 0x80A4E864
static class Symbol _s; // size: 0x4, address: 0x80A4E86C
// Range: 0x8020CC30 -> 0x8020D670
class DataNode BotbPanel::Handle(class BotbPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode _n; // r1+0x70

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
}

struct {
    // total size: 0x124
} __vt__9BotbPanel; // size: 0x124, address: 0x808ABBD8
struct {
    // total size: 0x8
} __RTTI__9BotbPanel; // size: 0x8, address: 0x808ABD48
struct {
    // total size: 0xC
} __vt__17UIScreenChangeMsg; // size: 0xC, address: 0x808ABE58
struct {
    // total size: 0x8
} __RTTI__17UIScreenChangeMsg; // size: 0x8, address: 0x808ABE88
struct {
    // total size: 0x8
} __RTTI__P23BotbPerformanceModifier; // size: 0x8, address: 0x808AC3B8
struct {
    // total size: 0x8
} __RTTI__P18BotbEntryCondition; // size: 0x8, address: 0x808AC3D8
struct {
    // total size: 0x8
} __RTTI__P15BotbSetListItem; // size: 0x8, address: 0x808AC3F8
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std60_Rb_tree_node<Q211stlpmtx_std28pair<Ci,P16BotbResultsCache>>; // size: 0x8, address: 0x808AC450

