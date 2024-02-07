/*
    Compile unit: C:\rockband2\band2\src\meta\TourEvent.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801D3930 -> 0x801D678C
*/
// Range: 0x801D3930 -> 0x801D3960
void * EventSong::EventSong(class EventSong * const this /* r31 */) {}

// Range: 0x801D3960 -> 0x801D3980
void * EventSong::EventSong() {}

// Range: 0x801D3980 -> 0x801D39C8
unsigned char EventSong::IsRanked() {}

static class Symbol random; // size: 0x4, address: 0x80A4DD3C
// Range: 0x801D39C8 -> 0x801D3A70
unsigned char EventSong::IsRandom(const class EventSong * const this /* r31 */) {
    // References
    // -> static class Symbol random;
}

static class Symbol any; // size: 0x4, address: 0x80A4DD44
// Range: 0x801D3A70 -> 0x801D3AFC
unsigned char EventSong::IsAny(const class EventSong * const this /* r30 */) {
    // References
    // -> static class Symbol any;
}

// Range: 0x801D3AFC -> 0x801D3BA4
class Symbol EventSong::Song(const class EventSong * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801D3BA4 -> 0x801D3C54
class Symbol EventSong::ConcreteSong(const class EventSong * const this /* r28 */, const class SongMgr & sm /* r29 */) {
    // Local variables
    class DataArray * a; // r30
}

static class Symbol min_rank; // size: 0x4, address: 0x80A4DD4C
static class Symbol min_tier; // size: 0x4, address: 0x80A4DD54
static class Symbol max_rank; // size: 0x4, address: 0x80A4DD5C
static class Symbol max_tier; // size: 0x4, address: 0x80A4DD64
// Range: 0x801D3C54 -> 0x801D3F6C
void EventSong::MinMaxBandRank(const class EventSong * const this /* r27 */, const class SongMgr & sm /* r28 */, float & min /* r29 */, float & max /* r30 */) {
    // Local variables
    class DataArray * a; // r26
    class DataArray * m; // r25
    class DataArray * m; // r25
    class DataArray * m; // r25
    class DataArray * m; // r25

    // References
    // -> static class Symbol max_tier;
    // -> static class Symbol max_rank;
    // -> static class Symbol min_tier;
    // -> static class Symbol min_rank;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol band; // size: 0x4, address: 0x80A4DD6C
struct iterator {
    // total size: 0x1
};
class reverse_iterator : public iterator {
    // total size: 0x4
protected:
    const class Symbol * current; // offset 0x0, size 0x4
};
// Range: 0x801D3F6C -> 0x801D41AC
float EventSong::BandTierRank(const class SongMgr & sm /* r29 */, int tier /* r30 */, unsigned char min /* r27 */) {
    // Local variables
    int num_tiers; // r0
    const class vector & songs; // r0
    const class Symbol * s; // r27
    class reverse_iterator s; // r1+0x34

    // References
    // -> static class Symbol band;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol band; // size: 0x4, address: 0x80A4DD74
// Range: 0x801D41AC -> 0x801D424C
float EventSong::BandSongRank(const class EventSong * const this /* r29 */, const class SongMgr & sm /* r30 */, int idx /* r31 */) {
    // References
    // -> static class Symbol band;
}

// Range: 0x801D424C -> 0x801D43AC
class Symbol EventSong::RankedSong(const class SongMgr & sm /* r31 */, class Symbol & part /* r28 */, int idx /* r29 */) {
    // Local variables
    const class vector & disc_songs; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

int sMaxStarsPerSong; // size: 0x4, address: 0x80A468C0
const char * sBotbLoadingScreen; // size: 0x4, address: 0x80A4DD78
static class Symbol songs; // size: 0x4, address: 0x80A4DD80
static class Symbol money_per_star; // size: 0x4, address: 0x80A4DD88
static class Symbol char_unlock; // size: 0x4, address: 0x80A4DD90
static class Symbol token; // size: 0x4, address: 0x80A4DD98
static class Symbol outfits; // size: 0x4, address: 0x80A4DDA0
static class Symbol instruments; // size: 0x4, address: 0x80A4DDA8
static class Symbol sellout; // size: 0x4, address: 0x80A4DDB0
static class Symbol min_difficulty; // size: 0x4, address: 0x80A4DDB8
static class Symbol loading_screen; // size: 0x4, address: 0x80A4DDC0
// Range: 0x801D43AC -> 0x801D49F4
void * TourEvent::TourEvent(class TourEvent * const this /* r27 */, const class SongMgr & song_mgr /* r25 */, class DataArray * cfg /* r28 */) {
    // Local variables
    struct DateTime t; // r1+0x78
    class DataArray * s_array; // r30
    int i; // r29
    class EventSong es; // r1+0x70
    class DataArray * cu; // r29
    class DataArray * o; // r26
    int i; // r30
    class DataArray * insts; // r26
    int i; // r29
    class DataArray * diff; // r25

    // References
    // -> static class Symbol loading_screen;
    // -> static class Symbol min_difficulty;
    // -> static class Symbol sellout;
    // -> static class Symbol instruments;
    // -> static class Symbol outfits;
    // -> static class Symbol token;
    // -> static class Symbol char_unlock;
    // -> static class Symbol money_per_star;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol songs;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__9TourEvent;
}

// Range: 0x801D49F4 -> 0x801D4C18
void * TourEvent::~TourEvent(class TourEvent * const this /* r30 */) {}

// Range: 0x801D4C18 -> 0x801D4C20
class Symbol TourEvent::EventName() {}

// Range: 0x801D4C20 -> 0x801D4C28
unsigned char TourEvent::IsOpportunity() {}

// Range: 0x801D4C28 -> 0x801D4C44
unsigned char TourEvent::IsBattle() {}

// Range: 0x801D4C44 -> 0x801D4C5C
int TourEvent::NumSongs() {}

// Range: 0x801D4C5C -> 0x801D4C6C
class EventSong & TourEvent::Song() {}

// Range: 0x801D4C6C -> 0x801D4CE4
class Symbol TourEvent::RankedSong(const class TourEvent * const this /* r30 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x801D4CE4 -> 0x801D4CFC
class Symbol TourEvent::ConcreteSong(const class TourEvent * const this /* r5 */) {}

static class Symbol tour; // size: 0x4, address: 0x80A4DDC8
static class Symbol default_money_per_star; // size: 0x4, address: 0x80A4DDD0
static class Symbol band; // size: 0x4, address: 0x80A4DDD8
// Range: 0x801D4CFC -> 0x801D4F04
int TourEvent::MoneyPerStar(const class TourEvent * const this /* r29 */, class Symbol & song /* r30 */) {
    // Local variables
    class DataArrayPtr args; // r1+0x28
    class DataArray * s; // r0

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol band;
    // -> static class Symbol default_money_per_star;
    // -> static class Symbol tour;
}

// Range: 0x801D4F04 -> 0x801D4F0C
class vector & TourEvent::UnlockOutfits() {}

// Range: 0x801D4F0C -> 0x801D4F14
class vector & TourEvent::UnlockInstruments() {}

// Range: 0x801D4F14 -> 0x801D4F1C
class Symbol TourEvent::RequiredPart() {}

// Range: 0x801D4F1C -> 0x801D4F44
int TourEvent::TotalStars() {
    // References
    // -> int sMaxStarsPerSong;
}

// Range: 0x801D4F44 -> 0x801D4F4C
enum Difficulty TourEvent::MinDifficulty() {}

// Range: 0x801D4F4C -> 0x801D4F54
int TourEvent::MaxStarsPerSong() {
    // References
    // -> int sMaxStarsPerSong;
}

// Range: 0x801D4F54 -> 0x801D4F6C
void TourEvent::SetBattleId() {
    // References
    // -> const char * sBotbLoadingScreen;
}

// Range: 0x801D4F6C -> 0x801D4F74
void TourEvent::SetDisplayName() {}

// Range: 0x801D4F74 -> 0x801D4F80
void TourEvent::SetEventName() {}

// Range: 0x801D4F80 -> 0x801D4FF8
void TourEvent::SetTime(class TourEvent * const this /* r7 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x801D4FF8 -> 0x801D50BC
void TourEvent::AddSong(class TourEvent * const this /* r31 */) {}

// Range: 0x801D50BC -> 0x801D50C8
void TourEvent::SetRequiredPart() {}

// Range: 0x801D50C8 -> 0x801D50D0
void TourEvent::SetMinDifficulty() {}

// Range: 0x801D50D0 -> 0x801D5230
void TourEvent::AddUnlockOutfit(class TourEvent * const this /* r31 */, class Symbol & gender /* r25 */, class Symbol & category /* r26 */, class Symbol & outfit /* r27 */) {
    // Local variables
    struct EventOutfit eo; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x801D5230 -> 0x801D53DC
void TourEvent::AddUnlockInstrument(class TourEvent * const this /* r28 */, class Symbol & category /* r29 */, class Symbol & outfit /* r30 */) {
    // Local variables
    struct EventInstrument ei; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x801D53DC -> 0x801D53E4
void TourEvent::SetMaxStarsPerSong() {
    // References
    // -> int sMaxStarsPerSong;
}

// Range: 0x801D53E4 -> 0x801D53EC
void TourEvent::SetBotbLoadingScreen() {
    // References
    // -> const char * sBotbLoadingScreen;
}

// Range: 0x801D53EC -> 0x801D5478
unsigned char TourEvent::IsExpired(class TourEvent * const this /* r31 */) {
    // Local variables
    struct DateTime t; // r1+0x8
    int elapsedTime; // r3

    // References
    // -> unsigned char sAllExpired;
}

// Range: 0x801D5478 -> 0x801D5508
unsigned char TourEvent::IsLive(class TourEvent * const this /* r31 */) {
    // Local variables
    struct DateTime t; // r1+0x8
    int elapsedTime; // r4

    // References
    // -> unsigned char sAllLive;
}

unsigned char sAllExpired; // size: 0x1, address: 0x80A4DDDC
unsigned char sAllLive; // size: 0x1, address: 0x80A4DDDD
static class Symbol random; // size: 0x4, address: 0x80A4DDE0
static class Symbol any; // size: 0x4, address: 0x80A4DDE8
// Range: 0x801D5508 -> 0x801D5768
void TourEvent::Validate(const class TourEvent * const this /* r29 */) {
    // Local variables
    const struct EventOutfit * eo; // r26
    const struct EventInstrument * ei; // r26
    int i; // r30
    class EventSong song; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol any;
    // -> static class Symbol random;
}

// Range: 0x801D5768 -> 0x801D58EC
void TourEvent::ValidateOutfit(const class TourEvent * const this /* r25 */, class Symbol & gender /* r26 */, class Symbol & category /* r27 */, class Symbol & outfit /* r28 */) {
    // Local variables
    class DataArray * loaders; // r0
    class DataArray * cat; // r30
    class DataArray * loader_oufits; // r3

    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A4DDF0
static class Symbol _s; // size: 0x4, address: 0x80A4DDF8
static class Symbol _s; // size: 0x4, address: 0x80A4DE00
static class Symbol _s; // size: 0x4, address: 0x80A4DE08
static class Symbol _s; // size: 0x4, address: 0x80A4DE10
static class Symbol _s; // size: 0x4, address: 0x80A4DE18
static class Symbol _s; // size: 0x4, address: 0x80A4DE20
static class Symbol _s; // size: 0x4, address: 0x80A4DE28
static class Symbol _s; // size: 0x4, address: 0x80A4DE30
static class Symbol _s; // size: 0x4, address: 0x80A4DE38
// Range: 0x801D58EC -> 0x801D6468
class DataNode TourEvent::Handle(class TourEvent * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x50
    class MessageTimer _mt; // r1+0x60
    class DataNode _n; // r1+0x58

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
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4DE40
static class Symbol _s; // size: 0x4, address: 0x80A4DE48
static class Symbol _s; // size: 0x4, address: 0x80A4DE50
// Range: 0x801D6468 -> 0x801D678C
unsigned char TourEvent::SyncProperty(class TourEvent * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x68
} __vt__9TourEvent; // size: 0x68, address: 0x808A4B80
struct {
    // total size: 0x8
} __RTTI__P15EventInstrument; // size: 0x8, address: 0x808A4C80
struct {
    // total size: 0x8
} __RTTI__P11EventOutfit; // size: 0x8, address: 0x808A4C98

