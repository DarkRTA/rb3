/*
    Compile unit: C:\rockband2\system\src\bandobj\EventCompleteDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8027CA10 -> 0x80280534
*/
class DataArray * types; // size: 0x4, address: 0x80A4F6E8
// Range: 0x8027CA10 -> 0x8027CBA8
void * EventCompleteDir::EventCompleteDir(class EventCompleteDir * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8BandList,9ObjectDir>;
    // -> struct [anonymous] __vt__16EventCompleteDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

class _List_node : public _List_node_base {
    // total size: 0xC8
public:
    struct Item _M_data; // offset 0x8, size 0xC0
};
// Range: 0x8027CBA8 -> 0x8027CCEC
class BinStream & __ls(class BinStream & s /* r30 */, const struct Item & i /* r31 */) {}

// Range: 0x8027CCEC -> 0x8027CDD4
void EventCompleteDir::Save(class EventCompleteDir * const this /* r30 */, class BinStream & d /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
static int gRev; // size: 0x4, address: 0x80A4F6F0
// Range: 0x8027CDD4 -> 0x8027CEEC
void EventCompleteDir::PreLoad(class EventCompleteDir * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x8027CEEC -> 0x8027D054
class BinStream & __rs(class BinStream & s /* r30 */, struct Item & i /* r31 */) {
    // Local variables
    int moment_state; // r1+0xC

    // References
    // -> static int gRev;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8027D054 -> 0x8027D1B8
void EventCompleteDir::PostLoad(class EventCompleteDir * const this /* r31 */, class BinStream & d /* r29 */) {
    // Local variables
    struct _List_iterator i; // r1+0x20

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class list sRevs;
}

// Range: 0x8027D1B8 -> 0x8027D5FC
void EventCompleteDir::Copy(class EventCompleteDir * const this /* r26 */, const class Object * o /* r27 */) {
    // Local variables
    const class EventCompleteDir * p; // r0

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8Sequence,9ObjectDir>;
    // -> struct [anonymous] __vt__29ObjPtr<9BandLabel,9ObjectDir>;
    // -> struct [anonymous] __vt__34ObjPtr<13RndAnimatable,9ObjectDir>;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16EventCompleteDir;
}

// Range: 0x8027D5FC -> 0x8027D99C
void EventCompleteDir::Poll(class EventCompleteDir * const this /* r30 */) {
    // Local variables
    float seconds; // f0
    unsigned char all_done; // r31
    struct _List_iterator i; // r1+0x10
    unsigned char started; // r6
    int moment_start; // r26
    unsigned char show_moment; // r6

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8027D99C -> 0x8027DCF4
void EventCompleteDir::Play(class EventCompleteDir * const this /* r31 */) {
    // Local variables
    float start; // f0
    float delay; // f29
    struct _List_iterator i; // r1+0x1C

    // References
    // -> const char * gNullStr;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8027DCF4 -> 0x8027DE1C
void EventCompleteDir::AddItem(const char * text /* r28 */, class Sequence * sfx /* r29 */, int text_start /* r30 */, int text_end /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18

    // References
    // -> class Debug TheDebug;
}

struct iterator {
    // total size: 0x1
};
class reverse_iterator : public iterator {
    // total size: 0x4
protected:
    struct _List_iterator current; // offset 0x0, size 0x4
};
// Range: 0x8027DE1C -> 0x8027DFB0
void EventCompleteDir::SetMoment(int text_end /* r29 */, class Sequence * sfx /* r30 */, unsigned char success /* r31 */) {
    // Local variables
    class reverse_iterator i; // r1+0x4C

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8027DFB0 -> 0x8027E270
unsigned char EventCompleteDir::Skip(class EventCompleteDir * const this /* r30 */) {
    // Local variables
    unsigned char skipped; // r31
    struct _List_iterator i; // r1+0x10

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x8027E270 -> 0x8027E3A4
class DataNode EventCompleteDir::OnAddItem(class EventCompleteDir * const this /* r28 */, class DataArray * a /* r29 */) {
    // Local variables
    class String icon; // r1+0x14
    class String text; // r1+0x8
    int text_start; // r30
    int text_end; // r8

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F6F8
static class Symbol _s; // size: 0x4, address: 0x80A4F700
static class Symbol _s; // size: 0x4, address: 0x80A4F708
static class Symbol _s; // size: 0x4, address: 0x80A4F710
// Range: 0x8027E3A4 -> 0x8027EB08
class DataNode EventCompleteDir::Handle(class EventCompleteDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x38
    class MessageTimer _mt; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8Sequence;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F718
static class Symbol _s; // size: 0x4, address: 0x80A4F720
static class Symbol _s; // size: 0x4, address: 0x80A4F728
static class Symbol _s; // size: 0x4, address: 0x80A4F730
static class Symbol _s; // size: 0x4, address: 0x80A4F738
static class Symbol _s; // size: 0x4, address: 0x80A4F740
static class Symbol _s; // size: 0x4, address: 0x80A4F748
static class Symbol _s; // size: 0x4, address: 0x80A4F750
static class Symbol _s; // size: 0x4, address: 0x80A4F758
static class Symbol _s; // size: 0x4, address: 0x80A4F760
static class Symbol _s; // size: 0x4, address: 0x80A4F768
static class Symbol _s; // size: 0x4, address: 0x80A4F770
static class Symbol _s; // size: 0x4, address: 0x80A4F778
static class Symbol _s; // size: 0x4, address: 0x80A4F780
static class Symbol _s; // size: 0x4, address: 0x80A4F788
static class Symbol _s; // size: 0x4, address: 0x80A4F790
static class Symbol _s; // size: 0x4, address: 0x80A4F798
static class Symbol _s; // size: 0x4, address: 0x80A4F7A0
// Range: 0x8027EB08 -> 0x8027F498
unsigned char PropSync(struct Item & _me /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

static class Symbol _s; // size: 0x4, address: 0x80A4F7A8
static class Symbol _s; // size: 0x4, address: 0x80A4F7B0
static class Symbol _s; // size: 0x4, address: 0x80A4F7B8
static class Symbol _s; // size: 0x4, address: 0x80A4F7C0
static class Symbol _s; // size: 0x4, address: 0x80A4F7C8
static class Symbol _s; // size: 0x4, address: 0x80A4F7D0
static class Symbol _s; // size: 0x4, address: 0x80A4F7D8
// Range: 0x8027F498 -> 0x8027FA80
unsigned char EventCompleteDir::SyncProperty(class EventCompleteDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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

// Range: 0x8027FA80 -> 0x80280534
unsigned char PropSync(class ObjList & v /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    struct _List_iterator it; // r1+0x2C
    struct Item tmp; // r1+0x38

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std37_List_node<Q216EventCompleteDir4Item>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__34ObjPtr<13RndAnimatable,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8RndGroup,9ObjectDir>;
    // -> struct [anonymous] __vt__29ObjPtr<9BandLabel,9ObjectDir>;
    // -> struct [anonymous] __vt__28ObjPtr<8Sequence,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std37_List_node<Q216EventCompleteDir4Item>; // size: 0x8, address: 0x808BB498
struct {
    // total size: 0x234
} __vt__16EventCompleteDir; // size: 0x234, address: 0x808BB4A0
struct {
    // total size: 0x8
} __RTTI__16EventCompleteDir; // size: 0x8, address: 0x808BB748
struct {
    // total size: 0x18
} __vt__28ObjPtr<8BandList,9ObjectDir>; // size: 0x18, address: 0x808BB750
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8BandList,9ObjectDir>; // size: 0x8, address: 0x808BB790
struct {
    // total size: 0x18
} __vt__28ObjPtr<8Sequence,9ObjectDir>; // size: 0x18, address: 0x808BB7E0
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8Sequence,9ObjectDir>; // size: 0x8, address: 0x808BB820
struct {
    // total size: 0x18
} __vt__29ObjPtr<9BandLabel,9ObjectDir>; // size: 0x18, address: 0x808BB828
struct {
    // total size: 0x8
} __RTTI__29ObjPtr<9BandLabel,9ObjectDir>; // size: 0x8, address: 0x808BB870

