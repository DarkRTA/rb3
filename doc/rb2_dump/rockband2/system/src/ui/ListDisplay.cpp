/*
    Compile unit: C:\rockband2\system\src\ui\ListDisplay.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803D344C -> 0x803D50F8
*/
// Range: 0x803D344C -> 0x803D3674
void * ListDisplay::ListDisplay(class ListDisplay * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
}

// Range: 0x803D3674 -> 0x803D37A8
void * ListDisplay::~ListDisplay(class ListDisplay * const this /* r31 */) {}

// Range: 0x803D37A8 -> 0x803D3884
unsigned char ListDisplay::Collide(class ListDisplay * const this /* r27 */, const class Segment & s /* r28 */, float & dist /* r29 */, class Plane & plane /* r30 */) {}

// Range: 0x803D3884 -> 0x803D395C
int ListDisplay::CollidePlane(class ListDisplay * const this /* r29 */, const class Plane & plane /* r30 */) {
    // Local variables
    int collide; // r0
}

// Range: 0x803D395C -> 0x803D3964
float ListDisplay::Spacing() {}

// Range: 0x803D3964 -> 0x803D396C
float ListDisplay::ArrowOffset() {}

// Range: 0x803D396C -> 0x803D3974
enum ListShowing ListDisplay::GetArrowShowing() {}

// Range: 0x803D3974 -> 0x803D397C
unsigned char ListDisplay::ArrowOnlyScroll() {}

// Range: 0x803D397C -> 0x803D3984
unsigned char ListDisplay::ArrowsOnHighlight() {}

// Range: 0x803D3984 -> 0x803D398C
enum ListShowing ListDisplay::GetHighlightShowing() {}

// Range: 0x803D398C -> 0x803D3994
unsigned char ListDisplay::IsVertical() {}

// Range: 0x803D3994 -> 0x803D399C
int ListDisplay::FadeOffset() {}

// Range: 0x803D399C -> 0x803D39A4
void ListDisplay::SetSpacing() {}

// Range: 0x803D39A4 -> 0x803D39AC
void ListDisplay::SetArrowOffset() {}

// Range: 0x803D39AC -> 0x803D39B4
void ListDisplay::SetArrowShowing() {}

// Range: 0x803D39B4 -> 0x803D39BC
void ListDisplay::SetArrowOnlyScroll() {}

// Range: 0x803D39BC -> 0x803D39C4
void ListDisplay::SetArrowsOnHighlight() {}

// Range: 0x803D39C4 -> 0x803D39CC
void ListDisplay::SetHighlightShowing() {}

// Range: 0x803D39CC -> 0x803D39D4
void ListDisplay::SetVertical() {}

static class Symbol vertical; // size: 0x4, address: 0x80A51AF4
static class Symbol element; // size: 0x4, address: 0x80A51AFC
static class Symbol colors; // size: 0x4, address: 0x80A51B04
static class Symbol back_arrow; // size: 0x4, address: 0x80A51B0C
static class Symbol next_arrow; // size: 0x4, address: 0x80A51B14
static class Symbol highlight; // size: 0x4, address: 0x80A51B1C
static class Symbol draw_first; // size: 0x4, address: 0x80A51B24
// Range: 0x803D39D4 -> 0x803D3D08
void ListDisplay::UpdateObjects(class ListDisplay * const this /* r28 */, class DataArray * listType /* r29 */, class ObjectDir * resources /* r30 */) {
    // Local variables
    class DataArray * h; // r31
    int i; // r29

    // References
    // -> static class Symbol draw_first;
    // -> static class Symbol highlight;
    // -> static class Symbol next_arrow;
    // -> static class Symbol back_arrow;
    // -> static class Symbol colors;
    // -> static class Symbol element;
    // -> static class Symbol vertical;
}

static class Symbol focused; // size: 0x4, address: 0x80A51B2C
static class Symbol selected; // size: 0x4, address: 0x80A51B34
static class Symbol selecting; // size: 0x4, address: 0x80A51B3C
static class Symbol normal; // size: 0x4, address: 0x80A51B44
static class Symbol highlight; // size: 0x4, address: 0x80A51B4C
static class Symbol disabled; // size: 0x4, address: 0x80A51B54
// Range: 0x803D3D08 -> 0x803D4290
void ListDisplay::Draw(class ListDisplay * const this /* r19 */, class Symbol & state /* r20 */, unsigned char pre_draw /* r21 */) {
    // Local variables
    class ListState & ls; // r27
    unsigned char highlight_showing; // r0
    int display; // r18
    int showing; // r26
    int data; // r25
    class Symbol elementState; // r1+0x1C
    int highlight_idx; // r24
    int direction; // r0
    int num_display; // r23
    int new_data; // r22
    unsigned char can_scroll_back; // r18
    unsigned char can_scroll_next; // r20

    // References
    // -> static class Symbol disabled;
    // -> static class Symbol highlight;
    // -> static class Symbol normal;
    // -> static class Symbol selecting;
    // -> static class Symbol selected;
    // -> static class Symbol focused;
}

