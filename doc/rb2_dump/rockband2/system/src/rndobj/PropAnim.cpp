/*
    Compile unit: C:\rockband2\system\src\rndobj\PropAnim.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804F323C -> 0x804F3F84
*/
class DataArray * types; // size: 0x4, address: 0x80A53708
class Symbol name; // size: 0x4, address: 0x80A53710
// Range: 0x804F323C -> 0x804F32E4
void * RndPropAnim::RndPropAnim(class RndPropAnim * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__11RndPropAnim;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class PropKeys * _M_data; // offset 0x8, size 0x4
};
// Range: 0x804F32E4 -> 0x804F33A0
void * RndPropAnim::~RndPropAnim(class RndPropAnim * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__11RndPropAnim;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x804F33A0 -> 0x804F3494
void RndPropAnim::Replace(class RndPropAnim * const this /* r27 */, class Object * from /* r28 */, class Object * to /* r29 */) {
    // Local variables
    struct _List_iterator i; // r1+0x1C
    class PropKeys * keys; // r30
}

static int PROPANIM_REV; // size: 0x4, address: 0x80A47388
static int gRev; // size: 0x4, address: 0x80A53714
// Range: 0x804F3494 -> 0x804F34D8
void RndPropAnim::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x804F34D8 -> 0x804F36B0
void RndPropAnim::Load(class RndPropAnim * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    class ObjOwnerPtr target; // r1+0x14
    int size; // r1+0x10
    int i; // r31
    int keysType; // r1+0xC
    class PropKeys * keys; // r0

    // References
    // -> struct [anonymous] __vt__37ObjOwnerPtr<Q23Hmx6Object,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> static int PROPANIM_REV;
    // -> static int gRev;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x804F36B0 -> 0x804F37AC
void RndPropAnim::Copy(class RndPropAnim * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndPropAnim * m; // r0
    struct _List_iterator i; // r1+0x18
    class PropKeys * newKeys; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndPropAnim;
}

// Range: 0x804F37AC -> 0x804F3850
float RndPropAnim::EndFrame(class RndPropAnim * const this /* r31 */) {
    // Local variables
    float frame; // r1+0x18
    struct _List_iterator i; // r1+0x14
}

// Range: 0x804F3850 -> 0x804F39C0
void RndPropAnim::SetFrame(class RndPropAnim * const this /* r28 */, float frame /* f30 */, float blend /* f31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
    class ObjKeys & eventKeys; // r0
    int i; // r29
    float t; // f1
    class EventTrigger * trigger; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x804F39C0 -> 0x804F3A40
void RndPropAnim::SetKey(class RndPropAnim * const this /* r31 */, float frame /* f31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x804F3A40 -> 0x804F3B04
class PropKeys * RndPropAnim::GetKeys(class RndPropAnim * const this /* r28 */, class Object * obj /* r29 */, class DataArray * prop /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x10
}

// Range: 0x804F3B04 -> 0x804F3E70
class PropKeys * RndPropAnim::AddKeys(class RndPropAnim * const this /* r29 */, class Object * obj /* r27 */, class DataArray * prop /* r30 */, enum AnimKeysType keysType /* r28 */) {
    // Local variables
    class PropKeys * keys; // r31
    class DataNode n; // r1+0x10

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8PropKeys>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__11Vector3Keys;
    // -> struct [anonymous] __vt__8QuatKeys;
    // -> struct [anonymous] __vt__8BoolKeys;
    // -> struct [anonymous] __vt__10ObjectKeys;
    // -> struct [anonymous] __vt__9ColorKeys;
    // -> struct [anonymous] __vt__9FloatKeys;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<P8PropKeys>; // size: 0x8, address: 0x808FF5B0
// Range: 0x804F3E70 -> 0x804F3F04
void RndPropAnim::RemoveKeys(class RndPropAnim * const this /* r31 */) {}

// Range: 0x804F3F04 -> 0x804F3F84
unsigned char RndPropAnim::SyncProperty(class RndPropAnim * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xA8
} __vt__11RndPropAnim; // size: 0xA8, address: 0x808FF5E0

