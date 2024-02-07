/*
    Compile unit: C:\rockband2\system\src\ui\Label.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803CA4E0 -> 0x803CE950
*/
class DataArray * types; // size: 0x4, address: 0x80A518A0
class Symbol name; // size: 0x4, address: 0x80A518A8
unsigned char sDebugHighlight; // size: 0x1, address: 0x80A518AC
// Range: 0x803CA4E0 -> 0x803CA714
void * UILabel::UILabel(class UILabel * const this /* r31 */) {
    // References
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndText;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__7UILabel;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x803CA714 -> 0x803CA850
void * UILabel::~UILabel(class UILabel * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__7UILabel;
}

// Range: 0x803CA850 -> 0x803CA8C8
void UILabel::Init() {
    // References
    // -> class Symbol name;
    // -> class UIManager TheUI;
}

// Range: 0x803CA8C8 -> 0x803CA97C
void UILabel::Copy(class UILabel * const this /* r29 */, const class Object * o /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class UILabel * f; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UILabel;
}

// Range: 0x803CA97C -> 0x803CAAE4
void UILabel::CopyMembers(class UILabel * const this /* r30 */, const class UIComponent * c /* r31 */) {
    // Local variables
    const class UILabel * l; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> struct [anonymous] __RTTI__7UILabel;
}

static int REV; // size: 0x4, address: 0x80A46F10
// Range: 0x803CAAE4 -> 0x803CAB28
void UILabel::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803CAB28 -> 0x803CAB84
void UILabel::Load(class UILabel * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803CAB84 -> 0x803CAEEC
void UILabel::PreLoad(class UILabel * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x14

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x803CAEEC -> 0x803CAF44
void UILabel::Print(class UILabel * const this /* r4 */) {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803CAF44 -> 0x803CB0A8
void UILabel::PostLoad(class UILabel * const this /* r29 */) {
    // References
    // -> unsigned char sVerboseNotify;
    // -> class Debug TheDebug;
    // -> class UIManager TheUI;
}

static class Symbol text; // size: 0x4, address: 0x80A518B0
// Range: 0x803CB0A8 -> 0x803CB230
void UILabel::DrawShowing(class UILabel * const this /* r31 */) {
    // Local variables
    class RndFont * state_font; // r0

    // References
    // -> unsigned char sDebugHighlight;
    // -> class Debug TheDebug;
    // -> unsigned char sVerboseNotify;
    // -> static class Symbol text;
}

// Range: 0x803CB230 -> 0x803CB418
void UILabel::Highlight(class UILabel * const this /* r31 */) {
    // Local variables
    class Vector3 min; // r1+0x30
    class Vector3 max; // r1+0x20
    class Box box; // r1+0x40
    class Color c; // r1+0x10

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x803CB418 -> 0x803CB45C
class RndDrawable * UILabel::CollideShowing(class UILabel * const this /* r31 */) {}

// Range: 0x803CB45C -> 0x803CB470
int UILabel::CollidePlane() {}

// Range: 0x803CB470 -> 0x803CB4CC
class Symbol UILabel::TextToken() {
    // Local variables
    char editor_text[1024]; // r1+0x10

    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x803CB4CC -> 0x803CB4D4
class RndText * UILabel::TextObj() {}

// Range: 0x803CB4D4 -> 0x803CB5A8
void UILabel::SetTextToken(class UILabel * const this /* r31 */) {
    // Local variables
    char buf[1024]; // r1+0x10

    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x803CB5A8 -> 0x803CB5EC
void UILabel::SetLocalized(class UILabel * const this /* r31 */) {}

static class Symbol size_range; // size: 0x4, address: 0x80A518B8
static class Symbol text; // size: 0x4, address: 0x80A518C0
// Range: 0x803CB5EC -> 0x803CC044
unsigned char UILabel::CheckValid(class UILabel * const this /* r29 */, unsigned char notify /* r30 */) {
    // Local variables
    float width; // r1+0x90
    float height; // r1+0x8C
    class vector lines; // r1+0xA0
    float textSize; // f1
    class Vector2 textSizeRange; // r1+0x98
    class DataArray * rangeArray; // r27
    class RndText * resourceText; // r0
    float lineHeight; // f0
    float textWidth; // f2
    int i; // r6
    float w; // f0

    // References
    // -> static class Symbol text;
    // -> const char * gNullStr;
    // -> static class Symbol size_range;
    // -> unsigned char sVerboseNotify;
    // -> unsigned char sDebugHighlight;
    // -> class Debug TheDebug;
}

static class Symbol text; // size: 0x4, address: 0x80A518C8
// Range: 0x803CC044 -> 0x803CC288
void UILabel::LabelUpdate(class UILabel * const this /* r26 */, unsigned char forceUpdateText /* r27 */) {
    // Local variables
    class RndText * t; // r29
    class RndFont * font; // r28
    float font_kerning; // f31
    unsigned char textChanged; // r1+0x10

    // References
    // -> class LoadMgr TheLoadMgr;
    // -> static class Symbol text;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803CC288 -> 0x803CC2C0
void UILabel::Validate() {
    // References
    // -> unsigned char sVerboseNotify;
}

// Range: 0x803CC2C0 -> 0x803CC468
void UILabel::AdjustHeight(class UILabel * const this /* r31 */, unsigned char useReserveLines /* r29 */) {
    // Local variables
    float w; // r1+0x1C
    class vector lines; // r1+0x20
}

static class Message localize_fail; // size: 0x8, address: 0x8097E250
// Range: 0x803CC468 -> 0x803CC7F8
void UILabel::CheckLocale(class UILabel * const this /* r30 */) {
    // References
    // -> static class Message localize_fail;
    // -> struct [anonymous] __vt__7Message;
    // -> const char * kNotObjectMsg;
    // -> class ObjectDir * sMainDir;
    // -> const char * gNullStr;
    // -> class Locale TheLocale;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x803CC7F8 -> 0x803CC80C
void UILabel::SetAlignment() {}

// Range: 0x803CC80C -> 0x803CC820
void UILabel::SetCapsMode() {}

// Range: 0x803CC820 -> 0x803CC834
void UILabel::SetFitType() {}

// Range: 0x803CC834 -> 0x803CCE4C
void UILabel::FitText(class UILabel * const this /* r28 */, unsigned char * update /* r29 */) {
    // Local variables
    float width; // f0
    class Transform xfm; // r1+0x90
    float scaleWidth; // f31
    float top; // r1+0x4C
    float bottom; // r1+0x48
    float height; // f0
    float scaleHeight; // f5
    class Vector3 v; // r1+0x80
    float size; // f31
    float width; // r1+0x44
    float height; // r1+0x40
    class vector lines; // r1+0x74
    float fontAspectRatio; // f0
    class String trunc_str; // r1+0x68
    class String str; // r1+0x5C
    int len; // r30
    float width; // r1+0x3C
    float height; // r1+0x38
    class vector lines; // r1+0x50
    unsigned int pos; // r0
    int trunc_len; // r0
    int i; // r26
    int i; // r26
}

static class Symbol _s; // size: 0x4, address: 0x80A518D0
static class Symbol _s; // size: 0x4, address: 0x80A518D8
static class Symbol _s; // size: 0x4, address: 0x80A518E0
static class Symbol _s; // size: 0x4, address: 0x80A518E8
static class Symbol _s; // size: 0x4, address: 0x80A518F0
// Range: 0x803CCE4C -> 0x803CD5A8
class DataNode UILabel::Handle(class UILabel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A518F8
static class Symbol _s; // size: 0x4, address: 0x80A51900
static class Symbol _s; // size: 0x4, address: 0x80A51908
static class Symbol _s; // size: 0x4, address: 0x80A51910
static class Symbol _s; // size: 0x4, address: 0x80A51918
static class Symbol _s; // size: 0x4, address: 0x80A51920
static class Symbol _s; // size: 0x4, address: 0x80A51928
static class Symbol _s; // size: 0x4, address: 0x80A51930
static class Symbol _s; // size: 0x4, address: 0x80A51938
static class Symbol _s; // size: 0x4, address: 0x80A51940
static class Symbol _s; // size: 0x4, address: 0x80A51948
static class Symbol _s; // size: 0x4, address: 0x80A51950
static class Symbol _s; // size: 0x4, address: 0x80A51958
static class Symbol _s; // size: 0x4, address: 0x80A51960
static class Symbol _s; // size: 0x4, address: 0x80A51968
static class Symbol _s; // size: 0x4, address: 0x80A51970
static class Symbol _s; // size: 0x4, address: 0x80A51978
static class Symbol _s; // size: 0x4, address: 0x80A51980
static class Symbol _s; // size: 0x4, address: 0x80A51988
static class Symbol _s; // size: 0x4, address: 0x80A51990
// Range: 0x803CD5A8 -> 0x803CE950
unsigned char UILabel::SyncProperty(class UILabel * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x154
} __vt__7UILabel; // size: 0x154, address: 0x808E2288
class Locale {
    // total size: 0x18
protected:
    int mSize; // offset 0x0, size 0x4
    class Symbol * mSymTable; // offset 0x4, size 0x4
    const char * * mStrTable; // offset 0x8, size 0x4
    class StringTable * mStringData; // offset 0xC, size 0x4
    class Symbol mFile; // offset 0x10, size 0x4
    int mNumFilesLoaded; // offset 0x14, size 0x4
};

