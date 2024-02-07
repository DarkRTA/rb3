/*
    Compile unit: C:\rockband2\band2\src\meta\PassiveMessagesPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8013A2BC -> 0x8013B480
*/
class DataArray * types; // size: 0x4, address: 0x80A4BEC0
// Range: 0x8013A2BC -> 0x8013A380
void * PassiveMessagesPanel::PassiveMessagesPanel(class PassiveMessagesPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__20PassiveMessagesPanel;
}

class _List_node : public _List_node_base {
    // total size: 0x14
public:
    class String _M_data; // offset 0x8, size 0xC
};
// Range: 0x8013A380 -> 0x8013A458
void * PassiveMessagesPanel::~PassiveMessagesPanel(class PassiveMessagesPanel * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__20PassiveMessagesPanel;
}

static class Symbol msg_duration; // size: 0x4, address: 0x80A4BEC8
// Range: 0x8013A458 -> 0x8013A4D0
void PassiveMessagesPanel::SetTypeDef(class PassiveMessagesPanel * const this /* r30 */, class DataArray * data /* r31 */) {
    // References
    // -> static class Symbol msg_duration;
}

// Range: 0x8013A4D0 -> 0x8013A5C8
void PassiveMessagesPanel::Enter(class PassiveMessagesPanel * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
}

// Range: 0x8013A5C8 -> 0x8013A5D4
void PassiveMessagesPanel::Exit() {}

static class Message setMsgText; // size: 0x8, address: 0x80979260
// Range: 0x8013A5D4 -> 0x8013AB90
void PassiveMessagesPanel::Poll(class PassiveMessagesPanel * const this /* r30 */) {
    // References
    // -> static class Message setMsgText;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x8013AB90 -> 0x8013AC78
void PassiveMessagesPanel::QueueMessage(class PassiveMessagesPanel * const this /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6String>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std19_List_node<6String>; // size: 0x8, address: 0x80891E80
static class RndAnimatable * anim; // size: 0x4, address: 0x80A4BED0
static class UILabel * label; // size: 0x4, address: 0x80A4BED8
static class Symbol game; // size: 0x4, address: 0x80A4BEE0
// Range: 0x8013AC78 -> 0x8013AE94
void PassiveMessagesPanel::SetupMessage(class PassiveMessagesPanel * const this /* r30 */, const char * msg /* r28 */) {
    // Local variables
    unsigned char inGame; // r29
    const class list & panels; // r0
    struct _List_iterator itr; // r1+0x18

    // References
    // -> const char * gNullStr;
    // -> static class Symbol game;
    // -> class UIManager TheUI;
    // -> static class UILabel * label;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> static class RndAnimatable * anim;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BEE8
static class Symbol _s; // size: 0x4, address: 0x80A4BEF0
// Range: 0x8013AE94 -> 0x8013B480
class DataNode PassiveMessagesPanel::Handle(class PassiveMessagesPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__20PassiveMessagesPanel; // size: 0xAC, address: 0x80892058
struct {
    // total size: 0x8
} __RTTI__20PassiveMessagesPanel; // size: 0x8, address: 0x80892138

