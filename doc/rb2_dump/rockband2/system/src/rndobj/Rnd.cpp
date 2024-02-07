/*
    Compile unit: C:\rockband2\system\src\rndobj\Rnd.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x804F4714 -> 0x804F93D8
*/
class Symbol name; // size: 0x4, address: 0x80A5371C
class Symbol name; // size: 0x4, address: 0x80A53724
class Symbol name; // size: 0x4, address: 0x80A5372C
class Symbol name; // size: 0x4, address: 0x80A53734
class Symbol name; // size: 0x4, address: 0x80A5373C
static int gCurHeap; // size: 0x4, address: 0x80A53740
// Range: 0x804F4714 -> 0x804F471C
void Rnd::ShowConsole() {}

// Range: 0x804F471C -> 0x804F48A8
void * Rnd::Rnd(class Rnd * const this /* r31 */) {
    // Local variables
    int i; // r5

    // References
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
    // -> struct [anonymous] __vt__3Rnd;
}

class _List_node : public _List_node_base {
    // total size: 0x18
public:
    struct PointTest _M_data; // offset 0x8, size 0x10
};
class _List_node : public _List_node_base {
    // total size: 0xC
public:
    class PostProcessor * _M_data; // offset 0x8, size 0x4
};
struct SortPostProc {
    // total size: 0x1
};
// Range: 0x804F48A8 -> 0x804F48E8
float Rnd::YRatio() {
    // Local variables
    float ratio[4]; // r1+0x8
}

