/*
    Compile unit: C:\rockband2\system\src\world\EventAnim.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804669B4 -> 0x80467B98
*/
class DataArray * types; // size: 0x4, address: 0x80A52860
// Range: 0x804669B4 -> 0x80466A6C
void * EventAnim::EventAnim(class EventAnim * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__9EventAnim;
}

class _List_node : public _List_node_base {
    // total size: 0x18
public:
    struct KeyFrame _M_data; // offset 0x8, size 0x10
};
// Range: 0x80466A6C -> 0x80466AC8
void * EventCall::EventCall() {
    // References
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> struct [anonymous] __vt__29ObjPtr<9ObjectDir,9ObjectDir>;
}

// Range: 0x80466AC8 -> 0x80466B00
void * KeyFrame::KeyFrame() {}

class _List_node : public _List_node_base {
    // total size: 0x20
public:
    struct EventCall _M_data; // offset 0x8, size 0x18
};
// Range: 0x80466B00 -> 0x80466B20
float EventAnim::EndFrame() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80466B20 -> 0x80466C18
void EventAnim::SetFrame(class EventAnim * const this /* r30 */, float frame /* f31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x1C
    float c; // f1
    struct _List_iterator call; // r1+0x18
}

// Range: 0x80466C18 -> 0x80466D20
void EventAnim::Copy(class EventAnim * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class EventAnim * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9EventAnim;
}

static int REV; // size: 0x4, address: 0x80A52868
// Range: 0x80466D20 -> 0x80466D64
void EventAnim::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A5286C
// Range: 0x80466D64 -> 0x80466E08
void EventAnim::Load(class EventAnim * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int REV;
    // -> static int gRev;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80466E08 -> 0x80466E54
class BinStream & __rs(class BinStream & d /* r30 */, struct KeyFrame & c /* r31 */) {}

// Range: 0x80466E54 -> 0x80467000
class BinStream & __rs(class BinStream & d /* r28 */, struct EventCall & c /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12EventTrigger;
}

// Range: 0x80467000 -> 0x80467018
unsigned char KeyFrame::__lt() {}

// Range: 0x80467018 -> 0x80467048
void EventAnim::RefreshKeys() {}

struct binary_function {
    // total size: 0x1
};
struct __stlport_class {
    // total size: 0x1
};
struct less : public binary_function, public __stlport_class {
    // total size: 0x1
};
static class EventAnim * gOwner; // size: 0x4, address: 0x80A52870
// Range: 0x80467070 -> 0x8046745C
class DataNode EventAnim::Handle(class EventAnim * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A52878
static class Symbol _s; // size: 0x4, address: 0x80A52880
// Range: 0x8046745C -> 0x8046756C
unsigned char PropSync(struct EventCall & _me /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A52888
static class Symbol _s; // size: 0x4, address: 0x80A52890
// Range: 0x8046756C -> 0x80467734
unsigned char PropSync(struct KeyFrame & _me /* r28 */, class DataNode & _val /* r29 */, class DataArray * _prop /* r30 */, int _i /* r27 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class EventAnim * gOwner;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

// Range: 0x80467734 -> 0x80467ABC
unsigned char PropSync(class ObjList & v /* r26 */, class DataNode & n /* r31 */, class DataArray * prop /* r27 */, int i /* r28 */, enum PropOp op /* r29 */) {
    // Local variables
    struct _List_iterator it; // r1+0x2C
    struct EventCall tmp; // r1+0x38

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std34_List_node<Q29EventAnim9EventCall>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__29ObjPtr<9ObjectDir,9ObjectDir>;
    // -> struct [anonymous] __vt__33ObjPtr<12EventTrigger,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std34_List_node<Q29EventAnim9EventCall>; // size: 0x8, address: 0x808F0E80
static class Symbol _s; // size: 0x4, address: 0x80A52898
// Range: 0x80467ABC -> 0x80467B98
unsigned char EventAnim::SyncProperty(class EventAnim * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class EventAnim * gOwner;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std33_List_node<Q29EventAnim8KeyFrame>; // size: 0x8, address: 0x808F0EC0
struct {
    // total size: 0xA0
} __vt__9EventAnim; // size: 0xA0, address: 0x808F0EC8
struct {
    // total size: 0x8
} __RTTI__9EventAnim; // size: 0x8, address: 0x808F0F90
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};

