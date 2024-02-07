/*
    Compile unit: C:\rockband2\band2\src\meta\MetaPerformer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80119AE4 -> 0x8011CFB0
*/
// Range: 0x80119AE4 -> 0x80119B40
class Symbol QuickplayPerformer::Song() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x80119B40 -> 0x80119B44
unsigned char QuickplayPerformer::IsWinning() {}

// Range: 0x80119B44 -> 0x80119B4C
class PersistentGameData * QuickplayPerformer::GetPersistentGameData() {}

// Range: 0x80119B4C -> 0x80119B54
float QuickplayPerformer::GetBotbTargetStartAccumScore() {}

// Range: 0x80119B54 -> 0x80119B5C
float QuickplayPerformer::GetBotbTargetEndAccumScore() {}

// Range: 0x80119B5C -> 0x80119B64
char * QuickplayPerformer::GetBotbRivalBandName() {}

// Range: 0x80119B64 -> 0x80119B6C
int QuickplayPerformer::GetBotbRivalBandScore() {}

// Range: 0x80119B6C -> 0x80119B74
int QuickplayPerformer::GetBotbRivalBandStars() {}

// Range: 0x80119B74 -> 0x80119B7C
unsigned char QuickplayPerformer::GetBotbBattleIsBrandNew() {}

// Range: 0x80119B7C -> 0x80119B84
class String QuickplayPerformer::GetBandIcon() {}

// Range: 0x80119B84 -> 0x80119B8C
class String QuickplayPerformer::GetBotbRivalBandIcon() {}

// Range: 0x80119B8C -> 0x80119B94
class String QuickplayPerformer::GetBotbRivalBandIconPath() {}

// Range: 0x80119B94 -> 0x80119B9C
enum Difficulty QuickplayPerformer::MinDifficultySelect() {}

// Range: 0x80119B9C -> 0x80119BA4
unsigned char QuickplayPerformer::GetNoOverdrive() {}

// Range: 0x80119BA4 -> 0x80119BAC
unsigned char QuickplayPerformer::GetNoCrowdMeter() {}

// Range: 0x80119BAC -> 0x80119BB4
unsigned char QuickplayPerformer::GetNoBackFromBrink() {}

// Range: 0x80119BB4 -> 0x80119BBC
enum WinMetric QuickplayPerformer::GetWinMetric() {}

// Range: 0x80119BBC -> 0x80119CB8
class BandUser * QuickplayPerformer::SongSelectUser(const class QuickplayPerformer * const this /* r29 */) {
    // Local variables
    int i; // r31
    class BandUser * u; // r30
    int i; // r30
    class BandUser * u; // r31

    // References
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Net TheNet;
}

static class Symbol any; // size: 0x4, address: 0x80A4B93C
// Range: 0x80119CB8 -> 0x80119D3C
int QuickplayPerformer::PreviousSongSelection(const class QuickplayPerformer * const this /* r31 */) {
    // Local variables
    int i; // r3

    // References
    // -> static class Symbol any;
}

// Range: 0x80119D3C -> 0x80119E24
class DataNode QuickplayPerformer::OnSetSong(class QuickplayPerformer * const this /* r30 */, class DataArray * a /* r31 */) {}

