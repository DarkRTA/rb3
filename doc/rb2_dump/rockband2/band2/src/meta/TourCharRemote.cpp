/*
    Compile unit: C:\rockband2\band2\src\meta\TourCharRemote.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801D14D0 -> 0x801D3908
*/
// Range: 0x801D14D0 -> 0x801D1544
class TourCharRemote * TourCharRemote::Create(class DataArray * char_data /* r29 */, unsigned char patches /* r30 */) {}

static class Symbol name; // size: 0x4, address: 0x80A4DC9C
static class Symbol hometown; // size: 0x4, address: 0x80A4DCA4
static class Symbol money; // size: 0x4, address: 0x80A4DCAC
static class Symbol gender; // size: 0x4, address: 0x80A4DCB4
static class Symbol attitude; // size: 0x4, address: 0x80A4DCBC
static class Symbol skin_color_index; // size: 0x4, address: 0x80A4DCC4
static class Symbol eye_color_index; // size: 0x4, address: 0x80A4DCCC
static class Symbol eyebrow_color_index; // size: 0x4, address: 0x80A4DCD4
static class Symbol height; // size: 0x4, address: 0x80A4DCDC
static class Symbol weight; // size: 0x4, address: 0x80A4DCE4
static class Symbol outfit; // size: 0x4, address: 0x80A4DCEC
static class Symbol colors; // size: 0x4, address: 0x80A4DCF4
static class Symbol tattoo_prefab; // size: 0x4, address: 0x80A4DCFC
// Range: 0x801D1544 -> 0x801D2C68
void * TourCharRemote::TourCharRemote(class TourCharRemote * const this /* r26 */, class DataArray * data /* r25 */) {
    // Local variables
    int size; // r1+0x90
    class BufStream b; // r1+0x244
    class String tmp_name; // r1+0x238
    class Symbol tmp_hometown; // r1+0x8C
    int tmp_money; // r1+0x88
    class Symbol tmp_gender; // r1+0x84
    int tmp_attitude; // r1+0x80
    int tmp_skin; // r1+0x7C
    int tmp_eye; // r1+0x78
    int tmp_eyebrow; // r1+0x74
    float tmp_height; // r1+0x70
    float tmp_weight; // r1+0x6C
    int i; // r30
    int num_outfits; // r1+0x68
    class DataArray * o; // r29
    int i; // r28
    class Symbol category; // r1+0x64
    class Symbol selected; // r1+0x60
    unsigned int num_colors; // r1+0x5C
    class DataArray * c; // r27
    int color; // r1+0x58
    int j; // r25
    class Symbol tatName; // r1+0x54
    int i; // r25
    int diff; // r1+0x50

    // References
    // -> static class Symbol tattoo_prefab;
    // -> static class Symbol colors;
    // -> static class Symbol outfit;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> static class Symbol weight;
    // -> static class Symbol height;
    // -> static class Symbol eyebrow_color_index;
    // -> static class Symbol eye_color_index;
    // -> static class Symbol skin_color_index;
    // -> static class Symbol attitude;
    // -> static class Symbol gender;
    // -> static class Symbol money;
    // -> static class Symbol hometown;
    // -> static class Symbol name;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__14TourCharRemote;
}

// Range: 0x801D2C68 -> 0x801D2D38
void * TourCharRemote::~TourCharRemote(class TourCharRemote * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__14TourCharRemote;
}

static class Symbol money; // size: 0x4, address: 0x80A4DD04
// Range: 0x801D2D38 -> 0x801D2E20
void TourCharRemote::Update(class TourCharRemote * const this /* r30 */, class DataArray * data /* r31 */) {
    // References
    // -> static class Symbol money;
}

static class Symbol name; // size: 0x4, address: 0x80A4DD0C
// Range: 0x801D2E20 -> 0x801D2EDC
void TourCharRemote::SetCharName(class TourCharRemote * const this /* r30 */, const char * charName /* r31 */) {
    // References
    // -> static class Symbol name;
}

// Range: 0x801D2EDC -> 0x801D2F80
void TourCharRemote::SetTourWinDiff(class TourCharRemote * const this /* r29 */, enum ControllerType ct /* r30 */, enum Difficulty diff /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol outfit; // size: 0x4, address: 0x80A4DD14
static class Symbol colors; // size: 0x4, address: 0x80A4DD1C
// Range: 0x801D2F80 -> 0x801D33A0
void TourCharRemote::SaveRemote(class TourCharRemote * const this /* r29 */, class DataArray * dest /* r30 */) {
    // Local variables
    class MemStream m; // r1+0x70
    class DataArray * o; // r27
    int i; // r26
    class DataArray * c; // r28
    int i; // r25
    class DataArray * tat; // r25
    int i; // r25

    // References
    // -> static class Symbol colors;
    // -> static class Symbol outfit;
}

static class Symbol name; // size: 0x4, address: 0x80A4DD24
// Range: 0x801D33A0 -> 0x801D3418
char * TourCharRemote::CharName(const class TourCharRemote * const this /* r31 */) {
    // References
    // -> static class Symbol name;
}

// Range: 0x801D3418 -> 0x801D3428
char * TourCharRemote::DebugName() {}

static class Symbol hometown; // size: 0x4, address: 0x80A4DD2C
// Range: 0x801D3428 -> 0x801D34A4
class Symbol TourCharRemote::Hometown(const class TourCharRemote * const this /* r31 */) {
    // References
    // -> static class Symbol hometown;
}

static class Symbol money; // size: 0x4, address: 0x80A4DD34
// Range: 0x801D34A4 -> 0x801D351C
int TourCharRemote::Money(const class TourCharRemote * const this /* r31 */) {
    // References
    // -> static class Symbol money;
}

// Range: 0x801D351C -> 0x801D3908
class DataNode TourCharRemote::Handle(class TourCharRemote * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x90
} __vt__14TourCharRemote; // size: 0x90, address: 0x808A44C0

