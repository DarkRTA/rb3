/*
    Compile unit: C:\rockband2\system\src\bandobj\Label3d.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80282EE0 -> 0x80285C38
*/
class Symbol name; // size: 0x4, address: 0x80A4F7E4
class DataArray * types; // size: 0x4, address: 0x80A4F7E8
// Range: 0x80282EE0 -> 0x8028311C
void * Label3d::Label3d(class Label3d * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__31ObjPtrList<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__7Label3d;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x8028311C -> 0x8028374C
void * Label3d::~Label3d(class Label3d * const this /* r28 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
    // -> struct [anonymous] __vt__21ObjDirPtr<9ObjectDir>;
    // -> struct [anonymous] __vt__31ObjPtrList<7RndMesh,9ObjectDir>;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__7Label3d;
}

static int gRev; // size: 0x4, address: 0x80A4F7F0
// Range: 0x8028374C -> 0x80283790
void Label3d::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x80283790 -> 0x802837EC
void Label3d::Load(class Label3d * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x802837EC -> 0x80283D00
void Label3d::PreLoad(class Label3d * const this /* r31 */, class BinStream & d /* r29 */) {
    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class LoadMgr TheLoadMgr;
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x80283D00 -> 0x80283E6C
void Label3d::PostLoad(class Label3d * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80283E6C -> 0x80283ECC
void Label3d::DrawShowing() {}

// Range: 0x80283ECC -> 0x80283F2C
void Label3d::Highlight() {}

// Range: 0x80283F2C -> 0x80284318
void Label3d::UpdateResource(class Label3d * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x80284318 -> 0x8028431C
void Label3d::UpdateSphere() {}

// Range: 0x8028431C -> 0x802843CC
unsigned char Label3d::MakeWorldSphere(class Label3d * const this /* r30 */, class Sphere & s /* r31 */) {}

// Range: 0x802843CC -> 0x80284550
void Label3d::FindBounds(float & leftmost /* r28 */, float & rightmost /* r29 */, class RndMesh * mesh /* r30 */) {
    // Local variables
    int i; // r31

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80284550 -> 0x80285144
void Label3d::UpdateText(class Label3d * const this /* r25 */) {
    // Local variables
    class String localized; // r1+0x90
    class Transform t; // r1+0x100
    float length; // f31
    int i; // r28
    unsigned int nChar; // r26
    class Object * pObj; // r0
    class RndMesh * pRmLetter; // r27
    class RndMesh * pRmBounds; // r26
    struct _List_iterator it; // r1+0x5C
    float leftmost; // r1+0x58
    float rightmost; // r1+0x54
    class Vector3 v; // r1+0x80
    class Object * pObj; // r0
    class RndMesh * pRmSpace; // r6
    float leftmost; // r1+0x50
    float rightmost; // r1+0x4C
    float offset; // f30
    class Vector3 v; // r1+0x70
    class Transform t; // r1+0xC0
    class Sphere s; // r1+0xA0

    // References
    // -> class Symbol name;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7RndMesh;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80285144 -> 0x80285664
class DataNode Label3d::Handle(class Label3d * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
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

static class Symbol _s; // size: 0x4, address: 0x80A4F7F8
static class Symbol _s; // size: 0x4, address: 0x80A4F800
static class Symbol _s; // size: 0x4, address: 0x80A4F808
static class Symbol _s; // size: 0x4, address: 0x80A4F810
static class Symbol _s; // size: 0x4, address: 0x80A4F818
static class Symbol _s; // size: 0x4, address: 0x80A4F820
// Range: 0x80285664 -> 0x80285C38
unsigned char Label3d::SyncProperty(class Label3d * const this /* r26 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
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

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class RndTransformable * _M_data; // offset 0x8, size 0x4
};
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x104
} __vt__7Label3d; // size: 0x104, address: 0x808BC168
struct {
    // total size: 0x8
} __RTTI__7Label3d; // size: 0x8, address: 0x808BC2C0

