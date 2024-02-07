/*
    Compile unit: C:\rockband2\system\src\rndwii\Mesh.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80550228 -> 0x80552DC0
*/
class DataArray * types; // size: 0x4, address: 0x80A53E98
class Symbol name; // size: 0x4, address: 0x80A53EA0
char * sTemp; // size: 0x4, address: 0x80A53EA4
char * sCurr; // size: 0x4, address: 0x80A53EA8
// Range: 0x80550228 -> 0x8055023C
void * DisplayList::DisplayList() {}

// Range: 0x8055023C -> 0x80550290
void * DisplayList::~DisplayList(class DisplayList * const this /* r30 */) {}

static int _x; // size: 0x4, address: 0x80A53EAC
// Range: 0x80550290 -> 0x80550300
void DisplayList::Init() {
    // References
    // -> static int _x;
    // -> char * sTemp;
}

// Range: 0x80550300 -> 0x80550340
void DisplayList::Clear(class DisplayList * const this /* r31 */) {}

static int _x; // size: 0x4, address: 0x80A53EB4
// Range: 0x80550340 -> 0x805503F8
void DisplayList::Copy(class DisplayList * const this /* r30 */, const class DisplayList & source /* r31 */) {
    // References
    // -> static int _x;
}

// Range: 0x805503F8 -> 0x8055047C
void DisplayList::Begin(class DisplayList * const this /* r30 */, unsigned short numMeshVerts /* r31 */) {
    // References
    // -> char * sTemp;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> char * sCurr;
}

// Range: 0x8055047C -> 0x805504E4
void DisplayList::Begin(class DisplayList * const this /* r28 */, enum _GXPrimitive prim /* r29 */, enum _GXVtxFmt format /* r30 */, unsigned short numVerts /* r31 */) {}

// Range: 0x805504E4 -> 0x80550510
void DisplayList::Start() {
    // References
    // -> char * sCurr;
}

static int _x; // size: 0x4, address: 0x80A53EBC
// Range: 0x80550510 -> 0x80550664
void DisplayList::End(class DisplayList * const this /* r29 */) {
    // Local variables
    int size; // r30

    // References
    // -> char * sTemp;
    // -> static int _x;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> char * sCurr;
}

// Range: 0x80550664 -> 0x805507C8
class DisplayList & DisplayList::__ls(class DisplayList * const this /* r28 */, unsigned short x /* r30 */) {
    // Local variables
    unsigned char xs; // r30
    unsigned char * d; // r29
    unsigned short * d; // r29

    // References
    // -> char * sTemp;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> char * sCurr;
}

// Range: 0x805507C8 -> 0x805507E0
enum _GXAttrType DisplayList::Type() {}

