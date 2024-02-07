/*
    Compile unit: C:\rockband2\band2\src\bandtrack\Tail.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800234A8 -> 0x80024ECC
*/
class Symbol name; // size: 0x4, address: 0x80A48FEC
class Symbol name; // size: 0x4, address: 0x80A48FF4
class Point {
    // total size: 0x50
public:
    class Vector3 v; // offset 0x0, size 0x10
    class Color c; // offset 0x10, size 0x10
    class Vector3 cam; // offset 0x20, size 0x10
    class Vector2 base; // offset 0x30, size 0x8
    class Vector2 dir; // offset 0x38, size 0x8
    class Vector2 delta; // offset 0x40, size 0x8
};
class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    class Point * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    class Point * _M_start; // offset 0x0, size 0x4
    class Point * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
enum Type {
    kNoCaps = 0,
    kCapsFirst = 1,
    kCapsLast = 2,
};
class VertsMap {
    // total size: 0x8
public:
    enum Type t; // offset 0x0, size 0x4
    class Vert * v; // offset 0x4, size 0x4
};
class RndLine : public RndDrawable, public RndTransformable {
    // total size: 0x160
protected:
    float mWidth; // offset 0xF8, size 0x4
    class vector mPoints; // offset 0xFC, size 0xC
    class RndMesh * mMesh; // offset 0x108, size 0x4
    unsigned char mHasCaps; // offset 0x10C, size 0x1
    unsigned char mLinePairs; // offset 0x10D, size 0x1
    float mFoldAngle; // offset 0x110, size 0x4
    float mFoldCos; // offset 0x114, size 0x4
    class ObjPtr mMat; // offset 0x118, size 0xC
    unsigned char mUpdate; // offset 0x124, size 0x1
};
// Range: 0x800234A8 -> 0x800235E0
void * Tail::~Tail(class Tail * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__4Tail;
}

// Range: 0x800235E0 -> 0x80023754
void Tail::Init(class Tail * const this /* r29 */, float x /* f30 */, float y /* f31 */, class Symbol & type /* r30 */, class RndGroup * parent /* r31 */) {}

// Range: 0x80023754 -> 0x800237D4
void Tail::MoveSlot() {
    // Local variables
    class Vector3 localPos; // r1+0x10
}

// Range: 0x800237D4 -> 0x80023818
void Tail::Done(class Tail * const this /* r31 */) {}

static class Symbol unison; // size: 0x4, address: 0x80A48FFC
static class Symbol star; // size: 0x4, address: 0x80A49004
static class Symbol bonus; // size: 0x4, address: 0x80A4900C
static class Symbol invisible; // size: 0x4, address: 0x80A49014
// Range: 0x80023818 -> 0x80023A14
void Tail::SetType(class Tail * const this /* r29 */, class Symbol & type /* r31 */) {
    // Local variables
    class RndMat * tail_glow_mat; // r4

    // References
    // -> static class Symbol invisible;
    // -> static class Symbol bonus;
    // -> static class Symbol star;
    // -> static class Symbol unison;
}

// Range: 0x80023A14 -> 0x80023D48
void Tail::EnableDuration(class Tail * const this /* r31 */, class RndMesh * cloneMesh /* r29 */) {
    // Local variables
    class Matrix3 m; // r1+0x20

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80023D48 -> 0x80023E24
void Tail::KillDuration(class Tail * const this /* r31 */) {}

// Range: 0x80023E24 -> 0x80023EB4
void Tail::SetDuration(class Tail * const this /* r31 */) {}

// Range: 0x80023EB4 -> 0x80023F18
void Tail::Miss(class Tail * const this /* r31 */) {}

static class Symbol star; // size: 0x4, address: 0x80A4901C
// Range: 0x80023F18 -> 0x80023FBC
void Tail::Hit(class Tail * const this /* r31 */) {
    // References
    // -> static class Symbol star;
}

// Range: 0x80023FBC -> 0x80024020
void Tail::Release(class Tail * const this /* r31 */) {}

static class Symbol star; // size: 0x4, address: 0x80A49024
static float pulseRate; // size: 0x4, address: 0x80A49028
// Range: 0x80024020 -> 0x800245DC
void Tail::Poll(class Tail * const this /* r30 */, float ms /* f27 */, float whammy /* f28 */, float whammyActive /* f29 */) {
    // Local variables
    float frame; // f1
    float whammyAlpha; // f1
    float amplitude; // f31
    float frequency; // f0
    float elapsed; // f0
    float f; // f30
    float cutoff_y; // f27
    class RndParticle * p; // r4
    class Color clr; // r1+0x40
    float tail_width; // f0

    // References
    // -> static float pulseRate;
    // -> class TaskMgr TheTaskMgr;
    // -> static class Symbol star;
}

// Range: 0x800245DC -> 0x800246C0
static class RndParticleSys * NewRndCopy(const class RndParticleSys * src /* r30 */) {
    // Local variables
    class RndParticleSys * result; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__14RndParticleSys;
    // -> class Symbol name;
}

static class Symbol star; // size: 0x4, address: 0x80A49030
// Range: 0x800246C0 -> 0x80024CF4
void Tail::UpdateVerts(class Tail * const this /* r25 */, float whammyAlpha /* f25 */, float whammyActive /* f26 */) {
    // Local variables
    float len; // f31
    float sec_len; // f30
    int num_sections; // r5
    float first_sec_len; // f29
    int total_sections; // r29
    int null_sections; // r28
    class Vert * v; // r27
    int sec; // r26
    float vy; // f28
    float vx; // f0
    float max_vx; // f27
    class Color clr; // r1+0x10
    int index; // r28

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol star;
}

// Range: 0x80024CF4 -> 0x80024ECC
void Tail::SetupInitialVerts(class Tail * const this /* r31 */, float alpha /* f31 */) {
    // Local variables
    float len; // f3
    float sec_len; // f4
    int num_sections; // r0
    const class Vert * src_beg; // r7
    const class Vert * src_end; // r0
    class Vert * v; // r4
    float vy; // f5
    float vx; // f6
    class Color clr; // r1+0x10
    int i; // r8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__7RndLine; // size: 0x8, address: 0x8086F210
struct {
    // total size: 0xC
} __vt__4Tail; // size: 0xC, address: 0x8086F488
struct {
    // total size: 0x8
} __RTTI__4Tail; // size: 0x8, address: 0x8086F4A0

