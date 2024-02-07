/*
    Compile unit: C:\rockband2\system\src\stlport\stl\_algobase.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8062571C -> 0x80625F90
*/
// Range: 0x8062571C -> 0x806258B0
void WaveFile::ReadFormat(class WaveFile * const this /* r30 */) {
    // Local variables
    const class ChunkHeader * chunk; // r0
    class IDataChunk formatChunk; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ChunkID kWaveFormatChunkID;
}

// Range: 0x806258B0 -> 0x80625F90
void WaveFile::ReadMarkers(class WaveFile * const this /* r30 */) {
    // Local variables
    class vector cues; // r1+0xE8
    class vector labels; // r1+0xDC
    int numCuePoints; // r1+0xB0
    int i; // r31
    const class ChunkHeader * chunk; // r0
    class IDataChunk cueChunk; // r1+0x158
    int id; // r1+0xAC
    int frame; // r1+0xA8
    class IListChunk adtlList; // r1+0x12C
    class IDataChunk lablChunk; // r1+0x108
    int len; // r29
    int id; // r1+0xA4
    class String str; // r1+0xD0
    int j; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ChunkID kWaveLabelChunkID;
    // -> class ChunkID kWaveAdditionalChunkID;
    // -> class ChunkID kWaveCueChunkID;
}


