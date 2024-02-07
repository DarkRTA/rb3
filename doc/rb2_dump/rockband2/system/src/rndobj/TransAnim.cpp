/*
    Compile unit: C:\rockband2\system\src\rndobj\TransAnim.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80511078 -> 0x805163FC
*/
class DataArray * types; // size: 0x4, address: 0x80A53B28
// Range: 0x80511078 -> 0x8051119C
void * RndTransAnim::RndTransAnim(class RndTransAnim * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__38ObjOwnerPtr<12RndTransAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__37ObjPtr<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__12RndTransAnim;
}

// Range: 0x8051119C -> 0x80511210
void RndTransAnim::SetTrans(class RndTransAnim * const this /* r30 */, class RndTransformable * o /* r31 */) {}

// Range: 0x80511210 -> 0x805112F8
void RndTransAnim::Replace(class RndTransAnim * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
}

static int TRANSANIM_REV; // size: 0x4, address: 0x80A4745C
// Range: 0x805112F8 -> 0x8051133C
void RndTransAnim::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8051133C -> 0x805115E0
void RndTransAnim::Load(class RndTransAnim * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x14

    // References
    // -> class Debug TheDebug;
    // -> static int TRANSANIM_REV;
}

// Range: 0x805115E0 -> 0x805119E4
void RndTransAnim::Copy(class RndTransAnim * const this /* r30 */, const class Object * o /* r29 */, enum CopyType type /* r28 */) {
    // Local variables
    const class RndTransAnim * t; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
}

// Range: 0x805119E4 -> 0x80511BBC
void RndTransAnim::Print(class RndTransAnim * const this /* r27 */) {
    // Local variables
    class TextStream & d; // r28

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80511BBC -> 0x80511D60
float RndTransAnim::EndFrame(class RndTransAnim * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80511D60 -> 0x80511F04
float RndTransAnim::StartFrame(class RndTransAnim * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80511F04 -> 0x80512778
void RndTransAnim::MakeTransform(class RndTransAnim * const this /* r23 */, float frame /* f30 */, class Transform & t /* r24 */, unsigned char whole /* r26 */, float blend /* f31 */) {
    // Local variables
    class Vector3 tangent; // r1+0x80
    class Vector3 repeat; // r1+0x70
    int n; // r0
    class Vector3 v; // r1+0x60
    class Vector3 blendScale; // r1+0x50
    class Quat q; // r1+0x40
    const class Quat * prev; // r26
    const class Quat * next; // r25
    float r; // f29
    class Quat q1; // r1+0x30
    class Vector3 s; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80512778 -> 0x805128C0
void RndTransAnim::SetFrame(class RndTransAnim * const this /* r31 */) {
    // Local variables
    class Transform t; // r1+0x10
}

// Range: 0x805128C0 -> 0x80513474
void RndTransAnim::SetKey(class RndTransAnim * const this /* r24 */, float frame /* f31 */) {
    // Local variables
    class Matrix3 m; // r1+0x90
    class Vector3 s; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A53B30
static class Symbol _s; // size: 0x4, address: 0x80A53B38
static class Symbol _s; // size: 0x4, address: 0x80A53B40
static class Symbol _s; // size: 0x4, address: 0x80A53B48
static class Symbol _s; // size: 0x4, address: 0x80A53B50
static class Symbol _s; // size: 0x4, address: 0x80A53B58
static class Symbol _s; // size: 0x4, address: 0x80A53B60
static class Symbol _s; // size: 0x4, address: 0x80A53B68
static class Symbol _s; // size: 0x4, address: 0x80A53B70
static class Symbol _s; // size: 0x4, address: 0x80A53B78
static class Symbol _s; // size: 0x4, address: 0x80A53B80
static class Symbol _s; // size: 0x4, address: 0x80A53B88
static class Symbol _s; // size: 0x4, address: 0x80A53B90
// Range: 0x80513474 -> 0x805149A8
class DataNode RndTransAnim::Handle(class RndTransAnim * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x58
    class MessageTimer _mt; // r1+0xD8
    class DataNode r; // r1+0xD0
    class DataNode r; // r1+0xC8
    class DataNode r; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode _n; // r1+0x68
    class DataNode _n; // r1+0x60

    // References
    // -> class Debug TheDebug;
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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x805149A8 -> 0x80514A54
class DataNode RndTransAnim::OnSetTransSpline(class RndTransAnim * const this /* r30 */, const class DataArray * a /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80514A54 -> 0x80514B00
class DataNode RndTransAnim::OnSetScaleSpline(class RndTransAnim * const this /* r30 */, const class DataArray * a /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80514B00 -> 0x80514BAC
class DataNode RndTransAnim::OnSetRotSlerp(class RndTransAnim * const this /* r30 */, const class DataArray * a /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80514BAC -> 0x80514BD0
class DataNode RndTransAnim::OnTrans() {}

// Range: 0x80514BD0 -> 0x80514C60
class DataNode RndTransAnim::OnNumTransKeys(class RndTransAnim * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80514C60 -> 0x80514CF0
class DataNode RndTransAnim::OnNumRotKeys(class RndTransAnim * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80514CF0 -> 0x80514D80
class DataNode RndTransAnim::OnNumScaleKeys(class RndTransAnim * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80514D80 -> 0x805150FC
class DataNode RndTransAnim::OnAddTransKey(class RndTransAnim * const this /* r29 */, const class DataArray * a /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805150FC -> 0x80515478
class DataNode RndTransAnim::OnAddScaleKey(class RndTransAnim * const this /* r29 */, const class DataArray * a /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80515478 -> 0x80515810
class DataNode RndTransAnim::OnAddRotKey(class RndTransAnim * const this /* r29 */, const class DataArray * a /* r28 */) {
    // Local variables
    class Vector3 v; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80515810 -> 0x80515D14
class DataNode RndTransAnim::OnRemoveRotKeys(class RndTransAnim * const this /* r28 */, const class DataArray * a /* r26 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80515D14 -> 0x80516218
class DataNode RndTransAnim::OnRemoveTransKeys(class RndTransAnim * const this /* r28 */, const class DataArray * a /* r26 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80516218 -> 0x805162A0
class DataNode RndTransAnim::OnSetTrans(class RndTransAnim * const this /* r30 */, const class DataArray * a /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

static class Symbol _s; // size: 0x4, address: 0x80A53B98
// Range: 0x805162A0 -> 0x805163FC
unsigned char RndTransAnim::SyncProperty(class RndTransAnim * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndTransAnim;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xA8
} __vt__12RndTransAnim; // size: 0xA8, address: 0x809036A8
struct {
    // total size: 0x18
} __vt__38ObjOwnerPtr<12RndTransAnim,9ObjectDir>; // size: 0x18, address: 0x80903788
struct {
    // total size: 0x8
} __RTTI__38ObjOwnerPtr<12RndTransAnim,9ObjectDir>; // size: 0x8, address: 0x809037D8

