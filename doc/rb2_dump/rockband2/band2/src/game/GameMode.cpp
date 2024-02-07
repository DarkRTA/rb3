/*
    Compile unit: C:\rockband2\band2\src\game\GameMode.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8005E4F8 -> 0x8005F66C
*/
class Symbol t; // size: 0x4, address: 0x80A4982C
class GameMode * TheGameMode; // size: 0x4, address: 0x80A49830
// Range: 0x8005E4F8 -> 0x8005E56C
void GameModeInit() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class GameMode * TheGameMode;
}

// Range: 0x8005E56C -> 0x8005E690
void * GameMode::GameMode(class GameMode * const this /* r31 */) {
    // References
    // -> class ObjectDir * sMainDir;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__8GameMode;
    // -> struct [anonymous] __vt__9MsgSource;
}

class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct Sink _M_data; // offset 0x8, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0x14
public:
    struct EventSink _M_data; // offset 0x8, size 0xC
};
// Range: 0x8005E690 -> 0x8005E718
void * GameMode::~GameMode(class GameMode * const this /* r29 */) {}

// Range: 0x8005E718 -> 0x8005E7EC
class DataNode GameMode::OnSetMode(class GameMode * const this /* r29 */, const class DataArray * a /* r30 */) {}

static class ModeChangedMsg msg; // size: 0x8, address: 0x80977288
// Range: 0x8005E7EC -> 0x8005EE9C
void GameMode::SetMode(class GameMode * const this /* r30 */, class Symbol & symModeNew /* r26 */, int iPlayer /* r27 */) {
    // Local variables
    class DataArray * daModes; // r28
    class DataArray * daMode; // r29
    class DataArray * daExit; // r4
    class DataArray * typeDef; // r29
    class DataArray * daEnter; // r4

    // References
    // -> class PlatformMgr ThePlatformMgr;
    // -> struct [anonymous] __vt__14ModeChangedMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class ModeChangedMsg msg;
}

static class Symbol _s; // size: 0x4, address: 0x80A49838
// Range: 0x8005EE9C -> 0x8005F3E0
class DataNode GameMode::Handle(class GameMode * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A49840
static class Symbol _s; // size: 0x4, address: 0x80A49848
// Range: 0x8005F3E0 -> 0x8005F66C
unsigned char GameMode::SyncProperty(class GameMode * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x70
} __vt__8GameMode; // size: 0x70, address: 0x808753F0
struct {
    // total size: 0x8
} __RTTI__8GameMode; // size: 0x8, address: 0x80875488
struct {
    // total size: 0xC
} __vt__14ModeChangedMsg; // size: 0xC, address: 0x80875490
struct {
    // total size: 0x8
} __RTTI__14ModeChangedMsg; // size: 0x8, address: 0x808754B8
class _List_node : public _List_node_base {
    // total size: 0x14
public:
    struct EventSinkElem _M_data; // offset 0x8, size 0xC
};

