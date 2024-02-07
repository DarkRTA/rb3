/*
    Compile unit: C:\rockband2\band2\src\meta\TutorialPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x801EBA5C -> 0x801EDC54
*/
class DataArray * types; // size: 0x4, address: 0x80A4E240
class DataArray * types; // size: 0x4, address: 0x80A4E248
class Symbol name; // size: 0x4, address: 0x80A4E250
class DataArray * types; // size: 0x4, address: 0x80A4E254
class DataArray * types; // size: 0x4, address: 0x80A4E25C
class DataArray * types; // size: 0x4, address: 0x80A4E264
static float kDbQuiet; // size: 0x4, address: 0x80A56670
class TutorialBackgroundPanel * TheTutorialBackgroundPanel; // size: 0x4, address: 0x80A4E26C
class TutorialTVScreenPanel * TheTutorialTVScreenPanel; // size: 0x4, address: 0x80A4E270
class TutorialTVOverlayPanel * TheTutorialTVOverlayPanel; // size: 0x4, address: 0x80A4E274
// Range: 0x801EBA5C -> 0x801EBBE0
void * TutorialPanel::TutorialPanel(class TutorialPanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__5Fader;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__13TutorialPanel;
    // -> struct [anonymous] __vt__23BeatMatchControllerSink;
}

class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct Flasher _M_data; // offset 0x8, size 0x8
};
// Range: 0x801EBBE0 -> 0x801EBCE4
void * TutorialPanel::~TutorialPanel(class TutorialPanel * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__13TutorialPanel;
}

// Range: 0x801EBCE4 -> 0x801EBD74
void TutorialPanel::Load(class TutorialPanel * const this /* r29 */) {}

// Range: 0x801EBD74 -> 0x801EBDBC
void TutorialPanel::Unload(class TutorialPanel * const this /* r31 */) {}

// Range: 0x801EBDBC -> 0x801EBF28
void TutorialPanel::Enter(class TutorialPanel * const this /* r28 */) {
    // References
    // -> class TutorialTVOverlayPanel * TheTutorialTVOverlayPanel;
    // -> class TutorialTVScreenPanel * TheTutorialTVScreenPanel;
    // -> class TutorialBackgroundPanel * TheTutorialBackgroundPanel;
    // -> class TaskMgr TheTaskMgr;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__3Sfx;
}

// Range: 0x801EBF28 -> 0x801EBFCC
void TutorialPanel::Exit(class TutorialPanel * const this /* r31 */) {
    // References
    // -> class TutorialTVOverlayPanel * TheTutorialTVOverlayPanel;
    // -> class TutorialTVScreenPanel * TheTutorialTVScreenPanel;
    // -> class TutorialBackgroundPanel * TheTutorialBackgroundPanel;
}

// Range: 0x801EBFCC -> 0x801EBFDC
void TutorialPanel::MuteAllTracks() {
    // References
    // -> class Game * TheGame;
}

