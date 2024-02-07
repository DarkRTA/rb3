/*
    Compile unit: C:\rockband2\system\src\bandobj\RenderDir.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8029BFAC -> 0x8029CDFC
*/
class DataArray * types; // size: 0x4, address: 0x80A4F9E0
class Symbol name; // size: 0x4, address: 0x80A4F9E8
unsigned char sValidate; // size: 0x1, address: 0x80A4F9EC
// Range: 0x8029BFAC -> 0x8029BFC4
static class DataNode OnValidateRenderDir() {
    // References
    // -> unsigned char sValidate;
}

class RenderDir : public PanelDir {
    // total size: 0x290
    class ObjPtr mPanelDir; // offset 0x24C, size 0xC
};
// Range: 0x8029BFC4 -> 0x8029C038
void RenderDir::Init() {
    // References
    // -> class Symbol name;
}

// Range: 0x8029C038 -> 0x8029C16C
void * RenderDir::RenderDir(class RenderDir * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8PanelDir,9ObjectDir>;
    // -> struct [anonymous] __vt__9RenderDir;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

class ObjPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class PanelDir * mPtr; // offset 0x8, size 0x4
};
// Range: 0x8029C16C -> 0x8029C244
void * RenderDir::~RenderDir(class RenderDir * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__28ObjPtr<8PanelDir,9ObjectDir>;
}

// Range: 0x8029C244 -> 0x8029C288
void RenderDir::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x8029C288 -> 0x8029C330
void RenderDir::PreLoad(class RenderDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // Local variables
    int rev; // r1+0xC

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
}

// Range: 0x8029C330 -> 0x8029C3E0
void RenderDir::PostLoad(class RenderDir * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> unsigned char sValidate;
    // -> class list sRevs;
}

// Range: 0x8029C3E0 -> 0x8029C47C
void RenderDir::Copy(class RenderDir * const this /* r30 */, const class Object * o /* r31 */) {
    // Local variables
    const class RenderDir * r; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__9RenderDir;
}

// Range: 0x8029C47C -> 0x8029C49C
class ObjectDir * RenderDir::DataDir() {}

// Range: 0x8029C49C -> 0x8029C4C4
class UIComponent * RenderDir::FocusComponent() {}

// Range: 0x8029C4C4 -> 0x8029C4E8
class UIComponent * RenderDir::FindComponent() {}

// Range: 0x8029C4E8 -> 0x8029C50C
void RenderDir::SetFocusComponent() {}

// Range: 0x8029C50C -> 0x8029C574
unsigned char RenderDir::Entering(class RenderDir * const this /* r31 */) {
    // Local variables
    unsigned char e; // r3
}

// Range: 0x8029C574 -> 0x8029C5DC
unsigned char RenderDir::Exiting(class RenderDir * const this /* r31 */) {
    // Local variables
    unsigned char e; // r3
}

static class Symbol _s; // size: 0x4, address: 0x80A4F9F0
static class Symbol _s; // size: 0x4, address: 0x80A4F9F8
// Range: 0x8029C5DC -> 0x8029CBC8
class DataNode RenderDir::Handle(class RenderDir * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x2C
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A4FA00
// Range: 0x8029CBC8 -> 0x8029CCA0
unsigned char RenderDir::SyncProperty(class RenderDir * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
}

// Range: 0x8029CCA0 -> 0x8029CDFC
unsigned char PropSync(class ObjPtr & p /* r29 */, class DataNode & n /* r30 */, enum PropOp op /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__8PanelDir;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

struct {
    // total size: 0x234
} __vt__9RenderDir; // size: 0x234, address: 0x808BF13C
struct {
    // total size: 0x8
} __RTTI__9RenderDir; // size: 0x8, address: 0x808BF3D8
struct {
    // total size: 0x18
} __vt__28ObjPtr<8PanelDir,9ObjectDir>; // size: 0x18, address: 0x808BF3E0
struct {
    // total size: 0x8
} __RTTI__28ObjPtr<8PanelDir,9ObjectDir>; // size: 0x8, address: 0x808BF420

