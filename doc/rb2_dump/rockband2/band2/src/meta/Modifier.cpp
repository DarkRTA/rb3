/*
    Compile unit: C:\rockband2\band2\src\meta\Modifier.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8011D294 -> 0x8011D7C4
*/
class Modifier {
    // total size: 0x4
    class DataArray * mData; // offset 0x0, size 0x4
};
// Range: 0x8011D294 -> 0x8011D2F8
void * Modifier::Modifier(class Modifier * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011D2F8 -> 0x8011D340
class Symbol Modifier::GetSymbol() {
    // Local variables
    class Symbol sym; // r1+0x10
}

// Range: 0x8011D340 -> 0x8011D3B0
char * Modifier::GetName() {
    // Local variables
    const char * str; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011D3B0 -> 0x8011D444
char * Modifier::GetDescription() {
    // Local variables
    class Symbol sym; // r1+0x10
    const char * str; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8011D444 -> 0x8011D4D8
char * Modifier::GetHowToObtain() {
    // Local variables
    class Symbol sym; // r1+0x10
    const char * str; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol hidden; // size: 0x4, address: 0x80A4BA7C
// Range: 0x8011D4D8 -> 0x8011D57C
unsigned char Modifier::IsHidden(const class Modifier * const this /* r31 */) {
    // Local variables
    unsigned char bFound; // r31

    // References
    // -> static class Symbol hidden;
}

static class Symbol unlocked; // size: 0x4, address: 0x80A4BA84
// Range: 0x8011D57C -> 0x8011D620
unsigned char Modifier::AlwaysUnlocked(const class Modifier * const this /* r31 */) {
    // Local variables
    unsigned char bFound; // r31

    // References
    // -> static class Symbol unlocked;
}

// Range: 0x8011D620 -> 0x8011D68C
class DataArray * Modifier::GetDisabledFeatures(const class Modifier * const this /* r31 */) {
    // Local variables
    class DataArray * disabled; // r31
}

// Range: 0x8011D68C -> 0x8011D728
void Modifier::ExecuteActivateScript(const class Modifier * const this /* r31 */) {
    // Local variables
    class DataArray * script; // r4
}

// Range: 0x8011D728 -> 0x8011D7C4
void Modifier::ExecuteDeactivateScript(const class Modifier * const this /* r31 */) {
    // Local variables
    class DataArray * script; // r4
}


