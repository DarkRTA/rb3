/*
    Compile unit: C:\rockband2\system\src\rndobj\DeferDraw.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8047E94C -> 0x8047FF90
*/
class DataArray * types; // size: 0x4, address: 0x80A52AC0
class Symbol name; // size: 0x4, address: 0x80A52AC8
class RndDeferDraw : public RndDrawable {
    // total size: 0x90
protected:
    class String mDrawName; // offset 0x34, size 0xC
    class ObjPtrList mObjects; // offset 0x40, size 0x14
};
// Range: 0x8047E94C -> 0x8047EA58
void * RndDeferDraw::RndDeferDraw(class RndDeferDraw * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__33ObjPtrList<9ObjectDir,9ObjectDir>;
    // -> struct [anonymous] __vt__12RndDeferDraw;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

struct Node {
    // total size: 0xC
    class ObjectDir * object; // offset 0x0, size 0x4
    struct Node * next; // offset 0x4, size 0x4
    struct Node * prev; // offset 0x8, size 0x4
};
class ObjPtrList : public ObjRef {
    // total size: 0x14
    int mSize; // offset 0x4, size 0x4
    struct Node * mNodes; // offset 0x8, size 0x4
    class Object * mOwner; // offset 0xC, size 0x4
    enum ObjListMode mMode; // offset 0x10, size 0x4
};
// Range: 0x8047EA58 -> 0x8047ECCC
void * RndDeferDraw::~RndDeferDraw(class RndDeferDraw * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__33ObjPtrList<9ObjectDir,9ObjectDir>;
    // -> struct [anonymous] __vt__12RndDeferDraw;
}

static int REV; // size: 0x4, address: 0x80A47170
// Range: 0x8047ECCC -> 0x8047ED10
void RndDeferDraw::Save() {
    // References
    // -> class Debug TheDebug;
}

class iterator {
    // total size: 0x4
    struct Node * mNode; // offset 0x0, size 0x4
};
// Range: 0x8047ED10 -> 0x8047EDB8
void RndDeferDraw::SetShowings(class RndDeferDraw * const this /* r30 */, unsigned char b /* r31 */) {
    // Local variables
    class iterator it; // r1+0x18

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
}

// Range: 0x8047EDB8 -> 0x8047EEB4
void RndDeferDraw::Load(class RndDeferDraw * const this /* r29 */, class BinStream & d /* r30 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> class Debug TheDebug;
    // -> static int REV;
}

// Range: 0x8047EEB4 -> 0x8047F240
void RndDeferDraw::Copy(class RndDeferDraw * const this /* r29 */, const class Object * o /* r28 */, enum CopyType type /* r27 */) {
    // Local variables
    const class RndDeferDraw * v; // r0

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__12RndDeferDraw;
}

// Range: 0x8047F240 -> 0x8047F3CC
void RndDeferDraw::DrawShowing(class RndDeferDraw * const this /* r31 */) {
    // Local variables
    class iterator it; // r1+0x18
    class RndDir * r; // r0
    class RndEnvironTracker _rndEnvironTracker; // r1+0x20

    // References
    // -> const class Vector3 * sCurrentPos;
    // -> class RndEnviron * sCurrent;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__11RndDrawable;
}

// Range: 0x8047F3CC -> 0x8047F7C4
class DataNode RndDeferDraw::Handle(class RndDeferDraw * const this /* r30 */, class DataArray * _msg /* r27 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x24
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30
    class DataNode _n; // r1+0x28

    // References
    // -> class Debug TheDebug;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A52AD0
static class Symbol _s; // size: 0x4, address: 0x80A52AD8
// Range: 0x8047F7C4 -> 0x8047F8EC
unsigned char RndDeferDraw::SyncProperty(class RndDeferDraw * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
    // -> static class Symbol _s;
}

// Range: 0x8047F8EC -> 0x8047FF90
unsigned char PropSync(class ObjPtrList & l /* r26 */, class DataNode & n /* r27 */, class DataArray * prop /* r28 */, int i /* r29 */, enum PropOp op /* r30 */) {
    // Local variables
    class iterator it; // r1+0x1C
    int which; // r3
    class ObjectDir * obj; // r31
    class ObjectDir * obj; // r31

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0xB8
} __vt__12RndDeferDraw; // size: 0xB8, address: 0x808F3E28
struct {
    // total size: 0x8
} __RTTI__12RndDeferDraw; // size: 0x8, address: 0x808F3F18
struct {
    // total size: 0x18
} __vt__33ObjPtrList<9ObjectDir,9ObjectDir>; // size: 0x18, address: 0x808F3F20
struct {
    // total size: 0x8
} __RTTI__33ObjPtrList<9ObjectDir,9ObjectDir>; // size: 0x8, address: 0x808F3F68

