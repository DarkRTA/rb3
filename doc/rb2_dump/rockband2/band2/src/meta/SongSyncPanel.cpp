/*
    Compile unit: C:\rockband2\band2\src\meta\SongSyncPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8017BD00 -> 0x8017CD00
*/
class DataArray * types; // size: 0x4, address: 0x80A4CA60
class SongSyncPanel * sInstance; // size: 0x4, address: 0x80A4CA68
// Range: 0x8017BD00 -> 0x8017BDEC
void * SongSyncPanel::SongSyncPanel(class SongSyncPanel * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongSyncPanel * sInstance;
    // -> struct [anonymous] __vt__13SongSyncPanel;
}

// Range: 0x8017BDEC -> 0x8017BEE0
void * SongSyncPanel::~SongSyncPanel(class SongSyncPanel * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongSyncPanel * sInstance;
    // -> struct [anonymous] __vt__13SongSyncPanel;
}

static class Symbol remote_player_left; // size: 0x4, address: 0x80A4CA70
// Range: 0x8017BEE0 -> 0x8017C124
void SongSyncPanel::Load(class SongSyncPanel * const this /* r31 */) {
    // Local variables
    class vector users; // r1+0x1C
    class BandUser * * u; // r28

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Net TheNet;
    // -> const char * gNullStr;
    // -> static class Symbol remote_player_left;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__19ContentLoadingPanel;
    // -> class ObjectDir * sMainDir;
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x8017C124 -> 0x8017C208
void SongSyncPanel::FinishLoad() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__19ContentLoadingPanel;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x8017C208 -> 0x8017C280
void SongSyncPanel::Unload(class SongSyncPanel * const this /* r31 */) {
    // References
    // -> class Net TheNet;
    // -> const char * gNullStr;
}

static class ReadyForSongsMsg ready_msg; // size: 0x4, address: 0x80A4CA78
// Range: 0x8017C280 -> 0x8017C3B0
unsigned char SongSyncPanel::IsLoaded(class SongSyncPanel * const this /* r30 */) {
    // References
    // -> class Net TheNet;
    // -> static class ReadyForSongsMsg ready_msg;
    // -> struct [anonymous] __vt__16ReadyForSongsMsg;
    // -> class SongMgr & TheSongMgr;
    // -> class ContentMgr & TheContentMgr;
}

// Range: 0x8017C3B0 -> 0x8017C3B8
class SongSyncPanel * SongSyncPanel::Instance() {
    // References
    // -> class SongSyncPanel * sInstance;
}

// Range: 0x8017C3B8 -> 0x8017C464
void SongSyncPanel::ReadyForSongs(class SongSyncPanel * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8017C464 -> 0x8017C568
void SongSyncPanel::ProcessedSongs(class SongSyncPanel * const this /* r29 */, const class vector & users /* r30 */) {
    // Local variables
    const int * it; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8017C568 -> 0x8017C5DC
void SongSyncPanel::SyncedSongs(class SongSyncPanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8017C5DC -> 0x8017C704
class DataNode SongSyncPanel::OnMsg(class SongSyncPanel * const this /* r29 */, const class RemotePlayerLeftMsg & msg /* r30 */) {
    // References
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x8017C704 -> 0x8017C784
void SongSyncPanel::CheckForAdvance(class SongSyncPanel * const this /* r31 */) {
    // References
    // -> class SongMgr & TheSongMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8017C784 -> 0x8017C78C
void SongSyncPanel::OnDiskError() {}

static class Symbol _s; // size: 0x4, address: 0x80A4CA80
// Range: 0x8017C78C -> 0x8017CD00
class DataNode SongSyncPanel::Handle(class SongSyncPanel * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__19RemotePlayerLeftMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__13SongSyncPanel; // size: 0xAC, address: 0x80899DB4
struct {
    // total size: 0x8
} __RTTI__13SongSyncPanel; // size: 0x8, address: 0x80899E90