// Range: 0x80119E24 -> 0x80119F2C
void QuickplayPerformer::SelectSong(class QuickplayPerformer * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80119F2C -> 0x8011A044
void QuickplayPerformer::SetSongs(class QuickplayPerformer * const this /* r29 */, class DataArray * songs /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011A044 -> 0x8011A150
void QuickplayPerformer::Restart(class QuickplayPerformer * const this /* r29 */) {
    // References
    // -> class SyncStore * TheSyncStore;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011A150 -> 0x8011A2CC
void QuickplayPerformer::OnFinalizeSetlist(class QuickplayPerformer * const this /* r31 */) {
    // Local variables
    int i; // r0

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol any; // size: 0x4, address: 0x80A4B944
// Range: 0x8011A2CC -> 0x8011A3C0
class Symbol QuickplayPerformer::RevertSongSelection(class QuickplayPerformer * const this /* r30 */) {
    // Local variables
    int i; // r0
    class Symbol reverted; // r1+0x8

    // References
    // -> class SyncStore * TheSyncStore;
    // -> const char * gNullStr;
    // -> static class Symbol any;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011A3C0 -> 0x8011A3F4
void QuickplayPerformer::Clear(class QuickplayPerformer * const this /* r31 */) {}

// Range: 0x8011A3F4 -> 0x8011A42C
void QuickplayPerformer::AdvanceSong(class QuickplayPerformer * const this /* r31 */) {}

// Range: 0x8011A42C -> 0x8011A4E0
void QuickplayPerformer::AdvanceSongSelectUser(class QuickplayPerformer * const this /* r31 */) {
    // Local variables
    class BandUser * u; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011A4E0 -> 0x8011A4E8
void QuickplayPerformer::SetSongSelectSync() {}

// Range: 0x8011A4E8 -> 0x8011A538
void QuickplayPerformer::SyncSave(const class QuickplayPerformer * const this /* r31 */) {}

// Range: 0x8011A538 -> 0x8011A580
void QuickplayPerformer::SyncLoad(class QuickplayPerformer * const this /* r31 */) {}

// Range: 0x8011A580 -> 0x8011A5D8
unsigned char QuickplayPerformer::HasSyncPermission() {
    // Local variables
    class BandUser * u; // r0
}

static class Symbol _s; // size: 0x4, address: 0x80A4B94C
static class Symbol _s; // size: 0x4, address: 0x80A4B954
static class Symbol _s; // size: 0x4, address: 0x80A4B95C
static class Symbol _s; // size: 0x4, address: 0x80A4B964
// Range: 0x8011A5D8 -> 0x8011ADC8
class DataNode QuickplayPerformer::Handle(class QuickplayPerformer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> class SyncStore * TheSyncStore;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class MetaPerformerHook * sScriptHook; // size: 0x4, address: 0x80A4B968
unsigned char sCheatFinale; // size: 0x1, address: 0x80A4B96C
class Symbol is_tour; // size: 0x4, address: 0x80A4B970
class MetaPerformerHook : public Object {
    // total size: 0x2C
    class QuickplayPerformer * mQuickplayPerformer; // offset 0x28, size 0x4
};
// Range: 0x8011ADC8 -> 0x8011B2F4
class DataNode MetaPerformerHook::Handle(class MetaPerformerHook * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
    // -> class Symbol is_tour;
    // -> class Tour * TheTour;
    // -> unsigned char sActive;
}

// Range: 0x8011B2F4 -> 0x8011B3C8
void MetaPerformer::Init() {
    // References
    // -> class ObjectDir * sMainDir;
    // -> struct [anonymous] __vt__17MetaPerformerHook;
    // -> class SongMgr & TheSongMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class MetaPerformerHook * sScriptHook;
}

// Range: 0x8011B3C8 -> 0x8011B458
void * MetaPerformerHook::~MetaPerformerHook(class MetaPerformerHook * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__17MetaPerformerHook;
}

// Range: 0x8011B5A0 -> 0x8011B668
void * MetaPerformer::MetaPerformer(class MetaPerformer * const this /* r29 */, const class SongMgr & sm /* r30 */, const char * uniqueTag /* r31 */) {
    // References
    // -> struct [anonymous] __vt__13MetaPerformer;
}

// Range: 0x8011B668 -> 0x8011B740
class MetaPerformer * MetaPerformer::Current() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
    // -> class Symbol is_tour;
    // -> class Tour * TheTour;
    // -> class MetaPerformerHook * sScriptHook;
}

// Range: 0x8011B740 -> 0x8011B7A4
unsigned char MetaPerformer::SongEndsWithEndgameSequence(const class MetaPerformer * const this /* r30 */) {}

// Range: 0x8011B7A4 -> 0x8011B7BC
int MetaPerformer::NumSongs() {}

// Range: 0x8011B7BC -> 0x8011B7D4
int MetaPerformer::NumCompleted() {}

static class Symbol any; // size: 0x4, address: 0x80A4B978
// Range: 0x8011B7D4 -> 0x8011B860
int MetaPerformer::NextAnyIndex(const class MetaPerformer * const this /* r31 */) {
    // Local variables
    int i; // r3

    // References
    // -> static class Symbol any;
}

// Range: 0x8011B860 -> 0x8011B8FC
void MetaPerformer::SetAnySong(class MetaPerformer * const this /* r29 */, class Symbol & song /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011B8FC -> 0x8011B9D4
class Symbol MetaPerformer::CompletedSong(const class MetaPerformer * const this /* r29 */) {
    // Local variables
    int idx; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011B9D4 -> 0x8011BA1C
unsigned char MetaPerformer::SongInSet() {}

// Range: 0x8011BA1C -> 0x8011BA34
unsigned char MetaPerformer::IsFirstSong() {}

// Range: 0x8011BA34 -> 0x8011BAC0
unsigned char MetaPerformer::IsLastSong(const class MetaPerformer * const this /* r30 */) {
    // Local variables
    int num_complete; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011BAC0 -> 0x8011BB54
unsigned char MetaPerformer::IsSetComplete(const class MetaPerformer * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol any; // size: 0x4, address: 0x80A4B980
static class Symbol random; // size: 0x4, address: 0x80A4B988
static class Symbol guitar; // size: 0x4, address: 0x80A4B990
static class Symbol bass; // size: 0x4, address: 0x80A4B998
// Range: 0x8011BB54 -> 0x8011BD28
class Symbol MetaPerformer::RequiredSetPart(const class MetaPerformer * const this /* r30 */) {
    // Local variables
    const class Symbol * s; // r31

    // References
    // -> const char * gNullStr;
    // -> static class Symbol bass;
    // -> static class Symbol guitar;
    // -> static class Symbol random;
    // -> static class Symbol any;
}

// Range: 0x8011BD28 -> 0x8011BD2C
class Symbol MetaPerformer::RequiredPart() {}

// Range: 0x8011BD2C -> 0x8011BD34
class BandUser * MetaPerformer::SongSelectUser() {}

static class Symbol modifier_saving_feature; // size: 0x4, address: 0x80A4B9A0
// Range: 0x8011BD34 -> 0x8011BE20
unsigned char MetaPerformer::CanUpdateScoreLeaderboards(class MetaPerformer * const this /* r31 */) {
    // References
    // -> class ModifierMgr * TheModifierMgr;
    // -> static class Symbol modifier_saving_feature;
    // -> class GameMode * TheGameMode;
}

// Range: 0x8011BE20 -> 0x8011BE24
void MetaPerformer::Clear() {}

// Range: 0x8011BE24 -> 0x8011BF04
void MetaPerformer::ResetSongs(class MetaPerformer * const this /* r30 */) {}

// Range: 0x8011BF04 -> 0x8011C1A0
void MetaPerformer::CompleteSong(class MetaPerformer * const this /* r27 */, int num_stars /* r29 */, int score /* r30 */, unsigned char cheat /* r26 */) {
    // Local variables
    class Symbol song; // r1+0x20
    class vector users; // r1+0x24
    class Profile * pProfile; // r26
    int n; // r26
    class Profile * pProfile; // r27

    // References
    // -> class ProfileMgr TheProfileMgr;
    // -> class BandUserMgr * TheBandUserMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011C1A0 -> 0x8011C2B0
void MetaPerformer::AdvanceSong(class MetaPerformer * const this /* r29 */, int num_stars /* r1+0x8 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011C2B0 -> 0x8011C2B4
void MetaPerformer::AdvanceSongSelectUser() {}

// Range: 0x8011C2B4 -> 0x8011C2B8
void MetaPerformer::SetSongSelectSync() {}

static class Symbol update_meta_performer; // size: 0x4, address: 0x80A4B9A8
// Range: 0x8011C2B8 -> 0x8011C3EC
void MetaPerformer::OnSynchronized() {
    // Local variables
    class DataArrayPtr update; // r1+0x20

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol update_meta_performer;
}

// Range: 0x8011C3EC -> 0x8011C434
unsigned char MetaPerformer::IsCheatWinning() {
    // References
    // -> unsigned char sCheatFinale;
}

// Range: 0x8011C434 -> 0x8011C448
unsigned char MetaPerformer::CheatToggleFinale() {
    // References
    // -> unsigned char sCheatFinale;
}

static class Symbol _s; // size: 0x4, address: 0x80A4B9B0
static class Symbol _s; // size: 0x4, address: 0x80A4B9B8
static class Symbol _s; // size: 0x4, address: 0x80A4B9C0
static class Symbol _s; // size: 0x4, address: 0x80A4B9C8
static class Symbol _s; // size: 0x4, address: 0x80A4B9D0
static class Symbol _s; // size: 0x4, address: 0x80A4B9D8
static class Symbol _s; // size: 0x4, address: 0x80A4B9E0
static class Symbol _s; // size: 0x4, address: 0x80A4B9E8
static class Symbol _s; // size: 0x4, address: 0x80A4B9F0
static class Symbol _s; // size: 0x4, address: 0x80A4B9F8
static class Symbol _s; // size: 0x4, address: 0x80A4BA00
static class Symbol _s; // size: 0x4, address: 0x80A4BA08
static class Symbol _s; // size: 0x4, address: 0x80A4BA10
static class Symbol _s; // size: 0x4, address: 0x80A4BA18
static class Symbol _s; // size: 0x4, address: 0x80A4BA20
static class Symbol _s; // size: 0x4, address: 0x80A4BA28
static class Symbol _s; // size: 0x4, address: 0x80A4BA30
static class Symbol _s; // size: 0x4, address: 0x80A4BA38
static class Symbol _s; // size: 0x4, address: 0x80A4BA40
static class Symbol _s; // size: 0x4, address: 0x80A4BA48
static class Symbol _s; // size: 0x4, address: 0x80A4BA50
static class Symbol _s; // size: 0x4, address: 0x80A4BA58
static class Symbol _s; // size: 0x4, address: 0x80A4BA60
static class Symbol _s; // size: 0x4, address: 0x80A4BA68
static class Symbol _s; // size: 0x4, address: 0x80A4BA70
// Range: 0x8011C448 -> 0x8011CFB0
class DataNode MetaPerformer::Handle(class MetaPerformer * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x30

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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x54
} __vt__17MetaPerformerHook; // size: 0x54, address: 0x8088D5D8
struct {
    // total size: 0x8
} __RTTI__17MetaPerformerHook; // size: 0x8, address: 0x8088D658
struct {
    // total size: 0xEC
} __vt__18QuickplayPerformer; // size: 0xEC, address: 0x8088D660
struct {
    // total size: 0xE8
} __vt__13MetaPerformer; // size: 0xE8, address: 0x8088D790
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Synchronizable * * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Synchronizable * * _M_start; // offset 0x0, size 0x4
    class Synchronizable * * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
class SyncStore {
    // total size: 0xC
    class vector mSyncObjs; // offset 0x0, size 0xC
};

