/*
    Compile unit: C:\rockband2\system\src\bandobj\BandScoreDisplay.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8025B90C -> 0x8025C888
*/
class DataArray * types; // size: 0x4, address: 0x80A4F1A8
// Range: 0x8025B90C -> 0x8025BBF0
void * BandScoreDisplay::BandScoreDisplay(class BandScoreDisplay * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__16BandScoreDisplay;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8025BBF0 -> 0x8025BC24
void BandScoreDisplay::Enter(class BandScoreDisplay * const this /* r31 */) {}

// Range: 0x8025BC24 -> 0x8025BD24
void BandScoreDisplay::SyncScore(class BandScoreDisplay * const this /* r30 */) {
    // Local variables
    int score; // r31
    int pos; // r29
    int newval; // r3
    int digit; // r0
}

// Range: 0x8025BD24 -> 0x8025BE08
void BandScoreDisplay::PostLoad(class BandScoreDisplay * const this /* r29 */, class BinStream & s /* r30 */) {
    // Local variables
    int tmp; // r1+0x14

    // References
    // -> class list sRevs;
}

// Range: 0x8025BE08 -> 0x8025C1FC
void BandScoreDisplay::Copy(class BandScoreDisplay * const this /* r28 */, const class Object * o /* r26 */, enum CopyType type /* r25 */) {
    // Local variables
    const class BandScoreDisplay * sd; // r0

    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16BandScoreDisplay;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F1B0
static class Symbol _s; // size: 0x4, address: 0x80A4F1B8
static class Symbol _s; // size: 0x4, address: 0x80A4F1C0
static class Symbol _s; // size: 0x4, address: 0x80A4F1C8
static class Symbol _s; // size: 0x4, address: 0x80A4F1D0
// Range: 0x8025C1FC -> 0x8025C5D4
unsigned char BandScoreDisplay::SyncProperty(class BandScoreDisplay * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x8025C5D4 -> 0x8025C888
unsigned char PropSync(class ObjVector & v /* r29 */, class DataNode & n /* r30 */, class DataArray * prop /* r26 */, int i /* r28 */, enum PropOp op /* r27 */) {
    // Local variables
    class ObjPtr * it; // r31
    class ObjPtr tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x21C
} __vt__16BandScoreDisplay; // size: 0x21C, address: 0x808B5EC8
struct {
    // total size: 0x8
} __RTTI__16BandScoreDisplay; // size: 0x8, address: 0x808B6150
struct {
    // total size: 0x8
} __RTTI__P27ObjPtr<7RndMesh,9ObjectDir>; // size: 0x8, address: 0x808B64B0
struct {
    // total size: 0x8
} __RTTI__P26ObjPtr<6RndMat,9ObjectDir>; // size: 0x8, address: 0x808B64D8

