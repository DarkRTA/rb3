/*
    Compile unit: C:\rockband2\system\src\bandobj\TrackPanelDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802BE710 -> 0x802C22AC
*/
class DataArray * types; // size: 0x4, address: 0x80A50330
// Range: 0x802BE710 -> 0x802BE9F0
void * TrackPanelDir::TrackPanelDir(class TrackPanelDir * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__31ObjPtr<10Scoreboard,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11EndingBonus,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndDir,9ObjectDir>;
    // -> struct [anonymous] __vt__35ObjPtr<14BandCrowdMeter,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtr<11GemTrackDir,9ObjectDir>;
    // -> struct [anonymous] __vt__34ObjPtr<13VocalTrackDir,9ObjectDir>;
    // -> struct [anonymous] __vt__13TrackPanelDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x802BE9F0 -> 0x802BEA9C
void TrackPanelDir::PostLoad(class TrackPanelDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class list sRevs;
}

// Range: 0x802BEA9C -> 0x802BEB1C
void TrackPanelDir::Copy(class TrackPanelDir * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class TrackPanelDir * p; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13TrackPanelDir;
}

static unsigned char cacheDefaultStreakOffsets; // size: 0x1, address: 0x80A46C00
static float defDrumStreakOffset; // size: 0x4, address: 0x80A50338
static float defGuitarStreakOffset; // size: 0x4, address: 0x80A5033C
// Range: 0x802BEB1C -> 0x802BF4EC
void TrackPanelDir::ConfigureTracks(class TrackPanelDir * const this /* r28 */) {
    // Local variables
    class Object * gamemode; // r29
    class vector trackOrder; // r1+0x5C
    int ii; // r27
    class GemTrackDir * dir; // r5
    int ii; // r26
    class GemTrackDir * trackDir; // r0
    class RndCam * cam; // r26
    const char * aspect; // r26
    const char * configName; // r0
    float HUDToTopFrame; // f31

    // References
    // -> class Rnd & TheRnd;
    // -> static float defGuitarStreakOffset;
    // -> static float defDrumStreakOffset;
    // -> static unsigned char cacheDefaultStreakOffsets;
    // -> struct [anonymous] __RTTI__9BandTrack;
    // -> struct [anonymous] __RTTI__11GemTrackDir;
}

static class Symbol output_texture; // size: 0x4, address: 0x80A50344
// Range: 0x802BF4EC -> 0x802BF71C
void TrackPanelDir::SetBotbBandIcon(class ObjectDir * target /* r28 */, class String & source /* r27 */) {
    // Local variables
    class FilePath target_path; // r1+0x14

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol output_texture;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Debug TheDebug;
}

static class Symbol stars; // size: 0x4, address: 0x80A5034C
static class Symbol streak; // size: 0x4, address: 0x80A50354
// Range: 0x802BF71C -> 0x802BFBAC
void TrackPanelDir::SetupApplauseMeter(class TrackPanelDir * const this /* r27 */, int endScore /* r28 */, const char * thisBandName /* r21 */, const char * otherBandName /* r22 */, class String & thisBandIcon /* r23 */, class String & rivalBandIcon /* r24 */, unsigned char show_applause_meter /* r29 */, class Symbol & metric /* r30 */) {
    // References
    // -> static class Symbol streak;
    // -> static class Symbol stars;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9BandLabel;
}

static class Symbol max_diff; // size: 0x4, address: 0x80A5035C
static class Symbol tie_window; // size: 0x4, address: 0x80A50364
// Range: 0x802BFBAC -> 0x802BFCEC
void TrackPanelDir::SetApplauseMeterScale(class TrackPanelDir * const this /* r31 */, int scale /* r30 */) {
    // References
    // -> static class Symbol tie_window;
    // -> static class Symbol max_diff;
}

// Range: 0x802BFCEC -> 0x802BFE88
void TrackPanelDir::FadeBotbBandNames(class TrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

static class Object * gameMode; // size: 0x4, address: 0x80A50368
// Range: 0x802BFE88 -> 0x802BFFDC
void TrackPanelDir::DisablePlayer(class TrackPanelDir * const this /* r28 */, class Symbol & instrument /* r29 */, unsigned char disconnectedAtStart /* r31 */) {
    // Local variables
    enum TrackInstrument ti; // r30

    // References
    // -> static class Object * gameMode;
}

static class Object * gameMode; // size: 0x4, address: 0x80A50370
// Range: 0x802BFFDC -> 0x802C00B8
void TrackPanelDir::EnablePlayer(class TrackPanelDir * const this /* r30 */) {
    // Local variables
    enum TrackInstrument ti; // r31

    // References
    // -> static class Object * gameMode;
}

// Range: 0x802C00B8 -> 0x802C0170
class BandTrack * TrackPanelDir::GetTrack() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x802C0170 -> 0x802C01C0
void TrackPanelDir::Enter(class TrackPanelDir * const this /* r31 */) {}

static class Message reset; // size: 0x8, address: 0x8097DA78
// Range: 0x802C01C0 -> 0x802C08A8
void TrackPanelDir::Reset(class TrackPanelDir * const this /* r29 */) {
    // Local variables
    unsigned char showApplauseMeter; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class LoadMgr TheLoadMgr;
    // -> static class Message reset;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x802C08A8 -> 0x802C0A1C
void TrackPanelDir::ResetAll(class TrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802C0A1C -> 0x802C0A34
void TrackPanelDir::ResetPlayers() {}

// Range: 0x802C0A34 -> 0x802C0B98
void TrackPanelDir::PlayIntro(class TrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

static class Symbol last_multiplier; // size: 0x4, address: 0x80A50378
static class Message set_multiplier; // size: 0x8, address: 0x8097DA90
// Range: 0x802C0B98 -> 0x802C0EB4
void TrackPanelDir::SetMultiplier(class TrackPanelDir * const this /* r30 */, int val /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message set_multiplier;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Symbol last_multiplier;
}

// Range: 0x802C0EB4 -> 0x802C0F3C
void TrackPanelDir::GameOver(class TrackPanelDir * const this /* r31 */) {}

// Range: 0x802C0F3C -> 0x802C1098
void TrackPanelDir::GameWon(class TrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802C1098 -> 0x802C11F0
void TrackPanelDir::StartFinale(class TrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802C11F0 -> 0x802C1398
void TrackPanelDir::GameLost(class TrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802C1398 -> 0x802C13A0
void TrackPanelDir::SetCrowdRating() {}

// Range: 0x802C13A0 -> 0x802C1564
void TrackPanelDir::Coda(class TrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x802C1564 -> 0x802C1594
void TrackPanelDir::CodaEnd() {}

// Range: 0x802C1594 -> 0x802C15C4
void TrackPanelDir::SetCodaScore() {}

// Range: 0x802C15C4 -> 0x802C16A8
void TrackPanelDir::CodaSuccess(class TrackPanelDir * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x802C16A8 -> 0x802C16DC
void TrackPanelDir::SoloEnd() {}

// Range: 0x802C16DC -> 0x802C16E4
void TrackPanelDir::UnisonStart() {}

// Range: 0x802C16E4 -> 0x802C16EC
void TrackPanelDir::UnisonEnd() {}

// Range: 0x802C16EC -> 0x802C16F4
void TrackPanelDir::UnisonSucceed() {}

static class Symbol _s; // size: 0x4, address: 0x80A50380
static class Symbol _s; // size: 0x4, address: 0x80A50388
static class Symbol _s; // size: 0x4, address: 0x80A50390
static class Symbol _s; // size: 0x4, address: 0x80A50398
// Range: 0x802C16F4 -> 0x802C1D58
class DataNode TrackPanelDir::Handle(class TrackPanelDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A503A0
static class Symbol _s; // size: 0x4, address: 0x80A503A8
static class Symbol _s; // size: 0x4, address: 0x80A503B0
static class Symbol _s; // size: 0x4, address: 0x80A503B8
static class Symbol _s; // size: 0x4, address: 0x80A503C0
// Range: 0x802C1D58 -> 0x802C22AC
unsigned char TrackPanelDir::SyncProperty(class TrackPanelDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x2A0
} __vt__13TrackPanelDir; // size: 0x2A0, address: 0x808C5C88
struct {
    // total size: 0x8
} __RTTI__13TrackPanelDir; // size: 0x8, address: 0x808C5FA0
struct {
    // total size: 0x18
} __vt__31ObjPtr<10Scoreboard,9ObjectDir>; // size: 0x18, address: 0x808C5FA8
struct {
    // total size: 0x8
} __RTTI__31ObjPtr<10Scoreboard,9ObjectDir>; // size: 0x8, address: 0x808C5FF0
struct {
    // total size: 0x18
} __vt__32ObjPtr<11EndingBonus,9ObjectDir>; // size: 0x18, address: 0x808C5FF8
struct {
    // total size: 0x8
} __RTTI__32ObjPtr<11EndingBonus,9ObjectDir>; // size: 0x8, address: 0x808C6040
struct {
    // total size: 0x18
} __vt__35ObjPtr<14BandCrowdMeter,9ObjectDir>; // size: 0x18, address: 0x808C6048
struct {
    // total size: 0x8
} __RTTI__35ObjPtr<14BandCrowdMeter,9ObjectDir>; // size: 0x8, address: 0x808C6090
struct {
    // total size: 0x8
} __RTTI__P32ObjPtr<11GemTrackDir,9ObjectDir>; // size: 0x8, address: 0x808C6BD0

