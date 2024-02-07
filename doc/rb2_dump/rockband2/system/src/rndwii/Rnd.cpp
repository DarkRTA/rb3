/*
    Compile unit: C:\rockband2\system\src\rndwii\Rnd.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805578B4 -> 0x8055AFAC
*/
class DataArray * types; // size: 0x4, address: 0x80A54008
class Symbol name; // size: 0x4, address: 0x80A54010
class Symbol name; // size: 0x4, address: 0x80A54018
class Symbol name; // size: 0x4, address: 0x80A54020
class WiiRnd TheWiiRnd; // size: 0x280, address: 0x80982740
class Rnd & TheRnd; // size: 0x4, address: 0x80A54024
unsigned char gFinishFrame; // size: 0x1, address: 0x80A54028
unsigned char gPreInitComplete; // size: 0x1, address: 0x80A54029
unsigned char gInitComplete; // size: 0x1, address: 0x80A5402A
class WiiDrawTarget * sCurrentTarget; // size: 0x4, address: 0x80A5402C
class list : public _List_base {
    // total size: 0x8
};
class list sDelayedFreeList; // size: 0x8, address: 0x809829D0
class NgStats gNgStats[3]; // size: 0x84, address: 0x809829D8
class NgStats * TheNgStats; // size: 0x4, address: 0x80A47590
// Range: 0x805578B4 -> 0x805578C0
static void OnVIRetrace() {
    // References
    // -> unsigned char gFinishFrame;
}

static class Timer * _t; // size: 0x4, address: 0x80A54030
// Range: 0x805578C0 -> 0x80557950
void OnDrawSync() {
    // References
    // -> static class Timer * _t;
}

// Range: 0x80557950 -> 0x805579BC
void WiiDrawTarget::MakeDrawTarget(class WiiDrawTarget * const this /* r31 */) {
    // References
    // -> class WiiDrawTarget * sCurrentTarget;
}

