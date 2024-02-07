/*
    Compile unit: C:\rockband2\system\src\rndobj\Line.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804A40BC -> 0x804A772C
*/
class DataArray * types; // size: 0x4, address: 0x80A52FE0
// Range: 0x804A40BC -> 0x804A4100
class RndDrawable * RndLine::CollideShowing(class RndLine * const this /* r31 */) {}

// Range: 0x804A4100 -> 0x804A4114
int RndLine::CollidePlane() {}

// Range: 0x804A4114 -> 0x804A4140
void Add() {}

// Range: 0x804A4140 -> 0x804A416C
void Subtract() {}

// Range: 0x804A416C -> 0x804A45F8
void RndLine::UpdateLine(class RndLine * const this /* r27 */, class Point * first /* r28 */, class Point * last /* r31 */) {
    // Local variables
    class Point * p; // r30
    float s; // f1
    class Ray r1; // r1+0x28
    unsigned char folded; // r29
    float dot; // f0
    class Ray r2; // r1+0x18
    class Point * back; // r0
    class Vector2 cap; // r1+0x10
    class VertsMap vm; // r1+0x8
}

// Range: 0x804A45F8 -> 0x804A49F8
void RndLine::UpdateLinePair(class RndLine * const this /* r29 */, class Point * first /* r30 */, class Point * last /* r31 */) {
    // Local variables
    class VertsMap vm; // r1+0x10
    float s; // f3
    class Vector2 cap; // r1+0x8
}

// Range: 0x804A49F8 -> 0x804A4AC0
void RndLine::DrawShowing(class RndLine * const this /* r30 */) {
    // References
    // -> class RndCam * sCurrent;
}

// Range: 0x804A4AC0 -> 0x804A4C08
void RndLine::UpdateSphere(class RndLine * const this /* r30 */) {
    // Local variables
    class Sphere s; // r1+0x20
    class Transform t; // r1+0x40
}

// Range: 0x804A4C08 -> 0x804A4D3C
unsigned char RndLine::MakeWorldSphere(class RndLine * const this /* r29 */, class Sphere & s /* r30 */) {
    // Local variables
    class Point * p; // r31
}

// Range: 0x804A4D3C -> 0x804A4FAC
void RndLine::MapVerts(int point /* r30 */, class VertsMap & map /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804A4FAC -> 0x804A5020
void RndLine::SetMat(class RndLine * const this /* r30 */, class RndMat * m /* r31 */) {}

// Range: 0x804A5020 -> 0x804A504C
void RndLine::SetHasCaps() {}

// Range: 0x804A504C -> 0x804A5078
void RndLine::SetLinePairs() {}

// Range: 0x804A5078 -> 0x804A5730
void RndLine::SetNumPoints(class RndLine * const this /* r29 */, int n /* r30 */) {
    // Local variables
    int i; // r31
    class VertsMap vm; // r1+0x38
    int j; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804A5730 -> 0x804A58D4
void RndLine::SetPointColor(class RndLine * const this /* r29 */, int i /* r28 */, const class Color & c /* r30 */, unsigned char sync /* r31 */) {
    // Local variables
    class VertsMap vm; // r1+0x8

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static int LINE_REV; // size: 0x4, address: 0x80A47210
// Range: 0x804A58D4 -> 0x804A5918
void RndLine::Save() {
    // References
    // -> class Debug TheDebug;
}

static class Vector3 offset; // size: 0x10, address: 0x8097F290
// Range: 0x804A5918 -> 0x804A5AA0
void RndLine::SetUpdate(class RndLine * const this /* r29 */) {
    // Local variables
    class Transform t; // r1+0x10

    // References
    // -> static class Vector3 offset;
}

// Range: 0x804A5AA0 -> 0x804A5FE8
void RndLine::UpdateLine(class RndLine * const this /* r30 */, float nearPlane /* f31 */) {
    // Local variables
    class Transform t; // r1+0x20
    int first; // r7
    int last; // r5
    int end; // r31
    int i; // r29
    float f; // f4
    float f; // f4
    class Point * b; // r5
    float f; // f4
    float f; // f4
}

// Range: 0x804A5FE8 -> 0x804A6058
void RndLine::UpdateInternal(class RndLine * const this /* r31 */) {}

// Range: 0x804A6058 -> 0x804A6384
void RndLine::Load(class RndLine * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0x14
    int rev; // r1+0x10
    class ObjPtrList collides; // r1+0x18

    // References
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> static int LINE_REV;
}

// Range: 0x804A6384 -> 0x804A64C0
void RndLine::Copy(class RndLine * const this /* r28 */, const class Object * o /* r29 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndLine * d; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndLine;
}

// Range: 0x804A64C0 -> 0x804A6520
static class TextStream & __ls(class TextStream & d /* r30 */, const class Point & c /* r31 */) {}

// Range: 0x804A6520 -> 0x804A65F0
void RndLine::Print(class RndLine * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804A65F0 -> 0x804A66C4
class TextStream & __ls(class TextStream & d /* r30 */, const class vector & c /* r31 */) {
    // Local variables
    const class Point * t; // r29
}

// Range: 0x804A66C4 -> 0x804A6908
void * RndLine::RndLine(class RndLine * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__7RndLine;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x804A6908 -> 0x804A6AEC
void * RndLine::~RndLine(class RndLine * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__7RndLine;
}

static class Symbol _s; // size: 0x4, address: 0x80A52FE8
static class Symbol _s; // size: 0x4, address: 0x80A52FF0
static class Symbol _s; // size: 0x4, address: 0x80A52FF8
static class Symbol _s; // size: 0x4, address: 0x80A53000
static class Symbol _s; // size: 0x4, address: 0x80A53008
// Range: 0x804A6AEC -> 0x804A7684
class DataNode RndLine::Handle(class RndLine * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x44
    class MessageTimer _mt; // r1+0x90
    class DataNode _n; // r1+0x58
    class DataNode _n; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x804A7684 -> 0x804A772C
unsigned char RndLine::SyncProperty(class RndLine * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xF8
} __vt__7RndLine; // size: 0xF8, address: 0x808F8588
struct {
    // total size: 0x8
} __RTTI__PQ27RndLine5Point; // size: 0x8, address: 0x808F8920

