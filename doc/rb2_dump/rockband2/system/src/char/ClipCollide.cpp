/*
    Compile unit: C:\rockband2\system\src\char\ClipCollide.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8039F34C -> 0x803A3A44
*/
class DataArray * types; // size: 0x4, address: 0x80A514C0
// Range: 0x8039F34C -> 0x8039F4E0
void * ClipCollide::~ClipCollide(class ClipCollide * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__29ObjPtr<9Character,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8Waypoint,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8CharClip,9ObjectDir>;
    // -> struct [anonymous] __vt__11ClipCollide;
}

// Range: 0x8039F4E0 -> 0x8039F5D8
void ClipCollide::SyncChar(class ClipCollide * const this /* r29 */) {
    // Local variables
    class FilePath f; // r1+0x14
    class FilePath cur; // r1+0x8

    // References
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

static class Symbol front; // size: 0x4, address: 0x80A514C8
static class Symbol back; // size: 0x4, address: 0x80A514D0
static class Symbol left; // size: 0x4, address: 0x80A514D8
static class Symbol right; // size: 0x4, address: 0x80A514E0
// Range: 0x8039F5D8 -> 0x8039F904
void ClipCollide::SyncWaypoint(class ClipCollide * const this /* r31 */) {
    // Local variables
    class Transform t; // r1+0x10
    float yRadius; // f0

    // References
    // -> static class Symbol right;
    // -> static class Symbol left;
    // -> static class Symbol back;
    // -> static class Symbol front;
}

// Range: 0x8039F904 -> 0x8039FD04
void ClipCollide::AddReport(class ClipCollide * const this /* r30 */, class Vector3 & pos /* r31 */) {
    // Local variables
    struct Report r; // r1+0x50
    class String p; // r1+0x40

    // References
    // -> const char * gNullStr;
}

// Range: 0x8039FD04 -> 0x803A0320
void ClipCollide::PickReport(class ClipCollide * const this /* r30 */, const char * r /* r27 */) {
    // Local variables
    int which; // r0
    class Message mc; // r1+0x28
    class DataNode n; // r1+0x20
    class Vector3 dir; // r1+0x40
    class Transform t; // r1+0x50

    // References
    // -> struct [anonymous] __RTTI__6RndCam;
    // -> struct [anonymous] __vt__7Message;
    // -> class ObjectDir * sMainDir;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8CharClip;
}

// Range: 0x803A0320 -> 0x803A0634
void ClipCollide::ClearReport(class ClipCollide * const this /* r31 */) {}

// Range: 0x803A0634 -> 0x803A068C
void ClipCollide::Demonstrate(class ClipCollide * const this /* r31 */) {}

// Range: 0x803A068C -> 0x803A06C0
unsigned char ClipCollide::ValidState() {}

// Range: 0x803A06C0 -> 0x803A0754
void ClipCollide::SetTypeDef(class ClipCollide * const this /* r30 */, class DataArray * d /* r31 */) {}

// Range: 0x803A0754 -> 0x803A0BB4
void ClipCollide::Collide(class ClipCollide * const this /* r28 */) {
    // Local variables
    class RndDrawable * w; // r31
    char * names[3]; // r1+0x7C
    class RndTransformable * meshes[3]; // r1+0x70
    class Vector3 points[3]; // r1+0xB0
    int i; // r29
    class CharServoBone * b; // r30
    float delta; // f31
    float f; // f30
    int i; // r29
    class Vector3 p; // r1+0x60
    class Segment s; // r1+0x90
    float dist; // r1+0x10
    class Plane plane; // r1+0x50
    class RndDrawable * d; // r26
    class Vector3 pos; // r1+0x40
    unsigned char punt; // r27
    class RndMesh * mesh; // r0

    // References
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__11RndDrawable;
}

// Range: 0x803A0BB4 -> 0x803A0BD4
class CharClipSet * ClipCollide::Clips() {}

static class Message vw; // size: 0x8, address: 0x8097E018
// Range: 0x803A0BD4 -> 0x803A0E54
unsigned char ClipCollide::ValidWaypoint(class ClipCollide * const this /* r30 */, class Waypoint * w /* r31 */) {
    // Local variables
    class DataNode ret; // r1+0x28

    // References
    // -> static class Message vw;
    // -> struct [anonymous] __vt__7Message;
}

static class Message vw; // size: 0x8, address: 0x8097E030
// Range: 0x803A0E54 -> 0x803A11A4
unsigned char ClipCollide::ValidClip(class ClipCollide * const this /* r30 */, class CharClip * clip /* r31 */) {
    // Local variables
    class DataNode ret; // r1+0x38

    // References
    // -> static class Message vw;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x803A11A4 -> 0x803A12AC
void ClipCollide::TestChars(class ClipCollide * const this /* r29 */) {
    // Local variables
    class DataArray * chars; // r31
    int i; // r30
    class String s; // r1+0xC
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class Waypoint * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x803A12AC -> 0x803A1628
void ClipCollide::TestWaypoints(class ClipCollide * const this /* r31 */) {
    // Local variables
    class ObjDirItr w; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Waypoint;
}

// Range: 0x803A1628 -> 0x803A1758
void ClipCollide::TestClips(class ClipCollide * const this /* r30 */) {
    // Local variables
    class CharClipSet * clips; // r0
    int i; // r31
    class CharClip * c; // r28
    char * poses[4]; // r1+0x10
    int j; // r27
}

// Range: 0x803A1758 -> 0x803A1A00
class DataNode ClipCollide::OnVenueName() {
    // Local variables
    class String s; // r1+0x28
    class Message cf; // r1+0x20
    class DataNode n; // r1+0x18
    char buffer[256]; // r1+0x38
    int len; // r0
    char * c; // r4

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> class ObjectDir * sMainDir;
}

int gRev; // size: 0x4, address: 0x80A514E8
// Range: 0x803A1A00 -> 0x803A1A88
void ClipCollide::Save(class ClipCollide * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803A1A88 -> 0x803A1B8C
void ClipCollide::Load(class ClipCollide * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> int gRev;
}

// Range: 0x803A1B8C -> 0x803A1BD8
void ClipCollide::Copy(const class Object * o /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11ClipCollide;
}

// Range: 0x803A1BD8 -> 0x803A1D80
void ClipCollide::SyncMode(class ClipCollide * const this /* r31 */) {
    // Local variables
    class Message m; // r1+0x30

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A514F0
static class Symbol _s; // size: 0x4, address: 0x80A514F8
static class Symbol _s; // size: 0x4, address: 0x80A51500
static class Symbol _s; // size: 0x4, address: 0x80A51508
static class Symbol _s; // size: 0x4, address: 0x80A51510
static class Symbol _s; // size: 0x4, address: 0x80A51518
static class Symbol _s; // size: 0x4, address: 0x80A51520
static class Symbol _s; // size: 0x4, address: 0x80A51528
static class Symbol _s; // size: 0x4, address: 0x80A51530
static class Symbol _s; // size: 0x4, address: 0x80A51538
// Range: 0x803A1D80 -> 0x803A2AA4
class DataNode ClipCollide::Handle(class ClipCollide * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x48
    class MessageTimer _mt; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode _n; // r1+0x50

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
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x803A2AA4 -> 0x803A2D5C
class DataNode ClipCollide::OnListClips(class DataNode * ret /* r30 */, class ClipCollide * const this /* r31 */) {
    // Local variables
    class list l; // r1+0x58
    class CharClipSet * clips; // r0
    int i; // r28
    class CharClip * c; // r27
    int i; // r27
    struct _List_iterator it; // r1+0x34

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8CharClip>;
    // -> unsigned char gStlAllocNameLookup;
}

class list : public _List_base {
    // total size: 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x803A2D5C -> 0x803A32BC
class DataNode ClipCollide::OnListWaypoints(class DataNode * ret /* r29 */, class ClipCollide * const this /* r30 */) {
    // Local variables
    class list l; // r1+0x68
    class ObjDirItr w; // r1+0x70
    int i; // r30
    struct _List_iterator it; // r1+0x44

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8Waypoint>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Waypoint;
}

class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class Waypoint * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<P8Waypoint>; // size: 0x8, address: 0x808DD8C8
static class Symbol _s; // size: 0x4, address: 0x80A51540
static class Symbol _s; // size: 0x4, address: 0x80A51548
static class Symbol _s; // size: 0x4, address: 0x80A51550
static class Symbol _s; // size: 0x4, address: 0x80A51558
static class Symbol _s; // size: 0x4, address: 0x80A51560
static class Symbol _s; // size: 0x4, address: 0x80A51568
static class Symbol _s; // size: 0x4, address: 0x80A51570
static class Symbol _s; // size: 0x4, address: 0x80A51578
static class Symbol _s; // size: 0x4, address: 0x80A51580
static class Symbol _s; // size: 0x4, address: 0x80A51588
// Range: 0x803A32BC -> 0x803A3A44
unsigned char ClipCollide::SyncProperty(class ClipCollide * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x54
} __vt__11ClipCollide; // size: 0x54, address: 0x808DD9F8
struct {
    // total size: 0x8
} __RTTI__11ClipCollide; // size: 0x8, address: 0x808DDA70
struct {
    // total size: 0x18
} __vt__29ObjPtr<9Character,9ObjectDir>; // size: 0x18, address: 0x808DDAC0
struct {
    // total size: 0x8
} __RTTI__29ObjPtr<9Character,9ObjectDir>; // size: 0x8, address: 0x808DDB08
struct {
    // total size: 0x8
} __RTTI__PQ211ClipCollide6Report; // size: 0x8, address: 0x808DDEB8

