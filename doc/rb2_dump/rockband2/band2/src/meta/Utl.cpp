/*
    Compile unit: C:\rockband2\band2\src\meta\Utl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801F0BC4 -> 0x801F2E54
*/
unsigned char gLatinToAscii[256]; // size: 0x100, address: 0x8097A0A8
unsigned char gLatinToLwrAscii[256]; // size: 0x100, address: 0x8097A1A8
static class Symbol ui; // size: 0x4, address: 0x80A4E34C
static class Symbol latin_to_ascii; // size: 0x4, address: 0x80A4E354
// Range: 0x801F0BC4 -> 0x801F0E5C
void UtlInit() {
    // Local variables
    int i; // r4
    class DataArray * latinToAscii; // r29
    int i; // r28
    int i; // r5

    // References
    // -> unsigned char gLatinToLwrAscii[256];
    // -> struct __locale _current_locale;
    // -> unsigned char gLatinToAscii[256];
    // -> static class Symbol latin_to_ascii;
    // -> static class Symbol ui;
}

// Range: 0x801F0E5C -> 0x801F0EB4
unsigned char IsLeaderLocal() {
    // Local variables
    class BandUser * pUserLeader; // r0

    // References
    // -> class SessionMgr * TheSessionMgr;
}

// Range: 0x801F0EB4 -> 0x801F0EEC
class DataNode OnIsLeaderLocal() {}

static class Symbol general_cash_format; // size: 0x4, address: 0x80A4E35C
// Range: 0x801F0EEC -> 0x801F0F60
char * FmtMoney(int money /* r31 */) {
    // References
    // -> static class Symbol general_cash_format;
}

// Range: 0x801F0F60 -> 0x801F0FB8
class DataNode OnFmtMoney(class DataArray * a /* r31 */) {}

// Range: 0x801F0FB8 -> 0x801F102C
char * AlphaKeySkip() {}

// Range: 0x801F102C -> 0x801F1094
void CalculateAlphaKey(char * output /* r31 */) {
    // References
    // -> unsigned char gLatinToAscii[256];
}

// Range: 0x801F1094 -> 0x801F1154
int AlphaKeyStrCmp(const char * lhs /* r29 */, const char * rhs /* r30 */, unsigned char skip_the /* r31 */) {
    // Local variables
    unsigned char l; // r4
    unsigned char r; // r0

    // References
    // -> unsigned char gLatinToLwrAscii[256];
}

// Range: 0x801F1154 -> 0x801F11C0
class DataNode OnGetFontCharFromInstrument(class DataArray * data /* r31 */) {
    // Local variables
    class Symbol instrument; // r1+0x14
}

// Range: 0x801F11C0 -> 0x801F1218
class DataNode OnGetFontCharFromControllerType(class DataArray * data /* r31 */) {}

// Range: 0x801F1218 -> 0x801F1270
class DataNode OnGetFontCharFromTrackType(class DataArray * data /* r31 */) {}

