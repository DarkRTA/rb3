/*
    Compile unit: C:\rockband2\band2\src\game\VocalScorer.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800A3328 -> 0x800A37E8
*/
// Range: 0x800A3328 -> 0x800A33EC
void * VocalScorer::~VocalScorer(class VocalScorer * const this /* r29 */) {}

// Range: 0x800A33EC -> 0x800A3784
float VocalScorer::ScoreFrame(class VocalScorer * const this /* r29 */, float ms /* f27 */, struct SpeechAnalysis * pMicAnalysis /* r30 */) {
    // Local variables
    struct SpeechAnalysis refAnalyses[8]; // r1+0x318
    int refCount; // r1+0xC
    float phonemeScore; // f31
    float warpingScore; // f30
    float sequencScore; // f29
    float transitScore; // f28
    double scoreSum; // f26
    double scoreWeight; // f25
    char refergs[256]; // r1+0x218
    char micergs[256]; // r1+0x118
    unsigned char energies[8]; // r1+0x10
    int numerg; // r0
    int ii; // r30
    int ii; // r30
    char buffer[256]; // r1+0x18
}

// Range: 0x800A3784 -> 0x800A378C
unsigned char VocalScorer::IsLastRefVoiced() {}

// Range: 0x800A378C -> 0x800A37E8
unsigned char VocalScorer::IsLastCorrectUnvoiced(class VocalScorer * const this /* r30 */) {}


