/*
    Compile unit: C:\rockband2\band2\src\meta\BotbChallengeLoader.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80202EA0 -> 0x802046F8
*/
class _List_node : public _List_node_base {
    // total size: 0x4C
public:
    class BotbOpenBattleRow _M_data; // offset 0x8, size 0x44
};
class BotbChallengeLoader TheBotbChallengeLoader; // size: 0xC8, address: 0x8097C840
// Range: 0x80202EA0 -> 0x80202F38
void * BotbChallengeLoader::BotbChallengeLoader(class BotbChallengeLoader * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__19BotbChallengeLoader;
}

// Range: 0x80202F38 -> 0x80202F54
void BotbChallengeLoader::Init() {
    // References
    // -> class ObjectDir * sMainDir;
}

static float kChallengeLoaderRetryMs; // size: 0x4, address: 0x80A566A0
// Range: 0x80202F54 -> 0x80203110
void BotbChallengeLoader::CheckLoad(class BotbChallengeLoader * const this /* r31 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Net TheNet;
    // -> static float kChallengeLoaderRetryMs;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class SessionMgr * TheSessionMgr;
    // -> class Tour * TheTour;
}

// Range: 0x80203110 -> 0x80203430
void BotbChallengeLoader::StartLoading(class BotbChallengeLoader * const this /* r30 */) {
    // Local variables
    int i; // r29
    int i; // r29

    // References
    // -> class RockCentralGateway RockCentral;
    // -> class Tour * TheTour;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80203430 -> 0x80203438
unsigned char BotbChallengeLoader::IsLoaded() {}

// Range: 0x80203438 -> 0x80203548
void BotbChallengeLoader::ExtractChallengeEvents(class BotbChallengeLoader * const this /* r31 */, class TourChallenge & tc /* r27 */, class list & names /* r28 */) {
    // Local variables
    int i; // r30
    class TourChallengeEvent * e; // r29

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80203548 -> 0x802036AC
void BotbChallengeLoader::ExtractWorldEvents(class BotbChallengeLoader * const this /* r28 */, class vector & we /* r29 */, class list & names /* r30 */) {
    // Local variables
    int i; // r31
    class TourWorldEvent * e; // r1+0x20

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x802036AC -> 0x802042A4
class DataNode BotbChallengeLoader::OnMsg(class BotbChallengeLoader * const this /* r25 */) {
    // Local variables
    const class list * rlist; // r27
    struct _List_iterator it; // r1+0xF0
    char type; // r26
    char text[255]; // r1+0x124
    const char * city; // r21
    const char * venue; // r23
    class TourWorld & w; // r22
    class TourTown * t; // r22
    class TourVenue * v; // r0
    struct OpenBattleRecord rec; // r1+0x118
    class TourWorldEvent * twe; // r1+0xEC
    class TourChallengeEvent * tce; // r1+0xE8
    int tier; // r0
    unsigned char gotSongs; // r26
    class TourEvent * tce; // r27
    class TourEvent * twe; // r28
    class list templist; // r1+0x110
    struct _List_iterator it; // r1+0xE4
    struct DateTime t; // r1+0x108
    int i; // r21
    int i; // r21

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std32_List_node<18BotbBattleSongInfo>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class RockCentralGateway RockCentral;
    // -> class SongMgr & TheSongMgr;
    // -> class Tour * TheTour;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std32_List_node<18BotbBattleSongInfo>; // size: 0x8, address: 0x808AA6E0
class _List_node : public _List_node_base {
    // total size: 0x2C
public:
    class BotbBattleSongInfo _M_data; // offset 0x8, size 0x24
};
static class Symbol _s; // size: 0x4, address: 0x80A4E69C
// Range: 0x802042A4 -> 0x802046B0
class DataNode BotbChallengeLoader::Handle(class BotbChallengeLoader * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x40
    class DataNode r; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__24RockCentralOpCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x54
} __vt__19BotbChallengeLoader; // size: 0x54, address: 0x808AA748
struct {
    // total size: 0x8
} __RTTI__19BotbChallengeLoader; // size: 0x8, address: 0x808AA7C8
struct {
    // total size: 0x8
} __RTTI__PQ219BotbChallengeLoader16OpenBattleRecord; // size: 0x8, address: 0x808AA848
// Range: 0x802046B0 -> 0x802046F8
static void __sinit_\BotbChallengeLoader_cpp() {
    // References
    // -> class BotbChallengeLoader TheBotbChallengeLoader;
}


