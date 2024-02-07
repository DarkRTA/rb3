/*
    Compile unit: C:\rockband2\system\src\bandobj\BandLabel.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8024F4CC -> 0x80250DC4
*/
class Symbol t; // size: 0x4, address: 0x80A4EF14
class DataArray * types; // size: 0x4, address: 0x80A4EF18
class Symbol name; // size: 0x4, address: 0x80A4EF20
// Range: 0x8024F4CC -> 0x8024F5E0
void * BandLabel::BandLabel(class BandLabel * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__9BandLabel;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8024F5E0 -> 0x8024F72C
void * BandLabel::~BandLabel(class BandLabel * const this /* r30 */) {}

// Range: 0x8024F72C -> 0x8024F730
void BandLabel::Copy() {}

// Range: 0x8024F730 -> 0x8024F7C0
void BandLabel::CopyMembers(class BandLabel * const this /* r29 */, const class UIComponent * c /* r30 */, enum CopyType t /* r31 */) {
    // Local variables
    const class BandLabel * l; // r3

    // References
    // -> struct [anonymous] __RTTI__11UIComponent;
    // -> struct [anonymous] __RTTI__9BandLabel;
}

static int LABEL_REV; // size: 0x4, address: 0x80A46A88
// Range: 0x8024F7C0 -> 0x8024F804
void BandLabel::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A4EF24
// Range: 0x8024F804 -> 0x8024F860
void BandLabel::Load(class BandLabel * const this /* r30 */, class BinStream & d /* r31 */) {}

static class Symbol custom_colors; // size: 0x4, address: 0x80A4EF2C
// Range: 0x8024F860 -> 0x8024FEDC
void BandLabel::PreLoad(class BandLabel * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    class Color color; // r1+0x60
    unsigned char all_caps; // r29
    unsigned char justified; // r0
    int fitText; // r1+0x50
    class Matrix3 m; // r1+0x70
    int seed; // r1+0x4C
    float delta_x; // r1+0x48
    float delta_z; // r1+0x44
    float delta_rot; // r1+0x40
    class Symbol style; // r1+0x3C
    float wrapWidth; // r1+0x38
    int fitText; // r1+0x34
    int seed; // r1+0x30
    float delta_x; // r1+0x2C
    float delta_z; // r1+0x28
    float delta_rot; // r1+0x24
    float wrap_width; // r1+0x20

    // References
    // -> static class Symbol custom_colors;
    // -> const char * gNullStr;
    // -> class Debug TheDebug;
    // -> static int LABEL_REV;
    // -> static int gRev;
}

class BandLabelCountDoneMsg : public Message {
    // total size: 0x8
};
// Range: 0x8024FEDC -> 0x802503DC
void BandLabel::Poll(class BandLabel * const this /* r25 */) {
    // Local variables
    float val; // f31
    float frame; // f30
    class BandLabelCountDoneMsg msg; // r1+0x38

    // References
    // -> class UIManager TheUI;
    // -> struct [anonymous] __vt__21BandLabelCountDoneMsg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Symbol t;
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x802503DC -> 0x80250450
void BandLabel::UpdateMat(class RndMat * mat /* r31 */) {
    // Local variables
    class Color c; // r1+0x10
}

// Range: 0x80250450 -> 0x80250668
void BandLabel::Count(class BandLabel * const this /* r29 */, int from /* r28 */, int to /* r30 */, float timeMs /* f31 */, const class String & formattedStr /* r31 */) {
    // Local variables
    class Key key; // r1+0x28

    // References
    // -> class TaskMgr TheTaskMgr;
}

// Range: 0x80250668 -> 0x80250760
void BandLabel::FinishCount(class BandLabel * const this /* r30 */) {}

// Range: 0x80250760 -> 0x802507E8
void BandLabel::ClearCount() {}

static class Symbol _s; // size: 0x4, address: 0x80A4EF34
static class Symbol _s; // size: 0x4, address: 0x80A4EF3C
// Range: 0x802507E8 -> 0x80250D1C
class DataNode BandLabel::Handle(class BandLabel * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80250D1C -> 0x80250DC4
unsigned char BandLabel::SyncProperty(class BandLabel * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0x16C
} __vt__9BandLabel; // size: 0x16C, address: 0x808B33E4
struct {
    // total size: 0xC
} __vt__21BandLabelCountDoneMsg; // size: 0xC, address: 0x808B35B0
struct {
    // total size: 0x8
} __RTTI__21BandLabelCountDoneMsg; // size: 0x8, address: 0x808B35E0

