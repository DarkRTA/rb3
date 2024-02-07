/*
    Compile unit: C:\rockband2\system\src\ui\Proxy.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803E40BC -> 0x803E60C0
*/
class DataArray * types; // size: 0x4, address: 0x80A51D38
class Symbol name; // size: 0x4, address: 0x80A51D40
// Range: 0x803E40BC -> 0x803E4240
void * UIProxy::UIProxy(class UIProxy * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__31ObjPtr<10RndEnviron,9ObjectDir>;
    // -> struct [anonymous] __vt__18ObjDirPtr<6RndDir>;
    // -> struct [anonymous] __vt__7UIProxy;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x803E4240 -> 0x803E42EC
void UIProxy::Copy(class UIProxy * const this /* r29 */, const class Object * o /* r30 */, enum CopyType type /* r31 */) {
    // Local variables
    const class UIProxy * p; // r0

    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__7UIProxy;
}

static int gRev; // size: 0x4, address: 0x80A51D44
// Range: 0x803E42EC -> 0x803E4330
void UIProxy::Save() {
    // References
    // -> class Debug TheDebug;
}

// Range: 0x803E4330 -> 0x803E438C
void UIProxy::Load(class UIProxy * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803E438C -> 0x803E44A8
void UIProxy::PreLoad(class UIProxy * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std13_List_node<i>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sRevs;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x803E44A8 -> 0x803E46A8
void UIProxy::PostLoad(class UIProxy * const this /* r30 */, class BinStream & d /* r31 */) {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
    // -> static int gRev;
    // -> class list sRevs;
}

// Range: 0x803E46A8 -> 0x803E4908
void UIProxy::Poll(class UIProxy * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x803E4908 -> 0x803E4AC4
void UIProxy::DrawShowing(class UIProxy * const this /* r28 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803E4AC4 -> 0x803E4B94
class RndDrawable * UIProxy::CollideShowing(class UIProxy * const this /* r28 */, const class Segment & s /* r29 */, float & dist /* r30 */, class Plane & plane /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803E4B94 -> 0x803E4C30
int UIProxy::CollidePlane(class UIProxy * const this /* r30 */, const class Plane & plane /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803E4C30 -> 0x803E50DC
void UIProxy::SetProxyDir(class UIProxy * const this /* r29 */, const class FilePath & path /* r30 */, unsigned char share /* r31 */) {
    // References
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__9DirLoader;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x803E50DC -> 0x803E5338
void UIProxy::SetProxyDir(class UIProxy * const this /* r31 */, class RndDir * dir /* r25 */) {
    // References
    // -> struct [anonymous] __RTTI__9ObjectDir;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class LoadMgr TheLoadMgr;
}

static class Message msg; // size: 0x8, address: 0x8097E3B0
// Range: 0x803E5338 -> 0x803E5784
void UIProxy::SyncDir(class UIProxy * const this /* r30 */) {
    // References
    // -> static class Message msg;
    // -> struct [anonymous] __vt__7Message;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x803E5784 -> 0x803E59B4
void UIProxy::UpdateDir(class UIProxy * const this /* r28 */) {
    // Local variables
    class DataArray * trans; // r29

    // References
    // -> const char * kNotObjectMsg;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__16RndTransformable;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x803E59B4 -> 0x803E5ADC
class DataNode UIProxy::OnSetProxyDir(class UIProxy * const this /* r29 */, class DataArray * a /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndDir;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
}

static class Symbol _s; // size: 0x4, address: 0x80A51D4C
static class Symbol _s; // size: 0x4, address: 0x80A51D54
// Range: 0x803E5ADC -> 0x803E5FE8
class DataNode UIProxy::Handle(class UIProxy * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A51D5C
// Range: 0x803E5FE8 -> 0x803E60C0
unsigned char UIProxy::SyncProperty(class UIProxy * const this /* r27 */, class DataNode & _val /* r28 */, class DataArray * _prop /* r29 */, int _i /* r30 */, enum PropOp _op /* r31 */) {
    // References
    // -> static class Symbol _s;
}

struct {
    // total size: 0x14C
} __vt__7UIProxy; // size: 0x14C, address: 0x808E5EE0
struct {
    // total size: 0x18
} __vt__18ObjDirPtr<6RndDir>; // size: 0x18, address: 0x808E6080
struct {
    // total size: 0x8
} __RTTI__18ObjDirPtr<6RndDir>; // size: 0x8, address: 0x808E60B8

