/*
    Compile unit: C:\rockband2\system\src\rndobj\EventTrigger.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804915D8 -> 0x80496554
*/
class DataArray * types; // size: 0x4, address: 0x80A52D30
class Symbol name; // size: 0x4, address: 0x80A52D38
static int gRev; // size: 0x4, address: 0x80A52D3C
static class DataArray * events; // size: 0x4, address: 0x80A52D40
// Range: 0x804915D8 -> 0x80491754
class DataArray * EventTrigger::SupportedEvents() {
    // References
    // -> static class DataArray * events;
    // -> const char * gNullStr;
}

static class Symbol range; // size: 0x4, address: 0x80A52D48
static class Symbol loop; // size: 0x4, address: 0x80A52D50
class list : public _List_base {
    // total size: 0x8
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80491754 -> 0x80491E48
class DataNode EventTrigger::Cleanup() {
    // Local variables
    class ObjectDir * dir; // r28
    class list triggers; // r1+0x60
    class ObjDirItr i; // r1+0x68
    struct _List_iterator e; // r1+0x5C
    char event[128]; // r1+0x80
    struct _List_iterator a; // r1+0x58
    class RndAnimFilter * filter; // r27
    struct _List_iterator r; // r1+0x54
    struct _List_iterator a; // r1+0x50
    class EventTrigger * i; // r27
    struct _List_iterator b; // r1+0x4C
    class EventTrigger * j; // r28

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol loop;
    // -> static class Symbol range;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> struct [anonymous] __RTTI__13RndAnimFilter;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class EventTrigger * _M_data; // offset 0x8, size 0x4
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
} __RTTI__PQ211stlpmtx_std27_List_node<P12EventTrigger>; // size: 0x8, address: 0x808F61F8
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
static class Symbol range; // size: 0x4, address: 0x80A52D58
static class Symbol loop; // size: 0x4, address: 0x80A52D60
// Range: 0x80491E48 -> 0x80491F38
static void ResetAnim(struct Anim & me /* r31 */) {
    // References
    // -> static class Symbol loop;
    // -> static class Symbol range;
}

static class Symbol range; // size: 0x4, address: 0x80A52D68
// Range: 0x80491F38 -> 0x80491FE8
void * Anim::Anim(struct Anim * const this /* r31 */) {
    // References
    // -> static class Symbol range;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__34ObjPtr<13RndAnimatable,9ObjectDir>;
}

// Range: 0x80491FE8 -> 0x80492108
class BinStream & __rs(class BinStream & d /* r29 */, struct Anim & c /* r30 */) {
    // References
    // -> static int gRev;
}

// Range: 0x80492108 -> 0x804922CC
class BinStream & __rs(class BinStream & d /* r28 */, struct ProxyCall & c /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
    // -> static int gRev;
}

// Range: 0x804922CC -> 0x80492330
void * ProxyCall::ProxyCall() {
    // References
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__29ObjPtr<9ObjectDir,9ObjectDir>;
}

// Range: 0x80492330 -> 0x804924C8
void * EventTrigger::EventTrigger(class EventTrigger * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjPtrList<8Sequence,9ObjectDir>;
    // -> struct [anonymous] __vt__12EventTrigger;
}

// Range: 0x804924C8 -> 0x8049250C
void * HideDelay::HideDelay() {
    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
}

static class Symbol trigger; // size: 0x4, address: 0x80A52D70
static class Symbol enable; // size: 0x4, address: 0x80A52D78
static class Symbol disable; // size: 0x4, address: 0x80A52D80
static class Symbol wait_for; // size: 0x4, address: 0x80A52D88
// Range: 0x8049250C -> 0x80492784
void EventTrigger::RegisterEvents(class EventTrigger * const this /* r29 */) {
    // Local variables
    class MsgSource * source; // r30
    struct _List_iterator i; // r1+0x58

    // References
    // -> static class Symbol wait_for;
    // -> static class Symbol disable;
    // -> static class Symbol enable;
    // -> static class Symbol trigger;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__9MsgSource;
}

// Range: 0x80492784 -> 0x80492924
void EventTrigger::UnregisterEvents(class EventTrigger * const this /* r30 */) {
    // Local variables
    class MsgSource * source; // r31
    struct _List_iterator i; // r1+0x48

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__9MsgSource;
}

// Range: 0x80492924 -> 0x80493204
void EventTrigger::Copy(class EventTrigger * const this /* r29 */, const class Object * o /* r27 */) {
    // Local variables
    const class EventTrigger * e; // r0

    // References
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__29ObjPtr<9ObjectDir,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__34ObjPtr<13RndAnimatable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x80493204 -> 0x80493248
void EventTrigger::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80493248 -> 0x804932E8
static void RemoveNullEvents(class list & events /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x1C

    // References
    // -> const char * gNullStr;
}

// Range: 0x804932E8 -> 0x804938C4
void EventTrigger::Load(class EventTrigger * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    class list created; // r1+0x68
    class Symbol event; // r1+0x50
    class ObjPtrList hides; // r1+0x80
    class iterator h; // r1+0x4C
    struct _List_iterator i; // r1+0x48
    int i; // r1+0x44

    // References
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

static class Message msg; // size: 0x8, address: 0x8097F250
static class Message msg; // size: 0x8, address: 0x8097F268
static class Message trigger; // size: 0x8, address: 0x8097F280
// Range: 0x804938C4 -> 0x80493E8C
void EventTrigger::TriggerSelf(class EventTrigger * const this /* r29 */) {
    // Local variables
    struct _List_iterator anim; // r1+0x68
    struct _List_iterator call; // r1+0x64
    class iterator seq; // r1+0x60
    class iterator show; // r1+0x5C
    struct _List_iterator hide; // r1+0x58

    // References
    // -> static class Message trigger;
    // -> class TaskMgr TheTaskMgr;
    // -> static class Message msg;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * gNullStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A52D90
static class Symbol _s; // size: 0x4, address: 0x80A52D98
static class Symbol _s; // size: 0x4, address: 0x80A52DA0
static class Symbol _s; // size: 0x4, address: 0x80A52DA8
static class Symbol _s; // size: 0x4, address: 0x80A52DB0
static class Symbol _s; // size: 0x4, address: 0x80A52DB8
static class Symbol _s; // size: 0x4, address: 0x80A52DC0
// Range: 0x80493E8C -> 0x804948CC
class DataNode EventTrigger::Handle(class EventTrigger * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
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

// Range: 0x804948CC -> 0x8049493C
class DataNode EventTrigger::OnTrigger() {}

// Range: 0x8049493C -> 0x80494C78
class DataNode EventTrigger::OnProxyCalls(class EventTrigger * const this /* r27 */) {
    // Local variables
    class DataArray * path; // r31
    class DataNode n; // r1+0x48
    class Object * proxy; // r0
    int idx; // r31
    class DataArrayPtr da; // r1+0x40
    class DataArray * typeDef; // r28
    int i; // r27

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
}

static class Symbol range; // size: 0x4, address: 0x80A52DC8
// Range: 0x80494C78 -> 0x80494CF8
static unsigned char OneShot(struct Anim & a /* r31 */) {
    // References
    // -> static class Symbol range;
}

// Range: 0x80494CF8 -> 0x80494E54
class DataNode EventTrigger::OnValidate(class EventTrigger * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x1C
    class RndAnimatable * a; // r0
    class Object * target; // r0
    struct _List_iterator j; // r1+0x18
    class Object * btarget; // r0

    // References
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A52DD0
static class Symbol _s; // size: 0x4, address: 0x80A52DD8
static class Symbol _s; // size: 0x4, address: 0x80A52DE0
static class Symbol _s; // size: 0x4, address: 0x80A52DE8
static class Symbol _s; // size: 0x4, address: 0x80A52DF0
static class Symbol _s; // size: 0x4, address: 0x80A52DF8
static class Symbol _s; // size: 0x4, address: 0x80A52E00
static class Symbol _s; // size: 0x4, address: 0x80A52E08
static class Symbol _s; // size: 0x4, address: 0x80A52E10
static class Symbol _s; // size: 0x4, address: 0x80A52E18
static class Symbol _s; // size: 0x4, address: 0x80A52E20
// Range: 0x80494E54 -> 0x804958DC
unsigned char PropSync(struct Anim & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
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
}

static class Symbol _s; // size: 0x4, address: 0x80A52E28
static class Symbol _s; // size: 0x4, address: 0x80A52E30
static class Symbol _s; // size: 0x4, address: 0x80A52E38
// Range: 0x804958DC -> 0x80495B28
unsigned char PropSync(struct ProxyCall & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A52E40
static class Symbol _s; // size: 0x4, address: 0x80A52E48
// Range: 0x80495B28 -> 0x80495CE0
unsigned char PropSync(struct HideDelay & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A52E50
static class Symbol _s; // size: 0x4, address: 0x80A52E58
static class Symbol _s; // size: 0x4, address: 0x80A52E60
static class Symbol _s; // size: 0x4, address: 0x80A52E68
static class Symbol _s; // size: 0x4, address: 0x80A52E70
static class Symbol _s; // size: 0x4, address: 0x80A52E78
static class Symbol _s; // size: 0x4, address: 0x80A52E80
static class Symbol _s; // size: 0x4, address: 0x80A52E88
static class Symbol _s; // size: 0x4, address: 0x80A52E90
static class Symbol _s; // size: 0x4, address: 0x80A52E98
static class Symbol _s; // size: 0x4, address: 0x80A52EA0
// Range: 0x80495CE0 -> 0x80496248
unsigned char EventTrigger::SyncProperty(class EventTrigger * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
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

// Range: 0x80496248 -> 0x80496554
unsigned char PropSync(class ObjList & v /* r26 */, class DataNode & n /* r31 */, class DataArray * prop /* r27 */, int i /* r28 */, enum PropOp op /* r29 */) {
    // Local variables
    struct _List_iterator it; // r1+0x2C
    struct HideDelay tmp; // r1+0x38

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std38_List_node<Q212EventTrigger9HideDelay>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__32ObjPtr<11RndDrawable,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std38_List_node<Q212EventTrigger9HideDelay>; // size: 0x8, address: 0x808F6500
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std38_List_node<Q212EventTrigger9ProxyCall>; // size: 0x8, address: 0x808F6550
struct {
    // total size: 0x60
} __vt__12EventTrigger; // size: 0x60, address: 0x808F6610
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};

