/*
    Compile unit: C:\rockband2\band2\src\game\Defines.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8004FB94 -> 0x800501B0
*/
// Range: 0x8004FB94 -> 0x8004FBF0
class Symbol TrackTypeToSym(enum TrackType t /* r30 */) {}

static class Symbol track_symbols[5]; // size: 0x14, address: 0x80976E30
// Range: 0x8004FBF0 -> 0x8004FCE8
enum TrackType SymToTrackType(class Symbol & s /* r29 */) {
    // Local variables
    int i; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol track_symbols[5];
}

enum GameCoopSlot {
    kGameCoopSlotGuitar0 = 0,
    kGameCoopSlotDrum = 1,
    kGameCoopSlotVocals = 2,
    kGameCoopSlotGuitar1 = 3,
    kGameCoopNumSlots = 4,
};
// Range: 0x8004FCE8 -> 0x8004FD38
enum GameCoopSlot TrackTypeToGameCoopSlot() {}

// Range: 0x8004FD38 -> 0x8004FDDC
class Symbol ControllerTypeToSym(enum ControllerType controllerType /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8004FDDC -> 0x8004FE74
enum ControllerType SymToControllerType(class Symbol & instrument /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8004FE74 -> 0x8004FEB0
enum ControllerType TrackTypeToControllerType() {}

// Range: 0x8004FEB0 -> 0x8004FEF4
enum TrackType ControllerTypeToTrackType() {}

// Range: 0x8004FEF4 -> 0x8004FF88
enum Difficulty SymToDifficulty(class Symbol & s /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8004FF88 -> 0x8004FFF8
enum Difficulty DefaultDifficulty() {}

// Range: 0x8004FFF8 -> 0x80050054
class Symbol DifficultyToSym(enum Difficulty d /* r30 */) {}

// Range: 0x80050054 -> 0x800500CC
void CensorString(class String & toBeCensored /* r30 */) {
    // Local variables
    int n; // r31
}

static class Symbol score; // size: 0x4, address: 0x80A49444
static class Symbol stars; // size: 0x4, address: 0x80A4944C
static class Symbol streak; // size: 0x4, address: 0x80A49454
// Range: 0x800500CC -> 0x800501B0
class Symbol WinMetricToSym(enum WinMetric m /* r30 */) {
    // References
    // -> static class Symbol streak;
    // -> static class Symbol stars;
    // -> static class Symbol score;
}


