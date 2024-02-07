/*
    Compile unit: C:\rockband2\band2\src\meta\SongStatusMgr.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8017853C -> 0x80179BB0
*/
// Range: 0x8017853C -> 0x80178554
unsigned char __eq() {}

// Range: 0x80178554 -> 0x80178574
unsigned char HasHigherSongScore() {}

// Range: 0x80178574 -> 0x80178608
class BinStream & __ls(class BinStream & dest /* r30 */, const struct SongStatus & ss /* r31 */) {}

// Range: 0x80178608 -> 0x80178690
class BinStream & __rs(class BinStream & src /* r30 */, struct SongStatus & ss /* r31 */) {
    // Local variables
    int ver; // r1+0x8
}

// Range: 0x80178690 -> 0x801786A8
unsigned char __eq() {}

// Range: 0x801786A8 -> 0x8017877C
class BinStream & __ls(class BinStream & s /* r28 */, const struct SoloSongStatus & ss /* r29 */) {
    // Local variables
    int n; // r30
}

// Range: 0x8017877C -> 0x801787FC
void * SoloSongStatusMgr::SoloSongStatusMgr(class SoloSongStatusMgr * const this /* r29 */, int padNum /* r30 */, const class SongMgr & sm /* r31 */) {
    // References
    // -> struct [anonymous] __vt__17SoloSongStatusMgr;
}

// Range: 0x801787FC -> 0x80178848
void SoloSongStatusMgr::Clear(class SoloSongStatusMgr * const this /* r31 */) {
    // References
    // -> class RockCentralGateway RockCentral;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80178848 -> 0x80178A74
unsigned char SoloSongStatusMgr::UpdateSong(class SoloSongStatusMgr * const this /* r28 */, class Symbol & songName /* r27 */, enum TrackType trackType /* r29 */, enum Difficulty diff /* r30 */, int score /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x24
    struct SoloSongStatus songStatus; // r1+0x28

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<14SoloSongStatus>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> class RockCentralGateway RockCentral;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<14SoloSongStatus>; // size: 0x8, address: 0x80899B00
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80178A74 -> 0x80178B04
int SoloSongStatusMgr::GetScore(const class SoloSongStatusMgr * const this /* r30 */, class Symbol & songName /* r6 */, enum TrackType trackType /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x24
}

// Range: 0x80178B04 -> 0x80178BE0
int SoloSongStatusMgr::GetTotalScore(const class SoloSongStatusMgr * const this /* r27 */, enum TrackType track /* r28 */, unsigned char includeDLC /* r29 */) {
    // Local variables
    int ret; // r30
    struct _List_iterator it; // r1+0x1C
}

// Range: 0x80178BE0 -> 0x80178CE8
void SoloSongStatusMgr::UpdateLeaderboards(class SoloSongStatusMgr * const this /* r28 */) {
    // Local variables
    struct _List_iterator it; // r1+0x14
    int n; // r30
    int userNum; // r29
    int total; // r0

    // References
    // -> class RockCentralGateway RockCentral;
}

// Range: 0x80178CE8 -> 0x80178D40
class BinStream & __ls(class BinStream & s /* r30 */, const class SoloSongStatusMgr & ssm /* r31 */) {}

// Range: 0x80178D40 -> 0x80178D58
unsigned char __eq() {}

// Range: 0x80178D58 -> 0x80178E10
class BinStream & __ls(class BinStream & s /* r30 */, const struct BandSongStatus & ss /* r31 */) {}

// Range: 0x80178E10 -> 0x80178E84
void * BandSongStatusMgr::BandSongStatusMgr(class BandSongStatusMgr * const this /* r30 */, const class SongMgr & sm /* r31 */) {
    // References
    // -> struct [anonymous] __vt__17BandSongStatusMgr;
}

class _List_node : public _List_node_base {
    // total size: 0x1C
public:
    struct BandSongStatus _M_data; // offset 0x8, size 0x14
};
// Range: 0x80178E84 -> 0x80178E94
void BandSongStatusMgr::Init() {}

// Range: 0x80178E94 -> 0x80178F2C
void * BandSongStatusMgr::~BandSongStatusMgr(class BandSongStatusMgr * const this /* r30 */) {
    // References
    // -> class RockCentralGateway RockCentral;
    // -> struct [anonymous] __vt__17BandSongStatusMgr;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80178F2C -> 0x801790C0
unsigned char BandSongStatusMgr::UpdateSong(class BandSongStatusMgr * const this /* r31 */, class Symbol & songName /* r26 */, int stars /* r27 */, int score /* r28 */, int fans /* r29 */) {
    // Local variables
    struct _List_iterator it; // r1+0x20
    unsigned char changed; // r30
    struct BandSongStatus songStatus; // r1+0x24

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<14BandSongStatus>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class RockCentralGateway RockCentral;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<14BandSongStatus>; // size: 0x8, address: 0x80899B98
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801790C0 -> 0x80179138
int BandSongStatusMgr::GetScore(const class BandSongStatusMgr * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x24
}

// Range: 0x80179138 -> 0x80179218
int BandSongStatusMgr::GetTotalScore(const class BandSongStatusMgr * const this /* r28 */, unsigned char includeDLC /* r29 */) {
    // Local variables
    int ret; // r30
    struct _List_iterator it; // r1+0x1C
}

// Range: 0x80179218 -> 0x801792FC
class DataNode BandSongStatusMgr::OnMsg(class BandSongStatusMgr * const this /* r29 */, const class RockCentralOpCompleteMsg & msg /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801792FC -> 0x80179630
void BandSongStatusMgr::GetTopScores(const class BandSongStatusMgr * const this /* r28 */, class vector & songs /* r29 */, int numSongs /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x44

    // References
    // -> const char * gNullStr;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x80179630 -> 0x80179688
class BinStream & __ls(class BinStream & s /* r30 */, const class BandSongStatusMgr & ssm /* r31 */) {}

// Range: 0x80179688 -> 0x801799B4
class DataNode BandSongStatusMgr::Handle(class BandSongStatusMgr * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__24RockCentralOpCompleteMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

// Range: 0x801799B4 -> 0x801799CC
void * HighScoreSongStatusMgr::HighScoreSongStatusMgr() {}

// Range: 0x801799CC -> 0x80179B00
unsigned char HighScoreSongStatusMgr::UpdateSong(class HighScoreSongStatusMgr * const this /* r28 */, class Symbol & songName /* r29 */, int stars /* r30 */, int score /* r31 */) {
    // Local variables
    struct SongStatus * it; // r0
    struct SongStatus songStatus; // r1+0x18

    // References
    // -> const char * gNullStr;
}

// Range: 0x80179B00 -> 0x80179B50
int HighScoreSongStatusMgr::GetScore(const class HighScoreSongStatusMgr * const this /* r31 */) {
    // Local variables
    const struct SongStatus * it; // r0
}

// Range: 0x80179B50 -> 0x80179B80
class BinStream & __ls(class BinStream & dest /* r31 */) {}

// Range: 0x80179B80 -> 0x80179BB0
class BinStream & __rs(class BinStream & src /* r31 */) {}

struct {
    // total size: 0x54
} __vt__17BandSongStatusMgr; // size: 0x54, address: 0x80899BCC
struct {
    // total size: 0x8
} __RTTI__17BandSongStatusMgr; // size: 0x8, address: 0x80899C48
struct {
    // total size: 0x54
} __vt__17SoloSongStatusMgr; // size: 0x54, address: 0x80899C50
struct {
    // total size: 0x8
} __RTTI__17SoloSongStatusMgr; // size: 0x8, address: 0x80899CD0

