/*
    Compile unit: C:\rockband2\band2\src\game\CrowdRating.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8004F048 -> 0x8004F544
*/
// Range: 0x8004F048 -> 0x8004F090
void CrowdRating::Reset(class CrowdRating * const this /* r31 */) {}

// Range: 0x8004F090 -> 0x8004F098
void CrowdRating::Poll() {}

// Range: 0x8004F098 -> 0x8004F0A0
void CrowdRating::SetActive() {}

// Range: 0x8004F0A0 -> 0x8004F1B8
void CrowdRating::Update(class CrowdRating * const this /* r31 */, float noteScore /* f30 */, float noteWeight /* f31 */) {
    // Local variables
    float weight; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8004F1B8 -> 0x8004F2D0
void CrowdRating::UpdatePhrase(class CrowdRating * const this /* r31 */, float phraseHit /* f30 */, float phraseWeight /* f31 */) {
    // Local variables
    float weight; // f1

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8004F2D0 -> 0x8004F32C
float CrowdRating::GetThreshold() {}

// Range: 0x8004F32C -> 0x8004F3D8
enum ExcitementLevel CrowdRating::GetExcitement(const class CrowdRating * const this /* r31 */) {
    // Local variables
    float rating; // f0
}

// Range: 0x8004F3D8 -> 0x8004F48C
void CrowdRating::CalculateValue(class CrowdRating * const this /* r30 */) {
    // Local variables
    float value; // f31
}

// Range: 0x8004F48C -> 0x8004F4A4
unsigned char CrowdRating::IsInWarning() {}

// Range: 0x8004F4A4 -> 0x8004F4BC
unsigned char CrowdRating::IsBelowLoseLevel() {}

// Range: 0x8004F4BC -> 0x8004F4F0
void CrowdRating::SetValue() {
    // Local variables
    float dx; // f2
}

// Range: 0x8004F4F0 -> 0x8004F4F8
void CrowdRating::SetRawValue() {}

// Range: 0x8004F4F8 -> 0x8004F50C
void CrowdRating::SetDisplayValue() {}

// Range: 0x8004F50C -> 0x8004F528
float CrowdRating::GetDisplayValue() {}

// Range: 0x8004F528 -> 0x8004F544
unsigned char CrowdRating::CantFailYet() {}

struct {
    // total size: 0x10
} __vt__11CrowdRating; // size: 0x10, address: 0x80873848
struct {
    // total size: 0x8
} __RTTI__11CrowdRating; // size: 0x8, address: 0x80873868

