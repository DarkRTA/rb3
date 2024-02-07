/*
    Compile unit: C:\rockband2\system\src\net\NetworkEmulator.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80533670 -> 0x805340A0
*/
// Range: 0x80533670 -> 0x8053371C
void NetworkEmulator::Enable(class NetworkEmulator * const this /* r31 */) {}

// Range: 0x8053371C -> 0x80533794
void NetworkEmulator::Disable(class NetworkEmulator * const this /* r31 */) {}

// Range: 0x80533794 -> 0x805337E4
void NetworkEmulator::SetBandwidth(class NetworkEmulator * const this /* r31 */) {}

// Range: 0x805337E4 -> 0x80533834
void NetworkEmulator::SetJitter(class NetworkEmulator * const this /* r31 */) {}

// Range: 0x80533834 -> 0x80533884
void NetworkEmulator::SetLatency(class NetworkEmulator * const this /* r31 */) {}

// Range: 0x80533884 -> 0x80533924
void NetworkEmulator::SetPacketDropProbability(class NetworkEmulator * const this /* r31 */) {
    // Local variables
    float inDropProbFloat; // f1
    float outDropProbFloat; // f31
}

static class Symbol _s; // size: 0x4, address: 0x80A53D8C
static class Symbol _s; // size: 0x4, address: 0x80A53D94
static class Symbol _s; // size: 0x4, address: 0x80A53D9C
static class Symbol _s; // size: 0x4, address: 0x80A53DA4
static class Symbol _s; // size: 0x4, address: 0x80A53DAC
static class Symbol _s; // size: 0x4, address: 0x80A53DB4
// Range: 0x80533924 -> 0x805340A0
class DataNode NetworkEmulator::Handle(class NetworkEmulator * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x38

    // References
    // -> class Debug TheDebug;
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

struct {
    // total size: 0x54
} __vt__15NetworkEmulator; // size: 0x54, address: 0x80906C78
struct {
    // total size: 0x8
} __RTTI__15NetworkEmulator; // size: 0x8, address: 0x80906CF8

