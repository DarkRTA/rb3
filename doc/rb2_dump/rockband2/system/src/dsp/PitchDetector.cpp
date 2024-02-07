/*
    Compile unit: C:\rockband2\system\src\dsp\PitchDetector.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803B9E14 -> 0x803BA458
*/
// Range: 0x803B9E14 -> 0x803B9ED8
void * PitchDetector::PitchDetector(class PitchDetector * const this /* r31 */) {
    // Local variables
    float B[5]; // r1+0x1C
    float A[5]; // r1+0x8
}

// Range: 0x803B9ED8 -> 0x803B9F48
void * PitchDetector::~PitchDetector(class PitchDetector * const this /* r30 */) {}

// Range: 0x803B9F48 -> 0x803BA2E0
void PitchDetector::AnalyzeBlock(class PitchDetector * const this /* r22 */, signed short * data /* r23 */, int size /* r24 */, float & pitch /* r25 */, float & energy /* r26 */) {
    // Local variables
    int residual; // r7
    int dec_size; // r30
    int n; // r29
    float prev_ss; // f31
    int overlap; // r28
    float ss_offset; // f1
    int trim; // r0
    int i; // r28
    int beg_n; // r27
    float val; // f0
    int int_period; // r0
    float freq; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803BA2E0 -> 0x803BA458
void PitchDetector::SetSampleRate(class PitchDetector * const this /* r31 */, int samplesPerSec /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}


