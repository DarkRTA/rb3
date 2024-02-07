/*
    Compile unit: C:\rockband2\band2\src\meta\Matchmaker.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801025B8 -> 0x80104B80
*/
class Symbol t; // size: 0x4, address: 0x80A4B314
static class Symbol join_result; // size: 0x4, address: 0x80A4B31C
static class Symbol mode_changed; // size: 0x4, address: 0x80A4B324
static class Symbol search_finished; // size: 0x4, address: 0x80A4B32C
// Range: 0x801025B8 -> 0x80102814
void * Matchmaker::Matchmaker(class Matchmaker * const this /* r30 */) {
    // Local variables
    class DataArray * config; // r29

    // References
    // -> class Net TheNet;
    // -> static class Symbol search_finished;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol mode_changed;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class NetSession * TheNetSession;
    // -> static class Symbol join_result;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__10Matchmaker;
}

static class Symbol join_result; // size: 0x4, address: 0x80A4B334
static class Symbol mode_changed; // size: 0x4, address: 0x80A4B33C
static class Symbol search_finished; // size: 0x4, address: 0x80A4B344
// Range: 0x80102814 -> 0x8010295C
void * Matchmaker::~Matchmaker(class Matchmaker * const this /* r30 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> class Net TheNet;
    // -> static class Symbol search_finished;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol mode_changed;
    // -> class NetSession * TheNetSession;
    // -> static class Symbol join_result;
    // -> struct [anonymous] __vt__10Matchmaker;
}

// Range: 0x8010295C -> 0x80102B54
void Matchmaker::Poll(class Matchmaker * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class Net TheNet;
    // -> class NetSession * TheNetSession;
}

// Range: 0x80102B54 -> 0x80102C9C
void Matchmaker::FindPlayers(class Matchmaker * const this /* r28 */, unsigned char forceLeader /* r29 */, unsigned char forceNonLeader /* r30 */) {
    // References
    // -> class NetSession * TheNetSession;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80102C9C -> 0x80102D98
class DataNode Matchmaker::OnFindPlayers(class Matchmaker * const this /* r29 */, class DataArray * a /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80102D98 -> 0x80102DC8
unsigned char Matchmaker::IsFinding() {
    // References
    // -> class NetSession * TheNetSession;
}

// Range: 0x80102DC8 -> 0x80102E8C
void Matchmaker::CancelFind(class Matchmaker * const this /* r31 */) {
    // References
    // -> class Net TheNet;
    // -> class NetSession * TheNetSession;
}

// Range: 0x80102E8C -> 0x80102E94
void Matchmaker::SetChannel() {}

class NetSearchResult : public Object {
    // total size: 0x40
protected:
    class SessionData * mSessionData; // offset 0x28, size 0x4
    class MatchmakingSettings * mSettings; // offset 0x2C, size 0x4
    int mNumOpenSlots; // offset 0x30, size 0x4
    class String mHostName; // offset 0x34, size 0xC
};
// Range: 0x80102E94 -> 0x80103000
class DataNode Matchmaker::OnSearchFinished(class Matchmaker * const this /* r30 */) {
    // Local variables
    class NetSearchResult * nextResult; // r4
    float waitTime; // f31

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class Net TheNet;
    // -> class NetSession * TheNetSession;
}

// Range: 0x80103000 -> 0x80103130
class DataNode Matchmaker::OnMsg(class Matchmaker * const this /* r29 */, const class JoinResultMsg & msg /* r30 */) {
    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> class BandUI * TheBandUI;
}

// Range: 0x80103130 -> 0x80103200
class DataNode Matchmaker::OnMsg(class Matchmaker * const this /* r30 */) {
    // References
    // -> class GameConfig * TheGameConfig;
    // -> class GameMode * TheGameMode;
    // -> class NetSession * TheNetSession;
}

// Range: 0x80103200 -> 0x801032C4
void Matchmaker::UpdateMatchmakingSettings(class Matchmaker * const this /* r30 */) {
    // References
    // -> class GameConfig * TheGameConfig;
    // -> class GameMode * TheGameMode;
    // -> class NetSession * TheNetSession;
}

class SearchSettings : public MatchmakingSettings {
    // total size: 0x2C
    int mQueryID; // offset 0x28, size 0x4
};
// Range: 0x801032C4 -> 0x80103410
void Matchmaker::StartSearch(class Matchmaker * const this /* r29 */) {
    // Local variables
    int queryID; // r30
    class SearchSettings settings; // r1+0x10

    // References
    // -> class NetSession * TheNetSession;
    // -> class Net TheNet;
    // -> class Tour * TheTour;
    // -> class GameConfig * TheGameConfig;
}

static class Symbol difficulty; // size: 0x4, address: 0x80A4B34C
static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B354
static class Symbol is_tour; // size: 0x4, address: 0x80A4B35C
// Range: 0x801034D4 -> 0x80103A14
void Matchmaker::AddCustomSettings(class Matchmaker * const this /* r24 */, class MatchmakingSettings * settings /* r29 */, unsigned char searching /* r30 */) {
    // Local variables
    class Symbol diff; // r1+0x18
    int needDrummer; // r27
    int needVocalist; // r26
    int needGuitarist; // r25
    int increment; // r28
    enum ControllerType instrument; // r0
    int n; // r24
    enum ControllerType instrument; // r0
    const class HxGuid * guid; // r31
    class HxGuid nullGuid; // r1+0x20
    unsigned char addGuid; // r24
    enum TourMode tMode; // r0
    class TourBand * band; // r25

    // References
    // -> const char * kAssertStr;
    // -> class Tour * TheTour;
    // -> static class Symbol is_tour;
    // -> class NetSession * TheNetSession;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol is_h2h_arrangement;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> class ObjectDir * sMainDir;
    // -> static class Symbol difficulty;
}

static class Symbol online_mode; // size: 0x4, address: 0x80A4B364
static class Symbol is_h2h_arrangement; // size: 0x4, address: 0x80A4B36C
static class Symbol separate_parts; // size: 0x4, address: 0x80A4B374
// Range: 0x80103A14 -> 0x80103C30
int Matchmaker::CurrentModeFilter() {
    // Local variables
    int mode; // r0
    unsigned char pro; // r0
    enum TrackType trackType; // r0

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> static class Symbol separate_parts;
    // -> class GameConfig * TheGameConfig;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol is_h2h_arrangement;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol online_mode;
}

static class Message matchmaker_update; // size: 0x8, address: 0x80978C90
// Range: 0x80103C30 -> 0x80103E28
void Matchmaker::UpdateUI() {
    // References
    // -> static class Message matchmaker_update;
    // -> struct [anonymous] __vt__7Message;
    // -> struct [anonymous] __RTTI__8UIScreen;
    // -> class UIManager TheUI;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__17MatchmakingScreen;
    // -> class ObjectDir * sMainDir;
}

static class Symbol _s; // size: 0x4, address: 0x80A4B37C
static class Symbol _s; // size: 0x4, address: 0x80A4B384
static class Symbol _s; // size: 0x4, address: 0x80A4B38C
static class Symbol _s; // size: 0x4, address: 0x80A4B394
static class Symbol _s; // size: 0x4, address: 0x80A4B39C
static class Symbol _s; // size: 0x4, address: 0x80A4B3A4
// Range: 0x80103E28 -> 0x80104A18
class DataNode Matchmaker::Handle(class Matchmaker * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x48
    class MessageTimer _mt; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode _n; // r1+0x68

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__14ModeChangedMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__13JoinResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
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

static class Symbol _s; // size: 0x4, address: 0x80A4B3AC
// Range: 0x80104A18 -> 0x80104B80
unsigned char Matchmaker::SyncProperty(class Matchmaker * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8
} __RTTI__17MatchmakingScreen; // size: 0x8, address: 0x8088A618
struct {
    // total size: 0xC
} __vt__13JoinResultMsg; // size: 0xC, address: 0x8088A6C0
struct {
    // total size: 0x8
} __RTTI__13JoinResultMsg; // size: 0x8, address: 0x8088A6E8
struct {
    // total size: 0x54
} __vt__10Matchmaker; // size: 0x54, address: 0x8088A738
struct {
    // total size: 0x8
} __RTTI__10Matchmaker; // size: 0x8, address: 0x8088A7B0

