/*
    Compile unit: C:\rockband2\system\src\ui\List.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803CEE8C -> 0x803D2834
*/
class Symbol t; // size: 0x4, address: 0x80A5199C
class Symbol t; // size: 0x4, address: 0x80A519A4
class DataArray * types; // size: 0x4, address: 0x80A519A8
// Range: 0x803CEE8C -> 0x803CF044
void * UIList::UIList(class UIList * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> struct [anonymous] __vt__6UIList;
    // -> struct [anonymous] __vt__12ListProvider;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x803CF044 -> 0x803CF1F4
void * UIList::~UIList(class UIList * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__6UIList;
}

static int REV; // size: 0x4, address: 0x80A46F34
static int gRev; // size: 0x4, address: 0x80A519B0
// Range: 0x803CF1F4 -> 0x803CF238
void UIList::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803CF238 -> 0x803CF294
void UIList::Load(class UIList * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803CF294 -> 0x803CF35C
void UIList::PreLoad(class UIList * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int REV;
    // -> static int gRev;
}

// Range: 0x803CF35C -> 0x803CF3B4
void UIList::Print(class UIList * const this /* r4 */) {
    // References
    // -> class Debug TheDebug;
}

static unsigned char gLoading; // size: 0x1, address: 0x80A519B4
// Range: 0x803CF3B4 -> 0x803CF764
void UIList::PostLoad(class UIList * const this /* r23 */, class BinStream & d /* r24 */) {
    // Local variables
    float spacing; // r1+0x38
    float arrowOffset; // r1+0x34
    enum ListShowing arrow_showing; // r31
    unsigned char arrow_only_scroll; // r30
    unsigned char arrows_on_highlight; // r29
    enum ListShowing highlight_showing; // r28
    int fadeOffset; // r1+0x30
    int numDisplay; // r1+0x2C
    unsigned char circular; // r27
    float speed; // r1+0x28
    unsigned char scroll_past_min_display; // r26
    unsigned char scroll_past_max_display; // r25
    int min_display; // r1+0x24
    int max_display; // r1+0x20
    int as; // r1+0x1C
    int ls; // r1+0x18
    float tmpGapSize; // r1+0x14
    int tmpGapFrequency; // r1+0x10

    // References
    // -> static unsigned char gLoading;
    // -> static int gRev;
}

// Range: 0x803CF764 -> 0x803CF76C
float UIList::Spacing() {}

// Range: 0x803CF76C -> 0x803CF774
float UIList::ArrowOffset() {}

// Range: 0x803CF774 -> 0x803CF77C
int UIList::NumDisplay() {}

// Range: 0x803CF77C -> 0x803CF784
unsigned char UIList::IsCircular() {}

// Range: 0x803CF784 -> 0x803CF78C
float UIList::Speed() {}

// Range: 0x803CF78C -> 0x803CF794
int UIList::FadeOffset() {}

// Range: 0x803CF794 -> 0x803CF79C
int UIList::FirstShowing() {}

// Range: 0x803CF79C -> 0x803CF7A4
int UIList::Selected() {}

// Range: 0x803CF7A4 -> 0x803CF7AC
int UIList::SelectedDisplay() {}

// Range: 0x803CF7AC -> 0x803CF7B4
int UIList::SelectedData() {}

// Range: 0x803CF7B4 -> 0x803CF7BC
int UIList::SelectedPos() {}

// Range: 0x803CF7BC -> 0x803CF88C
class Symbol UIList::SelectedSym(const class UIList * const this /* r29 */, unsigned char fail /* r30 */) {
    // Local variables
    class Symbol selected; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> const char * gNullStr;
}

// Range: 0x803CF88C -> 0x803CF894
unsigned char UIList::IsScrolling() {}

static class Symbol element; // size: 0x4, address: 0x80A519B8
static class Symbol dummy; // size: 0x4, address: 0x80A519C0
// Range: 0x803CF894 -> 0x803CF958
char * UIList::DummyData(const class UIList * const this /* r30 */, class Symbol & slot /* r31 */) {
    // References
    // -> static class Symbol dummy;
    // -> static class Symbol element;
}

// Range: 0x803CF958 -> 0x803CF960
void UIList::CalcBoundingBox() {}

// Range: 0x803CF960 -> 0x803CF968
class ListState & UIList::GetListState() {}

// Range: 0x803CF968 -> 0x803CF9A4
class UIList * UIList::ChildList(class UIList * const this /* r31 */) {}

// Range: 0x803CF9A4 -> 0x803CF9AC
unsigned char UIList::IsAutoScrolling() {}

// Range: 0x803CF9AC -> 0x803CF9F0
void UIList::SetSpacing(class UIList * const this /* r31 */) {}

// Range: 0x803CF9F0 -> 0x803CF9F8
void UIList::SetArrowOffset() {}

// Range: 0x803CF9F8 -> 0x803CFA48
void UIList::SetNumDisplay(class UIList * const this /* r31 */) {
    // References
    // -> static unsigned char gLoading;
}

// Range: 0x803CFA48 -> 0x803CFAA0
void UIList::SetCircular(class UIList * const this /* r31 */) {
    // References
    // -> static unsigned char gLoading;
}

// Range: 0x803CFAA0 -> 0x803CFAB4
void UIList::SetCircularOnly() {
    // References
    // -> static unsigned char gLoading;
}

// Range: 0x803CFAB4 -> 0x803CFABC
void UIList::SetSpeed() {}

// Range: 0x803CFABC -> 0x803CFAC4
void UIList::SetFadeOffset() {}

// Range: 0x803CFAC4 -> 0x803CFB50
void UIList::SetSelected(class UIList * const this /* r29 */, int pos /* r30 */, int first_showing /* r31 */) {}

// Range: 0x803CFB50 -> 0x803CFC14
unsigned char UIList::SetSelected(class UIList * const this /* r28 */, class Symbol & sym /* r29 */, unsigned char fail /* r30 */, int first_showing /* r31 */) {
    // Local variables
    int data; // r4

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803CFC14 -> 0x803CFC90
void UIList::SetSelectedSimulateScroll(class UIList * const this /* r30 */, int pos /* r31 */) {}

// Range: 0x803CFC90 -> 0x803CFD44
unsigned char UIList::SetSelectedSimulateScroll(class UIList * const this /* r29 */, class Symbol & sym /* r30 */, unsigned char fail /* r31 */) {
    // Local variables
    int data; // r4

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803CFD44 -> 0x803CFDB0
void UIList::SetProvider(class UIList * const this /* r31 */) {}

// Range: 0x803CFDB0 -> 0x803CFE00
void UIList::Scroll(class UIList * const this /* r30 */, int direction /* r31 */) {}

// Range: 0x803CFE00 -> 0x803CFE08
void UIList::SetParent() {}

// Range: 0x803CFE08 -> 0x803CFEB4
void UIList::SelectChildList(class UIList * const this /* r30 */, class UIList * l /* r31 */) {
    // Local variables
    class PanelDir * d; // r0

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803CFEB4 -> 0x803CFF60
void UIList::SelectParentList(class UIList * const this /* r31 */) {
    // Local variables
    class PanelDir * d; // r0

    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803CFF60 -> 0x803CFFAC
void UIList::AutoScroll(class UIList * const this /* r31 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803CFFAC -> 0x803CFFB8
void UIList::StopAutoScroll() {}

// Range: 0x803CFFB8 -> 0x803D0068
void UIList::Update(class UIList * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static unsigned char gLoading;
}

// Range: 0x803D0068 -> 0x803D009C
void UIList::Enter(class UIList * const this /* r31 */) {}

// Range: 0x803D009C -> 0x803D0134
void UIList::Poll(class UIList * const this /* r30 */) {
    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803D0134 -> 0x803D013C
void UIList::DrawShowing() {}

// Range: 0x803D013C -> 0x803D0144
void UIList::PreDraw() {}

// Range: 0x803D0144 -> 0x803D0198
void UIList::DrawImp(class UIList * const this /* r30 */, unsigned char pre_draw /* r31 */) {}

// Range: 0x803D0198 -> 0x803D01DC
class RndDrawable * UIList::CollideShowing(class UIList * const this /* r31 */) {}

// Range: 0x803D01DC -> 0x803D01E4
int UIList::CollidePlane() {}

// Range: 0x803D01E4 -> 0x803D0210
char * UIList::Text() {}

// Range: 0x803D0210 -> 0x803D0290
class RndMat * UIList::Mat(const class UIList * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class UIManager TheUI;
}

// Range: 0x803D0290 -> 0x803D0298
int UIList::NumData() {}

// Range: 0x803D0298 -> 0x803D02A0
int UIList::SelectedAux() {}

// Range: 0x803D02A0 -> 0x803D02A8
void UIList::SetSelectedAux() {}

// Range: 0x803D02A8 -> 0x803D0518
class DataNode UIList::OnMsg(class UIList * const this /* r28 */, const class ButtonDownMsg & msg /* r29 */) {
    // Local variables
    class Symbol type; // r1+0x10
    int direction; // r4
    int page_direction; // r4
    class UIList * l; // r4
}

// Range: 0x803D0518 -> 0x803D0558
class DataNode UIList::OnMsg() {}

// Range: 0x803D0558 -> 0x803D08D0
class DataNode UIList::OnMsg(class UIList * const this /* r28 */) {
    // Local variables
    int selected_pos; // r0
    const class ListProvider * p; // r3

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__20UIComponentScrollMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803D08D0 -> 0x803D08D8
void UIList::MakeDirty() {}

static class Symbol _s; // size: 0x4, address: 0x80A519C8
static class Symbol _s; // size: 0x4, address: 0x80A519D0
static class Symbol _s; // size: 0x4, address: 0x80A519D8
static class Symbol _s; // size: 0x4, address: 0x80A519E0
static class Symbol _s; // size: 0x4, address: 0x80A519E8
static class Symbol _s; // size: 0x4, address: 0x80A519F0
static class Symbol _s; // size: 0x4, address: 0x80A519F8
static class Symbol _s; // size: 0x4, address: 0x80A51A00
static class Symbol _s; // size: 0x4, address: 0x80A51A08
static class Symbol _s; // size: 0x4, address: 0x80A51A10
static class Symbol _s; // size: 0x4, address: 0x80A51A18
static class Symbol _s; // size: 0x4, address: 0x80A51A20
static class Symbol _s; // size: 0x4, address: 0x80A51A28
static class Symbol _s; // size: 0x4, address: 0x80A51A30
static class Symbol _s; // size: 0x4, address: 0x80A51A38
static class Symbol _s; // size: 0x4, address: 0x80A51A40
static class Symbol _s; // size: 0x4, address: 0x80A51A48
static class Symbol _s; // size: 0x4, address: 0x80A51A50
// Range: 0x803D08D8 -> 0x803D13D4
class DataNode UIList::Handle(class UIList * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode _n; // r1+0x50
    class DataNode _n; // r1+0x48

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
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x803D13D4 -> 0x803D14FC
class DataNode UIList::OnSetData(class UIList * const this /* r28 */, class DataArray * args /* r29 */) {
    // References
    // -> struct [anonymous] __vt__12DataProvider;
}

// Range: 0x803D14FC -> 0x803D1710
class DataNode UIList::OnSetSelected(class UIList * const this /* r28 */, class DataArray * args /* r29 */) {
    // Local variables
    class DataNode arg; // r1+0x10
    int first_showing; // r31
    unsigned char fail; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803D1710 -> 0x803D18D8
class DataNode UIList::OnSetSelectedSimulateScroll(class UIList * const this /* r30 */, class DataArray * args /* r31 */) {
    // Local variables
    class DataNode arg; // r1+0x10

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803D18D8 -> 0x803D199C
class DataNode UIList::OnScroll(class UIList * const this /* r29 */, class DataArray * msg /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__4User;
}

static class Symbol _s; // size: 0x4, address: 0x80A51A58
static class Symbol _s; // size: 0x4, address: 0x80A51A60
static class Symbol _s; // size: 0x4, address: 0x80A51A68
static class Symbol _s; // size: 0x4, address: 0x80A51A70
static class Symbol _s; // size: 0x4, address: 0x80A51A78
static class Symbol _s; // size: 0x4, address: 0x80A51A80
static class Symbol _s; // size: 0x4, address: 0x80A51A88
static class Symbol _s; // size: 0x4, address: 0x80A51A90
static class Symbol _s; // size: 0x4, address: 0x80A51A98
static class Symbol _s; // size: 0x4, address: 0x80A51AA0
static class Symbol _s; // size: 0x4, address: 0x80A51AA8
static class Symbol _s; // size: 0x4, address: 0x80A51AB0
static class Symbol _s; // size: 0x4, address: 0x80A51AB8
static class Symbol _s; // size: 0x4, address: 0x80A51AC0
static class Symbol _s; // size: 0x4, address: 0x80A51AC8
static class Symbol _s; // size: 0x4, address: 0x80A51AD0
static class Symbol _s; // size: 0x4, address: 0x80A51AD8
static class Symbol _s; // size: 0x4, address: 0x80A51AE0
static class Symbol _s; // size: 0x4, address: 0x80A51AE8
// Range: 0x803D199C -> 0x803D2834
unsigned char UIList::SyncProperty(class UIList * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
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

struct {
    // total size: 0x1C8
} __vt__6UIList; // size: 0x1C8, address: 0x808E2CC0
struct {
    // total size: 0xC
} __vt__13ListScrollMsg; // size: 0xC, address: 0x808E2F00
struct {
    // total size: 0x8
} __RTTI__13ListScrollMsg; // size: 0x8, address: 0x808E2F28
struct {
    // total size: 0xC
} __vt__18ListScrollStartMsg; // size: 0xC, address: 0x808E2F30
struct {
    // total size: 0x8
} __RTTI__18ListScrollStartMsg; // size: 0x8, address: 0x808E2F60
struct {
    // total size: 0x44
} __vt__12DataProvider; // size: 0x44, address: 0x808E2F68
struct {
    // total size: 0x8
} __RTTI__12DataProvider; // size: 0x8, address: 0x808E2FC8

