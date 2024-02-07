/*
    Compile unit: C:\rockband2\system\src\bandobj\CharDesc.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80268C38 -> 0x8026AAA8
*/
// Range: 0x80268C38 -> 0x80268CCC
void * CharDesc::CharDesc(class CharDesc * const this /* r30 */, class DataArray * char_data /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8CharDesc;
}

// Range: 0x80268CCC -> 0x80269218
void CharDesc::CheckData(class CharDesc * const this /* r27 */) {
    // Local variables
    class DataArray * outfits; // r30
    int i; // r29
    class Symbol category; // r1+0x88
    class DataArray * outfit; // r28
    class Symbol name; // r1+0x84

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80269218 -> 0x80269370
void CharDesc::CheckNotExcluded(class CharDesc * const this /* r25 */, class Symbol & category /* r26 */, class Symbol & outfit /* r27 */) {
    // Local variables
    class DataArray * outfits; // r29
    class DataArray * config; // r29
    class DataArray * exclude; // r29

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80269370 -> 0x802693E4
void * CharDesc::~CharDesc(class CharDesc * const this /* r30 */) {}

// Range: 0x802693E4 -> 0x802693F4
void CharDesc::AddRef() {}

// Range: 0x802693F4 -> 0x80269428
void CharDesc::Release() {}

// Range: 0x80269428 -> 0x80269430
class HxGuid & CharDesc::Guid() {}

// Range: 0x80269430 -> 0x80269440
char * CharDesc::DebugName() {}

// Range: 0x80269440 -> 0x80269448
char * CharDesc::CharName() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x80269448 -> 0x80269450
class DataArray * CharDesc::GetCharData() {}

static class Symbol gender; // size: 0x4, address: 0x80A4F3AC
// Range: 0x80269450 -> 0x802694CC
class Symbol CharDesc::GetGender(const class CharDesc * const this /* r31 */) {
    // References
    // -> static class Symbol gender;
}

static class Symbol valid; // size: 0x4, address: 0x80A4F3B4
// Range: 0x802694CC -> 0x80269568
unsigned char CharDesc::Valid(const class CharDesc * const this /* r30 */) {
    // Local variables
    class DataArray * d; // r30

    // References
    // -> static class Symbol valid;
}

static class Symbol attitude; // size: 0x4, address: 0x80A4F3BC
// Range: 0x80269568 -> 0x802695E0
int CharDesc::GetAttitude(const class CharDesc * const this /* r31 */) {
    // References
    // -> static class Symbol attitude;
}

static class Symbol outfit; // size: 0x4, address: 0x80A4F3C4
// Range: 0x802695E0 -> 0x80269684
class Symbol CharDesc::SelectedOutfit(const class CharDesc * const this /* r30 */, class Symbol & category /* r31 */) {
    // References
    // -> static class Symbol outfit;
}

static class Symbol skin_color_index; // size: 0x4, address: 0x80A4F3CC
// Range: 0x80269684 -> 0x802696FC
int CharDesc::SkinColor(const class CharDesc * const this /* r31 */) {
    // References
    // -> static class Symbol skin_color_index;
}

static class Symbol eye_color_index; // size: 0x4, address: 0x80A4F3D4
// Range: 0x802696FC -> 0x80269774
int CharDesc::EyeColor(const class CharDesc * const this /* r31 */) {
    // References
    // -> static class Symbol eye_color_index;
}

static class Symbol eyebrow_color_index; // size: 0x4, address: 0x80A4F3DC
// Range: 0x80269774 -> 0x802697EC
int CharDesc::EyebrowColor(const class CharDesc * const this /* r31 */) {
    // References
    // -> static class Symbol eyebrow_color_index;
}

static class Symbol height; // size: 0x4, address: 0x80A4F3E4
// Range: 0x802697EC -> 0x80269864
float CharDesc::Height(const class CharDesc * const this /* r31 */) {
    // References
    // -> static class Symbol height;
}

static class Symbol weight; // size: 0x4, address: 0x80A4F3EC
// Range: 0x80269864 -> 0x802698DC
float CharDesc::Weight(const class CharDesc * const this /* r31 */) {
    // References
    // -> static class Symbol weight;
}

// Range: 0x802698DC -> 0x8026993C
class Symbol CharDesc::TattooPrefab(const class CharDesc * const this /* r31 */) {
    // Local variables
    class DataArray * tattoo_data; // r31
}

// Range: 0x8026993C -> 0x80269B44
void CharDesc::ConfigureChar(class CharDesc * const this /* r27 */, class CompositeCharacter * cc /* r28 */) {
    // Local variables
    class DataArray * outs; // r30
    int i; // r29
    class Symbol category; // r1+0x38
    class Symbol selected; // r1+0x34
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80269B44 -> 0x80269CA4
void CharDesc::ConfigureOutfitColor(class CharDesc * const this /* r28 */, class CompositeCharacter * cc /* r29 */, class Symbol & category /* r30 */) {
    // Local variables
    class Symbol selected; // r1+0x24
    int i; // r31

    // References
    // -> const char * gNullStr;
}

static class Symbol colors; // size: 0x4, address: 0x80A4F3F4
static class Symbol outfit; // size: 0x4, address: 0x80A4F3FC
// Range: 0x80269CA4 -> 0x80269D90
int CharDesc::OutfitColor(const class CharDesc * const this /* r29 */, class Symbol & category /* r31 */, int idx /* r30 */) {
    // Local variables
    class DataArray * c; // r31

    // References
    // -> static class Symbol outfit;
    // -> static class Symbol colors;
}

// Range: 0x80269D90 -> 0x80269E3C
class Symbol CharDesc::Instrument(const class CharDesc * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80269E3C -> 0x80269ED0
void CharDesc::UpdatePref(class CompositeCharacter * cc /* r29 */, class Symbol & category /* r30 */, class Symbol & outfit /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80269ED0 -> 0x80269F78
unsigned int CharDesc::GetCategoryIndex(const class Symbol & category /* r28 */) {
    // Local variables
    const class DataArray * cats; // r30
    unsigned int i; // r29
}

// Range: 0x80269F78 -> 0x8026A08C
unsigned int CharDesc::GetOutfitIndex(const class Symbol & category /* r25 */, const class Symbol & outfit /* r26 */, unsigned int cat /* r27 */) {
    // Local variables
    const class DataArray * cats; // r30
    unsigned int i; // [invalid]
    class DataArray * outs; // r29
    unsigned int j; // r28
}

// Range: 0x8026A08C -> 0x8026A118
unsigned int CharDesc::GetAttitudeIndex() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8026A118 -> 0x8026A1A4
unsigned int CharDesc::GetTattooPrefabIndex(const class Symbol & name /* r29 */) {
    // Local variables
    const class DataArray * tats; // r31
    unsigned int i; // r30
}

// Range: 0x8026A1A4 -> 0x8026A1FC
unsigned int CharDesc::GetHeightIndex() {}

// Range: 0x8026A1FC -> 0x8026A200
unsigned int CharDesc::GetWeightIndex() {}

// Range: 0x8026A200 -> 0x8026A29C
class DataArray * CharDesc::OutfitCategories() {}

// Range: 0x8026A29C -> 0x8026A30C
class DataArray * CharDesc::TattooPrefabNames() {}

static class Symbol _s; // size: 0x4, address: 0x80A4F404
static class Symbol _s; // size: 0x4, address: 0x80A4F40C
static class Symbol _s; // size: 0x4, address: 0x80A4F414
static class Symbol _s; // size: 0x4, address: 0x80A4F41C
static class Symbol _s; // size: 0x4, address: 0x80A4F424
static class Symbol _s; // size: 0x4, address: 0x80A4F42C
// Range: 0x8026A30C -> 0x8026AAA8
class DataNode CharDesc::Handle(class CharDesc * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x4C
    class MessageTimer _mt; // r1+0x50

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__18CompositeCharacter;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x80
} __vt__8CharDesc; // size: 0x80, address: 0x808B8858

