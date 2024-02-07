/*
    Compile unit: C:\rockband2\system\src\bandobj\BandTextComp.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802666C8 -> 0x802671B4
*/
// Range: 0x802666C8 -> 0x80266708
void * BandTextComp::~BandTextComp(class BandTextComp * const this /* r31 */) {}

// Range: 0x80266708 -> 0x8026675C
void BandTextComp::Copy() {
    // Local variables
    int i; // r7
}

static int TEXT_COMP_REV; // size: 0x4, address: 0x80A46AD8
static int gRev; // size: 0x4, address: 0x80A4F340
static class Symbol custom_colors; // size: 0x4, address: 0x80A4F348
// Range: 0x8026675C -> 0x802668CC
void BandTextComp::Load(class BandTextComp * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int seed; // r1+0x1C
    float delta_x; // r1+0x18
    float delta_z; // r1+0x14
    float delta_rot; // r1+0x10
    int count; // r1+0xC
    int i; // r31

    // References
    // -> static class Symbol custom_colors;
    // -> class Debug TheDebug;
    // -> static int TEXT_COMP_REV;
    // -> static int gRev;
}

static class Symbol custom_colors; // size: 0x4, address: 0x80A4F350
static class DataArray * allPresets; // size: 0x4, address: 0x80A4F354
// Range: 0x802668CC -> 0x802669B0
void BandTextComp::SetColorPreset(class BandTextComp * const this /* r29 */) {
    // Local variables
    class DataArray * preset; // r31
    int i; // r30

    // References
    // -> static class DataArray * allPresets;
    // -> class UIManager TheUI;
    // -> static class Symbol custom_colors;
}

static class Symbol custom_colors; // size: 0x4, address: 0x80A4F35C
// Range: 0x802669B0 -> 0x80266A28
void BandTextComp::SetColorProp(class BandTextComp * const this /* r29 */, enum State state /* r30 */, int val /* r31 */) {
    // References
    // -> static class Symbol custom_colors;
}

static class Symbol custom_colors; // size: 0x4, address: 0x80A4F364
// Range: 0x80266A28 -> 0x80266B9C
void BandTextComp::GetStateColor(class BandTextComp * const this /* r29 */, enum State state /* r30 */, class Color & c /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> static class Symbol custom_colors;
}

static class DataArray * allPresets; // size: 0x4, address: 0x80A4F368
static class Symbol default_colors; // size: 0x4, address: 0x80A4F370
// Range: 0x80266B9C -> 0x80266D30
int BandTextComp::LookupStatePresetColor(class BandTextComp * const this /* r28 */, int state /* r29 */, class DataArray * preset /* r30 */) {
    // References
    // -> const char * kAssertStr;
    // -> static class Symbol default_colors;
    // -> class Debug TheDebug;
    // -> static class DataArray * allPresets;
    // -> class UIManager TheUI;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F378
static class Symbol _s; // size: 0x4, address: 0x80A4F380
static class Symbol _s; // size: 0x4, address: 0x80A4F388
static class Symbol _s; // size: 0x4, address: 0x80A4F390
static class Symbol _s; // size: 0x4, address: 0x80A4F398
static class Symbol _s; // size: 0x4, address: 0x80A4F3A0
// Range: 0x80266D30 -> 0x802671B4
unsigned char BandTextComp::SyncProperty(class BandTextComp * const this /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r27 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x10
} __vt__12BandTextComp; // size: 0x10, address: 0x808B8150