// Range: 0x805507E0 -> 0x805508D0
void DisplayList::Draw(const class DisplayList * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805508D0 -> 0x805509D8
void * WiiMesh::WiiMesh(class WiiMesh * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__7WiiMesh;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x805509D8 -> 0x80550A7C
void WiiMesh::Copy(class WiiMesh * const this /* r29 */, const class Object * o /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class WiiMesh * m; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7WiiMesh;
}

// Range: 0x80550A7C -> 0x80550B98
void WiiMesh::Init() {
    // References
    // -> class Symbol name;
}

// Range: 0x80550B98 -> 0x80550BE8
void WiiMesh::ReleaseBuffers(class WiiMesh * const this /* r31 */) {}

// Range: 0x80550BE8 -> 0x80550D7C
void WiiMesh::CreateBuffers(class WiiMesh * const this /* r31 */) {
    // Local variables
    int heap; // r0
    unsigned int sz; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80550D7C -> 0x80550E78
void * WiiMesh::~WiiMesh(class WiiMesh * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__7WiiMesh;
}

static class Timer * _t; // size: 0x4, address: 0x80A53EC4
// Range: 0x80550E78 -> 0x805514DC
void WiiMesh::Sync(class WiiMesh * const this /* r29 */, int flags /* r30 */) {
    // Local variables
    class AutoTimer _at; // r1+0x28
    float * wgt; // r3
    int i; // r4
    class Vert * it; // r5
    int i; // r7
    int numMeshVerts; // r28
    class Striper striper; // r1+0x48
    int patchStart; // r27
    unsigned char * p; // r28
    struct STRIPERRESULT sr; // r1+0x38
    int nv; // [invalid]
    unsigned short * index; // r26
    int i; // r25
    int x; // r24
    int numMeshVerts; // r24
    int i; // r24

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Timer * _t;
}

// Range: 0x805514DC -> 0x80551548
void WiiMesh::SetVertexDesc(class WiiMesh * const this /* r31 */) {
    // Local variables
    enum _GXAttrType type; // r31
}

// Range: 0x80551548 -> 0x805515F0
void WiiMesh::SetVertexBuffers() {
    // Local variables
    const struct VColTex * ctVtxs; // r30
}

static class Timer * _t; // size: 0x4, address: 0x80A53ECC
static class Timer * _t; // size: 0x4, address: 0x80A53ED4
static class Timer * _t; // size: 0x4, address: 0x80A53EDC
static class Timer * _t; // size: 0x4, address: 0x80A53EE4
static class Timer * _t; // size: 0x4, address: 0x80A53EEC
// Range: 0x805515F0 -> 0x80551A80
void WiiMesh::DrawShowing(class WiiMesh * const this /* r27 */) {
    // Local variables
    class AutoTimer _at; // r1+0x30
    class WiiMesh * owner; // r30
    class WiiMat * mat; // [invalid]
    struct VPosNrm * skinVtxs; // r1+0x2C
    class AutoTimer _at; // r1+0x28
    class WiiMat * pass; // r29
    unsigned char reflection; // r28
    class AutoTimer _at; // r1+0x24
    class AutoTimer _at; // r1+0x20
    class AutoTimer _at; // r1+0x1C

    // References
    // -> class NgStats * TheNgStats;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> class Rnd & TheRnd;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
}

// Range: 0x80551A80 -> 0x80551D64
static void SkinMesh_2B(const struct VPosNrm * src /* r26 */, void * dst /* r27 */, const float * weight /* r28 */, int numVerts /* r29 */, const class Transform & t0 /* r30 */, const class Transform & t1 /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80551D64 -> 0x80552090
static void SkinMesh_3B(const struct VPosNrm * src /* r25 */, void * dst /* r26 */, const float * weight /* r27 */, int numVerts /* r28 */, const class Transform & t0 /* r29 */, const class Transform & t1 /* r30 */, const class Transform & t2 /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80552090 -> 0x80552400
static void SkinMesh_4B(const struct VPosNrm * src /* r24 */, void * dst /* r25 */, const float * weight /* r26 */, int numVerts /* r27 */, const class Transform & t0 /* r28 */, const class Transform & t1 /* r29 */, const class Transform & t2 /* r30 */, const class Transform & t3 /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Timer * _t; // size: 0x4, address: 0x80A53EF4
static class Timer * _t; // size: 0x4, address: 0x80A53EFC
static class Timer * _t; // size: 0x4, address: 0x80A53F04
// Range: 0x80552400 -> 0x80552A9C
void WiiMesh::SetTransforms(class WiiMesh * const this /* r23 */, struct VPosNrm * & skinVtxs /* r24 */) {
    // Local variables
    class WiiMesh * owner; // r30
    float viewXfm[3][4]; // r1+0xF0
    float modelXfm[3][4]; // r1+0xC0
    class Transform t0; // r1+0x80
    float modelViewXfm[3][4]; // r1+0x50
    class AutoTimer _at; // r1+0x28
    class Transform t[4]; // r1+0x120
    int numVerts; // r1+0x24
    void * dstVtxs; // r29
    struct VPosNrm * srcVtxs; // [invalid]
    float * weights; // [invalid]
    struct VPosNrm * vertCache[4]; // r1+0x40
    float * weightCache[4]; // r1+0x30
    unsigned char * curVertDataPtr; // r28
    unsigned char * endVertDataPtr; // r27
    unsigned char * curWeightDataPtr; // r26
    unsigned char numTransfers; // r25
    unsigned char i; // r24
    int bytes; // r22
    int weightBytes; // r22
    unsigned char i; // r24
    int count; // r30
    int bytes; // r22
    int weightBytes; // r22

    // References
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> class GPUQueue & GPUMem;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Timer * _t;
    // -> const class Transform * sCurrentModelXfm;
    // -> class RndCam * sCurrent;
}

// Range: 0x80552A9C -> 0x80552DC0
void WiiMesh::DrawReflection(class WiiMesh * const this /* r29 */) {
    // Local variables
    float identity[3][4]; // r1+0xF0
    class WiiCam * camera; // r3
    float view[3][4]; // r1+0xC0
    float world[3][4]; // r1+0x90
    float modelView[3][4]; // r1+0x60
    struct Vec eyePos; // r1+0x50
    int f; // r31
    class Face & face; // r0
    int v; // r30
    int index; // r26
    struct Vec mvPos; // r1+0x44
    struct Vec mvNorm; // r1+0x38
    struct Vec reflection; // r1+0x2C
    struct Vec eyeDir; // r1+0x20
    struct Vec pos; // r1+0x14
    struct Vec norm; // r1+0x8

    // References
    // -> class RndCam * sCurrent;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xFC
} __vt__7WiiMesh; // size: 0xFC, address: 0x80917C20
struct {
    // total size: 0x8
} __RTTI__7WiiMesh; // size: 0x8, address: 0x80917D60

