/*
    Compile unit: C:\rockband2\system\src\utl\MultiTempoTempoMap.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80619DAC -> 0x8061A2C8
*/
// Range: 0x80619DAC -> 0x80619DCC
void * MultiTempoTempoMap::MultiTempoTempoMap() {
    // References
    // -> struct [anonymous] __vt__18MultiTempoTempoMap;
}

// Range: 0x80619DCC -> 0x80619E40
float MultiTempoTempoMap::GetTempo() {}

// Range: 0x80619E40 -> 0x80619E74
float MultiTempoTempoMap::GetTempoBPM() {
    // Local variables
    float msPerBeat; // f0
}

// Range: 0x80619E74 -> 0x80619F18
float MultiTempoTempoMap::TickToTime(float tick /* f31 */) {
    // Local variables
    const struct TempoInfoPoint * it; // r0
}

// Range: 0x80619F18 -> 0x80619FB8
float MultiTempoTempoMap::TimeToTick(float time /* f31 */) {
    // Local variables
    const struct TempoInfoPoint * it; // r0
}

// Range: 0x80619FB8 -> 0x8061A014
void MultiTempoTempoMap::WipeTempoInfoPoints() {}

// Range: 0x8061A014 -> 0x8061A03C
int MultiTempoTempoMap::GetNumTempoChangePoints() {}

// Range: 0x8061A03C -> 0x8061A1C8
void MultiTempoTempoMap::Finalize(class MultiTempoTempoMap * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ218MultiTempoTempoMap14TempoInfoPoint;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ218MultiTempoTempoMap14TempoInfoPoint; // size: 0x8, address: 0x8092E080
// Range: 0x8061A1C8 -> 0x8061A204
unsigned char MultiTempoTempoMap::CompareTick() {}

// Range: 0x8061A204 -> 0x8061A218
unsigned char MultiTempoTempoMap::CompareTime() {}

// Range: 0x8061A218 -> 0x8061A2C8
struct TempoInfoPoint * MultiTempoTempoMap::PointForTime(const class MultiTempoTempoMap * const this /* r31 */, float time /* r1+0x8 */) {
    // Local variables
    const struct TempoInfoPoint * it; // r3

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x28
} __vt__18MultiTempoTempoMap; // size: 0x28, address: 0x8092E0A8
struct {
    // total size: 0x28
} __vt__8TempoMap; // size: 0x28, address: 0x8092E0F8

