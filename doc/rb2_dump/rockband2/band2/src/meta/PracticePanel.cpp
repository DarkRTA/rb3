/*
    Compile unit: C:\rockband2\band2\src\meta\PracticePanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8013CEBC -> 0x8013E4D4
*/
class DataArray * types; // size: 0x4, address: 0x80A4BF50
class DataArray * types; // size: 0x4, address: 0x80A4BF58
// Range: 0x8013CEBC -> 0x8013CFCC
void * PracticePanel::PracticePanel(class PracticePanel * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__13PracticePanel;
}

// Range: 0x8013CFCC -> 0x8013D094
void * PracticePanel::~PracticePanel(class PracticePanel * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__13PracticePanel;
}

// Range: 0x8013D094 -> 0x8013D1A0
void PracticePanel::Exit(class PracticePanel * const this /* r28 */) {
    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__10MidiParser;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x8013D1A0 -> 0x8013D1A4
void PracticePanel::Poll() {}

// Range: 0x8013D1A4 -> 0x8013D214
void PracticePanel::SetPitchShiftRatio(float ratio /* f31 */) {
    // Local variables
    class GemPlayer * player; // r0
    float speed; // f0

    // References
    // -> struct [anonymous] __RTTI__6Player;
    // -> struct [anonymous] __RTTI__9GemPlayer;
    // -> class Game * TheGame;
}

// Range: 0x8013D214 -> 0x8013D21C
unsigned char PracticePanel::InVocalMode() {}

// Range: 0x8013D21C -> 0x8013D234
void PracticePanel::OnFadeSongOut(float seconds /* f2 */) {}

// Range: 0x8013D234 -> 0x8013D24C
void PracticePanel::OnFadeSongIn(float seconds /* f2 */) {}

// Range: 0x8013D24C -> 0x8013D2B4
void PracticePanel::StopMics() {
    // Local variables
    unsigned int i; // r31

    // References
    // -> class Synth * TheSynth;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BF60
static class Symbol _s; // size: 0x4, address: 0x80A4BF68
static class Symbol _s; // size: 0x4, address: 0x80A4BF70
static class Symbol _s; // size: 0x4, address: 0x80A4BF78
static class Symbol _s; // size: 0x4, address: 0x80A4BF80
static class Symbol _s; // size: 0x4, address: 0x80A4BF88
static class Symbol _s; // size: 0x4, address: 0x80A4BF90
// Range: 0x8013D2B4 -> 0x8013DDB4
class DataNode PracticePanel::Handle(class PracticePanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x40
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode _n; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
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

// Range: 0x8013DDB4 -> 0x8013DE30
void * PracticeBackgroundPanel::PracticeBackgroundPanel(class PracticeBackgroundPanel * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__23PracticeBackgroundPanel;
}

// Range: 0x8013DE30 -> 0x8013DEB8
void * PracticeBackgroundPanel::~PracticeBackgroundPanel(class PracticeBackgroundPanel * const this /* r29 */) {}

// Range: 0x8013DEB8 -> 0x8013DFB4
void PracticeBackgroundPanel::SelectCam(const char * name /* r30 */) {
    // Local variables
    class WorldDir * dir; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11BandCamShot;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> struct [anonymous] __RTTI__8WorldDir;
}

static class Symbol _s; // size: 0x4, address: 0x80A4BF98
// Range: 0x8013DFB4 -> 0x8013E4D4
class DataNode PracticeBackgroundPanel::Handle(class PracticeBackgroundPanel * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

struct {
    // total size: 0xAC
} __vt__23PracticeBackgroundPanel; // size: 0xAC, address: 0x80892E80
struct {
    // total size: 0x8
} __RTTI__23PracticeBackgroundPanel; // size: 0x8, address: 0x80892F68
struct {
    // total size: 0xAC
} __vt__13PracticePanel; // size: 0xAC, address: 0x80892F70
struct {
    // total size: 0x8
} __RTTI__13PracticePanel; // size: 0x8, address: 0x80893048

