/*
    Compile unit: C:\rockband2\system\src\rndobj\TransArray.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80516FE8 -> 0x8051A41C
*/
class DataArray * types; // size: 0x4, address: 0x80A53BA0
// Range: 0x80516FE8 -> 0x80517220
void * RndTransArray::RndTransArray(class RndTransArray * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__33ObjPtr<12RndTransAnim,9ObjectDir>;
    // -> struct [anonymous] __vt__9TnmLayout;
    // -> struct [anonymous] __vt__10RingLayout;
    // -> struct [anonymous] __vt__10GridLayout;
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__13RndTransArray;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

class TransLayout {
    // total size: 0x4
public:
    void * __vptr$; // offset 0x0, size 0x4
};
// Range: 0x80517220 -> 0x80517260
void * TransLayout::~TransLayout(class TransLayout * const this /* r31 */) {}

// Range: 0x80517260 -> 0x80517528
void * RndTransArray::~RndTransArray(class RndTransArray * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__41ObjPtrList<16RndTransformable,9ObjectDir>;
    // -> struct [anonymous] __vt__13RndTransArray;
}

static int REV; // size: 0x4, address: 0x80A53BA8
// Range: 0x80517910 -> 0x80517954
void RndTransArray::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80517954 -> 0x80517B74
void RndTransArray::Load(class RndTransArray * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0x10

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x80517B74 -> 0x80517B7C
void RndTransArray::SetFrame() {}

// Range: 0x80517B7C -> 0x80517BA0
float RndTransArray::EndFrame() {}

// Range: 0x80517BA0 -> 0x80517C08
void RndTransArray::UpdateLayout(class RndTransArray * const this /* r31 */) {}

// Range: 0x80517C08 -> 0x80517D6C
void TransLayout::Update(class TransLayout * const this /* r28 */, const class Transform & parentXfm /* r29 */, class ObjPtrList & targets /* r27 */) {
    // Local variables
    class Transform targetLocalXfm; // r1+0x70
    class Transform targetWorldXfm; // r1+0x30
    int num; // r31
    int index; // r30
    class iterator it; // r1+0x20
}

// Range: 0x80517D6C -> 0x80518280
class DataNode RndTransArray::Handle(class RndTransArray * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A53BB0
static class Symbol _s; // size: 0x4, address: 0x80A53BB8
static class Symbol _s; // size: 0x4, address: 0x80A53BC0
static class Symbol _s; // size: 0x4, address: 0x80A53BC8
static class Symbol _s; // size: 0x4, address: 0x80A53BD0
static class Symbol _s; // size: 0x4, address: 0x80A53BD8
static class Symbol _s; // size: 0x4, address: 0x80A53BE0
static class Symbol _s; // size: 0x4, address: 0x80A53BE8
static class Symbol _s; // size: 0x4, address: 0x80A53BF0
static class Symbol _s; // size: 0x4, address: 0x80A53BF8
static class Symbol _s; // size: 0x4, address: 0x80A53C00
static class Symbol _s; // size: 0x4, address: 0x80A53C08
static class Symbol _s; // size: 0x4, address: 0x80A53C10
static class Symbol _s; // size: 0x4, address: 0x80A53C18
static class Symbol _s; // size: 0x4, address: 0x80A53C20
static class Symbol _s; // size: 0x4, address: 0x80A53C28
static class Symbol _s; // size: 0x4, address: 0x80A53C30
static class Symbol _s; // size: 0x4, address: 0x80A53C38
// Range: 0x80518280 -> 0x80518F8C
unsigned char RndTransArray::SyncProperty(class RndTransArray * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x80518F8C -> 0x805191C0
unsigned char PropSync(class Keys & v /* r31 */, class DataNode & n /* r26 */, class DataArray * prop /* r27 */, int i /* r28 */, enum PropOp op /* r29 */) {
    // Local variables
    class Key * it; // r30
    unsigned char ret; // r30
    class Key tmp; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct _OKToSwap {
    // total size: 0x1
};
class Symbol frame; // size: 0x4, address: 0x80A53C40
class Symbol value; // size: 0x4, address: 0x80A53C48
class TnmLayout : public TransLayout {
    // total size: 0x28
public:
    class ObjPtr mTnm; // offset 0x4, size 0xC
    float mStart; // offset 0x10, size 0x4
    float mEnd; // offset 0x14, size 0x4
    float mOffset; // offset 0x18, size 0x4
    class Keys mOffsetKeys; // offset 0x1C, size 0xC
};
// Range: 0x805191C0 -> 0x805191E8
float TnmLayout::EndFrame() {}

// Range: 0x805191E8 -> 0x80519458
void TnmLayout::SetFrame(class TnmLayout * const this /* r25 */, float frame /* f30 */) {}

// Range: 0x80519458 -> 0x80519520
void TnmLayout::MakeTransform() {
    // Local variables
    float frame; // f1
}

struct {
    // total size: 0x1C
} __vt__9TnmLayout; // size: 0x1C, address: 0x80903BE4
struct {
    // total size: 0x8
} __RTTI__9TnmLayout; // size: 0x8, address: 0x80903C18
class RingLayout : public TransLayout {
    // total size: 0x18
public:
    float mRadius; // offset 0x4, size 0x4
    unsigned char mRotate; // offset 0x8, size 0x1
    unsigned char mInvertOrder; // offset 0x9, size 0x1
    class Keys mRadiusKeys; // offset 0xC, size 0xC
};
// Range: 0x80519520 -> 0x80519548
float RingLayout::EndFrame() {}

// Range: 0x80519548 -> 0x805197B8
void RingLayout::SetFrame(class RingLayout * const this /* r25 */, float frame /* f30 */) {}

// Range: 0x805197B8 -> 0x80519924
void RingLayout::MakeTransform(class RingLayout * const this /* r30 */, class Transform & xfm /* r31 */) {
    // Local variables
    float angle; // f30
}

struct {
    // total size: 0x1C
} __vt__10RingLayout; // size: 0x1C, address: 0x80903C70
struct {
    // total size: 0x8
} __RTTI__10RingLayout; // size: 0x8, address: 0x80903CA8
class GridLayout : public TransLayout {
    // total size: 0x44
public:
    int mRows; // offset 0x4, size 0x4
    int mCols; // offset 0x8, size 0x4
    float mRowSpacing; // offset 0xC, size 0x4
    float mColSpacing; // offset 0x10, size 0x4
    class Keys mRowKeys; // offset 0x14, size 0xC
    class Keys mColKeys; // offset 0x20, size 0xC
    class Keys mRowSpacingKeys; // offset 0x2C, size 0xC
    class Keys mColSpacingKeys; // offset 0x38, size 0xC
};
// Range: 0x80519924 -> 0x80519A20
float GridLayout::EndFrame() {}

// Range: 0x80519A20 -> 0x8051A31C
void GridLayout::SetFrame(class GridLayout * const this /* r31 */, float frame /* f30 */) {}

// Range: 0x8051A31C -> 0x8051A41C
void GridLayout::MakeTransform() {
    // Local variables
    int col; // r7
    int row; // r8
}

struct {
    // total size: 0x1C
} __vt__10GridLayout; // size: 0x1C, address: 0x80903CB0
struct {
    // total size: 0x8
} __RTTI__10GridLayout; // size: 0x8, address: 0x80903CE8
struct {
    // total size: 0x1C
} __vt__11TransLayout; // size: 0x1C, address: 0x80903CF0
struct {
    // total size: 0x8
} __RTTI__11TransLayout; // size: 0x8, address: 0x80903D18
struct {
    // total size: 0xEC
} __vt__13RndTransArray; // size: 0xEC, address: 0x80903D58
struct {
    // total size: 0x8
} __RTTI__13RndTransArray; // size: 0x8, address: 0x80903E80

