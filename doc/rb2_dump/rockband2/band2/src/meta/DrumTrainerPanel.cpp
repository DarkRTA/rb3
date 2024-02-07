/*
    Compile unit: C:\rockband2\band2\src\meta\DrumTrainerPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800E445C -> 0x800E88F8
*/
class DataArray * types; // size: 0x4, address: 0x80A4AEB8
class Symbol name; // size: 0x4, address: 0x80A4AEC0
class DrumTrainerPanel * TheDrumTrainerPanel; // size: 0x4, address: 0x80A4AEC4
// Range: 0x800E445C -> 0x800E4570
void * DrumTrainerPanel::DrumTrainerPanel(class DrumTrainerPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__16DrumTrainerPanel;
}

// Range: 0x800E4570 -> 0x800E4704
void * DrumTrainerPanel::~DrumTrainerPanel(class DrumTrainerPanel * const this /* r30 */) {}

// Range: 0x800E4704 -> 0x800E4F70
void DrumTrainerPanel::Enter(class DrumTrainerPanel * const this /* r30 */) {
    // Local variables
    class vector list; // r1+0xC
    int i; // r27
    class BandUser * user; // r28

    // References
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class TaskMgr TheTaskMgr;
    // -> struct [anonymous] __RTTI__8FillInfo;
    // -> struct [anonymous] __RTTI__12DrumFillInfo;
    // -> class SongDB * TheSongDB;
    // -> struct [anonymous] __RTTI__5Track;
    // -> struct [anonymous] __RTTI__8GemTrack;
    // -> struct [anonymous] __RTTI__6Player;
    // -> struct [anonymous] __RTTI__9GemPlayer;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8TempoMap;
    // -> struct [anonymous] __RTTI__18MultiTempoTempoMap;
    // -> class TempoMap * TheTempoMap;
    // -> class DrumTrainerPanel * TheDrumTrainerPanel;
}

// Range: 0x800E4F70 -> 0x800E5140
void DrumTrainerPanel::Exit(class DrumTrainerPanel * const this /* r31 */) {
    // References
    // -> class DrumTrainerPanel * TheDrumTrainerPanel;
}

// Range: 0x800E5140 -> 0x800E5334
void DrumTrainerPanel::Draw(class DrumTrainerPanel * const this /* r31 */) {
    // Local variables
    class GameplayOptions * options; // r0
    unsigned char lefty; // r0
    const struct TabData * it; // r29
    const struct TabData * it; // r29
    float slot; // f31
}

static class Message change_bpm; // size: 0x8, address: 0x80978AE8
// Range: 0x800E5334 -> 0x800E5AAC
void DrumTrainerPanel::Poll(class DrumTrainerPanel * const this /* r26 */) {
    // Local variables
    int tick; // r29
    struct MBT mbt; // r1+0x80
    float ms; // f0
    int jumpOffset; // r24
    class Message msg; // r1+0x78
    int beatsPerMeasure; // r0
    class Message msg; // r1+0x70
    int bottomTick; // r0
    class GemTrackDir * gemTrackDir; // r28
    class FillInfo * fillInfo; // r0
    const class vector & vec; // r0
    unsigned long i; // r27
    class Symbol crashSymbol; // r1+0x20

    // References
    // -> struct [anonymous] __RTTI__8TrackDir;
    // -> struct [anonymous] __RTTI__11GemTrackDir;
    // -> static class Message change_bpm;
    // -> struct [anonymous] __vt__7Message;
    // -> class SongDB * TheSongDB;
}

