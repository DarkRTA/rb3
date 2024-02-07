/*
    Compile unit: C:\rockband2\band2\src\game\HeadToHeadLeaderboard.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800A419C -> 0x800A419C
*/
class Symbol points; // size: 0x4, address: 0x80A4A2EC
class PlayerLeaderboardData : public LeaderboardData {
    // total size: 0x40
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class LeaderboardResultRow * _M_data; // offset 0x8, size 0x4
};
class RockCentralOpCompleteMsg : public Message {
    // total size: 0x8
};
class LeaderboardData : public Object {
    // total size: 0x40
protected:
    enum DataEnumState mEnumState; // offset 0x28, size 0x4
    class HxGuid mNetBandGuid; // offset 0x2C, size 0x10
    class Symbol units_symbol; // offset 0x3C, size 0x4
};
enum DataEnumState {
    kEnumInactive = 0,
    kEnumWaiting = 1,
    kGetBandProfile = 2,
    kEnumFailure = 3,
    kEnumSuccess = 4,
    kEnumDone = 5,
};
struct {
    // total size: 0x8
} __RTTI__21PlayerLeaderboardData; // size: 0x8, address: 0x8087BD40
struct {
    // total size: 0x8
} __RTTI__15LeaderboardData; // size: 0x8, address: 0x8087BD70

