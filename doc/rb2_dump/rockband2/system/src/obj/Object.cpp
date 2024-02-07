/*
    Compile unit: C:\rockband2\system\src\obj\Object.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805F1190 -> 0x805F3C6C
*/
unsigned char gLoadingProxyFromDisk; // size: 0x1, address: 0x80A55090
class map {
    // total size: 0x18
public:
    class _Rb_tree _M_t; // offset 0x0, size 0x18
};
class map sFactories; // size: 0x18, address: 0x80989610
class Object * sDeleting; // size: 0x4, address: 0x80A55094
class list sRevs; // size: 0x8, address: 0x80989638
// Range: 0x805F1190 -> 0x805F11A4
class ObjectDir * Object::DataDir() {
    // References
    // -> class ObjectDir * sMainDir;
}

struct _Rb_tree_iterator : public _Rb_tree_base_iterator {
    // total size: 0x4
};
// Range: 0x805F11A4 -> 0x805F1270
class Object * Object::NewObject() {
    // Local variables
    struct _Rb_tree_iterator i; // r1+0x14

    // References
    // -> class Debug TheDebug;
    // -> class map sFactories;
}

// Range: 0x805F1270 -> 0x805F1364
void Object::RegisterFactory(class Object * (* f)() /* r31 */) {
    // References
    // -> class map sFactories;
}

// Range: 0x805F1364 -> 0x805F13F0
unsigned char Object::RegisteredFactory() {
    // References
    // -> class map sFactories;
}

// Range: 0x805F13F0 -> 0x805F1454
void * Object::Object() {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__9TypeProps;
    // -> struct [anonymous] __vt__Q23Hmx6Object;
}

// Range: 0x805F1454 -> 0x805F15FC
void * Object::~Object(class Object * const this /* r30 */) {
    // Local variables
    class Object * deleting; // r29
    struct _List_iterator i; // r1+0x1C

    // References
    // -> struct [anonymous] __vt__9TypeProps;
    // -> const char * gNullStr;
    // -> class Object * sDeleting;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct OSThread * gMainThreadID;
    // -> struct [anonymous] __vt__Q23Hmx6Object;
}

// Range: 0x805F15FC -> 0x805F16A0
void Object::SetNote(class Object * const this /* r29 */, const char * note /* r30 */) {
    // References
    // -> const char * gNullStr;
}

// Range: 0x805F16A0 -> 0x805F17AC
void Object::SetName(class Object * const this /* r28 */, const char * name /* r29 */, class ObjectDir * dir /* r30 */) {
    // Local variables
    struct Entry * entry; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> const char * gNullStr;
}

// Range: 0x805F17AC -> 0x805F18A0
void Object::RemoveFromDir(class Object * const this /* r29 */) {
    // Local variables
    struct Entry * entry; // r0

    // References
    // -> class Debug TheDebug;
    // -> class Object * sDeleting;
}

// Range: 0x805F18A0 -> 0x805F1930
void Object::SetTypeDef(class Object * const this /* r30 */, class DataArray * a /* r31 */) {}

static class DataNode n; // size: 0x8, address: 0x80989650
// Range: 0x805F1930 -> 0x805F1AF8
class DataNode * Object::Property(class Object * const this /* r28 */, class DataArray * prop /* r29 */, unsigned char fail /* r30 */) {
    // Local variables
    class Symbol name; // r1+0x18
    const class DataNode * val; // r31
    class DataArray * p; // r0
    class DataArray * a; // r31

    // References
    // -> class Debug TheDebug;
    // -> static class DataNode n;
}

