/*
    Compile unit: C:\rockband2\system\src\bandobj\PlayerDiffIcon.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8029A25C -> 0x8029B8D4
*/
class DataArray * types; // size: 0x4, address: 0x80A4F9A0
class Symbol name; // size: 0x4, address: 0x80A4F9A8
// Range: 0x8029A25C -> 0x8029A390
void * PlayerDiffIcon::PlayerDiffIcon(class PlayerDiffIcon * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__14PlayerDiffIcon;
    // -> struct [anonymous] __vt__12ListAlphable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8029A390 -> 0x8029A4B0
void * PlayerDiffIcon::~PlayerDiffIcon(class PlayerDiffIcon * const this /* r30 */) {}

static int gRev; // size: 0x4, address: 0x80A4F9AC
// Range: 0x8029A4B0 -> 0x8029A538
void PlayerDiffIcon::Save(class PlayerDiffIcon * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8029A538 -> 0x8029A594
void PlayerDiffIcon::Load(class PlayerDiffIcon * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x8029A594 -> 0x8029A678
void PlayerDiffIcon::PreLoad(class PlayerDiffIcon * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8029A678 -> 0x8029A6B8
void PlayerDiffIcon::PostLoad(class PlayerDiffIcon * const this /* r31 */) {}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class UILabel * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x8029A6B8 -> 0x8029ADC4
void PlayerDiffIcon::DrawShowing(class PlayerDiffIcon * const this /* r30 */) {
    // Local variables
    int i; // r29
    int i; // r5
    class ObjDirItr l; // r1+0x3C
    class ObjDirItr m; // r1+0x28

    // References
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8029ADC4 -> 0x8029ADD4
class RndDrawable * PlayerDiffIcon::CollideShowing() {}

// Range: 0x8029ADD4 -> 0x8029ADEC
int PlayerDiffIcon::CollidePlane() {}

// Range: 0x8029ADEC -> 0x8029ADF4
void PlayerDiffIcon::SetAlpha() {}

// Range: 0x8029ADF4 -> 0x8029AE00
void PlayerDiffIcon::SetNumPlayersDiff() {}

static class Symbol player_meshes; // size: 0x4, address: 0x80A4F9B4
static class Symbol player_mat; // size: 0x4, address: 0x80A4F9BC
static class Symbol no_player_mat; // size: 0x4, address: 0x80A4F9C4
static class Symbol diff_labels; // size: 0x4, address: 0x80A4F9CC
// Range: 0x8029AE00 -> 0x8029B390
void PlayerDiffIcon::Update(class PlayerDiffIcon * const this /* r28 */) {
    // Local variables
    class ObjectDir * dir; // r29
    class DataArray * meshes; // r25
    int i; // r24
    class DataArray * labels; // r24
    int i; // r25

    // References
    // -> struct [anonymous] __RTTI__9BandLabel;
    // -> static class Symbol diff_labels;
    // -> static class Symbol no_player_mat;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> static class Symbol player_mat;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> static class Symbol player_meshes;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8029B390 -> 0x8029B65C
class DataNode PlayerDiffIcon::Handle(class PlayerDiffIcon * const this /* r31 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r28 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A4F9D4
static class Symbol _s; // size: 0x4, address: 0x80A4F9DC
// Range: 0x8029B65C -> 0x8029B8D4
unsigned char PlayerDiffIcon::SyncProperty(class PlayerDiffIcon * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x160
} __vt__14PlayerDiffIcon; // size: 0x160, address: 0x808BEBE8
struct {
    // total size: 0x10
} __vt__12ListAlphable; // size: 0x10, address: 0x808BEDA8

