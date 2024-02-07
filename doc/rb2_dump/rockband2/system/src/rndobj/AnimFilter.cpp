/*
    Compile unit: C:\rockband2\system\src\rndobj\AnimFilter.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8046CF8C -> 0x8046EB18
*/
class DataArray * types; // size: 0x4, address: 0x80A52960
class Symbol name; // size: 0x4, address: 0x80A52968
enum Type {
    kRange = 0,
    kLoop = 1,
    kShuttle = 2,
};
class RndAnimFilter : public RndAnimatable {
    // total size: 0x6C
protected:
    class ObjPtr mAnim; // offset 0x10, size 0xC
    float mPeriod; // offset 0x1C, size 0x4
    float mStart; // offset 0x20, size 0x4
    float mEnd; // offset 0x24, size 0x4
    float mScale; // offset 0x28, size 0x4
    float mOffset; // offset 0x2C, size 0x4
    float mSnap; // offset 0x30, size 0x4
    float mJitter; // offset 0x34, size 0x4
    float mJitterFrame; // offset 0x38, size 0x4
    enum Type mType; // offset 0x3C, size 0x4
};
// Range: 0x8046CF8C -> 0x8046D038
void RndAnimFilter::SetAnim(class RndAnimFilter * const this /* r30 */, class RndAnimatable * a /* r31 */) {}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndAnimatable * _M_data; // offset 0x8, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x8046D038 -> 0x8046D0B4
void RndAnimFilter::ListAnimChildren() {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<P13RndAnimatable>;
    // -> unsigned char gStlAllocNameLookup;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<P13RndAnimatable>; // size: 0x8, address: 0x808F16C0
// Range: 0x8046D0B4 -> 0x8046D1BC
void RndAnimFilter::Copy(class RndAnimFilter * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndAnimFilter * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndAnimFilter;
}

static int ANIMFILTER_REV; // size: 0x4, address: 0x80A470E8
// Range: 0x8046D1BC -> 0x8046D200
void RndAnimFilter::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A5296C
// Range: 0x8046D200 -> 0x8046D39C
void RndAnimFilter::Load(class RndAnimFilter * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int ANIMFILTER_REV;
    // -> static int gRev;
}

// Range: 0x8046D39C -> 0x8046D418
float RndAnimFilter::Scale(class RndAnimFilter * const this /* r31 */) {}

// Range: 0x8046D418 -> 0x8046D444
float RndAnimFilter::FrameOffset() {}

// Range: 0x8046D444 -> 0x8046D670
void RndAnimFilter::SetFrame(class RndAnimFilter * const this /* r31 */, float frame /* f28 */, float blend /* f31 */) {
    // Local variables
    int i; // r0
    float min; // f29
    float max; // f30
    int n; // r4
}

// Range: 0x8046D670 -> 0x8046D6E8
float RndAnimFilter::StartFrame(class RndAnimFilter * const this /* r31 */) {
    // Local variables
    float scale; // f31
}

// Range: 0x8046D6E8 -> 0x8046D774
float RndAnimFilter::EndFrame(class RndAnimFilter * const this /* r31 */) {
    // Local variables
    float scale; // f31
    float end; // f1
}

// Range: 0x8046D774 -> 0x8046D850
void * RndAnimFilter::RndAnimFilter(class RndAnimFilter * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__34ObjPtr<13RndAnimatable,9ObjectDir>;
    // -> struct [anonymous] __vt__13RndAnimFilter;
}

static class Symbol _s; // size: 0x4, address: 0x80A52974
// Range: 0x8046D850 -> 0x8046DD94
class DataNode RndAnimFilter::Handle(class RndAnimFilter * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

class ObjDirItr {
    // total size: 0x14
    class ObjectDir * mDir; // offset 0x0, size 0x4
    class ObjectDir * mSubDir; // offset 0x4, size 0x4
    struct Entry * mEntry; // offset 0x8, size 0x4
    class RndAnimatable * mObj; // offset 0xC, size 0x4
    int mWhich; // offset 0x10, size 0x4
};
// Range: 0x8046DD94 -> 0x8046E270
class DataNode RndAnimFilter::OnSafeAnims(class RndAnimFilter * const this /* r30 */, class DataArray * a /* r28 */) {
    // Local variables
    int idx; // r31
    class DataArrayPtr da; // r1+0x28
    class ObjDirItr ai; // r1+0x30

    // References
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> struct [anonymous] __vt__12DataArrayPtr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
}

static class Symbol _s; // size: 0x4, address: 0x80A5297C
static class Symbol _s; // size: 0x4, address: 0x80A52984
static class Symbol _s; // size: 0x4, address: 0x80A5298C
static class Symbol _s; // size: 0x4, address: 0x80A52994
static class Symbol _s; // size: 0x4, address: 0x80A5299C
static class Symbol _s; // size: 0x4, address: 0x80A529A4
static class Symbol _s; // size: 0x4, address: 0x80A529AC
static class Symbol _s; // size: 0x4, address: 0x80A529B4
static class Symbol _s; // size: 0x4, address: 0x80A529BC
// Range: 0x8046E270 -> 0x8046EB18
unsigned char RndAnimFilter::SyncProperty(class RndAnimFilter * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
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
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__13RndAnimatable;
    // -> static class Symbol _s;
}

struct {
    // total size: 0xA0
} __vt__13RndAnimFilter; // size: 0xA0, address: 0x808F1770
struct {
    // total size: 0x8
} __RTTI__13RndAnimFilter; // size: 0x8, address: 0x808F1840

