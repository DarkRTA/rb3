/*
    Compile unit: C:\rockband2\band2\src\meta\SessionPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80166D40 -> 0x8016766C
*/
class DataArray * types; // size: 0x4, address: 0x80A4C590
// Range: 0x80166D40 -> 0x80166DC8
void * SessionPanel::SessionPanel(class SessionPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__12SessionPanel;
}

// Range: 0x80166DC8 -> 0x80166DFC
void SessionPanel::Enter(class SessionPanel * const this /* r31 */) {}

static class Symbol session_ready_complete_msg; // size: 0x4, address: 0x80A4C598
// Range: 0x80166DFC -> 0x80166E70
void SessionPanel::Exit(class SessionPanel * const this /* r31 */) {
    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> static class Symbol session_ready_complete_msg;
}

static class Symbol session_ready_complete_msg; // size: 0x4, address: 0x80A4C5A0
// Range: 0x80166E70 -> 0x80166F04
class DataNode SessionPanel::OnSessionReadyComplete(class SessionPanel * const this /* r31 */) {
    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> static class Symbol session_ready_complete_msg;
}

// Range: 0x80166F04 -> 0x80166F38
class DataNode SessionPanel::OnMsg() {}

static class Symbol session_ready_complete_msg; // size: 0x4, address: 0x80A4C5A8
// Range: 0x80166F38 -> 0x80166FC8
void SessionPanel::WaitForSessionReady(class SessionPanel * const this /* r30 */) {
    // References
    // -> class SessionMgr * TheSessionMgr;
    // -> const char * gNullStr;
    // -> static class Symbol session_ready_complete_msg;
}

static class Symbol _s; // size: 0x4, address: 0x80A4C5B0
static class Symbol _s; // size: 0x4, address: 0x80A4C5B8
// Range: 0x80166FC8 -> 0x8016766C
class DataNode SessionPanel::Handle(class SessionPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__12SessionPanel; // size: 0xAC, address: 0x80897F68
struct {
    // total size: 0x8
} __RTTI__12SessionPanel; // size: 0x8, address: 0x80898040

