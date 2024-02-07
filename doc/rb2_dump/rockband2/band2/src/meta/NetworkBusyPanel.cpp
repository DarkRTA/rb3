/*
    Compile unit: C:\rockband2\band2\src\meta\NetworkBusyPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801F6DE8 -> 0x801F7650
*/
class DataArray * types; // size: 0x4, address: 0x80A4E440
// Range: 0x801F6DE8 -> 0x801F6E7C
void * NetworkBusyPanel::NetworkBusyPanel(class NetworkBusyPanel * const this /* r30 */) {
    // References
    // -> class NetworkBusyPanel * sInstance;
    // -> struct [anonymous] __vt__16NetworkBusyPanel;
}

// Range: 0x801F6E7C -> 0x801F6F08
void * NetworkBusyPanel::~NetworkBusyPanel(class NetworkBusyPanel * const this /* r29 */) {
    // References
    // -> class NetworkBusyPanel * sInstance;
}

static class Symbol min_duration; // size: 0x4, address: 0x80A4E448
// Range: 0x801F6F08 -> 0x801F6F80
void NetworkBusyPanel::SetTypeDef(class NetworkBusyPanel * const this /* r30 */, class DataArray * data /* r31 */) {
    // References
    // -> static class Symbol min_duration;
}

// Range: 0x801F6F80 -> 0x801F7078
void NetworkBusyPanel::Enter(class NetworkBusyPanel * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
}

// Range: 0x801F7078 -> 0x801F71CC
void NetworkBusyPanel::Poll(class NetworkBusyPanel * const this /* r31 */) {
    // References
    // -> class InputMgr * TheInputMgr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

class NetworkBusyPanel * sInstance; // size: 0x4, address: 0x80A4E44C
// Range: 0x801F71CC -> 0x801F7234
void NetworkBusyPanel::SetBusy(class NetworkBusyPanel * const this /* r31 */) {
    // References
    // -> class InputMgr * TheInputMgr;
}

// Range: 0x801F7234 -> 0x801F7288
void NetworkBusyPanel::SetHeightFrame() {}

static class Symbol _s; // size: 0x4, address: 0x80A4E454
// Range: 0x801F7288 -> 0x801F7650
class DataNode NetworkBusyPanel::Handle(class NetworkBusyPanel * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
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

struct {
    // total size: 0xAC
} __vt__16NetworkBusyPanel; // size: 0xAC, address: 0x808A8920
struct {
    // total size: 0x8
} __RTTI__16NetworkBusyPanel; // size: 0x8, address: 0x808A8A00