static class Symbol selecting; // size: 0x4, address: 0x80A51B5C
static class Symbol normal; // size: 0x4, address: 0x80A51B64
static class Symbol disabled; // size: 0x4, address: 0x80A51B6C
// Range: 0x803D4290 -> 0x803D448C
void ListDisplay::DrawHighlight(class ListDisplay * const this /* r30 */, class Symbol & state /* r31 */) {
    // Local variables
    const class ListState & ls; // r28
    class Color highlight_color; // r1+0x30
    int data; // r27
    int showing; // r26

    // References
    // -> static class Symbol disabled;
    // -> static class Symbol normal;
    // -> static class Symbol selecting;
}

// Range: 0x803D448C -> 0x803D45A0
void ListDisplay::CalcBoundingBox(class ListDisplay * const this /* r29 */, class Box & bb /* r30 */) {
    // Local variables
    class Box element_box; // r1+0x10
}

// Range: 0x803D45A0 -> 0x803D45B0
class UIList * ListDisplay::ChildList() {}

// Range: 0x803D45B0 -> 0x803D45F0
void ListDisplay::Poll(class ListDisplay * const this /* r31 */) {}

// Range: 0x803D45F0 -> 0x803D4658
void ListDisplay::FillAll(class ListDisplay * const this /* r29 */) {
    // Local variables
    int num_display; // r0
    int i; // r30
}

// Range: 0x803D4658 -> 0x803D4664
void ListDisplay::MakeDirty() {}

// Range: 0x803D4664 -> 0x803D476C
class ListElement * ListDisplay::Create(class ListDisplay * const this /* r29 */, class DataArray * slots /* r30 */, class ObjectDir * resources /* r31 */) {
    // Local variables
    class ListElement * e; // r1+0x10

    // References
    // -> class Symbol name;
}

// Range: 0x803D476C -> 0x803D4860
void ListDisplay::DestroyAll(class ListDisplay * const this /* r29 */) {}

// Range: 0x803D4860 -> 0x803D4990
void ListDisplay::StartScroll(class ListDisplay * const this /* r29 */) {
    // Local variables
    class ListState & ls; // r30
    class ListElement * * it; // r4

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803D4990 -> 0x803D4CA0
void ListDisplay::PollElements(class ListDisplay * const this /* r29 */) {
    // Local variables
    class ListState & ls; // r31
    int numDisplay; // r30
    int offset; // r23
    float topFadePos; // f0
    float botFadePos; // f0
    float scroll; // f1
    float elePos; // f28
    float gap; // f0
    float fade; // f1
    float bot_fade_gap; // f29
    float lastFade; // f0

    // References
    // -> class Debug TheDebug;
}

// Range: 0x803D4CA0 -> 0x803D4D68
void ListDisplay::CompleteScroll(class ListDisplay * const this /* r31 */) {
    // Local variables
    class ListState & ls; // r0
    class ListElement * newNext; // r1+0x14
}

// Range: 0x803D4D68 -> 0x803D4DB0
void ListDisplay::SetListPos(class ListDisplay * const this /* r30 */, class RndTransformable * t /* r31 */) {}

// Range: 0x803D4DB0 -> 0x803D4DE4
float ListDisplay::ElementPos() {}

// Range: 0x803D4DE4 -> 0x803D4E70
void ListDisplay::SetTransPos() {
    // Local variables
    class Vector3 transPos; // r1+0x10
}

// Range: 0x803D4E70 -> 0x803D4F20
void ListDisplay::FillElement(class ListDisplay * const this /* r27 */, int display /* r28 */) {
    // Local variables
    class ListState & ls; // r31
    int data; // r30
    int showing; // r29
    class ListElement * element; // r28
}

// Range: 0x803D4F20 -> 0x803D4FC4
int ListDisplay::NumDisplay() {
    // Local variables
    class ListState & ls; // r31
    int num; // r1+0xC
    int num_data; // r1+0x8
}

// Range: 0x803D4FC4 -> 0x803D50F8
void ListDisplay::CopyTypeMesh(class ListDisplay * const this /* r26 */, class RndMesh * m /* r27 */, class ObjectDir * dir /* r28 */, const char * name /* r29 */) {
    // Local variables
    unsigned char showing; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
}

struct {
    // total size: 0x8
} __RTTI__PP11ListElement; // size: 0x8, address: 0x808E3590
struct _OKToMemCpy {
    // total size: 0x1
};

