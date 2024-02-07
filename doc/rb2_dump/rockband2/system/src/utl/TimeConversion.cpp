/*
    Compile unit: C:\rockband2\system\src\utl\TimeConversion.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80624848 -> 0x80624B48
*/
// Range: 0x80624848 -> 0x806248A0
static class DataNode OnSecondsToBeat(class DataArray * msg /* r31 */) {}

// Range: 0x806248A0 -> 0x806248F8
static class DataNode OnBeatToSeconds(class DataArray * msg /* r31 */) {}

// Range: 0x806248F8 -> 0x80624950
static class DataNode OnBeatToMs(class DataArray * msg /* r31 */) {}

// Range: 0x80624950 -> 0x806249A8
static class DataNode OnMsToTick(class DataArray * msg /* r31 */) {}

// Range: 0x806249A8 -> 0x80624A34
void TimeConversionInit() {}

// Range: 0x80624A34 -> 0x80624A48
float MsToTick() {
    // References
    // -> class TempoMap * TheTempoMap;
}

// Range: 0x80624A48 -> 0x80624A8C
float MsToBeat() {
    // References
    // -> class BeatMap * TheBeatMap;
    // -> class TempoMap * TheTempoMap;
}

// Range: 0x80624A8C -> 0x80624AA0
float TickToMs() {
    // References
    // -> class TempoMap * TheTempoMap;
}

// Range: 0x80624AA0 -> 0x80624AD8
float BeatToMs() {
    // References
    // -> class TempoMap * TheTempoMap;
    // -> class BeatMap * TheBeatMap;
}

// Range: 0x80624AD8 -> 0x80624AE0
float BeatToTick() {
    // References
    // -> class BeatMap * TheBeatMap;
}

// Range: 0x80624AE0 -> 0x80624AEC
float TickToBeat() {
    // References
    // -> class BeatMap * TheBeatMap;
}

// Range: 0x80624AEC -> 0x80624AF8
float SecondsToBeat() {}

// Range: 0x80624AF8 -> 0x80624B20
float TickToSeconds() {}

// Range: 0x80624B20 -> 0x80624B48
float BeatToSeconds() {}


