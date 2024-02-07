/*
    Compile unit: C:\rockband2\system\src\synthwii\soundtouch\TDStretch.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80560B44 -> 0x80561A70
*/
int scanOffsets[4][24]; // size: 0x180, address: 0x80919BD0
// Range: 0x80560B44 -> 0x80560BE4
void * TDStretch::TDStretch(class TDStretch * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch9TDStretch;
}

// Range: 0x80560BE4 -> 0x80560C74
void * TDStretch::~TDStretch(class TDStretch * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__Q210soundtouch9TDStretch;
}

// Range: 0x80560C74 -> 0x80560CD8
static int _getClosest2Power(double value /* f30 */) {}

// Range: 0x80560CD8 -> 0x80560D50
void TDStretch::setParameters(class TDStretch * const this /* r31 */) {}

// Range: 0x80560D50 -> 0x80560D94
void TDStretch::getParameters() {}

// Range: 0x80560D94 -> 0x80560DDC
void TDStretch::overlapMono() {
    // Local variables
    int i; // r11
}

// Range: 0x80560DDC -> 0x80560E2C
void TDStretch::clearMidBuffer(class TDStretch * const this /* r31 */) {}

// Range: 0x80560E2C -> 0x80560E6C
void TDStretch::clearInput(class TDStretch * const this /* r31 */) {}

// Range: 0x80560E6C -> 0x80560EC0
void TDStretch::clear(class TDStretch * const this /* r31 */) {}

// Range: 0x80560EC0 -> 0x80560EC8
void TDStretch::enableQuickSeek() {}

// Range: 0x80560EC8 -> 0x80560F2C
unsigned int TDStretch::seekBestOverlapPosition() {}

// Range: 0x80560F2C -> 0x80560FCC
unsigned int TDStretch::seekBestOverlapPositionStereo(class TDStretch * const this /* r27 */, const signed short * refPos /* r28 */) {
    // Local variables
    unsigned int bestOffs; // r31
    long bestCorr; // r30
    long corr; // r3
    unsigned int i; // r29
}

// Range: 0x80560FCC -> 0x805610AC
unsigned int TDStretch::seekBestOverlapPositionStereoQuick(class TDStretch * const this /* r24 */, const signed short * refPos /* r25 */) {
    // Local variables
    unsigned int j; // r31
    unsigned int bestOffs; // r30
    long bestCorr; // r29
    long corr; // r3
    unsigned int scanCount; // r28
    unsigned int corrOffset; // r27
    unsigned int tempOffset; // r26

    // References
    // -> int scanOffsets[4][24];
}

// Range: 0x805610AC -> 0x8056114C
unsigned int TDStretch::seekBestOverlapPositionMono(class TDStretch * const this /* r27 */, const signed short * refPos /* r28 */) {
    // Local variables
    unsigned int bestOffs; // r31
    long bestCorr; // r30
    long corr; // r3
    unsigned int tempOffset; // r29
}

// Range: 0x8056114C -> 0x8056122C
unsigned int TDStretch::seekBestOverlapPositionMonoQuick(class TDStretch * const this /* r24 */, const signed short * refPos /* r25 */) {
    // Local variables
    unsigned int j; // r31
    unsigned int bestOffs; // r30
    long bestCorr; // r29
    long corr; // r3
    unsigned int scanCount; // r28
    unsigned int corrOffset; // r27
    unsigned int tempOffset; // r26

    // References
    // -> int scanOffsets[4][24];
}

// Range: 0x8056122C -> 0x80561230
void TDStretch::clearCrossCorrState() {}

// Range: 0x80561230 -> 0x805612B0
void TDStretch::setTempo() {
    // Local variables
    unsigned int intskip; // r0
}

// Range: 0x805612B0 -> 0x805612FC
void TDStretch::setChannels(class TDStretch * const this /* r31 */) {}

// Range: 0x805612FC -> 0x80561454
void TDStretch::processNominalTempo(class TDStretch * const this /* r30 */) {}

// Range: 0x80561454 -> 0x805616F4
void TDStretch::processSamples(class TDStretch * const this /* r31 */) {
    // Local variables
    unsigned int ovlSkip; // r4
    unsigned int offset; // r0
    int temp; // r28
}

// Range: 0x805616F4 -> 0x80561734
void TDStretch::putSamples(class TDStretch * const this /* r31 */) {}

// Range: 0x80561734 -> 0x805617C0
void TDStretch::acceptNewOverlapLength(class TDStretch * const this /* r31 */) {
    // Local variables
    unsigned int prevOvl; // r0
}

// Range: 0x805617C0 -> 0x8056182C
void TDStretch::precalcCorrReferenceStereo() {
    // Local variables
    int i; // r6
    int cnt2; // r7
    int temp; // r8
    int temp2; // r0
}

// Range: 0x8056182C -> 0x80561870
void TDStretch::precalcCorrReferenceMono() {
    // Local variables
    int i; // r7
}

// Range: 0x80561870 -> 0x805618E4
void TDStretch::overlapStereo() {
    // Local variables
    int i; // r10
    signed short temp; // r11
    unsigned int cnt2; // r12
}

// Range: 0x805618E4 -> 0x805619D4
void TDStretch::calculateOverlapLength(class TDStretch * const this /* r31 */) {
    // Local variables
    unsigned int newOvl; // r30
}

// Range: 0x805619D4 -> 0x80561A14
long TDStretch::calcCrossCorrMono() {
    // Local variables
    long corr; // r7
    unsigned int i; // r8
}

// Range: 0x80561A14 -> 0x80561A70
long TDStretch::calcCrossCorrStereo() {
    // Local variables
    long corr; // r9
    unsigned int i; // r10
}

struct {
    // total size: 0x4C
} __vt__Q210soundtouch9TDStretch; // size: 0x4C, address: 0x80919D50
struct {
    // total size: 0x8
} __RTTI__Q210soundtouch9TDStretch; // size: 0x8, address: 0x80919DC8

