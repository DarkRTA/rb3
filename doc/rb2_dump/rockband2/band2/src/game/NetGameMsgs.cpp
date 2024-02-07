/*
    Compile unit: C:\rockband2\band2\src\game\NetGameMsgs.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8007BD4C -> 0x8007E028
*/
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>; // size: 0x8, address: 0x80878648
// Range: 0x8007BD4C -> 0x8007BDF8
void PlayerGameplayMsg::Save(const class PlayerGameplayMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8007BDF8 -> 0x8007BE8C
void PlayerGameplayMsg::Load(class PlayerGameplayMsg * const this /* r30 */, class BinStream & src /* r31 */) {
    // Local variables
    unsigned char playerNum; // r1+0x9
    unsigned char opCode; // r1+0x8
}

static class Symbol incoming_msg; // size: 0x4, address: 0x80A49DBC
static class Message gameplayMsg; // size: 0x8, address: 0x80977770
// Range: 0x8007BE8C -> 0x8007C418
void PlayerGameplayMsg::Dispatch(class PlayerGameplayMsg * const this /* r30 */) {
    // References
    // -> const char * kAssertStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> class ObjectDir * sMainDir;
    // -> static class Message gameplayMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol incoming_msg;
}

static class DataArrayPtr restart; // size: 0x8, address: 0x80977788
// Range: 0x8007C418 -> 0x8007C538
void RestartGameMsg::Dispatch() {
    // References
    // -> static class DataArrayPtr restart;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x8007C538 -> 0x8007C548
void LoadAllCharsMsg::Dispatch() {
    // References
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x8007C548 -> 0x8007C5B0
void * PlayerStatsMsg::PlayerStatsMsg(unsigned char strummedUp /* r30 */, int deployCount /* r31 */, int score /* r12 */, int soloPercentage /* r0 */) {
    // References
    // -> struct [anonymous] __vt__14PlayerStatsMsg;
}

// Range: 0x8007C5B0 -> 0x8007C704
void PlayerStatsMsg::Save(const class PlayerStatsMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8007C704 -> 0x8007C834
void PlayerStatsMsg::Load(class PlayerStatsMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

// Range: 0x8007C834 -> 0x8007C8A4
void PlayerStatsMsg::Dispatch(class PlayerStatsMsg * const this /* r31 */) {
    // References
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x8007C8A4 -> 0x8007C8F0
void * SetPlayerTrackTypeMsg::SetPlayerTrackTypeMsg(class SetPlayerTrackTypeMsg * const this /* r31 */, int playerNum /* r0 */) {
    // References
    // -> struct [anonymous] __vt__21SetPlayerTrackTypeMsg;
}

// Range: 0x8007C8F0 -> 0x8007C948
void SetPlayerTrackTypeMsg::Save(const class SetPlayerTrackTypeMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8007C948 -> 0x8007C998
void SetPlayerTrackTypeMsg::Load(class SetPlayerTrackTypeMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

// Range: 0x8007C998 -> 0x8007CA28
void SetPlayerTrackTypeMsg::Dispatch(class SetPlayerTrackTypeMsg * const this /* r31 */) {
    // Local variables
    class Symbol type; // r1+0xC

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x8007CA28 -> 0x8007CA74
void * SetPlayerDifficultyMsg::SetPlayerDifficultyMsg(class SetPlayerDifficultyMsg * const this /* r31 */, int playerNum /* r0 */) {
    // References
    // -> struct [anonymous] __vt__22SetPlayerDifficultyMsg;
}

// Range: 0x8007CA74 -> 0x8007CACC
void SetPlayerDifficultyMsg::Save(const class SetPlayerDifficultyMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8007CACC -> 0x8007CB1C
void SetPlayerDifficultyMsg::Load(class SetPlayerDifficultyMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

// Range: 0x8007CB1C -> 0x8007CBAC
void SetPlayerDifficultyMsg::Dispatch(class SetPlayerDifficultyMsg * const this /* r31 */) {
    // Local variables
    class Symbol diff; // r1+0xC

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x8007CBAC -> 0x8007CBC4
void * ReassignPlayerTrackTypeMsg::ReassignPlayerTrackTypeMsg() {
    // References
    // -> struct [anonymous] __vt__26ReassignPlayerTrackTypeMsg;
}

// Range: 0x8007CBC4 -> 0x8007CC28
void ReassignPlayerTrackTypeMsg::Save(const class ReassignPlayerTrackTypeMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8007CC28 -> 0x8007CC7C
void ReassignPlayerTrackTypeMsg::Load(class ReassignPlayerTrackTypeMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

// Range: 0x8007CC7C -> 0x8007CCCC
void ReassignPlayerTrackTypeMsg::Dispatch(class ReassignPlayerTrackTypeMsg * const this /* r31 */) {
    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameConfig * TheGameConfig;
}

static class DataArrayPtr setTrackTypes; // size: 0x8, address: 0x809777A0
// Range: 0x8007CCCC -> 0x8007CDEC
void H2HSetTrackTypesMsg::Dispatch() {
    // References
    // -> static class DataArrayPtr setTrackTypes;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x8007CDEC -> 0x8007CE10
void ReadyForSongsMsg::Dispatch() {}

// Range: 0x8007CE10 -> 0x8007D004
void * LocalSongsMsg::LocalSongsMsg(class LocalSongsMsg * const this /* r27 */, class vector & localPlayers /* r28 */, class vector & songNames /* r29 */) {
    // Local variables
    int n; // r30
    int n; // r26

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__13LocalSongsMsg;
}

// Range: 0x8007D004 -> 0x8007D214
void LocalSongsMsg::Save(const class LocalSongsMsg * const this /* r29 */, class BinStream & dest /* r30 */) {
    // Local variables
    class MemStream s; // r1+0x20
    int n; // r28
    int n; // r27
    int compressed; // r1+0x1C

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8007D214 -> 0x8007D500
void LocalSongsMsg::Load(class LocalSongsMsg * const this /* r29 */, class BinStream & src /* r27 */) {
    // Local variables
    class MemStream s; // r1+0x38
    int uncompressed; // r1+0x34
    int compressed; // r1+0x30
    void * r; // r30
    unsigned char numPlayers; // r1+0x21
    int n; // r28
    unsigned char playerNum; // r1+0x20
    int numSongs; // r1+0x2C
    int n; // r28
    class Symbol songName; // r1+0x28

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
}

// Range: 0x8007D500 -> 0x8007D540
void LocalSongsMsg::Dispatch(class LocalSongsMsg * const this /* r31 */) {
    // References
    // -> class SongMgr & TheSongMgr;
}

// Range: 0x8007D540 -> 0x8007D58C
void * SharedSongsMsg::SharedSongsMsg(class SharedSongsMsg * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14SharedSongsMsg;
}

// Range: 0x8007D58C -> 0x8007D668
void SharedSongsMsg::Save(const class SharedSongsMsg * const this /* r31 */, class BinStream & dest /* r30 */) {
    // Local variables
    class MemStream s; // r1+0x18
    int compressed; // r1+0x14
}

static class Symbol lost_connection; // size: 0x4, address: 0x80A49DC4
static class Message init; // size: 0x8, address: 0x809777B8
// Range: 0x8007D668 -> 0x8007DA04
void SharedSongsMsg::Load(class SharedSongsMsg * const this /* r28 */, class BinStream & src /* r29 */) {
    // Local variables
    class MemStream s; // r1+0x38
    int uncompressed; // r1+0x24
    int compressed; // r1+0x20
    void * r; // r30
    int n; // r29

    // References
    // -> class BandUI * TheBandUI;
    // -> static class Message init;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol lost_connection;
    // -> class Debug TheDebug;
}

// Range: 0x8007DA04 -> 0x8007DA38
void SharedSongsMsg::Dispatch(class SharedSongsMsg * const this /* r4 */) {
    // References
    // -> class SongMgr & TheSongMgr;
}

// Range: 0x8007DA38 -> 0x8007DCC0
void * LocalBattlesMsg::LocalBattlesMsg(class LocalBattlesMsg * const this /* r28 */, const class vector & local_players /* r29 */, const class list & challenge_battles /* r30 */, const class list & world_battles /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__Pi;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__15LocalBattlesMsg;
}

// Range: 0x8007DCC0 -> 0x8007DD04
void LocalBattlesMsg::Save(const class LocalBattlesMsg * const this /* r31 */) {}

// Range: 0x8007DD04 -> 0x8007DD48
void LocalBattlesMsg::Load(class LocalBattlesMsg * const this /* r31 */) {}

// Range: 0x8007DD48 -> 0x8007DDB8
void LocalBattlesMsg::Dispatch(class LocalBattlesMsg * const this /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Tour * TheTour;
}

// Range: 0x8007DDB8 -> 0x8007DF9C
void * SharedBattlesMsg::SharedBattlesMsg(class SharedBattlesMsg * const this /* r30 */, const class list & challenge_battles /* r28 */, const class list & world_battles /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__16SharedBattlesMsg;
}

// Range: 0x8007DF9C -> 0x8007DFD8
void SharedBattlesMsg::Save(const class SharedBattlesMsg * const this /* r31 */) {}

// Range: 0x8007DFD8 -> 0x8007E014
void SharedBattlesMsg::Load(class SharedBattlesMsg * const this /* r31 */) {}

// Range: 0x8007E014 -> 0x8007E028
void SharedBattlesMsg::Dispatch(class SharedBattlesMsg * const this /* r5 */) {
    // References
    // -> class Tour * TheTour;
}

struct {
    // total size: 0x28
} __vt__16SharedBattlesMsg; // size: 0x28, address: 0x80878960
struct {
    // total size: 0x8
} __RTTI__16SharedBattlesMsg; // size: 0x8, address: 0x808789A8
struct {
    // total size: 0x28
} __vt__15LocalBattlesMsg; // size: 0x28, address: 0x808789B0
struct {
    // total size: 0x8
} __RTTI__15LocalBattlesMsg; // size: 0x8, address: 0x808789F8
struct {
    // total size: 0x28
} __vt__14SharedSongsMsg; // size: 0x28, address: 0x80878A00
struct {
    // total size: 0x8
} __RTTI__14SharedSongsMsg; // size: 0x8, address: 0x80878A48
struct {
    // total size: 0x28
} __vt__13LocalSongsMsg; // size: 0x28, address: 0x80878A50
struct {
    // total size: 0x8
} __RTTI__13LocalSongsMsg; // size: 0x8, address: 0x80878A98
struct {
    // total size: 0x28
} __vt__16ReadyForSongsMsg; // size: 0x28, address: 0x80878AA0
struct {
    // total size: 0x8
} __RTTI__16ReadyForSongsMsg; // size: 0x8, address: 0x80878AE8
struct {
    // total size: 0x28
} __vt__19H2HSetTrackTypesMsg; // size: 0x28, address: 0x80878AF0
struct {
    // total size: 0x8
} __RTTI__19H2HSetTrackTypesMsg; // size: 0x8, address: 0x80878B38
struct {
    // total size: 0x28
} __vt__26ReassignPlayerTrackTypeMsg; // size: 0x28, address: 0x80878B40
struct {
    // total size: 0x8
} __RTTI__26ReassignPlayerTrackTypeMsg; // size: 0x8, address: 0x80878B90
struct {
    // total size: 0x28
} __vt__22SetPlayerDifficultyMsg; // size: 0x28, address: 0x80878B98
struct {
    // total size: 0x8
} __RTTI__22SetPlayerDifficultyMsg; // size: 0x8, address: 0x80878BE8
struct {
    // total size: 0x28
} __vt__21SetPlayerTrackTypeMsg; // size: 0x28, address: 0x80878BF0
struct {
    // total size: 0x8
} __RTTI__21SetPlayerTrackTypeMsg; // size: 0x8, address: 0x80878C40
struct {
    // total size: 0x28
} __vt__14PlayerStatsMsg; // size: 0x28, address: 0x80878C48
struct {
    // total size: 0x8
} __RTTI__14PlayerStatsMsg; // size: 0x8, address: 0x80878C90
struct {
    // total size: 0x28
} __vt__15LoadAllCharsMsg; // size: 0x28, address: 0x80878C98
struct {
    // total size: 0x8
} __RTTI__15LoadAllCharsMsg; // size: 0x8, address: 0x80878CE0
struct {
    // total size: 0x28
} __vt__14RestartGameMsg; // size: 0x28, address: 0x80878CE8
struct {
    // total size: 0x8
} __RTTI__14RestartGameMsg; // size: 0x8, address: 0x80878D30
struct {
    // total size: 0x28
} __vt__17PlayerGameplayMsg; // size: 0x28, address: 0x80878D38
struct {
    // total size: 0x8
} __RTTI__17PlayerGameplayMsg; // size: 0x8, address: 0x80878D80
struct {
    // total size: 0x8
} __RTTI__P6Symbol; // size: 0x8, address: 0x80878E00
struct {
    // total size: 0x8
} __RTTI__Pc; // size: 0x8, address: 0x80878E10
struct _OKToMemCpy {
    // total size: 0x1
};

