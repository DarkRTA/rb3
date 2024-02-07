/*
    Compile unit: C:\rockband2\band2\src\meta\BandScreen.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800BC528 -> 0x800BD524
*/
class DataArray * types; // size: 0x4, address: 0x80A4A790
class Symbol name; // size: 0x4, address: 0x80A4A798
class Symbol t; // size: 0x4, address: 0x80A4A7A0
class Symbol t; // size: 0x4, address: 0x80A4A7A8
class Symbol t; // size: 0x4, address: 0x80A4A7B0
static class Message msg; // size: 0x8, address: 0x80977E18
static class Symbol in_transition; // size: 0x4, address: 0x80A4A7B8
// Range: 0x800BC528 -> 0x800BC7E0
void BandScreen::Enter(class BandScreen * const this /* r28 */, class UIScreen * from /* r29 */) {
    // Local variables
    const class DataNode * transition; // r0

    // References
    // -> static class Symbol in_transition;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUI * TheBandUI;
}

static class Message msg; // size: 0x8, address: 0x80977E30
// Range: 0x800BC7E0 -> 0x800BC994
void BandScreen::Exit(class BandScreen * const this /* r29 */, class UIScreen * to /* r30 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUI * TheBandUI;
}

// Range: 0x800BC994 -> 0x800BC9FC
unsigned char BandScreen::InComponentSelect(const class BandScreen * const this /* r31 */) {
    // Local variables
    class UIComponent * c; // r0

    // References
    // -> class BandUI * TheBandUI;
}

// Range: 0x800BC9FC -> 0x800BCA00
class DataNode BandScreen::OnMsg() {}

// Range: 0x800BCA00 -> 0x800BCA04
class DataNode BandScreen::OnMsg() {}

// Range: 0x800BCA04 -> 0x800BCA08
class DataNode BandScreen::OnMsg() {}

// Range: 0x800BCA08 -> 0x800BCA0C
class DataNode BandScreen::OnMsg() {}

// Range: 0x800BCA0C -> 0x800BCB1C
class DataNode BandScreen::OnEventMsgCommon(class BandScreen * const this /* r31 */, const class Message & msg /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUI * TheBandUI;
}

// Range: 0x800BCB1C -> 0x800BCBCC
unsigned char BandScreen::IsEventDialogOnTop(const class BandScreen * const this /* r29 */) {
    // References
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class BandUI * TheBandUI;
}

// Range: 0x800BCBCC -> 0x800BD524
class DataNode BandScreen::Handle(class BandScreen * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode _n; // r1+0x68

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__25UIComponentFocusChangeMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__24UIComponentSelectDoneMsg;
    // -> class Symbol t;
    // -> struct [anonymous] __vt__20UIComponentSelectMsg;
    // -> class Symbol t;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xC
} __vt__25UIComponentFocusChangeMsg; // size: 0xC, address: 0x8087F82C
struct {
    // total size: 0x8
} __RTTI__25UIComponentFocusChangeMsg; // size: 0x8, address: 0x8087F860
struct {
    // total size: 0xC
} __vt__24UIComponentSelectDoneMsg; // size: 0xC, address: 0x8087F868
struct {
    // total size: 0x8
} __RTTI__24UIComponentSelectDoneMsg; // size: 0x8, address: 0x8087F8A0
struct {
    // total size: 0xC
} __vt__20UIComponentSelectMsg; // size: 0xC, address: 0x8087F8A8
struct {
    // total size: 0x8
} __RTTI__20UIComponentSelectMsg; // size: 0x8, address: 0x8087F8D8
struct {
    // total size: 0x80
} __vt__10BandScreen; // size: 0x80, address: 0x8087F930

