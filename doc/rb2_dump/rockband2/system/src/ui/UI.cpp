/*
    Compile unit: C:\rockband2\system\src\ui\UI.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803EF270 -> 0x803F5B64
*/
class Symbol t; // size: 0x4, address: 0x80A51E7C
class Symbol name; // size: 0x4, address: 0x80A51E84
class Symbol button_down; // size: 0x4, address: 0x80A51E8C
class Symbol button_down; // size: 0x4, address: 0x80A51E94
class Message msg; // size: 0x8, address: 0x8097E570
class Symbol button_down; // size: 0x4, address: 0x80A51E9C
class ButtonDownMsg b_msg; // size: 0x8, address: 0x8097E578
static class Symbol _s; // size: 0x4, address: 0x80A51EA4
static class Symbol _s; // size: 0x4, address: 0x80A51EAC
static class Symbol _s; // size: 0x4, address: 0x80A51EB4
static class Symbol _s; // size: 0x4, address: 0x80A51EBC
static class Symbol _s; // size: 0x4, address: 0x80A51EC4
class Automator : public Object {
    // total size: 0x60
    class DataArray * mScreenScripts; // offset 0x28, size 0x4
    class DataArray * mRecord; // offset 0x2C, size 0x4
    class String mRecordPath; // offset 0x30, size 0xC
    class String mAutoPath; // offset 0x3C, size 0xC
    class DataArray * mCurScript; // offset 0x48, size 0x4
    int mCurScreenIndex; // offset 0x4C, size 0x4
    int mCurMsgIndex; // offset 0x50, size 0x4
    int mFramesSinceAdvance; // offset 0x54, size 0x4
    class list mCustomMsgs; // offset 0x58, size 0x8
};
// Range: 0x803EF270 -> 0x803EF8C8
class DataNode Automator::Handle(class Automator * const this /* r29 */, class DataArray * _msg /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68

    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x803EF8C8 -> 0x803EFB08
char * Automator::ToggleAuto(class Automator * const this /* r31 */) {
    // Local variables
    class Loader * l; // r27
    class DataLoader * dl; // r27

    // References
    // -> const char * gNullStr;
    // -> class UIManager TheUI;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__10DataLoader;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x803EFB08 -> 0x803EFBF4
char * Automator::ToggleRecord(class Automator * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803EFBF4 -> 0x803EFCA8
void Automator::AddMessageType(class Automator * const this /* r30 */, class Symbol & msg_type /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std19_List_node<6Symbol>;
    // -> unsigned char gStlAllocNameLookup;
    // -> const char * gNullStr;
}

// Range: 0x803EFCA8 -> 0x803EFE24
class DataNode Automator::OnMsg(class Automator * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
}

// Range: 0x803EFE24 -> 0x803F0310
class DataNode Automator::OnMsg(class Automator * const this /* r29 */, const class ButtonDownMsg & msg /* r26 */) {
    // Local variables
    class DataArrayPtr b_array; // r1+0x68

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class Symbol button_down;
    // -> class UIManager TheUI;
}

// Range: 0x803F0310 -> 0x803F0808
class DataNode Automator::OnMsg(class Automator * const this /* r29 */) {
    // References
    // -> class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class UIManager TheUI;
}

// Range: 0x803F0808 -> 0x803F0D00
class DataNode Automator::OnMsg(class Automator * const this /* r29 */) {
    // References
    // -> class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class UIManager TheUI;
}

// Range: 0x803F0D00 -> 0x803F11F8
class DataNode Automator::OnMsg(class Automator * const this /* r29 */) {
    // References
    // -> class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class UIManager TheUI;
}

// Range: 0x803F11F8 -> 0x803F16F0
class DataNode Automator::OnMsg(class Automator * const this /* r29 */) {
    // References
    // -> class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class UIManager TheUI;
}

// Range: 0x803F16F0 -> 0x803F1C34
class DataNode Automator::OnCustomMsg(class Automator * const this /* r29 */) {
    // Local variables
    class Symbol type; // r1+0x50

    // References
    // -> class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> class UIManager TheUI;
}

class UIManager TheUI; // size: 0xE8, address: 0x8097E458
// Range: 0x803F1C34 -> 0x803F1D60
void * UIManager::UIManager(class UIManager * const this /* r29 */) {
    // References
    // -> struct [anonymous] __vt__9Automator;
    // -> struct [anonymous] __vt__9UIManager;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class UIScreen * _M_data; // offset 0x8, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class UIResource * _M_data; // offset 0x8, size 0x4
};
struct Compare {
    // total size: 0x1
};
// Range: 0x803F1D60 -> 0x803F1E10
void * UIManager::~UIManager(class UIManager * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__9UIManager;
}

// Range: 0x803F1E10 -> 0x803F1F70
void * Automator::~Automator(class Automator * const this /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__9Automator;
}

// Range: 0x803F1F70 -> 0x803F1F7C
static void TerminateCallback() {
    // References
    // -> class UIManager TheUI;
}

static class Message cheat_init_msg; // size: 0x8, address: 0x8097E550
static class Message init_msg; // size: 0x8, address: 0x8097E568
// Range: 0x803F1F7C -> 0x803F2978
void UIManager::Init(class UIManager * const this /* r28 */) {
    // Local variables
    class DataArray * data; // r29
    class DataArray * cam; // r25
    class DataArray * zrange; // r25
    class Color c; // r1+0xE0
    unsigned char b; // r1+0x10

    // References
    // -> static class Message init_msg;
    // -> static class Message cheat_init_msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol name;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> unsigned char sVerboseNotify;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndCam;
    // -> class Symbol name;
    // -> class ObjectDir * sMainDir;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x803F2978 -> 0x803F2D30
void UIManager::Terminate(class UIManager * const this /* r30 */) {
    // Local variables
    struct _List_iterator itr; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__18ObjDirPtr<6RndDir>;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x803F2D30 -> 0x803F3EC8
void UIManager::Poll(class UIManager * const this /* r27 */) {
    // Local variables
    struct _List_iterator i; // r1+0x64
    class UIScreen * to; // r3
    class UIScreen * prevScreen; // r26
    class UITransitionCompleteMsg msg; // r1+0x120
    class UITransitionCompleteMsg msg; // r1+0x118

    // References
    // -> struct [anonymous] __vt__23UITransitionCompleteMsg;
    // -> class Symbol t;
    // -> class PlatformMgr ThePlatformMgr;
    // -> class TaskMgr TheTaskMgr;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> class UIManager TheUI;
    // -> class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class UserMgr * TheUserMgr;
    // -> class Symbol button_down;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class ButtonDownMsg b_msg;
    // -> class Symbol button_down;
}

// Range: 0x803F3EC8 -> 0x803F3F54
void UIManager::Draw(class UIManager * const this /* r31 */) {
    // Local variables
    struct _List_iterator i; // r1+0x10
}

// Range: 0x803F3F54 -> 0x803F4048
void UIManager::CancelTransition(class UIManager * const this /* r31 */) {
    // Local variables
    enum TransitionState state; // r3
    class UIScreen * screen; // r4

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803F4048 -> 0x803F43FC
void UIManager::GotoScreen(class UIManager * const this /* r30 */, class UIScreen * screen /* r31 */, unsigned char back /* r28 */) {
    // Local variables
    struct _List_iterator i; // r1+0x18
    class UIScreenChangeMsg msg; // r1+0x48

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__17UIScreenChangeMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class Debug TheDebug;
}

// Range: 0x803F43FC -> 0x803F45FC
void UIManager::PushScreen(class UIManager * const this /* r30 */, class UIScreen * screen /* r31 */) {
    // Local variables
    struct _List_iterator s; // r1+0x30

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8UIScreen>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std22_List_node<P8UIScreen>; // size: 0x8, address: 0x808E7AE0
// Range: 0x803F45FC -> 0x803F4620
unsigned char UIManager::InComponentSelect() {}

// Range: 0x803F4620 -> 0x803F4644
class UIPanel * UIManager::FocusPanel() {}

// Range: 0x803F4644 -> 0x803F4678
class UIComponent * UIManager::FocusComponent() {
    // Local variables
    class UIPanel * p; // r0
}

// Range: 0x803F4678 -> 0x803F4710
class UIResource * UIManager::Resource(class UIManager * const this /* r29 */, const class UIComponent * const c /* r30 */) {
    // Local variables
    class UIResource * typeRes; // r31
    class UIResource * classRes; // r31
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std25_List_node<P10UIResource>; // size: 0x8, address: 0x808E7B68
struct pair {
    // total size: 0x8
    struct _List_iterator first; // offset 0x0, size 0x4
    struct _List_iterator second; // offset 0x4, size 0x4
};
// Range: 0x803F4710 -> 0x803F4874
class UIResource * UIManager::FindResource(class UIManager * const this /* r29 */, const class UIComponent * const c /* r30 */, unsigned char useType /* r31 */) {
    // Local variables
    class Symbol className; // r1+0x58
    class Symbol typeName; // r1+0x54
    struct pair p; // r1+0x68

    // References
    // -> const char * gNullStr;
}

// Range: 0x803F4874 -> 0x803F49E0
class DataNode UIManager::OnIsResource(class UIManager * const this /* r31 */, class DataArray * msg /* r26 */) {
    // Local variables
    class FilePath path; // r1+0x24
    struct _List_iterator itr; // r1+0x20

    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x803F49E0 -> 0x803F4AA0
void UIManager::UseJoypad(class UIManager * const this /* r30 */, unsigned char autoRepeat /* r31 */) {}

static class DataArray * presets; // size: 0x4, address: 0x80A51ECC
// Range: 0x803F4AA0 -> 0x803F4B44
class DataArray * UIManager::ColorPresets() {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class DataArray * presets;
}

// Range: 0x803F4B44 -> 0x803F4B90
static enum JoypadAction NavButtonToNavAction() {}

static class Symbol none; // size: 0x4, address: 0x80A51ED4
// Range: 0x803F4B90 -> 0x803F4C60
unsigned char UIManager::OverloadHorizontalNav(const class UIManager * const this /* r30 */, enum JoypadAction action /* r27 */, enum JoypadButton button /* r29 */, class Symbol & controller_type /* r28 */) {
    // References
    // -> static class Symbol none;
}

// Range: 0x803F4C60 -> 0x803F4C68
unsigned char UIManager::RequireFixedText() {}

// Range: 0x803F4C68 -> 0x803F4C70
void UIManager::SetRequireFixedText() {}

// Range: 0x803F4C70 -> 0x803F4C9C
class UIScreen * UIManager::BottomScreen() {}

// Range: 0x803F4C9C -> 0x803F4CF0
void UIManager::ToggleLoadTimes(class UIManager * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A51EDC
static class Symbol _s; // size: 0x4, address: 0x80A51EE4
static class Symbol _s; // size: 0x4, address: 0x80A51EEC
static class Symbol _s; // size: 0x4, address: 0x80A51EF4
static class Symbol _s; // size: 0x4, address: 0x80A51EFC
static class Symbol _s; // size: 0x4, address: 0x80A51F04
static class Symbol _s; // size: 0x4, address: 0x80A51F0C
static class Symbol _s; // size: 0x4, address: 0x80A51F14
static class Symbol _s; // size: 0x4, address: 0x80A51F1C
static class Symbol _s; // size: 0x4, address: 0x80A51F24
static class Symbol _s; // size: 0x4, address: 0x80A51F2C
static class Symbol _s; // size: 0x4, address: 0x80A51F34
static class Symbol _s; // size: 0x4, address: 0x80A51F3C
static class Symbol _s; // size: 0x4, address: 0x80A51F44
static class Symbol _s; // size: 0x4, address: 0x80A51F4C
// Range: 0x803F4CF0 -> 0x803F56E8
class DataNode UIManager::Handle(class UIManager * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x20
    class MessageTimer _mt; // r1+0x60
    class DataNode _n; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

class KeyboardKeyMsg : public Message {
    // total size: 0x8
};
// Range: 0x803F56E8 -> 0x803F585C
class DataNode UIManager::OnGotoScreen(class UIManager * const this /* r28 */, const class DataArray * a /* r29 */) {
    // Local variables
    class UIScreen * scr; // r30

    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8UIScreen;
}

// Range: 0x803F585C -> 0x803F5B1C
class DataNode UIManager::ForeachScreen(class UIManager * const this /* r29 */, const class DataArray * a /* r30 */) {
    // Local variables
    class DataNode * var; // r31
    class DataNode tmp; // r1+0x68
    class list screens; // r1+0x60
    struct _List_iterator s; // r1+0x3C
    int j; // r27

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<P8UIScreen>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x54
} __vt__9Automator; // size: 0x54, address: 0x808E7C9C
struct {
    // total size: 0x8
} __RTTI__9Automator; // size: 0x8, address: 0x808E7D10
struct {
    // total size: 0x54
} __vt__9UIManager; // size: 0x54, address: 0x808E7D18
struct {
    // total size: 0x8
} __RTTI__9UIManager; // size: 0x8, address: 0x808E7D90
class _List_node : public _List_node_base {
    // total size: 0x18
public:
    struct UIText _M_data; // offset 0x8, size 0x10
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct UIFont _M_data; // offset 0x8, size 0x8
};
class _List_node : public _List_node_base {
    // total size: 0x10
public:
    struct UIMat _M_data; // offset 0x8, size 0x8
};
// Range: 0x803F5B1C -> 0x803F5B64
static void __sinit_\UI_cpp() {
    // References
    // -> class UIManager TheUI;
}


