/*
    Compile unit: C:\rockband2\system\src\rndwii\Part.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80554D28 -> 0x805552AC
*/
class DataArray * types; // size: 0x4, address: 0x80A53FC0
class Symbol name; // size: 0x4, address: 0x80A53FC8
float sIdentityMatrix[3][4]; // size: 0x30, address: 0x80982248
class WiiParticleSys : public RndParticleSys {
    // total size: 0x390
};
// Range: 0x80554D28 -> 0x80554DD4
void WiiParticleSys::Init() {
    // References
    // -> float sIdentityMatrix[3][4];
    // -> class Symbol name;
}

static class Timer * _t; // size: 0x4, address: 0x80A53FCC
// Range: 0x80554DD4 -> 0x805552AC
void WiiParticleSys::DrawShowing(class WiiParticleSys * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0x18
    class WiiMat * mat; // r3
    class Transform t; // r1+0x80
    class RndParticle * p; // r29
    class Vector3 v; // r1+0x70
    float s; // f1
    class Vector2 v1; // r1+0x68
    class Vector2 v2; // r1+0x60
    class Vector2 v3; // r1+0x58
    class Vector2 v4; // r1+0x50
    class Vector2 urVecX; // r1+0x48
    class Vector2 urVecY; // r1+0x40
    class Vector2 vNew1; // r1+0x38
    class Vector2 vNew2; // r1+0x30
    class Vector2 vNew3; // r1+0x28
    class Vector2 vNew4; // r1+0x20

    // References
    // -> class NgStats * TheNgStats;
    // -> float sIdentityMatrix[3][4];
    // -> class RndCam * sCurrent;
    // -> class Rnd & TheRnd;
    // -> static class Timer * _t;
}

struct {
    // total size: 0x18C
} __vt__14WiiParticleSys; // size: 0x18C, address: 0x809185C4
struct {
    // total size: 0x8
} __RTTI__14WiiParticleSys; // size: 0x8, address: 0x809187A8

