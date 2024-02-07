/*
    Compile unit: C:\rockband2\system\src\ui\Trigger.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803ED2C4 -> 0x803EE160
*/
class DataArray * types; // size: 0x4, address: 0x80A51E58
class Symbol name; // size: 0x4, address: 0x80A51E60
// Range: 0x803ED2C4 -> 0x803ED310
void * UITrigger::UITrigger(class UITrigger * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__9UITrigger;
}

// Range: 0x803ED6D0 -> 0x803ED738
void UITrigger::Copy(class UITrigger * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class UITrigger * t; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9UITrigger;
}

static int REV; // size: 0x4, address: 0x80A46FC0
// Range: 0x803ED738 -> 0x803ED77C
void UITrigger::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803ED77C -> 0x803EDAD8
void UITrigger::Load(class UITrigger * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x34
    class Symbol evt; // r1+0x30
    class ObjPtr anim; // r1+0x38

    // References
    // -> struct [anonymous] __vt__34ObjPtr<13RndAnimatable,9ObjectDir>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x803EDAD8 -> 0x803EDB18
void UITrigger::Enter(class UITrigger * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803EDB18 -> 0x803EDBA8
unsigned char UITrigger::IsBlocking(const class UITrigger * const this /* r30 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
static class DataArray * events; // size: 0x4, address: 0x80A51E64
// Range: 0x803EDBA8 -> 0x803EDC4C
class DataArray * UITrigger::SupportedEvents() {
    // References
    // -> static class DataArray * events;
}

static class Symbol _s; // size: 0x4, address: 0x80A51E6C
// Range: 0x803EDC4C -> 0x803EDFD4
class DataNode UITrigger::Handle(class UITrigger * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A51E74
// Range: 0x803EDFD4 -> 0x803EE160
unsigned char UITrigger::SyncProperty(class UITrigger * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x60
} __vt__9UITrigger; // size: 0x60, address: 0x808E7348
struct {
    // total size: 0x18
} __vt__32ObjPtrList<8Sequence,9ObjectDir>; // size: 0x18, address: 0x808E74F8
struct {
    // total size: 0x8
} __RTTI__32ObjPtrList<8Sequence,9ObjectDir>; // size: 0x8, address: 0x808E7540
class _List_node : public _List_node_base {
    // total size: 0x18
public:
    struct HideDelay _M_data; // offset 0x8, size 0x10
};
class _List_node : public _List_node_base {
    // total size: 0x24
public:
    struct ProxyCall _M_data; // offset 0x8, size 0x1C
};
class _List_node : public _List_node_base {
    // total size: 0x3C
public:
    struct Anim _M_data; // offset 0x8, size 0x34
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std33_List_node<Q212EventTrigger4Anim>; // size: 0x8, address: 0x808E7650
struct {
    // total size: 0x18
} __vt__29ObjPtr<9ObjectDir,9ObjectDir>; // size: 0x18, address: 0x808E76A8
struct {
    // total size: 0x8
} __RTTI__29ObjPtr<9ObjectDir,9ObjectDir>; // size: 0x8, address: 0x808E76F0