// Range: 0x801EBFDC -> 0x801EC158
void TutorialPanel::PollAutoplayBRE(class TutorialPanel * const this /* r29 */, int slot /* r30 */) {
    // Local variables
    int track; // r31

    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801EC158 -> 0x801EC1B8
void TutorialPanel::PollAutoplayBRE(class TutorialPanel * const this /* r31 */) {}

// Range: 0x801EC1B8 -> 0x801EC1D0
void TutorialPanel::StopAutoplayBRE() {}

// Range: 0x801EC1D0 -> 0x801EC2D8
void TutorialPanel::StartAutoplayBRE(class TutorialPanel * const this /* r29 */, float msWindow /* f31 */, unsigned char AutoplayingDrumsBRE /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__6Player;
    // -> struct [anonymous] __RTTI__9GemPlayer;
    // -> class Game * TheGame;
}

// Range: 0x801EC2D8 -> 0x801EC3B4
void TutorialPanel::GenerateAutoplayBRETimes(class TutorialPanel * const this /* r29 */, int slot /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x801EC3B4 -> 0x801EC414
void TutorialPanel::GenerateAutoplayBRETimes(class TutorialPanel * const this /* r31 */) {}

// Range: 0x801EC414 -> 0x801EC52C
void TutorialPanel::Poll(class TutorialPanel * const this /* r30 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
}

// Range: 0x801EC52C -> 0x801EC60C
void TutorialPanel::SetPaused(class TutorialPanel * const this /* r30 */, unsigned char paused /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x801EC60C -> 0x801EC6A4
void TutorialPanel::EnableController(class TutorialPanel * const this /* r31 */) {
    // References
    // -> class GameConfig * TheGameConfig;
    // -> class Game * TheGame;
}

// Range: 0x801EC6A4 -> 0x801EC73C
void TutorialPanel::DisableController(class TutorialPanel * const this /* r31 */) {
    // References
    // -> class GameConfig * TheGameConfig;
    // -> class Game * TheGame;
}

// Range: 0x801EC73C -> 0x801EC768
void TutorialPanel::StartAmbientLoop() {}

// Range: 0x801EC768 -> 0x801EC788
void TutorialPanel::StopAmbientLoop() {}

// Range: 0x801EC788 -> 0x801EC7A0
void TutorialPanel::PauseAmbientLoop() {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x801EC7A0 -> 0x801EC920
class DataNode TutorialPanel::OnMakeFlash(class TutorialPanel * const this /* r29 */, class DataArray * msg /* r30 */) {
    // Local variables
    struct Flasher flasher; // r1+0x18
    unsigned char found; // r5
    struct _List_iterator i; // r1+0x14

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std37_List_node<Q213TutorialPanel7Flasher>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std37_List_node<Q213TutorialPanel7Flasher>; // size: 0x8, address: 0x808A6D10
// Range: 0x801EC920 -> 0x801EC9C8
void TutorialPanel::UpdateFlashers(class TutorialPanel * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
}

// Range: 0x801EC9C8 -> 0x801EC9DC
void TutorialPanel::ResetController() {}

// Range: 0x801EC9DC -> 0x801ECA54
class DataNode TutorialPanel::OnFadeSongOut(class TutorialPanel * const this /* r30 */, class DataArray * msg /* r31 */) {
    // References
    // -> static float kDbQuiet;
}

// Range: 0x801ECA54 -> 0x801ECACC
class DataNode TutorialPanel::OnFadeSongIn(class TutorialPanel * const this /* r30 */, class DataArray * msg /* r31 */) {}

// Range: 0x801ECACC -> 0x801ECAD8
void TutorialPanel::SetSFXVolume() {
    // References
    // -> class Synth * TheSynth;
}

// Range: 0x801ECAD8 -> 0x801ECAE0
void TutorialPanel::SetTutorialPlayer() {}

// Range: 0x801ECAE0 -> 0x801ECC94
void TutorialPanel::RenderGroup(const char * groupName /* r28 */) {
    // Local variables
    class ObjectDir * dir; // r29

    // References
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIPanel;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x801ECC94 -> 0x801ECC9C
class BeatMatchController * TutorialPanel::GetController() {}

// Range: 0x801ECC9C -> 0x801ECD24
void * TutorialDrawPanel::TutorialDrawPanel(class TutorialDrawPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__17TutorialDrawPanel;
}

// Range: 0x801ECD24 -> 0x801ECDAC
void * TutorialDrawPanel::~TutorialDrawPanel(class TutorialDrawPanel * const this /* r29 */) {}

// Range: 0x801ECDAC -> 0x801ECDEC
void TutorialDrawPanel::Draw(class TutorialDrawPanel * const this /* r31 */) {}

// Range: 0x801ECDEC -> 0x801ECDF0
void TutorialDrawPanel::SpecialDraw() {}

// Range: 0x801ECDF0 -> 0x801ECDF8
void TutorialDrawPanel::SetActivePanel() {}

// Range: 0x801ECDF8 -> 0x801ECE78
void * TutorialBackgroundPanel::TutorialBackgroundPanel(class TutorialBackgroundPanel * const this /* r31 */) {
    // References
    // -> class TutorialBackgroundPanel * TheTutorialBackgroundPanel;
    // -> struct [anonymous] __vt__23TutorialBackgroundPanel;
}

// Range: 0x801ECE78 -> 0x801ECF04
void * TutorialBackgroundPanel::~TutorialBackgroundPanel(class TutorialBackgroundPanel * const this /* r29 */) {
    // References
    // -> class TutorialBackgroundPanel * TheTutorialBackgroundPanel;
}

// Range: 0x801ECF04 -> 0x801ECF0C
void TutorialBackgroundPanel::SpecialDraw() {}

// Range: 0x801ECF0C -> 0x801ECF8C
void * TutorialTVScreenPanel::TutorialTVScreenPanel(class TutorialTVScreenPanel * const this /* r31 */) {
    // References
    // -> class TutorialTVScreenPanel * TheTutorialTVScreenPanel;
    // -> struct [anonymous] __vt__21TutorialTVScreenPanel;
}

// Range: 0x801ECF8C -> 0x801ED018
void * TutorialTVScreenPanel::~TutorialTVScreenPanel(class TutorialTVScreenPanel * const this /* r29 */) {
    // References
    // -> class TutorialTVScreenPanel * TheTutorialTVScreenPanel;
}

// Range: 0x801ED018 -> 0x801ED020
void TutorialTVScreenPanel::SpecialDraw() {}

// Range: 0x801ED020 -> 0x801ED0A0
void * TutorialTVOverlayPanel::TutorialTVOverlayPanel(class TutorialTVOverlayPanel * const this /* r31 */) {
    // References
    // -> class TutorialTVOverlayPanel * TheTutorialTVOverlayPanel;
    // -> struct [anonymous] __vt__22TutorialTVOverlayPanel;
}

// Range: 0x801ED0A0 -> 0x801ED12C
void * TutorialTVOverlayPanel::~TutorialTVOverlayPanel(class TutorialTVOverlayPanel * const this /* r29 */) {
    // References
    // -> class TutorialTVOverlayPanel * TheTutorialTVOverlayPanel;
}

// Range: 0x801ED12C -> 0x801ED134
void TutorialTVOverlayPanel::SpecialDraw() {}

static class Symbol _s; // size: 0x4, address: 0x80A4E27C
static class Symbol _s; // size: 0x4, address: 0x80A4E284
static class Symbol _s; // size: 0x4, address: 0x80A4E28C
static class Symbol _s; // size: 0x4, address: 0x80A4E294
static class Symbol _s; // size: 0x4, address: 0x80A4E29C
static class Symbol _s; // size: 0x4, address: 0x80A4E2A4
static class Symbol _s; // size: 0x4, address: 0x80A4E2AC
static class Symbol _s; // size: 0x4, address: 0x80A4E2B4
static class Symbol _s; // size: 0x4, address: 0x80A4E2BC
static class Symbol _s; // size: 0x4, address: 0x80A4E2C4
static class Symbol _s; // size: 0x4, address: 0x80A4E2CC
static class Symbol _s; // size: 0x4, address: 0x80A4E2D4
static class Symbol _s; // size: 0x4, address: 0x80A4E2DC
static class Symbol _s; // size: 0x4, address: 0x80A4E2E4
static class Symbol _s; // size: 0x4, address: 0x80A4E2EC
static class Symbol _s; // size: 0x4, address: 0x80A4E2F4
static class Symbol _s; // size: 0x4, address: 0x80A4E2FC
static class Symbol _s; // size: 0x4, address: 0x80A4E304
static class Symbol _s; // size: 0x4, address: 0x80A4E30C
static class Symbol _s; // size: 0x4, address: 0x80A4E314
static class Symbol _s; // size: 0x4, address: 0x80A4E31C
static class Symbol _s; // size: 0x4, address: 0x80A4E324
// Range: 0x801ED134 -> 0x801EDC54
class DataNode TutorialPanel::Handle(class TutorialPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x18
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode _n; // r1+0x28
    class DataNode _n; // r1+0x20

    // References
    // -> class DebugNotifier TheDebugNotifier;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Game * TheGame;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xB0
} __vt__22TutorialTVOverlayPanel; // size: 0xB0, address: 0x808A7180
struct {
    // total size: 0x8
} __RTTI__22TutorialTVOverlayPanel; // size: 0x8, address: 0x808A7270
struct {
    // total size: 0xB0
} __vt__21TutorialTVScreenPanel; // size: 0xB0, address: 0x808A7278
struct {
    // total size: 0x8
} __RTTI__21TutorialTVScreenPanel; // size: 0x8, address: 0x808A7368
struct {
    // total size: 0xB0
} __vt__23TutorialBackgroundPanel; // size: 0xB0, address: 0x808A7370
struct {
    // total size: 0x8
} __RTTI__23TutorialBackgroundPanel; // size: 0x8, address: 0x808A7460
struct {
    // total size: 0xB0
} __vt__17TutorialDrawPanel; // size: 0xB0, address: 0x808A7468
struct {
    // total size: 0x8
} __RTTI__17TutorialDrawPanel; // size: 0x8, address: 0x808A7548
struct {
    // total size: 0xE4
} __vt__13TutorialPanel; // size: 0xE4, address: 0x808A7550
struct {
    // total size: 0x38
} __vt__23BeatMatchControllerSink; // size: 0x38, address: 0x808A7710

