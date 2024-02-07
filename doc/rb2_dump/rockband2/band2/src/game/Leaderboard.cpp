/*
    Compile unit: C:\rockband2\band2\src\game\Leaderboard.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800A4264 -> 0x800A89C0
*/
class ListProviderObject : public ListProvider, public Object {
    // total size: 0x2C
};
enum FilterType {
    kByID = 0,
    kByRank = 1,
    kNumFilters = 2,
};
class Leaderboard : public ListProviderObject {
    // total size: 0x78
protected:
    class LeaderboardData * mData; // offset 0x2C, size 0x4
    class RndMat * mSongBgMat; // offset 0x30, size 0x4
    class EntityID mEntityID; // offset 0x34, size 0x18
    int mDataStartRank; // offset 0x4C, size 0x4
    enum FilterType mFilter; // offset 0x50, size 0x4
    unsigned char mPageUp; // offset 0x54, size 0x1
    int mNumEntries; // offset 0x58, size 0x4
    int mDataCount; // offset 0x5C, size 0x4
    int mListIxOffset; // offset 0x60, size 0x4
    int mListCurPos; // offset 0x64, size 0x4
    unsigned long long mLowestScore; // offset 0x68, size 0x8
    class Symbol no_results_warning; // offset 0x70, size 0x4
};
// Range: 0x800A4264 -> 0x800A4348
void * Leaderboard::Leaderboard(class Leaderboard * const this /* r29 */, class LeaderboardData * pData /* r31 */, class EntityID & id /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__11Leaderboard;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x800A4348 -> 0x800A43EC
void * Leaderboard::~Leaderboard(class Leaderboard * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__11Leaderboard;
}

// Range: 0x800A43EC -> 0x800A4428
unsigned char Leaderboard::CancelEnumerate() {}

static class Symbol song_bg; // size: 0x4, address: 0x80A4A2F4
// Range: 0x800A4428 -> 0x800A44F8
class RndMat * Leaderboard::Mat(const class Leaderboard * const this /* r27 */, int data /* r28 */, class Symbol & slot /* r29 */) {
    // References
    // -> static class Symbol song_bg;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol name; // size: 0x4, address: 0x80A4A2FC
static class Symbol rank; // size: 0x4, address: 0x80A4A304
// Range: 0x800A44F8 -> 0x800A469C
char * Leaderboard::Text(const class Leaderboard * const this /* r30 */, int data /* r31 */, class Symbol & slot /* r28 */) {
    // Local variables
    const class LeaderboardResultList * resultList; // r29
    const class LeaderboardResultRow * pRow; // r4

    // References
    // -> static class Symbol rank;
    // -> static class Symbol name;
}

static class Symbol rank; // size: 0x4, address: 0x80A4A30C
static class Symbol name; // size: 0x4, address: 0x80A4A314
static class Symbol shortcut; // size: 0x4, address: 0x80A4A31C
static class Symbol score; // size: 0x4, address: 0x80A4A324
// Range: 0x800A469C -> 0x800A4844
char * Leaderboard::GetTextFromRow(const class LeaderboardResultRow * pRow /* r29 */, class Symbol & slot /* r30 */) {
    // Local variables
    int score; // r0

    // References
    // -> class Debug TheDebug;
    // -> class PlatformMgr ThePlatformMgr;
    // -> static class Symbol score;
    // -> static class Symbol shortcut;
    // -> static class Symbol name;
    // -> static class Symbol rank;
}

// Range: 0x800A4844 -> 0x800A4888
class LeaderboardResultRow * Leaderboard::GetDisplayRow(const class Leaderboard * const this /* r31 */) {}

// Range: 0x800A4888 -> 0x800A4894
int Leaderboard::DisplayToDataIx() {}

// Range: 0x800A4894 -> 0x800A48B4
int Leaderboard::GetUserPos() {}

// Range: 0x800A48B4 -> 0x800A48BC
void Leaderboard::SetUserPos() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x800A48BC -> 0x800A4D44
unsigned char Leaderboard::OnEnumComplete(class Leaderboard * const this /* r29 */) {
    // Local variables
    const class list * pRows; // r0
    int pageSize; // r1+0x50
    int listIndex; // r30
    struct _List_iterator it; // r1+0x4C
    int ixFirstRow; // r5

    // References
    // -> class LeaderboardsMgr * TheLeaderboards;
}

static class Message warningMsg; // size: 0x8, address: 0x80977AA0
static class Message unrankedMsg; // size: 0x8, address: 0x80977AB8
static class Message unrankedMsg; // size: 0x8, address: 0x80977AD0
static class Message warningMsg; // size: 0x8, address: 0x80977AE8
static class Message warningMsg; // size: 0x8, address: 0x80977B00
static class Message unrankedMsg; // size: 0x8, address: 0x80977B18
static class Message updateMsg; // size: 0x8, address: 0x80977B30
// Range: 0x800A4D44 -> 0x800A5A8C
void Leaderboard::ShowData(class Leaderboard * const this /* r29 */) {
    // Local variables
    class String s; // r1+0x138

    // References
    // -> static class Message updateMsg;
    // -> static class Message unrankedMsg;
    // -> static class Message warningMsg;
    // -> static class Message warningMsg;
    // -> static class Message unrankedMsg;
    // -> class LeaderboardsMgr * TheLeaderboards;
    // -> static class Message unrankedMsg;
    // -> class UIManager TheUI;
    // -> static class Message warningMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800A5A8C -> 0x800A5B6C
class Symbol Leaderboard::OnSelectRow(class Leaderboard * const this /* r29 */, int playerNum /* r30 */) {
    // Local variables
    const class LeaderboardResultRow * pRow; // r31

    // References
    // -> const char * gNullStr;
}

// Range: 0x800A5B6C -> 0x800A5B98
unsigned char Leaderboard::CanRowsBeSelected() {}

static class Symbol _s; // size: 0x4, address: 0x80A4A330
static class Symbol _s; // size: 0x4, address: 0x80A4A338
static class Symbol _s; // size: 0x4, address: 0x80A4A340
static class Symbol _s; // size: 0x4, address: 0x80A4A348
static class Symbol _s; // size: 0x4, address: 0x80A4A350
static class Symbol _s; // size: 0x4, address: 0x80A4A358
static class Symbol _s; // size: 0x4, address: 0x80A4A360
static class Symbol _s; // size: 0x4, address: 0x80A4A368
static class Symbol _s; // size: 0x4, address: 0x80A4A370
static class Symbol _s; // size: 0x4, address: 0x80A4A378
static class Symbol _s; // size: 0x4, address: 0x80A4A380
// Range: 0x800A5B98 -> 0x800A6934
class DataNode Leaderboard::Handle(class Leaderboard * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x58
    class MessageTimer _mt; // r1+0x68
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol leaderboard_nobody_ranked; // size: 0x4, address: 0x80A4A388
class LeaderboardLive : public Leaderboard {
    // total size: 0x80
    class ChampShortcutProvider * mFriendProvider; // offset 0x74, size 0x4
    class LeaderboardData * mChampData; // offset 0x78, size 0x4
};
// Range: 0x800A6934 -> 0x800A6A10
void * LeaderboardLive::LeaderboardLive(class LeaderboardLive * const this /* r31 */, class LeaderboardData * pChampData /* r27 */, class LeaderboardData * pData /* r28 */, int playerNum /* r29 */, class EntityID & id /* r30 */) {
    // References
    // -> static class Symbol leaderboard_nobody_ranked;
    // -> struct [anonymous] __vt__15LeaderboardLive;
}

// Range: 0x800A6A10 -> 0x800A6AD8
void * LeaderboardLive::~LeaderboardLive(class LeaderboardLive * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15LeaderboardLive;
}

// Range: 0x800A6B3C -> 0x800A6C84
void LeaderboardLive::RequestNewPage(class LeaderboardLive * const this /* r31 */, unsigned char down /* r29 */) {
    // References
    // -> class LeaderboardsMgr * TheLeaderboards;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800A6C84 -> 0x800A6D20
void LeaderboardLive::OnNextLandmark(class LeaderboardLive * const this /* r29 */, int dataIx /* r30 */) {
    // Local variables
    int shortcutCount; // r0
    int shortcutIx; // r0
}

// Range: 0x800A6D20 -> 0x800A6D68
int LeaderboardLive::IxCurrentLandmark(class LeaderboardLive * const this /* r31 */) {
    // Local variables
    const class LeaderboardResultRow * pRow; // r0
}

// Range: 0x800A6D68 -> 0x800A6F54
void LeaderboardLive::EnumerateLandmark(class LeaderboardLive * const this /* r31 */) {
    // Local variables
    int i; // r29

    // References
    // -> class LeaderboardsMgr * TheLeaderboards;
}

// Range: 0x800A6F54 -> 0x800A6FBC
char * LeaderboardLive::GetChampText(const class LeaderboardLive * const this /* r30 */, class Symbol & slot /* r31 */) {
    // Local variables
    const class LeaderboardResultRow * row; // r0
}

// Range: 0x800A6FBC -> 0x800A7340
unsigned char LeaderboardLive::EnumComplete(class LeaderboardLive * const this /* r31 */) {
    // Local variables
    enum DataEnumState state; // r0
    enum DataEnumState state; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LeaderboardsMgr * TheLeaderboards;
}

// Range: 0x800A7340 -> 0x800A73A4
unsigned char LeaderboardLive::CancelEnumerate(class LeaderboardLive * const this /* r31 */) {}

class LeaderboardCached : public Leaderboard {
    // total size: 0x78
protected:
    class ShortcutProviderWrapper * mShortcutProvider; // offset 0x74, size 0x4
};
// Range: 0x800A73A4 -> 0x800A7498
void * LeaderboardCached::LeaderboardCached(class LeaderboardCached * const this /* r28 */, class LeaderboardData * pData /* r29 */, int playerNum /* r30 */, class EntityID & id /* r31 */) {
    // References
    // -> struct [anonymous] __vt__23ShortcutProviderWrapper;
    // -> struct [anonymous] __vt__12ListProvider;
    // -> struct [anonymous] __vt__17LeaderboardCached;
}

// Range: 0x800A7498 -> 0x800A7534
void * LeaderboardCached::~LeaderboardCached(class LeaderboardCached * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__17LeaderboardCached;
}

// Range: 0x800A7598 -> 0x800A7694
unsigned char LeaderboardCached::EnumComplete(class LeaderboardCached * const this /* r31 */) {
    // Local variables
    enum DataEnumState state; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LeaderboardsMgr * TheLeaderboards;
}

// Range: 0x800A7694 -> 0x800A77B0
void LeaderboardCached::RequestNewPage(class LeaderboardCached * const this /* r31 */, unsigned char down /* r30 */) {
    // References
    // -> class LeaderboardsMgr * TheLeaderboards;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800A77B0 -> 0x800A7874
void LeaderboardCached::EnumerateLandmark(class LeaderboardCached * const this /* r30 */) {
    // Local variables
    const class LeaderboardResultRow * row; // r0
}

// Range: 0x800A7874 -> 0x800A78E0
void LeaderboardCached::OnNextLandmark(class LeaderboardCached * const this /* r31 */) {
    // Local variables
    int ShortcutIx; // r0
}

// Range: 0x800A78E0 -> 0x800A7928
int LeaderboardCached::IxCurrentLandmark(class LeaderboardCached * const this /* r31 */) {
    // Local variables
    const class LeaderboardResultRow * pRow; // r0
}

// Range: 0x800A7928 -> 0x800A7954
int LeaderboardCached::NumData() {
    // References
    // -> class LeaderboardsMgr * TheLeaderboards;
}

// Range: 0x800A7954 -> 0x800A79B0
char * LeaderboardCached::GetChampText(const class LeaderboardCached * const this /* r31 */) {}

static class Symbol leaderboard_no_ranked_friends; // size: 0x4, address: 0x80A4A390
class LeaderboardFriends : public LeaderboardCached {
    // total size: 0x78
};
// Range: 0x800A79B0 -> 0x800A7A8C
void * LeaderboardFriends::LeaderboardFriends(class LeaderboardFriends * const this /* r28 */, class LeaderboardData * pData /* r29 */, int playerNum /* r30 */, class EntityID & id /* r31 */) {
    // References
    // -> static class Symbol leaderboard_no_ranked_friends;
    // -> struct [anonymous] __vt__18LeaderboardFriends;
}

// Range: 0x800A7A8C -> 0x800A7B70
void LeaderboardFriends::SpecializedEnumerate(class LeaderboardFriends * const this /* r28 */) {}

static class Symbol leaderboards_no_local_bands; // size: 0x4, address: 0x80A4A398
class LeaderboardLocal : public LeaderboardCached {
    // total size: 0x78
};
// Range: 0x800A7B70 -> 0x800A7C4C
void * LeaderboardLocal::LeaderboardLocal(class LeaderboardLocal * const this /* r28 */, class LeaderboardData * pData /* r29 */, int playerNum /* r30 */, class EntityID & id /* r31 */) {
    // References
    // -> static class Symbol leaderboards_no_local_bands;
    // -> struct [anonymous] __vt__16LeaderboardLocal;
}

// Range: 0x800A7C4C -> 0x800A7D30
void LeaderboardLocal::SpecializedEnumerate(class LeaderboardLocal * const this /* r28 */) {}

class ChampShortcutProvider : public ListProviderObject {
    // total size: 0x34
    const class LeaderboardData * mFriends; // offset 0x2C, size 0x4
    const class LeaderboardData * mChamp; // offset 0x30, size 0x4
};
// Range: 0x800A7D30 -> 0x800A7E28
char * ChampShortcutProvider::Text(const class ChampShortcutProvider * const this /* r29 */, int data /* r30 */) {
    // Local variables
    const class LeaderboardResultRow * p; // r0
    int ix; // r31
    struct _List_iterator it; // r1+0x18

    // References
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x800A7E28 -> 0x800A7F38
int ChampShortcutProvider::NumData(const class ChampShortcutProvider * const this /* r30 */) {}

// Range: 0x800A7F38 -> 0x800A7FB8
int ChampShortcutProvider::GetRowIxFromRank(const class ChampShortcutProvider * const this /* r29 */, int rank /* r30 */) {
    // Local variables
    int result; // r0
    const class LeaderboardResultRow * row; // r0
}

// Range: 0x800A7FB8 -> 0x800A8018
class list * ChampShortcutProvider::GetRows() {}

// Range: 0x800A8018 -> 0x800A8140
class LeaderboardResultRow * ChampShortcutProvider::GetRow(class ChampShortcutProvider * const this /* r30 */, int ix /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x28
    int j; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A4A3A0
// Range: 0x800A8140 -> 0x800A84F0
class DataNode ChampShortcutProvider::Handle(class ChampShortcutProvider * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class ShortcutProviderWrapper : public ListProviderObject {
    // total size: 0x30
    const class LeaderboardCached * mShortcuts; // offset 0x2C, size 0x4
};
// Range: 0x800A84F0 -> 0x800A8568
char * ShortcutProviderWrapper::Text(const class ShortcutProviderWrapper * const this /* r29 */, int ix /* r30 */, class Symbol & slot /* r31 */) {
    // Local variables
    const class LeaderboardResultRow * resultRow; // r0
}

// Range: 0x800A8568 -> 0x800A8610
int ShortcutProviderWrapper::NumData() {
    // Local variables
    const class LeaderboardResultList * list; // r31
}

static class Symbol _s; // size: 0x4, address: 0x80A4A3A8
// Range: 0x800A8610 -> 0x800A89C0
class DataNode ShortcutProviderWrapper::Handle(class ShortcutProviderWrapper * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xD4
} __vt__16LeaderboardLocal; // size: 0xD4, address: 0x8087C078
struct {
    // total size: 0x8
} __RTTI__16LeaderboardLocal; // size: 0x8, address: 0x8087C198
struct {
    // total size: 0xD4
} __vt__18LeaderboardFriends; // size: 0xD4, address: 0x8087C1A0
struct {
    // total size: 0x8
} __RTTI__18LeaderboardFriends; // size: 0x8, address: 0x8087C2C0
struct {
    // total size: 0xD4
} __vt__17LeaderboardCached; // size: 0xD4, address: 0x8087C2C8
struct {
    // total size: 0x8
} __RTTI__17LeaderboardCached; // size: 0x8, address: 0x8087C3E0
struct {
    // total size: 0xD0
} __vt__15LeaderboardLive; // size: 0xD0, address: 0x8087C3E8
struct {
    // total size: 0x8
} __RTTI__15LeaderboardLive; // size: 0x8, address: 0x8087C4F8
struct {
    // total size: 0xD0
} __vt__11Leaderboard; // size: 0xD0, address: 0x8087C500
struct {
    // total size: 0x8
} __RTTI__11Leaderboard; // size: 0x8, address: 0x8087C600
struct {
    // total size: 0x9C
} __vt__23ShortcutProviderWrapper; // size: 0x9C, address: 0x8087C608
struct {
    // total size: 0x8
} __RTTI__23ShortcutProviderWrapper; // size: 0x8, address: 0x8087C6E8
struct {
    // total size: 0x9C
} __vt__21ChampShortcutProvider; // size: 0x9C, address: 0x8087C6F0
struct {
    // total size: 0x8
} __RTTI__21ChampShortcutProvider; // size: 0x8, address: 0x8087C7C8
struct {
    // total size: 0x98
} __vt__18ListProviderObject; // size: 0x98, address: 0x8087C7D0
struct {
    // total size: 0x8
} __RTTI__18ListProviderObject; // size: 0x8, address: 0x8087C898
class Friend {
    // total size: 0x20
    class String mName; // offset 0x0, size 0xC
    unsigned long long mFriendKey; // offset 0x10, size 0x8
    class String mUsername; // offset 0x18, size 0x4
};

