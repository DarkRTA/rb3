/*
    Compile unit: C:\rockband2\system\src\rndobj\Cam.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804742F8 -> 0x80475FFC
*/
class DataArray * types; // size: 0x4, address: 0x80A529E8
class RndCam * sCurrent; // size: 0x4, address: 0x80A529F0
// Range: 0x804742F8 -> 0x80474404
float RndCam::WorldToScreen() {
    // Local variables
    class Vector3 v1; // r1+0x10
    float q; // f1
}

// Range: 0x80474404 -> 0x80474478
void RndCam::Select(class RndCam * const this /* r31 */) {
    // References
    // -> class RndCam * sCurrent;
}

// Range: 0x80474478 -> 0x80474510
void RndCam::SetTargetTex(class RndCam * const this /* r30 */, class RndTex * tex /* r31 */) {
    // References
    // -> class RndCam * sCurrent;
}

static int CAM_REV; // size: 0x4, address: 0x80A47110
// Range: 0x80474510 -> 0x80474554
void RndCam::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80474554 -> 0x80474744
void RndCam::Load(class RndCam * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int CAM_REV;
}

// Range: 0x80474744 -> 0x80474858
void RndCam::Copy(class RndCam * const this /* r29 */, const class Object * o /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class RndCam * c; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndCam;
}

// Range: 0x80474858 -> 0x80474998
void * RndCam::RndCam(class RndCam * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> struct [anonymous] __vt__6RndCam;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80474998 -> 0x80474A84
void * RndCam::~RndCam(class RndCam * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__26ObjPtr<6RndTex,9ObjectDir>;
    // -> class RndCam * sCurrent;
}

static class DebugWarner _dw; // size: 0x100, address: 0x8097F100
// Range: 0x80474A84 -> 0x80474BA0
void RndCam::SetFrustum(class RndCam * const this /* r29 */, float nearPlane /* f29 */, float farPlane /* f30 */, float yFov /* f31 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
}

// Range: 0x80474BA0 -> 0x80474D50
void RndCam::UpdateLocal(class RndCam * const this /* r31 */) {
    // Local variables
    float yRatio; // f31
    float t; // f0

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x80474D50 -> 0x80474EA0
void RndCam::UpdatedWorldXfm(class RndCam * const this /* r29 */) {}

static class Transform sFlipYZ; // size: 0x40, address: 0x8097F200
static class Symbol _s; // size: 0x4, address: 0x80A529F8
static class Symbol _s; // size: 0x4, address: 0x80A52A00
static class Symbol _s; // size: 0x4, address: 0x80A52A08
static class Symbol _s; // size: 0x4, address: 0x80A52A10
// Range: 0x80474EA0 -> 0x804757EC
class DataNode RndCam::Handle(class RndCam * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol near_plane; // size: 0x4, address: 0x80A52A18
static class Symbol far_plane; // size: 0x4, address: 0x80A52A20
static class Symbol y_fov; // size: 0x4, address: 0x80A52A28
// Range: 0x804757EC -> 0x80475950
class DataNode RndCam::OnSetFrustum(class RndCam * const this /* r29 */, const class DataArray * a /* r30 */) {
    // Local variables
    float np; // r1+0x1C
    float fp; // r1+0x18
    float f; // r1+0x14

    // References
    // -> static class Symbol y_fov;
    // -> static class Symbol far_plane;
    // -> static class Symbol near_plane;
}

// Range: 0x80475950 -> 0x804759D8
class DataNode RndCam::OnSetZRange(class RndCam * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804759D8 -> 0x80475AE8
class DataNode RndCam::OnSetScreenRect(class RndCam * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class Rect r; // r1+0x8
}

// Range: 0x80475AE8 -> 0x80475AFC
class DataNode RndCam::OnFarPlane() {}

static class Symbol _s; // size: 0x4, address: 0x80A52A30
static class Symbol _s; // size: 0x4, address: 0x80A52A38
static class Symbol _s; // size: 0x4, address: 0x80A52A40
static class Symbol _s; // size: 0x4, address: 0x80A52A48
static class Symbol _s; // size: 0x4, address: 0x80A52A50
// Range: 0x80475AFC -> 0x80475E68
unsigned char RndCam::SyncProperty(class RndCam * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xA4
} __vt__6RndCam; // size: 0xA4, address: 0x808F2514
// Range: 0x80475E68 -> 0x80475F0C
static void __sinit_\Cam_cpp() {
    // References
    // -> static class Transform sFlipYZ;
}


