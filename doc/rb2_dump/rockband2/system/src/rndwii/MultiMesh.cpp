/*
    Compile unit: C:\rockband2\system\src\rndwii\MultiMesh.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80553E8C -> 0x80554998
*/
class DataArray * types; // size: 0x4, address: 0x80A53F28
class Symbol name; // size: 0x4, address: 0x80A53F30
static enum _GXPosNrmMtx index[10]; // size: 0x28, address: 0x80849768
enum _GXPosNrmMtx {
    GX_PNMTX0 = 0,
    GX_PNMTX1 = 3,
    GX_PNMTX2 = 6,
    GX_PNMTX3 = 9,
    GX_PNMTX4 = 12,
    GX_PNMTX5 = 15,
    GX_PNMTX6 = 18,
    GX_PNMTX7 = 21,
    GX_PNMTX8 = 24,
    GX_PNMTX9 = 27,
};
// Range: 0x80553E8C -> 0x80553EA0
static enum _GXPosNrmMtx MtxIndex() {
    // References
    // -> static enum _GXPosNrmMtx index[10];
}

static class Timer * _t; // size: 0x4, address: 0x80A53F34
static class Timer * _t; // size: 0x4, address: 0x80A53F3C
static class Timer * _t; // size: 0x4, address: 0x80A53F44
static class Timer * _t; // size: 0x4, address: 0x80A53F4C
static class Timer * _t; // size: 0x4, address: 0x80A53F54
static class Timer * _t; // size: 0x4, address: 0x80A53F5C
static class Timer * _t; // size: 0x4, address: 0x80A53F64
static class Timer * _t; // size: 0x4, address: 0x80A53F6C
static class Timer * _t; // size: 0x4, address: 0x80A53F74
static class Timer * _t; // size: 0x4, address: 0x80A53F7C
static class Timer * _t; // size: 0x4, address: 0x80A53F84
static class Timer * _t; // size: 0x4, address: 0x80A53F8C
static class Timer * _t; // size: 0x4, address: 0x80A53F94
static class Timer * _t; // size: 0x4, address: 0x80A53F9C
static class Timer * _t; // size: 0x4, address: 0x80A53FA4
static class Timer * _t; // size: 0x4, address: 0x80A53FAC
static class Timer * _t; // size: 0x4, address: 0x80A53FB4
class WiiMultiMesh : public RndMultiMesh {
    // total size: 0x80
};
// Range: 0x80553EA0 -> 0x80554998
void WiiMultiMesh::DrawShowing(class WiiMultiMesh * const this /* r25 */) {
    // Local variables
    class AutoTimer _at; // r1+0x78
    class WiiMesh * mesh; // r28
    class WiiMat * mat; // r30
    class WiiMesh * owner; // r27
    class WiiCam * cam; // r26
    class WiiEnviron * env; // r3
    class AutoTimer _at; // r1+0x74
    float modelXfm[3][4]; // r1+0xE0
    float viewXfm[3][4]; // r1+0xB0
    float modelViewXfm[3][4]; // r1+0x80
    int n; // r0
    struct _List_iterator t; // r1+0x70
    struct _List_iterator t_end; // r1+0x6C
    int i; // r26
    int x; // r25

    // References
    // -> class NgStats * TheNgStats;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> class Rnd & TheRnd;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class RndEnviron * sCurrent;
    // -> class RndCam * sCurrent;
    // -> static class Timer * _t;
}

struct {
    // total size: 0xBC
} __vt__12WiiMultiMesh; // size: 0xBC, address: 0x809182EC
struct {
    // total size: 0x8
} __RTTI__12WiiMultiMesh; // size: 0x8, address: 0x809183E8

