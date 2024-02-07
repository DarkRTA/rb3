/*
    Compile unit: C:\rockband2\system\src\beatmatch\BeatMatchUtl.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802D5E70 -> 0x802D62CC
*/
// Range: 0x802D5E70 -> 0x802D5F84
unsigned char IsNumberAnywhereInArray(class DataArray * cfg /* r27 */, int num /* r28 */) {
    // Local variables
    int i; // r29
    class DataNode & node; // r0
}

// Range: 0x802D5F84 -> 0x802D5FAC
unsigned char GemPlayableBy() {}

static int gSlotsToNumSlots[32]; // size: 0x80, address: 0x808CA858
// Range: 0x802D5FAC -> 0x802D6058
int GemNumSlots(int slot_bitfield /* r30 */) {
    // Local variables
    int left; // [invalid]
    int bits; // r3
    int bit; // r4
    int mask; // r5

    // References
    // -> static int gSlotsToNumSlots[32];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802D6058 -> 0x802D6094
int ConsumeNumber() {
    // Local variables
    int num; // r6
    int digit; // r4
}

// Range: 0x802D6094 -> 0x802D619C
float VelocityBucketToDb(int bucket /* r29 */) {
    // Local variables
    class DataArray * audio; // r31
    class DataArray * map; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol drum; // size: 0x4, address: 0x80A505A4
static class Symbol guitar; // size: 0x4, address: 0x80A505AC
static class Symbol rhythm; // size: 0x4, address: 0x80A505B4
static class Symbol bass; // size: 0x4, address: 0x80A505BC
static class Symbol vocals; // size: 0x4, address: 0x80A505C4
// Range: 0x802D619C -> 0x802D62CC
enum BeatmatchTrackType InstrumentToTrackType(class Symbol & name /* r30 */) {
    // References
    // -> static class Symbol vocals;
    // -> static class Symbol bass;
    // -> static class Symbol rhythm;
    // -> static class Symbol guitar;
    // -> static class Symbol drum;
}


