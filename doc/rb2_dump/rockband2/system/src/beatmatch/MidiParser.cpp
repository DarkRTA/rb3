/*
    Compile unit: C:\rockband2\system\src\beatmatch\MidiParser.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x802EC7FC -> 0x802F1234
*/
class DataArray * types; // size: 0x4, address: 0x80A50630
class Symbol name; // size: 0x4, address: 0x80A50638
class list sParsers; // size: 0x8, address: 0x8097DD08
class DataNode * mpStart; // size: 0x4, address: 0x80A5063C
class DataNode * mpEnd; // size: 0x4, address: 0x80A50640
class DataNode * mpLength; // size: 0x4, address: 0x80A50644
class DataNode * mpPrevStartDelta; // size: 0x4, address: 0x80A50648
class DataNode * mpPrevEndDelta; // size: 0x4, address: 0x80A5064C
class DataNode * mpVal; // size: 0x4, address: 0x80A50650
class DataNode * mpSingleBit; // size: 0x4, address: 0x80A50654
class DataNode * mpLowestBit; // size: 0x4, address: 0x80A50658
class DataNode * mpData; // size: 0x4, address: 0x80A5065C
class DataNode * mpOutOfBounds; // size: 0x4, address: 0x80A50660
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x802EC7FC -> 0x802EC980
void MidiParser::ClearManagedParsers() {
    // Local variables
    class list delParsers; // r1+0x38
    struct _List_iterator it; // r1+0x24
    class MidiParser * parser; // r31

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std25_List_node<P10MidiParser>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9MsgSource;
    // -> class ObjectDir * sMainDir;
    // -> class list sParsers;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class MidiParser * _M_data; // offset 0x8, size 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std25_List_node<P10MidiParser>; // size: 0x8, address: 0x808CC6F0
// Range: 0x802EC980 -> 0x802EC9B0
void * PostProcess::PostProcess() {}

// Range: 0x802EC9B0 -> 0x802ECB60
void * MidiParser::MidiParser(class MidiParser * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std25_List_node<P10MidiParser>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sParsers;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__10MidiParser;
    // -> struct [anonymous] __vt__9MsgSource;
}

// Range: 0x802ECB60 -> 0x802ECD0C
void * MidiParser::~MidiParser(class MidiParser * const this /* r30 */) {
    // References
    // -> class list sParsers;
    // -> struct [anonymous] __vt__10MidiParser;
}

// Range: 0x802ECD0C -> 0x802ECD14
void MidiParser::Reset() {}

static class DataNode & parser; // size: 0x4, address: 0x80A50668
static class Symbol world_drum_triggers; // size: 0x4, address: 0x80A50670
static class Symbol play_tambourine; // size: 0x4, address: 0x80A50678
static class Symbol events_parser; // size: 0x4, address: 0x80A50680
static class Symbol world_camera_parser; // size: 0x4, address: 0x80A50688
// Range: 0x802ECD14 -> 0x802ED0F8
void MidiParser::Poll(class MidiParser * const this /* r30 */) {
    // Local variables
    float beat; // f31
    class DataNode ret; // r1+0x40

    // References
    // -> class DataNode * mpData;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class DataNode * mpLength;
    // -> class DataNode * mpEnd;
    // -> class DataNode * mpStart;
    // -> static class Symbol world_camera_parser;
    // -> static class Symbol events_parser;
    // -> static class Symbol play_tambourine;
    // -> static class Symbol world_drum_triggers;
    // -> static class DataNode & parser;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x802ED0F8 -> 0x802ED1CC
unsigned char MidiParser::InsertIdle() {
    // Local variables
    class DataNode node; // r1+0x8
}

// Range: 0x802ED1CC -> 0x802ED268
unsigned char MidiParser::AllowedNote(class MidiParser * const this /* r28 */, int note /* r29 */) {
    // Local variables
    int i; // r30
}

// Range: 0x802ED268 -> 0x802ED390
void MidiParser::ParseNote(class MidiParser * const this /* r28 */, int startTick /* r29 */, int endTick /* r30 */, unsigned char data1 /* r31 */) {
    // Local variables
    class MemDoTempAllocations dummy_temp_mem_allocation; // r1+0x8
    int i; // r5
    struct Note * it; // r0
}

// Range: 0x802ED390 -> 0x802ED680
void MidiParser::PushIdle(class MidiParser * const this /* r28 */, float start /* f30 */, float end /* f31 */, int at /* r29 */, class Symbol & idleMessage /* r30 */) {
    // Local variables
    class DataNode ev; // r1+0x40
    int which; // r27
    class MemDoTempAllocations dummy_temp_mem_allocation; // r1+0x14

    // References
    // -> const char * gNullStr;
}

// Range: 0x802ED680 -> 0x802ED748
int MidiParser::GetIndex(class MidiParser * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802ED748 -> 0x802EDA1C
void MidiParser::SetIndex(class MidiParser * const this /* r30 */, int i /* r31 */) {
    // References
    // -> class DataNode * mpOutOfBounds;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802EDA1C -> 0x802EE0C4
int MidiParser::ParseAll(class MidiParser * const this /* r29 */, const class GameGemList * gems /* r31 */, class vector & text /* r30 */) {
    // Local variables
    class DataArray * init; // r4
    int which; // r31
    int startTick; // r30
    class DataArray * term; // r4
    int noteSize; // r30

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class DataNode * mpEnd;
    // -> class DataNode * mpStart;
}

// Range: 0x802EE0C4 -> 0x802EE4CC
void MidiParser::SetGlobalVars(class MidiParser * const this /* r29 */, int endTick /* r28 */, const class DataNode & data /* r30 */) {
    // Local variables
    float start; // f0
    float end; // f0
    int gems; // r28
    int lowest; // r30

    // References
    // -> class DataNode * mpLowestBit;
    // -> class DataNode * mpSingleBit;
    // -> class DataNode * mpVal;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class DataNode * mpData;
    // -> class DataNode * mpPrevEndDelta;
    // -> class DataNode * mpPrevStartDelta;
    // -> class DataNode * mpLength;
    // -> class DataNode * mpEnd;
    // -> class DataNode * mpStart;
    // -> class DataNode * mpOutOfBounds;
}

// Range: 0x802EE4CC -> 0x802EE604
void MidiParser::HandleEvent(class MidiParser * const this /* r28 */, int startTick /* r29 */, int endTick /* r30 */, const class DataNode & data /* r31 */) {
    // References
    // -> class DataNode * mpData;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802EE604 -> 0x802EE710
void MidiParser::InsertDataEvent(class MidiParser * const this /* r29 */, float start /* f30 */, float end /* f31 */, const class DataNode & ev /* r30 */) {
    // Local variables
    int i; // r31
    float length; // f0
    class MemDoTempAllocations dummy_temp_mem_allocation; // r1+0x8
}

// Range: 0x802EE710 -> 0x802EEB14
unsigned char MidiParser::AddMessage(class MidiParser * const this /* r26 */, float start /* f30 */, float end /* f31 */, class DataArray * msg /* r27 */, int firstArg /* r28 */) {
    // Local variables
    class DataNode type; // r1+0x30
    class DataArray * arr; // [invalid]
    int firstSrc; // [invalid]
    int size; // r30
    int firstDst; // r29
    int i; // r24

    // References
    // -> const char * gNullStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A50690
static class Symbol _s; // size: 0x4, address: 0x80A50698
static class Symbol _s; // size: 0x4, address: 0x80A506A0
static class Symbol _s; // size: 0x4, address: 0x80A506A8
static class Symbol _s; // size: 0x4, address: 0x80A506B0
static class Symbol _s; // size: 0x4, address: 0x80A506B8
static class Symbol _s; // size: 0x4, address: 0x80A506C0
static class Symbol _s; // size: 0x4, address: 0x80A506C8
static class Symbol _s; // size: 0x4, address: 0x80A506D0
static class Symbol _s; // size: 0x4, address: 0x80A506D8
static class Symbol _s; // size: 0x4, address: 0x80A506E0
static class Symbol _s; // size: 0x4, address: 0x80A506E8
static class Symbol _s; // size: 0x4, address: 0x80A506F0
// Range: 0x802EEB14 -> 0x802EFF50
class DataNode MidiParser::Handle(class MidiParser * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x58
    class MessageTimer _mt; // r1+0xC0
    class DataNode r; // r1+0xB8
    class DataNode r; // r1+0xB0
    class DataNode r; // r1+0xA8
    class DataNode r; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode _n; // r1+0x68
    class DataNode _n; // r1+0x60

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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class DataNode * mpStart;
    // -> class DataNode * mpEnd;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x802EFF50 -> 0x802F0150
class DataNode MidiParser::OnInsertIdle(class MidiParser * const this /* r30 */, class DataArray * msg /* r31 */) {
    // Local variables
    class Symbol idleMessage; // r1+0x14
    float idleLength; // f0
    float idleStartGap; // f0
    float idleEndGap; // f0
    float * lastEnd; // r0
    float idleStart; // f1
    float idleEnd; // f2
    float gap; // f0
    float gap; // f0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802F0150 -> 0x802F01C0
class DataNode MidiParser::OnNextStartDelta(class MidiParser * const this /* r31 */) {}

// Range: 0x802F01C0 -> 0x802F03A4
class DataNode MidiParser::OnGetStart(class MidiParser * const this /* r28 */, class DataArray * msg /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802F03A4 -> 0x802F0588
class DataNode MidiParser::OnGetEnd(class MidiParser * const this /* r28 */, class DataArray * msg /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x802F0588 -> 0x802F0694
class DataNode MidiParser::OnDebugDraw(class MidiParser * const this /* r30 */, class DataArray * msg /* r31 */) {
    // Local variables
    float top; // f0
    float beat; // f30

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x802F0694 -> 0x802F0734
class DataNode MidiParser::OnBeatToSecLength(class DataArray * msg /* r31 */) {
    // Local variables
    float beats; // f0

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x802F0734 -> 0x802F079C
class DataNode MidiParser::OnSecOffsetAll(class MidiParser * const this /* r30 */, class DataArray * msg /* r31 */) {
    // Local variables
    float sec; // f0
}

// Range: 0x802F079C -> 0x802F0840
class DataNode MidiParser::OnSecOffset(class DataArray * msg /* r31 */) {
    // Local variables
    float beat; // f31
    float ms; // f30
}

// Range: 0x802F0840 -> 0x802F08AC
class DataNode MidiParser::OnNextVal(class DataNode * val /* r29 */, class MidiParser * const this /* r30 */) {
    // Local variables
    int index; // r31

    // References
    // -> class DataNode * mpVal;
}

// Range: 0x802F08AC -> 0x802F096C
class DataNode MidiParser::OnPrevVal(class MidiParser * const this /* r30 */) {
    // Local variables
    int index; // r31
    class DataNode val; // r1+0x8

    // References
    // -> class DataNode * mpVal;
}

static class Symbol _s; // size: 0x4, address: 0x80A506F8
static class Symbol _s; // size: 0x4, address: 0x80A50700
static class Symbol _s; // size: 0x4, address: 0x80A50708
static class Symbol _s; // size: 0x4, address: 0x80A50710
static class Symbol _s; // size: 0x4, address: 0x80A50718
static class Symbol _s; // size: 0x4, address: 0x80A50720
static class Symbol _s; // size: 0x4, address: 0x80A50728
static class Symbol _s; // size: 0x4, address: 0x80A50730
// Range: 0x802F096C -> 0x802F1134
unsigned char MidiParser::SyncProperty(class MidiParser * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
}

struct {
    // total size: 0x7C
} __vt__10MidiParser; // size: 0x7C, address: 0x808CCAF0
// Range: 0x802F1134 -> 0x802F1160
void _Vector_base::_M_throw_length_error() {}

struct {
    // total size: 0x8
} __RTTI__PQ210MidiParser4Note; // size: 0x8, address: 0x808CCC18
// Range: 0x802F1160 -> 0x802F11BC
static void __sinit_\MidiParser_cpp() {
    // References
    // -> class list sParsers;
}


