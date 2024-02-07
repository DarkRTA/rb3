/*
    Compile unit: C:\rockband2\system\src\utl\MeasureMap.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x806117BC -> 0x80611C38
*/
// Range: 0x806117BC -> 0x80611878
void * MeasureMap::MeasureMap(class MeasureMap * const this /* r31 */) {
    // Local variables
    class TimeSigChange sig; // r1+0x10
}

// Range: 0x80611878 -> 0x8061191C
int MeasureMap::MeasureBeatTickToTick(const class MeasureMap * const this /* r29 */, int measure /* r1+0x8 */, int beat /* r30 */, int tick /* r31 */) {
    // Local variables
    const class TimeSigChange * it; // r3
}

// Range: 0x8061191C -> 0x80611940
void MeasureMap::TickToMeasureBeatTick() {
    // Local variables
    int unused; // r1+0x8
}

// Range: 0x80611940 -> 0x80611A28
void MeasureMap::TickToMeasureBeatTick(const class MeasureMap * const this /* r27 */, int tick /* r1+0x8 */, int & oMeasure /* r28 */, int & oBeat /* r29 */, int & oTick /* r30 */, int & oBeatsPerMeasure /* r31 */) {
    // Local variables
    const class TimeSigChange * it; // r3
    int ticks_per_measure; // r6
    int ticks_passed; // r7
    int measures_passed; // r8
    int beats_passed; // r4
}

// Range: 0x80611A28 -> 0x80611C00
void MeasureMap::AddTimeSignature(class MeasureMap * const this /* r29 */, int measure /* r26 */, int num /* r30 */, int denom /* r31 */) {
    // Local variables
    class TimeSigChange sig; // r1+0x30
    int measures_passed; // r27
    int this_tick; // r0
    class TimeSigChange this_sig; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80611C00 -> 0x80611C1C
unsigned char MeasureMap::CompareTick() {}

// Range: 0x80611C1C -> 0x80611C38
unsigned char MeasureMap::CompareMeasure() {}

struct {
    // total size: 0x8
} __RTTI__PQ210MeasureMap13TimeSigChange; // size: 0x8, address: 0x8092D3A8

