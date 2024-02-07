/*
    Compile unit: C:\rockband2\system\src\rndobj\MatAnim.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804B1978 -> 0x804B4634
*/
class DataArray * types; // size: 0x4, address: 0x80A531A0
class Symbol name; // size: 0x4, address: 0x80A531A8
static class Object * gOwner; // size: 0x4, address: 0x80A531AC
// Range: 0x804B1978 -> 0x804B19C4
void * TexPtr::TexPtr() {
    // References
    // -> struct [anonymous] __vt__Q210RndMatAnim6TexPtr;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> static class Object * gOwner;
}

// Range: 0x804B19C4 -> 0x804B1A28
void * TexPtr::TexPtr(class TexPtr * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__Q210RndMatAnim6TexPtr;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> static class Object * gOwner;
}

// Range: 0x804B1A28 -> 0x804B1A40
void * TexKeys::TexKeys() {}

// Range: 0x804B1A40 -> 0x804B1E18
int TexKeys::Add(class TexKeys * const this /* r25 */, float frame /* f31 */, unsigned char unique /* r26 */) {
    // References
    // -> struct [anonymous] __vt__Q210RndMatAnim6TexPtr;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> static class Object * gOwner;
}

// Range: 0x804B1E18 -> 0x804B2070
void TexKeys::__as(class TexKeys * const this /* r30 */, const class TexKeys & x /* r31 */) {
    // Local variables
    class Key * i; // r26
    const class Key * j; // r28

    // References
    // -> struct [anonymous] __vt__Q210RndMatAnim6TexPtr;
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> static class Object * gOwner;
}

// Range: 0x804B2070 -> 0x804B21A8
void * RndMatAnim::RndMatAnim(class RndMatAnim * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__36ObjOwnerPtr<10RndMatAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndMat,9ObjectDir>;
    // -> struct [anonymous] __vt__10RndMatAnim;
}

// Range: 0x804B21A8 -> 0x804B2290
void RndMatAnim::Replace(class RndMatAnim * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndMatAnim;
}

static int MATANIM_REV; // size: 0x4, address: 0x80A47258
// Range: 0x804B2290 -> 0x804B22D4
void RndMatAnim::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A531B0
// Range: 0x804B22D4 -> 0x804B2584
void RndMatAnim::Load(class RndMatAnim * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    class Keys lightColorKeys; // r1+0x40
    class Keys ambientKeys; // r1+0x34

    // References
    // -> static class Object * gOwner;
    // -> class Debug TheDebug;
    // -> static int MATANIM_REV;
    // -> static int gRev;
}

// Range: 0x804B2584 -> 0x804B28D0
void RndMatAnim::Copy(class RndMatAnim * const this /* r31 */, const class Object * o /* r29 */, enum CopyType type /* r28 */) {
    // Local variables
    const class RndMatAnim * m; // r0

    // References
    // -> static class Object * gOwner;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndMatAnim;
}

// Range: 0x804B28D0 -> 0x804B2A44
void RndMatAnim::Print(class RndMatAnim * const this /* r27 */) {
    // Local variables
    class TextStream & d; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x804B2A44 -> 0x804B2D60
float RndMatAnim::EndFrame(class RndMatAnim * const this /* r31 */) {
    // Local variables
    float frame; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804B2D60 -> 0x804B30BC
void RndMatAnim::SetFrame(class RndMatAnim * const this /* r31 */, float frame /* f30 */, float blend /* f31 */) {
    // Local variables
    class Vector3 v; // r1+0x50
    class Vector3 blendScale; // r1+0x40
    class Transform t; // r1+0x60
    class Vector3 euler; // r1+0x30
    class RndTex * t; // r1+0x14
    class Color c; // r1+0x20
    float a; // r1+0x10
}

// Range: 0x804B30BC -> 0x804B41BC
void RndMatAnim::SetKey(class RndMatAnim * const this /* r31 */, float frame /* f31 */) {
    // Local variables
    class Vector3 e; // r1+0x30
    class Vector3 s; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804B41BC -> 0x804B41C8
void Interp() {}

// Range: 0x804B41C8 -> 0x804B45B4
class DataNode RndMatAnim::Handle(class RndMatAnim * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

// Range: 0x804B45B4 -> 0x804B4634
unsigned char RndMatAnim::SyncProperty(class RndMatAnim * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xA8
} __vt__10RndMatAnim; // size: 0xA8, address: 0x808F9E58
struct {
    // total size: 0x18
} __vt__36ObjOwnerPtr<10RndMatAnim,9ObjectDir>; // size: 0x18, address: 0x808F9F30
struct {
    // total size: 0x8
} __RTTI__36ObjOwnerPtr<10RndMatAnim,9ObjectDir>; // size: 0x8, address: 0x808F9F78
struct {
    // total size: 0x18
} __vt__Q210RndMatAnim6TexPtr; // size: 0x18, address: 0x808F9F80
struct {
    // total size: 0x8
} __RTTI__Q210RndMatAnim6TexPtr; // size: 0x8, address: 0x808F9FC0
class Key {
    // total size: 0x10
public:
    class TexPtr value; // offset 0x0, size 0xC
    float frame; // offset 0xC, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__P26Key<Q210RndMatAnim6TexPtr>; // size: 0x8, address: 0x808FA198

