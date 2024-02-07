/*
    Compile unit: C:\rockband2\system\src\rndobj\ColorXfm.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80477F5C -> 0x804786A0
*/
// Range: 0x80477F5C -> 0x80477FE8
void * RndColorXfm::RndColorXfm(class RndColorXfm * const this /* r31 */) {}

// Range: 0x80477FE8 -> 0x80478024
void RndColorXfm::Reset() {}

// Range: 0x80478024 -> 0x804780D8
void RndColorXfm::AdjustLightness() {
    // Local variables
    class Transform xfm; // r1+0x10
    float p; // f0
    float scale; // f0
    float offset; // f3
}

// Range: 0x804780D8 -> 0x804781A4
void RndColorXfm::AdjustContrast() {
    // Local variables
    class Transform xfm; // r1+0x10
    float p; // f1
    float scale; // f2
    float ooScale; // f0
    float offset; // f0
}

// Range: 0x804781A4 -> 0x80478240
void RndColorXfm::AdjustBrightness() {
    // Local variables
    class Transform xfm; // r1+0x10
    float p; // f1
    float offset; // f0
}

// Range: 0x80478240 -> 0x804783B8
void RndColorXfm::AdjustLevels() {
    // Local variables
    class Vector3 kDelIn; // r1+0x30
    class Vector3 kS; // r1+0x20
    class Vector3 kO; // r1+0x10
    class Transform xfm; // r1+0x40
}

// Range: 0x804783B8 -> 0x80478434
void RndColorXfm::AdjustColorXfm(class RndColorXfm * const this /* r31 */) {}

// Range: 0x80478434 -> 0x804786A0
unsigned char RndColorXfm::Load(class RndColorXfm * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x8
}


