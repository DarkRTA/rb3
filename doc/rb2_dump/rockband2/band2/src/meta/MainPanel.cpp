/*
    Compile unit: C:\rockband2\band2\src\meta\MainPanel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x800FED54 -> 0x80101E34
*/
class DataArray * types; // size: 0x4, address: 0x80A4B2C8
class Symbol name; // size: 0x4, address: 0x80A4B2D0
class MainPanel * TheMainPanel; // size: 0x4, address: 0x80A4B2D4
class MainPanelWidget {
    // total size: 0x20
protected:
    class RndAnimatable * mShot; // offset 0x0, size 0x4
    class UILabel * mLabel; // offset 0x4, size 0x4
    const char * mCascade; // offset 0x8, size 0x4
    unsigned char mCascadeDown; // offset 0xC, size 0x1
    float mCurFrame; // offset 0x10, size 0x4
    float mDesFrame; // offset 0x14, size 0x4
    float mCurAlpha; // offset 0x18, size 0x4
    float mDesAlpha; // offset 0x1C, size 0x4
};
// Range: 0x800FED54 -> 0x800FEDE0
void * MainPanelWidget::MainPanelWidget(class MainPanelWidget * const this /* r31 */) {}

// Range: 0x800FEDE0 -> 0x800FEE28
void MainPanelWidget::PlayForward(class MainPanelWidget * const this /* r31 */) {}

// Range: 0x800FEE28 -> 0x800FEE70
void MainPanelWidget::PlayBackward(class MainPanelWidget * const this /* r31 */) {}

// Range: 0x800FEE70 -> 0x800FF07C
void MainPanelWidget::CascadeDown(class UIPanel * panel /* r31 */) {
    // Local variables
    class Message msg; // r1+0x30

    // References
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x800FF07C -> 0x800FF40C
void MainPanelWidget::CascadeUp(class MainPanelWidget * const this /* r30 */, class UIPanel * panel /* r31 */) {
    // Local variables
    class Message msg; // r1+0x50
    class Message msg; // r1+0x48

    // References
    // -> struct [anonymous] __vt__7Message;
    // -> class MainPanel * TheMainPanel;
}

// Range: 0x800FF40C -> 0x800FF4F8
unsigned char MainPanelWidget::UpdateAnim(class MainPanelWidget * const this /* r31 */) {}

// Range: 0x800FF4F8 -> 0x800FF504
void MainPanelWidget::Show() {}

// Range: 0x800FF504 -> 0x800FF510
void MainPanelWidget::Hide() {}

// Range: 0x800FF510 -> 0x800FF590
void MainPanelWidget::UpdateAlpha() {}

class MainPanel : public UIPanel {
    // total size: 0x1FC
protected:
    class MainPanelWidget mWidget[12]; // offset 0x30, size 0x180
    class MainPanelWidget * mCurAnim; // offset 0x1B0, size 0x4
    class MainPanelWidget * mNextAnim; // offset 0x1B4, size 0x4
    class MainPanelWidget * mCascadedWidget; // offset 0x1B8, size 0x4
    class vector mFocusStack; // offset 0x1BC, size 0xC
    unsigned char mEntered; // offset 0x1C8, size 0x1
    const char * mDelayedScreen; // offset 0x1CC, size 0x4
};
// Range: 0x800FF590 -> 0x800FF690
void * MainPanel::MainPanel(class MainPanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class MainPanel * TheMainPanel;
    // -> struct [anonymous] __vt__9MainPanel;
}

class StlNodeAlloc {
    // total size: 0x1
};
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x4
public:
    struct FocusEntry * _M_data; // offset 0x0, size 0x4
};
class _Vector_base {
    // total size: 0xC
protected:
    struct FocusEntry * _M_start; // offset 0x0, size 0x4
    struct FocusEntry * _M_finish; // offset 0x4, size 0x4
    class _STLP_alloc_proxy _M_end_of_storage; // offset 0x8, size 0x4
};
class vector : protected _Vector_base {
    // total size: 0xC
};
// Range: 0x800FF690 -> 0x800FF6BC
unsigned char MainPanel::IsMainScreen() {}

// Range: 0x800FF6BC -> 0x800FF720
void MainPanel::Exit(class MainPanel * const this /* r31 */) {
    // Local variables
    class UIComponent * f; // r0
}

