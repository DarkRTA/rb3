/*
    Compile unit: C:\rockband2\band2\src\meta\CreditsPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800E1FAC -> 0x800E2880
*/
class DataArray * types; // size: 0x4, address: 0x80A4AE20
class Symbol name; // size: 0x4, address: 0x80A4AE28
class CreditsPanel : public ListProvider, public UIPanel {
    // total size: 0x70
    class DataLoader * mLoader; // offset 0x34, size 0x4
    class DataArray * mNames; // offset 0x38, size 0x4
    class UIList * mList; // offset 0x3C, size 0x4
    class Stream * mStream; // offset 0x40, size 0x4
};
// Range: 0x800E1FAC -> 0x800E2050
void * CreditsPanel::CreditsPanel(class CreditsPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__12CreditsPanel;
    // -> struct [anonymous] __vt__12ListProvider;
}

// Range: 0x800E2050 -> 0x800E20DC
void * CreditsPanel::~CreditsPanel(class CreditsPanel * const this /* r29 */) {}

// Range: 0x800E20DC -> 0x800E2144
unsigned char CreditsPanel::IsLoaded(class CreditsPanel * const this /* r30 */) {}

// Range: 0x800E2144 -> 0x800E21EC
unsigned char CreditsPanel::Exiting(class CreditsPanel * const this /* r28 */) {}

// Range: 0x800E21EC -> 0x800E227C
void CreditsPanel::Unload(class CreditsPanel * const this /* r31 */) {}

// Range: 0x800E227C -> 0x800E22EC
void CreditsPanel::Enter(class CreditsPanel * const this /* r31 */) {
    // References
    // -> unsigned char gCreditsPanelLoaded;
}

// Range: 0x800E22EC -> 0x800E23A0
class DataNode CreditsPanel::OnMsg(const class ButtonDownMsg & msg /* r30 */) {}

static class Symbol heading; // size: 0x4, address: 0x80A4AE30
static class Symbol slot_heading; // size: 0x4, address: 0x80A4AE38
static class Symbol slot_left; // size: 0x4, address: 0x80A4AE40
static class Symbol slot_right; // size: 0x4, address: 0x80A4AE48
static class Symbol slot_centered; // size: 0x4, address: 0x80A4AE50
static class Symbol image; // size: 0x4, address: 0x80A4AE58
static class Symbol blank; // size: 0x4, address: 0x80A4AE60
static class Symbol heading2; // size: 0x4, address: 0x80A4AE68
static class Symbol title_name; // size: 0x4, address: 0x80A4AE70
static class Symbol centered; // size: 0x4, address: 0x80A4AE78
// Range: 0x800E23A0 -> 0x800E26D8
char * CreditsPanel::Text(const class CreditsPanel * const this /* r28 */, int data /* r29 */, class Symbol & slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol centered;
    // -> static class Symbol title_name;
    // -> static class Symbol heading2;
    // -> static class Symbol blank;
    // -> static class Symbol image;
    // -> static class Symbol slot_centered;
    // -> static class Symbol slot_right;
    // -> static class Symbol slot_left;
    // -> static class Symbol slot_heading;
    // -> static class Symbol heading;
}

static class Symbol image; // size: 0x4, address: 0x80A4AE80
static class Symbol blank; // size: 0x4, address: 0x80A4AE88
// Range: 0x800E26D8 -> 0x800E2874
class RndMat * CreditsPanel::Mat(const class CreditsPanel * const this /* r28 */, int data /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> static class Symbol blank;
    // -> static class Symbol image;
}

// Range: 0x800E2874 -> 0x800E2880
int CreditsPanel::NumData() {}

struct {
    // total size: 0x11C
} __vt__12CreditsPanel; // size: 0x11C, address: 0x80884A88
struct {
    // total size: 0x8
} __RTTI__12CreditsPanel; // size: 0x8, address: 0x80884BD8

