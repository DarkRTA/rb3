/*
    Compile unit: C:\rockband2\band2\src\game\Band.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800405C8 -> 0x80043074
*/
// Range: 0x800405C8 -> 0x800409DC
void * Band::Band(class Band * const this /* r26 */, unsigned char oneBandPerPlayer /* r27 */, int playerNum /* r28 */, class BeatMaster * beatMaster /* r29 */) {
    // Local variables
    int i; // r30
    class Player * p; // r1+0x24
    int i; // r25

    // References
    // -> struct [anonymous] __vt__10NullPlayer;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__4Band;
}

// Range: 0x800409DC -> 0x80040C7C
void * Band::~Band(class Band * const this /* r30 */) {
    // Local variables
    int i; // r28

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> struct [anonymous] __vt__4Band;
}

// Range: 0x80040D04 -> 0x80040DD4
void Band::Restart(class Band * const this /* r30 */) {
    // Local variables
    unsigned int i; // r31
}

// Range: 0x80040DD4 -> 0x80040DDC
class Performer * Band::GetBand() {}

// Range: 0x80040DDC -> 0x80040E7C
class Player * Band::GetPlayer(const class Band * const this /* r30 */, int player /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80040E7C -> 0x80040F1C
class Player * Band::GetActivePlayer(const class Band * const this /* r30 */, int player /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80040F1C -> 0x80040F34
int Band::NumActivePlayers() {}

// Range: 0x80040F34 -> 0x80040F54
class Performer * Band::MainPerformer() {}

// Range: 0x80040F54 -> 0x80040F5C
class vector & Band::GetActivePlayers() {}

// Range: 0x80040F5C -> 0x80040F64
class vector & Band::GetActivePlayers() {}

// Range: 0x80040F64 -> 0x80040F6C
void Band::SetAccumulatedScore() {}

// Range: 0x80040F6C -> 0x80040F74
void Band::SetTotalStars() {}

// Range: 0x80040F74 -> 0x80040F7C
void Band::SetLongestStreak() {}

// Range: 0x80040F7C -> 0x80041008
int Band::GetLongestStreak() {
    // Local variables
    int max_streak; // r1+0xC
    const class vector & players; // r0
    class Player * const * it; // r30
}

// Range: 0x80041008 -> 0x8004131C
void Band::Poll(class Band * const this /* r31 */, float ms /* f31 */, class SongPos & song_pos /* r28 */) {
    // Local variables
    int i; // r29
    float rating; // f0
    float rating; // f0
    int tick; // r29
    int codaStart; // r0
    int i; // r29
    int playerNum; // r29
    unsigned char codaResolved; // r29
    int i; // r28

    // References
    // -> class GameMode * TheGameMode;
    // -> class SongDB * TheSongDB;
}

// Range: 0x8004131C -> 0x800413A4
void Band::SetCrowdMeterActive(class Band * const this /* r29 */, unsigned char active /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x800413A4 -> 0x8004145C
unsigned char Band::AnyoneSaveable(const class Band * const this /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x8004145C -> 0x80041508
int Band::DeployBandEnergy(class Band * const this /* r27 */, int deployer /* r28 */) {
    // Local variables
    int nSavedCount; // r30
    int i; // r29
}

static class Message blowMsg; // size: 0x8, address: 0x80976DB0
// Range: 0x80041508 -> 0x800416A8
void Band::BlowCoda(class Band * const this /* r30 */, int player /* r29 */) {
    // References
    // -> static class Message blowMsg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message blownMsg; // size: 0x8, address: 0x80976DC8
// Range: 0x800416A8 -> 0x8004193C
void Band::LocalBlowCoda(class Band * const this /* r28 */, int player /* r29 */) {
    // Local variables
    int i; // r30
    class BandTrack * track; // r0

    // References
    // -> class GameMode * TheGameMode;
    // -> class GamePanel * TheGamePanel;
    // -> static class Message blownMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8004193C -> 0x800419BC
void Band::DealWithCodaGem(class Band * const this /* r28 */, int player_num /* r29 */, unsigned char hit /* r30 */, unsigned char last_gem /* r31 */) {
    // References
    // -> class Game * TheGame;
}

// Range: 0x800419BC -> 0x80041AB4
unsigned char Band::IsEndOfCoda(class Band * const this /* r26 */, int tick /* r27 */) {
    // Local variables
    int current_gem_tick; // r30
    int final_gem_tick; // r29
    int i; // r28

    // References
    // -> class SongDB * TheSongDB;
}

// Range: 0x80041AB4 -> 0x80041B34
unsigned char Band::HasFinishedCoda(class Band * const this /* r29 */, int player /* r30 */) {}

// Range: 0x80041B34 -> 0x80041B54
unsigned char Band::HasBlownCoda() {}

// Range: 0x80041B54 -> 0x80041BBC
unsigned char Band::HasResolvedCoda(class Band * const this /* r29 */, int player /* r30 */) {}

// Range: 0x80041BBC -> 0x80041C68
unsigned char Band::EveryoneFinishedCoda(class Band * const this /* r30 */) {
    // Local variables
    int i; // r31
}

static class Message codaEndMsg; // size: 0x8, address: 0x80976DE0
// Range: 0x80041C68 -> 0x80041ED4
void Band::WinCoda(class Band * const this /* r30 */) {
    // Local variables
    int i; // r31
    class BandTrack * track; // r0

    // References
    // -> class GameMode * TheGameMode;
    // -> class GamePanel * TheGamePanel;
    // -> static class Message codaEndMsg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message codaMsg; // size: 0x8, address: 0x80976DF8
// Range: 0x80041ED4 -> 0x8004213C
void Band::FinishedCoda(class Band * const this /* r30 */, int player /* r29 */) {
    // References
    // -> static class Message codaMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x8004213C -> 0x800421D8
void Band::LocalFinishedCoda(class Band * const this /* r30 */, int player /* r31 */) {
    // References
    // -> class GameMode * TheGameMode;
}

// Range: 0x800421D8 -> 0x800421E0
int Band::EnergyMultiplier() {}

static class Symbol crowd_boost; // size: 0x4, address: 0x80A491B0
// Range: 0x800421E0 -> 0x80042278
int Band::EnergyCrowdBoost(const class Band * const this /* r31 */) {
    // References
    // -> static class Symbol crowd_boost;
}

// Range: 0x80042278 -> 0x800422E4
void Band::ForceStars(class Band * const this /* r29 */, int stars /* r30 */) {
    // Local variables
    class Player * * p; // r31
}

// Range: 0x800422E4 -> 0x8004231C
int Band::GetInstrumentBitfield() {
    // Local variables
    int instr_bitfield; // r5
    class Player * * p; // r6
}

// Range: 0x8004231C -> 0x800423F0
class Player * Band::NewPlayer(class Band * const this /* r27 */, class BeatMaster * beatMaster /* r28 */, int num /* r29 */) {
    // Local variables
    int track; // r31
    class BandUser * cfg; // r30

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class GameConfig * TheGameConfig;
}

// Range: 0x800423F0 -> 0x800425A0
void Band::UpdateBonusLevel(class Band * const this /* r28 */, float ms /* f31 */) {
    // Local variables
    int bonus_level; // r29
    class Player * * p; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A491B8
static class Symbol _s; // size: 0x4, address: 0x80A491C0
static class Symbol _s; // size: 0x4, address: 0x80A491C8
static class Symbol _s; // size: 0x4, address: 0x80A491D0
static class Symbol _s; // size: 0x4, address: 0x80A491D8
static class Symbol _s; // size: 0x4, address: 0x80A491E0
static class Symbol _s; // size: 0x4, address: 0x80A491E8
static class Symbol _s; // size: 0x4, address: 0x80A491F0
static class Symbol _s; // size: 0x4, address: 0x80A491F8
// Range: 0x800425A0 -> 0x80043074
class DataNode Band::Handle(class Band * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x44
    class MessageTimer _mt; // r1+0x50
    class DataNode _n; // r1+0x48

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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class NullPlayer : public Player {
    // total size: 0x138
};
struct {
    // total size: 0x1E4
} __vt__10NullPlayer; // size: 0x1E4, address: 0x80871C2C
struct {
    // total size: 0x8
} __RTTI__10NullPlayer; // size: 0x8, address: 0x80871E48
struct {
    // total size: 0x54
} __vt__4Band; // size: 0x54, address: 0x80871EB0
struct {
    // total size: 0x8
} __RTTI__4Band; // size: 0x8, address: 0x80871F20
struct {
    // total size: 0x8
} __RTTI__PP6Player; // size: 0x8, address: 0x80871FB0

