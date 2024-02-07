/*
    Compile unit: C:\rockband2\band2\src\game\LeaderboardData.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800A8BC0 -> 0x800A8E1C
*/
class Symbol t; // size: 0x4, address: 0x80A4A3B4
// Range: 0x800A8BC0 -> 0x800A8C14
void * LeaderboardData::LeaderboardData(class LeaderboardData * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__15LeaderboardData;
}

// Range: 0x800A8C14 -> 0x800A8C8C
void * LeaderboardData::~LeaderboardData(class LeaderboardData * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__15LeaderboardData;
}

// Range: 0x800A8C8C -> 0x800A8CCC
void LeaderboardData::CleanUp(class LeaderboardData * const this /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x800A8CCC -> 0x800A8DE8
int LeaderboardData::GetRowIxFromRank(int rank /* r1+0x8 */) {
    // Local variables
    const class list * ShortcutRows; // r0
    struct _List_iterator it; // r1+0x58
    int ix; // r3
    struct _List_iterator comp_it; // r1+0x54
}

// Range: 0x800A8DE8 -> 0x800A8E14
class Symbol PlayerLeaderboardData::OnSelectRow() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x800A8E14 -> 0x800A8E1C
unsigned char PlayerLeaderboardData::CanRowsBeSelected() {}

struct {
    // total size: 0x7C
} __vt__21PlayerLeaderboardData; // size: 0x7C, address: 0x8087C9AC
struct {
    // total size: 0x7C
} __vt__15LeaderboardData; // size: 0x7C, address: 0x8087CA28
struct {
    // total size: 0xC
} __vt__24RockCentralOpCompleteMsg; // size: 0xC, address: 0x8087CAA4
struct {
    // total size: 0x8
} __RTTI__24RockCentralOpCompleteMsg; // size: 0x8, address: 0x8087CAD8

