/*
    Compile unit: C:\rockband2\system\src\bandobj\OutfitConfig.h
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80292E10 -> 0x80293828
*/
// Range: 0x80292E10 -> 0x80293064
void ColorPalette::Load(class ColorPalette * const this /* r31 */, class BinStream & d /* r29 */) {
    // Local variables
    int rev; // r1+0x38
    class vector old_colors; // r1+0x3C
    struct ColorSet * i; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80293064 -> 0x802930A8
class Symbol ColorPalette::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x802930A8 -> 0x80293154
void ColorPalette::Copy(class ColorPalette * const this /* r29 */, enum CopyType type /* r30 */) {
    // Local variables
    const class ColorPalette * c; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12ColorPalette;
}

// Range: 0x80293154 -> 0x802933FC
class DataNode ColorPalette::Handle(class ColorPalette * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

// Range: 0x802933FC -> 0x8029345C
class Object * ColorPalette::NewObject() {
    // References
    // -> class Symbol name;
}

// Range: 0x8029345C -> 0x802934D0
class Object * OutfitConfig::NewObject() {
    // References
    // -> class Symbol name;
}

// Range: 0x802934D0 -> 0x80293514
class Symbol OutfitConfig::ClassName() {
    // References
    // -> class Symbol name;
}

// Range: 0x80293514 -> 0x802936A8
void OutfitConfig::SetType(class OutfitConfig * const this /* r29 */, class Symbol & OutfitConfig /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}

// Range: 0x802936A8 -> 0x80293828
void ColorPalette::SetType(class ColorPalette * const this /* r29 */, class Symbol & ColorPalette /* r30 */) {
    // Local variables
    class DataArray * def; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> class DataArray * types;
    // -> class Symbol name;
}


