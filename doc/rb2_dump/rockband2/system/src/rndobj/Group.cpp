/*
    Compile unit: C:\rockband2\system\src\rndobj\Group.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804A00D4 -> 0x804A387C
*/
class DataArray * types; // size: 0x4, address: 0x80A52F88
static unsigned char gInReplace; // size: 0x1, address: 0x80A52F8D
// Range: 0x804A00D4 -> 0x804A02F0
void * RndGroup::RndGroup(class RndGroup * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__8RndGroup;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

static int GROUP_REV; // size: 0x4, address: 0x80A47200
// Range: 0x804A02F0 -> 0x804A0334
void RndGroup::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804A0334 -> 0x804A04C0
void RndGroup::Load(class RndGroup * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int GROUP_REV;
}

// Range: 0x804A04C0 -> 0x804A0928
void RndGroup::Copy(class RndGroup * const this /* r29 */, const class Object * o /* r28 */, enum CopyType type /* r27 */) {
    // Local variables
    const class RndGroup * v; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x804A0928 -> 0x804A0D0C
void RndGroup::AddObject(class RndGroup * const this /* r30 */, class Object * o /* r31 */) {
    // Local variables
    class RndAnimatable * a; // r1+0x44
    class RndDrawable * d; // r1+0x40

    // References
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804A0D0C -> 0x804A0EE4
void RndGroup::RemoveObject(class RndGroup * const this /* r28 */, class Object * o /* r1+0x8 */) {
    // References
    // -> static unsigned char gInReplace;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804A0EE4 -> 0x804A1060
void RndGroup::ClearObjects(class RndGroup * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804A1060 -> 0x804A10DC
void RndGroup::Merge(class RndGroup * const this /* r31 */) {
    // Local variables
    class iterator it; // r1+0x18
}

// Range: 0x804A10DC -> 0x804A131C
void RndGroup::Update(class RndGroup * const this /* r31 */) {
    // Local variables
    class iterator i; // r1+0x44
    class RndAnimatable * a; // r1+0x40
    class RndDrawable * d; // r1+0x3C

    // References
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
}

// Range: 0x804A131C -> 0x804A16C0
void RndGroup::SortDraws(class RndGroup * const this /* r27 */) {
    // Local variables
    class RndDrawable * * d; // r28
    class iterator i; // r1+0x34
    class RndAnimatable * a; // r1+0x30

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804A16C0 -> 0x804A178C
void RndGroup::Replace(class RndGroup * const this /* r28 */, class Object * from /* r29 */, class Object * to /* r30 */) {
    // References
    // -> static unsigned char gInReplace;
}

// Range: 0x804A178C -> 0x804A1818
void RndGroup::SetFrame(class RndGroup * const this /* r30 */, float frame /* f30 */, float blend /* f31 */) {
    // Local variables
    class RndAnimatable * * i; // r31
}

// Range: 0x804A1818 -> 0x804A1898
float RndGroup::EndFrame(class RndGroup * const this /* r30 */) {
    // Local variables
    float end; // f31
    class RndAnimatable * * i; // r31
}

// Range: 0x804A1898 -> 0x804A19A4
void RndGroup::ListAnimChildren() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<P13RndAnimatable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x804A19A4 -> 0x804A1BCC
void RndGroup::DrawShowing(class RndGroup * const this /* r30 */) {
    // Local variables
    class Sphere s; // r1+0x20
    class RndEnvironTracker _rndEnvironTracker; // r1+0x10
    class RndDrawable * * i; // r31

    // References
    // -> const class Vector3 * sCurrentPos;
    // -> class RndEnviron * sCurrent;
    // -> class RndCam * sCurrent;
}

// Range: 0x804A1BCC -> 0x804A1D28
void RndGroup::ListDrawChildren(class RndGroup * const this /* r27 */, class list & l /* r28 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x804A1D28 -> 0x804A1DB4
void RndGroup::CollideList(class RndGroup * const this /* r28 */, const class Segment & segment /* r29 */, class list & collisions /* r30 */) {
    // Local variables
    class RndDrawable * * child; // r31
}

// Range: 0x804A1DB4 -> 0x804A1E6C
int RndGroup::CollidePlane(class RndGroup * const this /* r28 */, const class Plane & plane /* r29 */) {
    // Local variables
    class RndDrawable * * child; // r31
    int inside; // r30
}

// Range: 0x804A1E6C -> 0x804A1FB4
class RndDrawable * RndGroup::CollideShowing(class RndGroup * const this /* r27 */, float & dist /* r28 */, class Plane & plane /* r29 */) {
    // Local variables
    class RndDrawable * collide; // r31
    class RndDrawable * * child; // r30
    class Segment s; // r1+0x20
    float d; // r1+0x10
    class RndDrawable * draw; // r3
}

// Range: 0x804A1FB4 -> 0x804A20FC
void RndGroup::UpdateSphere(class RndGroup * const this /* r30 */) {
    // Local variables
    class Sphere s; // r1+0x20
    class Transform t; // r1+0x40
}

// Range: 0x804A20FC -> 0x804A2268
unsigned char RndGroup::MakeWorldSphere(class RndGroup * const this /* r29 */, class Sphere & s /* r30 */) {
    // Local variables
    class RndDrawable * * c; // r31
    class Sphere s2; // r1+0x10
    class RndTransformable * t; // r0

    // References
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

static class Symbol _s; // size: 0x4, address: 0x80A52F90
static class Symbol _s; // size: 0x4, address: 0x80A52F98
static class Symbol _s; // size: 0x4, address: 0x80A52FA0
static class Symbol _s; // size: 0x4, address: 0x80A52FA8
static class Symbol _s; // size: 0x4, address: 0x80A52FB0
// Range: 0x804A2268 -> 0x804A2DA0
class DataNode RndGroup::Handle(class RndGroup * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode _n; // r1+0x60
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

// Range: 0x804A2DA0 -> 0x804A2F20
class DataNode RndGroup::OnGetDraws(class DataNode * n /* r29 */, class RndGroup * const this /* r30 */) {
    // Local variables
    class DataArray * arr; // r31
    int i; // r28
    class RndDrawable * * d; // r27
}

static class Symbol _s; // size: 0x4, address: 0x80A52FB8
static class Symbol _s; // size: 0x4, address: 0x80A52FC0
static class Symbol _s; // size: 0x4, address: 0x80A52FC8
static class Symbol _s; // size: 0x4, address: 0x80A52FD0
static class Symbol _s; // size: 0x4, address: 0x80A52FD8
// Range: 0x804A2F20 -> 0x804A3244
unsigned char RndGroup::SyncProperty(class RndGroup * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x804A3244 -> 0x804A387C
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class Object * obj; // r31
    class Object * obj; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x160
} __vt__8RndGroup; // size: 0x160, address: 0x808F7D78

