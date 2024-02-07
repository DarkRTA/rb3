/*
    Compile unit: C:\rockband2\system\src\dsp\SndAnalysis.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803B99F8 -> 0x803B9DDC
*/
// Range: 0x803B99F8 -> 0x803B9A54
void ShiftedDotProduct() {
    // Local variables
    int vlen; // r6
    int p; // r7
    float ss; // f2
    int n; // r8
}

static float bonus_exp; // size: 0x4, address: 0x80A51740
// Range: 0x803B9A54 -> 0x803B9C78
int FindCCPeak(const float * dp_data /* r27 */, const float * ss_data /* r28 */) {
    // Local variables
    int n; // r31
    int vlen; // r30
    float bestcor; // r1+0xC
    int peaks[10]; // r1+0x60
    float cors[10]; // r1+0x38
    int num_peaks; // r29
    float norm; // r1+0x8
    float dp_ratio; // f0
    float goodness[10]; // r1+0x10

    // References
    // -> static float bonus_exp;
}

// Range: 0x803B9C78 -> 0x803B9DDC
float RefinePeriod2() {
    // Local variables
    int vlen; // r9
    float alpha; // f2
    int attempt; // r10
    float v1v1; // f3
    float v2v2; // f4
    float wv1; // f2
    float wv2; // f5
    float v1v2; // f6
    int n; // r11
}


