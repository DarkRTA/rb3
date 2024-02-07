/*
    Compile unit: C:\rockband2\system\src\rndobj\Dir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8048098C -> 0x80484448
*/
class Symbol name; // size: 0x4, address: 0x80A52AE4
class DataArray * types; // size: 0x4, address: 0x80A52AE8
class Symbol name; // size: 0x4, address: 0x80A52AF0
class Symbol name; // size: 0x4, address: 0x80A52AF8
// Range: 0x8048098C -> 0x80480BD4
void * RndDir::RndDir(class RndDir * const this /* r30 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndPollable,9ObjectDir>;
    // -> struct [anonymous] __vt__6RndDir;
    // -> struct [anonymous] __vt__9MsgSource;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x80480BD4 -> 0x80480C2C
void RndDir::Replace(class RndDir * const this /* r29 */, class Object * from /* r30 */, class Object * to /* r31 */) {}

// Range: 0x80480C2C -> 0x80480C80
void RndDir::RemovingObject(class RndDir * const this /* r31 */, class Object * o /* r1+0x8 */) {}

// Range: 0x80480C80 -> 0x80480E2C
void RndDir::AddCustomPoll(class RndDir * const this /* r31 */, class RndPollable * poll /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80480E2C -> 0x80480F14
void RndDir::SetSubDir(class RndDir * const this /* r30 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndPollable * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x80480F14 -> 0x80481C68
void RndDir::SyncObjects(class RndDir * const this /* r31 */) {
    // Local variables
    class list draws; // r1+0xF0
    class ObjDirItr i; // r1+0x120
    class RndTexRenderer * texRenderObject; // r0
    struct _List_iterator dc; // r1+0xA8
    class list anims; // r1+0xE8
    class ObjDirItr i; // r1+0x10C
    struct _List_iterator ac; // r1+0xA4
    class list polls; // r1+0xE0
    class ObjDirItr i; // r1+0xF8
    struct _List_iterator pc; // r1+0xA0
    class MsgSource * s; // r4

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__9MsgSource;
    // -> struct [anonymous] __RTTI__11RndPollable;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> struct [anonymous] __RTTI__14RndTexRenderer;
    // -> class Symbol name;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct _OKToSwap {
    // total size: 0x1
};
// Range: 0x80481C68 -> 0x80481DB0
void RndDir::UpdateSphere(class RndDir * const this /* r30 */) {
    // Local variables
    class Sphere s; // r1+0x20
    class Transform t; // r1+0x40
}

// Range: 0x80481DB0 -> 0x80481F1C
unsigned char RndDir::MakeWorldSphere(class RndDir * const this /* r29 */, class Sphere & s /* r30 */) {
    // Local variables
    class RndDrawable * * c; // r31
    class Sphere s2; // r1+0x10
    class RndTransformable * t; // r0

    // References
    // -> struct [anonymous] __RTTI__11RndDrawable;
    // -> struct [anonymous] __RTTI__16RndTransformable;
}

// Range: 0x80481F1C -> 0x80481FD4
void RndDir::Poll(class RndDir * const this /* r30 */) {
    // Local variables
    class RndPollable * * it; // r31
    class iterator i; // r1+0x18
}

// Range: 0x80481FD4 -> 0x80482038
void RndDir::Exit(class RndDir * const this /* r30 */) {
    // Local variables
    class RndPollable * * it; // r31
}

// Range: 0x80482038 -> 0x80482154
void RndDir::ListPollChildren() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndPollable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80482154 -> 0x8048222C
void RndDir::DrawShowing(class RndDir * const this /* r30 */) {
    // Local variables
    class RndEnvironTracker _rndEnvironTracker; // r1+0x8
    class RndDrawable * * i; // r31

    // References
    // -> const class Vector3 * sCurrentPos;
    // -> class RndEnviron * sCurrent;
}

// Range: 0x8048222C -> 0x80482348
void RndDir::ListDrawChildren() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80482348 -> 0x80482400
int RndDir::CollidePlane(class RndDir * const this /* r28 */, const class Plane & plane /* r29 */) {
    // Local variables
    int inside; // r31
    class RndDrawable * * child; // r30
}

// Range: 0x80482400 -> 0x80482574
class RndDrawable * RndDir::CollideShowing(class RndDir * const this /* r27 */, float & dist /* r28 */, class Plane & plane /* r29 */) {
    // Local variables
    class RndDrawable * collide; // r31
    class Segment s; // r1+0x20
    float d; // r1+0x10
    class RndDrawable * * child; // r30
    class RndDrawable * draw; // r3
}

// Range: 0x80482574 -> 0x8048261C
void RndDir::CollideList(class RndDir * const this /* r28 */, const class Segment & s /* r29 */, class list & collisions /* r30 */) {
    // Local variables
    class RndDrawable * * child; // r31
}

// Range: 0x8048261C -> 0x804826A8
void RndDir::SetFrame(class RndDir * const this /* r30 */, float frame /* f30 */, float blend /* f31 */) {
    // Local variables
    class RndAnimatable * * c; // r31
}

// Range: 0x804826A8 -> 0x80482728
float RndDir::EndFrame(class RndDir * const this /* r30 */) {
    // Local variables
    float end; // f31
    class RndAnimatable * * c; // r31
}

// Range: 0x80482728 -> 0x80482844
void RndDir::ListAnimChildren() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<P13RndAnimatable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x80482844 -> 0x80482930
void RndDir::Export(class RndDir * const this /* r28 */, class DataArray * msg /* r29 */) {
    // Local variables
    int i; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80482930 -> 0x80482A18
void RndDir::Copy(class RndDir * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndDir * m; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndDir;
}

// Range: 0x80482A18 -> 0x80482A1C
void RndDir::Load() {}

// Range: 0x80482A1C -> 0x80482D18
void RndDir::PostLoad(class RndDir * const this /* r28 */, class BinStream & d /* r31 */) {
    // Local variables
    class ObjPtr env; // r1+0x1C
    class Symbol testEvent; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__11RndPostProc;
    // -> class Symbol name;
    // -> const char * gNullStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> unsigned char gLoadingProxyFromDisk;
    // -> class list sRevs;
}

static class Symbol _s; // size: 0x4, address: 0x80A52B00
static class Symbol _s; // size: 0x4, address: 0x80A52B08
// Range: 0x80482D18 -> 0x80483850
class DataNode RndDir::Handle(class RndDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode _n; // r1+0x68
    class DataNode _n; // r1+0x60
    class DataNode _n; // r1+0x58
    class DataNode _n; // r1+0x50
    class DataNode _n; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80483850 -> 0x8048392C
class DataNode RndDir::OnShowObjects(class DataArray * msg /* r29 */) {
    // Local variables
    class DataArray * objs; // r30
    unsigned char show; // r0
    int i; // r29

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
}

class list : public _List_base {
    // total size: 0x8
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class EventTrigger * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x8048392C -> 0x80483E50
class DataNode RndDir::OnSupportedEvents(class RndDir * const this /* r28 */) {
    // Local variables
    int idx; // r31
    class DataArrayPtr da; // r1+0x48
    class list events; // r1+0x40
    class ObjDirItr i; // r1+0x50
    class DataArray * a; // r1+0x24
    int j; // r28

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std23_List_node<P9DataArray>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class DataArray * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
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
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std23_List_node<P9DataArray>; // size: 0x8, address: 0x808F4460
static class Symbol _s; // size: 0x4, address: 0x80A52B10
static class Symbol _s; // size: 0x4, address: 0x80A52B18
static class Symbol _s; // size: 0x4, address: 0x80A52B20
// Range: 0x80483E50 -> 0x804840F8
unsigned char RndDir::SyncProperty(class RndDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x804840F8 -> 0x80484448
unsigned char PropSync(class vector & v /* r29 */, class DataNode & n /* r30 */, class DataArray * prop /* r26 */, int i /* r27 */, enum PropOp op /* r28 */) {
    // Local variables
    class RndPollable * * it; // r31
    class RndPollable * tmp; // r1+0x14

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPollable;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x21C
} __vt__6RndDir; // size: 0x21C, address: 0x808F4590
struct {
    // total size: 0x8
} __RTTI__PP11RndPollable; // size: 0x8, address: 0x808F4AF8
struct {
    // total size: 0x8
} __RTTI__PP13RndAnimatable; // size: 0x8, address: 0x808F4B18