static class DataArrayPtr d; // size: 0x8, address: 0x80989668
// Range: 0x805F1AF8 -> 0x805F1C70
class DataNode * Object::Property(class Object * const this /* r30 */, class Symbol & prop /* r29 */, unsigned char fail /* r31 */) {
    // References
    // -> static class DataArrayPtr d;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

static class DataNode n; // size: 0x8, address: 0x80989680
// Range: 0x805F1C70 -> 0x805F1DB4
class DataNode Object::HandleProperty(class Object * const this /* r28 */, class DataArray * prop /* r29 */, unsigned char fail /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static class DataNode n;
}

// Range: 0x805F1DB4 -> 0x805F1ECC
void Object::SetProperty(class Object * const this /* r29 */, class DataArray * prop /* r30 */, const class DataNode & val /* r31 */) {
    // Local variables
    class Symbol name; // r1+0x18

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class DataArrayPtr d; // size: 0x8, address: 0x80989698
// Range: 0x805F1ECC -> 0x805F2044
void Object::SetProperty(class Object * const this /* r30 */, class Symbol & prop /* r29 */, const class DataNode & val /* r31 */) {
    // References
    // -> static class DataArrayPtr d;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

static class DataNode n; // size: 0x8, address: 0x809896B0
// Range: 0x805F2044 -> 0x805F221C
int Object::PropertySize(class Object * const this /* r28 */, class DataArray * prop /* r29 */) {
    // Local variables
    class Symbol name; // r1+0x1C
    const class DataNode * a; // r31
    class DataArray * p; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class DataNode n;
}

static class DataNode n; // size: 0x8, address: 0x809896C8
// Range: 0x805F221C -> 0x805F2344
void Object::RemoveProperty(class Object * const this /* r29 */, class DataArray * prop /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class DataNode n;
}

// Range: 0x805F2344 -> 0x805F2438
void Object::InsertProperty(class Object * const this /* r28 */, class DataArray * prop /* r29 */, const class DataNode & val /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x805F2438 -> 0x805F24D8
void Object::AddRef(class Object * const this /* r30 */, class ObjRef * o /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6ObjRef>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x805F24D8 -> 0x805F25A4
void Object::Release(class Object * const this /* r30 */, class ObjRef * o /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x1C

    // References
    // -> class Object * sDeleting;
}

// Range: 0x805F25A4 -> 0x805F26A4
void Object::Save(class Object * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int s; // r31

    // References
    // -> const char * gNullStr;
}

// Range: 0x805F26A4 -> 0x805F26A8
void Object::Replace() {}

static class Symbol _s; // size: 0x4, address: 0x80A550A0
static class Symbol _s; // size: 0x4, address: 0x80A550A8
static class Symbol _s; // size: 0x4, address: 0x80A550B0
static class Symbol _s; // size: 0x4, address: 0x80A550B8
static class Symbol _s; // size: 0x4, address: 0x80A550C0
static class Symbol _s; // size: 0x4, address: 0x80A550C8
static class Symbol _s; // size: 0x4, address: 0x80A550D0
static class Symbol _s; // size: 0x4, address: 0x80A550D8
static class Symbol _s; // size: 0x4, address: 0x80A550E0
static class Symbol _s; // size: 0x4, address: 0x80A550E8
static class Symbol _s; // size: 0x4, address: 0x80A550F0
static class Symbol _s; // size: 0x4, address: 0x80A550F8
static class Symbol _s; // size: 0x4, address: 0x80A55100
static class Symbol _s; // size: 0x4, address: 0x80A55108
static class Symbol _s; // size: 0x4, address: 0x80A55110
static class Symbol _s; // size: 0x4, address: 0x80A55118
static class Symbol _s; // size: 0x4, address: 0x80A55120
static class Symbol _s; // size: 0x4, address: 0x80A55128
static class Symbol _s; // size: 0x4, address: 0x80A55130
static class Symbol _s; // size: 0x4, address: 0x80A55138
// Range: 0x805F26A8 -> 0x805F31B8
class DataNode Object::Handle(class Object * const this /* r27 */, class DataArray * _msg /* r28 */, unsigned char _warn /* r29 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataArray * handler; // r30
    class DataNode r; // r1+0x30

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
}

// Range: 0x805F31B8 -> 0x805F3344
class DataNode Object::HandleType(class Object * const this /* r28 */, class DataArray * msg /* r29 */) {
    // Local variables
    class DataArray * handler; // r30
    class Symbol t; // r1+0x1C
    class MessageTimer mt; // r1+0x20

    // References
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x805F3344 -> 0x805F34E8
class DataNode Object::OnIterateRefs(class Object * const this /* r29 */, const class DataArray * data /* r30 */) {
    // Local variables
    class DataNode * var; // r31
    class DataNode val; // r1+0x30
    struct _List_iterator i; // r1+0x1C
    int j; // r27
}

// Range: 0x805F34E8 -> 0x805F3644
class DataNode Object::OnSet(class Object * const this /* r28 */, const class DataArray * data /* r29 */) {
    // Local variables
    int i; // r30
    class String s; // r1+0xC

    // References
    // -> class Debug TheDebug;
}

static class DataArrayPtr d; // size: 0x8, address: 0x809896E0
static class DataArrayPtr path; // size: 0x8, address: 0x809896F8
// Range: 0x805F3644 -> 0x805F39F4
class DataNode Object::OnGetArray(class Object * const this /* r29 */, const class DataArray * data /* r25 */) {
    // Local variables
    class Symbol prop; // r1+0x18
    int size; // r30
    class DataArrayPtr array; // r1+0x40
    int i; // r25

    // References
    // -> static class DataArrayPtr path;
    // -> static class DataArrayPtr d;
    // -> struct [anonymous] __vt__12DataArrayPtr;
}

// Range: 0x805F39F4 -> 0x805F3B54
class DataNode Object::OnGet(class Object * const this /* r28 */, const class DataArray * data /* r31 */) {
    // Local variables
    const class DataNode * r; // r4
    class String s; // r1+0xC
    const class DataNode * r; // r4

    // References
    // -> class Debug TheDebug;
}

// Range: 0x805F3B54 -> 0x805F3BA8
unsigned char Object::SyncProperty(class DataArray * _prop /* r31 */) {}

struct {
    // total size: 0x54
} __vt__Q23Hmx6Object; // size: 0x54, address: 0x80929E70
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x10
public:
    struct _Rb_tree_node_base _M_data; // offset 0x0, size 0x10
};
struct _Rb_tree_base {
    // total size: 0x10
protected:
    class _STLP_alloc_proxy _M_header; // offset 0x0, size 0x10
};
class _Rb_tree : public _Rb_tree_base {
    // total size: 0x18
protected:
    unsigned long _M_node_count; // offset 0x10, size 0x4
    struct less _M_key_compare; // offset 0x14, size 0x1
};
struct pair {
    // total size: 0x8
    struct _Rb_tree_iterator first; // offset 0x0, size 0x4
    unsigned char second; // offset 0x4, size 0x1
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std65_Rb_tree_node<Q211stlpmtx_std33pair<C6Symbol,PFv_PQ23Hmx6Object>>; // size: 0x8, address: 0x80929F90
// Range: 0x805F3BA8 -> 0x805F3C6C
static void __sinit_\Object_cpp() {
    // References
    // -> class list sRevs;
    // -> class map sFactories;
}

struct pair {
    // total size: 0x8
    class Symbol first; // offset 0x0, size 0x4
    class Object * (* second)(); // offset 0x4, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};

