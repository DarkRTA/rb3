/*
    Compile unit: C:\rockband2\system\src\ui\Panel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803DB610 -> 0x803DDE3C
*/
// Range: 0x803DB610 -> 0x803DB6B8
void * UIPanel::UIPanel(class UIPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__7UIPanel;
}

// Range: 0x803DB6B8 -> 0x803DB6E0
class ObjectDir * UIPanel::DataDir() {}

static class Symbol focus; // size: 0x4, address: 0x80A51BF4
static class Symbol force_exit; // size: 0x4, address: 0x80A51BFC
// Range: 0x803DB6E0 -> 0x803DB7B8
void UIPanel::SetTypeDef(class UIPanel * const this /* r30 */, class DataArray * data /* r31 */) {
    // References
    // -> static class Symbol force_exit;
    // -> static class Symbol focus;
}

// Range: 0x803DB7B8 -> 0x803DB7E0
void UIPanel::CheckLoad() {}

static class Message msg; // size: 0x8, address: 0x8097E2A8
// Range: 0x803DB7E0 -> 0x803DB960
void UIPanel::CheckUnload(class UIPanel * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x803DB960 -> 0x803DB9E0
void UIPanel::SetLoadedDir(class UIPanel * const this /* r29 */, class PanelDir * dir /* r30 */, unsigned char shared /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803DB9E0 -> 0x803DBA4C
void UIPanel::UnsetLoadedDir(class UIPanel * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message msg; // size: 0x8, address: 0x8097E2C0
static class Symbol proj_file; // size: 0x4, address: 0x80A51C04
static class Symbol fileSym; // size: 0x4, address: 0x80A51C0C
static class Symbol allow_home_menu; // size: 0x4, address: 0x80A51C14
// Range: 0x803DBA4C -> 0x803DBDC4
void UIPanel::Load(class UIPanel * const this /* r29 */) {
    // Local variables
    class FilePath file; // r1+0x28
    enum LoaderPos pos; // r30
    class DataArray * data; // r27
    class Object * old_this; // r26
    class DataArray * data; // r26

    // References
    // -> static class Symbol allow_home_menu;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol fileSym;
    // -> static class Symbol proj_file;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message msg; // size: 0x8, address: 0x8097E2D8
// Range: 0x803DBDC4 -> 0x803DBF80
void UIPanel::Unload(class UIPanel * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x8097E2F0
// Range: 0x803DBF80 -> 0x803DC214
unsigned char UIPanel::IsLoaded(class UIPanel * const this /* r31 */) {
    // Local variables
    class DataNode ret; // r1+0x18

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__8PanelDir;
}

// Range: 0x803DC214 -> 0x803DC288
unsigned char UIPanel::CheckIsLoaded(class UIPanel * const this /* r31 */) {}

static class Message msg; // size: 0x8, address: 0x8097E308
// Range: 0x803DC288 -> 0x803DC3D4
void UIPanel::FinishLoad(class UIPanel * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x803DC3D4 -> 0x803DC3F8
class UIComponent * UIPanel::FocusComponent() {}

// Range: 0x803DC3F8 -> 0x803DC4A8
void * UIPanel::~UIPanel(class UIPanel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__7UIPanel;
}

// Range: 0x803DC4A8 -> 0x803DC4DC
unsigned char UIPanel::Entering() {}

// Range: 0x803DC4DC -> 0x803DC510
unsigned char UIPanel::Exiting() {}

static class Message msg; // size: 0x8, address: 0x8097E320
// Range: 0x803DC510 -> 0x803DC6F8
void UIPanel::Enter(class UIPanel * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message msg; // size: 0x8, address: 0x8097E338
// Range: 0x803DC6F8 -> 0x803DC920
void UIPanel::Exit(class UIPanel * const this /* r31 */) {
    // Local variables
    unsigned char resetFocus; // r1+0x8

    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Message msg; // size: 0x8, address: 0x8097E350
// Range: 0x803DC920 -> 0x803DCA8C
void UIPanel::Poll(class UIPanel * const this /* r31 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x803DCA8C -> 0x803DCABC
void UIPanel::Draw() {}

// Range: 0x803DCABC -> 0x803DCADC
void UIPanel::SetFocusComponent() {}

static class Symbol _s; // size: 0x4, address: 0x80A51C20
static class Symbol _s; // size: 0x4, address: 0x80A51C28
static class Symbol _s; // size: 0x4, address: 0x80A51C30
static class Symbol _s; // size: 0x4, address: 0x80A51C38
static class Symbol _s; // size: 0x4, address: 0x80A51C40
static class Symbol _s; // size: 0x4, address: 0x80A51C48
static class Symbol _s; // size: 0x4, address: 0x80A51C50
static class Symbol _s; // size: 0x4, address: 0x80A51C58
static class Symbol _s; // size: 0x4, address: 0x80A51C60
static class Symbol _s; // size: 0x4, address: 0x80A51C68
static class Symbol _s; // size: 0x4, address: 0x80A51C70
static class Symbol _s; // size: 0x4, address: 0x80A51C78
static class Symbol _s; // size: 0x4, address: 0x80A51C80
static class Symbol _s; // size: 0x4, address: 0x80A51C88
static class Symbol _s; // size: 0x4, address: 0x80A51C90
// Range: 0x803DCADC -> 0x803DDD60
class DataNode UIPanel::Handle(class UIPanel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x60
    class MessageTimer _mt; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode _n; // r1+0x70
    class DataNode _n; // r1+0x68

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
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

// Range: 0x803DDD60 -> 0x803DDE3C
class DataNode UIPanel::OnLoad(class UIPanel * const this /* r30 */, class DataArray * d /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LoadMgr TheLoadMgr;
}

struct {
    // total size: 0xAC
} __vt__7UIPanel; // size: 0xAC, address: 0x808E4930

