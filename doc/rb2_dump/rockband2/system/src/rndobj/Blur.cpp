/*
    Compile unit: C:\rockband2\system\src\rndobj\Blur.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8047296C -> 0x80473DC8
*/
class DataArray * types; // size: 0x4, address: 0x80A529C0
class Symbol name; // size: 0x4, address: 0x80A529C8
class RndBlur : public RndDrawable {
    // total size: 0xA0
protected:
    class ObjPtr mMesh; // offset 0x34, size 0xC
    class ObjPtr mText; // offset 0x40, size 0xC
    int mLength; // offset 0x4C, size 0x4
    int mRate; // offset 0x50, size 0x4
    float mFalloff; // offset 0x54, size 0x4
    class list mKeys; // offset 0x58, size 0x8
    int mCount; // offset 0x60, size 0x4
};
// Range: 0x8047296C -> 0x80472A9C
void RndBlur::Copy(class RndBlur * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndBlur * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndBlur;
}

static int BLUR_REV; // size: 0x4, address: 0x80A47104
// Range: 0x80472A9C -> 0x80472AE0
void RndBlur::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A529CC
// Range: 0x80472AE0 -> 0x80472C2C
void RndBlur::Load(class RndBlur * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int BLUR_REV;
    // -> static int gRev;
}

// Range: 0x80472C2C -> 0x80473130
void RndBlur::DrawShowing(class RndBlur * const this /* r27 */) {
    // Local variables
    class RndMat * mat; // r30
    enum ZMode zMode; // r0
    class RndTransformable * trans; // r29
    class RndDrawable * draw; // r28
    class Transform world; // r1+0x50
    class Transform * prevXfm; // r6
    float startAlpha; // f0
    float alpha; // f30
    float step; // f29
    struct _List_iterator x; // r1+0x40

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std22_List_node<9Transform>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Rnd & TheRnd;
}

// Range: 0x80473130 -> 0x8047321C
void RndBlur::ListDrawChildren(class RndBlur * const this /* r29 */, class list & l /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8047321C -> 0x8047338C
void * RndBlur::RndBlur(class RndBlur * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndText,9ObjectDir>;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__7RndBlur;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8047338C -> 0x804733D0
void RndBlur::SetLength(int l /* r1+0x8 */) {}

// Range: 0x804733D0 -> 0x80473414
void RndBlur::SetRate(int r /* r1+0x8 */) {}

static class Symbol _s; // size: 0x4, address: 0x80A529D4
static class Symbol _s; // size: 0x4, address: 0x80A529DC
static class Symbol _s; // size: 0x4, address: 0x80A529E4
// Range: 0x80473414 -> 0x80473C0C
class DataNode RndBlur::Handle(class RndBlur * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x30
    class MessageTimer _mt; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode _n; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x80473C0C -> 0x80473C78
class DataNode RndBlur::OnSetLength(class RndBlur * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x80473C78 -> 0x80473CE4
class DataNode RndBlur::OnSetRate(class RndBlur * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x80473CE4 -> 0x80473D48
class DataNode RndBlur::OnSetFalloff(class RndBlur * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x80473D48 -> 0x80473DC8
unsigned char RndBlur::SyncProperty(class RndBlur * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0xBC
} __vt__7RndBlur; // size: 0xBC, address: 0x808F1FE4
struct {
    // total size: 0x8
} __RTTI__7RndBlur; // size: 0x8, address: 0x808F20D0

