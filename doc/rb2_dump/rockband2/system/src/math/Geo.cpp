/*
    Compile unit: C:\rockband2\system\src\math\Geo.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80628BF8 -> 0x8062C028
*/
static float gBSPPosTol; // size: 0x4, address: 0x80A47C08
static float gBSPDirTol; // size: 0x4, address: 0x80A47C0C
static int gBSPMaxDepth; // size: 0x4, address: 0x80A47C10
static int gBSPMaxCandidates; // size: 0x4, address: 0x80A47C14
static float gBSPCheckScale; // size: 0x4, address: 0x80A47C18
// Range: 0x80628BF8 -> 0x80628CE0
static class DataNode SetBSPParams(class DataArray * a /* r29 */) {}

// Range: 0x80628CE0 -> 0x80628E64
void GeoInit() {
    // Local variables
    class DataArray * config; // r27
}

// Range: 0x80628E64 -> 0x80628F50
class BinStream & __rs(class BinStream & d /* r29 */, class BSPNode * & s /* r30 */) {
    // Local variables
    unsigned char c; // r1+0x8
}

// Range: 0x80628F50 -> 0x80628FD4
void Box::GrowToContain() {
    // Local variables
    int i; // r6
}

// Range: 0x80628FD4 -> 0x80629094
unsigned char Box::Clamp() {}

// Range: 0x80629094 -> 0x806291B0
void Multiply() {
    // Local variables
    class Vector3 center; // r1+0x10
}

// Range: 0x806291B0 -> 0x80629328
void Multiply(const class Plane & a /* r29 */, const class Transform & b /* r30 */, class Plane & c /* r31 */) {
    // Local variables
    class Vector3 on; // r1+0x30
    class Vector3 n; // r1+0x20
    class Matrix3 m; // r1+0x40
}

// Range: 0x80629328 -> 0x80629390
void Intersect() {
    // Local variables
    float a; // f1
    float b; // f2
    float c; // f3
    float d; // f4
    float e; // f5
    float f; // f6
    float g; // f7
    float h; // f8
    float l2; // f9
}

// Range: 0x80629390 -> 0x80629554
void Intersect() {
    // Local variables
    class Vector3 base; // r1+0x30
    class Vector3 dir; // r1+0x20
}

// Range: 0x80629554 -> 0x8062988C
unsigned char Intersect() {
    // Local variables
    class Vector3 v; // r1+0x20
    float d; // f0
    class Vector3 v2; // r1+0x10
    float zx; // f0
    float zy; // f0
    float zz; // f0
    int i; // r0
    int j; // r6
    float x; // f1
    float y; // f2
    float A; // f31
    float B; // f30
    float C; // f29
    float D; // f28
    float E; // f27
    float F; // f26
    float det; // f25

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8062988C -> 0x80629964
unsigned char Intersect(const class Vector3 & v /* r30 */, const class BSPNode * n /* r31 */) {
    // Local variables
    float dot; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80629964 -> 0x80629D64
unsigned char Intersect(const class Segment & s /* r28 */, const class BSPNode * n /* r29 */, float & dist /* r30 */, class Plane & plane /* r31 */) {
    // Local variables
    float startDot; // f0
    float endDot; // f0
    float d; // r1+0x10
    float diff; // f2
    float ratio; // f31
    class Segment startSeg; // r1+0x40
    class Segment endSeg; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80629D64 -> 0x8062A068
unsigned char Intersect(const class Transform & t /* r28 */, const class Polygon & p /* r29 */, const class BSPNode * n /* r30 */) {
    // Local variables
    unsigned char front; // r6
    unsigned char back; // r7
    const class Vector2 * i; // r8
    class Vector3 v; // r1+0x60
    float dot; // f0
    class Ray r; // r1+0x48
    class Polygon splitPoly; // r1+0x38
}

// Range: 0x8062A07C -> 0x8062A254
unsigned char Intersect() {
    // Local variables
    class Vector3 d; // r1+0x20
    class Vector3 d2; // r1+0x10
    float sq; // f0
    float dist; // f0
}

// Range: 0x8062A254 -> 0x8062A26C
void SetBSPParams() {
    // References
    // -> static float gBSPCheckScale;
    // -> static int gBSPMaxCandidates;
    // -> static int gBSPMaxDepth;
    // -> static float gBSPDirTol;
    // -> static float gBSPPosTol;
}

// Range: 0x8062A26C -> 0x8062AA28
unsigned char CheckBSPTree(const class BSPNode * tree /* r31 */, const class Box & box /* r30 */) {
    // Local variables
    class Box b; // r1+0x110
    class Polygon p; // r1+0x100
    class Transform t; // r1+0x130

    // References
    // -> static float gBSPCheckScale;
}

static int depth; // size: 0x4, address: 0x80A55538
// Range: 0x8062AA28 -> 0x8062AAE0
void NumNodes(const class BSPNode * n /* r29 */, int & num /* r30 */, int & maxDepth /* r31 */) {
    // References
    // -> static int depth;
}

// Range: 0x8062AAE0 -> 0x8062AAF8
static unsigned char __lt() {}

// Range: 0x8062AAF8 -> 0x8062ABF0
void BSPFace::OnSide() {
    // Local variables
    class Vector2 * point; // r7
    class Vector3 v; // r1+0x10
    float dot; // f0

    // References
    // -> static float gBSPPosTol;
}

// Range: 0x8062ABF0 -> 0x8062B050
void BSPFace::Update(class BSPFace * const this /* r31 */) {
    // Local variables
    class Vector2 * i; // r30
    class Vector2 * p1; // r3
    class Vector2 * p2; // r4
    class Vector3 v; // r1+0x60
    class Vector3 v2; // r1+0x50
    class Vector3 v3; // r1+0x40

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std18_List_node<5Plane>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8062B050 -> 0x8062B5F8
void BSPFace::Set(class BSPFace * const this /* r30 */, const class Vector3 & p2 /* r29 */, const class Vector3 & p3 /* r31 */) {
    // Local variables
    class Vector3 v; // r1+0x50
}

struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
// Range: 0x8062B5F8 -> 0x8062B824
void Sphere::GrowToContain() {
    // Local variables
    class Vector3 v; // r1+0x30
    float d; // f0
    class Vector3 a; // r1+0x20
    class Vector3 b; // r1+0x10
}

// Range: 0x8062B84C -> 0x8062BA0C
void Frustum::Set(class Frustum * const this /* r31 */, float yFov /* f30 */, float yRatio /* f31 */) {
    // Local variables
    float h; // f28
    class Vector2 v; // r1+0x8
}

// Range: 0x8062BA0C -> 0x8062BBE0
unsigned char __gt() {}

// Range: 0x8062BBE0 -> 0x8062C028
void Clip(const class Polygon & p1 /* r27 */, const class Ray & r /* r28 */, class Polygon & p2 /* r29 */) {
    // Local variables
    class vector * newPoints; // r31
    class vector tempPoints; // r1+0x60
    class Vector2 v; // r1+0x58
    float lastDot; // f4
    const class Vector2 * i; // r30
    const class Vector2 * lastPoint; // r3
    float dot; // f31
}


