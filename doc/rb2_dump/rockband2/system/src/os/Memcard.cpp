/*
    Compile unit: C:\rockband2\system\src\os\Memcard.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805BED24 -> 0x805BEEF8
*/
// Range: 0x805BED24 -> 0x805BED28
void Memcard::Terminate() {}

// Range: 0x805BED28 -> 0x805BED2C
void Memcard::Poll() {}

// Range: 0x805BED2C -> 0x805BEEF0
void Memcard::ShowDeviceSelector(class Object * pCallbackObj /* r31 */) {
    // Local variables
    class DeviceChosenMsg msg; // r1+0x28

    // References
    // -> struct [anonymous] __vt__15DeviceChosenMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
}

// Range: 0x805BEEF0 -> 0x805BEEF8
unsigned char Memcard::IsDeviceValid() {}

struct {
    // total size: 0x40
} __vt__11MCContainer; // size: 0x40, address: 0x80924620
struct {
    // total size: 0x84
} __vt__7Memcard; // size: 0x84, address: 0x80924678
struct {
    // total size: 0x8
} __RTTI__7Memcard; // size: 0x8, address: 0x80924720

