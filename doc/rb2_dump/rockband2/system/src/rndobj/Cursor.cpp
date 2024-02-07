/*
    Compile unit: C:\rockband2\system\src\rndobj\Cursor.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8047C248 -> 0x8047DB38
*/
class DataArray * types; // size: 0x4, address: 0x80A52AB0
class Symbol name; // size: 0x4, address: 0x80A52AB8
class RndCursor : public RndAnimatable, public RndDrawable {
    // total size: 0xB0
protected:
    class ObjOwnerPtr mText; // offset 0x44, size 0xC
    class ObjOwnerPtr mBlur; // offset 0x50, size 0xC
    class RndBlur * mCursor; // offset 0x5C, size 0x4
    class RndMesh * mMask; // offset 0x60, size 0x4
    float mYOffset; // offset 0x64, size 0x4
    float mStutter; // offset 0x68, size 0x4
    float mTextLen; // offset 0x6C, size 0x4
    class Vector2 mCursorOffset; // offset 0x70, size 0x8
};
// Range: 0x8047C248 -> 0x8047C384
void RndCursor::Copy(class RndCursor * const this /* r29 */, const class Object * o /* r31 */, enum CopyType type /* r30 */) {
    // Local variables
    const class RndCursor * f; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9RndCursor;
}

static int CURSOR_REV; // size: 0x4, address: 0x80A47164
// Range: 0x8047C384 -> 0x8047C3C8
void RndCursor::Save() {
    // References
    // -> class Debug TheDebug;
}

static int gRev; // size: 0x4, address: 0x80A52ABC
// Range: 0x8047C3C8 -> 0x8047C4F4
void RndCursor::Load(class RndCursor * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class Debug TheDebug;
    // -> static int CURSOR_REV;
    // -> static int gRev;
}

// Range: 0x8047C4F4 -> 0x8047C6A0
void RndCursor::RecreateCursor(class RndCursor * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndBlur;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8047C6A0 -> 0x8047D06C
void RndCursor::RecreateMask(class RndCursor * const this /* r31 */) {
    // Local variables
    class Vector3 ul; // r1+0x40
    class Vector3 br; // r1+0x30
    enum Alignment a; // r0
    float size; // f0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8047D06C -> 0x8047D1B0
void RndCursor::Replace(class RndCursor * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__7RndBlur;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndText;
}

// Range: 0x8047D1B0 -> 0x8047D224
float RndCursor::StutterFrame(class RndCursor * const this /* r31 */) {
    // Local variables
    float frame; // f0
    float baseFrame; // f0
}

// Range: 0x8047D224 -> 0x8047D2B4
float RndCursor::EndFrame(class RndCursor * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8047D2B4 -> 0x8047D60C
void RndCursor::DrawShowing(class RndCursor * const this /* r30 */) {
    // Local variables
    int tl; // r0
    float x; // f0
    float ff; // f0
    class Transform t; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x8047D60C -> 0x8047D758
void RndCursor::ListDrawChildren(class RndCursor * const this /* r31 */, class list & l /* r29 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std26_List_node<P11RndDrawable>;
    // -> unsigned char gStlAllocNameLookup;
}

// Range: 0x8047D758 -> 0x8047D920
void * RndCursor::~RndCursor(class RndCursor * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndText,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndBlur,9ObjectDir>;
    // -> struct [anonymous] __vt__9RndCursor;
}

class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndBlur * mPtr; // offset 0x8, size 0x4
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class RndText * mPtr; // offset 0x8, size 0x4
};
// Range: 0x8047D920 -> 0x8047DA90
void * RndCursor::RndCursor(class RndCursor * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndBlur,9ObjectDir>;
    // -> struct [anonymous] __vt__32ObjOwnerPtr<7RndText,9ObjectDir>;
    // -> struct [anonymous] __vt__9RndCursor;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8047DA90 -> 0x8047DB38
unsigned char RndCursor::SyncProperty(class RndCursor * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {}

struct {
    // total size: 0x114
} __vt__9RndCursor; // size: 0x114, address: 0x808F3748
struct {
    // total size: 0x8
} __RTTI__9RndCursor; // size: 0x8, address: 0x808F3898
struct {
    // total size: 0x18
} __vt__32ObjOwnerPtr<7RndBlur,9ObjectDir>; // size: 0x18, address: 0x808F38A0
struct {
    // total size: 0x8
} __RTTI__32ObjOwnerPtr<7RndBlur,9ObjectDir>; // size: 0x8, address: 0x808F38E8
struct {
    // total size: 0x18
} __vt__32ObjOwnerPtr<7RndText,9ObjectDir>; // size: 0x18, address: 0x808F38F0
struct {
    // total size: 0x8
} __RTTI__32ObjOwnerPtr<7RndText,9ObjectDir>; // size: 0x8, address: 0x808F3938

