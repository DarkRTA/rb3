/*
    Compile unit: C:\rockband2\system\src\dsp\VibratoDetector.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803BA458 -> 0x803BA818
*/
// Range: 0x803BA458 -> 0x803BA4CC
void * VibratoDetector::VibratoDetector(class VibratoDetector * const this /* r31 */) {}

// Range: 0x803BA4CC -> 0x803BA50C
void * VibratoDetector::~VibratoDetector(class VibratoDetector * const this /* r31 */) {}

// Range: 0x803BA50C -> 0x803BA67C
int VibratoDetector::Analyze(class VibratoDetector * const this /* r30 */) {
    // Local variables
    int vib_len; // r31
    float alpha; // f3
    int length; // r1+0xC
    int max_length; // r1+0x8
}

// Range: 0x803BA67C -> 0x803BA818
int VibratoDetector::Detect() {
    // Local variables
    int idx; // r0
    int last; // r8
    float last_pitch; // f2
    float diffs[4]; // r1+0x18
    float diffs_pitch[4]; // r1+0x8
    int d; // r4
    float total; // f3
    int i; // r9
    int cur; // r6
    float cur_pitch; // f4
    float diff; // f0
    float diff_pitch; // f0
    float ave; // f2
}


