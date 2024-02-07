/*
    Compile unit: C:\rockband2\system\src\rndobj\Trans.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8050B6EC -> 0x8051102C
*/
class Plane sShadowPlane; // size: 0x10, address: 0x80981850
// Range: 0x8050B6EC -> 0x8050B788
void RndTransformable::Init() {
    // Local variables
    class DataArray * rnd; // r31

    // References
    // -> class Plane sShadowPlane;
    // -> class Symbol name;
}

// Range: 0x8050B788 -> 0x8050B948
void * RndTransformable::RndTransformable(class RndTransformable * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__16RndTransformable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8050B948 -> 0x8050BBB8
void * RndTransformable::~RndTransformable(class RndTransformable * const this /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x2C

    // References
    // -> struct [anonymous] __vt__42ObjOwnerPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__16RndTransformable;
}

// Range: 0x8050BBB8 -> 0x8050C17C
void RndTransformable::SetTransParent(class RndTransformable * const this /* r29 */, class RndTransformable * t /* r30 */, unsigned char recalcLocal /* r28 */) {
    // Local variables
    class Transform oldXfm; // r1+0x90
    class Transform newXfm; // r1+0x50
    struct _List_iterator r; // r1+0x3C
    class RndTransAnim * ta; // r0

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std31_List_node<P16RndTransformable>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8050C17C -> 0x8050C1F0
void RndTransformable::Replace(class RndTransformable * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x8050C1F0 -> 0x8050C26C
void RndTransformable::SetDirtyForce(class RndTransformable * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x14
}

// Range: 0x8050C26C -> 0x8050C378
void RndTransformable::SetWorldXfm(class RndTransformable * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x14
}

// Range: 0x8050C378 -> 0x8050C41C
void RndTransformable::SetWorldPos(class RndTransformable * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x14
}

static class Timer * _t; // size: 0x4, address: 0x80A53A78
// Range: 0x8050C41C -> 0x8050C80C
void RndTransformable::RecalcWorldXfm(class RndTransformable * const this /* r30 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Timer * _t;
}

// Range: 0x8050C80C -> 0x8050D1F8
void RndTransformable::ApplyDynamicConstraint(class RndTransformable * const this /* r31 */) {
    // Local variables
    class Transform t; // r1+0x40
    class Plane p; // r1+0x30
    class Vector3 s; // r1+0x20

    // References
    // -> class RndCam * sCurrent;
    // -> class Plane sShadowPlane;
}

// Range: 0x8050D1F8 -> 0x8050D314
void RndTransformable::SetTransConstraint(class RndTransformable * const this /* r27 */, enum Constraint b /* r28 */, class RndTransformable * t /* r29 */, unsigned char scale /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8050D314 -> 0x8050D5A8
void RndTransformable::Copy(class RndTransformable * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndTransformable * d; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class Symbol name;
}

// Range: 0x8050D5A8 -> 0x8050D68C
static class TextStream & __ls(class TextStream & d /* r31 */) {}

// Range: 0x8050D68C -> 0x8050D794
void RndTransformable::Print(class RndTransformable * const this /* r30 */) {
    // Local variables
    class TextStream & d; // r29

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8050D794 -> 0x8050D800
void RndTransformable::Highlight(class RndTransformable * const this /* r31 */) {}

static int TRANS_REV; // size: 0x4, address: 0x80A47450
// Range: 0x8050D800 -> 0x8050D844
void RndTransformable::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8050D844 -> 0x8050E8B0
void RndTransformable::Load(class RndTransformable * const this /* r28 */, class BinStream & d /* r29 */) {
    // Local variables
    int rev; // r1+0x3C
    class Transform xfm; // r1+0xD0
    class ObjPtrList transes; // r1+0xB8
    class iterator i; // r1+0x38
    int billboard; // r1+0x34
    int billboard; // r1+0x30
    enum Constraint convert[6]; // r1+0xA0
    class Vector3 origin; // r1+0x70
    class Sphere s; // r1+0x80
    class RndDrawable * draw; // r0
    class ObjPtr target; // r1+0x58
    class ObjPtr parent; // r1+0x4C
    class ObjPtr owner; // r1+0x40

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> static int TRANS_REV;
}

static class Symbol _s; // size: 0x4, address: 0x80A53A80
static class Symbol _s; // size: 0x4, address: 0x80A53A88
static class Symbol _s; // size: 0x4, address: 0x80A53A90
static class Symbol _s; // size: 0x4, address: 0x80A53A98
static class Symbol _s; // size: 0x4, address: 0x80A53AA0
static class Symbol _s; // size: 0x4, address: 0x80A53AA8
static class Symbol _s; // size: 0x4, address: 0x80A53AB0
static class Symbol _s; // size: 0x4, address: 0x80A53AB8
static class Symbol _s; // size: 0x4, address: 0x80A53AC0
static class Symbol _s; // size: 0x4, address: 0x80A53AC8
static class Symbol _s; // size: 0x4, address: 0x80A53AD0
static class Symbol _s; // size: 0x4, address: 0x80A53AD8
static class Symbol _s; // size: 0x4, address: 0x80A53AE0
static class Symbol _s; // size: 0x4, address: 0x80A53AE8
static class Symbol _s; // size: 0x4, address: 0x80A53AF0
static class Symbol _s; // size: 0x4, address: 0x80A53AF8
static class Symbol _s; // size: 0x4, address: 0x80A53B00
static class Symbol _s; // size: 0x4, address: 0x80A53B08
static class Symbol _s; // size: 0x4, address: 0x80A53B10
static class Symbol _s; // size: 0x4, address: 0x80A53B18
static class Symbol _s; // size: 0x4, address: 0x80A53B20
// Range: 0x8050E8B0 -> 0x8050F5DC
class DataNode RndTransformable::Handle(class RndTransformable * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x1C
    class MessageTimer _mt; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode r; // r1+0x28
    class DataNode _n; // r1+0x20

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x8050F5DC -> 0x8050F720
class DataNode RndTransformable::OnCopyLocalTo(class RndTransformable * const this /* r29 */, const class DataArray * a /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x8050F720 -> 0x8050F8B8
class DataNode RndTransformable::OnGetWorldForward(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x8050F8B8 -> 0x8050FA50
class DataNode RndTransformable::OnGetWorldPos(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x8050FA50 -> 0x8050FBAC
class DataNode RndTransformable::OnGetLocalPos(class RndTransformable * const this /* r28 */, const class DataArray * a /* r29 */) {}

// Range: 0x8050FBAC -> 0x8050FC60
class DataNode RndTransformable::OnGetLocalPosIndex(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8050FC60 -> 0x8050FFA4
class DataNode RndTransformable::OnGetLocalRot(const class DataArray * a /* r29 */) {
    // Local variables
    class Vector3 e; // r1+0x30
    class Matrix3 m; // r1+0x40
}

// Range: 0x8050FFA4 -> 0x805100A0
class DataNode RndTransformable::OnGetLocalRotIndex(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class Vector3 e; // r1+0x20
    class Vector3 s; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805100A0 -> 0x8051024C
class DataNode RndTransformable::OnGetWorldRot(class RndTransformable * const this /* r30 */, const class DataArray * a /* r29 */) {
    // Local variables
    class Vector3 e; // r1+0x30
}

// Range: 0x8051024C -> 0x8051034C
class DataNode RndTransformable::OnSetLocalPos(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x8051034C -> 0x80510480
class DataNode RndTransformable::OnSetLocalPosIndex(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class Vector3 pos; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80510480 -> 0x80510564
void RndTransformable::SetLocalRot(class RndTransformable * const this /* r31 */) {
    // Local variables
    class Matrix3 m; // r1+0x10
}

// Range: 0x80510564 -> 0x8051064C
class DataNode RndTransformable::OnSetLocalRot(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x8051064C -> 0x8051084C
class DataNode RndTransformable::OnSetLocalRotIndex(class RndTransformable * const this /* r31 */, const class DataArray * a /* r29 */) {
    // Local variables
    class Vector3 e; // r1+0x20
    class Vector3 s; // r1+0x10
    class Matrix3 m; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8051084C -> 0x80510A24
class DataNode RndTransformable::OnSetLocalRotMat(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class Matrix3 m; // r1+0x10
}

// Range: 0x80510A24 -> 0x80510AEC
class DataNode RndTransformable::OnSetLocalScale(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x80510AEC -> 0x80510BE8
class DataNode RndTransformable::OnSetLocalScaleIndex(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class Vector3 v; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80510BE8 -> 0x80510D54
class DataNode RndTransformable::OnGetLocalScale(const class DataArray * a /* r29 */) {
    // Local variables
    class Vector3 v; // r1+0x30
}

// Range: 0x80510D54 -> 0x80510E24
class DataNode RndTransformable::OnGetLocalScaleIndex(class RndTransformable * const this /* r30 */, const class DataArray * a /* r31 */) {
    // Local variables
    class Vector3 v; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80510E24 -> 0x80510EE4
class DataNode RndTransformable::OnSetTransConstraint(class RndTransformable * const this /* r29 */, const class DataArray * a /* r30 */) {
    // Local variables
    class RndTransformable * t; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x80510EE4 -> 0x80510F38
unsigned char RndTransformable::SyncProperty(class DataArray * _prop /* r31 */) {}

struct {
    // total size: 0x9C
} __vt__16RndTransformable; // size: 0x9C, address: 0x80903050
// Range: 0x80510F38 -> 0x80510F3C
static void __sinit_\Trans_cpp() {}