// Range: 0x805579BC -> 0x805579F8
void * WiiOrthoProj::WiiOrthoProj(class WiiOrthoProj * const this /* r31 */) {
    // References
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x805579F8 -> 0x80557A4C
void * WiiOrthoProj::~WiiOrthoProj(class WiiOrthoProj * const this /* r30 */) {}

// Range: 0x80557A4C -> 0x80557AE8
void * WiiRnd::WiiRnd(class WiiRnd * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__6WiiRnd;
}

// Range: 0x80557AE8 -> 0x80557CD4
void * WiiRnd::~WiiRnd(class WiiRnd * const this /* r29 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
    // -> struct [anonymous] __vt__36ObjPtrList<11RndDrawable,9ObjectDir>;
}

// Range: 0x80557CD4 -> 0x80557CF4
static void WiiModal(unsigned char & fail /* r7 */, char * msg /* r0 */) {
    // References
    // -> class WiiRnd TheWiiRnd;
}

// Range: 0x80557CF4 -> 0x80557ECC
void WiiRnd::Modal(class WiiRnd * const this /* r28 */, unsigned char fail /* r29 */, char * msg /* r30 */, unsigned char wait /* r31 */) {
    // Local variables
    class Color clear; // r1+0x40
    char tmp[4000]; // r1+0x50
    class Rect r; // r1+0x30

    // References
    // -> class Debug TheDebug;
}

// Range: 0x80557ECC -> 0x805582BC
void WiiRnd::PreInit(class WiiRnd * const this /* r31 */) {
    // Local variables
    struct _GXRenderModeObj * rMode; // r28
    unsigned long tvFormat; // r0
    unsigned long scanMode; // r0
    float yScale; // f0
    unsigned int xfbHeight; // r0

    // References
    // -> unsigned char gPreInitComplete;
    // -> struct _GXRenderModeObj GXEurgb60Hz480IntDf;
    // -> struct _GXRenderModeObj GXPal528IntDf;
    // -> struct _GXRenderModeObj GXEurgb60Hz480Prog;
    // -> struct _GXRenderModeObj GXNtsc480IntDf;
    // -> struct _GXRenderModeObj GXNtsc480Prog;
    // -> class PlatformMgr ThePlatformMgr;
}

// Range: 0x805582BC -> 0x80558570
void WiiRnd::Init(class WiiRnd * const this /* r31 */) {
    // References
    // -> unsigned char gInitComplete;
    // -> class GPUQueue & GPUMem;
    // -> class WiiDrawTarget * sCurrentTarget;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Symbol name;
    // -> class Debug TheDebug;
    // -> unsigned char gPreInitComplete;
}

class WiiTexRenderer : public RndTexRenderer {
    // total size: 0xB0
};
// Range: 0x80558570 -> 0x80558574
void WiiRnd::WiiPreInit() {}

// Range: 0x80558574 -> 0x8055879C
void WiiRnd::GXReInit(class WiiRnd * const this /* r29 */, unsigned char flush /* r30 */) {
    // Local variables
    float yScale; // f0
    unsigned int xfbHeight; // r0
}

// Range: 0x8055879C -> 0x80558830
void WiiRnd::Terminate(class WiiRnd * const this /* r31 */) {}

// Range: 0x80558830 -> 0x80558838
void WiiRnd::SetAspect() {}

// Range: 0x80558838 -> 0x80558854
float WiiRnd::YRatio() {}

// Range: 0x80558854 -> 0x80558968
void WiiRnd::ExecProgressiveScan(class WiiRnd * const this /* r31 */) {
    // Local variables
    struct _GXRenderModeObj * rMode; // r4
    unsigned long tvFormat; // r0

    // References
    // -> struct _GXRenderModeObj GXMpal480IntDf;
    // -> struct _GXRenderModeObj GXMpal480Prog;
    // -> struct _GXRenderModeObj GXEurgb60Hz480IntDf;
    // -> struct _GXRenderModeObj GXPal528IntDf;
    // -> struct _GXRenderModeObj GXEurgb60Hz480Prog;
    // -> struct _GXRenderModeObj GXNtsc480IntDf;
    // -> struct _GXRenderModeObj GXNtsc480Prog;
}

// Range: 0x80558968 -> 0x805589A0
unsigned char WiiRnd::Ntsc() {
    // Local variables
    unsigned int mode; // r0
}

// Range: 0x805589A0 -> 0x80558B2C
void WiiRnd::ConfigureRenderMode(class WiiRnd * const this /* r30 */) {
    // Local variables
    float kfVideoAspectRatio; // f0
    float kfRenderAspectRatio; // f30
    float kfViewAspectRatio; // f2
    float kfPixelAspectRatio; // f3
}

// Range: 0x80558B2C -> 0x80558B4C
void WiiRnd::SetSync() {}

// Range: 0x80558B4C -> 0x80558BD0
void WiiRnd::SyncFree(void * pMem /* r31 */) {
    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__PQ211stlpmtx_std14_List_node<Pv>;
    // -> unsigned char gStlAllocNameLookup;
    // -> class list sDelayedFreeList;
}

struct {
    // total size: 0x8
} __RTTI__PQ211stlpmtx_std14_List_node<Pv>; // size: 0x8, address: 0x809189B0
struct _List_iterator : public _List_iterator_base {
    // total size: 0x4
};
// Range: 0x80558BD0 -> 0x80558C4C
void WiiRnd::SyncDestroy() {
    // Local variables
    struct _List_iterator it; // r1+0x10

    // References
    // -> class list sDelayedFreeList;
}

static class Timer * _t; // size: 0x4, address: 0x80A54038
static class Timer * _t; // size: 0x4, address: 0x80A54040
static class Timer * _t; // size: 0x4, address: 0x80A54048
static class Timer * _t; // size: 0x4, address: 0x80A54050
// Range: 0x80558C4C -> 0x8055908C
void WiiRnd::BeginDrawing(class WiiRnd * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x34
    unsigned long z; // r1+0x30

    // References
    // -> class WiiMat * sCurrent;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> class GPUQueue & GPUMem;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> unsigned char gFinishFrame;
    // -> unsigned char gInitComplete;
    // -> unsigned char gPreInitComplete;
    // -> class PlatformMgr ThePlatformMgr;
}

static class Timer * _t; // size: 0x4, address: 0x80A54058
static class Timer * _t; // size: 0x4, address: 0x80A54060
static class Timer * _t; // size: 0x4, address: 0x80A54068
static class Timer * _t; // size: 0x4, address: 0x80A54070
// Range: 0x8055908C -> 0x805593DC
void WiiRnd::BeginDrawing(class WiiRnd * const this /* r31 */) {
    // Local variables
    struct _List_iterator it; // r1+0x2C
    unsigned long z; // r1+0x28

    // References
    // -> class WiiMat * sCurrent;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> class GPUQueue & GPUMem;
    // -> static class Timer * _t;
    // -> static class Timer * _t;
    // -> unsigned char gFinishFrame;
    // -> unsigned char gInitComplete;
    // -> unsigned char gPreInitComplete;
}

// Range: 0x805593DC -> 0x80559450
void WiiRnd::EndDrawing(class WiiRnd * const this /* r31 */) {
    // References
    // -> class GPUQueue & GPUMem;
    // -> unsigned char gInitComplete;
    // -> unsigned char gPreInitComplete;
}

// Range: 0x80559450 -> 0x80559454
void WiiRnd::ClearBuffer() {}

// Range: 0x80559454 -> 0x80559738
void WiiRnd::DrawRect(class WiiRnd * const this /* r30 */, const class Rect & r /* r27 */, const class Color & c /* r29 */, class RndMat * mat /* r28 */, const class Color * right /* r26 */, const class Color * bottom /* r25 */) {
    // Local variables
    float savedProjection[7]; // r1+0x20
    unsigned long c1; // r31
    unsigned long c2; // r30
    unsigned long c3; // r26
    unsigned long c4; // r29
    class WiiMat * pass; // [invalid]
    unsigned char defaultMat; // r25

    // References
    // -> class Rnd & TheRnd;
}

// Range: 0x80559738 -> 0x805597F8
static void SetupDrawStringMaterial(const class Color & c /* r31 */) {}

// Range: 0x805597F8 -> 0x80559830
static void SetupDrawStringVertexDesc() {}

// Range: 0x80559830 -> 0x80559BC8
float WiiRnd::DrawString(class WiiRnd * const this /* r18 */, const char * s /* r19 */, const class Vector2 & place /* r20 */, const class Color & c /* r17 */) {
    // Local variables
    float savedProjection[7]; // r1+0x40
    class Vector2 pos; // r1+0x18
    void * image; // r1+0x14
    long xChar; // r1+0x10
    long yChar; // r1+0xC
    long width; // r1+0x8
    long qw; // r30
    long qh; // r29
    struct _GXTexObj texObj; // r1+0x20
    float mtx[3][4]; // r1+0x60
    unsigned char lastEol; // r28
    signed short posLeft; // r27
    signed short posRight; // r26
    signed short posTop; // r25
    signed short posBottom; // r24
    signed short texLeft; // r23
    signed short texRight; // r22
    signed short texTop; // r21
    signed short texBottom; // r17

    // References
    // -> class WiiMat * sCurrent;
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80559BC8 -> 0x80559CB4
void WiiRnd::DrawLine(const class Vector3 & start /* r29 */, const class Vector3 & end /* r30 */, const class Color & c /* r31 */) {}

// Range: 0x80559CB4 -> 0x80559CE8
void WiiRnd::DoWorldEnd(class WiiRnd * const this /* r31 */) {}

// Range: 0x80559CE8 -> 0x80559D30
void WiiRnd::DoPostProcess(class WiiRnd * const this /* r30 */) {
    // References
    // -> class WiiMat * sCurrent;
}

// Range: 0x80559D30 -> 0x80559D94
void MakeWiiMtx() {}

// Range: 0x80559D94 -> 0x80559E50
void MakeWiiMtxTex() {
    // Local variables
    float x; // f6
    float y; // f7
}

static class Symbol _s; // size: 0x4, address: 0x80A54078
static class Symbol _s; // size: 0x4, address: 0x80A54080
static class Symbol _s; // size: 0x4, address: 0x80A54088
static class Symbol _s; // size: 0x4, address: 0x80A54090
static class Symbol _s; // size: 0x4, address: 0x80A54098
// Range: 0x80559E50 -> 0x8055A604
class DataNode WiiRnd::Handle(class WiiRnd * const this /* r28 */, class DataArray * _msg /* r29 */, unsigned char _warn /* r30 */) {
    // Local variables
    class Symbol _type; // r1+0x34
    class MessageTimer _mt; // r1+0x40
    class DataNode _n; // r1+0x38

    // References
    // -> class Debug TheDebug;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> static class Symbol _s;
    // -> float sLowCycles2Ms;
    // -> float sHighCycles2Ms;
    // -> static class Symbol _s;
    // -> unsigned char sActive;
}

// Range: 0x8055A604 -> 0x8055A640
void WiiRnd::CopyBuffer(class WiiRnd * const this /* r31 */) {}

// Range: 0x8055A640 -> 0x8055A6A4
void WiiRnd::SetOrthoProj(class WiiRnd * const this /* r31 */) {}

// Range: 0x8055A6A4 -> 0x8055A730
void WiiRnd::ResetStats() {
    // References
    // -> class NgStats * TheNgStats;
    // -> class NgStats gNgStats[3];
}

// Range: 0x8055A730 -> 0x8055A9DC
float WiiRnd::UpdateOverlay(class WiiRnd * const this /* r29 */, float y /* f31 */) {
    // References
    // -> class NgStats * TheNgStats;
    // -> class NgStats gNgStats[3];
}

// Range: 0x8055A9DC -> 0x8055AACC
void WiiRnd::SetFullScrProj(class WiiRnd * const this /* r30 */) {
    // Local variables
    float screenOrthoProjXfm[4][4]; // r1+0x38
    float identityXfm[3][4]; // r1+0x8
}

// Range: 0x8055AACC -> 0x8055AB64
void WiiRnd::DrawQuad() {}

// Range: 0x8055AB64 -> 0x8055AC34
void WiiRnd::DrawQuad(const class Rect & rect /* r31 */) {}

// Range: 0x8055AC34 -> 0x8055AC74
void WiiRnd::SetScreenDimming(class WiiRnd * const this /* r30 */, unsigned char screenDimming /* r31 */) {}

// Range: 0x8055AC74 -> 0x8055ACBC
void WiiRnd::ClearSwapTables() {
    // Local variables
    int i; // r31
}

// Range: 0x8055ACBC -> 0x8055AF1C
void WiiRnd::DrawBlackBackground(class WiiRnd * const this /* r29 */) {
    // Local variables
    struct _GXColor matColor; // r1+0x14
    struct _GXColor ambColor; // r1+0x10
}

// Range: 0x8055AF1C -> 0x8055AF24
void WiiRnd::SetTriFrameRendering() {}

struct {
    // total size: 0xAC
} __vt__8WiiLight; // size: 0xAC, address: 0x80918BC0
struct {
    // total size: 0x8
} __RTTI__8WiiLight; // size: 0x8, address: 0x80918CA8
struct {
    // total size: 0xF4
} __vt__6WiiRnd; // size: 0xF4, address: 0x80918CB0
struct {
    // total size: 0x8
} __RTTI__6WiiRnd; // size: 0x8, address: 0x80918DD8
struct {
    // total size: 0x10
} __vt__13WiiDrawTarget; // size: 0x10, address: 0x80918DE0
class _STLP_alloc_proxy : public StlNodeAlloc {
    // total size: 0x8
public:
    struct _List_node_base _M_data; // offset 0x0, size 0x8
};
class _List_base {
    // total size: 0x8
public:
    class _STLP_alloc_proxy _M_node; // offset 0x0, size 0x8
};
// Range: 0x8055AF24 -> 0x8055AFAC
static void __sinit_\Rnd_cpp() {
    // References
    // -> class list sDelayedFreeList;
    // -> class Rnd & TheRnd;
    // -> class WiiRnd TheWiiRnd;
}

class _List_node : public _List_node_base {
    // total size: 0xC
public:
    void * _M_data; // offset 0x8, size 0x4
};
class StlNodeAlloc {
    // total size: 0x1
};
struct _GXRenderModeObj GXMpal480IntDf; // size: 0x3C, address: 0x8093C5C8
struct _GXRenderModeObj GXMpal480Prog; // size: 0x3C, address: 0x8093C604
struct _GXRenderModeObj GXEurgb60Hz480IntDf; // size: 0x3C, address: 0x8093C67C
struct _GXRenderModeObj GXPal528IntDf; // size: 0x3C, address: 0x8093C640
struct _GXRenderModeObj GXEurgb60Hz480Prog; // size: 0x3C, address: 0x8093C6B8
struct _GXRenderModeObj GXNtsc480IntDf; // size: 0x3C, address: 0x8093C550
struct _GXRenderModeObj GXNtsc480Prog; // size: 0x3C, address: 0x8093C58C

