/*
    Compile unit: C:\rockband2\system\src\synth\RateTables.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8056938C -> 0x80569830
*/
// Range: 0x8056938C -> 0x80569408
void Ps2ADSR::SetAttackRate(class Ps2ADSR * const this /* r30 */, unsigned int rate /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80569408 -> 0x80569484
void Ps2ADSR::SetDecayRate(class Ps2ADSR * const this /* r30 */, unsigned int rate /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80569484 -> 0x80569500
void Ps2ADSR::SetSustainRate(class Ps2ADSR * const this /* r30 */, unsigned int rate /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80569500 -> 0x80569578
void Ps2ADSR::SetSustainLevel(class Ps2ADSR * const this /* r30 */, unsigned int level /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80569578 -> 0x805695F0
void Ps2ADSR::SetReleaseRate(class Ps2ADSR * const this /* r30 */, unsigned int rate /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805695F0 -> 0x8056970C
static int FindNearestInTable(const float * table /* r30 */, int tableSize /* r31 */, float val /* r1+0x8 */) {
    // Local variables
    const float * end; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8056970C -> 0x80569830
void ADSR::Load(class ADSR * const this /* r30 */, class BinStream & s /* r31 */) {
    // Local variables
    int rev; // r1+0xC
    int tmp; // r1+0x8

    // References
    // -> class Debug TheDebug;
}


