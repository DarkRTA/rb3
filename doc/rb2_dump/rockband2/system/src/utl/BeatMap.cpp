/*
    Compile unit: C:\rockband2\system\src\utl\BeatMap.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805FF984 -> 0x805FFE1C
*/
static class BeatMap gDefaultBeatMap; // size: 0xC, address: 0x809897BC
class BeatMap * TheBeatMap; // size: 0x4, address: 0x80A47A78
// Range: 0x805FF984 -> 0x805FF98C
void SetTheBeatMap() {
    // References
    // -> class BeatMap * TheBeatMap;
}

// Range: 0x805FF98C -> 0x805FF99C
void ResetTheBeatMap() {
    // References
    // -> class BeatMap * TheBeatMap;
    // -> static class BeatMap gDefaultBeatMap;
}

// Range: 0x805FF99C -> 0x805FF9B8
unsigned char BeatInfoCmp() {}

// Range: 0x805FF9B8 -> 0x805FF9CC
void * BeatMap::BeatMap() {}

// Range: 0x805FF9CC -> 0x805FFA74
unsigned char BeatMap::AddBeat() {}

// Range: 0x805FFA74 -> 0x805FFB50
float BeatMap::Beat(const class BeatMap * const this /* r31 */, int tick /* r1+0x8 */) {
    // Local variables
    int idx; // r5
}

// Range: 0x805FFB50 -> 0x805FFC30
float BeatMap::BeatToTick() {
    // Local variables
    int idx; // r6
}

// Range: 0x805FFC30 -> 0x805FFC98
int BeatMap::IsDownbeat() {}

// Range: 0x805FFC98 -> 0x805FFD14
float BeatMap::Interpolate() {}

struct {
    // total size: 0x8
} __RTTI__P8BeatInfo; // size: 0x8, address: 0x8092AF48
// Range: 0x805FFD14 -> 0x805FFD5C
static void __sinit_\BeatMap_cpp() {
    // References
    // -> static class BeatMap gDefaultBeatMap;
}