// Range: 0x801F1270 -> 0x801F12E8
char * GetFontCharFromInstrument(class Symbol & instrument /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x801F12E8 -> 0x801F13FC
char * GetFontCharFromTrackType(enum TrackType trackType /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801F13FC -> 0x801F14DC
char * GetFontCharFromControllerType(enum ControllerType controllerType /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol venues; // size: 0x4, address: 0x80A4E364
static class Symbol kVideoVenueProbability; // size: 0x4, address: 0x80A4E36C
static class Symbol use_video_venues_from_songs; // size: 0x4, address: 0x80A4E374
static class Symbol blank_01; // size: 0x4, address: 0x80A4E37C
// Range: 0x801F14DC -> 0x801F17E8
class Symbol RandomVenue() {
    // Local variables
    class vector videoVenues; // r1+0x4C
    float fProbability; // f0
    class DataArray * v; // r30
    class Symbol venue; // r1+0x48

    // References
    // -> const char * gNullStr;
    // -> static class Symbol blank_01;
    // -> static class Symbol use_video_venues_from_songs;
    // -> static class Symbol kVideoVenueProbability;
    // -> static class Symbol venues;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
}

// Range: 0x801F17E8 -> 0x801F1AE0
void GetVideoVenuesFromCurrentPerformer(class vector & outVideoVenues /* r28 */) {
    // Local variables
    class map videoVenueMap; // r1+0x70
    class MetaPerformer * performer; // r30
    int songCount; // r0
    int iSong; // r29
    class Symbol song; // r1+0x38
    const class DataArray * videoVenues; // r27
    int iVenue; // r26
    struct _Rb_tree_iterator iter; // r1+0x34
    struct _Rb_tree_iterator iter; // r1+0x30

    // References
    // -> class SongMgr & TheSongMgr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801F1AE0 -> 0x801F1B1C
class DataNode OnRandomVenue() {}

static class Symbol venues; // size: 0x4, address: 0x80A4E384
static class Symbol blank_01; // size: 0x4, address: 0x80A4E38C
static class Symbol use_video_venues_from_songs; // size: 0x4, address: 0x80A4E394
// Range: 0x801F1B1C -> 0x801F1E78
class DataNode OnGetVenueSelectArray() {
    // Local variables
    class DataArray * rawVenues; // r30
    class DataArrayPtr venueArray; // r1+0x48
    class vector videoVenues; // r1+0x50
    class Symbol * iter; // r30
    class Symbol videoVenue; // r1+0x34

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
    // -> static class Symbol use_video_venues_from_songs;
    // -> static class Symbol blank_01;
    // -> static class Symbol venues;
}

// Range: 0x801F1E78 -> 0x801F1F04
static int FilterShot() {
    // References
    // -> class WorldDir * TheWorld;
}

// Range: 0x801F1F04 -> 0x801F1F90
static void ForceFocus(unsigned char & fc /* r30 */, unsigned char & fd /* r31 */) {}

static unsigned char sSoloMode; // size: 0x1, address: 0x80A4E398
// Range: 0x801F1F90 -> 0x801F1FF4
class DataNode OnSetCameraSoloMode(class DataArray * msg /* r31 */) {
    // References
    // -> static unsigned char sSoloMode;
}

static class Symbol bass; // size: 0x4, address: 0x80A4E39C
static class Symbol drum; // size: 0x4, address: 0x80A4E3A4
static class Symbol guitar; // size: 0x4, address: 0x80A4E3AC
static class Symbol vocals; // size: 0x4, address: 0x80A4E3B4
static char * cats[8]; // size: 0x20, address: 0x808A7F68
// Range: 0x801F1FF4 -> 0x801F2584
class DataNode OnGetCoopCameraFlags(class DataArray * data /* r26 */) {
    // Local variables
    unsigned char focusBass; // r1+0xB
    unsigned char focusDrum; // r1+0xA
    unsigned char focusGuitar; // r1+0x9
    unsigned char focusVocal; // r1+0x8
    unsigned char noCloseup; // r31
    unsigned char noBehind; // r27
    unsigned char forceCloseup; // r0
    unsigned char forceFar; // r0
    int numFocus; // r24
    class String s; // r1+0x4C
    class Symbol category; // r1+0x2C
    int distFlags; // r1+0x28
    int facingFlags; // r0
    class Symbol inst; // r1+0x24

    // References
    // -> class Game * TheGame;
    // -> static unsigned char sSoloMode;
    // -> static char * cats[8];
    // -> class Debug TheDebug;
    // -> class TaskMgr TheTaskMgr;
    // -> static class Symbol vocals;
    // -> static class Symbol guitar;
    // -> static class Symbol drum;
    // -> static class Symbol bass;
}

static class Symbol h2h_drum; // size: 0x4, address: 0x80A4E3BC
static class Symbol h2h_vocals; // size: 0x4, address: 0x80A4E3C4
// Range: 0x801F2584 -> 0x801F29E0
class DataNode OnGetH2HCameraFlags(class DataArray * data /* r24 */) {
    // Local variables
    class Symbol category; // r1+0x3C
    unsigned char drumsFocus; // r29
    unsigned char guitarFocus; // r28
    unsigned char vocalFocus; // r27
    unsigned char p1Focus; // r26
    unsigned char p2Focus; // r25
    int distFlags; // r1+0x38
    int facingFlags; // r0

    // References
    // -> const char * gNullStr;
    // -> static class Symbol h2h_vocals;
    // -> static class Symbol h2h_drum;
}

// Range: 0x801F29E0 -> 0x801F2A24
void * Jukebox::Jukebox(class Jukebox * const this /* r31 */) {}

// Range: 0x801F2A24 -> 0x801F2A3C
unsigned char __eq() {}

// Range: 0x801F2A3C -> 0x801F2C8C
class Symbol Jukebox::Pick(class Jukebox * const this /* r29 */, const class vector & valid_names /* r30 */) {
    // Local variables
    class vector valid; // r1+0x3C
    const class Symbol * i; // r31
    struct Item * item; // r5

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct LastPlayedCmp {
    // total size: 0x1
};
struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x801F2C8C -> 0x801F2CE8
unsigned char Jukebox::HasPlayed(const class Jukebox * const this /* r31 */) {
    // Local variables
    const struct Item * i; // r0
}

// Range: 0x801F2CE8 -> 0x801F2D68
void Jukebox::Play(class Jukebox * const this /* r30 */, class Symbol & item /* r31 */) {
    // Local variables
    struct Item * i; // r0
}

// Range: 0x801F2D68 -> 0x801F2E54
void Jukebox::AddItem(class Jukebox * const this /* r31 */) {
    // Local variables
    struct Item new_item; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ27Jukebox4Item; // size: 0x8, address: 0x808A8178

