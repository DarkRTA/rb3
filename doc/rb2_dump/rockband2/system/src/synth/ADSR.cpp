/*
    Compile unit: C:\rockband2\system\src\synth\ADSR.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80568F68 -> 0x8056938C
*/
static float gDecayRate[16]; // size: 0x40, address: 0x808498E0
static float gSustainLevel[16]; // size: 0x40, address: 0x80849920
static float gReleaseRateLin[32]; // size: 0x80, address: 0x80849960
static float gReleaseRateExp[32]; // size: 0x80, address: 0x808499E0
static float gLinInc[128]; // size: 0x200, address: 0x80849A60
static float gLinDec[128]; // size: 0x200, address: 0x80849C60
static float gExpInc[128]; // size: 0x200, address: 0x80849E60
static float gExpDec[128]; // size: 0x200, address: 0x8084A060
// Range: 0x80568F68 -> 0x80568F80
void * Ps2ADSR::Ps2ADSR() {}

// Range: 0x80568F80 -> 0x80568F94
void Ps2ADSR::SetAttackMode() {}

// Range: 0x80568F94 -> 0x80568FA8
void Ps2ADSR::SetSustainMode() {}

// Range: 0x80568FA8 -> 0x80568FC0
void Ps2ADSR::SetReleaseMode() {}

// Range: 0x80568FC0 -> 0x80568FCC
enum AttackMode Ps2ADSR::GetAttackMode() {}

// Range: 0x80568FCC -> 0x80568FD8
enum SustainMode Ps2ADSR::GetSustainMode() {}

// Range: 0x80568FD8 -> 0x80568FE4
enum ReleaseMode Ps2ADSR::GetReleaseMode() {}

// Range: 0x80568FE4 -> 0x805690E0
void Ps2ADSR::Set(class Ps2ADSR * const this /* r30 */, const class ADSR & adsr /* r31 */) {}

struct __less_2 {
    // total size: 0x1
};
// Range: 0x805690E0 -> 0x80569138
int Ps2ADSR::NearestAttackRate(float ar /* f31 */) {
    // Local variables
    const float * table; // r3
    int tableSize; // r4

    // References
    // -> static float gExpInc[128];
    // -> static float gLinInc[128];
}

// Range: 0x80569138 -> 0x80569148
int Ps2ADSR::NearestDecayRate() {
    // References
    // -> static float gDecayRate[16];
}

// Range: 0x80569148 -> 0x805691EC
int Ps2ADSR::NearestSustainRate(const class Ps2ADSR * const this /* r30 */, float sr /* f31 */) {
    // Local variables
    const float * table; // r3
    int tableSize; // r4

    // References
    // -> static float gLinDec[128];
    // -> static float gExpDec[128];
    // -> static float gExpInc[128];
    // -> static float gLinInc[128];
}

// Range: 0x805691EC -> 0x80569244
int Ps2ADSR::NearestReleaseRate(float rr /* f31 */) {
    // Local variables
    const float * table; // r3
    int tableSize; // r4

    // References
    // -> static float gReleaseRateExp[32];
    // -> static float gReleaseRateLin[32];
}

// Range: 0x80569244 -> 0x80569254
int Ps2ADSR::NearestSustainLevel() {
    // References
    // -> static float gSustainLevel[16];
}

// Range: 0x80569254 -> 0x805692CC
void * ADSR::ADSR(class ADSR * const this /* r30 */) {}

// Range: 0x805692CC -> 0x805692D4
float ADSR::GetAttackRate() {}

// Range: 0x805692D4 -> 0x805692DC
float ADSR::GetDecayRate() {}

// Range: 0x805692DC -> 0x805692E4
float ADSR::GetSustainRate() {}

// Range: 0x805692E4 -> 0x805692EC
float ADSR::GetSustainLevel() {}

// Range: 0x805692EC -> 0x805692F4
float ADSR::GetReleaseRate() {}

// Range: 0x805692F4 -> 0x805692FC
enum AttackMode ADSR::GetAttackMode() {}

// Range: 0x805692FC -> 0x80569304
enum SustainMode ADSR::GetSustainMode() {}

// Range: 0x80569304 -> 0x8056930C
enum ReleaseMode ADSR::GetReleaseMode() {}

// Range: 0x8056930C -> 0x80569354
void ADSR::SyncPacked(class ADSR * const this /* r31 */) {}

// Range: 0x80569354 -> 0x8056938C
class BinStream & __rs(class BinStream & s /* r31 */) {}


