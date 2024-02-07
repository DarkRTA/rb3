/*
    Compile unit: C:\rockband2\system\src\char\Waypoint.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803B48F8 -> 0x803B7388
*/
class DataArray * types; // size: 0x4, address: 0x80A516C0
class list sWaypoints; // size: 0x8, address: 0x8097E0A8
unsigned char sShowGraph; // size: 0x1, address: 0x80A516C5
// Range: 0x803B48F8 -> 0x803B49C0
void Waypoint::Init() {
    // References
    // -> class Symbol name;
}

// Range: 0x803B49C0 -> 0x803B4A24
class Waypoint * Waypoint::Find() {
    // Local variables
    struct _List_iterator it; // r1+0x10

    // References
    // -> class list sWaypoints;
}

// Range: 0x803B4A24 -> 0x803B4B58
class Waypoint * Waypoint::FindNearest(const class Vector3 & p /* r27 */, int flags /* r28 */) {
    // Local variables
    float dist; // f31
    class Waypoint * best; // r29
    struct _List_iterator it; // r1+0x18

    // References
    // -> class list sWaypoints;
}

class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class Waypoint * mPtr; // offset 0x8, size 0x4
};
// Range: 0x803B4B58 -> 0x803B4BC0
class DataNode Waypoint::OnWaypointFind(class DataArray * msg /* r31 */) {}

// Range: 0x803B4BC0 -> 0x803B4C7C
class DataNode Waypoint::OnWaypointNearest(class DataArray * msg /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x803B4C7C -> 0x803B4C9C
class DataNode Waypoint::OnWaypointToggleShow() {
    // References
    // -> unsigned char sShowGraph;
}

// Range: 0x803B4C9C -> 0x803B4D90
class DataNode Waypoint::OnWaypointLast(class DataArray * msg /* r31 */) {
    // Local variables
    class Waypoint * w; // r0
    struct _List_iterator it; // r1+0x24

    // References
    // -> class list sWaypoints;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Waypoint;
}

// Range: 0x803B4D90 -> 0x803B4F88
void * Waypoint::Waypoint(class Waypoint * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8Waypoint>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sWaypoints;
    // -> struct [anonymous] __vt__8Waypoint;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x803B4F88 -> 0x803B51B4
void * Waypoint::~Waypoint(class Waypoint * const this /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x2C

    // References
    // -> class list sWaypoints;
    // -> struct [anonymous] __vt__8Waypoint;
}

// Range: 0x803B51B4 -> 0x803B539C
void Waypoint::Replace(class Waypoint * const this /* r26 */, class Object * from /* r27 */, class Object * to /* r28 */) {
    // Local variables
    int i; // r29

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Waypoint;
}

static class Timer * _t; // size: 0x4, address: 0x80A516C8
static class Timer * _t; // size: 0x4, address: 0x80A516D0
// Range: 0x803B539C -> 0x803B5AD4
void Waypoint::DrawShowing(class Waypoint * const this /* r30 */) {
    // Local variables
    class Box b; // r1+0xF0
    float rad; // f31
    class Vector3 line; // r1+0xE0
    int i; // r31
    class Vector3 a; // r1+0xD0
    class Vector3 b; // r1+0xC0
    class Vector3 mid; // r1+0xB0
    class Vector3 delta; // r1+0xA0

    // References
    // -> static class Timer * _t;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class Rnd & TheRnd;
    // -> unsigned char sShowGraph;
    // -> static class Timer * _t;
}

// Range: 0x803B5AD4 -> 0x803B5BC0
void Waypoint::Constrain(class Waypoint * const this /* r30 */, class Transform & t /* r31 */) {
    // Local variables
    class Vector3 delta; // r1+0x10
    float ang; // f2
    float dang; // f0
}

// Range: 0x803B5BC0 -> 0x803B5BCC
void Waypoint::ShapeDelta() {}

// Range: 0x803B5BCC -> 0x803B5BD8
float Waypoint::ShapeDelta() {}

// Range: 0x803B5BD8 -> 0x803B5E3C
void Waypoint::ShapeDeltaBox(class Waypoint * const this /* r29 */, const class Vector3 & pos /* r30 */, float xradius /* f30 */, float yradius /* f31 */, class Vector3 & delta /* r31 */) {
    // Local variables
    float x; // f0
    float y; // f2
    float newX; // f0
    float newY; // f0
    float l; // f0
}

// Range: 0x803B5E3C -> 0x803B5F08
float Waypoint::ShapeDeltaAng(class Waypoint * const this /* r31 */, float angLimit /* f30 */, float ang /* f31 */) {
    // Local variables
    float delta; // f0
}

// Range: 0x803B5F08 -> 0x803B6160
void Waypoint::Copy(class Waypoint * const this /* r28 */, const class Object * o /* r26 */, enum CopyType type /* r25 */) {
    // Local variables
    const class Waypoint * w; // r0

    // References
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8Waypoint,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Waypoint;
}

// Range: 0x803B6160 -> 0x803B6240
void Waypoint::Save(class Waypoint * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803B6240 -> 0x803B630C
class BinStream & __ls(class BinStream & d /* r30 */, const class ObjOwnerPtr & f /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803B630C -> 0x803B646C
void Waypoint::Load(class Waypoint * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A516D8
static class Symbol _s; // size: 0x4, address: 0x80A516E0
static class Symbol _s; // size: 0x4, address: 0x80A516E8
static class Symbol _s; // size: 0x4, address: 0x80A516F0
static class Symbol _s; // size: 0x4, address: 0x80A516F8
static class Symbol _s; // size: 0x4, address: 0x80A51700
// Range: 0x803B646C -> 0x803B69F0
unsigned char Waypoint::SyncProperty(class Waypoint * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> unsigned char sShowGraph;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x803B69F0 -> 0x803B6CC0
unsigned char PropSync(class ObjVector & v /* r29 */, class DataNode & n /* r30 */, class DataArray * prop /* r26 */, int i /* r28 */, enum PropOp op /* r27 */) {
    // Local variables
    class ObjOwnerPtr * it; // r31
    class ObjOwnerPtr tmp; // r1+0x20

    // References
    // -> struct [anonymous] __vt__33ObjOwnerPtr<8Waypoint,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803B6CC0 -> 0x803B6E0C
unsigned char PropSync(class ObjOwnerPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Waypoint;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803B6E0C -> 0x803B732C
class DataNode Waypoint::Handle(class Waypoint * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

struct {
    // total size: 0x18
} __vt__33ObjOwnerPtr<8Waypoint,9ObjectDir>; // size: 0x18, address: 0x808DF208
struct {
    // total size: 0x8
} __RTTI__33ObjOwnerPtr<8Waypoint,9ObjectDir>; // size: 0x8, address: 0x808DF250
struct {
    // total size: 0xF4
} __vt__8Waypoint; // size: 0xF4, address: 0x808DF258
struct {
    // total size: 0x8
} __RTTI__P33ObjOwnerPtr<8Waypoint,9ObjectDir>; // size: 0x8, address: 0x808DF520
// Range: 0x803B732C -> 0x803B7388
static void __sinit_\Waypoint_cpp() {
    // References
    // -> class list sWaypoints;
}