// Range: 0x804F48E8 -> 0x804F48FC
static void TerminateCallback() {
    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x804F48FC -> 0x804F4998
void Rnd::DrawRectScreen() {
    // Local variables
    float w; // f4
    float h; // f1
}

// Range: 0x804F4998 -> 0x804F4A30
float Rnd::DrawStringScreen() {
    // Local variables
    float w; // f2
    float h; // f31
}

// Range: 0x804F4A30 -> 0x804F4BF4
void Rnd::SetupFont(class Rnd * const this /* r29 */) {
    // Local variables
    int i; // r31
    class DataArray * lower; // r30
    int j; // r27
    class DataArray * line; // r26
    int k; // r25
    float y; // f0
}

// Range: 0x804F4BF4 -> 0x804F5800
void Rnd::Init(class Rnd * const this /* r30 */) {
    // Local variables
    class DataArray * config; // r29

    // References
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> const char * kAssertStr;
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std17_List_node<PFv_v>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> class ObjectDir * sMainDir;
}

class RndSet : public Object {
    // total size: 0x48
protected:
    class ObjPtrList mObjects; // offset 0x28, size 0x14
    class vector mProps; // offset 0x3C, size 0xC
};
class RndTransArray : public RndAnimatable, public RndTransformable {
    // total size: 0x130
    class ObjPtrList mTargets; // offset 0xC8, size 0x14
    class TransLayout * mLayout; // offset 0xDC, size 0x4
    class GridLayout * mGridLayout; // offset 0xE0, size 0x4
    class RingLayout * mRingLayout; // offset 0xE4, size 0x4
    class TnmLayout * mTnmLayout; // offset 0xE8, size 0x4
};
struct _GXTlutObj {
    // total size: 0xC
    unsigned long dummy[3]; // offset 0x0, size 0xC
};
enum _GXTexMapID {
    GX_TEXMAP0 = 0,
    GX_TEXMAP1 = 1,
    GX_TEXMAP2 = 2,
    GX_TEXMAP3 = 3,
    GX_TEXMAP4 = 4,
    GX_TEXMAP5 = 5,
    GX_TEXMAP6 = 6,
    GX_TEXMAP7 = 7,
    GX_MAX_TEXMAP = 8,
    GX_TEXMAP_NULL = 255,
    GX_TEX_DISABLE = 256,
};
class WiiTex : public RndTex, public WiiDrawTarget {
    // total size: 0xF8
    struct _GXTexObj mTexture; // offset 0x7C, size 0x20
    unsigned char * mImageData; // offset 0x9C, size 0x4
    unsigned long mFormat; // offset 0xA0, size 0x4
    struct _GXTexObj mAlphaTexture; // offset 0xA4, size 0x20
    unsigned char * mAlphaImageData; // offset 0xC4, size 0x4
    int mHasAlpha; // offset 0xC8, size 0x4
    unsigned char * mMovieImage[2]; // offset 0xCC, size 0x8
    unsigned char mLoading; // offset 0xD4, size 0x1
    struct _GXTlutObj mPalette; // offset 0xD8, size 0xC
    unsigned char * mPaletteData; // offset 0xE4, size 0x4
    int mExtension; // offset 0xE8, size 0x4
    unsigned char mDisableFiltering; // offset 0xEC, size 0x1
    unsigned char mAlleyTarget; // offset 0xED, size 0x1
    int mLockInfo; // offset 0xF0, size 0x4
    int mSize; // offset 0xF4, size 0x4
};
class ObjOwnerPtr : public ObjRef {
    // total size: 0xC
protected:
    class Object * mOwner; // offset 0x4, size 0x4
    class WiiTex * mPtr; // offset 0x8, size 0x4
};
class RndTexMovie : public RndDrawable, public RndPollable {
    // total size: 0xA0
protected:
    class ObjOwnerPtr mTex; // offset 0x3C, size 0xC
    unsigned char mLoop; // offset 0x48, size 0x1
    unsigned char mPreload; // offset 0x49, size 0x1
    unsigned char mDrawPreClear; // offset 0x4A, size 0x1
    class FilePath mFile; // offset 0x4C, size 0xC
    class Movie mMovie; // offset 0x58, size 0x4
};
class RndScreenMask : public RndDrawable {
    // total size: 0xA0
protected:
    class ObjPtr mMat; // offset 0x34, size 0xC
    class Color mColor; // offset 0x40, size 0x10
    class Rect mRect; // offset 0x50, size 0x10
    unsigned char mUseCurrentRect; // offset 0x60, size 0x1
};
// Range: 0x804F5800 -> 0x804F58BC
void Rnd::Terminate(class Rnd * const this /* r31 */) {
    // References
    // -> class Debug TheDebug;
}

static class DebugWarner _dw; // size: 0x100, address: 0x809804A8
// Range: 0x804F58BC -> 0x804F5B00
void Rnd::TestPoint(class Rnd * const this /* r29 */, class RndFlare * f /* r30 */) {
    // Local variables
    class Vector2 v2; // r1+0x10
    float dist; // f31
    struct PointTest p; // r1+0x18

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<Q23Rnd9PointTest>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class Debug TheDebug;
    // -> static class DebugWarner _dw;
    // -> class RndCam * sCurrent;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<Q23Rnd9PointTest>; // size: 0x8, address: 0x808FF7E0
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x804F5B00 -> 0x804F5BAC
void Rnd::RemovePointTest(class Rnd * const this /* r29 */, class RndFlare * f /* r30 */) {
    // Local variables
    struct _List_iterator i; // r1+0x1C
}

static class DataArray * timerScript; // size: 0x4, address: 0x80A53744
// Range: 0x804F5BAC -> 0x804F6120
float Rnd::DrawTimers(class Rnd * const this /* r30 */, float topY /* f27 */) {
    // Local variables
    int count; // r31
    struct _List_iterator t; // r1+0x58
    float timerHeight; // f31
    float topMargin; // f30
    float leftMargin; // f29
    class Rect rect; // r1+0xB0
    class Color color; // r1+0xA0
    class Color budgetColor; // r1+0x90
    class Color worstColor; // r1+0x80
    float sx; // f28
    int i; // r29
    class Vector2 place; // r1+0x68
    float ms; // f0

    // References
    // -> class list sTimers;
    // -> static class DataArray * timerScript;
}

// Range: 0x804F6120 -> 0x804F61C0
void Rnd::RegisterPostProcessor(class Rnd * const this /* r30 */, class PostProcessor * p /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std28_List_node<P13PostProcessor>;
    // -> unsigned char gStlAllocNameLookup;
}

struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std28_List_node<P13PostProcessor>; // size: 0x8, address: 0x808FF838
// Range: 0x804F61C0 -> 0x804F6254
void Rnd::UnregisterPostProcessor(class PostProcessor * p /* r31 */) {}

// Range: 0x804F627C -> 0x804F637C
void Rnd::BeginDrawing(class Rnd * const this /* r31 */) {
    // References
    // -> class list sTimers;
}

// Range: 0x804F637C -> 0x804F63DC
void Rnd::EndWorld(class Rnd * const this /* r31 */) {}

// Range: 0x804F63DC -> 0x804F6444
void Rnd::DoWorldEnd() {
    // Local variables
    struct _List_iterator postIter; // r1+0x10
    struct _List_iterator postEnd; // r1+0xC
}

// Range: 0x804F6444 -> 0x804F64AC
void Rnd::DoPostProcess() {
    // Local variables
    struct _List_iterator postIter; // r1+0x10
    struct _List_iterator postEnd; // r1+0xC
}

// Range: 0x804F64AC -> 0x804F652C
void Rnd::DrawPreClear() {
    // Local variables
    class iterator meshItr; // r1+0x18
}

static class Timer * _t; // size: 0x4, address: 0x80A5374C
// Range: 0x804F652C -> 0x804F6634
void Rnd::EndDrawing(class Rnd * const this /* r31 */) {
    // Local variables
    class AutoTimer _at; // r1+0xC

    // References
    // -> class RndCam * sCurrent;
    // -> static class Timer * _t;
}

// Range: 0x804F6634 -> 0x804F6690
void Rnd::SetShowTimers(class Rnd * const this /* r30 */, unsigned char s /* r31 */) {}

// Range: 0x804F6690 -> 0x804F669C
unsigned char Rnd::ShowTimers() {}

// Range: 0x804F669C -> 0x804F6704
float Rnd::UpdateOverlay(float topY /* f31 */) {}

static class Timer * cpuTimer; // size: 0x4, address: 0x80A53754
static class Timer * gsTimer; // size: 0x4, address: 0x80A5375C
// Range: 0x804F6704 -> 0x804F6878
void Rnd::UpdateRate(class Rnd * const this /* r29 */) {
    // References
    // -> static class Timer * gsTimer;
    // -> static class Timer * cpuTimer;
}

// Range: 0x804F6878 -> 0x804F6904
void Rnd::UpdateHeap(class Rnd * const this /* r30 */) {
    // Local variables
    int free; // r1+0x10
    int frag; // r1+0xC
    int biggest; // r1+0x8

    // References
    // -> static int gCurHeap;
}

// Range: 0x804F6904 -> 0x804F6DDC
void Rnd::CreateDefaults(class Rnd * const this /* r30 */) {
    // References
    // -> struct [anonymous] __RTTI__6RndMat;
    // -> class Symbol name;
    // -> struct [anonymous] __RTTI__8RndLight;
    // -> class Symbol name;
    // -> struct [anonymous] __RTTI__10RndEnviron;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __RTTI__Q23Hmx6Object;
    // -> struct [anonymous] __RTTI__6RndCam;
    // -> class Symbol name;
    // -> class ObjectDir * sMainDir;
}

// Range: 0x804F6DDC -> 0x804F6F64
class DataNode Rnd::DumpMaterialList() {
    // Local variables
    char name[64]; // r1+0x8
    int a; // r31
    int x; // r31
    class File * filePtr; // r29

    // References
    // -> class RndMat * materialTrackingList[1024];
    // -> int materialTrackingCount;
    // -> class Debug TheDebug;
}

// Range: 0x804F6F64 -> 0x804F716C
class DataNode Rnd::DumpTextureList() {
    // Local variables
    char name[64]; // r1+0x18
    int a; // r30
    int x; // r30
    int total_bytes; // r28
    class File * j; // r27
    int total_bytes_wii; // r27
    class WiiTex * tx; // r0
    int bytes; // r9

    // References
    // -> class RndTex * textureTrackingList[1024];
    // -> class Debug TheDebug;
}

static class Symbol _s; // size: 0x4, address: 0x80A53764
static class Symbol _s; // size: 0x4, address: 0x80A5376C
static class Symbol _s; // size: 0x4, address: 0x80A53774
static class Symbol _s; // size: 0x4, address: 0x80A5377C
static class Symbol _s; // size: 0x4, address: 0x80A53784
static class Symbol _s; // size: 0x4, address: 0x80A5378C
static class Symbol _s; // size: 0x4, address: 0x80A53794
static class Symbol _s; // size: 0x4, address: 0x80A5379C
static class Symbol _s; // size: 0x4, address: 0x80A537A4
static class Symbol _s; // size: 0x4, address: 0x80A537AC
static class Symbol _s; // size: 0x4, address: 0x80A537B4
static class Symbol _s; // size: 0x4, address: 0x80A537BC
static class Symbol _s; // size: 0x4, address: 0x80A537C4
static class Symbol _s; // size: 0x4, address: 0x80A537CC
static class Symbol _s; // size: 0x4, address: 0x80A537D4
static class Symbol _s; // size: 0x4, address: 0x80A537DC
static class Symbol _s; // size: 0x4, address: 0x80A537E4
static class Symbol _s; // size: 0x4, address: 0x80A537EC
static class Symbol _s; // size: 0x4, address: 0x80A537F4
static class Symbol _s; // size: 0x4, address: 0x80A537FC
static class Symbol _s; // size: 0x4, address: 0x80A53804
static class Symbol _s; // size: 0x4, address: 0x80A5380C
static class Symbol _s; // size: 0x4, address: 0x80A53814
static class Symbol _s; // size: 0x4, address: 0x80A5381C
static class Symbol _s; // size: 0x4, address: 0x80A53824
static class Symbol _s; // size: 0x4, address: 0x80A5382C
static class Symbol _s; // size: 0x4, address: 0x80A53834
static class Symbol _s; // size: 0x4, address: 0x80A5383C
static class Symbol _s; // size: 0x4, address: 0x80A53844
static class Symbol _s; // size: 0x4, address: 0x80A5384C
static class Symbol _s; // size: 0x4, address: 0x80A53854
static class Symbol _s; // size: 0x4, address: 0x80A5385C
static class Symbol _s; // size: 0x4, address: 0x80A53864
static class Symbol _s; // size: 0x4, address: 0x80A5386C
static class Symbol _s; // size: 0x4, address: 0x80A53874
static class Symbol _s; // size: 0x4, address: 0x80A5387C
static class Symbol _s; // size: 0x4, address: 0x80A53884
static class Symbol _s; // size: 0x4, address: 0x80A5388C
static class Symbol _s; // size: 0x4, address: 0x80A53894
static class Symbol _s; // size: 0x4, address: 0x80A5389C
static class Symbol _s; // size: 0x4, address: 0x80A538A4
static class Symbol _s; // size: 0x4, address: 0x80A538AC
static class Symbol _s; // size: 0x4, address: 0x80A538B4
static class Symbol _s; // size: 0x4, address: 0x80A538BC
static class Symbol _s; // size: 0x4, address: 0x80A538C4
static class Symbol _s; // size: 0x4, address: 0x80A538CC
static class Symbol _s; // size: 0x4, address: 0x80A538D4
// Range: 0x804F716C -> 0x804F8850
class DataNode Rnd::Handle(class Rnd * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x18
    class MessageTimer _mt; // r1+0xA0
    class DataNode r; // r1+0x98
    class DataNode r; // r1+0x90
    class DataNode r; // r1+0x88
    class DataNode r; // r1+0x80
    class DataNode r; // r1+0x78
    class DataNode r; // r1+0x70
    class DataNode r; // r1+0x68
    class DataNode r; // r1+0x60
    class DataNode r; // r1+0x58
    class DataNode r; // r1+0x50
    class DataNode r; // r1+0x48
    class DataNode r; // r1+0x40
    class DataNode r; // r1+0x38
    class DataNode r; // r1+0x30
    class DataNode r; // r1+0x28
    class DataNode r; // r1+0x20

    // References
    // -> class DebugNotifier TheDebugNotifier;
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
}

// Range: 0x804F8850 -> 0x804F8914
class DataNode Rnd::OnShowOverlay(const class DataArray * msg /* r30 */) {
    // Local variables
    class RndOverlay * o; // r31
}

// Range: 0x804F8914 -> 0x804F89C0
class DataNode Rnd::OnToggleHeap(class Rnd * const this /* r31 */) {
    // Local variables
    int numHeaps; // r0

    // References
    // -> static int gCurHeap;
}

// Range: 0x804F89C0 -> 0x804F8AC4
class DataNode Rnd::OnReflect(const class DataArray * a /* r29 */) {
    // Local variables
    class RndOverlay * o; // r0
    int i; // r30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x804F8AC4 -> 0x804F8B40
class DataNode Rnd::OnToggleOverlay(const class DataArray * a /* r31 */) {
    // Local variables
    class RndOverlay * o; // r0
}

// Range: 0x804F8B40 -> 0x804F8B48
void Rnd::SetProcAndLock() {}

// Range: 0x804F8B48 -> 0x804F8B50
unsigned char Rnd::ProcAndLock() {}

// Range: 0x804F8B50 -> 0x804F8B78
void Rnd::ResetProcCounter() {}

// Range: 0x804F8B78 -> 0x804F8D70
void Rnd::AddPreClearDraw(class Rnd * const this /* r31 */, class RndDrawable * object /* r28 */) {
    // Local variables
    class iterator meshItr; // r1+0x20

    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804F8D70 -> 0x804F8ED8
void Rnd::RemovePreClearDraw(class Rnd * const this /* r28 */, class RndDrawable * object /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x804F8ED8 -> 0x804F8F10
int Rnd::GetUserNumber() {
    // Local variables
    int count; // r5
    int i; // r6
}

// Range: 0x804F8F10 -> 0x804F8F80
void Rnd::AddUserNumber() {
    // Local variables
    unsigned char userExists; // r6
    int i; // r7
    int i; // r6
}

// Range: 0x804F8F80 -> 0x804F8FB4
void Rnd::RemoveUserNumber() {
    // Local variables
    int i; // r6
}

// Range: 0x804F8FB4 -> 0x804F8FDC
void Rnd::RemoveAllUserNumbers() {
    // Local variables
    int i; // r6
}

// Range: 0x804F8FDC -> 0x804F901C
class DataNode Rnd::OnShowConsole() {}

// Range: 0x804F901C -> 0x804F9074
class DataNode Rnd::OnToggleTimers(class Rnd * const this /* r31 */) {}

// Range: 0x804F9074 -> 0x804F9088
class DataNode Rnd::OnClearColorR() {}

// Range: 0x804F9088 -> 0x804F909C
class DataNode Rnd::OnClearColorG() {}

// Range: 0x804F909C -> 0x804F90B0
class DataNode Rnd::OnClearColorB() {}

// Range: 0x804F90B0 -> 0x804F9114
class DataNode Rnd::OnClearColorPacked() {}

// Range: 0x804F9114 -> 0x804F9208
class DataNode Rnd::OnSetClearColor(class Rnd * const this /* r30 */, const class DataArray * a /* r31 */) {}

// Range: 0x804F9208 -> 0x804F9360
class DataNode Rnd::OnSetClearColorPacked(class Rnd * const this /* r28 */, const class DataArray * a /* r29 */) {
    // Local variables
    class Color c; // r1+0x10
}

// Range: 0x804F9360 -> 0x804F93D8
class DataNode Rnd::OnScreenDump(class Rnd * const this /* r30 */, const class DataArray * a /* r31 */) {}

struct {
    // total size: 0xDC
} __vt__3Rnd; // size: 0xDC, address: 0x808FFD5C
struct {
    // total size: 0x8
} __RTTI__3Rnd; // size: 0x8, address: 0x808FFE58

