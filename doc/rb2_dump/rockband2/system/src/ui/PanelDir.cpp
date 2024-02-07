/*
    Compile unit: C:\rockband2\system\src\ui\PanelDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803DDE50 -> 0x803E1948
*/
static unsigned char gSendFocusMsg; // size: 0x1, address: 0x80A46F78
// Range: 0x803DDE50 -> 0x803DE020
void * PanelDir::PanelDir(class PanelDir * const this /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> struct [anonymous] __vt__8PanelDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

class UITrigger : public EventTrigger {
    // total size: 0xBC
    unsigned char mBlockTransition; // offset 0xB0, size 0x1
    float mStartTime; // offset 0xB4, size 0x4
    float mEndTime; // offset 0xB8, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class UITrigger * _M_data; // offset 0x8, size 0x4
};
struct ObjMatchPr {
    // total size: 0x4
    class Object * mObj; // offset 0x0, size 0x4
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class UIComponent * _M_data; // offset 0x8, size 0x4
};
// Range: 0x803DE020 -> 0x803DE674
void * PanelDir::~PanelDir(class PanelDir * const this /* r29 */) {
    // Local variables
    class RndDir * * i; // r31
    class RndDir * * i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndPollable,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__26ObjPtr<6RndCam,9ObjectDir>;
    // -> struct [anonymous] __vt__8PanelDir;
}

// Range: 0x803DE674 -> 0x803DE6B8
void PanelDir::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803DE6B8 -> 0x803DE7D0
void PanelDir::PreLoad(class PanelDir * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0x10

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> class Debug TheDebug;
}

// Range: 0x803DE7D0 -> 0x803DE94C
void PanelDir::PostLoad(class PanelDir * const this /* r31 */, class BinStream & d /* r29 */) {
    // Local variables
    class Symbol testEvent; // r1+0x18

    // References
    // -> class UIManager TheUI;
    // -> const char * gNullStr;
    // -> class list sRevs;
}

// Range: 0x803DE94C -> 0x803DEA2C
void PanelDir::Copy(class PanelDir * const this /* r29 */, const class Object * o /* r30 */) {
    // Local variables
    const class PanelDir * p; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8PanelDir;
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class UIComponent * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class UITrigger * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x803DEA2C -> 0x803DF0F0
void PanelDir::SyncObjects(class PanelDir * const this /* r31 */) {
    // Local variables
    class ObjDirItr i; // r1+0x44
    class ObjDirItr i; // r1+0x30

    // References
    // -> static unsigned char gSendFocusMsg;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std23_List_node<P9UITrigger>;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __RTTI__9UITrigger;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std23_List_node<P9UITrigger>; // size: 0x8, address: 0x808E4BB8
// Range: 0x803DF0F0 -> 0x803DF1A8
void PanelDir::RemovingObject(class PanelDir * const this /* r30 */, class Object * o /* r31 */) {}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x803DF1A8 -> 0x803DF1E0
class RndCam * PanelDir::CamOverride() {
    // References
    // -> class UIManager TheUI;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x803DF1E0 -> 0x803DF304
void PanelDir::DrawShowing(class PanelDir * const this /* r30 */) {
    // Local variables
    class RndCam * cam; // r0
    class RndDir * * i; // r31
    class RndDir * * i; // r31

    // References
    // -> class RndEnviron * sCurrent;
    // -> class UIManager TheUI;
    // -> class RndCam * sCurrent;
    // -> class Rnd & TheRnd;
}

static class Message msg; // size: 0x8, address: 0x8097E368
static class Symbol ui_enter_forward; // size: 0x4, address: 0x80A51C9C
static class Symbol ui_enter_back; // size: 0x4, address: 0x80A51CA4
// Range: 0x803DF304 -> 0x803DF4B4
void PanelDir::Enter(class PanelDir * const this /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x20

    // References
    // -> static class Symbol ui_enter_back;
    // -> static class Symbol ui_enter_forward;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message msg; // size: 0x8, address: 0x8097E380
static class Symbol ui_exit_forward; // size: 0x4, address: 0x80A51CAC
static class Symbol ui_exit_back; // size: 0x4, address: 0x80A51CB4
// Range: 0x803DF4B4 -> 0x803DF628
void PanelDir::Exit(class PanelDir * const this /* r30 */) {
    // References
    // -> static class Symbol ui_exit_back;
    // -> static class Symbol ui_exit_forward;
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
}

static class Message dirMsg; // size: 0x8, address: 0x8097E398
// Range: 0x803DF628 -> 0x803DF85C
void PanelDir::SendTransition(class PanelDir * const this /* r28 */, const class Message & msg /* r29 */, class Symbol & forward /* r30 */, class Symbol & back /* r31 */) {
    // References
    // -> class UIManager TheUI;
    // -> static class Message dirMsg;
    // -> struct [anonymous] __vt__7Message;
}

// Range: 0x803DF85C -> 0x803DF92C
unsigned char PanelDir::Entering(class PanelDir * const this /* r31 */) {
    // Local variables
    struct _List_iterator c; // r1+0x1C
    struct _List_iterator c; // r1+0x18
}

// Range: 0x803DF92C -> 0x803DF9FC
unsigned char PanelDir::Exiting(class PanelDir * const this /* r31 */) {
    // Local variables
    struct _List_iterator c; // r1+0x1C
    struct _List_iterator c; // r1+0x18
}

// Range: 0x803DF9FC -> 0x803DFA3C
class UIComponent * PanelDir::FindComponent() {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

// Range: 0x803DFA3C -> 0x803DFAB4
void PanelDir::AddComponent(class UIComponent * component /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11UIComponent>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std26_List_node<P11UIComponent>; // size: 0x8, address: 0x808E4C48
// Range: 0x803DFAB4 -> 0x803DFDBC
void PanelDir::SetFocusComponent(class PanelDir * const this /* r30 */, class UIComponent * newComponent /* r31 */) {
    // Local variables
    class UIComponentFocusChangeMsg msg; // r1+0x38

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__25UIComponentFocusChangeMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static unsigned char gSendFocusMsg;
}

// Range: 0x803DFDBC -> 0x803DFE54
void PanelDir::EnableComponent(class PanelDir * const this /* r29 */, class UIComponent * c /* r30 */, enum RequestFocus focusable /* r31 */) {}

static class Symbol none; // size: 0x4, address: 0x80A51CBC
// Range: 0x803DFE54 -> 0x803DFFA4
void PanelDir::DisableComponent(class PanelDir * const this /* r27 */, class UIComponent * c /* r28 */, enum JoypadAction nav_action /* r29 */) {
    // References
    // -> static class Symbol none;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A51CC4
static class Symbol _s; // size: 0x4, address: 0x80A51CCC
static class Symbol _s; // size: 0x4, address: 0x80A51CD4
static class Symbol _s; // size: 0x4, address: 0x80A51CDC
// Range: 0x803DFFA4 -> 0x803E0A44
class DataNode PanelDir::Handle(class PanelDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x3C
    class MessageTimer _mt; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode _n; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode _n; // r1+0x48

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__13ButtonDownMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> static class Symbol _s;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x803E0A44 -> 0x803E0B00
unsigned char PanelDir::PanelNav(class PanelDir * const this /* r28 */, enum JoypadAction a /* r29 */, enum JoypadButton b /* r30 */, class Symbol & controller_type /* r31 */) {
    // Local variables
    class UIComponent * c; // r4
}

// Range: 0x803E0B00 -> 0x803E0C68
class UIComponent * PanelDir::ComponentNav(class PanelDir * const this /* r29 */, class UIComponent * c /* r30 */, enum JoypadAction a /* r28 */) {
    // Local variables
    class UIComponent * next; // r31
    unsigned char overload; // r0
    struct _List_iterator i; // r1+0x20
    struct _List_iterator i; // r1+0x1C

    // References
    // -> class UIManager TheUI;
}

// Range: 0x803E0C68 -> 0x803E0E04
class DataNode PanelDir::OnMsg(class PanelDir * const this /* r28 */, const class ButtonDownMsg & msg /* r29 */) {
    // Local variables
    class DataNode ret; // r1+0x18
}

// Range: 0x803E0E04 -> 0x803E0F04
class DataNode PanelDir::OnEnableComponent(class PanelDir * const this /* r29 */, const class DataArray * a /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

// Range: 0x803E0F04 -> 0x803E1004
class DataNode PanelDir::OnDisableComponent(class PanelDir * const this /* r29 */, const class DataArray * a /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11UIComponent;
}

// Range: 0x803E1004 -> 0x803E12B4
void PanelDir::SyncEditModePanels(class PanelDir * const this /* r31 */) {
    // Local variables
    class RndDir * * i; // r30
    class RndDir * * i; // r30
    class FilePath * i; // r29
    class FilePath path; // r1+0x24
    class RndDir * dir; // r1+0x14
    class FilePath * i; // r29
    class FilePath path; // r1+0x18
    class RndDir * dir; // r1+0x10

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> struct [anonymous] __vt__8FilePath;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x803E12B4 -> 0x803E15B4
unsigned char PanelDir::PropSyncEditModePanels(class PanelDir * const this /* r29 */, class vector & paths /* r30 */, class DataNode & n /* r31 */, class DataArray * prop /* r26 */, int i /* r27 */, enum PropOp op /* r28 */) {
    // Local variables
    class FilePath * it; // r27

    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

static class Symbol _s; // size: 0x4, address: 0x80A51CE4
static class Symbol _s; // size: 0x4, address: 0x80A51CEC
static class Symbol _s; // size: 0x4, address: 0x80A51CF4
static class Symbol _s; // size: 0x4, address: 0x80A51CFC
static class Symbol _s; // size: 0x4, address: 0x80A51D04
// Range: 0x803E15B4 -> 0x803E1948
unsigned char PanelDir::SyncProperty(class PanelDir * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x8
} __RTTI__9UITrigger; // size: 0x8, address: 0x808E4E50
struct {
    // total size: 0x234
} __vt__8PanelDir; // size: 0x234, address: 0x808E4F10
struct {
    // total size: 0x8
} __RTTI__PP6RndDir; // size: 0x8, address: 0x808E55C0
struct {
    // total size: 0x8
} __RTTI__P8FilePath; // size: 0x8, address: 0x808E55D8

