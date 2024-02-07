/*
    Compile unit: C:\rockband2\system\src\obj\Msg.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805EF9AC -> 0x805F09FC
*/
// Range: 0x805EF9AC -> 0x805EFAC0
void Sink::Export(struct Sink * const this /* r6 */) {}

// Range: 0x805EFAC0 -> 0x805EFC54
void * MsgSource::~MsgSource(class MsgSource * const this /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x28
    struct _List_iterator i; // r1+0x24
    struct _List_iterator j; // r1+0x20

    // References
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x805EFC54 -> 0x805EFD5C
void EventSink::Add() {
    // Local variables
    struct EventSinkElem s; // r1+0x10

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std39_List_node<Q29MsgSource13EventSinkElem>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
}

// Range: 0x805EFD5C -> 0x805EFE20
void EventSink::Remove(unsigned char exporting /* r30 */) {
    // Local variables
    struct _List_iterator s; // r1+0x18
}

// Range: 0x805EFE20 -> 0x805EFE50
void MsgSource::Replace() {
    // References
    // -> const char * gNullStr;
}

// Range: 0x805EFE50 -> 0x805EFF7C
void MsgSource::MergeSinks(class MsgSource * const this /* r31 */, class MsgSource * from /* r29 */) {
    // Local variables
    class list & sinks; // r30
    struct _List_iterator it; // r1+0x40
    class list & events; // r29
    struct _List_iterator e; // r1+0x3C
    struct _List_iterator p; // r1+0x38

    // References
    // -> const char * gNullStr;
}

// Range: 0x805EFF7C -> 0x805F02BC
void MsgSource::Export(class MsgSource * const this /* r29 */, class DataArray * a /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x54
    struct _List_iterator i; // r1+0x50
    class DataNode t; // r1+0x68
    struct _List_iterator j; // r1+0x4C
}

static class Symbol _s; // size: 0x4, address: 0x80A55084
static class Symbol _s; // size: 0x4, address: 0x80A5508C
// Range: 0x805F02BC -> 0x805F06E4
class DataNode MsgSource::Handle(class MsgSource * const this /* r30 */, class DataArray * _msg /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode r; // r1+0x28

    // References
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x805F06E4 -> 0x805F091C
class DataNode MsgSource::OnAddSink(class MsgSource * const this /* r30 */, class DataArray * a /* r25 */) {
    // Local variables
    enum SinkMode mode; // r27
    class DataArray * arr; // r26
    class Object * sink; // r31
    int i; // r25
    class DataNode n; // r1+0x48

    // References
    // -> const char * gNullStr;
}

// Range: 0x805F091C -> 0x805F09FC
class DataNode MsgSource::OnRemoveSink(class MsgSource * const this /* r28 */, class DataArray * a /* r29 */) {
    // Local variables
    class Object * obj; // r31
    int i; // r30

    // References
    // -> const char * gNullStr;
}

struct {
    // total size: 0x6C
} __vt__9MsgSource; // size: 0x6C, address: 0x80929AB0