static class Message sMsg; // size: 0x8, address: 0x80978B00
// Range: 0x800E5AAC -> 0x800E5C2C
void DrumTrainerPanel::UpdateScore(class DrumTrainerPanel * const this /* r31 */) {
    // References
    // -> static class Message sMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800E5C2C -> 0x800E5E18
void DrumTrainerPanel::AddBeatMask(class DrumTrainerPanel * const this /* r26 */, int tick /* r27 */, int index /* r28 */) {
    // Local variables
    float startTime; // f31
    float duration; // f30
    class Transform xform; // r1+0x10

    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11TrackWidget;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E5E18 -> 0x800E5E34
int DrumTrainerPanel::GetBeatLengthTick() {}

// Range: 0x800E5E34 -> 0x800E5ED0
class DataNode DrumTrainerPanel::OnSetDrumKit(class DrumTrainerPanel * const this /* r30 */, class DataArray * msg /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E5ED0 -> 0x800E5F4C
int DrumTrainerPanel::SlotToSample() {
    // Local variables
    int sample; // r4
}

// Range: 0x800E5F4C -> 0x800E6108
void DrumTrainerPanel::EncounterGem(class DrumTrainerPanel * const this /* r27 */, int gem_id /* r28 */) {
    // Local variables
    unsigned char last_gem; // r30
    const class GameGemList & gems; // r0
    int id; // r29
    int loopTicks; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongDB * TheSongDB;
}

// Range: 0x800E6108 -> 0x800E6158
int DrumTrainerPanel::LoopJumpTick(class DrumTrainerPanel * const this /* r31 */) {
    // Local variables
    int beatLength; // r0
    int numPatterns; // r0
}

// Range: 0x800E6158 -> 0x800E61C0
unsigned char DrumTrainerPanel::GetCanFreestyle(const class DrumTrainerPanel * const this /* r31 */) {}

// Range: 0x800E61C0 -> 0x800E61C8
void DrumTrainerPanel::SetMetronome() {}

// Range: 0x800E61C8 -> 0x800E61D0
unsigned char DrumTrainerPanel::GetMetronome() {}

// Range: 0x800E61D0 -> 0x800E61F4
int DrumTrainerPanel::GetTick() {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x800E61F4 -> 0x800E61FC
class GemTrack * DrumTrainerPanel::GetTrack() {}

static class Message force_fill; // size: 0x8, address: 0x80978B18
// Range: 0x800E61FC -> 0x800E651C
void DrumTrainerPanel::JumpToTick(class DrumTrainerPanel * const this /* r30 */, int tick /* r29 */) {
    // References
    // -> static class Message force_fill;
    // -> struct [anonymous] __vt__7Message;
    // -> class TaskMgr TheTaskMgr;
    // -> class Game * TheGame;
}

// Range: 0x800E651C -> 0x800E66CC
void DrumTrainerPanel::RebuildGems(class DrumTrainerPanel * const this /* r28 */) {
    // Local variables
    int endTick; // r0
    class GameGemList & gameGemList; // r0
    struct FillExtent e; // r1+0x8
    int id; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongDB * TheSongDB;
}

// Range: 0x800E66CC -> 0x800E66DC
int DrumTrainerPanel::BPMToTempo() {}

// Range: 0x800E66DC -> 0x800E6770
void DrumTrainerPanel::SetBPM(class DrumTrainerPanel * const this /* r30 */, int bpm /* r31 */) {}

// Range: 0x800E6770 -> 0x800E6798
int DrumTrainerPanel::GetNumBeats() {}

// Range: 0x800E6798 -> 0x800E6830
class Symbol DrumTrainerPanel::GetBeatName(const class DrumTrainerPanel * const this /* r29 */, int index /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E6830 -> 0x800E68CC
int DrumTrainerPanel::GetNumNotes(const class DrumTrainerPanel * const this /* r29 */, int index /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E68CC -> 0x800E6968
int DrumTrainerPanel::GetNumFillNotes(const class DrumTrainerPanel * const this /* r29 */, int index /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E6968 -> 0x800E6B54
void DrumTrainerPanel::CopyBeat(class DrumTrainerPanel * const this /* r29 */, int index /* r30 */, int loops /* r26 */, int dest_tick /* r31 */) {
    // Local variables
    const struct BeatData & bd; // r0
    unsigned char beatPatternStarted; // r0
    struct FillExtent inFill; // r1+0x10
    int i; // r28
    int tick; // r3
    int fillStartTick; // r4
    int fillEndTick; // r5

    // References
    // -> class SongDB * TheSongDB;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E6B54 -> 0x800E6C34
void DrumTrainerPanel::LoopBeat(class DrumTrainerPanel * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E6C34 -> 0x800E6DD4
void DrumTrainerPanel::StartBeat(class DrumTrainerPanel * const this /* r30 */, int bpm /* r27 */, int index /* r31 */) {
    // Local variables
    int horizonTick; // r28
    struct MBT mbt; // r1+0x8
    int beatsPerMeasure; // r0
    int destTick; // r27

    // References
    // -> class SongDB * TheSongDB;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E6DD4 -> 0x800E6E4C
int DrumTrainerPanel::LastGemBefore(int tick /* r31 */) {
    // Local variables
    const class GameGemList & gems; // r0
    int id; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class SongDB * TheSongDB;
}

// Range: 0x800E6E4C -> 0x800E6E68
void DrumTrainerPanel::SetHasBeats() {}

// Range: 0x800E6E68 -> 0x800E6EDC
float DrumTrainerPanel::GetHorizonMs(const class DrumTrainerPanel * const this /* r31 */) {}

// Range: 0x800E6EDC -> 0x800E6F2C
int DrumTrainerPanel::GetBottomTick(int tick /* r31 */) {}

// Range: 0x800E6F2C -> 0x800E6F5C
int DrumTrainerPanel::GetHorizonTick() {}

// Range: 0x800E6F5C -> 0x800E6FC0
int DrumTrainerPanel::GetHorizonBeatTick() {}

// Range: 0x800E6FC0 -> 0x800E6FC8
void DrumTrainerPanel::WipeDrumFills() {}

// Range: 0x800E6FC8 -> 0x800E7050
void DrumTrainerPanel::InsertDrumFill() {
    // Local variables
    int duration; // r5
    unsigned char ok; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E7050 -> 0x800E73E4
void DrumTrainerPanel::PopulateTabData(class DrumTrainerPanel * const this /* r28 */, int index /* r30 */, unsigned char fillOnly /* r29 */) {
    // Local variables
    int i; // r29
    int j; // r27
    float startTick; // f31
    float endTick; // f30
    float tick; // f2
    int slots; // r0
    float frame; // f29
    struct TabData tabData; // r1+0x34
    struct TabData tabData; // r1+0x28

    // References
    // -> class SongDB * TheSongDB;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E73E4 -> 0x800E7428
void DrumTrainerPanel::ClearGems(class DrumTrainerPanel * const this /* r31 */) {}

// Range: 0x800E7428 -> 0x800E747C
unsigned char DrumTrainerPanel::IsInFill(int tick /* r31 */) {
    // Local variables
    class FillInfo * fillInfo; // r0

    // References
    // -> class SongDB * TheSongDB;
}

static float bpm_min; // size: 0x4, address: 0x80A465C8
static float bpm_max; // size: 0x4, address: 0x80A465CC
// Range: 0x800E747C -> 0x800E74FC
void DrumTrainerPanel::UpdateTrackSpeed() {
    // Local variables
    float fbpm; // f0
    float t; // f2
    float modifier; // f1
    float final; // f1

    // References
    // -> static float bpm_max;
    // -> static float bpm_min;
}

static class Symbol start_drum_trainer_fill; // size: 0x4, address: 0x80A4AECC
static class Symbol end_drum_trainer_fill; // size: 0x4, address: 0x80A4AED4
static class Symbol start_drum_trainer_beat; // size: 0x4, address: 0x80A4AEDC
static class Symbol end_drum_trainer_beat; // size: 0x4, address: 0x80A4AEE4
static class Symbol drum_trainer_gems; // size: 0x4, address: 0x80A4AEEC
static class Symbol drum_trainer_begin; // size: 0x4, address: 0x80A4AEF4
static class Symbol drum_trainer_track_speed; // size: 0x4, address: 0x80A4AEFC
static class Symbol disco_beat; // size: 0x4, address: 0x80A4AF04
static class Symbol tom_beat; // size: 0x4, address: 0x80A4AF0C
// Range: 0x800E74FC -> 0x800E7890
void DrumTrainerPanel::InitBeatData(class DrumTrainerPanel * const this /* r28 */) {
    // Local variables
    struct BeatData temp; // r1+0x20
    const class DataEventList * events; // r31
    int i; // r30
    const class DataEvent & d; // r0
    unsigned char beatDone; // r29

    // References
    // -> class Game * TheGame;
    // -> static class Symbol tom_beat;
    // -> static class Symbol disco_beat;
    // -> static class Symbol drum_trainer_track_speed;
    // -> static class Symbol drum_trainer_begin;
    // -> static class Symbol drum_trainer_gems;
    // -> static class Symbol end_drum_trainer_beat;
    // -> static class Symbol start_drum_trainer_beat;
    // -> static class Symbol end_drum_trainer_fill;
    // -> static class Symbol start_drum_trainer_fill;
}

// Range: 0x800E7890 -> 0x800E7B78
void DrumTrainerPanel::GetNoteCount(class DrumTrainerPanel * const this /* r27 */) {
    // Local variables
    class GameGemList gemList; // r1+0x24
    int i; // r31
    int count; // r30
    int fillCount; // r29
    int start_id; // r3
    int j; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__P7GameGem;
    // -> unsigned char gStlAllocNameLookup;
    // -> class SongDB * TheSongDB;
}

static class Symbol _s; // size: 0x4, address: 0x80A4AF14
static class Symbol _s; // size: 0x4, address: 0x80A4AF1C
static class Symbol _s; // size: 0x4, address: 0x80A4AF24
static class Symbol _s; // size: 0x4, address: 0x80A4AF2C
static class Symbol _s; // size: 0x4, address: 0x80A4AF34
static class Symbol _s; // size: 0x4, address: 0x80A4AF3C
static class Symbol _s; // size: 0x4, address: 0x80A4AF44
static class Symbol _s; // size: 0x4, address: 0x80A4AF4C
static class Symbol _s; // size: 0x4, address: 0x80A4AF54
static class Symbol _s; // size: 0x4, address: 0x80A4AF5C
static class Symbol _s; // size: 0x4, address: 0x80A4AF64
static class Symbol _s; // size: 0x4, address: 0x80A4AF6C
static class Symbol _s; // size: 0x4, address: 0x80A4AF74
static class Symbol _s; // size: 0x4, address: 0x80A4AF7C
static class Symbol _s; // size: 0x4, address: 0x80A4AF84
static class Symbol _s; // size: 0x4, address: 0x80A4AF8C
static class Symbol _s; // size: 0x4, address: 0x80A4AF94
static class Symbol _s; // size: 0x4, address: 0x80A4AF9C
static class Symbol _s; // size: 0x4, address: 0x80A4AFA4
static class Symbol _s; // size: 0x4, address: 0x80A4AFAC
static class Symbol _s; // size: 0x4, address: 0x80A4AFB4
// Range: 0x800E7B78 -> 0x800E8668
class DataNode DrumTrainerPanel::Handle(class DrumTrainerPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x18
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28
    class DataNode _n; // r1+0x20

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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x800E8668 -> 0x800E86CC
void * BeatData::BeatData(struct BeatData * const this /* r31 */) {}

// Range: 0x800E86CC -> 0x800E874C
void BeatData::Clear(struct BeatData * const this /* r31 */) {}

// Range: 0x800E874C -> 0x800E8780
void BeatData::Finalize() {}

// Range: 0x800E8780 -> 0x800E88E4
void BeatData::SanityCheck(struct BeatData * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x800E88E4 -> 0x800E88F8
unsigned char BeatData::HasFill() {}

struct {
    // total size: 0x8
} __RTTI__18MultiTempoTempoMap; // size: 0x8, address: 0x808856D0
struct {
    // total size: 0x8
} __RTTI__8TempoMap; // size: 0x8, address: 0x808856E8
struct {
    // total size: 0x8
} __RTTI__12DrumFillInfo; // size: 0x8, address: 0x80885938
struct {
    // total size: 0x8
} __RTTI__8FillInfo; // size: 0x8, address: 0x80885950
struct {
    // total size: 0xAC
} __vt__16DrumTrainerPanel; // size: 0xAC, address: 0x80885C18
struct {
    // total size: 0x8
} __RTTI__16DrumTrainerPanel; // size: 0x8, address: 0x80885CF8
struct {
    // total size: 0x8
} __RTTI__PQ216DrumTrainerPanel7TabData; // size: 0x8, address: 0x80885DA0
struct {
    // total size: 0x8
} __RTTI__PQ216DrumTrainerPanel8BeatData; // size: 0x8, address: 0x80885DC8

