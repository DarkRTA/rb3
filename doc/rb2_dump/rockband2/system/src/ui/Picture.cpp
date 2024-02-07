/*
    Compile unit: C:\rockband2\system\src\ui\Picture.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x803E2C4C -> 0x803E3B54
*/
class DataArray * types; // size: 0x4, address: 0x80A51D08
class Symbol name; // size: 0x4, address: 0x80A51D10
class UIPicture : public UIComponent {
    // total size: 0x1A0
protected:
    class ObjPtr mMesh; // offset 0x130, size 0xC
    class FilePath mTexFile; // offset 0x13C, size 0xC
    class FilePath mLoadedFile; // offset 0x148, size 0xC
    class RndTex * mTex; // offset 0x154, size 0x4
    class FileLoader * mLoader; // offset 0x158, size 0x4
    unsigned char mHookTex; // offset 0x15C, size 0x1
};
// Range: 0x803E2C4C -> 0x803E2E30
void * UIPicture::UIPicture(class UIPicture * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndTex;
    // -> class Symbol name;
    // -> struct [anonymous] __vt__8FilePath;
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__9UIPicture;
    // -> struct [anonymous] __vt__16RndHighlightable;
}

// Range: 0x803E2E30 -> 0x803E2F94
void * UIPicture::~UIPicture(class UIPicture * const this /* r30 */) {
    // References
    // -> struct [anonymous] __vt__27ObjPtr<7RndMesh,9ObjectDir>;
    // -> struct [anonymous] __vt__9UIPicture;
}

static int gRev; // size: 0x4, address: 0x80A51D14
// Range: 0x803E2F94 -> 0x803E2FF0
void UIPicture::Load(class UIPicture * const this /* r30 */, class BinStream & d /* r31 */) {}

// Range: 0x803E2FF0 -> 0x803E30F4
void UIPicture::PreLoad(class UIPicture * const this /* r29 */, class BinStream & d /* r30 */) {
    // References
    // -> class FilePath sRoot;
    // -> class Debug TheDebug;
    // -> static int gRev;
}

// Range: 0x803E30F4 -> 0x803E3128
void UIPicture::PostLoad(class UIPicture * const this /* r31 */) {}

// Range: 0x803E3128 -> 0x803E3180
void UIPicture::Poll(class UIPicture * const this /* r31 */) {}

// Range: 0x803E3180 -> 0x803E31B4
void UIPicture::Exit(class UIPicture * const this /* r31 */) {}

// Range: 0x803E31B4 -> 0x803E3300
void UIPicture::SetTex(class UIPicture * const this /* r29 */, const class FilePath & path /* r30 */) {
    // References
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__6Loader;
    // -> struct [anonymous] __RTTI__10FileLoader;
    // -> class LoadMgr TheLoadMgr;
    // -> class Debug TheDebug;
    // -> struct [anonymous] __vt__8FilePath;
}

// Range: 0x803E3300 -> 0x803E33A4
void UIPicture::FinishLoading(class UIPicture * const this /* r31 */) {}

// Range: 0x803E33A4 -> 0x803E349C
void UIPicture::HookupMesh(class UIPicture * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> class LoadMgr TheLoadMgr;
}

// Range: 0x803E349C -> 0x803E34C4
void UIPicture::SetHookTex() {
    // References
    // -> class FilePath sRoot;
}

static class Symbol _s; // size: 0x4, address: 0x80A51D1C
static class Symbol _s; // size: 0x4, address: 0x80A51D24
// Range: 0x803E34C4 -> 0x803E3970
class DataNode UIPicture::Handle(class UIPicture * const this /* r29 */, class DataArray * _msg /* r30 */, unsigned char _warn /* r31 */) {
    // Local variables
    class Symbol _type; // r1+0x28
    class MessageTimer _mt; // r1+0x38
    class DataNode _n; // r1+0x30

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

static class Symbol _s; // size: 0x4, address: 0x80A51D2C
static class Symbol _s; // size: 0x4, address: 0x80A51D34
// Range: 0x803E3970 -> 0x803E3B54
unsigned char UIPicture::SyncProperty(class UIPicture * const this /* r31 */, class DataNode & _val /* r27 */, class DataArray * _prop /* r28 */, int _i /* r29 */, enum PropOp _op /* r30 */) {
    // References
    // -> static class Symbol _s;
    // -> class FilePath sRoot;
    // -> struct [anonymous] __vt__8FilePath;
    // -> static class Symbol _s;
}

struct {
    // total size: 0x14C
} __vt__9UIPicture; // size: 0x14C, address: 0x808E5854
struct {
    // total size: 0x8
} __RTTI__9UIPicture; // size: 0x8, address: 0x808E59E8

