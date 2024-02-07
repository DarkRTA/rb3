/*
    Compile unit: C:\rockband2\system\src\rndobj\Set.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804FC17C -> 0x804FD3B0
*/
class DataArray * types; // size: 0x4, address: 0x80A53908
// Range: 0x804FC17C -> 0x804FC1E4
void * RndSet::RndSet(class RndSet * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__36ObjPtrList<Q23Hmx6Object,9ObjectDir>;
    // -> struct [anonymous] __vt__6RndSet;
}

// Range: 0x804FC1E4 -> 0x804FC290
unsigned char RndSet::AllowedObject(class RndSet * const this /* r29 */, class Object * o /* r30 */) {
    // Local variables
    int i; // r31
}

static int REV; // size: 0x4, address: 0x80A53910
// Range: 0x804FC290 -> 0x804FC2D4
void RndSet::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804FC2D4 -> 0x804FC38C
void RndSet::Load(class RndSet * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x804FC38C -> 0x804FC6E4
void RndSet::Copy(class RndSet * const this /* r29 */, const class Object * o /* r27 */) {
    // Local variables
    const class RndSet * v; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndSet;
}

static class Symbol _s; // size: 0x4, address: 0x80A53918
// Range: 0x804FC6E4 -> 0x804FCB70
class DataNode RndSet::Handle(class RndSet * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode _n; // r1+0x48
    class iterator i; // r1+0x34

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x804FCB70 -> 0x804FD01C
class DataNode RndSet::OnAllowedObjects(class RndSet * const this /* r31 */) {
    // Local variables
    class list objects; // r1+0x60
    class ObjDirItr i; // r1+0x68
    class DataArrayPtr array; // r1+0x58
    int a; // r29
    struct _List_iterator i; // r1+0x38

    // References
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<PQ23Hmx6Object>;
    // -> unsigned char gStlAllocNameLookup;
}

static class Symbol _s; // size: 0x4, address: 0x80A53920
static class Object * milo; // size: 0x4, address: 0x80A53924
static class Message msg; // size: 0x8, address: 0x809806B8
// Range: 0x804FD01C -> 0x804FD3B0
unsigned char RndSet::SyncProperty(class RndSet * const this /* r26 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r28 */) {
    // Local variables
    class iterator i; // r1+0x30

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> static class Object * milo;
    // -> class ObjectDir * sMainDir;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x54
} __vt__6RndSet; // size: 0x54, address: 0x80900980
struct {
    // total size: 0x8
} __RTTI__6RndSet; // size: 0x8, address: 0x809009F0