// Range: 0x800FF720 -> 0x801000B0
void MainPanel::Enter(class MainPanel * const this /* r26 */) {
    // Local variables
    class ObjectDir * dir; // r27
    int i; // r27
    class ObjectDir * dir; // r0
    int widIdx; // r30
    class MainPanelWidget & wid; // r31

    // References
    // -> class Rnd & TheRnd;
    // -> const char * kNotObjectMsg;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__13BandHighlight;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> struct [anonymous] __RTTI__7UILabel;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> class UIManager TheUI;
}

// Range: 0x801000B0 -> 0x801001C8
void MainPanel::ResetStoredFocus(class MainPanel * const this /* r31 */) {}

struct FocusEntry {
    // total size: 0x8
    class Symbol mFocus; // offset 0x0, size 0x4
    int mWidget; // offset 0x4, size 0x4
};
// Range: 0x801001C8 -> 0x80100274
void MainPanel::PollAnim(class MainPanel * const this /* r29 */, unsigned char force /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x80100274 -> 0x801002AC
void MainPanel::Poll(class MainPanel * const this /* r31 */) {}

// Range: 0x801002AC -> 0x8010035C
void MainPanel::SetNextAnim(class MainPanel * const this /* r31 */) {}

// Range: 0x8010035C -> 0x8010050C
int MainPanel::FindWidget() {}

// Range: 0x8010050C -> 0x80100728
void MainPanel::OnPushFocus(class MainPanel * const this /* r31 */) {
    // Local variables
    class UIComponent * f; // r28
    int widIdx; // r28
    class MainPanelWidget & wid; // r29

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

// Range: 0x80100728 -> 0x801008D4
class DataNode MainPanel::OnPopFocus(class MainPanel * const this /* r31 */) {
    // Local variables
    int i; // r29
    int widIdx; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

// Range: 0x801008D4 -> 0x80100950
void MainPanel::ShowOnly(class MainPanel * const this /* r29 */, int widget /* r30 */) {
    // Local variables
    int i; // r31
}

// Range: 0x80100950 -> 0x801011F0
void MainPanel::SetFocusForScreen(class MainPanel * const this /* r29 */, const char * screen /* r30 */) {}

// Range: 0x801011F0 -> 0x80101244
class DataNode MainPanel::OnIsPlayingAnim() {}

// Range: 0x80101244 -> 0x801012A8
class DataNode MainPanel::OnAnimFramesLeft() {}

static char buffer[64]; // size: 0x40, address: 0x80978C40
// Range: 0x801012A8 -> 0x8010152C
class DataNode MainPanel::IsFocusedComponent(class MainPanel * const this /* r27 */, class RndDrawable * component /* r31 */) {
    // Local variables
    class vector draws; // r1+0x20
    class RndDrawable * const * d; // r3

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PP11RndDrawable;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8RndGroup;
    // -> static char buffer[64];
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class UIManager TheUI;
}

struct _OKToMemCpy {
    // total size: 0x1
};
struct {
    // total size: 0x8
} __RTTI__PP11RndDrawable; // size: 0x8, address: 0x80889EA0
static class Symbol _s; // size: 0x4, address: 0x80A4B2DC
static class Symbol _s; // size: 0x4, address: 0x80A4B2E4
static class Symbol _s; // size: 0x4, address: 0x80A4B2EC
static class Symbol _s; // size: 0x4, address: 0x80A4B2F4
static class Symbol _s; // size: 0x4, address: 0x80A4B2FC
static class Symbol _s; // size: 0x4, address: 0x80A4B304
static class Symbol _s; // size: 0x4, address: 0x80A4B30C
// Range: 0x8010152C -> 0x80101E34
class DataNode MainPanel::Handle(class MainPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
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

struct {
    // total size: 0x8
} __RTTI__13BandHighlight; // size: 0x8, address: 0x80889FD0
struct {
    // total size: 0xAC
} __vt__9MainPanel; // size: 0xAC, address: 0x8088A008
struct {
    // total size: 0x8
} __RTTI__9MainPanel; // size: 0x8, address: 0x8088A0E0
struct {
    // total size: 0x8
} __RTTI__P10FocusEntry; // size: 0x8, address: 0x8088A2C8

