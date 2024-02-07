/*
    Compile unit: C:\rockband2\system\src\os\VirtualKeyboard.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805CCC64 -> 0x805CD638
*/
class Symbol t; // size: 0x4, address: 0x80A54DFC
class VirtualKeyboard TheVirtualKeyboard; // size: 0x3C, address: 0x80988C2C
// Range: 0x805CCC64 -> 0x805CCCB8
void * VirtualKeyboard::VirtualKeyboard(class VirtualKeyboard * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__15VirtualKeyboard;
}

// Range: 0x805CCCB8 -> 0x805CCD28
void * VirtualKeyboard::~VirtualKeyboard(class VirtualKeyboard * const this /* r30 */) {}

// Range: 0x805CCD28 -> 0x805CCD44
void VirtualKeyboard::Init() {
    // References
    // -> class ObjectDir * sMainDir;
}

class VirtualKeyboardResultMsg : public Message {
    // total size: 0x8
};
// Range: 0x805CCD44 -> 0x805CCF94
void VirtualKeyboard::Poll(class VirtualKeyboard * const this /* r31 */) {
    // Local variables
    class VirtualKeyboardResultMsg msg; // r1+0x30

    // References
    // -> struct [anonymous] __vt__24VirtualKeyboardResultMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> const char * gNullStr;
}

// Range: 0x805CCF94 -> 0x805CCF98
void VirtualKeyboard::Terminate() {}

// Range: 0x805CCF98 -> 0x805CD108
class DataNode VirtualKeyboard::OnShowKeyboardUI(class VirtualKeyboard * const this /* r28 */, const class DataArray * da /* r29 */) {
    // Local variables
    class String strWindowTitle; // r1+0x44
    class String strDescription; // r1+0x38
    class String strDefaultText; // r1+0x2C
}

// Range: 0x805CD108 -> 0x805CD1F0
class DataNode VirtualKeyboard::PlaceholderKeyboardUI(class VirtualKeyboard * const this /* r30 */) {
    // Local variables
    char buffer[256]; // r1+0x8
    int i; // r31
    int val; // r0
}

static class Symbol _s; // size: 0x4, address: 0x80A54E04
// Range: 0x805CD1F0 -> 0x805CD5F0
class DataNode VirtualKeyboard::Handle(class VirtualKeyboard * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xC
} __vt__24VirtualKeyboardResultMsg; // size: 0xC, address: 0x80926B1C
struct {
    // total size: 0x8
} __RTTI__24VirtualKeyboardResultMsg; // size: 0x8, address: 0x80926B50
struct {
    // total size: 0x54
} __vt__15VirtualKeyboard; // size: 0x54, address: 0x80926B58
struct {
    // total size: 0x8
} __RTTI__15VirtualKeyboard; // size: 0x8, address: 0x80926BD8
// Range: 0x805CD5F0 -> 0x805CD638
static void __sinit_\VirtualKeyboard_cpp() {
    // References
    // -> class VirtualKeyboard TheVirtualKeyboard;
}


