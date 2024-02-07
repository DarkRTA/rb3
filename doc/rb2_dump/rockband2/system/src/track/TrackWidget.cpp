/*
    Compile unit: C:\rockband2\system\src\track\TrackWidget.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803C54F8 -> 0x803C6C68
*/
class DataArray * types; // size: 0x4, address: 0x80A51820
// Range: 0x803C54F8 -> 0x803C568C
void * TrackWidget::TrackWidget(class TrackWidget * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtrList<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__11TrackWidget;
    // -> struct [anonymous] __vt__11RndPollable;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x803C568C -> 0x803C5958
void * TrackWidget::~TrackWidget(class TrackWidget * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__31ObjPtrList<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__11TrackWidget;
}

class TrackWidgetImp {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
// Range: 0x803C5958 -> 0x803C59E8
void TrackWidget::DrawShowing(class TrackWidget * const this /* r31 */) {
    // References
    // -> class RndEnviron * sCurrent;
}

// Range: 0x803C59E8 -> 0x803C5A58
void TrackWidget::Enter(class TrackWidget * const this /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__8TrackDir;
}

// Range: 0x803C5A58 -> 0x803C5B60
void TrackWidget::Poll(class TrackWidget * const this /* r30 */) {
    // Local variables
    class list & instances; // r31
    float cutOffY; // f31
    struct _List_iterator inst; // r1+0x2C
}

// Range: 0x803C5B60 -> 0x803C5B74
class list & TrackWidget::Instances() {}

static class DebugWarner _dw; // size: 0x100, address: 0x8097E140
// Range: 0x803C5B74 -> 0x803C5D70
void TrackWidget::AddInstance(class TrackWidget * const this /* r28 */, const class Transform & xfm /* r31 */, float duration /* f31 */) {
    // Local variables
    class list & instances; // r29

    // References
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
}

struct InstanceCmp {
    // total size: 0x1
};
// Range: 0x803C5D98 -> 0x803C5EF4
void TrackWidget::RemoveAt(class TrackWidget * const this /* r30 */, float seconds /* f31 */) {
    // Local variables
    class list & instances; // r31
    float y; // f0
    struct _List_iterator from; // r1+0x38
    struct _List_iterator to; // r1+0x34
}

// Range: 0x803C5EF4 -> 0x803C603C
void TrackWidget::RemoveAt(class TrackWidget * const this /* r29 */, float seconds /* f30 */, int slot /* r30 */) {
    // Local variables
    class list & instances; // r0
    float y; // f0
    float x; // f30
    struct _List_iterator end; // r1+0x1C
    struct _List_iterator it; // r1+0x18
}

// Range: 0x803C603C -> 0x803C6070
void TrackWidget::Clear() {}

// Range: 0x803C6070 -> 0x803C61C4
void TrackWidget::Mats(class TrackWidget * const this /* r29 */, class list & mats /* r30 */) {
    // Local variables
    class iterator it; // r1+0x20
    struct MatShaderOptions opts; // r1+0x1C

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std20_List_node<P6RndMat>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x803C61C4 -> 0x803C61F0
unsigned char TrackWidget::Prunable() {}

// Range: 0x803C61F0 -> 0x803C6214
static unsigned char NearOne() {}

static class Symbol _s; // size: 0x4, address: 0x80A51828
// Range: 0x803C6214 -> 0x803C66EC
class DataNode TrackWidget::Handle(class TrackWidget * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A51830
static class Symbol _s; // size: 0x4, address: 0x80A51838
static class Symbol _s; // size: 0x4, address: 0x80A51840
static class Symbol _s; // size: 0x4, address: 0x80A51848
static class Symbol _s; // size: 0x4, address: 0x80A51850
static class Symbol _s; // size: 0x4, address: 0x80A51858
// Range: 0x803C66EC -> 0x803C6C68
unsigned char TrackWidget::SyncProperty(class TrackWidget * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x14
} __vt__14TrackWidgetImp; // size: 0x14, address: 0x808E1230
struct {
    // total size: 0x8
} __RTTI__14TrackWidgetImp; // size: 0x8, address: 0x808E1258
struct {
    // total size: 0xE8
} __vt__11TrackWidget; // size: 0xE8, address: 0x808E1260

